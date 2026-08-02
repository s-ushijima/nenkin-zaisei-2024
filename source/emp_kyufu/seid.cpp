#include "sepscommon.h"
#include "sepslib.h"
#include <vector>
using namespace std;
namespace sst = sepsstd;
namespace csv = csvio;

static void set_hsr(void);

void seps::seid(void) {



  int __tmp[] = {
    1000, 986,  972,  958,  944,  931,  917,  904,  891,  879,
    866,  854,  841,  829,  818,  806,  794,  783,  772,  761 
  };
  vector<int> tmp(__tmp, __tmp + 20);

  int __tmp2[] {
    7692, 7585, 7477, 7369, 7262, 7162, 7054, 6954, 6854, 6762,
    6662, 6569, 6469, 6377, 6292, 6200, 6108, 6023, 5938, 5854 
  };
  vector<int> tmp2(__tmp2, __tmp2 + 20);

  int __tmq[] {
    1875, 1817, 1761, 1707, 1654, 1603, 1553, 1505, 1458, 1413, 
    369,  1327, 1286, 1246, 1208, 1170, 1134, 1099, 1065, 1032
  };
  vector<int> tmq(__tmq, __tmq + 20);

  int __tmr[] {
    1000, 973,  947,  920,  893,  867,  840,  813,  787,  760,
    733,  707,  680,  653,  627,  600,  573,  547,  520,  493,
    467,  440,  413,  387,  360,  333,  307,  280,  253,  227,
    200,  173,  147,  120,   93,   67,   67,   67,   67,   67
  };
  vector<int> tmr(__tmr, __tmr + 40);

  v2_t iqp = VEC(double, 130, 2);
  string nensyu;
  double numer;
  int xs, xe;
  
  char buf[BUF_SIZE];
  vector<double> vals;

  v1_t dtem   = VEC(double, 2);
  v1_t shosik = VEC(double, 2);



  for(int kx = -74; kx <= -54; kx++) {
    if(kx <= -55)      pre.AT(C19(kx)) = (double)tmp.AT(kx + 74) * 1.0e-5;
    else if(kx == -54) pre.AT(C19(kx)) = 7.5e-3;
  }
  
  pra = pre.AT(C19(-74));
  prb = pre.AT(C19(-54));

  for(int kx = -74; kx <= -54; kx++) {
    if(kx <= -55)      pres.AT(C19(kx)) = tmp2.AT(kx + 74) * 1.0e-6;
    else if(kx == -54) pres.AT(C19(kx)) = 5.481e-3 / hikrate;
  }
  
  pras = pres.AT(C19(-74));
  prbs = pres.AT(C19(-54));


  for(int kx = -74; kx <= KE; kx++) {
    if(kx <= -55)      flt.AT(C19(kx)) = tmq.AT(kx + 74) * 1.0e-3;
    else if(-54 <= kx) flt.AT(C19(kx)) = 1.0;
  }


  fl1  = 8042.0e+2;
  minb = 6032.0e+2;

  fl1  = sst::roundn(fl1 * ad2.AT(KIJUN), -2);
  fl   = round(1676.0 * ad2.AT(KIJUN)) * 12.0;
  minb = sst::roundn(minb * ad2.AT(KIJUN), -2);


  adt.AT(1) = 2314.0e+2;
  adt.AT(2) = 2314.0e+2;
  adt.AT(3) =  771.0e+2;

  for(int ii = 1; ii <= 3; ii++) {
    adt.AT(ii) = sst::roundn(adt.AT(ii) * ad2.AT(KIJUN), -2);
  }

  for(int kx = -74; kx <= KE; kx++) {
    if (kx <= -67)              sadt.AT(C19(kx)) =    0.0e+0;
    if (-66 <= kx && kx <= -61) sadt.AT(C19(kx)) =  341.0e+2;
    if (kx == -60)              sadt.AT(C19(kx)) =  683.0e+2;
    if (kx == -59)              sadt.AT(C19(kx)) = 1025.0e+2;
    if (kx == -58)              sadt.AT(C19(kx)) = 1366.0e+2;
    if (-57 <= kx)              sadt.AT(C19(kx)) = 1707.0e+2;
  }


  for(int kx = -66; kx <= KE; kx++) {
    sadt.AT(C19(kx)) = sst::roundn(sadt.AT(C19(kx)) * ad2.AT(KIJUN), -2);
  }


  for(int kx = -100; kx <= KE; kx++) {
    if(kx <= -75)      cadt.AT(C19(kx)) = 0.0;
    else if(kx <= -35) cadt.AT(C19(kx)) = tmr.AT(kx + 74) * 1.0e-3 * adt.AT(1);
    else if(-34 <= kx) cadt.AT(C19(kx)) = 0.0;
  }


  wif = 6032.0e+2;
  wif = sst::roundn(wif * ad2.AT(KIJUN), -2);
  for(int kx = -100; kx <= KE; kx++) {
    if(kx <= -74)      wife.AT(C19(kx)) = wif;
    else if(kx <= -59) wife.AT(C19(kx)) = wif - fl1 * (kx - 1 + 75) / (kx + 24 + 75);
    else if(kx <= -45) wife.AT(C19(kx)) = wif - fl1 * (kx - 1 + 75) / 40.0;
    else if(-44 <= kx) wife.AT(C19(kx)) = 0.0;
  }


  for(int kx = -74; kx <= KE; kx++) {
    can.AT(C19(kx)) = min((double)kx + 75 + 24, 40.0);

    if(flg_sigo >= 1 && kx >= canyr - 60) {
         can.AT(C19(kx)) = kflcan.AT(KE, C19(kx));
    }
  }


  for(int kx = -74; kx <= KE; kx++) {
    if(kx <= -72)                   can2.AT(C19(kx)) = 35.0;
    else if(-71 <= kx && kx <= -67) can2.AT(C19(kx)) = 36.0;
    else if(-66 <= kx && kx <= -57) can2.AT(C19(kx)) = 37.0;
    else if(kx == -56)              can2.AT(C19(kx)) = 38.0;
    else if(kx == -55)              can2.AT(C19(kx)) = 39.0;
    else if(-54 <= kx)              can2.AT(C19(kx)) = 40.0;

   
    if(flg_sigo >= 1 && kx >= canyr - 60) {
         can2.AT(C19(kx)) = kflcan.AT(KE, C19(kx));
    }
  }


  senll = 44.0;


  ha.AT(1) = 1.25;
  ha.AT(2) = 1.00;
  ha.AT(3) = 1.00;
  hb.AT(1) = 1.25;
  hb.AT(2) = 1.00;
  hb.AT(3) = 0.75;


  ema.AT(1) = 1.284;
  ema.AT(2) = 1.031;
  ema.AT(3) = ema.AT(1);
  emb.AT(1) = 1.266;
  emb.AT(2) = 1.048;
  emb.AT(3) = emb.AT(1);
  
  if(flg_sigo == 2){
   	  emc.AT(1) = 1.165;
	  emc.AT(2) = 1.000;
	  emc.AT(3) = emc.AT(1);
  }


  srv = 0.75;


  ee.AT(2) = 0.25;
  if(pseid == 0) {
    ee.AT(1) = 0.20;
  } else if(pseid<=4) {
    ee.AT(1) = 0.1585;
  } else {
    ee.AT(1) = 0.1982;
  }

  for(s = 1; s <= 3; s++) { 
    for(int k = KS; k <= KE; k++) {
      for(int x = 15; x <= 115; x++) {
        for(int j = 1; j <= 4; j++) {
          rs.AT(s, k, x, j) = 0.0;
        }
      }
    }
  }

  FILE *fpy = fp_map["yuizor"];
  for(int s = 1; s <= 3; s++) {
    if(konen != 1 && s == 3) continue;
    fgets(buf, BUF_SIZE, fpy);
    nensyu = string(buf).substr(0, 2);
    assert(nensyu == "RS");

    for(int k = KS - 5; k <= 70; k++) {
      vals = csv::read(fpy);
      int kk = (int)vals.at(0);
      assert(k == kk);

      if(k >= KS) {
        for(int x = 15; x <= 115; x++) {
          rs.AT(s, k, x, 1) = vals.at(1 + (x - 15));
        }
      }
    }
    
    if(s != 2) {
      vals = csv::read(fpy);
      for(int x = 15; x <= 115; x++) rs.AT(s, KS, x, 2) = vals.at(1 + (x - 15));
    } else {
      vals = csv::read(fpy);
      for(int x = 15; x <= 115; x++) rs.AT(s, KS, x, 3) = vals.at(1 + (x - 15));
      vals = csv::read(fpy);
      for(int x = 15; x <= 115; x++) rs.AT(s, KS, x, 2) = vals.at(1 + (x - 15));
      vals = csv::read(fpy);
      for(int x = 15; x <= 115; x++) rs.AT(s, KS, x, 4) = vals.at(1 + (x - 15));
    }

    for(int x = 15; x <= 115; x++) {
      for(int k = KS + 1; k <= KE; k++) {
        if(k >= 71) {
          rs.AT(s, k, x, 1) = rs.AT(s, 70, x, 1);
        }
        rs.AT(s, k, x, 3) = rs.AT(s, KS, x, 3);
        rs.AT(s, k, x, 2) = rs.AT(s, KS, x, 2);
        rs.AT(s, k, x, 4) = rs.AT(s, KS, x, 4);
      }
    }
  }


  FILE *fps = fp_map["sikur"];
  csv::read(fps);
  for(int s = 1; s <= 2; s++) {
    for(int j = 1; j <= 2; j++) {
      csv::read(fps);
      vals = csv::read(fps);
      int kk = (int)vals.at(0);
      int ss = (int)vals.at(1);
      int jj = (int)vals.at(2);
      assert(kk == KS + 1);
      assert(ss == s);
      assert(jj == j);
      vals = csv::read(fps);
      for(int x = 0; x <= 115; x++) {
        vals = csv::read(fps);
        int xx = vals.at(0);
        assert(xx == x);  
        for(int i = 1; i <= 19; i++) {
          sik.AT(KS + 1, x, s, i, j) = vals.at(1 + (i - 1));
        }
      }
    }
  }

  for(int k = KS; k <= KE; k++) {
    for(int x = 60; x <= 69; x++) {
      for(int s = 1; s <= 2; s++) {
        for(int i = 1; i <= 17; i++) {
          for(int j = 1; j <= 2; j++) {
            if (k == KS) {
              sikr.AT(x, s, i, j) = 1.0;
            }
            nos.AT(k, x, s, i, j) = 1.0;
          }
        }
      }
    }
  }

  csv::read(fps);
  csv::read(fps);
  csv::read(fps);
  csv::read(fps);

  for(int x = 60; x <= 69; x++) {
    vals = csv::read(fps);
    int xx = (int)vals.at(0);
    assert(xx == x);
    sikr.AT(x, 1, 1, 1) = vals.at(1);
    sikr.AT(x, 1, 1, 2) = vals.at(2);
    sikr.AT(x, 1, 3, 1) = vals.at(3);
    sikr.AT(x, 1, 3, 2) = vals.at(4);
    sikr.AT(x, 1, 2, 1) = vals.at(5);
    sikr.AT(x, 1, 4, 1) = vals.at(6);
    sikr.AT(x, 2, 1, 1) = vals.at(7);
    sikr.AT(x, 2, 1, 2) = vals.at(8);
    sikr.AT(x, 2, 3, 1) = vals.at(9);
    sikr.AT(x, 2, 3, 2) = vals.at(10);
    sikr.AT(x, 2, 2, 1) = vals.at(11);
    sikr.AT(x, 2, 4, 1) = vals.at(12);
    for(int i = 2; i <= 4; i += 2) {
      for(int s = 1; s <= 2; s++) {
        sikr.AT(x, s, i, 2) = sikr.AT(x, s, i, 1);
      }
    }
  }
  

  if(pseid == 0){
	  csv::read(fps);
	  csv::read(fps);
	  csv::read(fps);
	  csv::read(fps);
	  
	  for(int j = 1; j <= 3; j++) {
          vals = csv::read(fps);
	      routsu.AT(1, 1, j) = vals.at(1);
	      routsu.AT(1, 2, j) = vals.at(2);
	      routsu.AT(1, 3, j) = vals.at(3);
	      routsu.AT(1, 4, j) = vals.at(4);
	      routsu.AT(2, 1, j) = vals.at(5);
	      routsu.AT(2, 2, j) = vals.at(6);
	      routsu.AT(2, 3, j) = vals.at(7);
	      routsu.AT(2, 4, j) = vals.at(8);
	 }
  }

  dtem.AT(1) = 0.995182;
  dtem.AT(2) = 1.006545;


  if(pseid == 0){
	  xs = 81;
	  xe = 96;
  }else{
	  xs = 80;
	  xe = 95;
  }

	
  for(int k = KS + 2; k <= KE; k++) {
    for(int x = 0; x <= 115; x++) {
      for(int s = 1; s <= 2; s++) {
        for(int i = 1; i <= 19; i++) {
          for(int j = 1; j <= 2; j++) {
            sik.AT(k, x, s, i, j) = sik.AT(KS + 1, x, s, i, j);
          }
        }
      }
    }


    for(int j = 1; j <= 2; j++) {
        for(int s = 1; s <= 2; s++) {
          if(pseid == 0 && s == 2){
            for(int x = 62; x <= 115; x++) {
              if(x - (k - (KS + 1)) < 62) {
                if(x < 65){
                	sik.AT(k, x, s, 9, j)  = sik.AT(k, 61, s, 9, j);
                	sik.AT(k, x, s, 16, j) = sik.AT(k, 61, s, 16, j);
                }
                if(x >= 65){
                	sik.AT(k, x, s, 9, j)  = 1.0;
                	sik.AT(k, x, s, 16, j) = 1.0;
                }
              }
            }
          }
          else {
            for(int x = 63; x <= 115; x++) {
              if(x - (k - (KS + 1)) < 63) {
                if(x < 65){
                	sik.AT(k, x, s, 9, j)  = sik.AT(k, 62, s, 9, j);
                	sik.AT(k, x, s, 16, j) = sik.AT(k, 62, s, 16, j);
                }
                if(x >= 65){
                	sik.AT(k, x, s, 9, j)  = 1.0;
                	sik.AT(k, x, s, 16, j) = 1.0;
                }
              }
            }
          }
        }
    }


    if(k >= KS + 2) {
      for(int ii = 1; ii <= 2; ii++) {
        int i;
        if(ii == 1) i = 11;
        if(ii == 2) i = 17;

        for(int x = 0; x <= 18; x++) {
          for(int s = 1; s <= 2; s++) {
            for(int j = 1; j <= 2; j++) {
              if(ii == 1){
	              numer = max(0.0, (double)x + 1 - (k - (KS + 1))) * sik.AT(KS + 1, x, s, i, j)
                          		 + min(x + 1, k - (KS + 1)) * 1.0;
              } else if (ii == 2) {
	              numer = max(0.0, (double)x + 1 - (k - (KS + 1))) * sik.AT(KS + 1, x, s, i, j)
                          		 + min(x + 1, k - (KS + 1)) * sik.AT(k, x, s, 19, j);
              }
              double denom = x + 1;
              sik.AT(k, x, s, i, j) = numer / denom;
            }
          }
        }
      }

      if(flg_okure == 0){
       	if(k <= KIJUN + 5){
	        for(int s = 1; s <= 2; s++) {
	        for(int i = 1; i <= 4; i++) {
	        for(int j = 1; j <= 2; j++) {
		      if(s == 1 || (pseid != 0 && s == 2)){
		      	   if(k == KIJUN + 2) {
		                nos.AT(k, 64, s, i, j) = 1.0 - (1.0 - sikr.AT(64, s, i, j)) * (3.0 - (k - KIJUN)) / 2.0;
		                sik.AT(k, 64, s, i, j) = sik.AT(KIJUN, 64, s, i, j) * nos.AT(k, 64, s, i, j);
		            }
		      }else {
		         if(k <= KIJUN + 3) {
		            for(int x = 62; x <= 62 + k - KIJUN - 1; x++) {
		              if(k == KIJUN + 3 && x == 62) {
		              }else{
			              nos.AT(k, x, s, i, j) = 1.0 - (1.0 - sikr.AT(x, s, i, j)) * (4.0 - (k - KIJUN)) / 3.0;
			              sik.AT(k, x, s, i, j) = sik.AT(KIJUN, x, s, i, j) * nos.AT(k, x, s, i, j);
			          }
		            }
		         }
		      }
		      
	          if(i == 2 || i == 4) {
	            if(k <= KIJUN + 2) {
	              if(s == 1 || (pseid != 0 && s == 2)) {
	                if(k == KIJUN + 1){
	                    assert(sikr.AT(64 - k + KIJUN, s, i, j) > 0.0);
	                    nos.AT(k, 64, s, i, j) = sikr.AT(64, s, i, j) / sikr.AT(64 - k + KIJUN, s, i, j);
	                    sik.AT(k, 64, s, i, j) = sik.AT(KIJUN, 64, s, i, j) * nos.AT(k, 64, s, i, j);
	                }
	              }else {
	                for(int x = 62 + k - KIJUN; x <= 64; x++) {
	                  assert(sikr.AT(x - k + KIJUN, s, i, j) > 0.0); 
	                  nos.AT(k, x, s, i, j) = sikr.AT(x, s, i, j) / sikr.AT(x - k + KIJUN, s, i, j);
	                  sik.AT(k, x, s, i, j) = sik.AT(KIJUN, x, s, i, j) * nos.AT(k, x, s, i, j);
	                }
	              }
	            }
				for(int x = 65; x <= 69; x++) {
	              nos.AT(k, x, s, i, j) = 1.0 - (1.0 - sikr.AT(x, s, i, j)) * (6.0 - (k - KIJUN)) / 5.0;
	              sik.AT(k, x, s, i, j) = sik.AT(KIJUN, x, s, i, j) * nos.AT(k, x, s, i, j);
	            }
	          }
	        }
	        }
	        }
	      }
       }
    }

    for(int i = 5; i <= 18; i++) {
    if(i >= 14 && i <= 17) continue;
    for(int x = 46; x <= 115; x++) {
      if((i >= 5  && i <= 8   && x >= 46) ||
         (i == 10 &&             x >= 66) ||
         (i >= 12 && i <= 13  && x >= 66) ||
         (i == 18 && x >= 66) ) {
        for(int j = 1; j <= 2; j++) {
        for(int s = 1; s <= 2; s++) {
          if(pseid == 0 && k == KS + 2) continue;
          sik.AT(k, x, s, i, j) = sik.AT(k - 1, x - 1, s, i, j);
        }
        }
      }
    }
    }

    for(int i = 9; i <= 16; i++) {
      if(i >= 11 && i <= 15) continue;
      for(int j = 1; j <= 2; j++) {
      for(int s = 1; s <= 2; s++) {
        if(pseid == 0 && s == 2) {
          if(k >= 24) sik.AT(k, 62, s, i, j) = sik.AT(k, 61, s, i, j);
          if(k >= 27) sik.AT(k, 63, s, i, j) = sik.AT(k, 61, s, i, j);
          if(k >= 30) sik.AT(k, 64, s, i, j) = sik.AT(k, 61, s, i, j);
        }else{
          if(k >= 22) sik.AT(k, 63, s, i, j) = sik.AT(k, 62, s, i, j);
          if(k >= 25) sik.AT(k, 64, s, i, j) = sik.AT(k, 62, s, i, j);
        } 
      }
      }
    }

    for(int i = 11; i <= 13; i++) {
      for(int j = 1; j <= 2; j++) {
        for(int s = 1; s <= 2; s++) {
          if(pseid == 0 && s == 1) {
            if(k >= 24) sik.AT(k, 62, s, i, j) = sik.AT(k, 61, s, i, j);
            if(k >= 27) sik.AT(k, 63, s, i, j) = sik.AT(k, 61, s, i, j);
            if(k >= 30) sik.AT(k, 64, s, i, j) = sik.AT(k, 61, s, i, j);
          }else{
            if(k >= 22) sik.AT(k, 63, s, i, j) = sik.AT(k, 62, s, i, j);
            if(k >= 25) sik.AT(k, 64, s, i, j) = sik.AT(k, 62, s, i, j);
          }
        }
      }
    }

    for(int i = 1; i <= 4; i++) {
      for(int j = 1; j <= 2; j++) {
        for(int s = 1; s <= 2; s++) {
          if(pseid == 0 && s == 2) {
            if(k >= 24) sik.AT(k, 62, s, i, j) = sik.AT(k, 61, s, i, j);
            if(k >= 27) sik.AT(k, 63, s, i, j) = sik.AT(k, 61, s, i, j);
            if(k >= 30) sik.AT(k, 64, s, i, j) = sik.AT(k, 61, s, i, j);
          }else{
            if(k >= 22) sik.AT(k, 63, s, i, j) = sik.AT(k, 62, s, i, j);
            if(k >= 25) sik.AT(k, 64, s, i, j) = sik.AT(k, 62, s, i, j);
          }
        }
      }
    }

    for(int x = xs; x <= 115; x++) {
      if(x <= 65 + k - 7) {
        for(int s = 1; s <= 2; s++) {
          if(x == xs) {
            sik.AT(k, x, s, 11, 1) = sik.AT(k, xs - 1, s, 11, 1) * 2.0 - sik.AT(k, xs - 2, s, 11, 1);
          } else if(x <= xe) {
            sik.AT(k, x, s, 11, 1) = sik.AT(KS + 1, min(x, xe), s, 11, 1)
                                     * (sik.AT(k, xs, s, 11, 1) / sik.AT(KS + 1, xs, s, 11, 1));
          } else{
          	sik.AT(k, x, s, 11, 1) = min(
          	                         max( sik.AT(k, x - 1, s, 11, 1) * 2.0 - sik.AT(k, x - 2, s, 11, 1), 
          	                              sik.AT(k, x - 1, s, 11, 1) ), 1.0);
          }
          for(int i = 1; i <= 4; i++) {
              sik.AT(k, x, s, i, 1) = sik.AT(k - 1, x - 1, s, i, 1);
              sik.AT(k, x, s, i, 2) = sik.AT(k - 1, x - 1, s, i, 2);
          }
        }
      } else if(x <= 95 + k - (KS + 1)) {
        for(int s = 1; s <= 2; s++) {
          sik.AT(k, x, s, 11, 1) = max(
            sik.AT(k - 1, x - 1, s, 11, 1) * dtem.AT(s),
            sik.AT(KS + 1, min(x, xe), s, 11, 1) * sik.AT(k, xs, s, 11, 1) / sik.AT(KS + 1, xs, s, 11, 1));
        }
      }
    }
  }



	if(flg_siktuika == 0){
	  for(int i = 3; i <= 4; i++) {
	  for(int k = KIJUN + 1; k <= KE; k++) {
	  for(int x = 0; x <= 115; x++) {
	    dtem.AT(1) = 1.0;
	    dtem.AT(2) = 1.0;
	    if(x - k >= 23 - KIJUN && x - k <= 59 - KIJUN) {
	      if(pseid == 0) {
	        dtem.AT(1) = 1.00;
	        dtem.AT(2) = (0.90 + (1.00 - 0.90) / 36.0 * (x - k + KIJUN - 23));
	      } 
	      sik.AT(k, x, 1, i, 2) = sik.AT(k, x, 1, i, 2) * dtem.AT(1);
	      sik.AT(k, x, 2, i, 2) = sik.AT(k, x, 2, i, 2) * dtem.AT(2);
	    } else if(x - k >= 60 - KIJUN && x - k <= 69 - KIJUN) {
	      if(x - k == 60 - KIJUN) {
	        if(pseid == 0) {
	           dtem.AT(1) = 1.00;
	           dtem.AT(2) = 1.00;
	        }
	      }
	       else {
	        if(pseid == 0) {
	          dtem.AT(1) = 0.80 + (0.70 - 0.80) / 8.0 * (x - k + KIJUN - 61);
	          dtem.AT(2) = 0.95 + (0.90 - 0.95) / 8.0 * (x - k + KIJUN - 61);
	        }
	      }
	      if(k <= KIJUN + 5) {
	        dtem.AT(1) = 1.00 - (1.00 - dtem.AT(1)) / 5.0 * (k - KIJUN);
	        dtem.AT(2) = 1.00 - (1.00 - dtem.AT(2)) / 5.0 * (k - KIJUN);
	      }
	      sik.AT(k, x, 1, i, 2) = sik.AT(k, x, 1, i, 2) * dtem.AT(1);
	      sik.AT(k, x, 2, i, 2) = sik.AT(k, x, 2, i, 2) * dtem.AT(2);
	    }
	  }
	  }
	  }
	}
	


  FILE *fpqx = fp_map["qx"];
  csv::read(fpqx);
  for(int ss = 1; ss <= 2; ss++) {
	if(seimei >= 4 && seimei <= 6){
	    for(int nensu = seiy - 55; nensu <= seiy; nensu++) {
	      vals = csv::read(fpqx);
	      
	      int kk = vals.at(0);
	      assert(kk == nensu);
	      for(int x = 0; x <= 114; x++) iqp.AT(x, ss) = vals.at(1 + (x - 0));
	      for(int x = 0; x <= 114; x++) qp.AT(nensu, x, ss) = iqp.AT(x, ss) / 1.0e+5;
	    }
	 }
  }

  set_hsr();

  if(key == 11 && nenbeex == 0) {
    FILE *fpso = fp_map["sikr_out"];
    fprintf(fpso, "%s\n", "支給率の出力");
    fprintf(fpso, "k,x,s,i,j,sik\n");
    if(pseid == 0 || pseid == 1 || pseid == 4 || pseid == 5) {
      for(int k = KIJUN; k <= KE; k++) {
        for(int x = 0; x <= 115; x++) {
          for(int s = 1; s <= 2; s++) {
            for(int i = 1; i <= 19; i++) {
              for(int j = 1; j <= 2; j++) {
                fprintf(fpso, "%d,%d,%d,%d,%d,%15.10lf\n", k, x, s, i, j, sik.AT(k, x, s, i, j));
              }
            }
          }
        }
      }
    }
    fprintf(fpso, "%s\n", "裁定遅れの処理に使用する率の出力");
    fprintf(fpso, "k,x,s,i,j,nos\n");
    if(pseid == 0 || pseid == 1 || pseid == 4 || pseid == 5) {
      for(int k = KIJUN+1; k <= KIJUN+10; k++) {
        for(int x = 60; x <= 69; x++) {
          for(int s = 1; s <= 2; s++) {
            for(int i = 1; i <= 4; i++) {
              for(int j = 1; j <= 2; j++) {
                fprintf(fpso, "%d,%d,%d,%d,%d,%15.10lf\n", k, x, s, i, j, nos.AT(k, x, s, i, j));
              }
            }
          }
        }
      }
    }
    
  }
}



static void set_hsr(void) {

  string nensyu;
  double tmp;
  double tml, tbn1, tbn2;
  double tmq, tmr;
  v2_t bnpti  = VEC(double, 84, 3);

  vector<double> vals;
  vector<string> items;


  FILE *fph = fp_map["hou"]; 

  items = csv::read_str(fph);
  nensyu = items.at(1).substr(0, 2);
  assert(nensyu == "BR");

  csv::read(fph);
  csv::read(fph);

  if(konen == 1) {
    for(int x = 15; x <= 84; x++) {
      vals = csv::read(fph);
      int xx = (int)vals.at(0);
      assert(xx == x);
      for(int s = 1; s <= 3; s++) br.AT(KS, x, s) = vals.at(1 + (s - 1));
    }
  } else {
    for(int x = 15; x <= 74; x++) {
      vals = csv::read(fph);
      int xx = (int)vals.at(0);
      assert(xx == x);
      for(int s = 1; s <= 2; s++) br.AT(KS, x, s) = vals.at(1 + (s - 1));
    }
  }

  items = csv::read_str(fph);
  nensyu = items.at(1).substr(0, 2);
  assert(nensyu == "BN");
  
  csv::read(fph);
  csv::read(fph);

  if(konen == 1) {
    for(int x = 15; x <= 84; x++) {
      vals = csv::read(fph);
      int xx = (int)vals.at(0);
      assert(xx == x);
      for(int s = 1; s <= 3; s++) bn.AT(KS, x, s) = vals.at(1 + (s - 1));
    }
  } else {
    for(int x = 15; x <= 74; x++) {
      vals = csv::read(fph);
      int xx = (int)vals.at(0);
      assert(xx == x);
      for(int s = 1; s <= 2; s++) bn.AT(KS, x, s) = vals.at(1 + (s - 1));
    }
  }

  if(pseid == 0) {
    items = csv::read_str(fph);
    nensyu = items.at(1).substr(0, 5);
    assert(nensyu == "BNPTI");

    csv::read(fph);
    csv::read(fph);

    for(int x = 15; x <= 84; x++) {
      vals = csv::read(fph);
      int xx = (int)vals.at(0);
      assert(xx == x);
      for(int s = 1; s <= 3; s++) bnpti.AT(x, s) = vals.at(1 + (s - 1));
    }
  } else {
    for(int s = 1; s <= 3; s++) {
      for(int x = 15; x <= 84; x++) {
        bnpti.AT(x, s) = 0.0;
      }
    }
  }

  FOR(s, 1, 3) {
    if(pseid != 0 && s == 3) continue;
    FOR(x, 15, 84) {
      br.AT(KS + 1, x, s) = br.AT(KS, x, s);
      bn.AT(KS + 1, x, s) = bn.AT(KS, x, s);
    }
  }

  if(pseid == 0) {
    FOR(x, 15, 84) FOR(k, KS + 2, KE) {
      if(k <= hsr_endy) {
        tbn1 = bn.AT(k - 1, x, 1);
        tbn2 = bn.AT(k - 1, x, 2);
        tml  = l.AT(k, 1, x) + l.AT(k, 2, x);
        if(tml > 0.0) {
          bn.AT(k, x, 1) = tbn1 - l.AT(k, 2, x) / tml * hsr_r * (tbn1 - tbn2);
          bn.AT(k, x, 2) = tbn2 + l.AT(k, 1, x) / tml * hsr_r * (tbn1 - tbn2);
        } else {
          bn.AT(k, x, 1) = tbn1 - hsr_r * (tbn1 - tbn2) / 2.0;
          bn.AT(k, x, 2) = tbn2 + hsr_r * (tbn1 - tbn2) / 2.0;
        }
      } else {
        bn.AT(k, x, 1) = bn.AT(k - 1, x, 1);
        bn.AT(k, x, 2) = bn.AT(k - 1, x, 2);
      }
      bn.AT(k, x, 3) = bn.AT(k - 1, x, 3);

      for(int s = 1; s <= 3; s++) {
        br.AT(k, x, s) = bn.AT(k, x, s) / bn.AT(KS + 1, 20, s);
      }
    }
  }  else {
    for(int s = 1; s <= 3; s++) {
      if(pseid != 0 && s == 3) break;
      for(int x = 15; x <= 84; x++) {
        for(int k = KS + 2; k <= KE; k++) {
          br.AT(k, x, s) = br.AT(KS + 1, x, s);
          bn.AT(k, x, s) = bn.AT(KS + 1, x, s);
        }
      }
    }
  }
   
  partbbn.AT(0, 0, 1, 1) = 16.9e4 * 12.0;
  partbbn.AT(0, 0, 2, 1) = 16.9e4 * 12.0;
  partbbn.AT(0, 0, 1, 2) = 15.1e4 * 12.0;
  partbbn.AT(0, 0, 2, 2) = 15.1e4 * 12.0;
  
  if(flg_part == 1){
	  partbbn.AT(1, 0, 1, 1) = 16.9e4 * 12.0;
	  partbbn.AT(1, 0, 2, 1) = 16.9e4 * 12.0;
	  partbbn.AT(1, 0, 1, 2) = 15.1e4 * 12.0;
	  partbbn.AT(1, 0, 2, 2) = 15.1e4 * 12.0;
  }
  

  else if(flg_part == 2){
	  partbbn.AT(1, 0, 1, 1) = 13.9e4 * 12.0;
	  partbbn.AT(1, 0, 2, 1) = 13.9e4 * 12.0;
	  partbbn.AT(1, 0, 1, 2) = 11.1e4 * 12.0;
	  partbbn.AT(1, 0, 2, 2) = 11.1e4 * 12.0;
  }
  
  else if(flg_part == 3){
	  partbbn.AT(1, 0, 1, 1) = 14.1e4 * 12.0;
	  partbbn.AT(1, 0, 2, 1) = 14.1e4 * 12.0;
	  partbbn.AT(1, 0, 1, 2) = 11.4e4 * 12.0;
	  partbbn.AT(1, 0, 2, 2) = 11.4e4 * 12.0;
  }
  else if(flg_part == 4){
	  partbbn.AT(1, 0, 1, 1) = 9.7e4 * 12.0;
	  partbbn.AT(1, 0, 2, 1) = 9.7e4 * 12.0;
	  partbbn.AT(1, 0, 1, 2) = 8.8e4 * 12.0;
	  partbbn.AT(1, 0, 2, 2) = 8.8e4 * 12.0;
  }
  else if(flg_part == 5){
	  partbbn.AT(1, 0, 1, 1) = 8.8e4 * 12.0;
	  partbbn.AT(1, 0, 2, 1) = 8.8e4 * 12.0;
	  partbbn.AT(1, 0, 1, 2) = 8.8e4 * 12.0;
	  partbbn.AT(1, 0, 2, 2) = 8.8e4 * 12.0;
  }
  
  
  if(pseid == 0) {
    for(int s = 1; s <= 2; s++) {
    for(int x = 15; x <= 84; x++) {
    for(int k = KS ; k <= KE; k++) {
      int x2;
      if(x <= 59) {
        x2 = 1;
      } else {
        x2 = 2;
      }

      bnpt.AT(k, x, s) = partbbn.AT(0, 0, x2, s) / ad.AT(22);
      
      if(flg_part >= 1){
	     if(k == partyr4){
      		if(lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x) > 1.0e-6){
	      		bnpt.AT(k, x, s) = (lpt2.AT(k, s, x) * bnpti.AT(x, s)
	      		                    + (lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) * partbbn.AT(1, 0, x2, s))
	      		                   / (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) / ad.AT(22);
      		}else{
      			bnpt.AT(k, x, s) = 0.0;
      		}
      	 }
      	 else if(k > partyr4){
      	 	if(lpt.AT(k, s, x) > 1.0e-6){
	      		bnpt.AT(k, x, s) = (lpt2.AT(k, s, x) * bnpti.AT(x, s)
	      		                    + (lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) * partbbn.AT(1, 0, x2, s)
	      		                    + (lpt.AT(k, s, x) - lpt2.AT(k, s, x) - lpt3.AT(k, s, x) 
	      		                       - lpt4.AT(k, s, x)) * partbbn.AT(0, 0, x2, s) )
	      		                   / lpt.AT(k, s, x)  / ad.AT(22);
      		}else{
      			bnpt.AT(k, x, s) = 0.0;
      		}
      	 }
      }
      
      if(k == partyr3 - 1 || k == partyr3){
          dmpt2.AT(k, x, s) = partbbn.AT(0, 0, x2, s) / ad.AT(22);
      }
      else if(flg_part >= 1 && (k == partyr4 - 1 || k == partyr4)){
      	if(lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x) > 1.0e-6){
	    	dmpt2.AT(k, x, s) = (lpt2.AT(k, s, x) * bnpti.AT(x, s)
	    	                    + (lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) * partbbn.AT(1, 0, x2, s))
	    	                   / (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) / ad.AT(22);
      	}else{
      		dmpt2.AT(k, x, s) = 0.0;
      	}
      }
      
    }
    }
    }
  }

  if(pseid == 0) {
    for(int k = KS; k <= KE; k++) {
      if(flg_hiho70 == 0 || (flg_hiho70 >= 1 && k < hiho70yr - 5)) {
        for(int x = 70; x <= 84; x++) {
          for(int s = 1; s <= 3; s++) {
            bn.AT(k, x, s) = 0.0;
            if(s <= 2) {
              bnpt.AT(k, x, s) = 0.0;
            }
          }
        }
      }
    }
  }


  if(key == 11 && nenbeex == 0) {
 
    FILE *fpho = fp_map["hou_out"];
    fprintf(fpho, "%s\n", "報酬設定ファイルの出力（パート適用拡分を除く）");
    
    for(int s = 1; s <= 2; s++) {
      for(int k = KS; k <= 35; k++) {
        vals.clear();
        for(int x = 15; x <= 69; x++) vals.push_back(l.AT(k, s, x));
        fprintf(fpho, "L,%d,%d,%s\n", s, k, csv::join("%.0lf", vals).c_str());

        vals.clear();
        for(int x = 15; x <= 69; x++) vals.push_back(bn.AT(k, x, s));
        fprintf(fpho, "BN,%d,%d,%s\n", s, k, csv::join(vals).c_str());
        
        vals.clear();
        for(int x = 15; x <= 69; x++) vals.push_back(br.AT(k, x, s));
        fprintf(fpho, "BR,%d,%d,%s\n", s, k, csv::join(vals).c_str());
      }
    }
  }
}
