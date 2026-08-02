#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
namespace csv = csvio;
namespace sst = sepsstd;
using namespace std;

void seps::subrh2(FILE *fp, int exp, v2_t &v, std::string v_name) {
  string aa;
  v1_t vals;
  
  csv::skip(fp, 7);
  
  FOR(x, 15, 89) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0);
    if(xx != x) {
      clog << "基礎数の年齢が違います（" << v_name << "）: x = " << x << ", xx= " << xx << "\n";
      throw invalid_argument("subrh");
    }
    int t_max = min(50, (int)vals.size() - 1);
    FOR(t, 0, t_max) {
      assert(!isnan(vals.at(1 + t) * pow(10.0, exp)));
      v.AT(x, t) = vals.at(1 + t) * pow(10.0, exp);
    }
  }
  csv::skip(fp);
}



void seps::subrh4(FILE* fp, int exp, v4_t &v, std::string v_name, int i, int j) {
  v1_t vals;
  
  csv::skip(fp, 7);
  
  FOR(x, 15, 89) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0);
    if(xx != x) {
      clog << sst::format(
        "基礎数の年齢が違います（%s）: "
        "x = %d, xx = %d, i = %d, j = %d\n", 
        v_name.c_str(), x, xx, i, j); 
      throw invalid_argument("subrh");
    }
    int t_max = min(50, (int)vals.size() - 1);
    FOR(t, 0, t_max) {
      assert(!isnan(vals.at(1 + t) * pow(10.0, exp)));
      v.AT(x, t, i, j) = vals.at(1 + t) * pow(10.0, exp);
    }
  }
  csv::skip(fp);
}



void seps::subrh5(FILE* fp, int exp, v5_t &v, std::string v_name, int i, int j, int ii) {
  v1_t vals;
  csv::skip(fp, 7);
  
  FOR(x, 15, 89) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0);
    if(xx != x) {
      clog << sst::format(
        "基礎数の年齢が違います（%s）: "
        "x = %d, xx = %d, i = %d, j = %d, ii = %d\n", 
        v_name.c_str(), x, xx, i, j, ii);
      throw invalid_argument("subrh");
    }
    int t_max = min(50, (int)vals.size() - 1);
    FOR(t, 0, t_max) {
      assert(!isnan(vals.at(1 + t) * pow(10.0, exp)));
      v.AT(x, t, i, j, ii) = vals.at(1 + t) * pow(10.0, exp);
    }
  }
  csv::skip(fp);
}