#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <cassert>
namespace sst = sepsstd;

void seps::shkejuk(int i, int x, int xx) {

  double tmx, tmy, tmy2, tmz;
  double ab, aba, abb, kk;
  v1_t tmp = VEC(double, 24); 

  FOR(jj, 1, 2) {
    if(s <= 3 || (5 <= i && i <= 10) || 12 <= i) {
      if(jj == 1) tmp.AT(0) = t4k.AT(x, xx, i);
      if(jj == 2) tmp.AT(0) = t4 .AT(x, xx, i);
      FOR(j, 1, 23) {
        if(jj == 1) tmp.AT(j) = t6k.AT(x, xx, i, j);
        if(jj == 2) tmp.AT(j) = t6 .AT(x, xx, i, j);
      }
    }
    
    if(jj == 1) {
      aba = hn2k.AT(x, xx, i, 1);
      abb = hn2k.AT(x, xx, i, 1) + hn2k.AT(x, xx, i, 2);
    }
    else if(jj == 2) {
      aba = hn2.AT(x, xx, i, 1);
      abb = hn2.AT(x, xx, i, 1) + hn2.AT(x, xx, i, 2);
    }

    if(s != 3) {
      kk = ee.AT(1);
    } else {
      kk = ee.AT(2);
    }

    if((i == 2 || i == 4 || i == 6 || i == 8) && x < 65) {
      kk = 0.0;
    }

    if(abb > 1.0e-6 && aba >= 1.0e-6) {
      ab = aba / abb;
    } else {
      ab = 0.0;
    }

    if(pseid == 0)      ab *= 0.9301;
    else if(pseid == 1) ab *= 0.8745;
    else if(pseid == 4) ab *= 461.6518;
    else if(pseid == 5) ab *= 0.7979;
    
    double eps = 1.0e-6;
    assert(-eps <= ab || ab <= 1.0 + eps);
    

    d3.AT(k, s2, i, 0, jj) += tmp.AT(0);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 0) += tmp.AT(0);
    } else {
      d3xs.AT(k, x, s2, i, 0) += tmp.AT(0);
    }

    d3.AT(k, s2, i, 19, jj) += tmp.AT(14);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 19) += tmp.AT(14);
    } else {
      d3xs.AT(k, x, s2, i, 19) += tmp.AT(14);
    }

    d3.AT(k, s2, i, 20, jj) += tmp.AT(21);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 20) += tmp.AT(21);
    } else {
      d3xs.AT(k, x, s2, i, 20) += tmp.AT(21);
    }

    d3.AT(k, s2, i, 21, jj) += tmp.AT(6);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 21) += tmp.AT(6);
    } else {
      d3xs.AT(k, x, s2, i, 21) += tmp.AT(6);
    }

    d3.AT(k, s2, i, 22, jj) += tmp.AT(15) + tmp.AT(16) * 3.0 / 4.0 + tmp.AT(17);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 22) += tmp.AT(15) + tmp.AT(16) * 3.0 / 4.0 + tmp.AT(17);
    } else {
      d3xs.AT(k, x, s2, i, 22) += tmp.AT(15) + tmp.AT(16) * 3.0 / 4.0 + tmp.AT(17);
    }

    d3.AT(k, s2, i, 28, jj) += tmp.AT(17);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 28) += tmp.AT(17);
    } else {
      d3xs.AT(k, x, s2, i, 28) += tmp.AT(17);
    }

    d3.AT(k, s2, i, 23, jj) += tmp.AT(19) + tmp.AT(20);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 23) += tmp.AT(19) + tmp.AT(20);
    } else {
      d3xs.AT(k, x, s2, i, 23) += tmp.AT(19) + tmp.AT(20);
    }

    d3.AT(k, s2, i, 24, jj) += tmp.AT(18);
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 24) += tmp.AT(18);
    } else {
      d3xs.AT(k, x, s2, i, 24) += tmp.AT(18);
    }

    d3.AT(k, s2, i, 25, jj) += tmp.AT(16) / 4.0;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 25) += tmp.AT(16) / 4.0;
    } else {
      d3xs.AT(k, x, s2, i, 25) += tmp.AT(16) / 4.0;
    }

    if(i <= 8) {
      d3.AT(k, s2, i, 31, jj) += tmp.AT(24) * (1 - ab * kk); 
      d3.AT(k, s2, i, 32, jj) += tmp.AT(24) * ab;
      if(jj == 2) {
        d3x.AT(k, x, s2, i, 31) += tmp.AT(24) * (1 - ab * kk);
        d3x.AT(k, x, s2, i, 32) += tmp.AT(24) * ab;
      } else {
        d3xs.AT(k, x, s2, i, 31) += tmp.AT(24) * (1 - ab * kk);
        d3xs.AT(k, x, s2, i, 32) += tmp.AT(24) * ab;
      }
    }


    tmx = tmp.AT(1) + tmp.AT(10);
    tmy = 0.0;
    if(i == 11) tmy = tmp.AT(18);

    d3.AT(k, s2, i, 1, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 1) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 1) += tmx;
    }

    d3.AT(k, s2, i, 7, jj) += tmx - tmy;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 7) += tmx - tmy;
    } else {
      d3xs.AT(k, x, s2, i, 7) += tmx - tmy;
    }

    if(x >= 65) {
      d3.AT(k, s2, i, 35, jj) += tmx - tmy;
      if(jj == 2) {
        d3x.AT(k, x, s2, i, 35) += tmx - tmy;
      } else {
        d3xs.AT(k, x, s2, i, 35) += tmx - tmy;
      }
    }

    d3.AT(k, s2, i, 13, jj) += (tmx - tmy) * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 13) += (tmx - tmy) * ab;
    } else {
      d3xs.AT(k, x, s2, i, 13) += (tmx - tmy) * ab;
    }

    d3.AT(k, s2, i, 26, jj) += (tmx - tmy) * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 26) += (tmx - tmy) * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 26) += (tmx - tmy) * ab * kk;
    }


    tmx = tmp.AT(2) + tmp.AT(11);

    tmy = tmp.AT(15) + tmp.AT(16) * 3.0 / 4.0 + tmp.AT(17);
    if(i != 11) tmy += tmp.AT(18);

    tmy2 = tmp.AT(17);
    if(i != 11) tmy2 += tmp.AT(18);

    tmz = 0.0;
    if(i <= 4) tmz = tmp.AT(14);
    
    d3.AT(k, s2, i, 2, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 2) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 2) += tmx;
    }

    d3.AT(k, s2, i, 8, jj) += tmx - tmy;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 8) += tmx - tmy;
    } else {
      d3xs.AT(k, x, s2, i, 8) += tmx - tmy;
    }

    d3.AT(k, s2, i, 14, jj) += (tmx - tmy2 + tmz) * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 14) += (tmx - tmy2 + tmz) * ab;
    } else {
      d3xs.AT(k, x, s2, i, 14) += (tmx - tmy2 + tmz) * ab;
    }

    d3.AT(k, s2, i, 27, jj) += (tmx - tmy2 + tmz) * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 27) += (tmx - tmy2 + tmz) * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 27) += (tmx - tmy2 + tmz) * ab * kk;
    }


    tmx = tmp.AT(3);

    d3.AT(k, s2, i, 3, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 3) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 3) += tmx;
    }

    d3.AT(k, s2, i, 9, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 9) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 9) += tmx;
    }
    
    d3.AT(k, s2, i, 15, jj) += tmx * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 15) += tmx * ab;
    } else {
      d3xs.AT(k, x, s2, i, 15) += tmx * ab;
    }
    

    d3.AT(k, s2, i, 27, jj) += tmx * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 27) += tmx * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 27) += tmx * ab * kk;
    }


    tmx = tmp.AT(4) + tmp.AT(5) + tmp.AT(23);
    tmy = tmp.AT(19) + tmp.AT(20);

    d3.AT(k, s2, i, 4, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 4) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 4) += tmx;
    }

    d3.AT(k, s2, i, 10, jj) += tmx - tmy;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 10) += tmx - tmy;
    } else {
      d3xs.AT(k, x, s2, i, 10) += tmx - tmy;
    }

    d3.AT(k, s2, i, 16, jj) += (tmx - tmy) * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 16) += (tmx - tmy) * ab;
    } else {
      d3xs.AT(k, x, s2, i, 16) += (tmx - tmy) * ab;
    }

    d3.AT(k, s2, i, 27, jj) += (tmx - tmy) * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 27) += (tmx - tmy) * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 27) += (tmx - tmy) * ab * kk;
    }


    tmx = tmp.AT(7) + tmp.AT(8) + tmp.AT(9);

    d3.AT(k, s2, i, 5, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 5) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 5) += tmx;
    }

    d3.AT(k, s2, i, 11, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 11) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 11) += tmx;
    }

    d3.AT(k, s2, i, 17, jj) += tmx * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 17) += tmx * ab;
    } else {
      d3xs.AT(k, x, s2, i, 17) += tmx * ab;
    }

    d3.AT(k, s2, i, 27, jj) += tmx * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 27) += tmx * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 27) += tmx * ab * kk;
    }


    tmx = tmp.AT(12);

    d3.AT(k, s2, i, 6, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 6) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 6) += tmx;
    }

    d3.AT(k, s2, i, 12, jj) += tmx;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 12) += tmx;
    } else {
      d3xs.AT(k, x, s2, i, 12) += tmx;
    }

    d3.AT(k, s2, i, 18, jj) += tmx * ab;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 18) += tmx * ab;
    } else {
      d3xs.AT(k, x, s2, i, 18) += tmx * ab;
    }

    d3.AT(k, s2, i, 27, jj) += tmx * ab * kk;
    if(jj == 2) {
      d3x.AT(k, x, s2, i, 27) += tmx * ab * kk;
    } else {
      d3xs.AT(k, x, s2, i, 27) += tmx * ab * kk;
    }
  }
}