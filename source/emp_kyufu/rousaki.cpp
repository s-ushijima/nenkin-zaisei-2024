#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <cassert>
namespace sst = sepsstd;

void seps::rousaki(void) {

  double dtemp, rtemp;
  v2_t   sinrou = VEC(double, 3, 4);
  double kk;

  FOR(k, KIJUN + 1, KE) FOR(x, 80, 114) {
    if(x >= 66 + k - 7 && x <= 95 + k - KIJUN) {
      sst::subc2(sinrou, 1,3, 0,4);
      FOR(i, 1, 4) FOR(s, 1, 3) {
        int s3;
        if(pseid != 0 && s == 3) continue;
        if(s != 2) {
          s3 = 1;
        } else {
          s3 = 2;
        }
        FOR(j,  7,  10) {
          sinrou.AT(s, 0) += d3xs.AT(k, x, s, i, j) * (1.0 - sik.AT(k, x, s3, i, 1));
          sinrou.AT(s, i) += d3xs.AT(k, x, s, i, j) * (1.0 - sik.AT(k, x, s3, i, 1));
        }
      }
      if (sinrou.AT(1, 0) + sinrou.AT(3, 0) <= 0.0){
		sinrou.AT(1, 0) = 1.0;
		sinrou.AT(1, 1) = 1.0;
	  }
      if (sinrou.AT(2, 0) <= 0.0){
		sinrou.AT(2, 0) = 1.0;
		sinrou.AT(2, 1) = 1.0;
	  }

      FOR(j, 1, 58) { 
        int jj = -1;
        if(j == 1 || j == 7  || j == 13 || j == 35 || j == 41) jj = j;
        if(j == 5 || j == 11 || j == 17 || j == 39 || j == 45) jj = j - 2;
        if(jj < 0) continue;

        FOR(s, 1, 3) {
          if(pseid != 0  &&  s == 3) continue;
          int s3;
          if(s != 2) {
            s3 = 1;
          } else {
            s3 = 2;
          }
          rtemp = sik.AT(KIJUN, x, s3, 11, 1) - sik.AT(k, x, s3, 11, 1);
          if(rtemp < 0.0) rtemp = 0.0;

          if(jj == j) {
            dtemp = d3xs.AT(k, x, s, 11, j) * rtemp;
          } else {
            dtemp = d3xs.AT(k, x, s, 11, j) * rtemp * (1.0 - rc.AT(s, k, x));
          }

          if(dtemp <= 0.0) continue;

          FOR(ss, 1, 3) {
            if(pseid != 0 && ss == 3) continue;
            if((s == 2 && ss == 2) || 
               (s != 2 && ss != 2)   ) continue;
            if(ss != 3) {
              kk = ee.AT(1);
            } else {
              kk = ee.AT(2);
            }
            if(ss != 2) {
              rtemp = sinrou.AT(1, 0) + sinrou.AT(3, 0);
            } else {
              rtemp = sinrou.AT(2, 0);
            }

            FOR(i, 1, 4) {
              d3x.AT(k, x, ss, i, jj) += dtemp * sinrou.AT(ss, i) / rtemp;
              d3.AT(k, ss, i, jj, 2)  += dtemp * sinrou.AT(ss, i) / rtemp;
              if(jj == 13 && (i == 1 || i == 3)) {
                d3x.AT(k, x, ss, i, 26) += dtemp * sinrou.AT(ss, i) / rtemp * kk;
                d3.AT(k, ss, i, 26, 2)  += dtemp * sinrou.AT(ss, i) / rtemp * kk;
              } else if(jj == 15 && (i == 1 || i == 3)) {
                d3x.AT(k, x, ss, i, 27) += dtemp * sinrou.AT(ss, i) / rtemp * kk;
                d3.AT(k, ss, i, 27, 2)  += dtemp * sinrou.AT(ss, i) / rtemp * kk;
              }
            }
          }
        }
      }
    }
  }

}