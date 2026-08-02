#include "sepscommon.h"

void seps::siku(int x, int i, double &gv, double &gvr, double &gvk, double &gvkk) {

  double dkzik;
  double gv1, gvr1;
  v1_t gva = VEC(double, 2);
  v1_t gvra = VEC(double, 2);
  
  v1_t gvb = VEC(double, 2);
  v1_t gvrb = VEC(double, 2);

  seps::sknr(k, x, xxr, xrb);
  xrb = max(60, xrb);

  gv   = 1.0;
  gvr  = 1.0;
  gvk  = 1.0;
  gv1  = 1.0;
  gvr1 = 1.0;
  gvkk = 1.0;
  dkzik = 0.0;
  
  int s3;
  if(s2 != 2) {
    s3 = 1;
  } else {
    s3 = 2;
  }

  if(flg_toukei == 0){
	  if(i == 1) {
	    gv   = sik.AT(k, x, s3,  1, 1);
	    gvr  = sik.AT(k, x, s3,  1, 2);
	    gvk  = sik.AT(k, x, s3, 14, 1);
	    gvkk = gv;
	  }
	  else if(i == 2) {
	    gv1  = sik.AT(k, x, s3, 2, 1);
	    gvr1 = sik.AT(k, x, s3, 2, 2);
	    gvk  = sik.AT(k, x, s3, 14, 1);
	    gvkk = dkzik;

	    if(flg_kozax == 1 && k >= kozaxyr && x >= kozax) {
	      gv1  = sik.AT(k, x, s3, 1, 1);
	      gvr1 = sik.AT(k, x, s3, 1, 2);
	    }
	    
	    gv  = gv1;
	    gvr = gvr1;

	  }

	  else if(i == 3) {
	    gv   = sik.AT(k, x, s3,  3, 1);
	    gvr  = sik.AT(k, x, s3,  3, 2);
	    gvk  = sik.AT(k, x, s3, 15, 1);
	    gvkk = gv;
	  }

	  else if(i == 4) {
	    gv1  = sik.AT(k, x, s3,  4, 1);
	    gvr1 = sik.AT(k, x, s3,  4, 2);
	    gvk  = sik.AT(k, x, s3, 15, 1);
	    gvkk = dkzik;

	    if(flg_kozax == 1 && k >= kozaxyr && x >= kozax) {
	      gv1  = sik.AT(k, x, s3, 3, 1);
	      gvr1 = sik.AT(k, x, s3, 3, 2);
	    } 

	    gv  = gv1;
	    gvr = gvr1;
	    
	  }

	  else if(i == 5 || (i == 6 && x >= max(xend, 85))) {
	    gv   = sik.AT(k, x, s3, 5, 1);
	    gvr  = sik.AT(k, x, s3, 5, 2);
	    gvk  = gvr;
	    gvkk = gv;
	  }

	  else if(i == 6) {
	    gv   = sik.AT(k, x, s3, 6, 1);
	    gvr  = sik.AT(k, x, s3, 6, 2);
	    gvk  = gvr;
	    gvkk = dkzik;

	    if(flg_kozax >= 1 && k >= kozaxyr && x >= kozax) {
	      gv  = sik.AT(k, x, s3, 5, 1);
	      gvr = sik.AT(k, x, s3, 5, 2);
	    }
	  }

	  else if(i == 7 || (i == 8 && x >= max(xend, 85))) {
	    gv   = sik.AT(k, x, s3, 7, 1);
	    gvr  = sik.AT(k, x, s3, 7, 2);
	    gvk  = gvr;
	    gvkk = gv;
	  }

	  else if(i == 8) {
	    gv   = sik.AT(k, x, s3, 8, 1);
	    gvr  = sik.AT(k, x, s3, 8, 2);
	    gvk  = gvr;
	    gvkk = dkzik;

	    if(flg_kozax == 1 && k >= kozaxyr && x >= kozax) {
	      gv  = sik.AT(k, x, s3, 7, 1);
	      gvr = sik.AT(k, x, s3, 7, 2);
	    }
	  }

	  else if(i == 9  ||  i == 10) {
	    gv  = sik.AT(k, x, s3,  i, 1);
	    gvr = sik.AT(k, x, s3,  i, 2);
	    gvk = sik.AT(k, x, s3, 16, 1);
	    if(i == 10)  gvkk = sik.AT(k, x, s3, 18, 1);
	  }

	  else if(i >= 11) {
	    gv  = sik.AT(k, x, s3,  i, 1);
	    gvr = sik.AT(k, x, s3,  i, 2);
	    gvk = sik.AT(k, x, s3, 17, 1);
	  }
	  
   }
}
