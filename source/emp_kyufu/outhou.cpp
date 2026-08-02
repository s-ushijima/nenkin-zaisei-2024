#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
namespace csv = csvio;

void seps::outhou(void) { 
  
  double tmp;
  v1_t   tmq = VEC(double, 75);

  FILE *fp;
  v1_t vals;

  fp = fp_map["hou2_out"];

  if(true) {
    fprintf(fp,"%s\n",
      ",k,s,x=15-69,15,16,17,18,19,20,"
      "21,22,23,24,25,26,27,28,29,30,"
      "31,32,33,34,35,36,37,38,39,40,"
      "41,42,43,44,45,46,47,48,49,50,"
      "51,52,53,54,55,56,57,58,59,60,"
      "61,62,63,64,65,66,67,68,69,70,"
      "71,72,73,74,75");
    FOR(s, 1, 3) {
      if(pseid != 0 && s == 3) continue;
      FOR(k, KIJUN, KE) {
        tmp = ad.AT(k);
        FOR(x, 14, 75) {
          if(gx.AT(k,x,s) > 0.0) {
            tmq.AT(x) = ax.AT(k,x,s) / gx.AT(k,x,s);
          } else {
            tmq.AT(x) = 0.0;
          }
        }
        char f8000[] = "%s,%d,%d,%s\n"; 
        vals.clear(); FOR(x, 14, 75) vals.push_back(ax.AT(k,x,s) / tmp);
        fprintf(fp, f8000, "ax" , k, s, csv::join("%19.12lf", vals).c_str());
        vals.clear(); FOR(x, 14, 75) vals.push_back(gx.AT(k,x,s));
        fprintf(fp, f8000, "gx" , k, s, csv::join("%19.12lf", vals).c_str());
        vals.clear(); FOR(x, 14, 75) vals.push_back(tmq.AT(x) / tmp);
        fprintf(fp, f8000, "a/g", k, s, csv::join("%19.12lf", vals).c_str());
        
        vals.clear(); FOR(x, 14, 75) vals.push_back(gtal.AT(k,x,s));
        fprintf(fp, f8000, "gtal" , k, s, csv::join("%19.12lf", vals).c_str());
        
        vals.clear(); FOR(x, 14, 75) vals.push_back(gztal.AT(k,x,s));
        fprintf(fp, f8000, "gztal" , k, s, csv::join("%19.12lf", vals).c_str());
        
        vals.clear(); FOR(x, 14, 75) vals.push_back(gntal.AT(k,x,s));
        fprintf(fp, f8000, "gntal" , k, s, csv::join("%19.12lf", vals).c_str());
        
        vals.clear(); FOR(x, 14, 75) vals.push_back(getal.AT(k,x,s));
        fprintf(fp, f8000, "getal" , k, s, csv::join("%19.12lf", vals).c_str());
        
      }
    }
  }
}
