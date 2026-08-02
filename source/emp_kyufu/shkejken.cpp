#include "sepscommon.h"
#include "sepslib.h"

void seps::shkejken(int i, int x, int xx) {

  double tmgd, tmgk, tmgbe, tmp1, tmp2, tmf;
  v1_t tmfsen = VEC(double, 23);
  int kx = k-x, n;
  

  xrb = 0;
  if(i <= 4) {
    seps::sknr(k, x, xxr, xrb);
    xxr = max(60, xxr);
    xrb = max(60, xrb);
  }
 
  if((xrb > 60 && x < 65 - xx && x < xrb && xx <= 5) || (xx > 5 && x < 60 + xx)) {
  }else {
    
    t4k.AT(x, xx, i) = r.AT(x, xx, i);
   
  
    if(flg_hantei == 0 && k >= KIJUN + 1 && pseid == 0 && s <= 2 &&
       xx == 0 && (i >= 1 && i <= 4)
      ){
    	tmp1 = 0.0;
    	if( (k-x <= KIJUN+1-65 && k-x >= KIJUN+1-70) || 
	    	(s == 1 && k-x == KIJUN+2-65)            || 
	    	(s == 2 && (k-x == KIJUN+2-65 || k-x == KIJUN+3-65))
    	  ){
    		if(i == 2){
    			t4k.AT(x, xx, i) = r.AT(x, xx, i) + rhantei.AT(x, xx, i);
    		}
    		if(i == 4){
    			t4k.AT(x, xx, i) = max( r.AT(x, xx, i) + rhantei.AT(x, xx, i) ,
	  			                        r.AT(x, xx, i) * routsu.AT(s, i, 1) );
	  			tmp1 += - rhantei.AT(x, xx, i) - (r.AT(x, xx, i) - t4k.AT(x, xx, i)); 
	  			t4k.AT(x, xx, 2) -= tmp1;
    		}
    	}
    	
    	else{
		  	if(i == 1){
		  		t4k.AT(x, xx, i) = r.AT(x, xx, i) - (rhantei.AT(x, xx, 2) 
		  		                     + rhantei.AT(x, xx, 3) + rhantei.AT(x, xx, 4)) ;
		  	}
		  	if(i == 2){
		  		t4k.AT(x, xx, i) = r.AT(x, xx, i) + rhantei.AT(x, xx, i);
	  		}
	  		if(i == 3){
	  			t4k.AT(x, xx, i) = max( r.AT(x, xx, i) + rhantei.AT(x, xx, i) , 
	  			                        r.AT(x, xx, i) * routsu.AT(s, i, 1) );
	  			tmp1 += - rhantei.AT(x, xx, i) - (r.AT(x, xx, i) - t4k.AT(x, xx, i));
	  		}
	  		if(i == 4){
	  			t4k.AT(x, xx, i) = max( r.AT(x, xx, i) + rhantei.AT(x, xx, i) ,
	  			                        r.AT(x, xx, i) * routsu.AT(s, i, 1) );
	  			tmp1 += - rhantei.AT(x, xx, i) - (r.AT(x, xx, i) - t4k.AT(x, xx, i)); 
	  			t4k.AT(x, xx, 1) -= tmp1;
	  		}
  		}
    }
    
    hn2k.AT(x, xx, i, 1) = hn.AT(x, xx, i, 1);
    hn2k.AT(x, xx, i, 2) = hn.AT(x, xx, i, 2);
  }
  
  if(i == 1 && xx == 0 && (60 <= x && x <= 69) && xxr > 60) {
    t4k .AT(x, 0, 1)    += rsen.AT(x);
    hn2k.AT(x, 0, 1, 1) += hnsen.AT(x, 1);
    hn2k.AT(x, 0, 1, 2) += hnsen.AT(x, 2);
  }
  
  FOR(j, 1, 23) {
    if((i <= 8 && x >= 60 && xrb > 60 && x < 65 - xx && x < xrb && xx <= 5)
       || (xx > 5  &&  x < 60+xx)) continue;
    if(j == 14 || j == 21) {
      t6k.AT(x, xx, i, j) = max(f.AT(x, xx, i, j), f_min.AT(x, xx, i, j));
    } else if(j == 1  ||  j == 10) {
       t6k.AT(x, xx, i, j) = max(max(
                                f.AT(x, xx, i, j),
                                f_hik.AT(x, xx, i, j)),
                                f_min.AT(x, xx, i, j));
    } else if(j != 13  &&  j != 22) {
      t6k.AT(x, xx, i, j) = max(f.AT(x, xx, i, j), f_min.AT(x, xx, i, j));
    }
    
    
    if(flg_hantei == 0 && k >= KIJUN + 1 && pseid == 0 && s <= 2 && xx == 0 &&
       (i >= 1 && i <= 4) && (j == 1 || (j >= 3 && j <= 6) || j == 14 || j == 23) 
      ){
		tmp2 = 0.0;
		tmf  = 0.0;
		if((j >= 3 && j <= 6) || j ==23) n = 1;
		if(j == 1)                       n = 2;
		if(j == 14)                      n = 3;
		
    	if( (k-x <= KIJUN+1-65 && k-x >= KIJUN+1-70) || 
    	    (s == 1 && k-x == KIJUN+2-65)            || 
    	    (s == 2 && (k-x == KIJUN+2-65 || k-x == KIJUN+3-65)) 
    	   ){
    		if(i == 2){
	  			t6k.AT(x, xx, i, j)  += fhantei.AT(x, xx, i, j);
	  		}
	  		if(i == 4){
	  			tmf = t6k.AT(x, xx, i, j);
	  			t6k.AT(x, xx, i, j)  = max( t6k.AT(x, xx, i, j) + fhantei.AT(x, xx, i, j) ,
	  								        t6k.AT(x, xx, i, j) * routsu.AT(s, i, n) );
	  			tmp2 += - fhantei.AT(x, xx, i, j) - (tmf - t6k.AT(x, xx, i, j));
	  			t6k.AT(x, xx, 2, j) -= tmp2;
	  		}
    	}
	    else{
	  		if(i == 1){
			  	t6k.AT(x, xx, i, j)  += - ( fhantei.AT(x, xx, 2, j) + fhantei.AT(x, xx, 3, j)
	  			                             + fhantei.AT(x, xx, 4, j) ) ;
	  		}
	  		if(i == 2){
			  	t6k.AT(x, xx, i, j)  += fhantei.AT(x, xx, i, j);
	  		}
	  		if(i == 3){
	  			t6k.AT(x, xx, i, j)  = max( t6k.AT(x, xx, i, j) + fhantei.AT(x, xx, i, j) ,
	  			                            t6k.AT(x, xx, i, j) * routsu.AT(s, i, n) );
	  			tmp2 += - fhantei.AT(x, xx, i, j) - (f.AT(x, xx, i, j) - t6k.AT(x, xx, i, j)); 
	  		}
	  		if(i == 4){
	  			tmf = t6k.AT(x, xx, i, j);
	  			t6k.AT(x, xx, i, j)  = max( t6k.AT(x, xx, i, j) + fhantei.AT(x, xx, i, j) ,
	  								        t6k.AT(x, xx, i, j) * routsu.AT(s, i, n) );
	  			tmp2 += - fhantei.AT(x, xx, i, j) - (tmf - t6k.AT(x, xx, i, j));
	  			t6k.AT(x, xx, 1, j) -= tmp2;
	  		}
	  	}
  	}

  }

  if(i == 11 || i == 12) {
    if(x >= 19) {
      if(s2 != 2) {
        t6k.AT(x, xx, i, 14) *= rc.AT(s, k, x);
        t6k.AT(x, xx, i, 17) *= rc.AT(s, k, x);
        t6k.AT(x, xx, i, 7)  *= 1.0 - rc.AT(s, k, x);
        t6k.AT(x, xx, i, 8)  *= 1.0 - rc.AT(s, k, x);
        t6k.AT(x, xx, i, 18) *= 1.0 - rc.AT(s, k, x);
      } else {
        t6k.AT(x, xx, i, 14) *= rc.AT(s, k, x);
        t6k.AT(x, xx, i, 17) = 0.0;
        t6k.AT(x, xx, i, 18) = 0.0;
        t6k.AT(x, xx, i, 20) = 0.0;
      }
    }
  }
  if(i == 13 && x >= 19 && s2 == 2) {
    t6k.AT(x, xx, i, 17) = 0.0;
  }
  
  if(i <= 4) {
    int j;
    if(k >= 22 && k - 22 >= x - 60){
      j = 1;
    } else {
      j = 0;
    }
	
    if(x >= 60 && xrb > 60 && xx <= 5 && 65 - xx < xrb) {
      	  tmgbe = rigbe.AT(s2, 65 - xx, xrb, j);
	      t6k .AT(x, xx, i, 1) *= tmgbe;
    }
    
    if(xx <= 5) {
      tmgd = rigd.AT(s2, 65 - xx, xxr, j);
      tmgk = rigk.AT(s2, 65 - xx, xxr, j);

      if(xrb > 60 && 65 - xx < xrb) {
        if(x < 65 - xx) {
          t6k.AT(x, xx, i, 3) = 0.0;
        } else {
          t6k.AT(x, xx, i, 3) *= tmgk;
        }
      } else {
        if(x < 65) {
          t6k.AT(x, xx, i, 3) = 0.0;
        }
      }

      if(x < 65 - xx) {
        t6k.AT(x, xx, i, 14) = 0.0;
        if(x < xxr && xxr > 60) {
          t6k.AT(x, xx, i, 2) = 0.0;
        }
      } else if(x < 65) {
        t6k.AT(x, xx, i, 2)  *= tmgd;
        t6k.AT(x, xx, i, 14) *= tmgk;
      } else if(x >= 65) {
        t6k.AT(x, xx, i, 2)  = 0.0;
        t6k.AT(x, xx, i, 14) *= tmgd + tmgk;
      }
    } else if (xx > 5) {
      if(x < 60 + xx) {
        t6k .AT(x, xx, i, 1)  = 0.0;
        t6k .AT(x, xx, i, 2)  = 0.0;
        t6k .AT(x, xx, i, 3)  = 0.0;
        t6k .AT(x, xx, i, 14) = 0.0;
      } else {
        tmgbe = 1.0 + 0.007 * (xx - 5) * 12.0;

        t6k .AT(x, xx, i, 1)  *= tmgbe;
        t6k .AT(x, xx, i, 2)  = 0.0;
        t6k .AT(x, xx, i, 3)  *= tmgbe;
        t6k .AT(x, xx, i, 14) *= tmgbe;
      }
    }
  }


  double adt_3_2 = adt.AT(3) / adt.AT(2);
  int ii;
  if(i <= 8) {
    if(i <= 2) {
      ii = 1;
    } else if(i <= 4) {
      ii = 6;
    } else {
      ii = 2;
    }
    t6k.AT(x, xx, i, 4)  *= kd.AT(k, ii, 1, x);
    t6k.AT(x, xx, i, 5)  *= kd.AT(k, ii, 2, x) + kd.AT(k, ii, 3, x) * adt_3_2;
    t6k.AT(x, xx, i, 6)  *= kd.AT(k, ii, 4, x);
    t6k.AT(x, xx, i, 19) *= kd.AT(k, ii, 1, x);
    t6k.AT(x, xx, i, 23) *= kd.AT(k, ii, 1, x);
    if(x < xxr || (xx > 5 && x < 60+xx)) {
      t6k.AT(x, xx, i, 4)  = 0.0;
      t6k.AT(x, xx, i, 5)  = 0.0;
      t6k.AT(x, xx, i, 6)  = 0.0;
      t6k.AT(x, xx, i, 19) = 0.0;
      t6k.AT(x, xx, i, 23) = 0.0;
    }
  } else if(i <= 10) {
    if(i == 9) {
      ii = 3;
    } else {
      ii = 4;
    }

    t6k.AT(x, xx, i, 4)  *= kd.AT(k, ii, 1, x);
    t6k.AT(x, xx, i, 5)  *= kd.AT(k, ii, 2, x) + kd.AT(k, ii, 3, x) * adt_3_2;
    t6k.AT(x, xx, i, 6)  *= kd.AT(k, ii, 4, x);
    t6k.AT(x, xx, i, 19) *= kd.AT(k, ii, 1, x);
    t6k.AT(x, xx, i, 20) *= kd.AT(k, ii, 2, x) + kd.AT(k, ii, 3, x) * adt_3_2;
    t6k.AT(x, xx, i, 21) *= kd.AT(k, ii, 2, x) + kd.AT(k, ii, 3, x) * adt_3_2;
  } else {
    t6k.AT(x, xx, i, 5)  *= kd.AT(k, 5, 2, x) + kd.AT(k, 5, 3, x) * adt_3_2;
    t6k.AT(x, xx, i, 20) *= kd.AT(k, 5, 2, x) + kd.AT(k, 5, 3, x) * adt_3_2;
    t6k.AT(x, xx, i, 21) *= kd.AT(k, 5, 2, x) + kd.AT(k, 5, 3, x) * adt_3_2;
  }

  if(i == 1 && xx == 0 && (60 <= x && x <= 69) && xxr > 60) {
    FOR(j, 1, 23) {
      tmfsen.AT(j) = fsen.AT(x, j);
      if(j == 1 || j == 10) {
        tmfsen.AT(j) = max(fsen.AT(x, j), fsenhik.AT(x, j));
      }
      tmfsen.AT(j) = max(tmfsen.AT(j), fsenmin.AT(x, j));
    }
    t6k.AT(x, 0, 1, 1)  += tmfsen.AT(1);
    t6k.AT(x, 0, 1, 2)  += tmfsen.AT(2);
    t6k.AT(x, 0, 1, 4)  += tmfsen.AT(4) * kd.AT(k, ii, 1, x);
    t6k.AT(x, 0, 1, 5)  += tmfsen.AT(5)
                           * (kd.AT(k, ii, 2, x) + kd.AT(k, ii, 3, x) * adt_3_2);
    t6k.AT(x, 0, 1, 23) += tmfsen.AT(23) * kd.AT(k, ii, 1, x);
  }

  if(x >= 65 || x < 40) {
    t6k.AT(x, xx, i, 7) = 0.0;
  }
  if(x < 65) {
    t6k.AT(x, xx, i, 8)  = 0.0;
    t6k.AT(x, xx, i, 15) = 0.0;
    t6k.AT(x, xx, i, 16) = 0.0;
  }
  
  if(i == 12) {
    t6k.AT(x, xx, i, 12) = max(0.0,
      t6k.AT(x, xx, i, 12)
      - t6k.AT(x, xx, i, 10)
      - t6k.AT(x, xx, i, 5)
      - t6k.AT(x, xx, i, 9)
      - t6k.AT(x, xx, i, 11));
  } else {
    t6k.AT(x, xx, i, 12) = max(0.0,
      t6k.AT(x, xx, i, 12)
      - t6k.AT(x, xx, i, 10)
      - t6k.AT(x, xx, i, 11));
  }

  if(x >= 15) {
    int nsx = (int)round(ns.AT(k, x));
    if(nsx < 65 || k - nsx < -74) {
      t6k.AT(x, xx, i, 6) = 0.0;
    }
    if(k - nsx >= -74) {
      t6k.AT(x, xx, i, 18) = 0.0;
    }
  }
  
 

  if(pseid == 0 && s <= 2 && k >= partyr3 && (60 <= x &&  x <= 70)) {
      if(i == 1) {
        t6k.AT(x, xx, i, 1) -= fpart.AT(x, xx, 1);
      } else if(i == 2) {
        t6k.AT(x, xx, i, 1) += fpart.AT(x, xx, 1);
      } else if(i == 3) {
        t6k.AT(x, xx, i, 1) -= fpart.AT(x, xx, 2);
      } else if(i == 4) {
        t6k.AT(x, xx, i, 1) += fpart.AT(x, xx, 2);
      }
  }
  
  
  
}
