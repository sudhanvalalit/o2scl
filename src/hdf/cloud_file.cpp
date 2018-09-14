/*
  -------------------------------------------------------------------
  
  Copyright (C) 2016-2018, Andrew W. Steiner
  
  This file is part of O2scl.
  
  O2scl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  O2scl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with O2scl. If not, see <http://www.gnu.org/licenses/>.

  -------------------------------------------------------------------
*/
#include <o2scl/cloud_file.h>

using namespace o2scl;
using namespace o2scl_hdf;

cloud_file::cloud_file() {
  allow_wget=true;
  allow_curl=true;
  verbose=1;
  throw_on_fail=true;
  hash_type=sha256;
}

int cloud_file::hdf5_open_hash
(o2scl_hdf::hdf_file &hf, std::string file, 
 std::string url, std::string hash, std::string dir) {
  std::string fname;
  get_file_hash(file,url,hash,fname,dir);
  hf.open(fname);
  return 0;
}
    
int cloud_file::hdf5_open(o2scl_hdf::hdf_file &hf, std::string file,
			  std::string url, std::string dir) {
  return hdf5_open_hash(hf,file,url,"",dir);
}
  
int cloud_file::get_file(std::string file, std::string url, 
			 std::string &fname, std::string dir) {
  return get_file_hash(file,url,"",fname,dir);
}
    
int cloud_file::get_file_hash
(std::string file, std::string url,
 std::string hash, std::string &fname, std::string dir) {

#ifndef O2SCL_USE_BOOST_FILESYSTEM

  // File status object
  struct stat sb;
  // Return value of stat()
  int sret=0;

  // -------------------------------------------------------
  // Main directory section

  // Look for directory 
  bool dir_present=false;
  if (dir.length()>0) {
    if (verbose>1) {
      std::cout << "Using directory " << dir << std::endl;
    }
    sret=stat(dir.c_str(),&sb);
    if (sret==0) {
      dir_present=S_ISDIR(sb.st_mode);
    }
    if (dir_present==false) {
      if (verbose>0) {
	std::cout << "Directory '" << dir
		  << "' not present. Trying to create it." << std::endl;
      }
      // If not found, try to make it with 'mkdir'
      std::string cmd=((std::string)"mkdir -p ")+dir;
      if (verbose>1) {
	std::cout << "Directory specified but not present in filesystem."
		  << std::endl;
	std::cout << "Trying to create with command:\n\t"
		  << cmd << std::endl;
      }
      int mret=system(cmd.c_str());
      if (mret!=0) {
	if (verbose>1) {
	  std::cout << "Command to make directory '" << cmd
		    << "' failed." << std::endl;
	}
      } else {
	sret=stat(dir.c_str(),&sb);
	if (sret==0) {
	  dir_present=S_ISDIR(sb.st_mode);
	}
      }
    }
    if (sret!=0 || dir_present==false) {
      // If not found, prompt user for it
      std::cout << "Could not find or create directory '" << dir 
		<< ". Please enter new directory name."
		<< std::endl;
      std::cin >> dir;
      // Check again
      dir_present=false;
      if (dir.length()>0) {
	sret=stat(dir.c_str(),&sb);
	if (sret==0) {
	  dir_present=S_ISDIR(sb.st_mode);
	}
      }
      // If that failed, then give up
      if (dir.length()==0 || sret!=0 || dir_present==false) {
	if (throw_on_fail) {
	  O2SCL_ERR("Could not find correct directory.",
		    o2scl::exc_efilenotfound);
	} else {
	  return o2scl::exc_efilenotfound;
	}
      }
    }
  }
  
  // End of directory section
  // -------------------------------------------------------

  // -------------------------------------------------------
  // Start of file section
    
  // Now look for the full data file
  if (dir.length()>0) {
    fname=dir+"/"+file;
  } else {
    fname=file;
  }
  bool file_present=false;
  bool valid_hash=false;
  sret=stat(fname.c_str(),&sb);
  if (sret==0) {
    file_present=S_ISREG(sb.st_mode);
  }

  // If there's no hash, assume it's valid
  if (hash.length()==0) valid_hash=true;
    
  // If the file was found, check the hash
  if (sret==0 && file_present && hash.length()>0) {
    std::string cmd;
    if (hash_type==sha256) {
      cmd=((std::string)"openssl dgst -sha256 ")+fname+
	" | awk '{print $2}'";
    } else if (hash_type==md5sum) {
      cmd=((std::string)"md5sum ")+fname+
	" | awk '{print $1}'";
    } else {
      cmd=((std::string)"md5 ")+fname+
	" | awk '{print $4}'";
    }
    if (verbose>1) {
      std::cout << "Checking hash with command:\n\t" << cmd
		<< std::endl;
    }
    std::string hash2=o2scl::pipe_cmd_string(cmd);
    o2scl::remove_whitespace(hash2);
    if (hash2==hash) {
      valid_hash=true;
      if (verbose>1) {
	std::cout << "Hash valid." << std::endl;
      }
    } else {
      if (verbose>1) {
	std::cout << "File hash " << hash2 << " does not match "
		  << hash << "." << std::endl;
      }
    }
  }
      
  if (sret!=0 || file_present==false || valid_hash==false) {
    // If it couldn't be found, try to download it
    int ret=1;
    if (allow_curl) {
      std::string cmd=((std::string)"cd ")+dir+"; curl -o "+
	file+" "+url;
      if (verbose>0) {
	std::cout << "Trying curl command:\n\t"
		  << cmd << std::endl;
      }
      ret=system(cmd.c_str());
    }
    if (allow_wget && ret!=0) {
      std::string cmd=((std::string)"cd ")+dir+"; wget -O "+file+
	" "+url;
      if (verbose>0) {
	std::cout << "File did not exist or read failed or invalid hash."
		  << std::endl;
	std::cout << "Trying wget command:\n\t"
		  << cmd << std::endl;
      }
      ret=system(cmd.c_str());
    }
    // Check to see if download command succeeded
    if (ret!=0) {
      if (throw_on_fail) {
	O2SCL_ERR("Failed to download file.",o2scl::exc_efilenotfound);
      } else {
	return o2scl::exc_efilenotfound;
      }
    }
    // Check to see if the file is there
    sret=stat(fname.c_str(),&sb);
    if (sret==0) {
      file_present=S_ISREG(sb.st_mode);
    }
    // If it's still not there, then give up
    if (sret!=0 || file_present==false) {
      if (throw_on_fail) {
	O2SCL_ERR("Could not find or download file.",
		  o2scl::exc_efilenotfound);
      } else {
	return o2scl::exc_efilenotfound;
      }
    }
  }

  // -------------------------------------------------------
  // Check hash if specified by the caller and it was originally
  // invalid
    
  if (hash.length()>0 && valid_hash==false) {
    std::string cmd;
    if (hash_type==sha256) {
      cmd=((std::string)"openssl dgst -sha256 ")+fname+
	" | awk '{print $2}'";
    } else if (hash_type==md5sum) {
      cmd=((std::string)"md5sum ")+fname+
	" | awk '{print $1}'";
    } else {
      cmd=((std::string)"md5 ")+fname+
	" | awk '{print $4}'";
    }
    if (verbose>1) {
      std::cout << "Checking hash with command:\n\t" << cmd
		<< std::endl;
    }
    std::string hash2=o2scl::pipe_cmd_string(cmd);
    o2scl::remove_whitespace(hash2);
    if (hash2!=hash) {
      O2SCL_ERR("Invalid hash after download in cloud_file. Wrong URL?",
		o2scl::exc_efailed);
    }
  }

  // -------------------------------------------------------
  // Output full filename
    
  if (verbose>1) {
    std::cout << "Success with file named '" << fname
	      << "'" << std::endl;
  }

#else

  std::cout << "Here6 " << dir << std::endl;
  boost::filesystem::path p(dir.c_str());
  std::cout << "Here7." << std::endl;
  std::cout << boost::filesystem::exists(p) << std::endl;
  std::cout << "Here7b." << std::endl;
  std::cout << boost::filesystem::is_directory(p) << std::endl;
  std::cout << "Here8." << std::endl;
  std::cout << boost::filesystem::is_regular_file(p) << std::endl;
  std::cout << "Here9." << std::endl;
  exit(-1);
      
#endif      
      
  return o2scl::success;
}

