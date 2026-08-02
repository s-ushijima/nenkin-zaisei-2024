#include "sepscommon.h"
#include "sepslib.h"
namespace sst = sepsstd;

void seps::stat(void) {

  double tmp;
  v1_t   kk = VEC(double, 115);
  v1_t   kk2 = VEC(double, 115);


    REV_FOR(k, KE, KIJUN) {
      FOR(s, 1, 3) {
        FOR(i, 1, 13) {
          REV_FOR(x, 115, 0) {
            if(x == 0) {
              d3x.AT(k, x, s, i, 0)=d3x.AT(k, x, s, i, 0)/2.0;
              if(nenbe65 == 1) {
                d3x.AT(k, x, s, i, 34)=d3x.AT(k, x, s, i, 34)/2.0;
              }
            } else {
              d3x.AT(k, x, s, i, 0)=(d3x.AT(k-1, x-1, s, i, 0)
                                    +d3x.AT(k, x, s, i, 0))/2.0;
              if(nenbe65 == 1) {
                d3x.AT(k, x, s, i, 34)=(d3x.AT(k-1, x-1, s, i, 34)
                                    +d3x.AT(k, x, s, i, 34))/2.0;
              }
            }
          }
          if(nenbeex == 0) {
            FOR(x, 0, xa - 2) {
              d3x.AT(k, xa-1, s, i, 0)=d3x.AT(k, xa-1, s, i, 0)+d3x.AT(k, x, s, i, 0);
              d3x.AT(k, x, s, i, 0)=0.0;

              d3xs.AT(k, xa-1, s, i, 0)=d3xs.AT(k, xa-1, s, i, 0)+d3xs.AT(k, x, s, i, 0);
              d3xs.AT(k, x, s, i, 0)=0.0;
              if(nenbe65 == 1) {
                d3x.AT(k, xa-1, s, i, 34)=d3x.AT(k, xa-1, s, i, 34)+d3x.AT(k, x, s, i, 34);
                d3x.AT(k, x, s, i, 34)=0.0;

                d3xs.AT(k, xa-1, s, i, 34)=d3xs.AT(k, xa-1, s, i, 34)
                                    +d3xs.AT(k, x, s, i, 34);
                d3xs.AT(k, x, s, i, 34)=0.0;
              }
            }
          }
          FOR(j, 0, 58) {
            if(j == 0  ||  j == 34  || 
              (nenbe65 == 0 && j >= 35)) continue;
            tmp=0.0;
            FOR(x, 0, 115) {
              tmp += d3x.AT(k, x, s, i, j);
            }
            if(tmp < 1.0e-6) {
              FOR(x, 0, 115) {
                d3x.AT(k, x, s, i, j)=0.0;
              }
            }
            if(nenbeex == 0) {
              FOR(x, 0, xa - 2) {
                d3x.AT(k, xa-1, s, i, j)=d3x.AT(k, xa-1, s, i, j)+d3x.AT(k, x, s, i, j);
                d3x.AT(k, x, s, i, j)=0.0;

                d3xs.AT(k, xa-1, s, i, j)=d3xs.AT(k, xa-1, s, i, j)+d3xs.AT(k, x, s, i, j);
                d3xs.AT(k, x, s, i, j)=0.0;
              }
            }
          }
          FOR(j, 0, 58) {
            if(nenbeex == 0) {
              FOR(x, xa - 1, 115) {
                d3x.AT(k, x, s, 0, j)=d3x.AT(k, x, s, 0, j)+d3x.AT(k, x, s, i, j);
                d3x.AT(k, x, 0, i, j)=d3x.AT(k, x, 0, i, j)+d3x.AT(k, x, s, i, j);
                d3x.AT(k, x, 0, 0, j)=d3x.AT(k, x, 0, 0, j)+d3x.AT(k, x, s, i, j);

                d3xs.AT(k, x, s, 0, j)=d3xs.AT(k, x, s, 0, j)+d3xs.AT(k, x, s, i, j);
                d3xs.AT(k, x, 0, i, j)=d3xs.AT(k, x, 0, i, j)+d3xs.AT(k, x, s, i, j);
                d3xs.AT(k, x, 0, 0, j)=d3xs.AT(k, x, 0, 0, j)+d3xs.AT(k, x, s, i, j);
              }
            } else if(nenbeex == 1) {
              FOR(x, 0, 115) {
                d3x.AT(k, x, s, 0, j)=d3x.AT(k, x, s, 0, j)+d3x.AT(k, x, s, i, j);
                d3x.AT(k, x, 0, i, j)=d3x.AT(k, x, 0, i, j)+d3x.AT(k, x, s, i, j);
                d3x.AT(k, x, 0, 0, j)=d3x.AT(k, x, 0, 0, j)+d3x.AT(k, x, s, i, j);

                d3xs.AT(k, x, s, 0, j)=d3xs.AT(k, x, s, 0, j)+d3xs.AT(k, x, s, i, j);
                d3xs.AT(k, x, 0, i, j)=d3xs.AT(k, x, 0, i, j)+d3xs.AT(k, x, s, i, j);
                d3xs.AT(k, x, 0, 0, j)=d3xs.AT(k, x, 0, 0, j)+d3xs.AT(k, x, s, i, j);
              }
            }
          }
          sst::subc1(kk, 0,115);
          sst::subc1(kk2, 0,115);
          FOR(x, 0, 115) {
            if(s != 3) {
              kk.AT(x)=ee.AT(1);
            } else {
              kk.AT(x)=ee.AT(2);
            }
            if((i == 2  ||  i == 4  ||  i == 6  ||  i == 8)  && 
              x < 65) {
              kk2.AT(x)=kk.AT(x);
              kk.AT(x)=0.0;
            } else {
              kk2.AT(x)=0.0;
            }
          }
          FOR(x, 0, 115) {
            kfprx.AT(k, x, s, i, 0)=(d3x.AT(k, x, s, i, 13)+d3x.AT(k, x, s, i, 14)
                            +d3x.AT(k, x, s, i, 15)+d3x.AT(k, x, s, i, 16)
                            +d3x.AT(k, x, s, i, 17)+d3x.AT(k, x, s, i, 18))*kk.AT(x);
          }
          if(nenbeex == 0) {
            FOR(x, 0, xa - 2) {
              kfprx.AT(k, xa-1, s, i, 0) += kfprx.AT(k, x, s, i, 0);
              kfprx.AT(k, x, s, i, 0)=0.0;
            }
          }
          FOR(x, 0, 115) {
            kfprx.AT(k, x, s, i, 1) = d3x.AT(k, x, s, i, 13) * kk.AT(x);
          }
          if(nenbeex == 0) {
            FOR(x, 0, xa - 2) {
              kfprx.AT(k, xa-1, s, i, 1) += kfprx.AT(k, x, s, i, 1);
              kfprx.AT(k, x, s, i, 1) = 0.0;
            }
          }
          FOR(x, 0, 115) {
            kfprx.AT(k, x, s, i, 2) = kfprx.AT(k, x, s, i, 0) - kfprx.AT(k, x, s, i, 1);
          }
          if(nenbeex == 0) {
            FOR(x, 0, xa - 2) {
              kfprx.AT(k, xa-1, s, i, 2) += kfprx.AT(k, x, s, i, 2);
              kfprx.AT(k, x, s, i, 2) = 0.0;
            }
          }
          if(i == 2  ||  i == 4  ||  i == 6  ||  i == 8) {
            FOR(x, 0, 64) {
              kfprx.AT(k, x, s, i, 0) = 0.0;
              kfprx.AT(k, x, s, i, 1) = 0.0;
              kfprx.AT(k, x, s, i, 2) = 0.0;
            }
          }
          if(nenbe65 == 1) {
            FOR(x, 0, 115) {
              kfprx.AT(k, x, s, i, 3)=(d3x.AT(k, x, s, i, 53)+d3x.AT(k, x, s, i, 54)
                              +d3x.AT(k, x, s, i, 55)+d3x.AT(k, x, s, i, 56)
                              +d3x.AT(k, x, s, i, 57)+d3x.AT(k, x, s, i, 58))
                                                              *kk.AT(x);
              kfprx.AT(k, x, s, i, 4)=d3x.AT(k, x, s, i, 53)*kk.AT(x);
              kfprx.AT(k, x, s, i, 5)=kfprx.AT(k, x, s, i, 3)-kfprx.AT(k, x, s, i, 4);
            }
            if(nenbeex == 0) {
              FOR(x, 0, xa - 2) {
                kfprx.AT(k, xa-1, s, i, 3)
                                =kfprx.AT(k, xa-1, s, i, 3)+kfprx.AT(k, x, s, i, 3);
                kfprx.AT(k, xa-1, s, i, 4)
                                =kfprx.AT(k, xa-1, s, i, 4)+kfprx.AT(k, x, s, i, 4);
                kfprx.AT(k, xa-1, s, i, 5)
                                =kfprx.AT(k, xa-1, s, i, 5)+kfprx.AT(k, x, s, i, 5);
                kfprx.AT(k, x, s, i, 3) =0.0;
                kfprx.AT(k, x, s, i, 4) =0.0;
                kfprx.AT(k, x, s, i, 5) =0.0;
              }
            }
          }
          if(nenbe65 == 1) {
            FOR(x, 0, 115) {
              kfprx.AT(k, x, s, i, 6)=(d3x.AT(k, x, s, i, 53)+d3x.AT(k, x, s, i, 54)
                              +d3x.AT(k, x, s, i, 55)+d3x.AT(k, x, s, i, 56)
                              +d3x.AT(k, x, s, i, 57)+d3x.AT(k, x, s, i, 58))
                                                            *kk2.AT(x);
              kfprx.AT(k, x, s, i, 7)=d3x.AT(k, x, s, i, 53)*kk2.AT(x);
              kfprx.AT(k, x, s, i, 8)=kfprx.AT(k, x, s, i, 6)-kfprx.AT(k, x, s, i, 7);
            }
            if(nenbeex == 0) {
              FOR(x, 0, xa - 2) {
                kfprx.AT(k, xa-1, s, i, 6)
                                =kfprx.AT(k, xa-1, s, i, 6)+kfprx.AT(k, x, s, i, 6);
                kfprx.AT(k, xa-1, s, i, 7)
                                =kfprx.AT(k, xa-1, s, i, 7)+kfprx.AT(k, x, s, i, 7);
                kfprx.AT(k, xa-1, s, i, 8)
                                =kfprx.AT(k, xa-1, s, i, 8)+kfprx.AT(k, x, s, i, 8);
                kfprx.AT(k, x, s, i, 6) = 0.0;
                kfprx.AT(k, x, s, i, 7) = 0.0;
                kfprx.AT(k, x, s, i, 8) = 0.0;
              }
            }
          }
          FOR(j, 0, 8) {
            if(nenbe65 == 0 && j >= 3) continue;
            if(nenbeex == 0) {
              FOR(x, xa - 1, 115) {
                kfprx.AT(k, x, s, 0, j)=kfprx.AT(k, x, s, 0, j)+kfprx.AT(k, x, s, i, j);
                kfprx.AT(k, x, 0, i, j)=kfprx.AT(k, x, 0, i, j)+kfprx.AT(k, x, s, i, j);
                kfprx.AT(k, x, 0, 0, j)=kfprx.AT(k, x, 0, 0, j)+kfprx.AT(k, x, s, i, j);
              }
            } else if(nenbeex == 1) {
              FOR(x, 0, 115) {
                kfprx.AT(k, x, s, 0, j)=kfprx.AT(k, x, s, 0, j)+kfprx.AT(k, x, s, i, j);
                kfprx.AT(k, x, 0, i, j)=kfprx.AT(k, x, 0, i, j)+kfprx.AT(k, x, s, i, j);
                kfprx.AT(k, x, 0, 0, j)=kfprx.AT(k, x, 0, 0, j)+kfprx.AT(k, x, s, i, j);
              }
            }
          }
        }
      }
    }


  FOR(s, 1, 3) REV_FOR(k, KE, KIJUN + 1) {
    aal.AT(k, s)=a.AT(k, s)+aiku.AT(k, s);
    
   if(pseid == 1  ||  pseid == 4) {
      a.AT(k, s)   =(5.0*a.AT(k-1, s)   +7.0*a.AT(k, s)   )/12.0;
      aiku.AT(k, s)=(5.0*aiku.AT(k-1, s)+7.0*aiku.AT(k, s))/12.0;
      a60.AT(k, s)=(5.0*a60.AT(k-1, s)+7.0*a60.AT(k, s))/12.0;
      a65.AT(k, s)=(5.0*a65.AT(k-1, s)+7.0*a65.AT(k, s))/12.0;
      a70.AT(k, s)=(5.0*a70.AT(k-1, s)+7.0*a70.AT(k, s))/12.0;
      a75.AT(k, s)=(5.0*a75.AT(k-1, s)+7.0*a75.AT(k, s))/12.0;
      a85.AT(k, s)=(5.0*a85.AT(k-1, s)+7.0*a85.AT(k, s))/12.0;
    } 
    else if(pseid == 0 && (k == partyr3 || k == partyr4)) {
      a.AT(k, s)   =(6.0*a.AT(k-1, s)   +6.0*adum.AT(k, s)   )/12.0;
      aiku.AT(k, s)=(6.0*aiku.AT(k-1, s)+6.0*aikudum.AT(k, s))/12.0;
      a60.AT(k, s)=(6.0*a60.AT(k-1, s)+6.0*a60dum.AT(k, s))/12.0;
      a65.AT(k, s)=(6.0*a65.AT(k-1, s)+6.0*a65dum.AT(k, s))/12.0;
      a70.AT(k, s)=(6.0*a70.AT(k-1, s)+6.0*a70dum.AT(k, s))/12.0;
      a75.AT(k, s)=(6.0*a75.AT(k-1, s)+6.0*a75dum.AT(k, s))/12.0;
      a85.AT(k, s)=(6.0*a85.AT(k-1, s)+6.0*a85dum.AT(k, s))/12.0;
      apart.AT(k, s)=(6.0*apart.AT(k-1, s)+6.0*apart.AT(k, s))/12.0;
      aikupart.AT(k, s)=(6.0*aikupart.AT(k-1, s)+6.0*aikupart.AT(k, s))/12.0;
      a60part.AT(k, s)=(6.0*a60part.AT(k-1, s)+6.0*a60part.AT(k, s))/12.0;
      a65part.AT(k, s)=(6.0*a65part.AT(k-1, s)+6.0*a65part.AT(k, s))/12.0;
      a70part.AT(k, s)=(6.0*a70part.AT(k-1, s)+6.0*a70part.AT(k, s))/12.0;
      a75part.AT(k, s)=(6.0*a75part.AT(k-1, s)+6.0*a75part.AT(k, s))/12.0;
      a85part.AT(k, s)=(6.0*a85part.AT(k-1, s)+6.0*a85part.AT(k, s))/12.0;
      apart.AT(k-1, s)=0.0;
      aikupart.AT(k-1, s)=0.0;
      a60part.AT(k-1, s)=0.0;
      a65part.AT(k-1, s)=0.0;
      a70part.AT(k-1, s)=0.0;
      a75part.AT(k-1, s)=0.0;
      a85part.AT(k-1, s)=0.0;
    } 
    else {
      a.AT(k, s)   =(6.0*a.AT(k-1, s)   +6.0*a.AT(k, s)   )/12.0;
      aiku.AT(k, s)=(6.0*aiku.AT(k-1, s)+6.0*aiku.AT(k, s))/12.0;
      a60.AT(k, s)=(6.0*a60.AT(k-1, s)+6.0*a60.AT(k, s))/12.0;
      a65.AT(k, s)=(6.0*a65.AT(k-1, s)+6.0*a65.AT(k, s))/12.0;
      a70.AT(k, s)=(6.0*a70.AT(k-1, s)+6.0*a70.AT(k, s))/12.0;
      a75.AT(k, s)=(6.0*a75.AT(k-1, s)+6.0*a75.AT(k, s))/12.0;
      a85.AT(k, s)=(6.0*a85.AT(k-1, s)+6.0*a85.AT(k, s))/12.0;
    }


    ap.AT(k, s)=(ap.AT(k-1, s)+ap.AT(k, s))/2.0;
    appart.AT(k, s)=(appart.AT(k-1, s)+appart.AT(k, s))/2.0;
    at.AT(k, s)=(at.AT(k-1, s)+at.AT(k, s))/2.0;
    
    
      ap65.AT(k, s)=(ap65.AT(k-1, s)+ap65.AT(k, s))/2.0;
      ap70.AT(k, s)=(ap70.AT(k-1, s)+ap70.AT(k, s))/2.0;
      ap75.AT(k, s)=(ap75.AT(k-1, s)+ap75.AT(k, s))/2.0;
      ap85.AT(k, s)=(ap85.AT(k-1, s)+ap85.AT(k, s))/2.0;
      appart65.AT(k, s)=(appart65.AT(k-1, s)+appart65.AT(k, s))/2.0;
      appart70.AT(k, s)=(appart70.AT(k-1, s)+appart70.AT(k, s))/2.0;
      appart75.AT(k, s)=(appart75.AT(k-1, s)+appart75.AT(k, s))/2.0;
      appart85.AT(k, s)=(appart85.AT(k-1, s)+appart85.AT(k, s))/2.0;
  }

  FOR(s, 0, 3) {
    a.AT(KIJUN, s) =0.0;
    ap.AT(KIJUN, s)=0.0;
    appart.AT(KIJUN, s)=0.0;
    at.AT(KIJUN, s)=0.0;
    aiku.AT(KIJUN, s)=0.0;
    a60.AT(KIJUN, s) =0.0;
    a65.AT(KIJUN, s) =0.0;
    a70.AT(KIJUN, s) =0.0;
    a75.AT(KIJUN, s) =0.0;
    a85.AT(KIJUN, s) =0.0;
    ap65.AT(KIJUN, s)=0.0;
    appart65.AT(KIJUN, s)=0.0;
    ap70.AT(KIJUN, s)=0.0;
    appart70.AT(KIJUN, s)=0.0;
    ap75.AT(KIJUN, s)=0.0;
    appart75.AT(KIJUN, s)=0.0;
    ap85.AT(KIJUN, s)=0.0;
    appart85.AT(KIJUN, s)=0.0;
    
    
    FOR(x, 15, 85) FOR(t, 0, 70) {
      gee.AT(KIJUN, s, x, t) = 0.0;
      geept.AT(KIJUN, s, x, t) = 0.0;
      
    }
  }


  REV_FOR(k, KE, KIJUN + 1) {
    a.AT(k, 0)=a.AT(k, 1)+a.AT(k, 2)+a.AT(k, 3);

    aal.AT(k, 0)=aal.AT(k, 1)+aal.AT(k, 2)+aal.AT(k, 3);

    aiku.AT(k, 0)=aiku.AT(k, 1)+aiku.AT(k, 2)+aiku.AT(k, 3);

    ap.AT(k, 0)=ap.AT(k, 1)+ap.AT(k, 2)+ap.AT(k, 3);
    appart.AT(k, 0)=appart.AT(k, 1)+appart.AT(k, 2)+appart.AT(k, 3);

    at.AT(k, 0)=at.AT(k, 1)+at.AT(k, 2)+at.AT(k, 3);

    ap65.AT(k, 0) = ap65.AT(k, 1)+ap65.AT(k, 2)+ap65.AT(k, 3);
    ap70.AT(k, 0) = ap70.AT(k, 1)+ap70.AT(k, 2)+ap70.AT(k, 3);
    ap75.AT(k, 0) = ap75.AT(k, 1)+ap75.AT(k, 2)+ap75.AT(k, 3);
    ap85.AT(k, 0) = ap85.AT(k, 1)+ap85.AT(k, 2)+ap85.AT(k, 3);
    appart65.AT(k, 0) = appart65.AT(k, 1)+appart65.AT(k, 2)+appart65.AT(k, 3);
    appart70.AT(k, 0) = appart70.AT(k, 1)+appart70.AT(k, 2)+appart70.AT(k, 3);
    appart75.AT(k, 0) = appart75.AT(k, 1)+appart75.AT(k, 2)+appart75.AT(k, 3);
    appart85.AT(k, 0) = appart85.AT(k, 1)+appart85.AT(k, 2)+appart85.AT(k, 3);
    a60.AT(k, 0) = a60.AT(k, 1) +a60.AT(k, 2)+a60.AT(k, 3);
    a65.AT(k, 0) = a65.AT(k, 1) +a65.AT(k, 2)+a65.AT(k, 3);
    a70.AT(k, 0) = a70.AT(k, 1) +a70.AT(k, 2)+a70.AT(k, 3);
    a75.AT(k, 0) = a75.AT(k, 1) +a75.AT(k, 2)+a75.AT(k, 3);
    a85.AT(k, 0) = a85.AT(k, 1) +a85.AT(k, 2)+a85.AT(k, 3);

    apart   .AT(k, 0) = apart.AT(k, 1) + apart.AT(k, 2) + apart.AT(k, 3);
    aikupart.AT(k, 0) = aikupart.AT(k, 1) + aikupart.AT(k, 2)+ aikupart.AT(k, 3);
    a60part .AT(k, 0) = a60part.AT(k, 1) + a60part.AT(k, 2) + a60part.AT(k, 3);
    a65part .AT(k, 0) = a65part.AT(k, 1) + a65part.AT(k, 2) + a65part.AT(k, 3);
    a70part .AT(k, 0) = a70part.AT(k, 1) + a70part.AT(k, 2) + a70part.AT(k, 3);
    a75part .AT(k, 0) = a75part.AT(k, 1) + a75part.AT(k, 2) + a75part.AT(k, 3);
    a85part .AT(k, 0) = a85part.AT(k, 1) + a85part.AT(k, 2) + a85part.AT(k, 3);

    FOR(x, 15, 85) FOR(t, 0, 70) {
      gee.AT(k, 0, x, t)   = gee.AT(k, 1, x, t) + gee.AT(k, 2, x, t) + gee.AT(k, 3, x, t);
      geept.AT(k, 0, x, t) = geept.AT(k, 1, x, t) + geept.AT(k, 2, x, t) + geept.AT(k, 3, x, t);
      
    }
    
    
  }


}