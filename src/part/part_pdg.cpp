/*
  ───────────────────────────────────────────────────────────────────
  
  Copyright (C) 2019-2023, Andrew W. Steiner
  
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
#include <o2scl/part_pdg.h>

using namespace std;
using namespace o2scl;

part_pdg_db::part_pdg_db() {
  /*
  db={
    {21,0,0,-0,
     0,0,-0,"g",0},
    {22,0,0,-0,
     0,0,-0,"gamma",0},
    {24,80.379,0.012,-0.012,
     2.085,0.042,-0.042,"W",3},
    {23,91.1876,0.0021,-0.0021,
     2.4952,0.0023,-0.0023,"Z",0},
    {25,125.1,0.14,-0.14,
     -1,-1,1,"H",0},
    {11,0.0005109989461,3.1e-12,-3.1e-12,
     0,0,-0,"e",-3},
    {12,-1,-1,1,
     -1,-1,1,"nu(e)",0},
    {13,0.1056583745,2.4e-09,-2.4e-09,
     2.9959847e-19,3e-25,-3e-25,"mu",-3},
    {14,-1,-1,1,
     -1,-1,1,"nu(mu)",0},
    {15,1.77686,0.00012,-0.00012,
     2.267e-12,4e-15,-4e-15,"tau",-3},
    {16,-1,-1,1,
     -1,-1,1,"nu(tau)",0},
    {1,0.00467,0.0005,-0.0002,
     -1,-1,1,"d",-1},
    {2,0.00216,0.0005,-0.0003,
     -1,-1,1,"u",2},
    {3,0.093,0.011,-0.005,
     -1,-1,1,"s",-1},
    {4,1.27,0.02,-0.02,
     -1,-1,1,"c",2},
    {5,4.18,0.03,-0.02,
     -1,-1,1,"b",-1},
    {6,173.1,0.9,-0.9,
     1.42,0.19,-0.15,"t",2},
    {211,0.13957061,2.4e-07,-2.4e-07,
     2.5284e-17,5e-21,-5e-21,"pi",3},
    {111,0.134977,5e-07,-5e-07,
     7.73e-09,1.7e-10,-1.7e-10,"pi",0},
    {221,0.547862,1.7e-05,-1.7e-05,
     1.31e-06,5e-08,-5e-08,"eta",0},
    {9000221,0.475,0.075,-0.075,
     0.55,0.15,-0.15,"f(0)(500)",0},
    {113,0.77526,0.00025,-0.00025,
     0.1491,0.0008,-0.0008,"rho(770)",0},
    {213,0.77526,0.00025,-0.00025,
     0.1491,0.0008,-0.0008,"rho(770)",3},
    {223,0.78265,0.00012,-0.00012,
     0.00849,8e-05,-8e-05,"omega(782)",0},
    {331,0.95778,6e-05,-6e-05,
     0.000196,9e-06,-9e-06,"eta'(958)",0},
    {9010221,0.99,0.02,-0.02,
     0.06,0.05,-0.05,"f(0)(980)",0},
    {9000111,0.98,0.02,-0.02,
     0.075,0.025,-0.025,"a(0)(980)",0},
    {9000211,0.98,0.02,-0.02,
     0.075,0.025,-0.025,"a(0)(980)",3},
    {333,1.019461,1.6e-05,-1.6e-05,
     0.004249,1.3e-05,-1.3e-05,"phi(1020)",0},
    {10223,1.17,0.02,-0.02,
     0.36,0.04,-0.04,"h(1)(1170)",0},
    {10113,1.2295,0.0032,-0.0032,
     0.142,0.009,-0.009,"b(1)(1235)",0},
    {10213,1.2295,0.0032,-0.0032,
     0.142,0.009,-0.009,"b(1)(1235)",3},
    {20113,1.23,0.04,-0.04,
     0.42,0.18,-0.18,"a(1)(1260)",0},
    {20213,1.23,0.04,-0.04,
     0.42,0.18,-0.18,"a(1)(1260)",3},
    {225,1.2755,0.0008,-0.0008,
     0.1867,0.0022,-0.0025,"f(2)(1270)",0},
    {20223,1.2819,0.0005,-0.0005,
     0.0227,0.0011,-0.0011,"f(1)(1285)",0},
    {100221,1.294,0.004,-0.004,
     0.055,0.005,-0.005,"eta(1295)",0},
    {100111,1.3,0.1,-0.1,
     0.4,0.2,-0.2,"pi(1300)",0},
    {100211,1.3,0.1,-0.1,
     0.4,0.2,-0.2,"pi(1300)",3},
    {115,1.3169,0.0009,-0.0009,
     0.107,0.005,-0.005,"a(2)(1320)",0},
    {215,1.3169,0.0009,-0.0009,
     0.107,0.005,-0.005,"a(2)(1320)",3},
    {10221,1.35,0.15,-0.15,
     0.35,0.15,-0.15,"f(0)(1370)",0},
    {9000113,1.354,0.025,-0.025,
     0.33,0.035,-0.035,"pi(1)(1400)",0},
    {9000213,1.354,0.025,-0.025,
     0.33,0.035,-0.035,"pi(1)(1400)",3},
    {9020221,1.4088,0.002,-0.002,
     0.0501,0.0026,-0.0026,"eta(1405)",0},
    {10333,1.416,0.008,-0.008,
     0.09,0.015,-0.015,"h(1)(1415)",0},
    {20333,1.4264,0.0009,-0.0009,
     0.0549,0.0026,-0.0026,"f(1)(1420)",0},
    {1000223,1.425,0.025,-0.025,
     0.215,0.035,-0.035,"omega(1420)",0},
    {10111,1.467,0.014,-0.014,
     0.271,0.011,-0.011,"a(0)(1450)",0},
    {10211,1.467,0.014,-0.014,
     0.271,0.011,-0.011,"a(0)(1450)",3},
    {100113,1.465,0.025,-0.025,
     0.4,0.06,-0.06,"rho(1450)",0},
    {100213,1.465,0.025,-0.025,
     0.4,0.06,-0.06,"rho(1450)",3},
    {100331,1.475,0.004,-0.004,
     0.09,0.009,-0.009,"eta(1475)",0},
    {9030221,1.506,0.006,-0.006,
     0.112,0.009,-0.009,"f(0)(1500)",0},
    {335,1.525,0.005,-0.005,
     0.073,0.006,-0.005,"f(2)'(1525)",0},
    {9010113,1.66,0.015,-0.011,
     0.26,0.06,-0.06,"pi(1)(1600)",0},
    {9010213,1.66,0.015,-0.011,
     0.26,0.06,-0.06,"pi(1)(1600)",3},
    {9020113,1.655,0.016,-0.016,
     0.25,0.04,-0.04,"a(1)(1640)",0},
    {9020213,1.655,0.016,-0.016,
     0.25,0.04,-0.04,"a(1)(1640)",3},
    {10225,1.617,0.005,-0.005,
     0.181,0.011,-0.011,"eta(2)(1645)",0},
    {30223,1.67,0.03,-0.03,
     0.315,0.035,-0.035,"omega(1650)",0},
    {227,1.667,0.004,-0.004,
     0.168,0.01,-0.01,"omega(3)(1670)",0},
    {10115,1.6706,0.0029,-0.0012,
     0.258,0.008,-0.009,"pi(2)(1670)",0},
    {10215,1.6706,0.0029,-0.0012,
     0.258,0.008,-0.009,"pi(2)(1670)",3},
    {100333,1.68,0.02,-0.02,
     0.15,0.05,-0.05,"phi(1680)",0},
    {117,1.6888,0.0021,-0.0021,
     0.161,0.01,-0.01,"rho(3)(1690)",0},
    {217,1.6888,0.0021,-0.0021,
     0.161,0.01,-0.01,"rho(3)(1690)",3},
    {30113,1.72,0.02,-0.02,
     0.25,0.1,-0.1,"rho(1700)",0},
    {30213,1.72,0.02,-0.02,
     0.25,0.1,-0.1,"rho(1700)",3},
    {9000115,1.7,0.04,-0.04,
     0.26,0.04,-0.04,"a(2)(1700)",0},
    {9000215,1.7,0.04,-0.04,
     0.26,0.04,-0.04,"a(2)(1700)",3},
    {10331,1.704,0.012,-0.012,
     0.123,0.018,-0.018,"f(0)(1710)",0},
    {9010111,1.81,0.009,-0.011,
     0.215,0.007,-0.008,"pi(1800)",0},
    {9010211,1.81,0.009,-0.011,
     0.215,0.007,-0.008,"pi(1800)",3},
    {337,1.854,0.007,-0.007,
     0.087,0.028,-0.023,"phi(3)(1850)",0},
    {9050225,1.936,0.012,-0.012,
     0.464,0.024,-0.024,"f(2)(1950)",0},
    {119,1.967,0.016,-0.016,
     0.324,0.015,-0.018,"a(4)(1970)",0},
    {219,1.967,0.016,-0.016,
     0.324,0.015,-0.018,"a(4)(1970)",3},
    {9060225,2.01,0.06,-0.08,
     0.2,0.06,-0.06,"f(2)(2010)",0},
    {229,2.018,0.011,-0.011,
     0.237,0.018,-0.018,"f(4)(2050)",0},
    {9080225,2.297,0.028,-0.028,
     0.15,0.04,-0.04,"f(2)(2300)",0},
    {9090225,2.35,0.05,-0.04,
     0.32,0.07,-0.06,"f(2)(2340)",0},
    {321,0.493677,1.6e-05,-1.6e-05,
     5.317e-17,9e-20,-9e-20,"K",3},
    {311,0.497611,1.3e-05,-1.3e-05,
     -1,-1,1,"K",0},
    {310,0.497611,1.3e-05,-1.3e-05,
     7.3508e-15,2.9e-18,-2.9e-18,"K(S)",0},
    {130,0.497611,1.3e-05,-1.3e-05,
     1.287e-17,5e-20,-5e-20,"K(L)",0},
    {9000311,0.824,0.03,-0.03,
     0.48,0.05,-0.05,"K(0)*(700)",0},
    {9000321,0.824,0.03,-0.03,
     0.48,0.05,-0.05,"K(0)*(700)",3},
    {313,0.89555,0.0002,-0.0002,
     0.0473,0.0005,-0.0005,"K*(892)",0},
    {323,0.89166,0.00026,-0.00026,
     0.0503,0.0008,-0.0008,"K*(892)",3},
    {10313,1.272,0.007,-0.007,
     0.09,0.02,-0.02,"K(1)(1270)",0},
    {10323,1.272,0.007,-0.007,
     0.09,0.02,-0.02,"K(1)(1270)",3},
    {20313,1.403,0.007,-0.007,
     0.174,0.013,-0.013,"K(1)(1400)",0},
    {20323,1.403,0.007,-0.007,
     0.174,0.013,-0.013,"K(1)(1400)",3},
    {100313,1.421,0.009,-0.009,
     0.236,0.018,-0.018,"K*(1410)",0},
    {100323,1.421,0.009,-0.009,
     0.236,0.018,-0.018,"K*(1410)",3},
    {10311,1.43,0.05,-0.05,
     0.27,0.08,-0.08,"K(0)*(1430)",0},
    {10321,1.43,0.05,-0.05,
     0.27,0.08,-0.08,"K(0)*(1430)",3},
    {315,1.4324,0.0013,-0.0013,
     0.109,0.005,-0.005,"K(2)*(1430)",0},
    {325,1.4256,0.0015,-0.0015,
     0.0985,0.0027,-0.0027,"K(2)*(1430)",3},
    {30313,1.718,0.018,-0.018,
     0.32,0.11,-0.11,"K*(1680)",0},
    {30323,1.718,0.018,-0.018,
     0.32,0.11,-0.11,"K*(1680)",3},
    {10315,1.773,0.008,-0.008,
     0.186,0.014,-0.014,"K(2)(1770)",0},
    {10325,1.773,0.008,-0.008,
     0.186,0.014,-0.014,"K(2)(1770)",3},
    {317,1.776,0.007,-0.007,
     0.159,0.021,-0.021,"K(3)*(1780)",0},
    {327,1.776,0.007,-0.007,
     0.159,0.021,-0.021,"K(3)*(1780)",3},
    {20315,1.819,0.012,-0.012,
     0.264,0.034,-0.034,"K(2)(1820)",0},
    {20325,1.819,0.012,-0.012,
     0.264,0.034,-0.034,"K(2)(1820)",3},
    {319,2.045,0.009,-0.009,
     0.198,0.03,-0.03,"K(4)*(2045)",0},
    {329,2.045,0.009,-0.009,
     0.198,0.03,-0.03,"K(4)*(2045)",3},
    {411,1.86965,5e-05,-5e-05,
     6.33e-13,4e-15,-4e-15,"D",3},
    {421,1.86483,5e-05,-5e-05,
     1.605e-12,6e-15,-6e-15,"D",0},
    {423,2.00685,5e-05,-5e-05,
     -1,-1,1,"D*(2007)",0},
    {413,2.01026,5e-05,-5e-05,
     8.34e-05,1.8e-06,-1.8e-06,"D*(2010)",3},
    {10421,2.3,0.019,-0.019,
     0.27,0.04,-0.04,"D(0)*(2300)",0},
    {10411,2.3,0.019,-0.019,
     0.27,0.04,-0.04,"D(0)*(2300)",3},
    {10423,2.4208,0.0005,-0.0005,
     0.0317,0.0025,-0.0025,"D(1)(2420)",0},
    {425,2.4607,0.0004,-0.0004,
     0.0475,0.0011,-0.0011,"D(2)*(2460)",0},
    {415,2.4654,0.0013,-0.0013,
     0.0467,0.0012,-0.0012,"D(2)*(2460)",3},
    {431,1.96834,7e-05,-7e-05,
     1.305e-12,1e-14,-1e-14,"D(s)",3},
    {433,2.1122,0.0004,-0.0004,
     -1,-1,1,"D(s)*",3},
    {10431,2.3178,0.0005,-0.0005,
     -1,-1,1,"D(s0)*(2317)",3},
    {20433,2.4595,0.0006,-0.0006,
     -1,-1,1,"D(s1)(2460)",3},
    {10433,2.53511,6e-05,-6e-05,
     0.00092,5e-05,-5e-05,"D(s1)(2536)",3},
    {435,2.5691,0.0008,-0.0008,
     0.0169,0.0007,-0.0007,"D(s2)*(2573)",3},
    {521,5.27933,0.00013,-0.00013,
     4.018e-13,1e-15,-1e-15,"B",3},
    {511,5.27964,0.00013,-0.00013,
     4.333e-13,1.1e-15,-1.1e-15,"B",0},
    {513,5.3247,0.00022,-0.00022,
     -1,-1,1,"B*",0},
    {523,5.3247,0.00022,-0.00022,
     -1,-1,1,"B*",3},
    {515,5.7395,0.0007,-0.0007,
     0.0242,0.0017,-0.0017,"B(2)*(5747)",0},
    {525,5.7395,0.0007,-0.0007,
     0.0242,0.0017,-0.0017,"B(2)*(5747)",3},
    {531,5.36688,0.00017,-0.00017,
     4.359e-13,1.2e-15,-1.2e-15,"B(s)",0},
    {533,5.4154,0.0018,-0.0015,
     -1,-1,1,"B(s)*",0},
    {535,5.83985,0.00012,-0.00012,
     0.00149,0.00027,-0.00027,"B(s2)*(5840)",0},
    {541,6.2749,0.0008,-0.0008,
     1.291e-12,2.3e-14,-2.3e-14,"B(c)",3},
    {441,2.9839,0.0005,-0.0005,
     0.0319,0.0007,-0.0007,"eta(c)(1S)",0},
    {443,3.0969,6e-06,-6e-06,
     9.29e-05,2.8e-06,-2.8e-06,"J/psi(1S)",0},
    {10441,3.41471,0.0003,-0.0003,
     0.0108,0.0006,-0.0006,"chi(c0)(1P)",0},
    {20443,3.51067,5e-05,-5e-05,
     0.00084,4e-05,-4e-05,"chi(c1)(1P)",0},
    {10443,3.52538,0.00011,-0.00011,
     0.0007,0.0004,-0.0004,"h(c)(1P)",0},
    {445,3.55617,7e-05,-7e-05,
     0.00197,9e-05,-9e-05,"chi(c2)(1P)",0},
    {100441,3.6375,0.0011,-0.0011,
     0.0113,0.0032,-0.0029,"eta(c)(2S)",0},
    {100443,3.686097,2.5e-05,-2.5e-05,
     0.000294,8e-06,-8e-06,"psi(2S)",0},
    {30443,3.77313,0.00035,-0.00035,
     0.0272,0.001,-0.001,"psi(3770)",0},
    {100445,3.9272,0.0026,-0.0026,
     0.024,0.006,-0.006,"chi(c2)(3930)",0},
    {9000443,4.039,0.001,-0.001,
     0.08,0.01,-0.01,"psi(4040)",0},
    {9010443,4.191,0.005,-0.005,
     0.07,0.01,-0.01,"psi(4160)",0},
    {9020443,4.421,0.004,-0.004,
     0.062,0.02,-0.02,"psi(4415)",0},
    {553,9.4603,0.00026,-0.00026,
     5.402e-05,1.3e-06,-1.3e-06,"Upsilon(1S)",0},
    {10551,9.8594,0.0005,-0.0005,
     -1,-1,1,"chi(b0)(1P)",0},
    {20553,9.892878,0.0003,-0.0003,
     -1,-1,1,"chi(b1)(1P)",0},
    {10553,9.8993,0.0008,-0.0008,
     -1,-1,1,"h(b)(1P)",0},
    {555,9.91221,0.0003,-0.0003,
     -1,-1,1,"chi(b2)(1P)",0},
    {100553,10.02326,0.00031,-0.00031,
     3.198e-05,2.6e-06,-2.6e-06,"Upsilon(2S)",0},
    {30553,10.1637,0.0014,-0.0014,
     -1,-1,1,"Upsilon(2)(1D)",0},
    {110551,10.2325,0.0004,-0.0005,
     -1,-1,1,"chi(b0)(2P)",0},
    {120553,10.25546,0.0002,-0.0005,
     -1,-1,1,"chi(b1)(2P)",0},
    {100555,10.26865,0.0002,-0.0005,
     -1,-1,1,"chi(b2)(2P)",0},
    {200553,10.3552,0.0005,-0.0005,
     2.032e-05,1.9e-06,-1.9e-06,"Upsilon(3S)",0},
    {300553,10.5794,0.0012,-0.0012,
     0.0205,0.0025,-0.0025,"Upsilon(4S)",0},
    {9000553,10.8899,0.0032,-0.0026,
     0.051,0.006,-0.007,"Upsilon(10860)",0},
    {9010553,10.9929,0.01,-0.0031,
     0.049,0.009,-0.015,"Upsilon(11020)",0},
    {2212,0.938272081,6e-09,-6e-09,
     0,0,-0,"p",3},
    {2112,0.939565413,6e-09,-6e-09,
     7.485e-28,5e-31,-5e-31,"n",0},
    {12112,1.44,0.03,-0.03,
     0.35,0.1,-0.1,"N(1440)",0},
    {12212,1.44,0.03,-0.03,
     0.35,0.1,-0.1,"N(1440)",3},
    {1214,1.515,0.005,-0.005,
     0.11,0.01,-0.01,"N(1520)",0},
    {2124,1.515,0.005,-0.005,
     0.11,0.01,-0.01,"N(1520)",3},
    {22112,1.53,0.015,-0.015,
     0.15,0.025,-0.025,"N(1535)",0},
    {22212,1.53,0.015,-0.015,
     0.15,0.025,-0.025,"N(1535)",3},
    {32112,1.65,0.015,-0.015,
     0.125,0.025,-0.025,"N(1650)",0},
    {32212,1.65,0.015,-0.015,
     0.125,0.025,-0.025,"N(1650)",3},
    {2116,1.675,0.005,-0.01,
     0.145,0.015,-0.015,"N(1675)",0},
    {2216,1.675,0.005,-0.01,
     0.145,0.015,-0.015,"N(1675)",3},
    {12116,1.685,0.005,-0.005,
     0.12,0.01,-0.005,"N(1680)",0},
    {12216,1.685,0.005,-0.005,
     0.12,0.01,-0.005,"N(1680)",3},
    {21214,1.72,0.08,-0.07,
     0.2,0.1,-0.1,"N(1700)",0},
    {22124,1.72,0.08,-0.07,
     0.2,0.1,-0.1,"N(1700)",3},
    {42112,1.71,0.03,-0.03,
     0.14,0.06,-0.06,"N(1710)",0},
    {42212,1.71,0.03,-0.03,
     0.14,0.06,-0.06,"N(1710)",3},
    {31214,1.72,0.03,-0.04,
     0.25,0.15,-0.1,"N(1720)",0},
    {32124,1.72,0.03,-0.04,
     0.25,0.15,-0.1,"N(1720)",3},
    {1218,2.18,0.04,-0.04,
     0.4,0.1,-0.1,"N(2190)",0},
    {2128,2.18,0.04,-0.04,
     0.4,0.1,-0.1,"N(2190)",3},
    {1114,1.232,0.002,-0.002,
     0.117,0.003,-0.003,"Delta(1232)",-3},
    {2114,1.232,0.002,-0.002,
     0.117,0.003,-0.003,"Delta(1232)",0},
    {2214,1.232,0.002,-0.002,
     0.117,0.003,-0.003,"Delta(1232)",3},
    {2224,1.232,0.002,-0.002,
     0.117,0.003,-0.003,"Delta(1232)",6},
    {31114,1.57,0.07,-0.07,
     0.25,0.05,-0.05,"Delta(1600)",-3},
    {32114,1.57,0.07,-0.07,
     0.25,0.05,-0.05,"Delta(1600)",0},
    {32214,1.57,0.07,-0.07,
     0.25,0.05,-0.05,"Delta(1600)",3},
    {32224,1.57,0.07,-0.07,
     0.25,0.05,-0.05,"Delta(1600)",6},
    {1112,1.61,0.02,-0.02,
     0.13,0.02,-0.02,"Delta(1620)",-3},
    {1212,1.61,0.02,-0.02,
     0.13,0.02,-0.02,"Delta(1620)",0},
    {2122,1.61,0.02,-0.02,
     0.13,0.02,-0.02,"Delta(1620)",3},
    {2222,1.61,0.02,-0.02,
     0.13,0.02,-0.02,"Delta(1620)",6},
    {11114,1.71,0.02,-0.02,
     0.3,0.08,-0.08,"Delta(1700)",-3},
    {12114,1.71,0.02,-0.02,
     0.3,0.08,-0.08,"Delta(1700)",0},
    {12214,1.71,0.02,-0.02,
     0.3,0.08,-0.08,"Delta(1700)",3},
    {12224,1.71,0.02,-0.02,
     0.3,0.08,-0.08,"Delta(1700)",6},
    {11112,1.86,0.06,-0.02,
     0.25,0.07,-0.07,"Delta(1900)",-3},
    {11212,1.86,0.06,-0.02,
     0.25,0.07,-0.07,"Delta(1900)",0},
    {12122,1.86,0.06,-0.02,
     0.25,0.07,-0.07,"Delta(1900)",3},
    {12222,1.86,0.06,-0.02,
     0.25,0.07,-0.07,"Delta(1900)",6},
    {1116,1.88,0.03,-0.025,
     0.33,0.07,-0.06,"Delta(1905)",-3},
    {1216,1.88,0.03,-0.025,
     0.33,0.07,-0.06,"Delta(1905)",0},
    {2126,1.88,0.03,-0.025,
     0.33,0.07,-0.06,"Delta(1905)",3},
    {2226,1.88,0.03,-0.025,
     0.33,0.07,-0.06,"Delta(1905)",6},
    {21112,1.9,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1910)",-3},
    {21212,1.9,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1910)",0},
    {22122,1.9,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1910)",3},
    {22222,1.9,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1910)",6},
    {21114,1.92,0.05,-0.05,
     0.3,0.06,-0.06,"Delta(1920)",-3},
    {22114,1.92,0.05,-0.05,
     0.3,0.06,-0.06,"Delta(1920)",0},
    {22214,1.92,0.05,-0.05,
     0.3,0.06,-0.06,"Delta(1920)",3},
    {22224,1.92,0.05,-0.05,
     0.3,0.06,-0.06,"Delta(1920)",6},
    {11116,1.95,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1930)",-3},
    {11216,1.95,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1930)",0},
    {12126,1.95,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1930)",3},
    {12226,1.95,0.05,-0.05,
     0.3,0.1,-0.1,"Delta(1930)",6},
    {1118,1.93,0.02,-0.015,
     0.28,0.05,-0.05,"Delta(1950)",-3},
    {2118,1.93,0.02,-0.015,
     0.28,0.05,-0.05,"Delta(1950)",0},
    {2218,1.93,0.02,-0.015,
     0.28,0.05,-0.05,"Delta(1950)",3},
    {2228,1.93,0.02,-0.015,
     0.28,0.05,-0.05,"Delta(1950)",6},
    {3122,1.115683,6e-06,-6e-06,
     2.501e-15,1.9e-17,-1.9e-17,"Lambda",0},
    {13122,1.4051,0.0013,-0.001,
     0.0505,0.002,-0.002,"Lambda(1405)",0},
    {3124,1.5195,0.001,-0.001,
     0.0156,0.001,-0.001,"Lambda(1520)",0},
    {23122,1.6,0.1,-0.04,
     0.15,0.1,-0.1,"Lambda(1600)",0},
    {33122,1.67,0.01,-0.01,
     0.035,0.015,-0.01,"Lambda(1670)",0},
    {13124,1.69,0.005,-0.005,
     0.06,0.01,-0.01,"Lambda(1690)",0},
    {43122,1.8,0.05,-0.08,
     0.3,0.1,-0.1,"Lambda(1800)",0},
    {53122,1.81,0.04,-0.06,
     0.15,0.1,-0.1,"Lambda(1810)",0},
    {3126,1.82,0.005,-0.005,
     0.08,0.01,-0.01,"Lambda(1820)",0},
    {13126,1.83,0,-0.02,
     0.095,0.015,-0.035,"Lambda(1830)",0},
    {23124,1.89,0.02,-0.04,
     0.1,0.1,-0.04,"Lambda(1890)",0},
    {3128,2.1,0.01,-0.01,
     0.2,0.05,-0.1,"Lambda(2100)",0},
    {23126,2.11,0.03,-0.02,
     0.2,0.05,-0.05,"Lambda(2110)",0},
    {3222,1.18937,7e-05,-7e-05,
     8.209e-15,2.7e-17,-2.7e-17,"Sigma",3},
    {3212,1.192642,2.4e-05,-2.4e-05,
     8.9e-06,9e-07,-8e-07,"Sigma",0},
    {3112,1.197449,3e-05,-3e-05,
     4.45e-15,3.2e-17,-3.2e-17,"Sigma",-3},
    {3114,1.3872,0.0005,-0.0005,
     0.0394,0.0021,-0.0021,"Sigma(1385)",-3},
    {3214,1.3837,0.001,-0.001,
     0.036,0.005,-0.005,"Sigma(1385)",0},
    {3224,1.3828,0.00035,-0.00035,
     0.036,0.0007,-0.0007,"Sigma(1385)",3},
    {13112,1.66,0.03,-0.03,
     0.1,0.1,-0.06,"Sigma(1660)",-3},
    {13212,1.66,0.03,-0.03,
     0.1,0.1,-0.06,"Sigma(1660)",0},
    {13222,1.66,0.03,-0.03,
     0.1,0.1,-0.06,"Sigma(1660)",3},
    {13114,1.67,0.015,-0.005,
     0.06,0.02,-0.02,"Sigma(1670)",-3},
    {13214,1.67,0.015,-0.005,
     0.06,0.02,-0.02,"Sigma(1670)",0},
    {13224,1.67,0.015,-0.005,
     0.06,0.02,-0.02,"Sigma(1670)",3},
    {23112,1.75,0.05,-0.02,
     0.09,0.07,-0.03,"Sigma(1750)",-3},
    {23212,1.75,0.05,-0.02,
     0.09,0.07,-0.03,"Sigma(1750)",0},
    {23222,1.75,0.05,-0.02,
     0.09,0.07,-0.03,"Sigma(1750)",3},
    {3116,1.775,0.005,-0.005,
     0.12,0.015,-0.015,"Sigma(1775)",-3},
    {3216,1.775,0.005,-0.005,
     0.12,0.015,-0.015,"Sigma(1775)",0},
    {3226,1.775,0.005,-0.005,
     0.12,0.015,-0.015,"Sigma(1775)",3},
    {13116,1.915,0.02,-0.015,
     0.12,0.04,-0.04,"Sigma(1915)",-3},
    {13216,1.915,0.02,-0.015,
     0.12,0.04,-0.04,"Sigma(1915)",0},
    {13226,1.915,0.02,-0.015,
     0.12,0.04,-0.04,"Sigma(1915)",3},
    {23114,1.94,0.01,-0.04,
     0.22,0.08,-0.07,"Sigma(1940)",-3},
    {23214,1.94,0.01,-0.04,
     0.22,0.08,-0.07,"Sigma(1940)",0},
    {23224,1.94,0.01,-0.04,
     0.22,0.08,-0.07,"Sigma(1940)",3},
    {3118,2.03,0.01,-0.005,
     0.18,0.02,-0.03,"Sigma(2030)",-3},
    {3218,2.03,0.01,-0.005,
     0.18,0.02,-0.03,"Sigma(2030)",0},
    {3228,2.03,0.01,-0.005,
     0.18,0.02,-0.03,"Sigma(2030)",3},
    {3322,1.31486,0.0002,-0.0002,
     2.27e-15,7e-17,-7e-17,"Xi",0},
    {3312,1.32171,7e-05,-7e-05,
     4.02e-15,4e-17,-4e-17,"Xi",-3},
    {3314,1.535,0.0006,-0.0006,
     0.0099,0.0017,-0.0019,"Xi(1530)",-3},
    {3324,1.5318,0.00032,-0.00032,
     0.0091,0.0005,-0.0005,"Xi(1530)",0},
    {203312,1.69,0.01,-0.01,
     -1,-1,1,"Xi(1690)",-3},
    {203322,1.69,0.01,-0.01,
     -1,-1,1,"Xi(1690)",0},
    {13314,1.823,0.005,-0.005,
     0.024,0.015,-0.01,"Xi(1820)",-3},
    {13324,1.823,0.005,-0.005,
     0.024,0.015,-0.01,"Xi(1820)",0},
    {103316,1.95,0.015,-0.015,
     0.06,0.02,-0.02,"Xi(1950)",-3},
    {103326,1.95,0.015,-0.015,
     0.06,0.02,-0.02,"Xi(1950)",0},
    {203316,2.025,0.005,-0.005,
     0.02,0.015,-0.005,"Xi(2030)",-3},
    {203326,2.025,0.005,-0.005,
     0.02,0.015,-0.005,"Xi(2030)",0},
    {3334,1.67245,0.00029,-0.00029,
     8.02e-15,1.1e-16,-1.1e-16,"Omega",-3},
    {203338,2.252,0.009,-0.009,
     0.055,0.018,-0.018,"Omega(2250)",-3},
    {4122,2.28646,0.00014,-0.00014,
     3.3e-12,9e-14,-9e-14,"Lambda(c)",3},
    {14122,2.59225,0.00028,-0.00028,
     0.0026,0.0006,-0.0006,"Lambda(c)(2595)",3},
    {104122,2.62811,0.00019,-0.00019,
     -1,-1,1,"Lambda(c)(2625)",3},
    {204126,2.88163,0.00024,-0.00024,
     0.0056,0.0008,-0.0006,"Lambda(c)(2880)",3},
    {4112,2.45375,0.00014,-0.00014,
     0.00183,0.00011,-0.00019,"Sigma(c)(2455)",0},
    {4212,2.4529,0.0004,-0.0004,
     -1,-1,1,"Sigma(c)(2455)",3},
    {4222,2.45397,0.00014,-0.00014,
     0.00189,9e-05,-0.00018,"Sigma(c)(2455)",6},
    {4114,2.51848,0.0002,-0.0002,
     0.0153,0.0004,-0.0005,"Sigma(c)(2520)",0},
    {4214,2.5175,0.0023,-0.0023,
     -1,-1,1,"Sigma(c)(2520)",3},
    {4224,2.51841,0.00021,-0.00019,
     0.01478,0.0003,-0.0004,"Sigma(c)(2520)",6},
    {4232,2.46793,0.00018,-0.00018,
     1.49e-12,9e-14,-9e-14,"Xi(c)",3},
    {4132,2.47091,0.00025,-0.00025,
     5.9e-12,6e-13,-6e-13,"Xi(c)",0},
    {4322,2.5784,0.0005,-0.0005,
     -1,-1,1,"Xi(c)'",3},
    {4312,2.5792,0.0005,-0.0005,
     -1,-1,1,"Xi(c)'",0},
    {4314,2.64638,0.00021,-0.00021,
     0.00235,0.00022,-0.00022,"Xi(c)(2645)",0},
    {4324,2.64557,0.00026,-0.00026,
     0.00214,0.00019,-0.00019,"Xi(c)(2645)",3},
    {104314,2.7941,0.0005,-0.0005,
     0.01,0.0011,-0.0011,"Xi(c)(2790)",0},
    {104324,2.7924,0.0005,-0.0005,
     0.0089,0.001,-0.001,"Xi(c)(2790)",3},
    {104312,2.82026,0.00027,-0.00027,
     0.00254,0.00025,-0.00025,"Xi(c)(2815)",0},
    {104322,2.81673,0.00021,-0.00021,
     0.00243,0.00026,-0.00026,"Xi(c)(2815)",3},
    {4332,2.6952,0.0017,-0.0017,
     2.46e-12,2.6e-13,-2.2e-13,"Omega(c)",0},
    {4334,2.7659,0.002,-0.002,
     -1,-1,1,"Omega(c)(2770)",0},
    {5122,5.6196,0.00017,-0.00017,
     4.475e-13,2.7e-15,-2.7e-15,"Lambda(b)",0},
    {5112,5.81564,0.00027,-0.00027,
     0.0053,0.0005,-0.0005,"Sigma(b)",-3},
    {5222,5.81056,0.00025,-0.00025,
     0.005,0.0005,-0.0005,"Sigma(b)",3},
    {5114,5.83474,0.0003,-0.0003,
     0.0104,0.0008,-0.0008,"Sigma(b)*",-3},
    {5224,5.83032,0.00027,-0.00027,
     0.0094,0.0005,-0.0005,"Sigma(b)*",3},
    {5132,5.797,0.0009,-0.0009,
     4.19e-13,1.1e-14,-1.1e-14,"Xi(b)",-3},
    {5232,5.7919,0.0005,-0.0005,
     4.45e-13,9e-15,-9e-15,"Xi(b)",0},
    {5332,6.0461,0.0017,-0.0017,
     4e-13,4e-14,-4e-14,"Omega(b)",-3}
  };
  */
}

void part_pdg_db::output_text() {

  for(size_t i=0;i<db.size();i++) {
    cout << db[i].id << " " << db[i].name << " " << db[i].charge << " "
	 << db[i].mass << " " << db[i].width << endl;
    if (db[i].id>=1000 && db[i].id<9999) {
      cout << "  diquark" << endl;
    } else if (db[i].id>=1 && db[i].id<=6) {
      cout << "  quark" << endl;
    } else if (db[i].id==7) {
      cout << "  b'" << endl;
    } else if (db[i].id==8) {
      cout << "  t'" << endl;
    } else if (db[i].id==17) {
      cout << "  tau'" << endl;
    } else if (db[i].id==18) {
      cout << "  nutau'" << endl;
    } else if (db[i].id>=11 && db[i].id<=16) {
      cout << "  lepton" << endl;
    } else if (db[i].id>=81 && db[i].id<=100) {
      cout << "  internal" << endl;
    } else if (db[i].id==21) {
      cout << "  gluon" << endl;
    } else if (db[i].id==22) {
      cout << "  photon" << endl;
    } else if (db[i].id==23) {
      cout << "  Z boson" << endl;
    } else if (db[i].id==24) {
      cout << "  W boson" << endl;
    } else if (db[i].id==25) {
      cout << "  Higgs" << endl;
    } else if (db[i].id==310) {
      cout << "  K0S" << endl;
    } else if (db[i].id==130) {
      cout << "  K0L" << endl;
    } else if (db[i].id==990) {
      cout << "  pomeron" << endl;
    } else if (db[i].id==9990) {
      cout << "  odderon" << endl;
    } else if (db[i].id==110) {
      cout << "  reggeon" << endl;
    } 
  }
  
  return;
}
