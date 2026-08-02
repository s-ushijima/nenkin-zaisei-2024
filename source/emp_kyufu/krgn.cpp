#include "sepscommon.h"
#include "sepslib.h"
#include <vector>

typedef VEC_TYPE1(double) v1_t;
typedef VEC_TYPE2(double) v2_t;
typedef VEC_TYPE5(double) v5_t;
namespace sst = sepsstd;
namespace csv = csvio;

void seps::krgn(void) {

  v2_t tuki   = VEC(double, 5, 1);
  v1_t tmp    = VEC(double, 1);
  v1_t tmq    = VEC(double, 64);

  v1_t rtemp  = VEC(double, 2);
  
  v2_t rkrag    = VEC(double, 64, 2);
  v3_t rkrgn    = VEC(double, 64, 2, 2);
  
  v1_t  vals2;
  int s2;
  
 sst::subc5(riss, KS,KE, 60,70, 60,65, 1,3, 0,1);

 FILE *fpk = fp_map["kragsg"];
 
 csv::read(fpk);
 csv::read(fpk);
 for(int x = 60; x <= 64; x++){
 	vals2 = csv::read(fpk);
 	int xx = vals2.at(0);
 	assert(xx = x);
 	for(int s = 1; s <= 2; s++) rkrag.AT(x, s) = vals2.at(s);
 }
 
 csv::read(fpk);
 csv::read(fpk);
 for(int x = 60; x <= 64; x++){
 	vals2 = csv::read(fpk);
 	int xx = vals2.at(0);
 	assert(xx = x);
 	for(int s = 1; s <= 2; s++) rkrgn.AT(x, s, 0) = vals2.at(s);
 }
 csv::read(fpk);
 csv::read(fpk);
 for(int x = 60; x <= 64; x++){
 	vals2 = csv::read(fpk);
 	int xx = vals2.at(0);
 	assert(xx = x);
 	for(int s = 1; s <= 2; s++) rkrgn.AT(x, s, 1) = vals2.at(s);
 }

  FOR(s, 1, 3) {
    if(s != 2) {
      tmq.AT(60) = rkrag.AT(60, 1);
      tmq.AT(61) = rkrag.AT(61, 1);
      tmq.AT(62) = rkrag.AT(62, 1);
      tmq.AT(63) = rkrag.AT(63, 1);
      tmq.AT(64) = rkrag.AT(64, 1);
    } else {
      tmq.AT(60) = rkrag.AT(60, 2);
      tmq.AT(61) = rkrag.AT(61, 2);
      tmq.AT(62) = rkrag.AT(62, 2);
      tmq.AT(63) = rkrag.AT(63, 2);
      tmq.AT(64) = rkrag.AT(64, 2);
    }

    FOR(i, 0, 1) FOR(k, KS, KE) FOR(x2, 60, 65) {
     riss.AT(k, 65, x2, s, i) = 1.0;
      FOR(x1, 60, 64) {
        if(x2 == 60 || x1 >= x2) break;
        if(i == 0) riss.AT(k, x1, x2, s, i) = tmq.AT(x1);
        riss.AT(k, 65, x2, s, i) = 
          riss.AT(k, 65, x2, s, i) - riss.AT(k, x1, x2, s, i);
      }
    }
  }

  FOR(s, 1, 3)  {
    FOR(x1, 60, 70) FOR(x2, 60, 70) FOR(j, 0, 1) {
      rigd.AT(s, x1, x2, j) = 0.0;
      rigk.AT(s, x1, x2, j) = 0.0;
      rigbe.AT(s, x1, x2, j) = 0.0;
    }

    tmp.AT(0) = 0.005;
    tmp.AT(1) = 0.004;
    tuki.AT(0, 0) = (1.0 - rkrgn.AT(60, 1, 0)) / tmp.AT(0);
    tuki.AT(1, 0) = (1.0 - rkrgn.AT(61, 1, 0)) / tmp.AT(0);
    tuki.AT(2, 0) = (1.0 - rkrgn.AT(62, 1, 0)) / tmp.AT(0);
    tuki.AT(3, 0) = (1.0 - rkrgn.AT(63, 1, 0)) / tmp.AT(0);
    tuki.AT(4, 0) = (1.0 - rkrgn.AT(64, 1, 0)) / tmp.AT(0);
    tuki.AT(5, 0) = 0.0;
    tuki.AT(0, 1) = (1.0 - rkrgn.AT(60, 1, 1)) / tmp.AT(1);
    tuki.AT(1, 1) = (1.0 - rkrgn.AT(61, 1, 1)) / tmp.AT(1);
    tuki.AT(2, 1) = (1.0 - rkrgn.AT(62, 1, 1)) / tmp.AT(1);
    tuki.AT(3, 1) = (1.0 - rkrgn.AT(63, 1, 1)) / tmp.AT(1);
    tuki.AT(4, 1) = (1.0 - rkrgn.AT(64, 1, 1)) / tmp.AT(1);
    tuki.AT(5, 1) = 0.0;

    FOR(j, 0, 1) {
      rigd.AT(s, 65, 60, j) = 1.0;
      FOR(x1, 60, 65)
      FOR(x2, 61, 65) {
        if(x2 < 65) {
          if(x1 < x2) {
            rigd.AT(s, x1, x2, j) =
                (65 - x2) / (tuki.AT(x1 - 60, j) / 12.0);
            rigk.AT(s, x1, x2, j) =
                (1.0 - rigd.AT(s, x1, x2, j)) * (1.0 - tuki.AT(x1 - 60, j) * tmp.AT(j));
          } else if(x1 == 65) {
            rigd.AT(s, x1, x2, j) =
                (65 - x2) / (tuki.AT(5, j) / 12.0 + (x1 - x2));
            rigk.AT(s, x1, x2, j) =
                1.0 - tuki.AT(5, j) * tmp.AT(j) - rigd.AT(s, x1, x2, j);
          }
        } else {
          rigk.AT(s, x1, x2, j) = 1.0 - tuki.AT(x1 - 60, j) * tmp.AT(j);
        }
      }
    }
  }


  FILE *fp = fp_map["prtfil"];
  vector<double> vals;
  fprintf(fp, "%s\n", "·«¤ê¾å¤²¸º³ÛÎ¨");

  FOR(s, 1, 2) FOR(j, 0, 1) {
    fprintf(fp, "rigd,%d", s);
    FOR(x1, 60, 65) {
      vals.clear(); FOR(x2, 60, 65) vals.push_back(rigd.AT(s, x1, x2, j));
      fprintf(fp, "%d,%s", x1, csv::join(vals).c_str());
    }

    fprintf(fp, "rigk,%d", s);
    FOR(x1, 60 ,65) {
      vals.clear(); FOR(x2, 60, 65) vals.push_back(rigk.AT(s, x1, x2, j));
      fprintf(fp, "%d,%s", x1, csv::join(vals).c_str());
    }
  }


  FOR(s, 1, 3) FOR(j, 0, 1) {
    rigbe.AT(s, 60, 60, j) = 1.0;
    FOR(x1, 60, 65) FOR(x2, 61, 65) {
      if(x2 < 65) {
        if(x1 < x2) {
          rigbe.AT(s,x1,x2,j) =
            1.0 - (tuki.AT(x1 - 60, j) / 12.0 - (65 - x2)) * 12.0 * tmp.AT(j);
        } else if(x1 == x2) {
          rigbe.AT(s, x1, x2, j) = 1.0 - tuki.AT(5, j) * tmp.AT(j);
        }
      } else {
        rigbe.AT(s, x1, x2, j) = 1.0 - tuki.AT(x1 - 60, j) * tmp.AT(j);
      }
    }
  }

  fprintf(fp, "·«¤ê¾å¤²¸º³ÛÎ¨\n");
  FOR(s, 1, 2) FOR(j, 0, 1) {
    fprintf(fp, "RIGBE,%d\n", s);
    FOR(x1, 60, 65) {
      vals.clear(); FOR(x2, 60, 65) vals.push_back(rigbe.AT(s, x1, x2, j));
      fprintf(fp, "%d,%s\n", x1, csv::join("%10.5lf",vals).c_str());
    }
  }
}
