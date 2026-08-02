#include "sepscommon.h"
#include "sepslib.h"

void seps::shkehiho(void) {
  double tmp, tmq, tmr, tms;


  FOR(x, 15, 85) {
    FOR(t, 0, 70) {

      gee  .AT(k, s2, x, t) = g  .AT(x, t);
      geept.AT(k, s2, x, t) = gpt.AT(x, t);

      if(x < 70) {
        ap   .AT(k, s2) += g.AT(x, t);
        apdum.AT(k, s2) += g.AT(x, t);
        if(pseid == 0 && s <= 2) {
          appart   .AT(k, s2) += gpt.AT(x, t);
          appartdum.AT(k, s2) += gpt.AT(x, t);
        }
      } else if(x >= 70) {
        if(xend > 70) {
          ap   .AT(k, s2) += g.AT(x, t);
          apdum.AT(k, s2) += g.AT(x, t);
          if(pseid == 0 && s <= 2) {
            appart   .AT(k, s2) += gpt.AT(x, t);
            appartdum.AT(k, s2) += gpt.AT(x, t);
          }
        }
      }


      if(x >= 65 && x <= 69) {
        ap65   .AT(k, s2) += g.AT(x, t);
        ap65dum.AT(k, s2) += g.AT(x, t);
        if(pseid == 0 && s <= 2) {
          appart65   .AT(k, s2) += gpt.AT(x, t);
          appart65dum.AT(k, s2) += gpt.AT(x, t);
        }
      }

      if(xend > 70 && x >= 70) {
        ap70   .AT(k, s2) += g.AT(x, t);
        ap70dum.AT(k, s2) += g.AT(x, t);
        if(pseid == 0 && s <= 2) {
          appart70   .AT(k, s2) += gpt.AT(x, t);
          appart70dum.AT(k, s2) += gpt.AT(x, t);
        }
      }

      if(xend > 75  &&  x >= 75) {
        ap75   .AT(k, s2) += g.AT(x, t);
        ap75dum.AT(k, s2) += g.AT(x, t);
        if(pseid == 0 && s <= 2) {
          appart75   .AT(k, s2) += gpt.AT(x, t);
          appart75dum.AT(k, s2) += gpt.AT(x, t);
        }
      }

      if(xend > 85 && x >= 85) {
        ap85   .AT(k, s2) += g.AT(x, t);
        ap85dum.AT(k, s2) += g.AT(x, t);
        if(pseid == 0 && s <= 2) {
          appart85   .AT(k, s2) += gpt.AT(x, t);
          appart85dum.AT(k, s2) += gpt.AT(x, t);
        }
      }


      tmp = 0.0;
      tmr = 0.0;
      if(x >= 20 && x <= 49) {
        tmp = g.AT(x, t) * bb.AT(x, t) * (1.0 - ikucoe.AT(k, x));
        tmr = g.AT(x, t) * bb.AT(x, t) * ikucoe.AT(k, x);
      } else if (flg_hiho70 == 0 && x < 70)
      {
        tmp = g.AT(x, t) * bb.AT(x, t);
      }
      if(x < 65) {
        a.AT(k, s2)    += tmp;
        adum.AT(k, s2) += tmp;
        aiku.AT(k, s2) += tmr;
        aikudum.AT(k, s2) += tmr;
      } else if(65 <= x && x < 70) {
        if(xend > 65) {
          a.AT(k, s2)    += tmp;
          adum.AT(k, s2) += tmp;
        }
      } else {
        if(xend > 70) {
          a.AT(k, s2)    += tmp;
          adum.AT(k, s2) += tmp;
        }
      }

      if(15 <= x && x <= 75) {
        ax.AT(k, x, s) += g.AT(x, t) * bb.AT(x, t) - gpt.AT(x, t) * bbpt.AT(x, t);
        gx.AT(k, x, s) += g.AT(x, t) - gpt.AT(x, t);
        if(x < 70) {
          ax.AT(k, 14, s) += g.AT(x, t) * bb.AT(x, t) - gpt.AT(x, t) * bbpt.AT(x, t);
          gx.AT(k, 14, s) += g.AT(x, t) - gpt.AT(x, t);
        }
        gtal.AT(k, x, s)   += g.AT(x, t);
        gztal.AT(k, x, s)  += gz.AT(x, t);
        gntal.AT(k, x, s)  += gn.AT(x, t);
        getal.AT(k, x, s)  += ge.AT(x, t);
      }

      if(x < 70) {
        if(x >= 60) {
          a60   .AT(k, s2) += tmp;
          a60dum.AT(k, s2) += tmp;
        }
        if(x >= 65) {
          a65   .AT(k, s2) += tmp;
          a65dum.AT(k, s2) += tmp;
        }
      } else if(x >= 70 && xend > 70) {
        a60   .AT(k, s2) += tmp;
        a65   .AT(k, s2) += tmp;
        a70   .AT(k, s2) += tmp;
        a60dum.AT(k, s2) += tmp;
        a65dum.AT(k, s2) += tmp;
        a70dum.AT(k, s2) += tmp;
        if(x >= 75 && xend > 75) {
          a75   .AT(k, s2) += tmp;
          a75dum.AT(k, s2) += tmp;
        }
        if(x >= 85 && xend > 85) {
          a85   .AT(k, s2) += tmp;
          a85dum.AT(k, s2) += tmp;
        }
      }
    }

    if(pseid == 0 && s <= 2 && (k == partyr3 - 1 || k == partyr3)){
      
      tmq = dmpt2.AT(k, x, s) * ad.AT(k);
      if(x >= 20 && x <= 49) {
        tmp = lpt1.AT(k, s, x) * tmq * (1.0 - ikucoe.AT(k, x));
        tmr = lpt1.AT(k, s, x) * tmq * ikucoe.AT(k, x);
      } else {
        tmp = lpt1.AT(k, s, x) * tmq;
        tmr = 0.0;
      }
      apart   .AT(k, s) += tmp;
      aikupart.AT(k, s) += tmr;
      if(x >= 60) a60part.AT(k, s) += tmp;
      if(x >= 65) a65part.AT(k, s) += tmp;
      if(x >= 70) a70part.AT(k, s) += tmp;
      if(x >= 75) a75part.AT(k, s) += tmp;
      if(x >= 85) a85part.AT(k, s) += tmp;
	  
      if(k == partyr3) {
        adum   .AT(k, s2) -= tmp;
        aikudum.AT(k, s2) -= tmr;
        if(x >= 60) a60dum.AT(k, s) -= tmp;
        if(x >= 65) a65dum.AT(k, s) -= tmp;
        if(x >= 70) a70dum.AT(k, s) -= tmp;
        if(x >= 75) a75dum.AT(k, s) -= tmp;
        if(x >= 85) a85dum.AT(k, s) -= tmp;
      }
    } 
    
    if(flg_part >= 1 && pseid == 0 && s <= 2 && 
        (k == partyr4 - 1 || k == partyr4)) {
      
      tmq = dmpt2.AT(k, x, s) * ad.AT(k);
      if(x >= 20 && x <= 49) {
        tmp = (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x))
               * tmq * (1.0 - ikucoe.AT(k, x));
        tmr = (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x))
               * tmq * ikucoe.AT(k, x);
      } else {
        tmp = (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x)) * tmq;
        tmr = 0.0;
      }
      apart   .AT(k, s) += tmp;
      aikupart.AT(k, s) += tmr;
      if(x >= 60) a60part.AT(k, s) += tmp;
      if(x >= 65) a65part.AT(k, s) += tmp;
      if(x >= 70) a70part.AT(k, s) += tmp;
      if(x >= 75) a75part.AT(k, s) += tmp;
      if(x >= 85) a85part.AT(k, s) += tmp;
	  
      if(k == partyr4) {
        adum   .AT(k, s2) -= tmp;
        aikudum.AT(k, s2) -= tmr;
        if(x >= 60) a60dum.AT(k, s) -= tmp;
        if(x >= 65) a65dum.AT(k, s) -= tmp;
        if(x >= 70) a70dum.AT(k, s) -= tmp;
        if(x >= 75) a75dum.AT(k, s) -= tmp;
        if(x >= 85) a85dum.AT(k, s) -= tmp;
      }
    } 
    
    if(x <= 70){
    	FOR(t, 0, 70) {
		   g3.AT(k, s2, x, t)         = g.AT(x, t);
		   if(pseid == 0 && s2 <= 2){
			   gnp3.AT(k, s2, x, t)   = g.AT(x, t) - gpt.AT(x, t);
			   gpt3.AT(k, s2, x, t)   = gpt.AT(x, t);
		   }
		   bb3.AT(k, s2, x, t)   = bb.AT(x, t);
		   if(pseid == 0 && s2 <= 2){
			   bbnp3.AT(k, s2, x, t) = bbnp.AT(x, t);
			   bbpt3.AT(k, s2, x, t) = bbpt.AT(x, t);
		   }
	   }
	}    
    
    FOR(t, 0, 70) {
     
      g2.AT(k, s2, x, t)   = g.AT(x, t);
      ge2.AT(k, s2, x, t)  = ge.AT(x, t);
      gz2.AT(k, s2, x, t)  = gz.AT(x, t);
      gn2.AT(k, s2, x, t)  = gn.AT(x, t);
      gez2.AT(k, s2, x, t) = gez.AT(x, t);
      
      bb2.AT(k, s2, x, t) = bb.AT(x, t);
      z2.AT(k, s2, x, t)  = z.AT(x, t, 0, 4);
      ze2.AT(k, s2, x, t) = ze.AT(x, t, 0, 4);
      w2.AT(k, s2, x, t)  = w.AT(x, t, 0, 4, 0);
      we2.AT(k, s2, x, t) = we.AT(x, t, 0, 4, 0);
      
    }
    
  }
}