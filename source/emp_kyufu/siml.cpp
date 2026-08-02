#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
namespace sst = sepsstd;

void seps::siml(void) {
  FILE *fp = fp_map["prog"];

  double tmx, tmy, tmz, tmp, tmq, tmr, tms, tmp2, tmq2, tmr2, tms2, tmp3, tmq3, tmr3, tms3, tmp4;
  double rtemp, ftemp, rcoe, fcoe;
  int n;


  if(k == KIJUN + 1) {
    sst::subc3(y  , 14,115, 0,100, 0,3);
    sst::subc3(ypt, 14,115, 0,100, 0,3);

    sst::subc2(bbnp, 14,115, 0,100);
    FOR(x, 15, xend - 1) FOR(t, 0, tend - 2) {
      if(g.AT(x, t) - gpt.AT(x, t) > 1.0e-6) {
        bbnp.AT(x, t) = (bb.AT(x, t) * g.AT(x, t) - bbpt.AT(x, t) * gpt.AT(x, t))
                        / (g.AT(x, t) - gpt.AT(x, t));
      } else {
        bbnp.AT(x, t) = 0.0;
      }
    }

    sst::subc2(gzpt,  14,115, 0,100);
    sst::subc2(gnpt,  14,115, 0,100);
    sst::subc1(gnnpt, 4,115);
    sst::subc2(gd,    55,65,  0,100);
  }

  REV_FOR(x, xend, 15) {
    if(x < 70 + k-KIJUN || pseid != 0) { 
      seps::sknr(k, x, xxr, xrb);
      xrb = max(60, xrb);
      seps::simlg(x, xrb);
      #ifdef DEBUG
      fprintf(fp, "[siml:g] pseid = %d, s = %d, k = %d, x = %d\n", pseid, s, k, x);
      #endif
    }
    else {
      if(l.AT(k - 1, s, x - 1) > 1.0e-6) {
        q2.AT(k, x) = 1.0 - min(1.0, l.AT(k, s, x) / l.AT(k - 1, s, x - 1));
        if(q2.AT(k, x) < q.AT(k, x, 1)) {
          std::cout << sst::format(
                    "  [log] (q2[外枠] < q[生命表]) = (%lf < %lf); "
                    "(s, k, x) = (%d, %d, %d)\n",
                    q2.AT(k, x), q.AT(k, x, 1), s, k, x);
        }
      } else {
        q2.AT(k, x) = 1.0;
      }
    }
  }
  

  if((key == 13) && k >= psly) {
  } else {



    REV_FOR(x, xend, 15) {

      REV_FOR(t, tend - 1, 1) {
        #ifdef DEBUG
        fprintf(fp, "[siml:bzw] pseid = %d, s = %d, k = %d, x = %d, t = %d\n", pseid, s, k, x, t);
        #endif
        seps::simlbzw(x, t);
      }

      #ifdef DEBUG
      fprintf(fp, "[siml:bzw0] pseid = %d, s = %d, k = %d, x = %d\n", pseid, s, k, x);
      #endif
      seps::simlbzw0(x);
    }
  }

    sst::subc3(rn,    0,115, 0,15, 1,13);
    sst::subc4(fn,    0,115, 0,15, 1,13, 1,23);
    sst::subc4(fnhik, 0,115, 0,15, 1,13, 1,23);
    sst::subc4(fnmin, 0,115, 0,15, 1,13, 1,23);
    sst::subc4(hnn,   0,115, 0,15, 1,13, 1,2);
    sst::subc3(pshnn, 0,115, 0,15, 1,13);
    sst::subc1(rsenn,     60,70);
    sst::subc2(fsenn,     60,70, 1,23);
    sst::subc2(fsennhik,  60,70, 1,23);
    sst::subc2(fsennmin,  60,70, 1,23);
    sst::subc2(hnsenn,    60,70, 1,2);
    sst::subc1(pshnsenn,  60,70);
   
    
    bool calc_shinshoizo = true;
    if(key == 12) {
      if(k >= psly && (pslsi == 0 || pslsi == 2)) {
        calc_shinshoizo = false;
      }
    }
    else if (key == 13) {
      if(k >= psly) {
        calc_shinshoizo = false;
      }
    }

    if(calc_shinshoizo) {
    
      FOR(x, 15, xend) FOR(t, 0, tend - 1) {
        #ifdef DEBUG
        fprintf(fp, "[siml:saitesho] pseid = %d, s = %d, k = %d, x = %d, t = %d\n", pseid, s, k, x, t);
        #endif
        seps::saitesho(x, t);
      }
      FOR(x, 15, xend) FOR(t, 0, tend - 1) {
        #ifdef DEBUG
        fprintf(fp, "[siml:saitehiho] pseid = %d, s = %d, k = %d, x = %d, t = %d\n", pseid, s, k, x, t);
        #endif
        seps::saiteizohiho(x, t);
      }
    }

    if((key == 12 || key == 13)
       && k >= psly && pslsi == 2) {
    } else {
      
      FOR(x, 15, 115) {
        #ifdef DEBUG
        fprintf(fp, "[siml:saiteizojuk] pseid = %d, s = %d, k = %d, x = %d\n", pseid, s, k, x);
        #endif
        seps::saiteizojuk(x);
      }
    }

    if(key == 13 && k >= psly) {
    } else {
       
      REV_FOR(x, xend, 55) FOR(t, 0, tend - 1) {
        if (z.AT(x, t, 0, 0) < 1.0 - 1.0e-6 && x < 65) continue;
        #ifdef DEBUG
        fprintf(fp, "[siml:saitezai] pseid = %d, s = %d, k = %d, x = %d, t = %d\n", pseid, s, k, x, t);
        #endif
        seps::saitezai(x, t);
      }

      
      FOR(x, 55, xend) {
        FOR(t, 0, tend - 1) {
          if(ze.AT(x, t, 0, 0) < 1.0 - 1.0e-6 && x < 65) continue;
          #ifdef DEBUG
          fprintf(fp, "[siml:saitetai] pseid = %d, s = %d, k = %d, x = %d, t = %d\n", pseid, s, k, x, t);
          #endif
          seps::saitetai(x, t);
        }
        FOR(xx, 0, 15) FOR(i, 1, 4) {
          if(k-x <= -75 && rn.AT(x, xx, i) > 1.0e-6) {
            rn    .AT(x, xx, i + 4)     = rn    .AT(x, xx, i);
            hnn   .AT(x, xx, i + 4, 1)  = hnn   .AT(x, xx, i, 1);
            hnn   .AT(x, xx, i + 4, 2)  = hnn   .AT(x, xx, i, 2);
            pshnn .AT(x, xx, i + 4)     = pshnn .AT(x, xx, i);
            rn    .AT(x, xx, i)         = 0.0;
            hnn   .AT(x, xx, i, 1)      = 0.0;
            hnn   .AT(x, xx, i, 2)      = 0.0;
            pshnn .AT(x, xx, i)         = 0.0;
            FOR(j, 1, 23) {
              fn.AT(x, xx, i + 4, j) = fn.AT(x, xx, i, j);
              fn.AT(x, xx,     i, j) = 0.0;
              if(j == 1 || j == 10 || j == 13 || j == 22) {
                fnhik.AT(x, xx, i + 4, j) = fnhik.AT(x, xx, i, j);
                fnmin.AT(x, xx, i + 4, j) = fnmin.AT(x, xx, i, j);
                fnhik.AT(x, xx,     i, j) = 0.0;
                fnmin.AT(x, xx,     i, j) = 0.0;
              }
            }
           
          }
        }
      }
    } 
    
    FOR(i, 1, 13) {
      REV_FOR(x, 115, 1) {
        seps::sknr(k, x, xxr, xrb);
        xxr = max(60, xxr);
        xrb = max(60, xrb);
        
        #ifdef DEBUG
        fprintf(fp, "[siml:rhnf] pseid = %d, s = %d, k = %d, i = %d, x = %d\n", pseid, s, k, i, x);
        #endif
        FOR(xx, 0, 15) {
          if(i >= 5 && xx != 0) continue;
          seps::simlrhnf(i, x, xx, xxr);

        }
        if(i == 12 && x >= 19) {
          tmz = rc.AT(s, k, x);
          tmx =   f.AT(x, 0, i, 2)
                + f.AT(x, 0, i, 3)
                + f.AT(x, 0, i, 11)
                - f.AT(x, 0, i, 15)
                - f.AT(x, 0, i, 16) * 3.0 / 4.0
                - f.AT(x, 0, i, 17) * tmz
                - f.AT(x, 0, i, 18) * (1.0 - tmz);
          if(tmx < 0.0) {
            tmy = - f.AT(x, 0, i, 2)
                  - f.AT(x, 0, i, 3)
                  + f.AT(x, 0, i, 15)
                  + f.AT(x, 0, i, 16) * 3.0 / 4.0;
            f.AT(x, 0, i, 11) = tmy
                                + f.AT(x, 0, i, 17) * tmz
                                + f.AT(x, 0, i, 18) * (1.0 - tmz);
          }
        }
      }
      #ifdef DEBUG
      fprintf(fp, "[siml:rhnf0] pseid = %d, s = %d, k = %d, i = %d\n", pseid, s, k, i);
      #endif
      seps::simlrhnf0(i);

    }

       
    REV_FOR(x, 70, 61) {
      #ifdef DEBUG
      fprintf(fp, "[siml:rhnfsen] pseid = %d, s = %d, k = %d, x = %d\n", pseid, s, k, x);
      #endif
      seps::simlrhnfsen(x);
    }

    #ifdef DEBUG
    fprintf(fp, "[siml:rhnfsen60] pseid = %d, s = %d, k = %d\n", pseid, s, k);
    #endif
    seps::simlrhnfsen60();


    if(pseid == 0 && s <= 2) {
	      if(k == KIJUN + 1){
	        sst::subc3(fpart, 60,70, 0,15, 1,2);
	        sst::subc3(fpart2, 60,70, 0,15, 1,2);
	      }
	      if(k == partyr3) {
	        FOR(x, 60, 70) {
	          seps::sknr(k, x, xxr, xrb);
	          if(x <= xrb) continue;
	          tmp = 0.0;
	          FOR(xx, 0, 15) {
	            tmp += r.AT(x, xx, 1) + r.AT(x, xx, 3);
	          }
	          tmq = lpt1.AT(k, s, x) * rt.AT(k, xrb);
	          tmq = min(tmq, tmp);
	          if(tmp > 1.0e-6) {
	            FOR(xx, 0, 15) {
	              tmr = r.AT(x, xx, 1) * tmq / tmp;
	              tms = r.AT(x, xx, 3) * tmq / tmp;
	              r.AT(x, xx, 1) -= tmr;
	              r.AT(x, xx, 3) -= tms;
	              if(x < 65) {
	                r.AT(x, xx, 2) += tmr;
	                r.AT(x, xx, 4) += tms;
	              }
	              fpart.AT(x, xx, 1) += f.AT(x, xx, 1, 1) * tmq / tmp;
	              fpart.AT(x, xx, 2) += f.AT(x, xx, 3, 1) * tmq / tmp;
	            }
	          }
	        }
	      }
	      if(flg_part >= 1 && k == partyr4) {
	        FOR(x, 60, 70) {
	          seps::sknr(k, x, xxr, xrb);
	          if(x <= xrb) continue;
	          tmp2 = 0.0;
	          FOR(xx, 0, 15) {
	            tmp2 += r.AT(x, xx, 1) + r.AT(x, xx, 3);
	          }
	          tmq2 = (lpt2.AT(k, s, x) + lpt3.AT(k, s, x) + lpt4.AT(k, s, x))
	                  * rt.AT(k, xrb);
	          tmq2 = min(tmq2, tmp2);
	          if(tmp2 > 1.0e-6) {
	            FOR(xx, 0, 15) {
	              tmr2 = r.AT(x, xx, 1) * tmq2 / tmp2;
	              tms2 = r.AT(x, xx, 3) * tmq2 / tmp2;
	              r.AT(x, xx, 1) -= tmr2;
	              r.AT(x, xx, 3) -= tms2;
	              if(x < 65) {
	                r.AT(x, xx, 2) += tmr2;
	                r.AT(x, xx, 4) += tms2;
	              }
	              fpart2.AT(x, xx, 1) += f.AT(x, xx, 1, 1) * tmq2 / tmp2;
	              fpart2.AT(x, xx, 2) += f.AT(x, xx, 3, 1) * tmq2 / tmp2;
	            }
	          }
	        }
	      }
	      
	      if(k > partyr3) {
	        REV_FOR(x, 70, 61) {
	          tmr = 1.0 - q2.AT(k, x);
	          if(x <= 67) {
	            tms = 1.0 + hh.AT(k);
	          } else {
	            tms = 1.0 + ci.AT(k);
	          }
	          FOR(xx, 0, 15) {
	            fpart.AT(x, xx, 1) = fpart.AT(x - 1, xx, 1) * tmr * tms;
	            fpart.AT(x, xx, 2) = fpart.AT(x - 1, xx, 2) * tmr * tms;
	            if(flg_part >= 1 && k == partyr4){
	            	fpart.AT(x, xx, 1) += fpart2.AT(x, xx, 1);
	            	fpart.AT(x, xx, 2) += fpart2.AT(x, xx, 2);
	            }
	          }
	        }
	        FOR(xx, 0, 15) {
	          fpart.AT(60, xx, 1) = 0.0;
	          fpart.AT(60, xx, 2) = 0.0;
	        }
	      }
    }


	if(flg_hantei == 0 && pseid == 0 && s <= 2){
		
		REV_FOR(i, 4, 1){
			REV_FOR(x, xend, 60){
				seps::sknr(k, x, xxr, xrb);
				FOR(xx, 0, 15){
					if(xx != 0) continue;
					
					if(x == xrb){
						if(i != 1){
							rcoe = 0.0;
							if(s == 1 && i == 1) rcoe = 0.36;
							if(s == 1 && i == 2) rcoe = 0.64;
							if(s == 2 && i == 1) rcoe = 0.60;
							if(s == 2 && i == 2) rcoe = 0.40;
							
							if(i == 1 || i == 2){
								rhantei.AT(x, xx, i) = - (rhantei.AT(x, xx, 3) + rhantei.AT(x, xx, 4)) * rcoe;
							}
							if(i == 3 || i == 4){
								rhantei.AT(x, xx, i) = rn.AT(x, xx, i) * (routsu.AT(s, i, 1) - 1.0);
							}
						}
					}
					else if((i == 2 || i == 4) && k == KIJUN + 1 && (x >= 65 && x <= 70)){
						rtemp = 0.0;
						if(i == 2 && s == 1) rtemp = routsu.AT(s, i, 1) - 0.06;
						if(i == 4 && s == 1) rtemp = routsu.AT(s, i, 1) + 0.13;
						if(i == 2 && s == 2) rtemp = routsu.AT(s, i, 1) - 0.06;
						if(i == 4 && s == 2) rtemp = routsu.AT(s, i, 1) + 0.03;
					    rhantei.AT(x, xx, i)  = rn.AT(x, xx, i) * ( rtemp - 1.0 );
					} 
					else if( ((i == 2 || i == 4) && s == 1 && k == KIJUN + 2 && x == 65) ||
							 ((i == 2 || i == 4) && s == 2 && 
					           ((k == KIJUN + 2 && x == 65) || (k == KIJUN + 3 && x == 65)))
					){
						rhantei.AT(x, xx, i)  = rn.AT(x, xx, i) * (routsu.AT(s, i, 1) - 1.0);
					}
					else{
						if(i == 1 || i == 3){
							rhantei.AT(x, xx, i) = rhantei.AT(x-1, xx, i) * (1.0 - q.AT(k, x, 1));
						}
						if(i == 2 || i == 4){
							rhantei.AT(x, xx, i) = rhantei.AT(x-1, xx, i) * (1.0 - q2.AT(k, x));
						}
					}
					
					if(k == KIJUN + 1 && (i == 1 || i == 3) && ((s == 1 && x >= 65) || (s == 2 && x >= 63))){
						rhantei.AT(x, xx, i) = 0.0;
					}
					if(k == KIJUN + 1 && (i == 2 || i == 4) && x >= 71){
						rhantei.AT(x, xx, i) = 0.0;
					}
					FOR(j, 1, 23){
						if(j == 1 || (j >= 3 && j <= 6) || j == 14 || j == 23){
							
							if((j >= 3 && j <= 6) || j == 23) n = 1;
							if(j == 1)                        n = 2;
							if(j == 14)                       n = 3;

							if(x == xrb){
								fcoe = 0.0;
								if((j >= 3 && j <= 6) || j == 23){
									if(s == 1 && i == 1) fcoe = 0.36;
									if(s == 1 && i == 2) fcoe = 0.64;
									if(s == 2 && i == 1) fcoe = 0.60;
									if(s == 2 && i == 2) fcoe = 0.40;
								}
								if(j == 1){
									if(s == 1 && i == 1) fcoe = 0.11;
									if(s == 1 && i == 2) fcoe = 0.89;
									if(s == 2 && i == 1) fcoe = 0.46;
									if(s == 2 && i == 2) fcoe = 0.54;
								}
								if(j == 14){
									if(s == 1 && i == 1) fcoe = 0.15;
									if(s == 1 && i == 2) fcoe = 0.85;
									if(s == 2 && i == 1) fcoe = 0.50;
									if(s == 2 && i == 2) fcoe = 0.50;
								}
								
								if(i == 1 || i == 2){
									fhantei.AT(x, xx, i, j) = - (fhantei.AT(x, xx, 3, j) + fhantei.AT(x, xx, 4, j)) * fcoe;
								}
								if(i == 3 || i == 4){
									fhantei.AT(x, xx, i, j) = fn.AT(x, xx, i, j) * (routsu.AT(s, i, n) - 1.0);
								}
							}
							else if((i == 2 || i == 4) && k == KIJUN + 1 && (x >= 65 && x <= 70)){
								ftemp = 0.0;
								if((j >= 3 && j <= 6) || j == 23){
									if(i == 2 && s == 1) ftemp = routsu.AT(s, i, n) - 0.06;
									if(i == 4 && s == 1) ftemp = routsu.AT(s, i, n) + 0.13;
									if(i == 2 && s == 2) ftemp = routsu.AT(s, i, n) - 0.06;
									if(i == 4 && s == 2) ftemp = routsu.AT(s, i, n) + 0.03;
								}
								if(j == 1){
									if(i == 2 && s == 1) ftemp = routsu.AT(s, i, n) - 0.00;
									if(i == 4 && s == 1) ftemp = routsu.AT(s, i, n) + 0.03;
									if(i == 2 && s == 2) ftemp = routsu.AT(s, i, n) - 0.01;
									if(i == 4 && s == 2) ftemp = routsu.AT(s, i, n) + 0.01;
								}
								if(j == 14){
									if(i == 2 && s == 1) ftemp = routsu.AT(s, i, n) - 0.01;
									if(i == 4 && s == 1) ftemp = routsu.AT(s, i, n) + 0.01;
									if(i == 2 && s == 2) ftemp = routsu.AT(s, i, n) - 0.02;
									if(i == 4 && s == 2) ftemp = routsu.AT(s, i, n) + 0.01;
								}
							    fhantei.AT(x, xx, i, j)  = fn.AT(x, xx, i, j) * ( ftemp - 1.0 );
							}
							else if( ((i == 2 || i == 4) && s == 1 && k == KIJUN + 2 && x == 65) ||
									 ((i == 2 || i == 4) && s == 2 && 
						         	  ((k == KIJUN + 2 && x == 65) || (k == KIJUN + 3 && x == 65)))
							){
								fhantei.AT(x, xx, i, j) = fn.AT(x, xx, i, j) * (routsu.AT(s, i, n) - 1.0);
							}
							else{
								if(i == 1 || i == 3){
									fhantei.AT(x, xx, i, j) = fhantei.AT(x-1, xx, i, j) * (1.0 - q.AT(k, x, 1));
								}
								if(i == 2 || i == 4){
									fhantei.AT(x, xx, i, j) = fhantei.AT(x-1, xx, i, j) * (1.0 - q2.AT(k, x));
								}
							}
							if(k == KIJUN + 1 && (i == 1 || i == 3) &&
							   ((s == 1 && x >= 65) || (s == 2 && x >= 63)) ){
								fhantei.AT(x, xx, i, j) = 0.0;
							}
							if(k == KIJUN + 1 && (i == 2 || i == 4) && x >= 71){
								fhantei.AT(x, xx, i, j) = 0.0;
							}
						}
					}
				}
				
			}
		}
	}


    if(key == 12 && k == psly - 1) {
      FOR(x, 15, xend - 1) FOR(t, 0, tend - 1) FOR(i, 0, 1) FOR(j, 0, 6) {
        psz .AT(x, t, i, j) = z .AT(x, t, i, j);
        psze.AT(x, t, i, j) = ze.AT(x, t, i, j);
      }
      FOR(x, 0, 114) {
        if(60 <= x && x <= 70) {
          pshnsen.AT(x) = rsen.AT(x);
        }
        FOR(xx, 0, 15) FOR(i, 1, 13) {
          pshn.AT(x, xx, i) = r.AT(x, xx, i);
        }
      }
    }
 
 
}
