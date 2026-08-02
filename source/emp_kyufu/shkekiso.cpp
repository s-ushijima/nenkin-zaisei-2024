#include "sepscommon.h"

void seps::shkekiso(void) {

  double tmq, gv, gvr, gvk, gvkk;

  FOR(x, 0, 115) {
    xrb = 0;
    seps::sknr(k, x, xxr, xrb);
    xxr = max(60, xxr);
    xrb = max(60, xrb);

    FOR(i, 1, 13) {
      int ss;
      if(i <= 10) {
        if(s2 == 2) {
          ss = 2;
        } else {
          ss = 1;
        }
      } else {
        if(s2 == 2) {
          ss = 1;
        } else {
          ss = 2;
        }
      }

      FOR(xx, 0, 15) {

        tmq = 0.0;
        
        FOR(j, 1, 4) {
        	if(flg_toukei == 0){ 
	          	if(i == 9 || i == 11){
	          		seps::siku(x, i, gv, gvr, gvk, gvkk);
		          	tmq = t4k.AT(x, xx, i) * gvk;
	          	} else if(i == 10){
		          	seps::siku(x, i, gv, gvr, gvk, gvkk);
		          	tmq = t4k.AT(x, xx, i) * gvkk;
	          	} else{
	          		tmq = t4.AT(x, xx, i);
	          	}	          
          }
          if(tmq <= 1.0e-30) tmq = 0.0;
          if(j == 1) {
            if(x < 65) tmq = 0.0;
          } else if(j >= 2) {
            
            if(i <= 4) {
              if(x < 65-xx) tmq = 0.0;
            } else if(i <= 8) {
              if(x < 65) tmq = 0.0;
            } else if(i <= 10) {
            	if(i == 9){
            		tmq = tmq * (cl.AT(k, 1) + cl.AT(k, 2));
            	}else{
            		tmq = tmq * (cl2.AT(k, 1) + cl2.AT(k, 2));
            	} 
             } else {
            	if(x >= 19) {
            		tmq = tmq * rc.AT(s, k, x);
                }
            }
            if(j == 3 && x >= 65) tmq = 0.0;
            if(j == 4 && x < 65)  tmq = 0.0;
          }
          okisor.AT(k, ss, i, j) += tmq;
        }

        if(i <= 4) {
          okiso2x.AT(k, x, ss, 1, 1) += t6.AT(x, xx, i, 14);
          okiso2x.AT(k, x, ss, 1, 3) += t6.AT(x, xx, i,  6);
          okiso2x.AT(k, x, ss, 1, 5) += t6.AT(x, xx, i, 19);
          dk3x.AT(k, x, ss, 1, 0) += t6.AT(x, xx, i,  6)
                                     + t6.AT(x, xx, i, 14);
          dk3x.AT(k, x, ss, 2, 0) += t6.AT(x, xx, i, 15)
                                     + t6.AT(x, xx, i, 16) * 3.0 / 4.0
                                     + t6.AT(x, xx, i, 19);
        }
        else if(xx == 0) {
          if(i <= 8) {
            okiso2x.AT(k, x, ss, 1, 4) += t6.AT(x, xx, i, 15);
            okiso2x.AT(k, x, ss, 1, 5) += t6.AT(x, xx, i, 19);
            okiso2x.AT(k, x, ss, 1, 6) += t6.AT(x, xx, i, 16) * 3.0 / 4.0;
            dk3x.AT(k, x, ss, 2, 0) += t6.AT(x, xx, i, 15)
                                       + t6.AT(x, xx, i, 16) * 3.0 / 4.0
                                       + t6.AT(x, xx, i, 19);
          } else if(i == 9) {
            okiso2x.AT(k, x, ss, 2, 1) += t6.AT(x, xx, i, 14);
            okiso2x.AT(k, x, ss, 2, 2) += t6.AT(x, xx, i, 21);
            okiso2x.AT(k, x, ss, 2, 3) += t6.AT(x, xx, i,  6);
            okiso2x.AT(k, x, ss, 2, 5) += t6.AT(x, xx, i, 19);
            dk3x.AT(k, x, ss, 3, 0) += t6.AT(x, xx, i, 6)
                                       + t6.AT(x, xx, i, 14)
                                       + t6.AT(x, xx, i, 21);
            dk3x.AT(k, x, ss, 4, 0) += t6.AT(x, xx, i, 19);
          } else if(i == 10) {
            okiso2x.AT(k, x, ss, 2, 4) += t6.AT(x, xx, i, 17);
            okiso2x.AT(k, x, ss, 2, 5) += t6.AT(x, xx, i, 19)
                                          + t6.AT(x, xx, i, 20);
            dk3x.AT(k, x, ss, 4, 0) += t6.AT(x, xx, i, 17)
                                       + t6.AT(x, xx, i, 19)
                                       + t6.AT(x, xx, i, 20);
          } else if(i == 11) {
            okiso2x.AT(k, x, ss, 1, 5) += t6.AT(x, xx, i, 18);
            okiso2x.AT(k, x, ss, 3, 1) += t6.AT(x, xx, i, 14);
            okiso2x.AT(k, x, ss, 3, 2) += t6.AT(x, xx, i, 21);
            dk3x.AT(k, x, ss, 5, 0) += t6.AT(x, xx, i, 14)
                                       + t6.AT(x, xx, i, 21);
            dk3x.AT(k, x, ss, 2, 0) += t6.AT(x, xx, i, 18);
          } else if(i >= 12) {
            okiso2x.AT(k, x, ss, 1, 5) += t6.AT(x, xx, i, 18);
            okiso2x.AT(k, x, ss, 3, 4) += t6.AT(x, xx, i, 17);
            okiso2x.AT(k, x, ss, 3, 5) += t6.AT(x, xx, i, 20);
            dk3x.AT(k, x, ss, 6, 0) += t6.AT(x, xx, i, 17)
                                       + t6.AT(x, xx, i, 20);
            dk3x.AT(k, x, ss, 2, 0) += t6.AT(x, xx, i, 18);
          }
        }
      }
    }
  }

  int ss;
  if(s2 == 2) {
    ss = 2;
  } else {
    ss = 1;
  }

  FOR(j, 1, 4) {
    okisor.AT(k, ss, 1, j) += okisor.AT(k, ss, 2, j);
    okisor.AT(k, ss, 3, j) += okisor.AT(k, ss, 4, j);
    okisor.AT(k, ss, 5, j) += okisor.AT(k, ss, 6, j);
    okisor.AT(k, ss, 7, j) += okisor.AT(k, ss, 8, j);
    okisor.AT(k, ss, 2, j) = 0.0;
    okisor.AT(k, ss, 4, j) = 0.0;
    okisor.AT(k, ss, 6, j) = 0.0;
    okisor.AT(k, ss, 8, j) = 0.0;
  }
}