#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
namespace csv = csvio;
namespace sst = sepsstd;
using namespace std;

void seps::subrj3(FILE *fp, int exp, v3_t &v) {
  v1_t vals;
  int pos;

  csv::skip(fp, 3);

  FOR(x, 0, 115) {
    vals = csv::read(fp);
    int xtp = (int)vals.at(0); assert(xtp == x);
    int size = (int)vals.size();

    FOR(t, 1, 4) {
      pos = t;  if(pos >= size) break;
      v.AT(x, 0, t) = vals.at(pos) * pow(10.0, exp);
      FOR(xx, 1, 5) {
        pos = 24 + t - xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t) = vals.at(pos) * pow(10.0, exp);
      }
      FOR(xx, 6, 10) {
        pos = 4 + t + xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t) = vals.at(pos) * pow(10.0, exp);
      }
    }
    FOR(t, 5, 13) {
      pos = 44 + t;  if(pos >= size) break;
      assert(!isnan(vals.at(pos) * pow(10.0, exp)));
      v.AT(x, 0, t) = vals.at(pos) * pow(10.0, exp);
    }
  }
}



void seps::subrj4(FILE *fp, int exp, v4_t &v, int j) {
  v1_t vals;
  int pos;

  csv::skip(fp, 4);

  FOR(x, 0, 115) {
    vals = csv::read(fp);
    int xtp = (int)vals.at(0); assert(xtp == x);
    int size = (int)vals.size();

    FOR(t, 1, 4) {
      pos = t;  if(pos >= size) break;
      v.AT(x, 0, t, j) = vals.AT(pos) * pow(10.0, exp);
      FOR(xx, 1, 5) {
        pos = 24 + t - xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t, j) = vals.AT(pos) * pow(10.0, exp);
      }
      FOR(xx, 6, 10) {
        pos = 4 + t + xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t, j) = vals.AT(pos) * pow(10.0, exp);
      }
    }
    FOR(t, 5, 13) {
      pos = 44 + t;  if(pos >= size) break;
      assert(!isnan(vals.at(pos) * pow(10.0, exp)));
      v.AT(x, 0, t, j) = vals.AT(pos) * pow(10.0, exp);
    }
  }
}



void seps::subrj5(FILE *fp, int exp, v5_t &v, int jj, int ii) {
  v1_t vals;
  int pos;

  csv::skip(fp, 4);
	  
  FOR(x, 0, 115) {
    vals = csv::read(fp);
    int xtp = (int)vals.at(0); assert(xtp == x);
    int size = (int)vals.size();

    FOR(t, 1, 4) {
      pos = t;  if(pos >= size) break;
      v.AT(x, 0, t, jj, ii) = vals.at(pos) * pow(10.0, exp);
      FOR(xx, 1, 5) {
        pos = 24 + t - xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t, jj, ii) = vals.at(pos) * pow(10.0, exp);
      }
      FOR(xx, 6, 10) {
        pos = 4 + t + xx * 4;  if(pos >= size) break;
        assert(!isnan(vals.at(pos) * pow(10.0, exp)));
        v.AT(x, xx, t, jj, ii) = vals.at(pos) * pow(10.0, exp);
      }
    }
    FOR(t, 5, 13) {
      pos = 44 + t;  if(pos >= size) break;
      assert(!isnan(vals.at(pos) * pow(10.0, exp)));
      v.AT(x, 0, t, jj, ii) = vals.at(pos) * pow(10.0, exp);
    }
  }
}
