#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <cassert>

void seps::simlg(const int x, const int xrb) {

  v1_t tm   = VEC(double, 4);
  v2_t gezz = VEC(double, 115, 100);
  double tmp, tmq, tmr1, tmr2, tmz, tmv;

  
  gz  .AT(x, 0) = 0.0;
  gzpt.AT(x, 0) = 0.0;
  FOR(t, 1, tend - 2) {
    if(pseid == 0){
    	gz.AT(x, t) = g.AT(x - 1, t - 1) * (1.0 - u.AT(k, x, 0));
    }else{
    	gz.AT(x, t) = g.AT(x - 1, t - 1) * exp(-u.AT(k, x, 0));
    }
    
    if(s <= 2 && pseid == 0) {
      gzpt.AT(x, t) = gpt.AT(x - 1, t - 1) * (1.0 - u.AT(k, x, 0));
      gz.AT(x, t) -= gzpt.AT(x, t);
    }
  }
  
  if(pseid == 0){
	  gz.AT(x, tend - 1) = (g.AT(x-1, tend - 2) + g.AT(x - 1, tend - 1))
    	                   * (1.0 - u.AT(k, x, 0));
  }else{
  	  gz.AT(x, tend - 1) = (g.AT(x-1, tend - 2) + g.AT(x - 1, tend - 1))
    	                   * exp(-u.AT(k, x, 0));
  }
  
  if(s <= 2 && pseid == 0) {
	gzpt.AT(x, tend - 1) = (gpt.AT(x - 1, tend - 2) + gpt.AT(x - 1, tend - 1))
	                       * (1.0 - u.AT(k, x, 0));
	gz.AT(x, tend - 1) -= gzpt.AT(x, tend - 1);
  }
  
  FOR(t, 0, tend - 1) {
    gezz.AT(x, t) = ge.AT(x - 1, t) * (1.0 - q.AT(k, x, 1));
    ye.AT(x, t)   = ge.AT(x - 1, t) - gezz.AT(x, t);
  }

  tmp = gezz.AT(x, 0);
  tmq = 0.0;
  tmv = 0.0;
  FOR(t, 1, tend - 1) {
    tmp += gezz.AT(x, t);
    tmq += gz.AT(x, t);
    tmv += gzpt.AT(x, t);
  }
  
  if(l.AT(k, s, x) < tmq) {
    FOR(t, 1, tend - 1) {
      if(tmq > 1.0e-6) {
        gz.AT(x, t) *= l.AT(k, s, x) / tmq;
      } else {
        gz.AT(x, t) = 0.0;
      }
    }
    tmq = l.AT(k, s, x);
  }
  
  if(k == partyr3 && s <= 2 && pseid == 0){
    if(lpt.AT(k, s, x) - lpt1.AT(k, s, x) < tmv) {
        FOR(t, 1, tend - 1) {
          if(tmv > 1.0e-6) {
            gzpt.AT(x, t) *= (lpt.AT(k, s, x) - lpt1.AT(k, s, x)) / tmv;
          } else {
            gzpt.AT(x, t) = 0.0;
          }
        }
        tmv = lpt.AT(k, s, x) - lpt1.AT(k, s, x);
    }
  }
   else if(flg_part >= 1 && k == partyr4 && s <= 2 && pseid == 0){
    if(lpt.AT(k, s, x) - lpt2.AT(k, s, x) - lpt3.AT(k, s, x) - lpt4.AT(k, s, x) < tmv) {
        FOR(t, 1, tend - 1) {
          if(tmv > 1.0e-6) {
            gzpt.AT(x, t) *= (lpt.AT(k, s, x) - lpt2.AT(k, s, x) 
                              - lpt3.AT(k, s, x) - lpt4.AT(k, s, x)) / tmv;
          } else {
            gzpt.AT(x, t) = 0.0;
          }
        }
        tmv = lpt.AT(k, s, x) - lpt2.AT(k, s, x) - lpt3.AT(k, s, x) - lpt4.AT(k, s, x);
    }
  }
   else if(s <= 2 && pseid == 0) {
    if(lpt.AT(k, s, x) < tmv) {
      FOR(t, 1, tend - 1) {
        if(tmv > 1.0e-6) {
          gzpt.AT(x, t) *= lpt.AT(k, s, x) / tmv;
        } else {
          gzpt.AT(x, t) = 0.0;
        }
      }
      tmv = lpt.AT(k, s, x);
    }
  }
  
  tmr2 = 0.0;
  if(s <= 2) {
    if(tmp + tmq + tmv < pop.AT(k, s, x)) {
      tmr1 = min(1.0,
                max(rt.AT(k, x), tmp / (pop.AT(k, s, x) - tmq - tmv))
             ) * (l.AT(k, s, x) - tmq);
      if(pseid == 0) {
      	if(k == partyr3){
          tmr2 = min(1.0,
                   max(rt.AT(k, x), tmp / (pop.AT(k, s, x) - tmq - tmv))
                 ) * (lpt.AT(k, s, x) - lpt1.AT(k, s, x) - tmv)
                 + rt.AT(k, x) * min(1.0, max(0.0, (x - 25) / 40.0)) * lpt1.AT(k, s, x);
        }
        else if(flg_part >= 1 && k == partyr4){
          tmr2 = min(1.0,
                   max(rt.AT(k, x), tmp / (pop.AT(k, s, x) - tmq - tmv))
                 ) * (lpt.AT(k, s, x) - lpt2.AT(k, s, x)  - lpt3.AT(k, s, x) - lpt4.AT(k, s, x) - tmv)
                 + rt.AT(k, x) * min(1.0, max(0.0, (x - 25) / 40.0))
                     * (lpt2.AT(k, s, x)  + lpt3.AT(k, s, x) + lpt4.AT(k, s, x));
        }
         else {
          tmr2 = min(1.0,
                   max(rt.AT(k, x), tmp / (pop.AT(k, s, x) - tmq - tmv))
                 ) * (lpt.AT(k, s, x) - tmv);
        }
      }
    } else {
      tmr1 = max(0.0, l.AT(k, s, x) - tmq);
      if(pseid == 0) {
        tmr2 = max(0.0, lpt.AT(k, s, x) - tmv);
      }
    }
  } else {
    tmr1 = rt.AT(k, x) * max(0.0, l.AT(k, s, x) - tmq);
  }
  
  FOR(t, 0, tend - 1) {
    if(x <= xrb && tmp > 1.0e-6) {
      if(s <= 2 && pseid == 0) {
        if(tmp >= tmr1 + tmr2) {
          gn.AT(x, t)   = gezz.AT(x, t) * tmr1 / tmp;
          gnpt.AT(x, t) = gezz.AT(x, t) * tmr2 / tmp;
        } else {
          if(tmr1 + tmr2 > 1.0e-6) {
            gn.AT(x, t)   = gezz.AT(x, t) * tmr1 / (tmr1 + tmr2);
            gnpt.AT(x, t) = gezz.AT(x, t) * tmr2 / (tmr1 + tmr2);
          } else {
            gn.AT(x, t)   = 0.0;
            gnpt.AT(x, t) = 0.0;
          }
        }
      } else {
        if(tmp >= tmr1) {
          gn.AT(x, t) = gezz.AT(x, t) * tmr1 / tmp;
        } else {
          gn.AT(x, t) = gezz.AT(x, t);
        }
        gnpt.AT(x, t) = 0.0;
      }
    } else {
      gn.AT(x, t)   = 0.0;
      gnpt.AT(x, t) = 0.0;
    }
    gez.AT(x, t) = max(0.0, gezz.AT(x, t) - gn.AT(x, t) - gnpt.AT(x, t));
  }
  
  gnn.AT(x) = l.AT(k, s, x) - gn.AT(x, 0);
  FOR(t, 1, tend - 1) {
    gnn.AT(x) -= gz.AT(x, t) + gn.AT(x, t);
  }
  if(abs(gnn.AT(x)) < 1.0e-6) {
    l.AT(k, s, x) -= gnn.AT(x);
    gnn.AT(x) = 0.0;
  } 

  assert(gnn.AT(x) > -1.0e-6);
  
  g.AT(x, tend - 1) = gz.AT(x, tend - 1) + gn.AT(x, tend - 1);
  
  if(s <= 2 && pseid == 0) {
    y.AT(x, tend - 1, 0) =
        g.AT(x - 1, tend - 2) + g.AT(x - 1, tend - 1)
        - gpt.AT(x - 1, tend - 2) - gpt.AT(x - 1, tend - 1) - gz.AT(x, tend - 1);
	tm.AT(0) =
	    g.AT(x - 1, tend - 2) + g.AT(x - 1, tend - 1)
	    - gpt.AT(x - 1, tend  -2) - gpt.AT(x - 1, tend - 1);
  }
  else {
    y.AT(x, tend-1, 0) =
        g.AT(x - 1, tend - 2) + g.AT(x - 1, tend - 1) - gz.AT(x, tend - 1);
    if(pseid == 0){
	    tm.AT(0) = g.AT(x - 1, tend - 2) + g.AT(x - 1, tend - 1);
	}
	else{
	    tm.AT(0) = (
	        g.AT(x - 1, tend - 2) + g.AT(x - 1, tend - 1) + gz.AT(x, tend - 1)
	        ) / 2.0;
	}
  }
  y.AT(x, tend - 1, 2) = tm.AT(0) * u.AT(k, x, 2);
  y.AT(x, tend - 1, 3) = tm.AT(0) * u.AT(k, x, 3);
  y.AT(x, tend - 1, 1) =   y.AT(x, tend - 1, 0)
                         - y.AT(x, tend - 1, 2)
                         - y.AT(x, tend - 1, 3);
  if(y.AT(x, tend - 1, 1) < -1.0e-12) {

	 assert(x > xrb && y.AT(x, tend - 1, 1) > -1.0e-2);
	
    y.AT(x, tend-1, 1) = 0.0;
    tmp = y.AT(x, tend - 1, 2) + y.AT(x, tend - 1, 3);
    if(tmp > 1.0e-12) {
      y.AT(x, tend - 1, 2) = y.AT(x, tend - 1, 0) * y.AT(x, tend - 1, 2) / tmp;
      y.AT(x, tend - 1, 3) = y.AT(x, tend - 1, 0) * y.AT(x, tend - 1, 3) / tmp;
    } else {
      y.AT(x, tend - 1, 0) = 0.0;
      y.AT(x, tend - 1, 2) = 0.0;
      y.AT(x, tend - 1, 3) = 0.0;
    }
  }
  ge.AT(x, tend - 1) = gez.AT(x, tend - 1) + y.AT(x, tend - 1, 1);
  
  REV_FOR(t, tend - 2, 1) {
    g.AT(x, t) = gz.AT(x, t) + gn.AT(x, t);
    if(s <= 2 && pseid == 0) {
      y.AT(x, t, 0) = g.AT(x - 1, t - 1) - gpt.AT(x - 1, t - 1) - gz.AT(x, t);
      tm.AT(0) = g.AT(x - 1, t - 1) - gpt.AT(x - 1, t - 1) ;
    }
    else {
      y.AT(x, t, 0) = g.AT(x - 1, t - 1) - gz.AT(x, t);
      if(pseid == 0){
	      tm.AT(0) = g.AT(x - 1, t - 1);
      }
      else{
          tm.AT(0) = (g.AT(x - 1, t - 1) + gz.AT(x, t)) / 2.0;
      }
    }
    y.AT(x, t, 2) = tm.AT(0) * u.AT(k, x, 2);
    y.AT(x, t, 3) = tm.AT(0) * u.AT(k, x, 3);
    y.AT(x, t, 1) = y.AT(x, t, 0) - y.AT(x, t, 2) - y.AT(x, t, 3);
    
    if(y.AT(x, t, 1) < -1.0e-12) {
      assert(x > xrb && y.AT(x, t, 1) > -1.0e-2);

      y.AT(x, t, 1) = 0.0;
      tmp = y.AT(x, t, 2) + y.AT(x, t, 3);
      if(tmp > 1.0e-12) {
        y.AT(x, t, 2) = y.AT(x, t, 0) * y.AT(x, t, 2) / tmp;
        y.AT(x, t, 3) = y.AT(x, t, 0) * y.AT(x, t, 3) / tmp;
      } else {
        y.AT(x, t, 0) = 0.0;
        y.AT(x, t, 2) = 0.0;
        y.AT(x, t, 3) = 0.0;
      }
    }
    ge.AT(x, t) = gez.AT(x, t) + y.AT(x, t, 1);
  }
  
  g.AT(x, 0)  = gn.AT(x, 0) + gnn.AT(x);
  ge.AT(x, 0) = gez.AT(x, 0);

  if(s <= 2 && pseid == 0) {

    gnnpt.AT(x) = lpt.AT(k, s, x) - gnpt.AT(x, 0);
    FOR(t, 1, tend - 1) {
      gnnpt.AT(x) -= gzpt.AT(x, t) + gnpt.AT(x, t);
    }
    if(abs(gnnpt.AT(x)) < 1.0e-6) {
      lpt.AT(k, s, x) = lpt.AT(k, s, x) - gnnpt.AT(x);
      gnnpt.AT(x) = 0.0;
    }
    assert(gnnpt.AT(x) > -1.0e-6);

    gpt.AT(x, tend - 1) = gzpt.AT(x, tend - 1) + gnpt.AT(x, tend - 1);
    ypt.AT(x, tend - 1, 0) = gpt.AT(x - 1, tend - 2) + gpt.AT(x - 1, tend - 1)
                             - gzpt.AT(x, tend - 1);
    tm.AT(0) = gpt.AT(x - 1, tend - 2) + gpt.AT(x - 1, tend - 1);
    ypt.AT(x, tend - 1, 2) = tm.AT(0) * u.AT(k, x, 2);
    ypt.AT(x, tend - 1, 3) = tm.AT(0) * u.AT(k, x, 3);
    ypt.AT(x, tend - 1, 1) = ypt.AT(x, tend - 1, 0)
                             - ypt.AT(x, tend - 1, 2)
                             - ypt.AT(x, tend - 1, 3);
                             
    if(ypt.AT(x, tend-1, 1) < -1.0e-12) {
      assert(x > xrb && ypt.AT(x, tend - 1, 1) >= -1.0e-2);

      ypt.AT(x, tend-1, 1) = 0.0;
      tmp = ypt.AT(x, tend - 1, 2) + ypt.AT(x, tend - 1, 3);
      if(tmp > 1.0e-12) {
        ypt.AT(x, tend - 1, 2) = ypt.AT(x, tend - 1, 0) * ypt.AT(x, tend - 1, 2) / tmp;
        ypt.AT(x, tend - 1, 3) = ypt.AT(x, tend - 1, 0) * ypt.AT(x, tend - 1, 3) / tmp;
      } else {
        ypt.AT(x, tend - 1, 0) = 0.0;
        ypt.AT(x, tend - 1, 2) = 0.0;
        ypt.AT(x, tend - 1, 3) = 0.0;
      }
    }

    REV_FOR(t, tend - 2, 1) {
      gpt.AT(x, t) = gzpt.AT(x, t) + gnpt.AT(x, t);
      ypt.AT(x, t, 0) = gpt.AT(x - 1, t - 1) - gzpt.AT(x, t);
      tm.AT(0) = gpt.AT(x - 1, t - 1);
      ypt.AT(x, t, 2) = tm.AT(0) * u.AT(k, x, 2);
      ypt.AT(x, t, 3) = tm.AT(0) * u.AT(k, x, 3);
      ypt.AT(x, t, 1) = ypt.AT(x, t, 0) - ypt.AT(x, t, 2) - ypt.AT(x, t, 3);
    
      if(ypt.AT(x, t, 1) < -1.0e-12) {
		
		assert(x > xrb && ypt.AT(x, t, 1)  >= -1.0e-2);
		ypt.AT(x, t, 1) = 0.0;
        tmp = ypt.AT(x, t, 2) + ypt.AT(x, t, 3);
        if(tmp > 1.0e-12) {
          ypt.AT(x, t, 2) = ypt.AT(x, t, 0) * ypt.AT(x, t, 2) / tmp;
          ypt.AT(x, t, 3) = ypt.AT(x, t, 0) * ypt.AT(x, t, 3) / tmp;
        } else {
          ypt.AT(x, t, 0) = 0.0;
          ypt.AT(x, t, 2) = 0.0;
          ypt.AT(x, t, 3) = 0.0;
        }
      }
    }
    gpt.AT(x, 0) = gnpt.AT(x, 0) + gnnpt.AT(x);
    
    FOR(t, 1, tend - 1) {
      g.AT(x, t)    += gpt.AT(x, t);
      y.AT(x, t, 0) += ypt.AT(x, t, 0);
      y.AT(x, t, 1) += ypt.AT(x, t, 1);
      y.AT(x, t, 2) += ypt.AT(x, t, 2);
      y.AT(x, t, 3) += ypt.AT(x, t, 3);
      ge.AT(x, t)   += ypt.AT(x, t, 1);

      gn.AT(x, t) += gnpt.AT(x, t);
      gz.AT(x, t) += gzpt.AT(x, t);
    }
    g.AT(x, 0)  += gpt.AT(x, 0);
    gn.AT(x, 0) += gnpt.AT(x, 0);
    gnn.AT(x)   += gnnpt.AT(x);
  }

  if(x >= 61) {
    tmz = gz.AT(x, 0);
    FOR(t, 1,tend - 1) {
      tmz += gz.AT(x, t);
    }

    if(pseid == 0 && s <= 2) {
      if(l.AT(k - 1, s, x - 1) + lpt.AT(k - 1, s, x - 1) > 1.0e-6) {
        q2.AT(k, x) = 1.0 - max(0.0, min(1.0,
            tmz / (l.AT(k - 1, s, x - 1) + lpt.AT(k - 1, s, x - 1))));
      } else {
        q2.AT(k, x) = 1.0;
      }
    } else {
      if(l.AT(k - 1, s, x - 1) > 1.0e-6) {
        q2.AT(k, x) = 1.0 - max(0.0, min(1.0, tmz / (l.AT(k - 1, s, x - 1))));
      } else {
        q2.AT(k, x) = 1.0;
      }
    }
  }
}