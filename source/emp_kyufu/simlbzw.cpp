#include "sepscommon.h" 
#include "sepslib.h"

void seps::simlbzw(int x, int t) {

  double bb0, bbnp0, bbpt0;
  double w0, we0;
  double chs, ch9, cht;
  double tmp, tmq;
  double bbdum, bbnpdum, bbptdum;
  double bb0dum, bbnp0dum, bbpt0dum, bndum, bnptdum;

  v1_t tm  = VEC(double, 4);
  v1_t z0  = VEC(double, 1);
  v1_t ze0 = VEC(double, 1);


  bb0 = bb.AT(x - 1, t - 1);
  if(pseid == 0 && s <= 2) {
    bbnp0 = bbnp.AT(x-1, t-1);
    bbpt0 = bbpt.AT(x-1, t-1);
  } else {
    bbnp0 = bb0;
  }

  if(pseid == 0 && s <= 2) {
    if(g.AT(x, t)-gpt.AT(x, t) > 1.0e-6) {
      if(x != 15) {
        double numer = bn.AT(k, x, s) * ad.AT(k) * (gn.AT(x, t) - gnpt.AT(x, t))
                       + bbnp0 * br.AT(k, x, s) / br.AT(k-1, x-1, s) * (1.0 + h.AT(k)) * (gz.AT(x, t) - gzpt.AT(x, t));
        double denom = g.AT(x, t) - gpt.AT(x, t);
        bbnp.AT(x, t) = numer / denom;
      } else {
        bbnp.AT(x, t) = bn.AT(k, x, s) * ad.AT(k);
      }
    } else {
      bbnp.AT(x, t) = 0.0;
    }
    if(gpt.AT(x, t) > 1.0e-6) {
      if(x != 15) {
        bbpt.AT(x, t) = (
            bnpt.AT(k, x, s) * ad.AT(k) * gnpt.AT(x, t)
            + bbpt0 * (1.0 + h.AT(k)) * gzpt.AT(x, t)
            ) / gpt.AT(x, t);
      } else {
        bbpt.AT(x, t) = bnpt.AT(k, x, s) * ad.AT(k);
      }
    } else {
      bbpt.AT(x, t) = 0.0;
    }

    if(x == xend) {
      bbnp.AT(x, t) = bbnp0 * br.AT(k, x, s) / br.AT(k-1, x-1, s) * (1.0 + h.AT(k));
      bbpt.AT(x, t) = bbpt0 * (1.0 + h.AT(k));
    }
	
    if(g.AT(x, t) > 1.0e-6) {
      bb.AT(x, t) = (
          bbnp.AT(x, t) * (g.AT(x, t) - gpt.AT(x, t))
          + bbpt.AT(x, t) * gpt.AT(x, t)
          ) / g.AT(x, t);
    } else {
      bb.AT(x, t) = 0.0;
    }
  
  } else {
    if(g.AT(x, t) > 1.0e-6) {
      if(x != 15) {
        bb.AT(x, t) = (
            bn.AT(k, x, s) * ad.AT(k) * gn.AT(x, t)
            + bb0 * br.AT(k, x, s) / br.AT(k-1, x-1, s) * (1.0 + h.AT(k)) * gz.AT(x, t)
            ) / g.AT(x, t);
      } else {
        bb.AT(x, t) = bn.AT(k, x, s) * ad.AT(k);
      }
    } else {
      bb.AT(x, t) = 0.0;
    }
    if(x == xend) {
      bb.AT(x, t) = bb0 * br.AT(k, x, s) / br.AT(k-1, x-1, s) * (1.0 + h.AT(k));
    }
  }


  int dx = 60;
  int kx_74 = max(k - x, -74);

  if(flg_sigo >= 1) {
    dx = 20 + max((int)round(can.AT(C19(kx_74))), 40);
  }

  int hihonen = 70;

  FOR(j, 0, 6) FOR(i, 0, 1) {
    z0.AT(i)= z.AT(x-1, t-1, i, j);
    if(t == tend-1 && z0.AT(i) <= 1.0e-6) z0.AT(i) = z.AT(x-1, t, i, j);
    ze0.AT(i) = ze.AT(x-1, t, i, j);
    
    tm.AT(1) = gn .AT(x, t) * ze0.AT(i) + gz.AT(x, t)   * z0.AT(i);
    tm.AT(2) = gez.AT(x, t) * ze0.AT(i) + y.AT(x, t, 1) * z0.AT(i);

    if(key == 12 && k >= psly) {
      z0.AT(i) = psz.AT(x-1, t-1, i, j);
      if(t == tend-1 && z0.AT(i) <= 1.0e-6) z0.AT(i) = psz.AT(x-1, t, i, j);

      ze0.AT(i) = psze.AT(x-1, t, i, j);

      tm.AT(3) = gn .AT(x, t) * ze0.AT(i) + gz.AT(x, t)   * z0.AT(i);
      tm.AT(4) = gez.AT(x, t) * ze0.AT(i) + y.AT(x, t, 1) * z0.AT(i);
    }

    if(x <= hihonen &&
        (j == 0 || j == 4 || 
         (s == 1  && x >= 40 && j == 5) || 
         (s >= 2  && x >= 35 && j == 5) || 
         (x >= 20 && x <= dx && j == 6))
    ) {

      if(i == 0 || (s == 3 && i == 1)) {
        if((s == 1 && x == 40  && j == 5)     || 
           (s >= 2 && x == 35  && j == 5)     || 
           ((x == 20 || x == dx) &&  j == 6)  || 
           x == hihonen                         ) {
          tm.AT(0) = gz.AT(x, t) / 2.0 + gn.AT(x, t) / 2.0;
        } else {
          tm.AT(0) = gz.AT(x, t)       + gn.AT(x, t) / 2.0;
        }
        if(key == 12
           && k >= psly) {
          tm.AT(3) += tm.AT(0);
        } else {
          tm.AT(1) += tm.AT(0);
        }
        
        if((s == 1 && x == 40 && j == 5) || 
           (s >= 2 && x == 35 && j == 5) || 
           (          x == 20 && j == 6)   ) {
          tm.AT(0) = 0.0;
        } else {
          tm.AT(0) = y.AT(x, t, 1) / 2.0;
        }
        if(key == 12
           && k >= psly) {
          tm.AT(4) += tm.AT(0);
        } else {
          tm.AT(2) += tm.AT(0);
        }
      }
    }

    z .AT(x, t, i, j) = 0.0;
    ze.AT(x, t, i, j) = 0.0;
	
    if(g .AT(x, t) > 1.0e-6) z .AT(x, t, i, j) = tm.AT(1) / g .AT(x, t);
    if(ge.AT(x, t) > 1.0e-6) ze.AT(x, t, i, j) = tm.AT(2) / ge.AT(x, t);
    if(key == 12
       && k >= psly) {
      psz .AT(x, t, i, j) = 0.0;
      psze.AT(x, t, i, j) = 0.0;
      if(g .AT(x, t) > 1.0e-6) psz .AT(x, t, i, j) = tm.AT(3) / g .AT(x, t);
      if(ge.AT(x, t) > 1.0e-6) psze.AT(x, t, i, j) = tm.AT(4) / ge.AT(x, t);
    }
  }
  
  
  FOR(ii, 0, 3) {
    if(ii == 0) {
      if(x <= 67) {
        chs = 1.0 + hh.AT(k);
      } else {
        chs = 1.0 + ci.AT(k);
      }
      ch9 = 1.0 + h.AT(k);

      if(cht_flg == 1) {
        int kk=min(k, KE-3);
        cht=dir.AT(k)*(1.0+ci0.AT(kk-1+2))*(1.0+ci0.AT(kk-1+3));

        if(x <= 64) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+hh.AT(kk+3));
        } else if(x == 65) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+ci.AT(kk+3));
        } else if(x == 66) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+ci.AT(kk+2))/(1.0+ci.AT(kk+3));
        } else {
          cht=cht/(1.0+ci.AT(kk+1))/(1.0+ci.AT(kk+2))/(1.0+ci.AT(kk+3));
        }
      } 
    }
    else if(ii == 1) {
      chs=1.0;
      ch9=1.0+h.AT(k);
      cht=1.0;
    }
    else if(ii == 2) {
      chs=1.0+ci2.AT(k, max(x, 67));
      ch9=1.0+h.AT(k);

      if(cht_flg == 1) {
        cht=jz_shk.AT(k)*1.031*0.988;
        FOR(kk, 5, k) {
          cht=cht*(1.0+ci2.AT(kk, max(x-k+kk, 67)));
        }
      } 
    }
    else if(ii == 3) {
      chs=1.0+hh.AT(k);
      ch9=1.0+h.AT(k);
      if(cht_flg == 1) {
        int kk=min(k, KE - 3);
        cht=dir.AT(k)*(1.0+ci0.AT(kk-1+2))*(1.0+ci0.AT(kk-1+3))
                /(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+hh.AT(kk+3));
      } 
    }
    
    if(k-x >= -62) {
      cht=cht*0.998*0.991*0.995*0.999;
    } else {
      cht=cht*0.991*0.995*0.999;
    }
    
    if(houjou >= 1) {
      if(k == houjouyr) {
        if(s == 1 || s == 3){
          cht=cht*(1.0+(houjour1-1.0)*1.0/2.0);
        } else {
          cht=cht*(1.0+(houjour2-1.0)*1.0/2.0);
        }
      } else if(k > houjouyr) {
        if(s == 1 || s == 3){
          cht=cht*houjour1;
        } else {
          cht=cht*houjour2;
        }
      }
    }
	
    if(s == 2 && x >= 20 && x <= 49) {
      cht=cht*( 1.0 + jiiku.AT(k, x) );
    }
    
    chwd.AT(x, t, ii) =bb.AT(x, t) /2.0*cht;
    if(flg_hiho70 == 0 || k < hiho70yr) {
      if(pseid == 0) {
        if(x >= hihonen) {
          chwd.AT(x, t, ii)  =0.0;
        }
      }
    }

    w.AT(x, t, 0, 0, ii) =0.0;
    we.AT(x, t, 0, 0, ii)=0.0;

    FOR(j, 1, 4) {

      w0=w.AT(x-1, t-1, 0, j, ii);
      if(t == tend-1 && w0 <= 1.0e-6) w0=w.AT(x-1, t, 0, j, ii);
      we0=we.AT(x-1, t, 0, j, ii);

      tmp=gn.AT(x, t) *we0+gz.AT(x, t) *w0;
      tmq=gez.AT(x, t)*we0+y.AT(x, t, 1)*w0;
      tm.AT(1)=tmp*chs;
      tm.AT(2)=tmq*chs;


      bool j4_calc = true;
      if(j <= 3) j4_calc = false;
      if(key == 12 && k >= psly) j4_calc = false;
	
      if(j4_calc) {
        if(pseid == 0) {
          if(x >= hihonen) {
            bn.AT(k, x, s) = 0.0;
            if(s <= 2) {
              bnpt.AT(k, x, s) = 0.0;
            }
          }
        }
        
        if(pseid == 0 && s <= 2) {
          tm.AT(1)=tm.AT(1)+(bn.AT(k, x, s)*ad.AT(k)*(gn.AT(x, t)-gnpt.AT(x, t))
                      +bnpt.AT(k, x, s)*ad.AT(k)*gnpt.AT(x, t))/2.0*cht;
                      
          if(x > 15) {
            if(pseid == 0) {
              if(x >= hihonen) {
                bb.AT(x, t)   = 0.0;
                bbnp.AT(x, t) = 0.0;
                bbpt.AT(x, t) = 0.0;
                if(x >= hihonen+1) {
                  bbnp0 = 0.0;
                  bbpt0 = 0.0;
                }
              }
            }
            if(br.AT(k-1, x-1, s) > 1.0e-6){
	            tmp=bbnp0*(1.0+br.AT(k, x, s)/br.AT(k-1, x-1, s))*ch9/2.0
	                *(gz.AT(x, t)-gzpt.AT(x, t))
	                +bbpt0*ch9*gzpt.AT(x, t);
            }
            else{
            	tmp=(bbnp0*ch9+bbnp.AT(x, t))/2.0*(gz.AT(x, t)-gzpt.AT(x, t))
            		+(bbpt0*ch9+bbpt.AT(x, t))/2.0*gzpt.AT(x, t);
            }
            tmq=( bbnp0*ch9*(y.AT(x, t, 1)-ypt.AT(x, t, 1))
                  +bbpt0*ch9*ypt.AT(x, t, 1)           )/2.0;
            assert(!isnan(tmp));
            
            tm.AT(1)=tm.AT(1)+tmp*cht;
            tm.AT(2)=tm.AT(2)+tmq*cht;
            
          }
        }
        
        else {
          tm.AT(1)=tm.AT(1)+bn.AT(k, x, s)*ad.AT(k)/2.0*gn.AT(x, t)*cht;
          if(x > 15) {
            if(pseid == 0) {
              if(x >= hihonen) {
                bb.AT(x, t) = 0.0;
                if(x >= hihonen+1) {
                  bb0     = 0.0;
                }
              }
            }
            if(br.AT(k-1, x-1, s) > 1.0e-6){
            	tmp=bb0*(1.0+br.AT(k, x, s)/br.AT(k-1, x-1, s))*ch9/2.0*gz.AT(x, t);
            }else{
            	tmp=(bb0*ch9+bb.AT(x, t))/2.0*gz.AT(x, t);
            }
            tmq= bb0*ch9         /2.0*y.AT(x, t, 1);

            tm.AT(1)=tm.AT(1)+tmp*cht;
            tm.AT(2)=tm.AT(2)+tmq*cht;
            
          }
        }

      }

      w .AT(x, t, 0, j, ii) = 0.0;
      we.AT(x, t, 0, j, ii) = 0.0;

      if(g.AT(x, t)  > 1.0e-6) w.AT(x, t, 0, j, ii) =tm.AT(1)/g.AT(x, t);
      if(ge.AT(x, t) > 1.0e-6) we.AT(x, t, 0, j, ii)=tm.AT(2)/ge.AT(x, t);

      if(j <= 3) {
        w.AT(x, t, 0, 0, ii) =w.AT(x, t, 0, 0, ii) +w.AT(x, t, 0, j, ii);
        we.AT(x, t, 0, 0, ii)=we.AT(x, t, 0, 0, ii)+we.AT(x, t, 0, j, ii);
      }
    }
  }
}



void seps::simlbzw0(int x) {
  
  double chs, cht;
  double tmp, tmq;
  double bndum, bnptdum;

  v1_t tm = VEC(double, 4);
  v1_t ze0 = VEC(double, 1);


  if(g.AT(x, 0) > 1.0e-6) {
    if(pseid == 0 && s <= 2) {
	    	bb.AT(x, 0) = (bn.AT(k, x, s)*(g.AT(x, 0)-gpt.AT(x, 0))
	                    + bnpt.AT(k, x, s)*gpt.AT(x, 0))*ad.AT(k)/g.AT(x, 0);
	        bbnp.AT(x, 0)= bn.AT(k, x, s)*ad.AT(k);
	      	bbpt.AT(x, 0)= bnpt.AT(k, x, s)*ad.AT(k);

    } else {
      bb.AT(x, 0)=bn.AT(k, x, s)*ad.AT(k);
    }
  } else {
    bb.AT(x, 0)=0.0;
    bbpt.AT(x, 0)=0.0;
  }
  if(x == xend) {
    bb.AT(x, 0)=bn.AT(k, x, s)*ad.AT(k);
    if(s <= 2) {
      bbpt.AT(x, 0)=bnpt.AT(k, x, s)*ad.AT(k);
    }
  }

  int dx = 60;
  int kx_74 = max(k - x, -74);
  if(flg_sigo >= 1) {
    dx = 20 + max((int)round(can.AT(C19(kx_74))), 40);
  }

  int hihonen = 70;

  FOR(j, 0, 6) FOR(i, 0, 1) {
    ze0.AT(i)=ze.AT(x-1, 0, i, j);

    tm.AT(1)=gn.AT(x, 0) *ze0.AT(i);
    tm.AT(2)=gez.AT(x, 0)*ze0.AT(i);
    if(key == 12 && k >= psly) {
      ze0.AT(i)=psze.AT(x-1, 0, i, j);
      tm.AT(3)=gn.AT(x, 0) *ze0.AT(i);
      tm.AT(4)=gez.AT(x, 0)*ze0.AT(i);
    }
    if(x <= hihonen && (j == 0 || j == 4  || 
          (s == 1 && x >= 40 && j == 5)  || 
          (s >= 2 && x >= 35 && j == 5)  || 
          (x >= 20 && x <= dx && j == 6))   ) {
      tm.AT(0)=0.0;
      if(i == 0 || (s == 3 && i == 1)) {
        tm.AT(0)=(gnn.AT(x)+gn.AT(x, 0))/2.0;
      }
      if(key == 12 && k >= psly) {
        tm.AT(3)=tm.AT(3)+tm.AT(0);
      } else {
        tm.AT(1)=tm.AT(1)+tm.AT(0);
      }
    }

    z.AT(x, 0, i, j) =0.0;
    ze.AT(x, 0, i, j)=0.0;

    if(g.AT(x, 0)  > 1.0e-6) z.AT(x, 0, i, j) =tm.AT(1)/g.AT(x, 0);
    if(ge.AT(x, 0) > 1.0e-6) ze.AT(x, 0, i, j)=tm.AT(2)/ge.AT(x, 0);
    if(key == 12 && k >= psly) {
      psz.AT(x, 0, i, j) =0.0;
      psze.AT(x, 0, i, j)=0.0;

      if(g.AT(x, 0)  > 1.0e-6) psz.AT(x, 0, i, j) =tm.AT(3)/g.AT(x, 0);
      if(ge.AT(x, 0) > 1.0e-6) psze.AT(x, 0, i, j)=tm.AT(4)/ge.AT(x, 0);
    }
  }

  FOR(ii, 0, 3) {
    if(ii == 0) {
      if(x <= 67) {
        chs=1.0+hh.AT(k);
      } else {
        chs=1.0+ci.AT(k);
      }

      if(cht_flg == 1) {
        int kk=min(k, KE-3);
        cht=dir.AT(k)*(1.0+ci0.AT(kk-1+2))*(1.0+ci0.AT(kk-1+3));

        if(x <= 64) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+hh.AT(kk+3));
        } else if(x == 65) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+ci.AT(kk+3));
        } else if(x == 66) {
          cht=cht/(1.0+hh.AT(kk+1))/(1.0+ci.AT(kk+2))/(1.0+ci.AT(kk+3));
        } else {
          cht=cht/(1.0+ci.AT(kk+1))/(1.0+ci.AT(kk+2))/(1.0+ci.AT(kk+3));
        }

      } 

    } else if(ii == 1) {
      chs=1.0;
      cht=1.0;
    } else if(ii == 2) {
      chs=1.0+ci2.AT(k, max(x, 67));

      if(cht_flg == 1) {
        cht=jz_shk.AT(k)*1.031*0.988;
        FOR(kk, 5, k) {
          cht=cht*(1.0+ci2.AT(kk, max(x-k+kk, 67)));
        }
      }      
    } else if(ii == 3) {
      chs=1.0+hh.AT(k);
      if(cht_flg == 1) {
        int kk=min(k, KE-3);
        cht=dir.AT(k)*(1.0+ci0.AT(kk-1+2))*(1.0+ci0.AT(kk-1+3))
                /(1.0+hh.AT(kk+1))/(1.0+hh.AT(kk+2))/(1.0+hh.AT(kk+3));
      } 
    }
    if(k-x >= -62) {
      cht=cht*0.998*0.991*0.995*0.999;
    } else {
      cht=cht*0.991*0.995*0.999;
    }
    
    chwd.AT(x, 0, ii) =bb.AT(x, 0) /2.0*cht;
    if(flg_hiho70 == 0 || k < hiho70yr) {
      if(pseid == 0) {
        if(x >= hihonen) {
          chwd.AT(x, 0, ii)  =0.0;
        }
      }
    }

    if(houjou >= 1) {
      if(k == houjouyr) {
        if(s == 1 || s == 3){
          cht=cht*(1.0+(houjour1-1.0)*1.0/2.0);
        } else {
          cht=cht*(1.0+(houjour2-1.0)*1.0/2.0);
        }
      } else if(k > houjouyr) {
        if(s == 1 || s == 3){
          cht=cht*houjour1;
        } else {
          cht=cht*houjour2;
        }
      }
    }

    w.AT(x, 0, 0, 0, ii) =0.0;
    we.AT(x, 0, 0, 0, ii)=0.0;

    FOR(j, 1, 4) {

      tmp=gn.AT(x, 0) *we.AT(x-1, 0, 0, j, ii);
      tmq=gez.AT(x, 0)*we.AT(x-1, 0, 0, j, ii);

      tm.AT(1)=tmp*chs;
      tm.AT(2)=tmq*chs;

      bool j4_calc = true;
      if(j <= 3) j4_calc = false;

      if(key == 12 && k >= psly) j4_calc = false;
      
      if(j4_calc) {
        if(pseid == 0) {
          if(x >= hihonen) {
            bn.AT(k, x, s) = 0.0;
            if(s <= 2) {
              bnpt.AT(k, x, s) = 0.0;
            }
          }
        }

        if(pseid == 0 && s <= 2) {
          tm.AT(1)=tm.AT(1)
              +(bn.AT(k, x, s)*(g.AT(x, 0)-gpt.AT(x, 0))+bnpt.AT(k, x, s)*gpt.AT(x, 0))
                /2.0*ad.AT(k)*cht;
        } else {
          tm.AT(1)=tm.AT(1)+bn.AT(k, x, s)*ad.AT(k)/2.0*g.AT(x, 0)*cht;
        }
        
      }


      w.AT(x, 0, 0, j, ii) =0.0;
      we.AT(x, 0, 0, j, ii)=0.0;

      if(g.AT(x, 0)  > 1.0e-6) w.AT(x, 0, 0, j, ii) =tm.AT(1)/g.AT(x, 0);
      if(ge.AT(x, 0) > 1.0e-6) we.AT(x, 0, 0, j, ii)=tm.AT(2)/ge.AT(x, 0);

      if(j <= 3) {
        w.AT(x, 0, 0, 0, ii) =w.AT(x, 0, 0, 0, ii) +w.AT(x, 0, 0, j, ii);
        we.AT(x, 0, 0, 0, ii)=we.AT(x, 0, 0, 0, ii)+we.AT(x, 0, 0, j, ii);
      }

    }
  }
}
