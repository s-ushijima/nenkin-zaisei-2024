#include "sepscommon.h"
#include "sepslib.h"

static void set_jikoutou(v1_t &);
static void set_jshahosei(v1_t &);

void seps::shkejsha(int i, int x, int xx) {

  double gv, gvr, gvk, gvkk;
  v1_t tmsii  = VEC(double, 13);
  v1_t tmsii2 = VEC(double, 13);


  seps::siku(x, i, gv, gvr, gvk, gvkk);

  set_jikoutou(tmsii);


  t4.AT(x, xx, i) = t4k.AT(x, xx, i) * gvr;


  hn2.AT(x, xx, i, 1) = hn2k.AT(x, xx, i, 1) * gvr;
  hn2.AT(x, xx, i, 2) = hn2k.AT(x, xx, i, 2) * gvr;


  FOR(j, 1, 23) {
    if(j == 6 || j == 14 || j == 21) {
      t6.AT(x, xx, i, j) = t6k.AT(x, xx, i, j) * gvk;
    } else if(i == 10 && (j == 17 || j == 19 || j == 20)) {
      t6.AT(x, xx, i, j) = t6k.AT(x, xx, i, j) * gvkk;
    } else {
      if(flg_toukei == 1){
      	t6.AT(x, xx, i, j) = t6k.AT(x, xx, i, j) * gvr;
      } else{
        t6.AT(x, xx, i, j) = t6k.AT(x, xx, i, j) * gv;
      }
    }

    if(pseid == 0 && ((j <= 12 && j != 6) || j == 23)) {
       if(k <= 22) {
	      t6.AT(x, xx, i, j) *= 1.0 + tmsii.AT(i);
	   } else if(k <= 22 + 4) {
	      t6.AT(x, xx, i, j) *= 1.0 + tmsii.AT(i) * (22 + 5 - k) / 5.0;
	   }
    } else if(pseid == 1 || pseid == 4 || pseid == 5) {
      if((j == 1 || j == 2 || j == 3 || (7 <= j && j <= 12 ))
        && (i >= 5 && i != 9 && i != 11)) {
        t6 .AT(x, xx, i, j) *= tmsii.AT(i);
        t6k.AT(x, xx, i, j) *= tmsii.AT(i);
      }
    }
  }




  if(k <= KIJUN + 5 
    && (60 <= x && x <= 69)
    && i <= 4) {

    int ss = s;
    if(s == 3) ss = 1; 

   	t4k.AT(x, xx, i) *= nos.AT(k, x, ss, i, 2);
	

    FOR(j, 1, 23) {
      t6k.AT(x, xx, i, j) *= nos.AT(k, x, ss, i, 1);
    }
  }

  if(s != 2 && x >= 19 && i == 11 && 1.0 - rc.AT(s, k, x) >= 1.0e-6) {
    t6k.AT(x, xx, i, 7) /= 1.0 - rc.AT(s, KIJUN, x);
    t6k.AT(x, xx, i, 8) /= 1.0 - rc.AT(s, KIJUN, x);
  }
  
}


static void set_jikoutou(v1_t &tmsii) {

  FOR(i, 1, 13) {
    if(pseid == 0) {
      tmsii.AT(i) = 0.0;
    } else {
      tmsii.AT(i) = 1.0;
    }
  }

  int key_jikout = 1;
  int key_kyosai = 1;
  
  
  if(flg_hantei == 0){

	  if(pseid == 0 && key_jikout == 1) {
	    	tmsii.AT(1)  = 0.0009;
		    tmsii.AT(5)  = 0.0015;
		    tmsii.AT(7)  = 0.0269;
		    tmsii.AT(9)  = 0.0001;
		    tmsii.AT(10) = 0.0049;
		    tmsii.AT(11) = 0.0000;
		    tmsii.AT(12) = 0.0009;
		    tmsii.AT(13) = 0.0028;
		    tmsii.AT(2)  = tmsii.AT(1);
		    tmsii.AT(3)  = tmsii.AT(1);
		    tmsii.AT(4)  = tmsii.AT(1);
		    tmsii.AT(6)  = tmsii.AT(5);
		    tmsii.AT(8)  = tmsii.AT(7);
	  }
	  else if(key_kyosai == 1) {
	    if(pseid == 1) {
	      tmsii.AT(5)  = 1.1296;
	      tmsii.AT(6)  = 1.0000;
	      tmsii.AT(7)  = 1.0311;
	      tmsii.AT(8)  = 1.0000;
	      tmsii.AT(10) = 0.9977;
	      tmsii.AT(12) = 0.9488;
	      tmsii.AT(13) = 1.3214;
	    }
	    
	    else if(pseid == 4) {
	      tmsii.AT(5)  = 1.0517;
	      tmsii.AT(6)  = 1.0000;
	      tmsii.AT(7)  = 1.0022;
	      tmsii.AT(8)  = 1.0000;
	      tmsii.AT(10) = 1.0118;
	      tmsii.AT(12) = 1.0155;
	      tmsii.AT(13) = 1.5290;
	    }
	    
	    else if(pseid == 5) {
	      tmsii.AT(5)  = 1.0298;
	      tmsii.AT(6)  = 1.0000;
	      tmsii.AT(7)  = 1.0001;
	      tmsii.AT(8)  = 1.0000;
	      tmsii.AT(10) = 0.9866;
	      tmsii.AT(12) = 0.9887;
	      tmsii.AT(13) = 1.5069;
	    }
	  }
	  
   }
}

