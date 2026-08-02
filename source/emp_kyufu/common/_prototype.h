#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include "_vecarray.h"
#include <string>

namespace seps {
  void cntl(void);

  void sepsd(void);

  void zero_init(void);
  void zero_sepsd(void);

  void fopn(void);
  void fcls(void);

  void flck(void);

  void waku(void);

  void econ(void);

  void seid(void);

  void krgn(void);

  void kiso(void);

  void dtst(void);

  void sknr(const int, const int, int &, int &);

  void subrh2(FILE *, int, v2_t &, std::string);
  void subrh4(FILE *, int, v4_t &, std::string, int, int);
  void subrh5(FILE *, int, v5_t &, std::string, int, int, int);

  void subrj3(FILE *, int, v3_t &);
  void subrj4(FILE *, int, v4_t &, int);
  void subrj5(FILE *, int, v5_t &, int, int);

  void daik(void);

  void shke(void);
    void shkehiho(void);
    void shkejken(int, int, int);
    void shkejsha(int, int, int);
      void siku(int, int, double &, double &, double &, double &);
    void shkejuk(int, int, int);
    void shkekiso(void);
  
  void dsitk(int, int, int, double &, double &, double &);

  void siml(void);
    void simlg(const int, const int);
    void simlbzw(int, int);
    void simlbzw0(int);
    void saitesho(int, int);
    void saiteizohiho(int, int);
    void saiteizojuk(int);
    void saitezai(int, int);
    void saitetai(int, int);
    void simlrhnf0(int);
    void simlrhnf(int, int, int, int);
    void simlrhnfsen(int);
    void simlrhnfsen60(void);
  
  void outkn(void);

  void rousaki(void);

  void pstat(void);

  void stat(void);

  void crshfl(void);

  void oldkou(void);

  void outhou(void);
}

#endif