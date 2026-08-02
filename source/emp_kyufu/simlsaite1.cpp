#include "sepscommon.h"
#include "sepslib.h"

void seps::saitesho(int x, int t) {

  double bk, bk2, bk3;
  double tmg, tmg1, tmg2, tmg3, tmf, tmo, em;

  seps::dsitk(x, t, 9, bk, bk2, bk3);
  tmg =y.AT(x, t, 2);
  tmg1=tmg*cl.AT(k, 1);
  tmg2=tmg*cl.AT(k, 2);
  tmg3=tmg*cl.AT(k, 3);
  rn.AT(x, 0, 9)=rn.AT(x, 0, 9)+tmg;
  hnn.AT(x, 0, 9, 1)=hnn.AT(x, 0, 9, 1)+tmg*tz.AT(1);
  hnn.AT(x, 0, 9, 2)=hnn.AT(x, 0, 9, 2)+tmg*tz.AT(2);
  pshnn.AT(x, 0, 9)=pshnn.AT(x, 0, 9)+tmg*pslr;

  fn.AT(x, 0, 9, 1)=fn.AT(x, 0, 9, 1)+(tmg1*ha.AT(1)+tmg2*ha.AT(2))*bk;
  fnhik.AT(x, 0, 9, 1)=fnhik.AT(x, 0, 9, 1)+(tmg1*ha.AT(1)+tmg2*ha.AT(2))*bk2;
  fnmin.AT(x, 0, 9, 1)=fnmin.AT(x, 0, 9, 1)+(tmg1*ha.AT(1)+tmg2*ha.AT(2))*bk3;
  tmo=(tmg1*ha.AT(1)+tmg2*ha.AT(2))*fl1*bd.AT(k, 14)*pslr;

  fn.AT(x, 0, 9, 14)=fn.AT(x, 0, 9, 14)+tmo;

  if((key == 12 || key == 13)&& 
      pslsi2 == 1 && k >= psly) {
  } else {
    fn.AT(x, 0, 9, 21)=fn.AT(x, 0, 9, 21)+(tmg1+tmg2)*adt.AT(2)*bd.AT(k, 21)*pslr;
    fn.AT(x, 0, 9, 4) =fn.AT(x, 0, 9, 4) +(tmg1+tmg2)*adt.AT(1)*bd.AT(k, 4) *pslr;
    fn.AT(x, 0, 9, 6) += (tmg1 + tmg2) * cadt.AT(C19(k-(int)round(ns.AT(k, x)))) * bd.AT(k, 6) * pslr;
  }

  fn.AT(x, 0, 9, 10)=fn.AT(x, 0, 9, 10)+tmg3*ha.AT(3)*bk;
  fnhik.AT(x, 0, 9, 10)=fnhik.AT(x, 0, 9, 10)+tmg3*ha.AT(3)*bk2;
  fnmin.AT(x, 0, 9, 10)=fnmin.AT(x, 0, 9, 10)+tmg3*ha.AT(3)*bk3;

  tmf=tmg3*ha.AT(3)*minb*bd.AT(k, 12)*pslr;
  
    fn.AT(x, 0, 9, 12)=fn.AT(x, 0, 9, 12)+tmf*ema.AT(s);

}

 
void seps::saiteizohiho(int x, int t) {

  double bk, bk2, bk3, bka, bkb, bka2, bkb2, bka3, bkb3;
  double tmp, tmg, tmo, tmf;


  FOR(p, 0, 1) { 
    if(p == 1 && s != 2) continue;
    int jj = p*2;
    int v = (int)(yx.AT(k, x, p));
    tmp=yx.AT(k, x, p)-(int)(yx.AT(k, x, p));
    FOR(bin1, 0, 1) {
      v=v+bin1;

      srv=0.75;
      if(v >= 65) {
        if(s2 != 2) {
          srv=srv*1.0357;
        } else {
          srv=srv*1.2019;
        }
      }

      seps::dsitk(x, t, 15, bka, bka2, bka3);
      seps::dsitk(x, t, 16, bkb, bkb2, bkb3);
      tmg=y.AT(x, t, 3)*rs.AT(s, k, x, 1+jj);
      if(bin1 == 0) {
        tmg=tmg*(1.0-tmp);
      } else {
        tmg=tmg*tmp;
      }
      rn.AT(v, 0, 11)=rn.AT(v, 0, 11)+tmg;
      hnn.AT(v, 0, 11, 1)=hnn.AT(v, 0, 11, 1)+tmg*tz.AT(1);
      hnn.AT(v, 0, 11, 2)=hnn.AT(v, 0, 11, 2)+tmg*tz.AT(2);

      fn.AT(v, 0, 11, 1)=fn.AT(v, 0, 11, 1)+tmg*max(bkb, bka)*srv;
      fnhik.AT(v, 0, 11, 1)=fnhik.AT(v, 0, 11, 1)+tmg*max(bkb2, bka2)*srv;
      fnmin.AT(v, 0, 11, 1)=fnmin.AT(v, 0, 11, 1)+tmg*max(bkb3, bka3)*srv;
      tmo=tmg*fl1*bd.AT(k, 14)*pslr;
      
      fn.AT(v, 0, 11, 14)=fn.AT(v, 0, 11, 14)+tmo;

      if((key == 12 ||  key == 13)  && 
        pslsi2 == 1 && k >= psly) {
      } else {
        fn.AT(v, 0, 11, 21)=fn.AT(v, 0, 11, 21)+tmg*adt.AT(2)*bd.AT(k, 21)*pslr;
        if(s2 != 2 && v >= 19) {
          tmf=tmg*wif*bd.AT(k, 7)*pslr;
          
          fn.AT(v, 0, 11, 7)=fn.AT(v, 0, 11, 7)+tmf;
          fn.AT(v, 0, 11, 8)=fn.AT(v, 0, 11, 8)+tmg*wife.AT(C19(k-v))*bd.AT(k, 8)*pslr;
        }
      }
      
      seps::dsitk(x, t, 17, bk, bk2, bk3);
      if((it == 1 ||  it == 2 ||  it == 3)  && 
        (x <= max(60, xrb) || (k <= KIJUN+13 && x <= 69+k-KIJUN))
      ){

        tmg=ye.AT(x, t)*rs.AT(s, k, x, 1+jj);
        if(bin1 == 0) {
          tmg=tmg*(1.0-tmp);
        } else {
          tmg=tmg*tmp;
        }
        rn.AT(v, 0, 11)=rn.AT(v, 0, 11)+tmg;
        hnn.AT(v, 0, 11, 1)=hnn.AT(v, 0, 11, 1)+tmg*tz.AT(1);
        hnn.AT(v, 0, 11, 2)=hnn.AT(v, 0, 11, 2)+tmg*tz.AT(2);

        fn.AT(v, 0, 11, 1)=fn.AT(v, 0, 11, 1)+tmg*bk*srv;
        fnhik.AT(v, 0, 11, 1)=fnhik.AT(v, 0, 11, 1)+tmg*bk2*srv;
        fnmin.AT(v, 0, 11, 1)=fnmin.AT(v, 0, 11, 1)+tmg*bk3*srv;

        if((key == 12 ||  key == 13)  && 
          pslsi2 == 1 && k >= psly) {
        } else {
          if(s2 != 2 && v >= 19) {
            tmf=tmg*wif*bd.AT(k, 7)*pslr;
            
            fn.AT(v, 0, 11, 7)=fn.AT(v, 0, 11, 7)+tmf;
            fn.AT(v, 0, 11, 8)=fn.AT(v, 0, 11, 8)+tmg*wife.AT(C19(k-v))*bd.AT(k, 8)*pslr;
          }
        }
      }
    }
  }
}


void seps::saiteizojuk(int x) {

  double tmp, tmrv, riv, riv2;
  double tmg, tmg1, tmg2, tmh1, tmh2, tmf, tmf2, tmf3;
  double tmq3, tmtu, tmo1, tmo2, tmo3;

 
  int dx = max(x, 67);
  if(x > 70 && l.AT(k-1, s, x-1) > 1.0e-6) {
    tmq3=(1.0+l.AT(k, s, x)/l.AT(k-1, s, x-1))*u.AT(k, x, 3)/2.0;
  } else {
    tmq3=0.0;
  }

  FOR(p, 0, 1) {
    if(p == 1 && s != 2) continue;
    int jj = p*2;
    int v = (int)(yx.AT(k, x, p));
    tmp=yx.AT(k, x, p)-(int)(yx.AT(k, x, p));
    FOR(bin1, 0, 1) {
      v=v+bin1;
      srv=0.75;
      if(v >= 65) {
        if(s2 != 2) {
          srv=srv*1.0357;
        } else {
          srv=srv*1.2019;
        }
      }
      if(x <= 67) {
        riv=1.0+hh.AT(k);
      } else {
        riv=1.0+ci.AT(k);
      }
      
      riv2=1.0;
      if(k-x >= -62 && k-v >= -62) {
        riv2=1.0;
      } else if(k-x >= -62 && k-v < -62) {
        riv2=riv2/0.998;
      } else if(k-x < -62 && k-v >= -62) {
        riv2=riv2*0.998;
      }

      tmrv=1.0;
      if(x > 67) {
        FOR(kk, 0, x-68) {
          if(kk <= k-5) {
            tmrv=tmrv*(1.0+hh.AT(k-kk))/(1.0+ci.AT(k-kk));
          } else if(kk <= k-2) {
            assert(-1 <= k-kk-3 && k-kk-3 <= 1);
            if(k-kk-3 == -1) tmrv=tmrv*(1.0+hh2_1999);
            if(k-kk-3 ==  0) tmrv=tmrv*(1.0+hh2_2000);
            if(k-kk-3 ==  1) tmrv=tmrv*(1.0+hh2_2001);
          }
        }
      }
      if(k-x >= -62) {
        tmrv=tmrv/0.998;
      } 

      if(v > 67) {
        FOR(kk, 0, v-68) {
          if(kk <= k-5) {
            tmrv=tmrv*(1.0+ci.AT(k-kk))/(1.0+hh.AT(k-kk));
          } else if(kk <= k-2) {
            assert(-1 <= k-kk-3 && k-kk-3 <= 1);
            if(k-kk-3 == -1) tmrv=tmrv/(1.0+hh2_1999);
            if(k-kk-3 ==  0) tmrv=tmrv/(1.0+hh2_2000);
            if(k-kk-3 ==  1) tmrv=tmrv/(1.0+hh2_2001);
          }
        }
      }
      if(k-v >= -62) {
        tmrv=tmrv*0.998;
      } 

      if(x >= 45) {
        tmg =0.0;
        tmg1=0.0;
        tmg2=0.0;
        tmh1=0.0;
        tmh2=0.0;
        tmf =0.0;
        tmf2=0.0;
        tmf3=0.0;
        tmo1=0.0;
        tmo2=0.0;
        tmo3=0.0;
        
        FOR(xx, 0, 15) {
          tmg1=tmg1+pshn.AT(x-1, xx, 1);
          tmg2=tmg2+r.AT(x-1, xx, 1);
          tmg=tmg+r.AT(x-1, xx, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh1=tmh1+hn.AT(x-1, xx, 1, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh2=tmh2+hn.AT(x-1, xx, 1, 2)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);

          tmf =tmf +f.AT(x-1, xx, 1, 1)*riv
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*tmrv;
          tmf2=tmf2+f_hik.AT(x-1, xx, 1, 1)*(1.0+ci2.AT(k, dx))
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
          tmf3=tmf3+f_min.AT(x-1, xx, 1, 1)*(1.0+hh.AT(k))
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
          if(pseid == 0 && x >= 70+k-KIJUN){
            tmg1=tmg1+pshn.AT(x-1, xx, 2);
            tmg2=tmg2+r.AT(x-1, xx, 2);
            tmg=tmg+r.AT(x-1, xx, 2)*tmq3*rs.AT(s, k, x, 1+jj);
            tmh1=tmh1+hn.AT(x-1, xx, 2, 1)*tmq3*rs.AT(s, k, x, 1+jj);
            tmh2=tmh2+hn.AT(x-1, xx, 2, 2)*tmq3*rs.AT(s, k, x, 1+jj);

            tmf =tmf +f.AT(x-1, xx, 2, 1)*riv
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*tmrv;
            tmf2=tmf2+f_hik.AT(x-1, xx, 2, 1)*(1.0+ci2.AT(k, dx))
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*riv2;
            tmf3=tmf3+f_min.AT(x-1, xx, 2, 1)*(1.0+hh.AT(k))
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*riv2;
          }
        }
        tmg1=tmg1+pshn.AT(x-1, 0, 5);
        tmg2=tmg2+r.AT(x-1, 0, 5);
        tmg =tmg +r.AT(x-1, 0, 5)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
        tmh1=tmh1+hn.AT(x-1, 0, 5, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
        tmh2=tmh2+hn.AT(x-1, 0, 5, 2)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);

        tmf =tmf +f.AT(x-1, 0, 5, 1)*riv
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*tmrv;
        tmf2=tmf2+f_hik.AT(x-1, 0, 5, 1)*(1.0+ci2.AT(k, dx))
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
        tmf3=tmf3+f_min.AT(x-1, 0, 5, 1)*(1.0+hh.AT(k))
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
        if(x >= 61 && x <= 70) {
          tmg1=tmg1+pshnsen.AT(x-1);
          tmg2=tmg2+rsen.AT(x-1);
          tmg=tmg+rsen.AT(x-1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh1=tmh1+hnsen.AT(x-1, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh2=tmh2+hnsen.AT(x-1, 2)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);

          tmf =tmf +fsen.AT(x-1, 1)*riv*srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*tmrv;
          tmf2=tmf2+fsenhik.AT(x-1, 1)*(1.0+ci2.AT(k, dx))
                            *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
          tmf3=tmf3+fsenmin.AT(x-1, 1)*(1.0+hh.AT(k))
                            *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
        }
        if(key == 12 && 
          k >= psly && tmg2 > 1.0e-6) {
          pslr=tmg1/tmg2;
        } else {
          pslr=1.0;
        }
        if(bin1 == 0) {
          tmg =tmg *(1.0-tmp);
          tmh1=tmh1*(1.0-tmp);
          tmh2=tmh2*(1.0-tmp);
          tmf =tmf *(1.0-tmp);
          tmf2=tmf2*(1.0-tmp);
          tmf3=tmf3*(1.0-tmp);
        } else {
          tmg =tmg *tmp;
          tmh1=tmh1*tmp;
          tmh2=tmh2*tmp;
          tmf =tmf *tmp;
          tmf2=tmf2*tmp;
          tmf3=tmf3*tmp;
        }
        rn.AT(v, 0, 11)=rn.AT(v, 0, 11)+tmg;
        hnn.AT(v, 0, 11, 1)=hnn.AT(v, 0, 11, 1)+tmh1;
        hnn.AT(v, 0, 11, 2)=hnn.AT(v, 0, 11, 2)+tmh2;

        fn.AT(v, 0, 11, 1)=fn.AT(v, 0, 11, 1)+tmf;
        fnhik.AT(v, 0, 11, 1)=fnhik.AT(v, 0, 11, 1)+tmf2;
        fnmin.AT(v, 0, 11, 1)=fnmin.AT(v, 0, 11, 1)+tmf3;
        tmo1=tmg*fl1*bd.AT(k, 14)*pslr;
       
        fn.AT(v, 0, 11, 14)=fn.AT(v, 0, 11, 14)+tmo1;

        if((key == 12 ||  key == 13)  && 
          pslsi2 == 1 && k >= psly) {
        } else {
          fn.AT(v, 0, 11, 21)=fn.AT(v, 0, 11, 21)+tmg*adt.AT(2)*bd.AT(k, 21)*pslr;
          if(s2 != 2 && v >= 19) {
            tmo2=tmg*wif*bd.AT(k, 7)*pslr;
           
            fn.AT(v, 0, 11, 7)=fn.AT(v, 0, 11, 7)+tmo2;
            fn.AT(v, 0, 11, 8)=fn.AT(v, 0, 11, 8)+tmg*wife.AT(C19(k-v))*bd.AT(k, 8)*pslr;
          }
        }
        tmg =0.0;
        tmh1=0.0;
        tmh2=0.0;
        tmf =0.0;
        tmf2=0.0;
        tmf3=0.0;
        tmtu=0.0;
        tmo1=0.0;
        tmo2=0.0;
        tmo3=0.0;
        
        FOR(xx, 0, 15) {
          tmg=tmg+r.AT(x-1, xx, 3)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh1=tmh1+hn.AT(x-1, xx, 3, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmh2=tmh2+hn.AT(x-1, xx, 3, 2)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmtu=tmtu+f.AT(x-1, xx, 3, 4)/(adt.AT(1)*bd.AT(k-1, 4))
                    *q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
          tmf =tmf +f.AT(x-1, xx, 3, 1)*riv
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*tmrv;
          tmf2=tmf2+f_hik.AT(x-1, xx, 3, 1)*(1.0+ci2.AT(k, dx))
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
          tmf3=tmf3+f_min.AT(x-1, xx, 3, 1)*(1.0+hh.AT(k))
                    *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
          if(pseid == 0 && x >= 70+k-KIJUN){
            tmg=tmg+r.AT(x-1, xx, 4)*tmq3*rs.AT(s, k, x, 1+jj);
            tmh1=tmh1+hn.AT(x-1, xx, 4, 1)*tmq3*rs.AT(s, k, x, 1+jj);
            tmh2=tmh2+hn.AT(x-1, xx, 4, 2)*tmq3*rs.AT(s, k, x, 1+jj);

            tmf =tmf +f.AT(x-1, xx, 4, 1)*riv
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*tmrv;
            tmf2=tmf2+f_hik.AT(x-1, xx, 4, 1)*(1.0+ci2.AT(k, dx))
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*riv2;
            tmf3=tmf3+f_min.AT(x-1, xx, 4, 1)*(1.0+hh.AT(k))
                      *srv*tmq3*rs.AT(s, k, x, 1+jj)*riv2;
          }
        }
        tmg=tmg+r.AT(x-1, 0, 7)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
        tmh1=tmh1+hn.AT(x-1, 0, 7, 1)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);
        tmh2=tmh2+hn.AT(x-1, 0, 7, 2)*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj);

        tmf=tmf+f.AT(x-1, 0, 7, 1)*riv
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*tmrv;
        tmf2=tmf2+f_hik.AT(x-1, 0, 7, 1)*(1.0+ci2.AT(k, dx))
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
        tmf3=tmf3+f_min.AT(x-1, 0, 7, 1)*(1.0+hh.AT(k))
                  *srv*q.AT(k, x, 1)*rs.AT(s, k, x, 1+jj)*riv2;
        if(bin1 == 0) {
          tmg =tmg *(1.0-tmp);
          tmh1=tmh1*(1.0-tmp);
          tmh2=tmh2*(1.0-tmp);
          tmf =tmf *(1.0-tmp);
          tmf2=tmf2*(1.0-tmp);
          tmf3=tmf3*(1.0-tmp);
          tmtu=tmtu*(1.0-tmp);
        } else {
          tmg =tmg *tmp;
          tmh1=tmh1*tmp;
          tmh2=tmh2*tmp;
          tmf =tmf *tmp;
          tmf2=tmf2*tmp;
          tmf3=tmf3*tmp;
          tmtu=tmtu*tmp;
        }
        rn.AT(v, 0, 11)=rn.AT(v, 0, 11)+tmg;
        hnn.AT(v, 0, 11, 1)=hnn.AT(v, 0, 11, 1)+tmh1;
        hnn.AT(v, 0, 11, 2)=hnn.AT(v, 0, 11, 2)+tmh2;

        fn.AT(v, 0, 11, 1)=fn.AT(v, 0, 11, 1)+tmf;
        fnhik.AT(v, 0, 11, 1)=fnhik.AT(v, 0, 11, 1)+tmf2;
        fnmin.AT(v, 0, 11, 1)=fnmin.AT(v, 0, 11, 1)+tmf3;
		tmo1=tmtu*fl1*bd.AT(k, 14)*pslr;
		
        fn.AT(v, 0, 11, 14)=fn.AT(v, 0, 11, 14)+tmo1;
        if((key == 12 ||  key == 13)  && 
          pslsi2 == 1 && k >= psly) {
        } else {
          fn.AT(v, 0, 11, 21)=fn.AT(v, 0, 11, 21)+tmtu*adt.AT(2)*bd.AT(k, 21)*pslr;
          if(s2 != 2 && v >= 19) {
            tmo2=tmtu*wif*bd.AT(k, 7)*pslr;
            
            fn.AT(v, 0, 11, 7)=fn.AT(v, 0, 11, 7)+tmo2;
            fn.AT(v, 0, 11, 8)=fn.AT(v, 0, 11, 8)+tmtu*wife.AT(C19(k-v))*bd.AT(k, 8)*pslr;
          }
        }
      }
      if(key == 12 && 
        k >= psly && (r.AT(x-1, 0, 9)+r.AT(x-1, 0, 10)) > 1.0e-6) {
        pslr=(pshn.AT(x-1, 0, 9)+pshn.AT(x-1, 0, 10))/(r.AT(x-1, 0, 9)+r.AT(x-1, 0, 10));
      } else {
        pslr=1.0;
      }
      tmg = r.AT(x-1, 0, 9) *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*(cl.AT(k, 1)+cl.AT(k, 2))
          +r.AT(x-1, 0, 10)*q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*(cl2.AT(k, 1)+cl2.AT(k, 2));
      tmh1= hn.AT(x-1, 0, 9, 1) *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)
            *(cl.AT(k, 1)+cl.AT(k, 2))
          +hn.AT(x-1, 0, 10, 1)*q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)
            *(cl2.AT(k, 1)+cl2.AT(k, 2));
      tmh2= hn.AT(x-1, 0, 9, 2) *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)
            *(cl.AT(k, 1)+cl.AT(k, 2))
          +hn.AT(x-1, 0, 10, 2)*q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)
            *(cl2.AT(k, 1)+cl2.AT(k, 2));

      if(cl.AT(k, 1)+cl.AT(k, 2) > 1.0e-6) {
        tmf= f.AT(x-1, 0, 9, 1)*q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*riv*srv
            *(cl.AT(k, 1)+cl.AT(k, 2))/(cl.AT(k, 1)*ha.AT(1)+cl.AT(k, 2)*ha.AT(2))*tmrv
            +f.AT(x-1, 0, 10, 1)*prb/pra*25.0/20.0
            *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*riv*srv*(cl2.AT(k, 1)+cl2.AT(k, 2))
            /(cl2.AT(k, 1)*hb.AT(1)+cl2.AT(k, 2)*hb.AT(2))*tmrv;

        tmf2= f_hik.AT(x-1, 0, 9, 1)*(1.0+ci2.AT(k, dx))*q.AT(k, x, 2)
              *rs.AT(s, k, x, 2+jj)*srv
              *(cl.AT(k, 1)+cl.AT(k, 2))/(cl.AT(k, 1)*ha.AT(1)+cl.AT(k, 2)*ha.AT(2))*riv2
          +f_hik.AT(x-1, 0, 10, 1)*(1.0+ci2.AT(k, dx))*prb/pra*25.0/20.0
            *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*srv*riv2
            *(cl2.AT(k, 1)+cl2.AT(k, 2))/(cl2.AT(k, 1)*hb.AT(1)+cl2.AT(k, 2)*hb.AT(2));

        tmf3= f_min.AT(x-1, 0, 9, 1)*(1.0+hh.AT(k))*q.AT(k, x, 2)
              *rs.AT(s, k, x, 2+jj)*srv
              *(cl.AT(k, 1)+cl.AT(k, 2))/(cl.AT(k, 1)*ha.AT(1)+cl.AT(k, 2)*ha.AT(2))*riv2
            +f_min.AT(x-1, 0, 10, 1)*(1.0+hh.AT(k))*prb/pra*25.0/20.0
                  *q.AT(k, x, 2)*rs.AT(s, k, x, 2+jj)*srv*(cl2.AT(k, 1)+cl2.AT(k, 2))
                  /(cl2.AT(k, 1)*hb.AT(1)+cl2.AT(k, 2)*hb.AT(2))*riv2;
      } else {
        tmf=0.0;
      }
      if(bin1 == 0) {
        tmg =tmg *(1.0-tmp);
        tmh1=tmh1*(1.0-tmp);
        tmh2=tmh2*(1.0-tmp);
        tmf =tmf *(1.0-tmp);
        tmf2=tmf2*(1.0-tmp);
        tmf3=tmf3*(1.0-tmp);
      } else {
        tmg =tmg *tmp;
        tmh1=tmh1*tmp;
        tmh2=tmh2*tmp;
        tmf =tmf *tmp;
        tmf2=tmf2*tmp;
        tmf3=tmf3*tmp;
      }
      rn.AT(v, 0, 11)=rn.AT(v, 0, 11)+tmg;
      hnn.AT(v, 0, 11, 1)=hnn.AT(v, 0, 11, 1)+tmh1;
      hnn.AT(v, 0, 11, 2)=hnn.AT(v, 0, 11, 2)+tmh2;

      fn.AT(v, 0, 11, 1)=fn.AT(v, 0, 11, 1)+tmf;
      fnhik.AT(v, 0, 11, 1)=fnhik.AT(v, 0, 11, 1)+tmf2;
      fnmin.AT(v, 0, 11, 1)=fnmin.AT(v, 0, 11, 1)+tmf3;

      if((key == 12 ||  key == 13)  && 
        pslsi2 == 1 && k >= psly) {
      } else {
        if(s2 != 2 && v >= 19) {
          tmo3=tmg*wif*bd.AT(k, 7)*pslr;
          
          fn.AT(v, 0, 11, 7)=fn.AT(v, 0, 11, 7)+tmo3;
          fn.AT(v, 0, 11, 8)=fn.AT(v, 0, 11, 8)+tmg*wife.AT(C19(k-v))*bd.AT(k, 8)*pslr;
        }
      }
    }
  }
}