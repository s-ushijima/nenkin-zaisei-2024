#ifndef SEPSSTD_H_INCLUDED
#define SEPSSTD_H_INCLUDED

#include "_vecarray.h"
#include <string>
#include <cstdio>
#include <math.h>
#include <vector>
#include <cassert>

namespace sepsstd {

  std::string to_string(int);
  
  std::string to_string(double);
  
  std::string trim(const std::string, const std::string);
  std::string trim(const std::string);
  
  inline double dparse(std::string str) {
    return atof(trim(str).c_str());
  }

  template <typename T0>
  static std::string format(const std::string &fmt, T0 arg0)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2);
    std::vector<char> buf(len + 1);
    std::snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2, typename T3>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2, T3 arg3)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2, arg3);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2, arg3);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2, arg3, arg4);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2, arg3, arg4);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5, arg6);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
  template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  static std::string format(const std::string &fmt, T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7)
  {
    char dum;
    size_t len = snprintf(&dum, 0, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    std::vector<char> buf(len + 1);
    snprintf(&buf.at(0), len + 1, fmt.c_str(), arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    return std::string(&buf.at(0), &buf.at(0) + len);
  }
 
  inline double roundn(double val, int n) {
    return round(val * pow(10.0, n)) / pow(10.0, n);
  }
  
  void subc1(VEC_TYPE1(double) &v, int from1, int to1);
  void subc2(VEC_TYPE2(double) &v, int from1, int to1, int from2, int to2);
  void subc3(VEC_TYPE3(double) &v, int from1, int to1, int from2, int to2, int from3, int to3);
  void subc4(VEC_TYPE4(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4);
  void subc5(VEC_TYPE5(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4, int from5, int to5);
  void subc6(VEC_TYPE6(double) &v, int from1, int to1, int from2, int to2, int from3, int to3, int from4, int to4, int from5, int to5, int from6, int to6);
}

#endif