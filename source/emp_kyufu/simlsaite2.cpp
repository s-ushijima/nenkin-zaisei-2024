#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <cassert>
namespace sst = sepsstd;
namespace csv = csvio;

void seps::saitezai(int x, int t) {

  double bk, bk2, bk3; 
  double tmg, tmf, tmo, tmgp, tmgd;
  double tmris, tmris2;
  double tmrps, tml;
  double taizai;
  
  v1_t   ris = VEC(double, 15);
  v1_t   tmrp = VEC(double, 15);

  tmo = z.AT(x, t, 0, 0);
  seps::dsitk(x, t, 2, bk, bk2, bk3);

  int i = 0;
  if( ((x == xr && x < 65)  || 
      (x > xr && x < 65 && x <= xrb && xrb > 60))
      && it != 3 && it != 4                             ) i=2;
  if((((x == xr && x < 65)  || 
      (x > xr && x < 65 && x <= xrb && xrb > 60))
      && (it == 3 || it == 4) && 1.0-1.0e-6 <= tmo )  || 
    (x > xrb && x < 65  && 
      1.0-1.0e-6 <= tmo && tmo < 2.0-1.0e-6          )) i=4;

  if(i == 2 || i == 4) {

    ris.AT(0)=1.0;
    FOR(xx, 1, 15) {
      ris.AT(xx)=0.0;
    }

    if(xr >= 60) {
      FOR(xx, 1, 5) {
        if(xxr > 65-xx) {
          ris.AT(xx)=riss.AT(k, 65-xx, xxr, s, 1);
        } else {
          ris.AT(xx)=0.0;
        }
      }
      FOR(xx, 1, 5) {
        ris.AT(0)=ris.AT(0)-ris.AT(xx);
      }
      tmris=0.0;
      FOR(xx, 0, 5) {
        if(65-xx >= x) {
          tmris=tmris+ris.AT(xx);
        } else {
          ris.AT(xx)=0.0;
        }
      }
      tmris2=0.0;
      FOR(xx, 0, 5) {
        if(tmris >= 1.0e-6) {
          ris.AT(xx)=ris.AT(xx)/tmris;
        } else {
          if(xx == 0) {
            ris.AT(xx)=1.0;
          } else {
            ris.AT(xx)=0.0;
          }
        }
        tmris2=tmris2+ris.AT(xx);
      }
      assert(tmris2-1.0 <= 1.0e-6);
    }
    
    if(k == KIJUN+1) {
      if(xrb > 60 && x > 60 && x <= xrb && t > 0) {
        FOR(xx, 0, 5) {
          tmgd=(r.AT(x-1, xx, 2)+r.AT(x-1, xx, 4))*(1.0-q2.AT(k, x))*g.AT(x, t)/l.AT(k, s, x);
          if(xrb > 60 && x < xrb) {
            gd.AT(x, t)=gd.AT(x, t)+tmgd;
          } else {
            gd.AT(x, t)=0.0;
          }
        }
      } else {
        gd.AT(x, t)=0.0;
      }
    } else {
      if(xrb > 60 && x > 60 && x <= xrb && t > 0) {
        gd.AT(x, t)=gd.AT(x-1, t-1)*(1.0-q2.AT(k, x));
      } else {
        gd.AT(x, t)=0.0;
      }
    }

    FOR(xx, 0, 5) {
      if(x < 60 && xx >= 1) continue;
      tmg=ris.AT(xx)*(g.AT(x, t)-gd.AT(x, t));
      if(xrb > 60 && x < xrb && x != 65-xx) tmg=0.0;

      if(xrb > 60 && x < xrb) {
        gd.AT(x, t)=gd.AT(x, t)+tmg;
      }

      rn.AT(x, xx, i)=rn.AT(x, xx, i)+tmg;
      hnn.AT(x, xx, i, 1)=hnn.AT(x, xx, i, 1)+tmg*tz.AT(1);
      hnn.AT(x, xx, i, 2)=hnn.AT(x, xx, i, 2)+tmg*tz.AT(2);
      pshnn.AT(x, xx, i)=pshnn.AT(x, xx, i)+tmg*pslr;

      fn.AT(x, xx, i, 1)=fn.AT(x, xx, i, 1)+tmg*bk;
      fnhik.AT(x, xx, i, 1)=fnhik.AT(x, xx, i, 1)+tmg*bk2;
      fnmin.AT(x, xx, i, 1)=fnmin.AT(x, xx, i, 1)+tmg*bk3;

      tmf=tmg*fl*flt.AT(C19(max(-74, k-x)))*bd.AT(k, 2)*tn;
      fn.AT(x, xx, i, 2)=fn.AT(x, xx, i, 2)+tmf;
      tmo=tmg*fl1*bd.AT(k, 14)*min(ta/can.AT(C19(max(-74, k-x))), 1.0);
      if(flg_sigo >= 1) {
        tmo=tmo*max(can.AT(C19(max(-74, k-x))), 40.0) / 40.0;
      }
      fn.AT(x, xx, i, 14)=fn.AT(x, xx, i, 14)+tmo;

      bool do_calc = true;
      if((key == 12 || key == 13)
        && pslsi2 == 1 && k >= psly)          do_calc = false;

      if(s >= 4)                              do_calc = false;

      if(do_calc) {
        if(i == 2 || i == 4 ) {
          fn.AT(x, xx, i, 4) =fn.AT(x, xx, i, 4) +tmg*adt.AT(1)*bd.AT(k, 4)*pslr;
          fn.AT(x, xx, i, 23)=fn.AT(x, xx, i, 23)
                        +tmg*sadt.AT(C19(max(-74, k-x)))*bd.AT(k, 23)*pslr;
          fn.AT(x, xx, i, 5) =fn.AT(x, xx, i, 5) +tmg*adt.AT(2)*bd.AT(k, 5)*pslr;
          fn.AT(x, xx, i, 6)=fn.AT(x, xx, i, 6)
                        +tmg*cadt.AT(C19(k-(int)round(ns.AT(k, x))))*bd.AT(k, 6)*pslr;
        }
      }
    }
  }

  taizai = 0;
  if( (xend > 65 && x == 65)  || (xend > 70 && x == 70)  || 
      (xend > 75 && x == 75 && flg_hiho70 == 1  && k >= hiho70yr) || 
      (xend > 85 && x == 85 && flg_hiho70 == 2  && k >= hiho70yr)  ) {
    taizai = 1;
  }
   else if( (xend > 66 && x == 66)  || (xend > 67 && x == 67)  || 
             (xend > 68 && x == 68)  || (xend > 69 && x == 69)   ) {
    taizai = 2;
  }

  if(taizai == 1 || taizai == 2) {
    if(it == 1 || it == 2) i=2;
    if(it == 3 || it == 4) i=4;

    if(pseid == 0 && s <= 2) {
      tml=l.AT(k, s, x)+lpt.AT(k, s, x);
    } else {
      tml=l.AT(k, s, x);
    }
    tmrps=0.0;
    FOR(xx, 0, 15) {
      tmrp.AT(xx)=(r.AT(x-1, xx, 2)+r.AT(x-1, xx, 4)+r.AT(x-1, xx, 6)+r.AT(x-1, xx, 8))
              *(1.0-q2.AT(k, x));
      tmrps=tmrps+tmrp.AT(xx);
    }

    if(taizai == 1 || taizai == 2) {
      ris.AT(0)=1.0;
      FOR(xx, 1, 10) {
        if(tml > 1.0e-6 && tml >= tmrps) {
          ris.AT(xx)=tmrp.AT(xx)/tml;
        } else {
          if(tmrps > 1.0e-6) {
            ris.AT(xx)=tmrp.AT(xx)/tmrps;
          } else {
            ris.AT(xx)=0.0;
          }
        }
        ris.AT(0)=ris.AT(0)-ris.AT(xx);
      }
      assert(ris.AT(0) >= 0.0);
    }
    

    FOR(xx, 0, 15) {
      tmg=ris.AT(xx)*g.AT(x, t);
      tmgp=0.0;     
      if(s <= 2 && pseid == 0){
	      if(k >= partyr3 && x-k > xrb-partyr3) {
	        if(lpt.AT(k, s, x) > 1.0e-6) {
	          tmgp += ris.AT(xx)*gpt.AT(x, t)*lpt1.AT(k, s, x)/lpt.AT(k, s, x)*rt.AT(partyr3, xrb);
	        }
	      }
	      if(flg_part >= 1 && k >= partyr4 && x-k > xrb-partyr4) {
	        if(lpt.AT(k, s, x) > 1.0e-6) {
	          tmgp += ris.AT(xx)*gpt.AT(x, t)
	                   *(lpt2.AT(k, s, x)+lpt3.AT(k, s, x)+lpt4.AT(k, s, x))/lpt.AT(k, s, x)
	                   *rt.AT(partyr4, xrb);
	        }
	      }
	  }
      
      rn.AT(x, xx, i)=rn.AT(x, xx, i)+tmg;
      hnn.AT(x, xx, i, 1)=hnn.AT(x, xx, i, 1)+tmg*tz.AT(1);
      hnn.AT(x, xx, i, 2)=hnn.AT(x, xx, i, 2)+tmg*tz.AT(2);
      pshnn.AT(x, xx, i)=pshnn.AT(x, xx, i)+tmg*pslr;

      fn.AT(x, xx, i, 1)=fn.AT(x, xx, i, 1)+tmg*bk;
      fnhik.AT(x, xx, i, 1)=fnhik.AT(x, xx, i, 1)+tmg*bk2;
      fnmin.AT(x, xx, i, 1)=fnmin.AT(x, xx, i, 1)+tmg*bk3;

      tmf=tmg*fl*flt.AT(C19(max(-74, k-x)))*bd.AT(k, 2)*tn;
      fn.AT(x, xx, i, 2)=fn.AT(x, xx, i, 2)+tmf;
      tmo=tmg*fl1*bd.AT(k, 14)*min(ta/can.AT(C19(max(-74, k-x))), 1.0);
      if(flg_sigo >= 1) {
        tmo=tmo*max(can.AT(C19(max(-74, k-x))), 40.0)/40.0;
      }      
      fn.AT(x, xx, i, 14)=fn.AT(x, xx, i, 14)+tmo;
      
      tmf=max(tmf-tmo, 0.0);
      fn.AT(x, xx, i, 3)=fn.AT(x, xx, i, 3)+tmf;

      bool calc_flag = true;
      if((key == 12 || key == 13)
        && pslsi2 == 1 && k >= psly)           calc_flag = false;

      if(s >= 4)                               calc_flag = false;

      if(calc_flag) {
        if(i == 2  || i == 4) {
          fn.AT(x, xx, i, 4) =fn.AT(x, xx, i, 4)+(tmg-tmgp)*adt.AT(1)*bd.AT(k, 4)*pslr;
          fn.AT(x, xx, i, 23)=fn.AT(x, xx, i, 23)
                      +(tmg-tmgp)*sadt.AT(C19(max(-74, k-x)))*bd.AT(k, 23)*pslr;
          fn.AT(x, xx, i, 5) =fn.AT(x, xx, i, 5)+(tmg-tmgp)*adt.AT(2)*bd.AT(k, 5)*pslr;
          fn.AT(x, xx, i, 6) =fn.AT(x, xx, i, 6)+(tmg-tmgp)
                               *cadt.AT(C19(k-(int)round(ns.AT(k, x))))*bd.AT(k, 6)*pslr;
        }
      }
    }
  }
}


void seps::saitetai(int x, int t) {

  double bk, bk2, bk3;
  double tmg, tmf, tmo;
  
  v1_t   tmg2 = VEC(double, 15);
  v1_t   ris  = VEC(double, 15);
  
  double tmris, tmris2;
  double ged;
  v1_t   tmrp = VEC(double, 15);
  double tmrps, tmlp;

  tmo=ze.AT(x, t, 0, 0);
  seps::dsitk(x, t, 1, bk, bk2, bk3);
  
  if(tmo >= senll-1.0e-6 && it != 2  && 
    x >= xrb && x < xxr && xxr > 60) {

    tmg=ge.AT(x, t);

    rsenn.AT(x)=rsenn.AT(x)+tmg;
    hnsenn.AT(x, 1)=hnsenn.AT(x, 1)+tmg*tz.AT(1);
    hnsenn.AT(x, 2)=hnsenn.AT(x, 2)+tmg*tz.AT(2);
    pshnsenn.AT(x)=pshnsenn.AT(x)+tmg*pslr;

    fsenn.AT(x, 1) =fsenn.AT(x, 1)+tmg*bk;
    fsennhik.AT(x, 1)=fsennhik.AT(x, 1)+tmg*bk2;
    fsennmin.AT(x, 1)=fsennmin.AT(x, 1)+tmg*bk3;

    tmf=tmg*fl*flt.AT(C19(max(-74, k-x)))*bd.AT(k, 2)*tn;
    fsenn.AT(x, 2) =fsenn.AT(x, 2)+tmf;
    tmo=tmg*fl1*bd.AT(k, 14)*min(ta/can.AT(C19(max(-74, k-x))), 1.0);
    if(flg_sigo >= 1) {
      tmo=tmo*max(can.AT(C19(max(-74, k-x))), 40.0)/40.0;
    }
    fsenn.AT(x, 14)=fsenn.AT(x, 14)+tmo;
    tmf=max(tmf-tmo, 0.0);
    fsenn.AT(x, 3) =fsenn.AT(x, 3)+tmf;

    bool calc_flag = true;
    if((key == 12 || key == 13)
      && pslsi2 == 1 && k >= psly) calc_flag = false;

    if(s >= 4)                     calc_flag = false;

    if(calc_flag) {
      fsenn.AT(x, 4) =fsenn.AT(x, 4) +tmg*adt.AT(1)*bd.AT(k, 4)*pslr;
      fsenn.AT(x, 23)=fsenn.AT(x, 23)+tmg*sadt.AT(C19(max(-74, k-x)))*bd.AT(k, 23)*pslr;
      fsenn.AT(x, 5) =fsenn.AT(x, 5) +tmg*adt.AT(2)*bd.AT(k, 5)*pslr;
      fsenn.AT(x, 6)=fsenn.AT(x, 6)
                  +tmg*cadt.AT(C19(k-(int)round(ns.AT(k, x))))*bd.AT(k, 6)*pslr;
    }

    ge.AT(x, t)=0.0;
    sst::subc4(ze, x,x, t,t, 0,1, 0,9);
    sst::subc5(we, x,x, t,t, 0,0, 0,7, 0,3);

  } else if(x >= xr) {

    int i;
    if(it == 1 || it == 2) i=1;
    if(it == 3 || it == 4) i=3;
    
    FOR(xx, 0, 15) {
      tmg2.AT(xx)=0.0;
      ris.AT(xx)=0.0;
    }

    if(y.AT(x, t, 1) > 1.0e-6) {
      if(pseid == 0 && s <= 2) {
        tmlp=l.AT(k-1, s, x-1)+lpt.AT(k-1, s, x-1);
      } else {
        tmlp=l.AT(k-1, s, x-1);
      }
      tmrps=0.0;
      FOR(xx, 0, 15) {
        tmrp.AT(xx)=r.AT(x-1, xx, 2)+r.AT(x-1, xx, 4)+r.AT(x-1, xx, 6)+r.AT(x-1, xx, 8);
        tmrps=tmrps+tmrp.AT(xx);
      }
	 
      ged=0.0;
      if(xr < 60 || tmlp <= 1.0e-6) {
        tmg2.AT(0)=y.AT(x, t, 1);
        ged=tmg2.AT(0);
      } else if(x > xrb) {
        if(tmrps >= tmlp) {
          FOR(xx, 0, 15) {
            ris.AT(xx)=tmrp.AT(xx)/tmrps;
            tmg2.AT(xx)=y.AT(x, t, 1)*ris.AT(xx);
          }
        } else {
          if(x > 65) {
            FOR(xx, 0, 15) {
              ris.AT(xx)=tmrp.AT(xx)/tmlp;
              tmg2.AT(xx)=y.AT(x, t, 1)*ris.AT(xx);
            }
            tmg2.AT(min(10, x-60))=tmg2.AT(min(10, x-60))
                              + y.AT(x, t, 1)*(tmlp-tmrps) / tmlp;
          } else {
            FOR(xx, 0, 15) {
              ris.AT(xx)=tmrp.AT(xx)/tmlp;
              tmg2.AT(xx)=y.AT(x, t, 1)*ris.AT(xx);
            }
            tmg2.AT(0)=tmg2.AT(0)+y.AT(x, t, 1)*(tmlp-tmrps)/tmlp;
          }
        }
        ged=0.0;
        FOR(xx, 0, 15) {
          ged=ged+tmg2.AT(xx);
        }
        assert(abs(ged-y.AT(x, t, 1)) <= 1.0e-6);

      } else if(x <= xrb && xrb > 60) {
        assert(tmrps-tmlp <= 1.0e-6);
        ris.AT(0)=1.0;
        tmris =1.0;
        FOR(xx, 1, 5) {
          if(65-xx < x) {
            ris.AT(xx)=tmrp.AT(xx)/tmlp;
            ris.AT(0)=ris.AT(0)-ris.AT(xx);
          } else {
            ris.AT(xx)=riss.AT(k, 65-xx, xxr, s, 0);
            tmris=tmris-ris.AT(xx);
          }
        }
        tmris2=ris.AT(0);
        ris.AT(0)=tmris;
        FOR(xx, 0, 65-x) {
          ris.AT(xx)=ris.AT(xx) * tmris2;
        }

        tmris=1.0;
        FOR(xx, 0, 15) {
          tmris=tmris-ris.AT(xx);
        }
        assert(abs(tmris) <= 1.0e-8);
        

        ged=0.0;
        FOR(xx, 1, 5) {
          if(65-xx < x) tmg2.AT(xx)=y.AT(x, t, 1)*ris.AT(xx);
          ged=ged+tmg2.AT(xx);
        }
        assert(y.AT(x, t, 1)-ged > -1.0e-8);
      }
	  

      ge.AT(x, t)=ge.AT(x, t)-ged;
      if(ge.AT(x, t) < -1.0e-6) {
        std::cout << sst::format(
          "ºßÏ·Å¾¤ÓºÛÄê¥¨¥é¡¼£³(saiteitai) (x, t, y, ge) = (%d, %d, %lf, %lf)\n", 
          x,  t,  y.AT(x, t, 1), ge.AT(x, t));
      } else if(ge.AT(x, t) < 1.0e-6) {
        ge.AT(x, t)=0.0;
      }

      tmrps=0.0;
      FOR(xx, 0, 15) {
        tmrps = tmrps + tmg2.AT(xx);
      }
      assert(tmrps-ged > -1.0e-8);
    }

    ris.AT(0)=1.0;
    FOR(xx, 1, 15) {
      ris.AT(xx)=0.0;
    }
    
    if(x >= 60+k-KIJUN && x <= 69+k-KIJUN && x > 65) {
      FOR(xx, 0, 15) {
        ris.AT(xx)=0.0;
      }
      ris.AT(min(15, x-60))=1.0;
    } else if(xr == 60 && ((x >= xr && x <= xrb)  || 
                            (k == KIJUN+1 && x <= xxr)) ) {
      FOR(xx, 1, 5) {
        if(xx > 65-xxr) {
          ris.AT(xx)=riss.AT(k, 65-xx, xxr, s, 0);
        }
      }
      FOR(xx, 1, 5) {
        ris.AT(0)=ris.AT(0)-ris.AT(xx);
      }
      tmris=0.0;
      FOR(xx, 0, 5) {
        if(x <= 65-xx) {
          tmris=tmris+ris.AT(xx);
        } else {
          ris.AT(xx)=0.0;
        }
      }
      tmris2=0.0;
      FOR(xx, 0, 5) {
        if(tmris > 1.0e-6) {
          ris.AT(xx)=ris.AT(xx)/tmris;
        } else {
          if(xx == 0) {
            ris.AT(xx)=1.0;
          } else {
            ris.AT(xx)=0.0;
          }
        }
        tmris2=tmris2+ris.AT(xx);
      }
      assert(tmris2-1.0 <= 1.0e-6);
    }
    
    
	

    ged=0.0;
    FOR(xx, 0, 15) {
      if(x < 60 && xx >= 1) continue;
      if(x >= xrb || (x == 65-xx && xx <= 5)) {
        tmg=ris.AT(xx)*ge.AT(x, t);
        if( (((pseid == 0 && s == 1) || pseid != 0) && k-x <= KIJUN-63 && k-x >= KIJUN-69) ||
	         ((pseid == 0 && s != 1) && k-x <= KIJUN-62 && k-x >= KIJUN-69)    ){
	          tmg=tmg/max(1.0, (double)((k-x+54)-(k-KIJUN-1)));
	    } 
      } else {
        tmg=0.0;
      }
      ged=ged+tmg;
      tmg=tmg+tmg2.AT(xx);

      rn.AT(x, xx, i)=rn.AT(x, xx, i)+tmg;
      hnn.AT(x, xx, i, 1)=hnn.AT(x, xx, i, 1)+tmg*tz.AT(1);
      hnn.AT(x, xx, i, 2)=hnn.AT(x, xx, i, 2)+tmg*tz.AT(2);
      pshnn.AT(x, xx, i)=pshnn.AT(x, xx, i)+tmg*pslr;

      fn.AT(x, xx, i, 1)=fn.AT(x, xx, i, 1)+tmg*bk;
      fnhik.AT(x, xx, i, 1)=fnhik.AT(x, xx, i, 1)+tmg*bk2;
      fnmin.AT(x, xx, i, 1)=fnmin.AT(x, xx, i, 1)+tmg*bk3;

      tmf=tmg*fl*flt.AT(C19(max(-74, k-x)))*bd.AT(k, 2)*tn;
      fn.AT(x, xx, i, 2)=fn.AT(x, xx, i, 2)+tmf;
      tmo=tmg*fl1*bd.AT(k, 14)*min(ta/can.AT(C19(max(-74, k-x))), 1.0);
      if(flg_sigo >= 1) {
        tmo=tmo*max(can.AT(C19(max(-74, k-x))), 40.0)/40.0;
      }
      fn.AT(x, xx, i, 14)=fn.AT(x, xx, i, 14)+tmo;
      tmf=max(tmf-tmo, 0.0);
      fn.AT(x, xx, i, 3)=fn.AT(x, xx, i, 3)+tmf;

      bool calc_flag = true;
      if((key == 12 || key == 13)
        && pslsi2 == 1 && k >= psly) calc_flag = false;

      if(s >= 4)                     calc_flag = false;

      if(calc_flag) {
        if(i == 1 || i == 3) {
          fn.AT(x, xx, i, 4) =fn.AT(x, xx, i, 4)+tmg*adt.AT(1)*bd.AT(k, 4)*pslr;
          fn.AT(x, xx, i, 23)=fn.AT(x, xx, i, 23)
                      +tmg*sadt.AT(C19(max(-74, k-x)))*bd.AT(k, 23)*pslr;
          fn.AT(x, xx, i, 5) =fn.AT(x, xx, i, 5)+tmg*adt.AT(2)*bd.AT(k, 5)*pslr;
          fn.AT(x, xx, i, 6)=fn.AT(x, xx, i, 6)
                        +tmg*cadt.AT(C19(k-(int)round(ns.AT(k, x))))*bd.AT(k, 6)*pslr;
        }
      }
    }

    ge.AT(x, t)=ge.AT(x, t)-ged;
    if(abs(ge.AT(x, t)) < 1.0e-6) {
      ge.AT(x, t)=0.0;
      sst::subc4(ze, x,x, t,t, 0,1, 0,9);
      sst::subc5(we, x,x, t,t, 0,0, 0,7, 0,3);
    } else {
      assert(ge.AT(x, t) > -1.0e-6);
    }
  }
}
