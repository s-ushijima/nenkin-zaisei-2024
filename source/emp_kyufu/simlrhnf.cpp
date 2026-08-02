#include "sepscommon.h"
#include "sepslib.h"

void seps::simlrhnf0(int i) {


  r.AT(0, 0, i)=rn.AT(0, 0, i);
  hn.AT(0, 0, i, 1)=hnn.AT(0, 0, i, 1);
  hn.AT(0, 0, i, 2)=hnn.AT(0, 0, i, 2);
  pshn.AT(0, 0, i)=pshnn.AT(0, 0, i);
  FOR(j, 1, 23) {
    if(i <= 10) {
      f_hik.AT(0, 0, i, j)=0.0;
      f_min.AT(0, 0, i, j)=0.0;
    } else {
      if(j == 1  ||  j == 10) { 
        f_hik.AT(0, 0, i, j)=fnhik.AT(0, 0, i, j);
        f_min.AT(0, 0, i, j)=fnmin.AT(0, 0, i, j);
      } else if(j == 13  ||  j == 22) {
        f_hik.AT(0, 0, i, j)=0.0;
        f_min.AT(0, 0, i, j)=0.0;
        fn.AT(0, 0, i, j)=0.0;
      } else {
        fnmin.AT(0, 0, i, j)=fn.AT(0, 0, i, j)*0.8;
        f_min.AT(0, 0, i, j)=fnmin.AT(0, 0, i, j);
      }
    }
    f.AT(0, 0, i, j)=fn.AT(0, 0, i, j);
  }
  
}


void seps::simlrhnf(int i, int x, int xx, int xxr) {

  double tmo, riv, riv2, riv3, riv4, riv5, tmp, taizai;

  int dx = max(x, 67);

  if(i == 1  ||  i == 3  ||  i == 5  ||  i == 7  || 
    ((i == 6 || i == 8) &&  x > 70+k-KIJUN)){
      tmo=1.0-q.AT(k, x, 1);
  } else if(i == 2  ||  i == 4  ||  i == 6  ||  i == 8) {
    if (x > 55  &&  x <= 60) {
      tmo=exp(-u.AT(k, x, 0));
    } else if(x > 60  &&  x <= xend-1) {
      tmo=1.0-q2.AT(k, x);
    } else {
      tmo=0.0;
    }
  }  
  if(i ==  9  ||  i == 10) tmo=1.0-q.AT(k, x, 2);  
  if(i >= 11)              tmo=1.0-q.AT(k, x, 3);
  

  if(i == 2  ||  i == 4) {
    if(x == 65) tmo=0.0;
    if(xend > 70  &&  x == 70) tmo=0.0;

    
    if( (xend > 66  &&  x == 66) || (xend > 67  &&  x == 67) || 
        (xend > 68  &&  x == 68) || (xend > 69  &&  x == 69)  ) {
      taizai=2;
      tmo=0.0;
    }
  }

  if(pseid == 0  &&  (i == 1  ||  i == 3)  && 
    x >= 70+k-KIJUN                            ){
    if(l.AT(k-1, s, x-1) > 1.0e-6) {
      tmp=max(0.0, 
              q2.AT(k, x)-(1.0+l.AT(k, s, x)/l.AT(k-1, s, x-1))*u.AT(k, x, 3)/2.0);
    } else {
      tmp=0.0;
    }
  } else {
    tmp=0.0;
  }

  if(i == 1  &&  x == xxr  &&  xxr > 60  &&  xx == 0) {
    r.AT(x, 0, 1)=(r.AT(x-1, 0, 1)+rsen.AT(x-1))*tmo+rn.AT(x, 0, 1);
    hn.AT(x, 0, 1, 1)=(hn.AT(x-1, 0, 1, 1)+hnsen.AT(x-1, 1))*tmo+hnn.AT(x, 0, 1, 1);
    hn.AT(x, 0, 1, 2)=(hn.AT(x-1, 0, 1, 2)+hnsen.AT(x-1, 2))*tmo+hnn.AT(x, 0, 1, 2);
    pshn.AT(x, 0, 1)=(pshn.AT(x-1, 0, 1)+pshnsen.AT(x-1))*tmo+pshnn.AT(x, 0, 1);
    rsen.AT(x-1)=0.0;
    hnsen.AT(x-1, 1)=0.0;
    hnsen.AT(x-1, 2)=0.0;
    pshnsen.AT(x-1)=0.0;
  } else {
    r.AT(x, xx, i)=r.AT(x-1, xx, i)*tmo+rn.AT(x, xx, i);
    hn.AT(x, xx, i, 1)=hn.AT(x-1, xx, i, 1)*tmo+hnn.AT(x, xx, i, 1);
    hn.AT(x, xx, i, 2)=hn.AT(x-1, xx, i, 2)*tmo+hnn.AT(x, xx, i, 2);
    pshn.AT(x, xx, i)=pshn.AT(x-1, xx, i)*tmo+pshnn.AT(x, xx, i);
  }

  if(pseid == 0  &&  (i == 1  ||  i == 3)  && 
    x >= 70+k-KIJUN                            ){
    r.AT(x, xx, i)   =r.AT(x, xx, i)    +r.AT(x-1, xx, i+1)*tmp;
    hn.AT(x, xx, i, 1)=hn.AT(x, xx, i, 1) +hn.AT(x-1, xx, i+1, 1)*tmp;
    hn.AT(x, xx, i, 2)=hn.AT(x, xx, i, 2) +hn.AT(x-1, xx, i+1, 2)*tmp;
    pshn.AT(x, xx, i)=pshn.AT(x, xx, i) +pshn.AT(x-1, xx, i+1)*tmp;
  }

  FOR(j, 1, 23) {
    if(j == 13  ||  j == 22) {
    } else {

      int kku;
      if(j == 4   ||  j == 5   ||  j == 9   || 
        j == 19  ||  j == 20  ||  j == 21  ||  j == 23) {
        kku=1;
      } else {
        kku=0;
      }

      if(j == 1  ||  j == 10) {
        if(x <= 67) {
          riv=1.0+hh.AT(k);
        } else {
          riv=1.0+ci.AT(k);
        }
      } 
      else if(kku == 1) {
        riv=1.0+hp2.AT(k, 67);
      } 
      else {
        riv=1.0+hp2.AT(k, dx);
      }
      
      riv3 = 1.0+ci2.AT(k, dx);
	  riv4 = 1.0+hh.AT(k);
	  riv5 = 1.0+hp2.AT(k, 67);
   	   
      if(j != 1  &&  j != 10) {
        fnmin.AT(x, xx, i, j)=fn.AT(x, xx, i, j)*0.80;

        if(x > 67  && kku != 1) {
          riv2=1.0;
          int k_vs_x = min(k-5, x-68);
          FOR(kk, 0, k_vs_x) {
            riv2=riv2*(1.0+hp2.AT(k-kk, x-kk))/(1.0+hp2.AT(k-kk, 67));
          }
          fn.AT(x, xx, i, j)=fn.AT(x, xx, i, j)*riv2;
        }
      }


      if(i == 1  &&  x == xxr  &&  xxr > 60  &&  xx == 0) {
        f.AT(x, xx, 1, j)=(f.AT(x-1, xx, 1, j)+fsen.AT(x-1, j))*tmo*riv+fn.AT(x, xx, 1, j);
        fsen.AT(x-1, j)=0.0;
        if(j == 1  ||  j == 10) {
          f_hik.AT(x, xx, 1, j)=(f_hik.AT(x-1, xx, 1, j)+fsenhik.AT(x-1, j))
                        *tmo*riv3+fnhik.AT(x, xx, 1, j);
          f_min.AT(x, xx, 1, j)=(f_min.AT(x-1, xx, 1, j)+fsenmin.AT(x-1, j))
                        *tmo*riv4+fnmin.AT(x, xx, 1, j);
          fsenhik.AT(x-1, j)=0.0;
          fsenmin.AT(x-1, j)=0.0;
        } else {
          f_min.AT(x, xx, 1, j)=(f_min.AT(x-1, xx, 1, j)+fsenmin.AT(x-1, j))
                        *tmo*riv5 + fnmin.AT(x, xx, 1, j);
          fsenmin.AT(x-1, j)=0.0;
        }
      } else if(i == 11  && s2 != 2  && x == 65) {
        if(j == 1 ||  j == 10) {
          f.AT(x, xx, i, j)=f.AT(x-1, xx, i, j)*tmo*riv*1.0628+fn.AT(x, xx, i, j);
          f_hik.AT(x, xx, i, j)= f_hik.AT(x-1, xx, i, j)*tmo*riv3
                        *1.0608+fnhik.AT(x, xx, i, j);
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv4
                        *1.0608+fnmin.AT(x, xx, i, j);
        } else {
          f.AT(x, xx, i, j)=f.AT(x-1, xx, i, j)*tmo*riv+fn.AT(x, xx, i, j);
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv5
                        +fnmin.AT(x, xx, i, j);
        }
      } else if(i == 11 && s2 == 2  && x == 65) {
        if(j == 1 ||  j == 10) {
          f.AT(x, xx, i, j)=f.AT(x-1, xx, i, j)*tmo*riv*2.5057+fn.AT(x, xx, i, j);
          f_hik.AT(x, xx, i, j)= f_hik.AT(x-1, xx, i, j)*tmo*riv3
                        *2.9759+fnhik.AT(x, xx, i, j);
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv4
                        *2.9759+fnmin.AT(x, xx, i, j);
        } else {
          f.AT(x, xx, i, j)=f.AT(x-1, xx, i, j)*tmo*riv+fn.AT(x, xx, i, j);
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv5
                        +fnmin.AT(x, xx, i, j);
        }
      } else {
        f.AT(x, xx, i, j)=f.AT(x-1, xx, i, j)*tmo*riv+fn.AT(x, xx, i, j);
        if(j == 1  ||  j == 10) {
          f_hik.AT(x, xx, i, j)= f_hik.AT(x-1, xx, i, j)*tmo*riv3
                        +fnhik.AT(x, xx, i, j);
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv4
                        +fnmin.AT(x, xx, i, j);
        } else {
          f_min.AT(x, xx, i, j)= f_min.AT(x-1, xx, i, j)*tmo*riv5
                        +fnmin.AT(x, xx, i, j);
        }
      }

      if(pseid == 0  &&  (i == 1  ||  i == 3)  && 
        x >= 70+k-KIJUN                            ){
        f.AT(x, xx, i, j)= f.AT(x, xx, i, j)+f.AT(x-1, xx, i+1, j)*tmp*riv;
        if(j == 1  ||  j == 10) {
          f_hik.AT(x, xx, i, j)= f_hik.AT(x, xx, i, j)
                        +f_hik.AT(x-1, xx, i+1, j)*tmp*riv3;
          f_min.AT(x, xx, i, j)= f_min.AT(x, xx, i, j)
                        +f_min.AT(x-1, xx, i+1, j)*tmp*riv4;
        } else {
          f_min.AT(x, xx, i, j)= f_min.AT(x, xx, i, j)
                        +f_min.AT(x-1, xx, i+1, j)*tmp*riv5;
        }
      }
    }
  }

}


void seps::simlrhnfsen(int x) {

  double tmo, riv, riv2, riv3, riv4;

  int dx = max(x, 67);

  tmo=1.0-q.AT(k, x, 1);
  rsen.AT(x)=rsen.AT(x-1)*tmo+rsenn.AT(x);
  hnsen.AT(x, 1)=hnsen.AT(x-1, 1)*tmo+hnsenn.AT(x, 1);
  hnsen.AT(x, 2)=hnsen.AT(x-1, 2)*tmo+hnsenn.AT(x, 2);
  pshnsen.AT(x)=pshnsen.AT(x-1)*tmo+pshnsenn.AT(x);

  FOR(j, 1, 23) {
    if(j == 13  ||  j == 22) {
    
    } else {
    

      int kku;
      if(j == 4   ||  j == 5   ||  j == 9   || 
        j == 19  ||  j == 20  ||  j == 21  ||  j == 23) {
        kku=1;
      } else {
        kku=0;
      }


      if(j == 1  ||  j == 10) {
        if(x <= 67) {
          riv=1.0+hh.AT(k);
        } else {
          riv=1.0+ci.AT(k);
        }
      } else if(kku == 1) {
        riv=1.0+hp2.AT(k, 67);
      } else {
        riv=1.0+hp2.AT(k, dx);
      }
      
      riv3 = 1.0+ci2.AT(k, dx);
	  riv4 = 1.0+hh.AT(k);

      if(j != 1  &&  j != 10) {
        fsennmin.AT(x, j)=fsenn.AT(x, j)*0.8;

        if(x > 67  &&  kku != 1) {
          riv2=1.0;
          int k_vs_x = min(k-5, x-68);
          FOR(kk, 0, k_vs_x) {
            riv2=riv2*(1.0+hp2.AT(k-kk, x-kk))/(1.0+hp2.AT(k-kk, 67));
          }
          fsenn.AT(x, j)=fsenn.AT(x, j)*riv2;
        }
      }

      fsen.AT(x, j)=fsen.AT(x-1, j)*tmo*riv+fsenn.AT(x, j);

	
      if(j == 1  ||  j == 10) {
        fsenhik.AT(x, j)=fsenhik.AT(x-1, j)*tmo
                    *riv3+fsennhik.AT(x, j);
        fsenmin.AT(x, j)=fsenmin.AT(x-1, j)*tmo
                    *riv4+fsennmin.AT(x, j);
      }
    }
  }

}


void seps::simlrhnfsen60() {

  rsen.AT(60)=rsenn.AT(60);
  hnsen.AT(60, 1)=hnsenn.AT(60, 1);
  hnsen.AT(60, 2)=hnsenn.AT(60, 2);
  pshnsen.AT(60)=pshnsenn.AT(60);
  FOR(j, 1, 23) {
    if(j == 13  ||  j == 22) {
    
    } else {
      fsen.AT(60, j)=fsenn.AT(60, j);
      if(j != 1  &&  j != 10) {
        fsennmin.AT(60, j)=fsenn.AT(60, j)*0.8;
      } else {
        fsenhik.AT(60, j)=fsennhik.AT(60, j);
      }
      fsenmin.AT(60, j)=fsennmin.AT(60, j);
    }
  }
  
}
