#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
#include <iostream>
namespace sst = sepsstd;
namespace csv = csvio;

static void set_tmsij(v1_t &, v1_t &, v1_t &);


void seps::dtst(void) {

  v5_t wn = VEC(double, 115, 10, 13, 4, 1);
  double tmp, tmx, tmy, tmgbe;
  double tamari = 0;

  sst::subc2(g    ,14,115, 0,100);
  sst::subc2(ge   ,14,115, 0,100);
  sst::subc2(gpt  ,14,115, 0,100);
  sst::subc2(bb   ,14,115, 0,100);
  sst::subc2(bbpt ,14,115, 0,100);
  sst::subc4(z    ,14,115, 0,100, 0,1, 0,9);
  sst::subc4(ze   ,14,115, 0,100, 0,1, 0,9);
  sst::subc5(w    ,14,115, 0,100, 0,0, 0,7, 0,3);
  sst::subc5(we   ,14,115, 0,100, 0,0, 0,7, 0,3);
  sst::subc4(psz  ,14,115, 0,100, 0,1, 0,7);
  sst::subc4(psze ,14,115, 0,100, 0,1, 0,7);

  
  sst::subc2(gd   ,55,65, 0,100);
  sst::subc3(r    ,0,115, 0,15, 1,13); 
  sst::subc4(f    ,0,115, 0,15, 1,13, 1,23);
  sst::subc4(f_min,0,115, 0,15, 1,13, 1,23);
  sst::subc4(f_hik,0,115, 0,15, 1,13, 1,23);
  sst::subc4(hn   ,0,115, 0,15, 1,13, 1,4);
  sst::subc3(pshn ,0,115, 0,15, 1,13);

  sst::subc1(rsen   ,60,70);
  sst::subc2(hnsen  ,60,70, 1,2);
  sst::subc1(pshnsen,60,70);
  sst::subc2(fsen   ,60,70, 1,23);
  sst::subc2(fsenmin,60,70, 1,23);
  sst::subc2(fsenhik,60,70, 1,23);

  sst::subc3(fkouzai2, 70,84, 0,10, 1,2);

  sst::subc5(wn,    0,115, 0,10, 1,13, 1,4 ,0,1);

  FILE *fph;
  if(s == 1) fph = fp_map["hk-1"];
  if(s == 2) fph = fp_map["hk-2"];
  if(s == 3) {
    assert(pseid == 0);
    fph = fp_map["hk-3"];
  }

  csv::skip(fph, 3);
  seps::subrh2(fph, 0, g, "g");

  seps::subrh2(fph, 0, ge, "ge");

  seps::subrh2(fph, 0, gpt, "gpt");

  seps::subrh2(fph, 0, bb, "bb");

  seps::subrh2(fph, 0, bbpt, "bbpt");

  FOR(i, 0, 1) FOR(j, 0, 8) {
    seps::subrh4(fph, 0, z, "z", i, j);
  }
  
  FOR(i, 0, 1) FOR(j, 0, 8) {
    seps::subrh4(fph, 0, ze, "ze", i, j);
  }

  FOR(ii, 2, 3) {
    seps::subrh5(fph, 0, w, "w", 0, 0, ii);
  }
  FOR(j, 0, 6) {
    seps::subrh5(fph, 0, w, "w", 0, j, 0);
    seps::subrh5(fph, 0, w, "w", 0, j, 1);
    if(j == 4) {
      seps::subrh5(fph,0, w, "w", 0, j, 2);
      seps::subrh5(fph,0, w, "w", 0, j, 3);
    }
  }
  
  FOR(ii, 2, 3) {
    seps::subrh5(fph, 0, we, "we", 0, 0, ii);
  }
  FOR(j, 0, 6) {
    seps::subrh5(fph, 0, we, "we", 0, j, 0);
    seps::subrh5(fph, 0, we, "we", 0, j, 1);
    if(j == 4) {
      seps::subrh5(fph, 0, we, "we", 0, j, 2);
      seps::subrh5(fph, 0, we, "we", 0, j, 3);
    }
  }


  FOR(x, 15, 74) FOR(t, 0, 50) {
    FOR(i, 0, 1) {
      z .AT(x, t, i, 9) = z.AT(x, t, i, 3);
      z .AT(x, t, i, 3) = z.AT(x, t, i, 3) + z.AT(x, t, i, 4);
      z .AT(x, t, i, 4) = z.AT(x, t, i, 5);
      z .AT(x, t, i, 5) = z.AT(x, t, i, 6);
      z .AT(x, t, i, 6) = z.AT(x, t, i, 7);
      z .AT(x, t, i, 7) = z.AT(x, t, i, 8);
      z .AT(x, t, i, 8) = 0.0;
      ze.AT(x, t, i, 9) = ze.AT(x, t, i, 3);
      ze.AT(x, t, i, 3) = ze.AT(x, t, i, 3) + ze.AT(x, t, i, 4);
      ze.AT(x, t, i, 4) = ze.AT(x, t, i, 5);
      ze.AT(x, t, i, 5) = ze.AT(x, t, i, 6);
      ze.AT(x, t, i, 6) = ze.AT(x, t, i, 7);
      ze.AT(x, t, i, 7) = ze.AT(x, t, i, 8);
      ze.AT(x, t, i, 8) = 0.0;

      
      if(KIJUN - x > -54) {
        if(z.AT(x, t, i, 1) > 0.0)  z .AT(x, t, i, 1) = 0.0;
        if(ze.AT(x, t, i, 1) > 0.0) ze.AT(x, t, i, 1) = 0.0;
      }
      tmp = z.AT(x, t, i, 1)
            + z.AT(x, t, i, 2)
            + z.AT(x, t, i, 3)
            + z.AT(x, t, i, 4);
      if(z.AT(x, t, i, 0) < tmp) {
        z.AT(x, t, i, 0) = tmp;
      } else if(z.AT(x, t, i, 0) > tmp) {
        if(tmp > 0.0) {
          tmp = z.AT(x, t, i, 0) / tmp;
          z.AT(x, t, i, 0) = 0.0;
          FOR(j, 1, 4) {
            z.AT(x, t, i, j) = z.AT(x, t, i, j) * tmp;
            z.AT(x, t, i, 0) = z.AT(x, t, i, 0) + z.AT(x, t, i, j);
          }
        } else {
          z.AT(x, t, i, 0) = 0.0;
        }
      }
      tmp = ze.AT(x, t, i, 1)
            + ze.AT(x, t, i, 2)
            + ze.AT(x, t, i, 3)
            + ze.AT(x, t, i, 4);
      if(ze.AT(x, t, i, 0) < tmp) {
        ze.AT(x, t, i, 0) = tmp;
      } else if(ze.AT(x, t, i, 0) > tmp) {
        if(tmp > 0.0) {
          tmp = ze.AT(x, t, i, 0) / tmp;
          ze.AT(x, t, i, 0) = 0.0;
          FOR(j, 1, 4) {
            ze.AT(x, t, i, j) = ze.AT(x, t, i, j) * tmp;
            ze.AT(x, t, i, 0) = ze.AT(x, t, i, 0) + ze.AT(x, t, i, j);
          }
        } else {
          ze.AT(x, t, i, 0) = 0.0;
        }
      }
    }

    FOR(ii, 0, 1) {
      w .AT(x, t, 0, 7, ii) = w .AT(x, t, 0, 3, ii);
      w .AT(x, t, 0, 3, ii) = w .AT(x, t, 0, 3, ii) + w .AT(x, t, 0, 4, ii);
      w .AT(x, t, 0, 4, ii) = w .AT(x, t, 0, 5, ii);
      w .AT(x, t, 0, 5, ii) = 0.0;
      w .AT(x, t, 0, 0, ii) = w .AT(x, t, 0, 0, ii) - w .AT(x, t, 0, 4, ii);
      we.AT(x, t, 0, 7, ii) = we.AT(x, t, 0, 3, ii);
      we.AT(x, t, 0, 3, ii) = we.AT(x, t, 0, 3, ii) + we.AT(x, t, 0, 4, ii);
      we.AT(x, t, 0, 4, ii) = we.AT(x, t, 0, 5, ii);
      we.AT(x, t, 0, 5, ii) = 0.0;
      we.AT(x, t, 0, 0, ii) = we.AT(x, t, 0, 0, ii) - we.AT(x, t, 0, 4, ii);
    }
   	
   	we.AT(x, t, 0, 0, 2) = we.AT(x, t, 0, 0, 2) - we.AT(x, t, 0, 4, 2);
   	we.AT(x, t, 0, 0, 3) = we.AT(x, t, 0, 0, 3) - we.AT(x, t, 0, 4, 3);

  }

  std::cout << "被保険者の読み込みが終わりました" << "\n";


  FILE *fpj;
  if(s == 1) fpj = fp_map["jk-1"];
  if(s == 2) fpj = fp_map["jk-2"];
  if(s == 3) {
    assert(pseid == 0);
    fpj = fp_map["jk-3"];
  }

  csv::skip(fpj, 4);
  seps::subrj3(fpj, 0, r);

  FOR(j, 1, 23) {
    seps::subrj4(fpj, 3, f, j);
  }
  seps::subrj4(fpj, 3, f_hik, 1);
  seps::subrj4(fpj, 3, f_min, 1);
  FOR(j, 1, 4) {
    seps::subrj4(fpj, 0, hn, j);
  }
  FOR(jj, 1, 4) {
    seps::subrj5(fpj, 3, wn, jj, 0);
    seps::subrj5(fpj, 3, wn, jj, 1);
  }

  std::cout << "受給権者の読み込みが終わりました" << "\n";

 FOR(i, 1, 13) FOR(xx, 0, 10) {
 	r.AT(114, xx, i) += r.AT(115, xx, i);
 	r.AT(115, xx, i)  = 0;
	 	
 	FOR(j, 1, 4){
	 	hn   .AT(114, xx, i, j) += hn   .AT(115, xx, i, j);
	 	hn   .AT(115, xx, i, j)  = 0;
	}
	FOR(j, 1, 23){
	 	f    .AT(114, xx, i, j) += f    .AT(115, xx, i, j);
	    f_hik.AT(114, xx, i, j) += f_hik.AT(115, xx, i, j);
	    f_min.AT(114, xx, i, j) += f_min.AT(115, xx, i, j);
	 	f    .AT(115, xx, i, j)  = 0;
	    f_hik.AT(115, xx, i, j)  = 0;
	    f_min.AT(115, xx, i, j)  = 0;
    }
 }


  FOR(x, 0, 115) {
    FOR(i, 1, 4) FOR(xx, 1, 10) {
      r.AT(x, 0, i) = r.AT(x, 0, i) - r.AT(x, xx, i);
      FOR(j, 1, 23) {
        f    .AT(x, 0, i, j) = f    .AT(x, 0, i, j) - f    .AT(x, xx, i, j);
        f_hik.AT(x, 0, i, j) = f_hik.AT(x, 0, i, j) - f_hik.AT(x, xx, i, j);
        f_min.AT(x, 0, i, j) = f_min.AT(x, 0, i, j) - f_min.AT(x, xx, i, j);
      }
      FOR(j, 1, 4) {
        hn.AT(x, 0, i, j)    = hn.AT(x, 0, i, j) - hn.AT(x, xx, i, j);

        wn.AT(x, 0, i, j, 0) = wn.AT(x, 0, i, j, 0) - wn.AT(x, xx, i, j, 0);
        wn.AT(x, 0, i, j, 1) = wn.AT(x, 0, i, j, 1) - wn.AT(x, xx, i, j, 1);
      }
    }
    FOR(i, 5, 13) FOR(xx, 1, 10) {
      r.AT(x, xx, i) = 0.0;
      FOR(j, 1, 23) {
        f    .AT(x, xx, i, j) = 0.0;
        f_hik.AT(x, xx, i, j) = 0.0;
        f_min.AT(x, xx, i, j) = 0.0;
      }
      FOR(j, 1, 4) {
        hn.AT(x, xx, i, j)    = 0.0;

        wn.AT(x, xx, i, j, 0) = 0.0;
        wn.AT(x, xx, i, j, 1) = 0.0;
      }
    }

    if(konen != 1) {
      f.AT(x, 0, 9, 12) = f.AT(x, 0, 9, 12) * ema.AT(s);
    }
    FOR(i, 1, 10) FOR(xx, 0, 10) {
      if(i >= 5 && xx != 0) continue;
      if(KIJUN - x > -54) {
        if(hn.AT(x, xx, i, 1) > 0.0) {
          hn.AT(x, xx, i, 2) = hn.AT(x, xx, i, 2) + hn.AT(x, xx, i, 1);
          hn.AT(x, xx, i, 1) = 0.0;
        }
      }
    }
  }
  
  if(konen == 1) { 
    FOR(i, 1, 13) {
      int ii;
      if(           i <= 2 ) ii = 1;
      if(i >= 3  && i <= 4 ) ii = 6;
      if(i >= 5  && i <= 8 ) ii = 2;
      if(i == 9            ) ii = 3;
      if(i == 10           ) ii = 4;
      if(i >= 11 && i <= 13) ii = 5;

      FOR(x, 0, 115) {
        seps::sknr(k, x, xxr, xrb);
        xxr = max(60, xxr);
        xrb = max(60, xrb);

        FOR(xx, 0, 10) {
          if(i >= 5 && xx > 0) continue;
            if(ii == 1 || ii == 6) {
            if(xx <= 5) {
              if(x >= 60 && xrb > 60 && (65 - xx) >= 60 && (65 - xx) < xrb) {
                f    .AT(x, xx, i, 1) = f    .AT(x, xx, i, 1) / rigbe.AT(s2, 65 - xx, xrb, 0);
                f_hik.AT(x, xx, i, 1) = f_hik.AT(x, xx, i, 1) / rigbe.AT(s2, 65 - xx, xrb, 0);
                f_min.AT(x, xx, i, 1) = f_min.AT(x, xx, i, 1) / rigbe.AT(s2, 65 - xx, xrb, 0);
                f    .AT(x, xx, i, 3) = f    .AT(x, xx, i, 3) / rigk.AT(s2, 65-xx, xxr, 0);
              }
              if(65 - xx < xxr && x >= 65 - xx && x < 65 && xxr < 65) {
                f.AT(x, xx, i, 2) =f.AT(x, xx, i, 2) / rigd.AT(s2, 65 - xx, xxr, 0);
              }
            } else {
              tmgbe = 1.0 + 0.007 * (xx - 5) * 12.0;
              f    .AT(x, xx, i, 1) = f    .AT(x, xx, i, 1) / tmgbe;
              f_hik.AT(x, xx, i, 1) = f_hik.AT(x, xx, i, 1) / tmgbe;
              f_min.AT(x, xx, i, 1) = f_min.AT(x, xx, i, 1) / tmgbe;
              f    .AT(x, xx, i, 3) = f.AT(x, xx, i, 3) / tmgbe;
            }
          } 

          if(kd.AT(KIJUN, ii, 1, x) >= 1.0e-6) {
            if(5 <= i && i <= 13) {
              f.AT(x, xx, i, 4)  = f.AT(x, xx, i, 4)  / kd.AT(KIJUN, ii, 1, x);
              f.AT(x, xx, i, 23) = f.AT(x, xx, i, 23) / kd.AT(KIJUN, ii, 1, x);
            }
            f.AT(x, xx, i, 19) = f.AT(x, xx, i, 19) / kd.AT(KIJUN, ii, 1, x);
          }

          double adt_ratio_3_2 = adt.AT(3) / adt.AT(2); 
          double kd_sum = kd.AT(KIJUN, ii, 2, x) + kd.AT(KIJUN, ii, 3, x) * adt_ratio_3_2;
          if(kd_sum >= 1.0e-6) {
            if(5 <= i && i <= 13) {
              f.AT(x, xx, i, 5) = f.AT(x, xx, i, 5) / kd_sum;
            }
            f.AT(x, xx, i, 20) = f.AT(x, xx, i, 20) / kd_sum;
            f.AT(x, xx, i, 21) = f.AT(x, xx, i, 21) / kd_sum;
          }
          if((i == 11  ||  i == 12)  &&  x >= 19) {
            double rc_kijun = rc.AT(s, KIJUN, x);
            if(rc_kijun >= 1.0e-6) {
              f.AT(x, xx, i, 14) = f.AT(x, xx, i, 14) / rc_kijun;
              f.AT(x, xx, i, 17) = f.AT(x, xx, i, 17) / rc_kijun;
            }
            if(1.0 - rc_kijun >= 1.0e-6) {
              f.AT(x, xx, i, 18) = f.AT(x, xx, i, 18) / (1.0 - rc_kijun);
            }
          }
        }
      }
    }
  }
  
  else {
   
    FOR(i, 1, 13) FOR(x, 0, 115) FOR(xx, 0, 10) {
      if(i == 5 || i == 6 || i == 10) {
        f.AT(x, xx, i, 19) = 0.0;
        f.AT(x, xx, i, 20) = 0.0;
      }
      if(i == 13 && x >= 19) {
        f.AT(x, xx, i, 17) = f.AT(x, xx, i, 17) * rc.AT(s, KIJUN, x);
      }
    }
  }

  v1_t tmsi = VEC(double, 13);
  v1_t tmsj = VEC(double, 23);
  v1_t tmso = VEC(double, 23);
  set_tmsij(tmsi, tmsj, tmso);


    FOR(i, 1, 13) FOR(xx, 0, 10) {
      if(i >= 5 && xx > 0) continue;
      FOR(x, 0, 115) {
        if(i <= 8  &&  x < 71+KIJUN  &&  konen != 1) {
          f.AT(x, xx, i, 16) = 0.0;
        }
        FOR(j, 1, 23) {
          if(j == 4 || j == 5 || j == 23 || (j >= 15 && j <= 20)) {
            if((i >= 5 && i != 9 && i != 11) && 
               (j == 4 || j == 5 || j == 23)) {
              f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * tmso.AT(j);
            } else {
              f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * tmsj.AT(j);
            }
          }
        }

        if(pseid != 2 && pseid != 3) {
          FOR(j, 1, 23) {
            if(j == 1 || j == 2 || j == 3 || (7 <= j && j <= 12)) {
              f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * tmsi.AT(i);
            }
          }
          f_min.AT(x, xx, i, 1) = f_min.AT(x, xx, i, 1) * tmsi.AT(i);
          f_hik.AT(x, xx, i, 1) = f_hik.AT(x, xx, i, 1) * tmsi.AT(i);
        }
      }
    }



  FOR(x, 0, 115) FOR(xx, 0, 10) FOR(i, 1, 13) FOR(j, 1, 23) {
    if(j == 1) {
    }
    else if(j == 10) {
      f_hik.AT(x, xx, i, j) = f.AT(x, xx, i, j);
      f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * hikrate * (1.0 - tamari);

      if(KIJUN - x == -70) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.019 * 0.998 * 1.024 / 1.031;
      } else if(KIJUN - x == -69) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.042 * 0.996 * 1.025 / 1.031;
      } else if(KIJUN - x >= -68 && KIJUN -x <= -66) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.080 * 0.990         / 1.031;
      } else if(KIJUN - x == -65) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.080 * 0.990 * 1.004 / 1.031;
      } else if(KIJUN - x == -64) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.080 * 0.990 * 1.004 * 1.007 / 1.031;
      } else if(KIJUN - x >= -63) {
        f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                            * 1.080 * 0.990 * 1.004 * 1.007 * 1.008 / 1.031;
      }

      f_min.AT(x, xx, i, j) = f_hik.AT(x, xx, i, j)
                              * hikrate * (1.0 - tamari)
                              * 1.080 * 0.990 * 1.004 * 1.007 * 1.008 / 1.031
                              * 0.80;

      FOR(kk, 5, KIJUN) {
        if(KIJUN - x >= kk - 67) {
          f.AT(x, xx, i, j) = f.AT(x, xx, i, j)
                              * (1.0 + hh.AT(kk)) / (1.0 + ci.AT(kk));
        }
        f_min.AT(x, xx, i, j) = f_min.AT(x, xx, i, j)
                                *(1.0 + hh.AT(kk)) / (1.0 + ci.AT(kk));
      }
    }
    else {
      f_min.AT(x, xx, i, j) = f.AT(x, xx, i, j) * 0.80;
    }
  }


  FOR(x, 14, 115) FOR(t, 0, 100) FOR(j, 0, 7) {
    if(j <= 3 || j == 7) {
      if(w.AT(x, t, 0, 0, 0) > 1.0e-6) {
        w.AT(x, t, 0, j, 2) = w.AT(x, t, 0, j, 0) * w.AT(x, t, 0, 0, 2) / w.AT(x, t, 0, 0, 0);
        w.AT(x, t, 0, j, 3) = w.AT(x, t, 0, j, 0) * w.AT(x, t, 0, 0, 3) / w.AT(x, t, 0, 0, 0);
      } else {
        w.AT(x, t, 0, j, 2) = 0.0;
        w.AT(x, t, 0, j, 3) = 0.0; 
      }
      if(we.AT(x, t, 0, 0, 0) > 1.0e-6) {
        we.AT(x, t, 0, j, 2) = we.AT(x, t, 0, j, 0) * we.AT(x, t, 0, 0, 2) / we.AT(x, t, 0, 0, 0);
        we.AT(x, t, 0, j, 3) = we.AT(x, t, 0, j, 0) * we.AT(x, t, 0, 0, 3) / we.AT(x, t, 0, 0, 0);
      } else {
        we.AT(x, t, 0, j, 2) = 0.0;
        we.AT(x, t, 0, j, 3) = 0.0;
      }
    }
  }



  if(key == 12 &&  psly == -3) {
    FOR(x, 15, xend) FOR(t, 0, 50) {
      FOR(i, 0, 1) FOR(j, 0, 6) {
        psz.AT(x, t, i, j) = z.AT(x, t, i, j);
        psze.AT(x, t, i, j) = ze.AT(x, t, i, j);
        if(j == 0) {
          z.AT(x, t, i, j) = z.AT(x, t, i, 1) + z.AT(x, t, i, 2) + z.AT(x, t, i, 9);
          ze.AT(x, t, i, j) = ze.AT(x, t, i, 1) + ze.AT(x, t, i, 2) + ze.AT(x, t, i, 9);
        } else if(j == 3) {
          z.AT(x, t, i, j) = z.AT(x, t, i, 9);
          ze.AT(x, t, i, j) = ze.AT(x, t, i, 9);
        } else if(j == 4) {
          z.AT(x, t, i, j) = 0.0;
          ze.AT(x, t, i, j) = 0.0;
        } else {
          z.AT(x, t, i, j) = z.AT(x, t, i, j);
          ze.AT(x, t, i, j) = ze.AT(x, t, i, j);
        }
      }

      FOR(j, 0, 4) FOR(ii, 0, 3) {
        if(j == 0) {
          w.AT(x, t, 0, j, ii) =
            w.AT(x, t, 0, 1, ii) + w.AT(x, t, 0, 2, ii) + w.AT(x, t, 0, 7, ii);
          we.AT(x, t, 0, j, ii) =
            we.AT(x, t, 0, 1, ii) + we.AT(x, t, 0, 2, ii) + we.AT(x, t, 0, 7, ii);
        } else if(j == 3) {
          w.AT(x, t, 0, j, ii) = w.AT(x, t, 0, 7, ii);
          we.AT(x, t, 0, j, ii) = we.AT(x, t, 0, 7, ii);
        } else if(j == 4) {
          w.AT(x, t, 0, j, ii) = 0.0;
          we.AT(x, t, 0, j, ii) = 0.0;
        } else {
          w.AT(x, t, 0, j, ii) = w.AT(x, t, 0, j, ii);
          we.AT(x, t, 0, j, ii) = we.AT(x, t, 0, j, ii);
        }
      }
    }

    FOR(x, 0, 115) FOR(xx, 0, 10) FOR(i, 1, 13) {
      tmx = 0.0;
      tmy = 0.0;

      double _hn_sum =
        hn.AT(x, xx, i, 1) + hn.AT(x, xx, i, 2)
        + hn.AT(x, xx, i, 3) + hn.AT(x, xx, i, 4);

      if(_hn_sum > 1.0e-6) {
        tmx = (hn.AT(x, xx, i, 1) + hn.AT(x, xx, i, 2)) / _hn_sum;
      } else {
        tmx = 0.0;
      }
      tmx = max(0.0, min(1.0, tmx));

      double _wn_sum =
        wn.AT(x, xx, i, 1, 0) + wn.AT(x, xx, i, 2, 0)
        + wn.AT(x, xx, i, 3, 0) + wn.AT(x, xx, i, 4, 0);

      if(_wn_sum > 1.0e-6) {
        tmy = (wn.AT(x, xx, i, 1, 0) + wn.AT(x, xx, i, 2, 0)) / _wn_sum;
      } else {
        tmy = 0.0;
      }
      tmy = max(0.0, min(1.0, tmy));

      pshn.AT(x, xx, i) = r.AT(x, xx, i) * tmx;
      pshn.AT(x, xx, i) = r.AT(x, xx, i) * tmx;
      FOR(j, 1, 23) {
        if(j == 1 || j == 10) {
          f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * tmy;
          f_min.AT(x, xx, i, j) = f_min.AT(x, xx, i, j) * tmy;
          f_hik.AT(x, xx, i, j) = f_hik.AT(x, xx, i, j) * tmy;
        } else {
          f.AT(x, xx, i, j) = f.AT(x, xx, i, j) * tmx;
          f_min.AT(x, xx, i, j) = f_min.AT(x, xx, i, j) * tmx;
        }
      }
    }
  }
   

  FOR(xx, 0, 10) FOR(x, 0, 115) FOR(i, 1, 13) {
    hn.AT(x, xx, i, 2) = hn.AT(x, xx, i, 2) + hn.AT(x, xx, i, 3) + hn.AT(x, xx, i, 4);
    hn.AT(x, xx, i, 3) = 0.0;
    hn.AT(x, xx, i, 4) = 0.0;
  }
} 


static void set_tmsij(v1_t &tmsi, v1_t &tmsj, v1_t &tmso) {

  FOR(i, 1, 13) {
    tmsi.AT(i) = 1.0;
  }
  FOR(j, 1, 23) {
    tmsj.AT(j) = 1.0;
    tmso.AT(j) = 1.0;
  }
  
  if(flg_hantei == 0){
  
    if(pseid == 0) {
	  tmsj.AT(15) = 1.1711;
	  tmsj.AT(16) = 0.9560;
	  tmsj.AT(4)  = 1.0021;
	  tmso.AT(4)  = 1.1608;
    } else if(pseid == 1) {
      tmsj.AT(15) = 1.1199;
      tmsj.AT(16) = 0.1679;
      tmsj.AT(4)  = 1.0000;
      tmso.AT(4)  = 1.0005;
    } else if(pseid == 4) {
      tmsj.AT(15) = 1.1212;
      tmsj.AT(16) = 0.2987;
      tmsj.AT(4)  = 1.0000;
      tmso.AT(4)  = 1.0003;
    } else if(pseid == 5) {
      tmsj.AT(15) = 1.1199;
      tmsj.AT(16) = 0.2366;
      tmsj.AT(4)  = 1.0000;
      tmso.AT(4)  = 1.0001;
    }
    
    tmsj.AT(5)  = tmsj.AT(4);
    tmsj.AT(23) = tmsj.AT(4);
    tmso.AT(5)  = tmso.AT(4);
    tmso.AT(23) = tmso.AT(4);
    tmsj.AT(17) = tmsj.AT(15);
    tmsj.AT(18) = tmsj.AT(15);
    tmsj.AT(19) = tmsj.AT(15);
    tmsj.AT(20) = tmsj.AT(15);


    if(pseid == 0) {
       tmsi.AT(1) = 1.0005;
	   tmsi.AT(2) = 1.0030;
	   tmsi.AT(3) = 1.0051;
	   tmsi.AT(4) = 1.0089;
	   tmsi.AT(5) = 0.9807;
	   tmsi.AT(6) = 0.9853;
	   tmsi.AT(7) = 1.0006;
	   tmsi.AT(8) = 1.0001;
	   tmsi.AT(9) = 0.9997;
	   tmsi.AT(10) = 1.0129;
	   tmsi.AT(11) = 1.0001;
	   tmsi.AT(12) = 1.0000;
	   tmsi.AT(13) = 1.0003;
    } else if(pseid == 1) {
      tmsi.AT(1) = 0.9910;
      tmsi.AT(2) = 1.0198;
      tmsi.AT(3) = 0.9735;
      tmsi.AT(4) = 1.0195;
      tmsi.AT(9) = 1.0095;
      tmsi.AT(11) = 0.9624;
    } else if(pseid == 4) {
      tmsi.AT(1) = 1.0004;
      tmsi.AT(2) = 1.0384;
      tmsi.AT(3) = 0.9859;
      tmsi.AT(4) = 0.9808;
      tmsi.AT(9) = 1.0539;
      tmsi.AT(11) = 1.0407;
    } else if(pseid == 5) {
      tmsi.AT(1) = 1.0011;
      tmsi.AT(2) = 0.9920;
      tmsi.AT(3) = 0.9743;
      tmsi.AT(4) = 0.9767;
      tmsi.AT(9) = 1.0557;
      tmsi.AT(11) = 0.8044;
   }
   
 }

}