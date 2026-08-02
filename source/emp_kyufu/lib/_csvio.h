#ifndef CSVIO_H_INCLUDED
#define CSVIO_H_INCLUDED

#include "_sepsstd.h"
#include <string>
#include <vector>
#include <stdio.h>
#include <climits>
#define BUF_SIZE 10000

namespace csvio {
  static char __csvio_buf[BUF_SIZE];

  std::vector<std::string> split(const std::string, int, int);
  std::vector<std::string> split(const std::string, int);
  std::vector<std::string> split(const std::string);

  std::string join(std::string, std::vector<double>);
  std::string join(std::vector<double>);

  std::vector<double> getnums(const std::string, int, int);
  std::vector<double> getnums(const std::string, int);
  std::vector<double> getnums(const std::string);

  inline std::vector<double> read(FILE *fp, int begin, int end) {
    fgets(__csvio_buf, BUF_SIZE, fp);
    return getnums(__csvio_buf, begin, end);
  }
  inline std::vector<double> read(FILE *fp, int begin) {
    return read(fp, begin, INT_MAX);
  }
  inline std::vector<double> read(FILE *fp) {
    return read(fp, 0, INT_MAX);
  }

  inline std::vector<std::string> read_str(FILE *fp) {
    fgets(__csvio_buf, BUF_SIZE, fp);
    return split(__csvio_buf);
  }

  inline void skip(FILE *fp, int lines) {
    for(int csvio_int = 0; csvio_int < lines; csvio_int++)
      fgets(__csvio_buf, BUF_SIZE, fp);
  }
  inline void skip(FILE *fp) {
    skip(fp, 1);
  }
  
  namespace sequential {
    inline void print_int(FILE *fp, int val) {
      fprintf(fp, "%d", val);
    }
    inline void print_dbl(FILE *fp, std::string fmt, double val) {
      fprintf(fp, fmt.c_str(), val);
    }
    inline void add_int(FILE *fp, int val) {
      fprintf(fp, ",%d", val);
    }
    inline void add_dbl(FILE *fp, std::string fmt, double val) {
      fprintf(fp, fmt.insert(0, ",").c_str(), val);
    }
    inline void line_feed(FILE *fp) {
      fprintf(fp, "%s", "\n");
    }
  }
}

#endif