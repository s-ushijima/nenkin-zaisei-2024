#include "sepslib.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

namespace sepsstd {
  string to_string(double val) {
    char buf[32];
    snprintf(buf, 32, "%lf", val);
    return string(buf);
  }
  string to_string(int val) {
    char buf[32];
    snprintf(buf, 32, "%d", val);
    return string(buf);
  }

  string trim(const string str) {
    return trim(str, "\t\v\r\n");
  }
  string trim(const string str, const string blank_charset) {
    string::size_type left = str.find_first_not_of(blank_charset);
    if(left != string::npos) {
      string::size_type right = str.find_last_not_of(blank_charset);
      return str.substr(left, right - left + 1);
    }
    return "";
  }

  void subc1(VEC_TYPE1(double) &v, int from1, int to1) {
    for(int i = from1; i <= to1; i++) {
      v.at(i) = 0.0;
    }
  }
  void subc2(VEC_TYPE2(double) &v, int from1, int to1, int from2, int to2) {
    for(int i = from1; i <= to1; i++) {
      subc1(v.at(i), from2, to2);
    }
  }
  void subc3(VEC_TYPE3(double) &v, int from1, int to1, int from2, int to2, int from3, int to3) {
    for(int i = from1; i <= to1; i++) {
      subc2(v.at(i), from2, to2, from3, to3);
    }
  }
  void subc4(VEC_TYPE4(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4) {
    for(int i = from1; i <= to1; i++) {
      subc3(v.at(i), from2, to2, from3, to3, from4, to4);
    }
  }
  void subc5(VEC_TYPE5(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4, int from5, int to5) {
    for(int i = from1; i <= to1; i++) {
      subc4(v.at(i), from2, to2, from3, to3, from4, to4, from5, to5);
    }
  }
  void subc6(VEC_TYPE6(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4, int from5, int to5, int from6, int to6) {
    for(int i = from1; i <= to1; i++) {
      subc5(v.at(i), from2, to2, from3, to3, from4, to4, from5, to5, from6, to6);
    }
  }
}

namespace csvio {
  vector<string> split(const string str) {
    return split(str, 0, INT_MAX);
  }
  vector<string> split(const string str, int begin) {
    return split(str, begin, INT_MAX);
  }
  vector<string> split(const string str, int begin, int end) {
    string::size_type first = 0;
    string::size_type last = str.find_first_of(',');
    vector<string> result_vals;

    int counter = 0;
    while(first < str.size()) {

      counter++;
      if(counter <= begin) {
      } else if(counter > end) {
        break;
      } else {
        string val(str, first, last - first);
        result_vals.push_back(val);
      }

      first = last + 1;
      last = str.find_first_of(',', first);
      if(last == string::npos) {
        last = str.size();
      }
    }
    return result_vals;
  }

  string join(vector<double> vals) {
    return join("%.14e", vals);
  }
  string join(string format, vector<double> vals) {
    string result = "";
    for(vector<double>::iterator itr = vals.begin(); itr != vals.end(); itr++) {
      if(itr != vals.begin()) {
        result += ",";
      }
      result += sepsstd::format(format, *itr);
    }
    return result;
  }

  vector<double> getnums(const string str){
    return getnums(str, 0, INT_MAX);
  }
  vector<double> getnums(const string str, int begin) {
    return getnums(str, begin, INT_MAX);
  }
  vector<double> getnums(const string str, int begin, int end) {
    if (begin < 0) throw invalid_argument("begin = " + sepsstd::to_string(begin));
    if (begin > end) throw invalid_argument("begin > end: " + sepsstd::to_string(begin) + " > " + sepsstd::to_string(end));
    vector<string> splitted = split(str, begin, end);
    vector<double> result_vals;
    for(vector<string>::iterator itr = splitted.begin(); itr != splitted.end(); itr++) {
      string trimmed = sepsstd::trim(*itr);
      double val;
      try {
        val = atof(trimmed.c_str());
      }
      catch (...) {
        clog << "文字列から double 値への変換に失敗しました: atof(\"" + trimmed + "\")" << "\n";
        throw;
      }
      result_vals.push_back(val);
    }
    return result_vals;
  }
}