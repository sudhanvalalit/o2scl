/*
  ───────────────────────────────────────────────────────────────────

  Copyright (C) 2022-2025, Andrew W. Steiner

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

  ───────────────────────────────────────────────────────────────────
*/
/** \file xml.h
    \brief File describing pugixml interface
*/
#ifndef O2SCL_XML_H
#define O2SCL_XML_H

#include <string>
#include <vector>

#include <o2scl/err_hnd.h>
#include <o2scl/set_pugixml.h>

#ifdef O2SCL_SET_PUGIXML
#include "pugixml.hpp"
#endif

namespace o2scl {

#ifdef O2SCL_SET_PUGIXML

  /** \brief A base class for pugixml walkers
   */
  class walker_base  : public pugi::xml_tree_walker {
    
  public:

    /** \brief The depth of the last node traversed
     */
    int last_depth;

    /** \brief Verbosity parameter, principally for debugging
     */
    int verbose;
    
    /** \brief Current hierarchy of node names
     */
    std::vector<std::string> names;

    /** \brief Begin a traversal
     */
    virtual bool begin(pugi::xml_node &node) {
      last_depth=-1;
      verbose=0;
      names.clear();
      return true;
    }
      
    walker_base() {
    }
    
  };
  
  /** \brief A pugixml walker which outputs the full contents of the 
      node (no attributes yet) to an ostream
   */
  class ostream_walker : public walker_base {
    
  public:

    /** \brief The output stream to be used (defaults to &cout)
     */
    std::ostream *outs;

    ostream_walker() {
      outs=&std::cout;
    }

    /** \brief Output XML for each node
     */
    virtual bool for_each(pugi::xml_node &node) {

      if (verbose>0) {
        (*outs) << " d: "
                  << depth() << " l: " << last_depth << std::endl;
      }
      
      if (depth()<last_depth) {
        int n=last_depth-depth();
        for(int i=0;i<n;i++) {
          for (int j = 0; j < depth()-i+n-1; j++) {
            (*outs) << "  ";
          }
          (*outs) << "</" << names[names.size()-1] << ">"
                    << std::endl;
          names.pop_back();
        }
      }
      
      if (((std::string)node.name()).length()>0) {
        names.push_back(node.name());
      }
      
      for (int i = 0; i < depth(); i++) {
        (*outs) << "  ";
      }
      
      if (((std::string)node.name()).length()>0) {
        (*outs) << "<" << node.name()
                  << ">" << node.value();
      } else {
        (*outs) << node.value();
      }
      if (verbose>0) {
        for(size_t k=0;k<names.size();k++) {
          (*outs) << "." << names[k] << ". ";
        }
      }
      (*outs) << std::endl;
      
      last_depth=depth();
      
      return true;
    }

    /** \brief Complete the XML output by ending all of the tags
     */
    virtual bool end(pugi::xml_node &node) {
      int n=last_depth;
      for(int i=0;i<n;i++) {
        if (names.size()>0) {
          for (int j = 0; j < depth()-i+n; j++) {
            (*outs) << "  ";
          }
          (*outs) << "</" << names[names.size()-1] << ">"
                  << std::endl;
          names.pop_back();
        }
      }
      return true;
    }
    
  };
  
  /** \brief A pugixml walker which outputs the full contents of the 
      node (no attributes yet) to a vector<string> object
   */
  class vec_string_walker : public walker_base {
    
  public:

    vec_string_walker() {
      indent=true;
    }
    
    /** \brief The traversal output
     */
    std::vector<std::string> output;

    bool indent;

    /** \brief Before traversing
     */
    virtual bool begin(pugi::xml_node &node) {
      output.clear();
      walker_base::begin(node);
      return true;
    }

    /** \brief Store output for each node
     */
    virtual bool for_each(pugi::xml_node &node) {

      std::string stmp;
      
      if (verbose>0) {
        std::cout << " d: "
                  << depth() << " l: " << last_depth << std::endl;
      }
      
      if (depth()<last_depth) {
        int n=last_depth-depth();
        for(int i=0;i<n;i++) {
          if (indent) {
            for (int j = 0; j < depth()-i+n-1; j++) {
              stmp+=((std::string)"  ");
            }
          }
          stmp+=((std::string)"</")+names[names.size()-1]+">";
          output.push_back(stmp);
          stmp.clear();
          names.pop_back();
        }
      }
      
      if (((std::string)node.name()).length()>0) {
        names.push_back(node.name());
      }

      if (indent) {
        for (int i = 0; i < depth(); i++) {
          stmp+=((std::string)"  ");
        }
      }
      
      if (((std::string)node.name()).length()>0) {
        stmp+=((std::string)"<")+node.name()+">"+node.value();
      } else {
        stmp+=node.value();
      }
      if (verbose>0) {
        for(size_t k=0;k<names.size();k++) {
          std::cout << "." << names[k] << ". ";
        }
      }
      output.push_back(stmp);
      stmp.clear();
      
      last_depth=depth();
      
      //names=node.name();
      return true;
    }

    /** \brief Finish output by closing all tags
     */
    virtual bool end(pugi::xml_node &node) {
      int n=last_depth;
      for(int i=0;i<n;i++) {
        std::string stmp;
        if (names.size()>0) {
          if (indent) {
            for (int j = 0; j < depth()-i+n; j++) {
              stmp+=((std::string)"  ");
            }
          }
          stmp+=((std::string)"</")+names[names.size()-1]+">";
          output.push_back(stmp);
          stmp.clear();
          names.pop_back();
        }
      }
      return true;
    }
    
  };
  
  /** \brief Extract XML node named \c node_name in the doxygen
      documentation for a global function named \c func_name from a
      file named \c fname
  */
  pugi::xml_node doxygen_xml_get
  (std::string fname, std::string func_name,
   std::string node_name, pugi::xml_document &doc,
   int verbose=0);
  
  /** \brief Extract XML node named \c node_name in the doxygen
      documentation for a member function named \c func_name from a
      class named \c class_name from a file named \c fname
  */
  pugi::xml_node doxygen_xml_member_get
  (std::string fname, std::string class_name, std::string func_name, 
   std::string node_name, pugi::xml_document &doc, int verbose=0);
   
#endif
  
}

#endif

