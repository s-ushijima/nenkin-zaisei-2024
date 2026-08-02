#include "sepscommon.h"
#include "sepslib.h"
#include <cassert>
namespace sst = sepsstd;

void seps::dsitk(int x, int t, int ii, double &bk, double &bk2, double &bk3) {

  double ch, tmq;
  v1_t tmp    = VEC(double, 4);
  v2_t zd     = VEC(double, 1, 6);
  v2_t pszd   = VEC(double, 1, 6);
  v1_t wd     = VEC(double, 3);
  v1_t wd2    = VEC(double, 3);
  v2_t zem    = VEC(double, 1, 6);
  v2_t pszem  = VEC(double, 1, 6);
  v1_t wem    = VEC(double, 3);
  v1_t wem2   = VEC(double, 3);



  it  = 4;
  xr  = 0;
  bk  = 0.0;
  bk2 = 0.0;
  bk3 = 0.0;
  tn  = 0.0;
  ta  = 0.0;
  tz = VEC(double, 4);

  int kx = k - x;
  int kx_74 = max(kx, -74);

  if(ii == 1) {
    tmp.AT(1) = ze.AT(x, t, 0, 0);
    tmp.AT(2) = ze.AT(x, t, 0, 5);
    tmp.AT(3) = ze.AT(x, t, 1, 0);
    tmp.AT(4) = ze.AT(x, t, 1, 5);
    if(key == 12 && k >= psly) {
      tmp.AT(1) = psze.AT(x, t, 0, 0);
      tmp.AT(2) = psze.AT(x, t, 0, 5);
      tmp.AT(3) = psze.AT(x, t, 1, 0);
      tmp.AT(4) = psze.AT(x, t, 1, 5);
    }
  }
  else if(ii == 2) {
    tmp.AT(1) = z.AT(x, t, 0, 0);
    tmp.AT(2) = z.AT(x, t, 0, 5);
    tmp.AT(3) = z.AT(x, t, 1, 0);
    tmp.AT(4) = z.AT(x, t, 1, 5);
    if(key == 12 && k >= psly) {
      tmp.AT(1) = psz.AT(x, t, 0, 0);
      tmp.AT(2) = psz.AT(x, t, 0, 5);
      tmp.AT(3) = psz.AT(x, t, 1, 0);
      tmp.AT(4) = psz.AT(x, t, 1, 5);
    }
  }
  else if(ii == 9 || ii == 15 || ii == 16) {
    FOR(j, 0, 6) FOR(i, 0, 1) {
      if(j == 0 || j == 4 || 
         (s2 == 1 && x >= 40 && j == 5) || 
         (s2 >= 2 && x >= 35 && j == 5) || 
         (x >= 20 && x <= 60 && j == 6)   ) {
        if((s2 != 3 && i == 0)  || 
           (s2 == 3 && (i == 0 || i == 1))) {
          ch = 0.5;
        } else {
          ch = 0.0;
        }
      } else {
        ch = 0.0;
      }
      if(key == 12 && k >= psly) {
        if(x < xend) {
          pszd.AT(i, j) = max(0.0, psz.AT(x, t, i, j)  -ch);
        } else {
          pszd.AT(i, j) = max(0.0, psz.AT(x - 1, t, i, j) - ch);
        }
        ch = 0.0;
      }
      if(key != 12 || k < psly) {
        if(x < xend) {
          zd.AT(i, j) = max(0.0, z.AT(x, t, i, j) - ch);
        } else {
          zd.AT(i, j) = max(0.0, z.AT(x - 1, t, i, j) - ch);
        }
      } else {
        if(x < xend) {
          zd.AT(i, j) = z.AT(x, t, i, j);
        } else {
          zd.AT(i, j) = z.AT(x - 1, t, i, j);
        }
      }
    }
    FOR(i2, 0, 3) {
      if(key != 12 || k < psly) {
        if(x < xend) {
          wd .AT(i2) = w.AT(x, t, 0, 0, i2);
          wd2.AT(i2) = max(0.0, w.AT(x, t, 0, 4, i2) - chwd.AT(x, t, i2));
        } else {
          wd .AT(i2) = w.AT(x-1, t, 0, 0, i2);
          wd2.AT(i2) = max(0.0, w.AT(x-1, t, 0, 4, i2) - chwd.AT(x - 1, t, i2));
        }
      } else {
        if(x < xend) {
          wd .AT(i2) = w.AT(x, t, 0, 0, i2);
          wd2.AT(i2) = w.AT(x, t, 0, 4, i2);
        } else {
          wd .AT(i2) = w.AT(x - 1, t, 0, 0, i2);
          wd2.AT(i2) = w.AT(x - 1, t, 0, 4, i2);
        }
      }
    }
  }
  else if(ii == 17) {
    FOR(j, 0, 6) FOR(i, 0, 1) {
      zem.AT(i, j) = ze.AT(x, t, i, j);
      if(key == 12 && k >= psly) {
        pszem.AT(i, j) = psze.AT(x, t, i, j);
      }
    }
    tmp.AT(1) = zem.AT(0, 0);
    tmp.AT(2) = zem.AT(0, 5);
    tmp.AT(3) = zem.AT(1, 0);
    tmp.AT(4) = zem.AT(1, 5);
    if(key == 12 && k >= psly) {
      tmp.AT(1) = pszem.AT(0, 0);
      tmp.AT(2) = pszem.AT(0, 5);
      tmp.AT(3) = pszem.AT(1, 0);
      tmp.AT(4) = pszem.AT(1, 5);
    }
    FOR(i2, 0, 3) {
      wem .AT(i2) = we.AT(x, t, 0, 0, i2);
      wem2.AT(i2) = we.AT(x, t, 0, 4, i2);
    }
  }


  if( kx >= -48 && tmp.AT(1) >= 20.0 - 1.0e-6) it = 3;

  if((kx <= -54 && tmp.AT(2) >= 15.0 - 1.0e-6)  || 
     (kx == -53 && tmp.AT(2) >= 16.0 - 1.0e-6)  || 
     (kx == -52 && tmp.AT(2) >= 17.0 - 1.0e-6)  || 
     (kx == -51 && tmp.AT(2) >= 18.0 - 1.0e-6)  || 
     (kx == -50 && tmp.AT(2) >= 19.0 - 1.0e-6)  || 
     (kx <= -49 && tmp.AT(1) >= 20.0 - 1.0e-6)  || 
     (kx == -48 && tmp.AT(1) >= 21.0 - 1.0e-6)  || 
     (kx == -47 && tmp.AT(1) >= 22.0 - 1.0e-6)  || 
     (kx == -46 && tmp.AT(1) >= 23.0 - 1.0e-6)  || 
     (kx == -45 && tmp.AT(1) >= 24.0 - 1.0e-6)  || 
     (kx >= -44 && tmp.AT(1) >= 25.0 - 1.0e-6)    ) it = 1;

  if((kx <= -54 && tmp.AT(4) >= 15.0 - 1.0e-6)  || 
     (kx == -53 && tmp.AT(4) >= 16.0 - 1.0e-6)  || 
     (kx == -52 && tmp.AT(4) >= 17.0 - 1.0e-6)  || 
     (kx == -51 && tmp.AT(4) >= 18.0 - 1.0e-6)  || 
     (kx == -50 && tmp.AT(4) >= 19.0 - 1.0e-6)  || 
     (kx <= -49 && tmp.AT(3) >= 20.0 - 1.0e-6)  || 
     (kx == -48 && tmp.AT(3) >= 21.0 - 1.0e-6)  || 
     (kx == -47 && tmp.AT(3) >= 22.0 - 1.0e-6)  || 
     (kx == -46 && tmp.AT(3) >= 23.0 - 1.0e-6)  || 
     (kx == -45 && tmp.AT(3) >= 24.0 - 1.0e-6)  || 
     (kx >= -44 && tmp.AT(3) >= 25.0 - 1.0e-6)    ) it = 2;

  if(ii <= 8 || ii == 17) {
    xr = 60;

    if(konen == 1 && it == 2) {
      if(             kx <= -55) xr = 55;
      if(-54 <= kx && kx <= -53) xr = 56;
      if(-52 <= kx && kx <= -51) xr = 57;
      if(-50 <= kx && kx <= -49) xr = 58;
      if(-48 <= kx && kx <= -47) xr = 59;
    }


    xxr = xr;

    if((s2 == 1 && it != 2) || konen != 1) {
      if(kx >= -59 && kx <= -58) xxr = 61;
      if(kx >= -57 && kx <= -56) xxr = 62;
      if(kx >= -55 && kx <= -54) xxr = 63;
      if(kx >= -53 && kx <= -52) xxr = 64;
      if(kx >= -51             ) xxr = 65;
    } else if(s2 == 2 && it != 2) {
      if(kx >= -54 && kx <= -53) xxr = 61;
      if(kx >= -52 && kx <= -51) xxr = 62;
      if(kx >= -50 && kx <= -49) xxr = 63;
      if(kx >= -48 && kx <= -47) xxr = 64;
      if(kx >= -46             ) xxr = 65;
    } else {
      if(kx >= -42 && kx <= -41) xxr = 61;
      if(kx >= -40 && kx <= -39) xxr = 62;
      if(kx >= -38 && kx <= -37) xxr = 63;
      if(kx >= -36 && kx <= -35) xxr = 64;
      if(kx >= -34             ) xxr = 65;
    }


    xrb = xr;

    if((s2 == 1 && it != 2) || konen != 1) {
      if(kx >= -47 && kx <= -46) xrb = 61;
      if(kx >= -45 && kx <= -44) xrb = 62;
      if(kx >= -43 && kx <= -42) xrb = 63;
      if(kx >= -41 && kx <= -40) xrb = 64;
      if(kx >= -39             ) xrb = 65;
    } else if(s2 == 2 && it != 2) {
      if(kx >= -42 && kx <= -41) xrb = 61;
      if(kx >= -40 && kx <= -39) xrb = 62;
      if(kx >= -38 && kx <= -37) xrb = 63;
      if(kx >= -36 && kx <= -35) xrb = 64;
      if(kx >= -34             ) xrb = 65;
    } else {
      xrb = xxr;
    }
    
    assert(xr <= 65);
  }


  pro  = 0.0;
  pros = 0.0;
  if(kx >= -74 && kx <= -54) {
    pro = pre.AT(C19(kx));
    pros = pres.AT(C19(kx));
  } else if(kx > -54) {
    pro = prb;
    pros = prbs;
  } else {
    pro = pra;
    pros = pras;
  }


  if(ii == 1) {
    tz.AT(1) = ze.AT(x, t, 0, 0) - ze.AT(x, t, 0, 2) - ze.AT(x, t, 0, 3) - ze.AT(x, t, 0, 4);
    tz.AT(2) = ze.AT(x, t, 0, 2) + ze.AT(x, t, 0, 3) + ze.AT(x, t, 0, 4);
    tz.AT(3) = ze.AT(x, t, 0, 1) + ze.AT(x, t, 0, 2) + ze.AT(x, t, 0, 3);
    tz.AT(4) = ze.AT(x, t, 0, 0) - ze.AT(x, t, 0, 4);

    if(key == 12 && k >= psly) {
        tn = psze.AT(x, t, 0, 0);
    } else {
        tn=ze.AT(x, t, 0, 0);
    }
    
    tn = min(tn, can2.AT(C19(kx_74)));
    

    ta = ze.AT(x, t, 0, 6);
    if(tz.AT(3) > 1.0e-6) {
      tmq = tz.AT(4) / tz.AT(3);
    } else {
      tmq = 0.0;
    }
    bk  = (we.AT(x, t, 0, 0, 0) * tmq * pro + we.AT(x, t, 0, 4, 0) * pros) * hikrate;
    bk2 =  we.AT(x, t, 0, 0, 2) * tmq * pro + we.AT(x, t, 0, 4, 2) * pros;
    bk3 = (we.AT(x, t, 0, 0, 3) * tmq * pro + we.AT(x, t, 0, 4, 3) * pros) * hikrate * 0.8;
    pslr = 1.0;
    if(key == 12 && k >= psly) {
      if(psze.AT(x, t, 0, 0) > 1.0e-6) {
        pslr = min(1.0, ze.AT(x, t, 0, 0) / psze.AT(x, t, 0, 0));
      } else {
        pslr = 0.0;
      }
      tn *= pslr;
    }
  }

  else if(ii == 2) {
    tz.AT(1) = z.AT(x, t, 0, 0) - z.AT(x, t, 0, 2) - z.AT(x, t, 0, 3) - z.AT(x, t, 0, 4);
    tz.AT(2) = z.AT(x, t, 0, 2) + z.AT(x, t, 0, 3) + z.AT(x, t, 0, 4);
    tz.AT(3) = z.AT(x, t, 0, 1) + z.AT(x, t, 0, 2) + z.AT(x, t, 0, 3);
    tz.AT(4) = z.AT(x, t, 0, 0) - z.AT(x, t, 0, 4);

    if(key == 12 && k >= psly) {
        tn = psz.AT(x, t, 0, 0);
    } else {
        tn = z.AT(x, t, 0, 0);
    }
    
    tn = min(tn, can2.AT(C19(kx_74)));
    
    ta = z.AT(x, t, 0, 6);
    if(tz.AT(3) > 1.0e-6) {
      tmq = tz.AT(4) / tz.AT(3);
    } else {
      tmq = 0.0;
    }
    bk  = (w.AT(x, t, 0, 0, 0) * tmq * pro + w.AT(x, t, 0, 4, 0) * pros) * hikrate;
    bk2 =  w.AT(x, t, 0, 0, 2) * tmq * pro + w.AT(x, t, 0, 4, 2) * pros;
    bk3 = (w.AT(x, t, 0, 0, 3) * tmq * pro + w.AT(x, t, 0, 4, 3) * pros) * hikrate * 0.8;
    pslr = 1.0;
    if(key == 12 && k >= psly) {
      if(psz.AT(x, t, 0, 0) > 1.0e-6) {
        pslr = min(1.0, z.AT(x, t, 0, 0) / psz.AT(x, t, 0, 0));
      } else {
        pslr = 0.0;
      }
      tn = tn * pslr;
    }
  }

  else if(ii == 9 || ii == 15 || ii == 16) {
    tz.AT(1) = zd.AT(0, 0) - zd.AT(0, 2) - zd.AT(0, 3) - zd.AT(0, 4);
    tz.AT(2) = zd.AT(0, 2) + zd.AT(0, 3) + zd.AT(0, 4);
    if(key == 12 && k >= psly) {
      if(ii == 9 && pszd.AT(0, 0) >= 25.0) {
        bk  = wd.AT(0) * prb + wd2.AT(0) * prbs;
        bk2 = wd.AT(2) * prb + wd2.AT(2) * prbs;
        bk3 = wd.AT(3) * prb + wd2.AT(3) * prbs;
      } else if(ii == 15 && pszd.AT(0, 0) >= 25.0) {
        bk  = wd.AT(0) * pro + wd2.AT(0) * pros;
        bk2 = wd.AT(2) * pro + wd2.AT(2) * pros;
        bk3 = wd.AT(3) * pro + wd2.AT(3) * pros;
      } else if(ii == 16) {
        bk  = wd.AT(0) * prb + wd2.AT(0) * prbs;
        bk2 = wd.AT(2) * prb + wd2.AT(2) * prbs;
        bk3 = wd.AT(3) * prb + wd2.AT(3) * prbs;
      } else {
        if(pszd.AT(0, 0) > 1.0e-6) {
          if(ii == 9) {
            bk  = (wd.AT(0) * prb + wd2.AT(0) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
            bk2 = (wd.AT(2) * prb + wd2.AT(2) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
            bk3 = (wd.AT(3) * prb + wd2.AT(3) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
          } else {
            bk  = (wd.AT(0) * prb + wd2.AT(0) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
            bk2 = (wd.AT(2) * prb + wd2.AT(2) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
            bk3 = (wd.AT(3) * prb + wd2.AT(3) * prbs) * 25.0 / min(pszd.AT(0, 0), 25.0);
          }
        } else {
          bk  = 0.0;
          bk2 = 0.0;
          bk3 = 0.0;
        }
      }
    } else {
      if(ii == 9 && zd.AT(0, 0) >= 25.0) {
        bk  = wd.AT(0) * prb + wd2.AT(0) * prbs;
        bk2 = wd.AT(2) * prb + wd2.AT(2) * prbs;
        bk3 = wd.AT(3) * prb + wd2.AT(3) * prbs;
      } else if(ii == 15 && zd.AT(0, 0) >= 25.0) {
        bk  = wd.AT(0) * pro + wd2.AT(0) * pros;
        bk2 = wd.AT(2) * pro + wd2.AT(2) * pros;
        bk3 = wd.AT(3) * pro + wd2.AT(3) * pros;
      } else if(ii == 16) {
        bk  = wd.AT(0) * prb + wd2.AT(0) * prbs;
        bk2 = wd.AT(2) * prb + wd2.AT(2) * prbs;
        bk3 = wd.AT(3) * prb + wd2.AT(3) * prbs;
      } else {
        if(zd.AT(0, 0) > 1.0e-6) {
          if(ii == 9) {
            bk = (wd.AT(0) * prb + wd2.AT(0) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
            bk2= (wd.AT(2) * prb + wd2.AT(2) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
            bk3= (wd.AT(3) * prb + wd2.AT(3) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
          } else {
            bk = (wd.AT(0) * prb + wd2.AT(0) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
            bk2= (wd.AT(2) * prb + wd2.AT(2) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
            bk3= (wd.AT(3) * prb + wd2.AT(3) * prbs) * 25.0 / min(zd.AT(0, 0), 25.0);
          }
        } else {
          bk  = 0.0;
          bk2 = 0.0;
          bk3 = 0.0;
        }
      }
    }
    bk  = bk * hikrate;
    bk3 = bk3 * hikrate * 0.8;
    pslr = 1.0;

    if(key == 12 && k >= psly) {
      if(pslsi == 1 && pszd.AT(0, 0) > 1.0e-6) {
        pslr = min(1.0, zd.AT(0, 0) / pszd.AT(0, 0));
      } else {
        pslr = 0.0;
      }
    }
  }
  

  else if(ii == 17) {
    tz.AT(1) = zem.AT(0, 0) - zem.AT(0, 2) - zem.AT(0, 3) - zem.AT(0, 4);
    tz.AT(2) = zem.AT(0, 2) + zem.AT(0, 3) + zem.AT(0, 4);
    bk  = wem.AT(0) * pro + wem2.AT(0) * pros;
    bk2 = wem.AT(2) * pro + wem2.AT(2) * pros;
    bk3 = wem.AT(3) * pro + wem2.AT(3) * pros;
    bk  = bk * hikrate;
    bk3 = bk3 * hikrate * 0.8;
    pslr = 1.0;

    if(key == 12 && k >= psly) {
      if(pslsi == 1 && pszem.AT(0, 0) > 1.0e-6) {
        pslr = min(1.0, zem.AT(0, 0) / pszem.AT(0, 0));
      } else {
        pslr = 0.0;
      }
    }
  }
}