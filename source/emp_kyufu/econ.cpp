#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;
namespace sst = sepsstd;
namespace csv = csvio;

void jitsuchin_kashobun(vector<double> &, vector<double> &);

void seps::econ(void) {

  double ci_kijun, tamari_ci;
  double hhd, cid;
  double kaite_hh, kaite_hp, kaite_ci;
  double kaite_hhrd, kaite_hprd, kaite_cird;
  v1_t ridum          = VEC(double, ECEDY);
  v1_t ci0dum         = VEC(double, ECEDY);

  v1_t jh_kaite       = VEC(double, ECEDY);
  v1_t koujor         = VEC(double, ECEDY);
  v1_t id_hh_juzen    = VEC(double, ECEDY);
  v2_t id_hh_hon0     = VEC(double, ECEDY, 115);
  v2_t id_hh_honju8w  = VEC(double, ECEDY, 115);
  v2_t id_hh_toku     = VEC(double, ECEDY, 115);
  v2_t id_hh_siku     = VEC(double, ECEDY, 115);
  v2_t arv_hh         = VEC(double, ECEDY, 115);
  v2_t idr_hp_hon     = VEC(double, ECEDY, 115);
  v2_t idg_hp_hon8w   = VEC(double, ECEDY, 115);
  v2_t idr_hp_toku    = VEC(double, ECEDY, 115);
  v2_t idg_hp_toku    = VEC(double, ECEDY, 115);
  v2_t idg_hp_siku    = VEC(double, ECEDY, 115);
  v2_t arv_hp         = VEC(double, ECEDY, 115);

  v2_t rv             = VEC(double, ECEDY, 23);

  int _same[] = {
    0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,
    14, 14, 14, 6,  4,
    5,  5,  13, 4
  };
  vector<int> same(_same, _same + 24);

  double marume_yr;
  marume_yr= 24;

  FILE *fp;
  char buf[BUF_SIZE];
  
  fp = fp_map["econ"];
  for(k = 1; k <= KE; k++) {
    char *result = fgets(buf, BUF_SIZE, fp);

    if(result != NULL && string(buf).length() > 2) {
      vector<double> vals = csv::getnums(buf);

      int kk = (int)vals.at(0);
      assert(k == kk);

      ridum  .AT(k) = vals.at(1) * 1.0e-2;
      hdum   .AT(k) = vals.at(5) * 1.0e-2;
      ci0dum .AT(k) = vals.at(6) * 1.0e-2;
    }
    else {
      ridum  .AT(k) = ridum  .AT(k - 1);
      hdum   .AT(k) = hdum   .AT(k - 1);
      ci0dum .AT(k) = ci0dum .AT(k - 1);
    }
    
    ri.AT(k)   = (1.0 + ridum.AT(k)) *  (1.0 + ci0dum .AT(k)) - 1.0;
    h.AT(k)    = (1.0 + hdum.AT(k))  *  (1.0 + ci0dum .AT(k)) - 1.0; 
    ci0.AT(k)  = ci0dum.AT(k) ;
    
    if(k == 1)   ri.AT(k) =  1.99 * 1.0e-2,   h.AT(k) =  0.38 * 1.0e-2;
    if(k == 2)   ri.AT(k) =  0.21 * 1.0e-2,   h.AT(k) = -0.66 * 1.0e-2;
    if(k == 3)   ri.AT(k) =  4.91 * 1.0e-2,   h.AT(k) = -0.61 * 1.0e-2;
    if(k == 4)   ri.AT(k) =  2.73 * 1.0e-2,   h.AT(k) = -0.18 * 1.0e-2;
    if(k == 5)   ri.AT(k) =  6.82 * 1.0e-2,   h.AT(k) = -0.24 * 1.0e-2;
    if(k == 6)   ri.AT(k) =  3.10 * 1.0e-2,   h.AT(k) = -0.25 * 1.0e-2;
    if(k == 7)   ri.AT(k) = -3.54 * 1.0e-2,   h.AT(k) = -0.46 * 1.0e-2;
    if(k == 8)   ri.AT(k) = -6.83 * 1.0e-2,   h.AT(k) = -0.49 * 1.0e-2;
    if(k == 9)   ri.AT(k) =  7.54 * 1.0e-2,   h.AT(k) = -3.03 * 1.0e-2;
    if(k == 10)  ri.AT(k) = -0.26 * 1.0e-2,   h.AT(k) = -0.44 * 1.0e-2;
    if(k == 11)  ri.AT(k) =  2.17 * 1.0e-2,   h.AT(k) = -0.08 * 1.0e-2;
    if(k == 12)  ri.AT(k) =  9.57 * 1.0e-2,   h.AT(k) = -0.32 * 1.0e-2;
    if(k == 13)  ri.AT(k) =  8.22 * 1.0e-2,   h.AT(k) = -0.14 * 1.0e-2;
    if(k == 14)  ri.AT(k) = 11.61 * 1.0e-2,   h.AT(k) =  1.06 * 1.0e-2;
    if(k == 15)  ri.AT(k) = -3.14 * 1.0e-2,   h.AT(k) =  0.33 * 1.0e-2;
    if(k == 16)  ri.AT(k) =  5.30 * 1.0e-2,   h.AT(k) = -0.05 * 1.0e-2;
    if(k == 17)  ri.AT(k) =  6.50 * 1.0e-2,   h.AT(k) =  0.26 * 1.0e-2;
    if(k == 18)  ri.AT(k) =  1.42 * 1.0e-2,   h.AT(k) =  0.79 * 1.0e-2;
    if(k == 19)  ri.AT(k) = -4.96 * 1.0e-2,   h.AT(k) =  0.60 * 1.0e-2;
    if(k == 20)  ri.AT(k) = 23.90 * 1.0e-2,   h.AT(k) = -0.52 * 1.0e-2;
    if(k == 21)  ri.AT(k) =  5.19 * 1.0e-2,   h.AT(k) =  1.04 * 1.0e-2;
    if(k == 22)  ri.AT(k) =  1.44 * 1.0e-2,   h.AT(k) =  1.39 * 1.0e-2;

  }


  tamari_ci = -1.7e-2;

  id_hh_juzen.AT(4) = 0.986;
  
  id_hh_hon0.AT(4, 67) = 0.990;
  id_hh_hon0.AT(4, 68) = 0.982;
  id_hh_hon0.AT(4, 69) = 0.975;
  id_hh_hon0.AT(4, 70) = 0.971;
  id_hh_hon0.AT(4, 71) = 0.971;
  id_hh_hon0.AT(4, 72) = 0.971;
  id_hh_hon0.AT(4, 73) = 0.971 * 1.064 / 1.069;
  id_hh_hon0.AT(4, 74) = 0.971 * 1.041 / 1.069;
  id_hh_hon0.AT(4, 75) = 0.971 * 1.031 / 1.069;

  id_hh_honju8w.AT(4, 67) = max(max(id_hh_juzen.AT(4), id_hh_hon0.AT(4, 67)), id_hh_hon0.AT(4, 67) * 0.8);

  id_hh_toku.AT(4, 67) = 1.003;
  id_hh_siku.AT(4, 67) = max(id_hh_honju8w.AT(4, 67), id_hh_toku.AT(4, 67));

  idr_hp_hon.AT(4, 67) = 1.000;

  idg_hp_hon8w.AT(4, 67) = 7809;

  idr_hp_toku.AT(4, 67) = 0.988;
  idg_hp_toku.AT(4, 67) = round(idr_hp_toku.AT(4, 67) * 8042);

  idg_hp_siku.AT(4, 67) = max(idg_hp_hon8w.AT(4, 67), idg_hp_toku.AT(4, 67));

  for(int x = 68; x <= 115; x++) {
    if(x >= 76) id_hh_hon0.AT(4, x) = id_hh_hon0.AT(4, 75);

    id_hh_honju8w.AT(4, x)  = max(max(id_hh_juzen.AT(4), id_hh_hon0.AT(4, x)), id_hh_hon0.AT(4, 67) * 0.8);
    id_hh_toku.AT(4, x)     = id_hh_toku.AT(4, 67);
    id_hh_siku.AT(4, x)     = max(id_hh_honju8w.AT(4, x), id_hh_toku.AT(4, x));

    idr_hp_hon.AT(4, x)   = idr_hp_hon.AT(4, 67);
    idg_hp_hon8w.AT(4, x) = idg_hp_hon8w.AT(4, 67);
    idr_hp_toku.AT(4, x)  = idr_hp_toku.AT(4, 67);
    idg_hp_toku.AT(4, x)  = idg_hp_toku.AT(4, 67);
    idg_hp_siku.AT(4, x)  = idg_hp_siku.AT(4, 67);
  }

  jz_shk.AT(4) = sst::roundn(0.917 / 0.990, 3);

  dir.AT(4) = 0.980;

  ci_kijun = 1.0;

  jitsuchin_kashobun(jh_kaite, koujor);

  for(int k = 5; k <= KE; k++) {
    kaite_ci = ci0.AT(k - 1);
    kaite_hh = (1.0 + kaite_ci) * jh_kaite.AT(k) * koujor.AT(k) - 1.0;

    kaite_cird = sst::roundn(ci0.AT(k - 1), 3);

    double jh_kaite_k_rd = sst::roundn(jh_kaite.AT(k), 3);
    double koujour_k_rd = sst::roundn(koujor.AT(k), 3);

    kaite_hhrd = (1.0 + kaite_cird) * jh_kaite_k_rd * koujour_k_rd - 1.0;
    kaite_hhrd = sst::roundn(kaite_hhrd, 3);

    hhd = kaite_hh;
    cid = kaite_ci;
    
      if(k < 21) {
        if(hhd < cid && hhd < 0.0) {
          kaite_hh = min(cid, 0.0);
        }
        if(hhd < cid && cid > 0.0) {
          kaite_ci = max(hhd, 0.0);
        }
      } else if(hhd < cid) {
        kaite_ci = hhd;
      } 

    if(tamari_ci >= 0.0 && k > marume_yr) {
        if(k >= 21) {
          jz_shk.AT(k) = jz_shk.AT(k - 1) / (1.0 + ci0.AT(k - 1)) / jh_kaite.AT(k);
        } else {
          if(hhd < cid) {
            if(hhd < 0.0 && cid < 0.0) {
              jz_shk.AT(k) = jz_shk.AT(k - 1) / (1.0 + ci0.AT(k - 1));
            } else if (hhd < 0.0 && cid >= 0.0) {
              jz_shk.AT(k) = jz_shk.AT(k - 1);
            } else {
              jz_shk.AT(k) = jz_shk.AT(k - 1) / (1.0 + ci0.AT(k - 1)) / jh_kaite.AT(k);
            }
          } else {
            jz_shk.AT(k) = jz_shk.AT(k - 1) / (1.0 + ci0.AT(k - 1)) / jh_kaite.AT(k);
          }
        } 
    } 

    hhd = kaite_hhrd;
    cid = kaite_cird;
    
      if(k < 21) {
        if(hhd < cid && hhd < 0.0) {
          kaite_hhrd = min(cid, 0.0);
        }
        if(hhd < cid && cid > 0.0) {
          kaite_cird = max(hhd, 0.0);
        }
      } else if(hhd < cid) {
        kaite_cird = hhd;
      } 

    if(tamari_ci < 0.0 || k <= marume_yr) {
        if(k >= 21) {
          double _jz_shk_prev = jz_shk.AT(k - 1);
          double _ci_prev = (1.0 + ci0.AT(k - 1));
          double _jh_kaite_rd = sst::roundn(jh_kaite.AT(k), 3);
          double _jz_shk_tmp = (_jz_shk_prev / _ci_prev) / _jh_kaite_rd;
          jz_shk.AT(k) = sst::roundn(_jz_shk_tmp, 3);
        } else {
          if(hhd < cid) {
            if(hhd < 0.0 && cid < 0.0) {
              double _jz_shk_tmp = jz_shk.AT(k - 1) / (1.0 + ci0.AT(k - 1));
              jz_shk.AT(k) = sst::roundn(_jz_shk_tmp, 3);
            } else if (hhd < 0.0 && cid >= 0.0) {
              jz_shk.AT(k) = jz_shk.AT(k - 1);
            } else {
              double _jz_shk_prev = jz_shk.AT(k - 1);
              double _ci_prev = (1.0 + ci0.AT(k - 1));
              double _jh_kaite_rd = sst::roundn(jh_kaite.AT(k), 3);
              double _jz_shk_tmp = (_jz_shk_prev / _ci_prev) / _jh_kaite_rd;
              jz_shk.AT(k) = sst::roundn(_jz_shk_tmp, 3);
            }
          } else {
            double _jz_shk_prev = jz_shk.AT(k - 1);
            double _ci_prev = (1.0 + ci0.AT(k - 1));
            double _jh_kaite_rd = sst::roundn(jh_kaite.AT(k), 3);
            double _jz_shk_tmp = (_jz_shk_prev / _ci_prev) / _jh_kaite_rd;
            jz_shk.AT(k) = sst::roundn(_jz_shk_tmp, 3);
          }
        }
    }

    if(k >= 7) {
      kaite_hp   = kaite_hh;
      kaite_hprd = kaite_hhrd;
    } else {
      kaite_hp   = kaite_ci;
      kaite_hprd = kaite_cird;
    }

    ci_kijun = sst::roundn(ci_kijun * (1.0 + ci0.AT(k - 1)), 3);

    if(ci_kijun < 1.0) {
      cid = ci_kijun - 1.0;
      ci_kijun = 1.0;
    } else {
      cid = 0.0;
    }
    hhd = cid;

    if(flg_kaisho == 2) {
      if(k == 13 || k == 14) {
        if(k == 13) {
          assert(cid == kaite_hhrd && cid == kaite_cird);
        }
        hhd = min(1.0, sst::roundn((1.0 + kaite_hhrd) * 0.99, 3)) - 1.0;
        cid = min(1.0, sst::roundn((1.0 + kaite_cird) * 0.99, 3)) - 1.0;
      }
      else if(k >= 15) {
        hhd = -1.0;
        cid = -1.0;
      }
    }

    if(tamari_ci < 0.0  ||  k <= marume_yr) { 
      id_hh_juzen.AT(k) = sst::roundn(id_hh_juzen.AT(k - 1) * (1.0 + kaite_cird), 4);
      id_hh_hon0.AT(k, 67) = sst::roundn(id_hh_hon0.AT(k - 1, 67) * (1.0 + kaite_hhrd), 4);

      for(int x = 68; x <= 115; x++) {
        id_hh_hon0.AT(k, x) = sst::roundn(id_hh_hon0.AT(k - 1, x - 1) * (1.0 + kaite_cird), 4);
      }
      dir.AT(k) = sst::roundn(dir.AT(k - 1) * sst::roundn(koujor.AT(k), 3), 3);
    } else {
      id_hh_juzen.AT(k) = id_hh_juzen.AT(k - 1) * (1.0 + kaite_ci);
      id_hh_hon0.AT(k, 67) = id_hh_hon0.AT(k - 1, 67) * (1.0 + kaite_hh);
      for(int x = 68; x <= 115; x++) {
        id_hh_hon0.AT(k, x) = id_hh_hon0.AT(k - 1, x - 1) * (1.0 + kaite_ci);
      }
      dir.AT(k) = dir.AT(k - 1) * koujor.AT(k);
    }
    
    id_hh_honju8w.AT(k, 67) = max(max(id_hh_juzen.AT(k), id_hh_hon0.AT(k, 67)), id_hh_hon0.AT(k, 67) * 0.8);

    id_hh_toku.AT(k, 67) = sst::roundn(id_hh_toku.AT(k - 1, 67) * (1.0 + hhd), 4);
    if(k == 6) id_hh_toku.AT(k, 67) = 0.9999;

    id_hh_siku.AT(k, 67) = max(id_hh_honju8w.AT(k, 67), id_hh_toku.AT(k, 67));

    if(id_hh_honju8w.AT(k, 67) < id_hh_toku.AT(k, 67)) {
      arv_hh.AT(k, 67) = 1.0 + hhd;
    }
    else if(k <= marume_yr && id_hh_honju8w.AT(k - 1, 67) >= id_hh_toku.AT(k - 1, 67)){
      arv_hh.AT(k, 67) = sst::roundn(id_hh_siku.AT(k, 67) / id_hh_siku.AT(k - 1, 67), 3);
    }
    else {
      arv_hh.AT(k, 67) = id_hh_siku.AT(k, 67) / id_hh_siku.AT(k - 1, 67);
    }

    if(idg_hp_hon8w.AT(k - 1, 67) < idg_hp_toku.AT(k - 1, 67) || k <= marume_yr) {
      idr_hp_hon.AT(k, 67) = sst::roundn(idr_hp_hon.AT(k - 1, 67) * (1.0 + kaite_hprd), 3);
      idg_hp_hon8w.AT(k, 67) = round(idr_hp_hon.AT(k, 67) * 7809);
    }
    else {
      idr_hp_hon.AT(k, 67) = idr_hp_hon.AT(k - 1, 67) * (1.0 + kaite_hp);
      idg_hp_hon8w.AT(k, 67) = idg_hp_hon8w.AT(k - 1, 67) * (1.0 + kaite_hp);
    }

    idr_hp_toku.AT(k, 67) = sst::roundn(idr_hp_toku.AT(k - 1, 67) * (1.0 + hhd), 3);
    idg_hp_toku.AT(k, 67) = round(idr_hp_toku.AT(k, 67) * 8042);

    idg_hp_siku.AT(k, 67) = max(idg_hp_hon8w.AT(k, 67), idg_hp_toku.AT(k, 67));

    if(idg_hp_hon8w.AT(k, 67) < idg_hp_toku.AT(k, 67)) {
      arv_hp.AT(k, 67) = 1.0 + hhd;
    }
    else if(k <= marume_yr && idg_hp_hon8w.AT(k - 1, 67) >= idg_hp_toku.AT(k - 1, 67)) {
      arv_hp.AT(k, 67) = sst::roundn(idg_hp_siku.AT(k, 67)/idg_hp_siku.AT(k - 1, 67), 3);
    } else {
      arv_hp.AT(k, 67) = idg_hp_siku.AT(k, 67) / idg_hp_siku.AT(k - 1, 67);
    }

    for(int x = 68; x <= 115; x++) {
      id_hh_honju8w.AT(k, x) = max(max(id_hh_juzen.AT(k), id_hh_hon0.AT(k, x)), id_hh_hon0.AT(k, 67) * 0.8);
      id_hh_toku.AT(k, x) = sst::roundn(id_hh_toku.AT(k - 1, x - 1) * (1.0 + cid), 4);
      if(k == 6) id_hh_toku.AT(k, x) = 0.9999;

      id_hh_siku.AT(k, x) = max(id_hh_honju8w.AT(k, x), id_hh_toku.AT(k, x));
      if(id_hh_honju8w.AT(k, x) < id_hh_toku.AT(k, x)) {
        arv_hh.AT(k, x) = 1.0 + cid;
      }
      else if(k <= marume_yr && id_hh_honju8w.AT(k - 1, x - 1) >= id_hh_toku.AT(k - 1, x - 1)) {
        arv_hh.AT(k, x) = sst::roundn(id_hh_siku.AT(k, x) / id_hh_siku.AT(k - 1, x - 1), 3);
      }
      else {
        arv_hh.AT(k, x) = id_hh_siku.AT(k, x) / id_hh_siku.AT(k - 1, x - 1);
      }

      if(idg_hp_hon8w.AT(k - 1, x - 1) < idg_hp_toku.AT(k - 1, x - 1)) {
        idr_hp_hon.AT(k, x) = sst::roundn(idr_hp_hon.AT(k - 1, x - 1) * (1.0 + kaite_cird), 3);
        idg_hp_hon8w.AT(k, x) = round(max(idr_hp_hon.AT(k, x), idr_hp_hon.AT(k, 67) * 0.8) * 7809);
      }
      else {
        idr_hp_hon.AT(k, x) = idr_hp_hon.AT(k - 1, x - 1) * (1.0 + kaite_ci);
        idg_hp_hon8w.AT(k, x) = max(idg_hp_hon8w.AT(k, 67) * 0.8, idg_hp_hon8w.AT(k - 1, x - 1) * (1.0 + kaite_ci));
      }
      idr_hp_toku.AT(k, x) = sst::roundn(idr_hp_toku.AT(k - 1, x - 1) * (1.0 + cid), 3);
      idg_hp_toku.AT(k, x) = round(idr_hp_toku.AT(k, x) * 8042);

      idg_hp_siku.AT(k, x) = max(idg_hp_hon8w.AT(k, x), idg_hp_toku.AT(k, x));
      if(idg_hp_hon8w.AT(k, x) < idg_hp_toku.AT(k, x)) {
        arv_hp.AT(k, x) = 1.0 + cid;
      }
      else if(k <= marume_yr && idg_hp_hon8w.AT(k - 1, x - 1) >= idg_hp_toku.AT(k - 1, x - 1)) {
        arv_hp.AT(k, x) = sst::roundn(idg_hp_siku.AT(k, x) / idg_hp_siku.AT(k - 1, x - 1), 3);
      }
      else {
        arv_hp.AT(k, x) = idg_hp_siku.AT(k, x) / idg_hp_siku.AT(k - 1, x - 1);
      }
    }
    
    if(tamari_ci < 0.0 || k <= marume_yr) {
      hh.AT(k) = kaite_hhrd;
      ci.AT(k) = kaite_cird;
    }
    else {
      hh.AT(k) = kaite_hh;
      ci.AT(k) = kaite_ci;
    }

    if(id_hh_juzen.AT(k) < id_hh_toku.AT(k, 67)) {
      ci2.AT(k,67) = hhd;
    }
    else if(id_hh_juzen.AT(k - 1) < id_hh_toku.AT(k - 1, 67)) {
      ci2.AT(k, 67) = id_hh_juzen.AT(k) / id_hh_toku.AT(k - 1, 67) - 1.0;
    }
    else { 
      if(chinsura == 1 && k >= 21) {
        ci2.AT(k, 67) = ci.AT(k);
      } else {
        if(hhd < 0.0 && cid > 0.0) {
          ci2.AT(k, 67) = 0.0;
        } else {
          ci2.AT(k, 67) = ci.AT(k);
        }
      }
    }

    for(int x = 68; x <= 115; x++) {
      if(id_hh_juzen.AT(k) < id_hh_toku.AT(k, x)) {
        ci2.AT(k, x) = cid;
      }
      else if(id_hh_juzen.AT(k - 1) < id_hh_toku.AT(k - 1, x - 1)) {
        ci2.AT(k, x) = id_hh_juzen.AT(k) / id_hh_toku.AT(k - 1, x - 1) - 1.0;
      }
      else {
        ci2.AT(k, x) = ci.AT(k);
      }
    }

    if(idg_hp_hon8w.AT(k - 1, 67) < idg_hp_toku.AT(k - 1, 67)) {
      hp2.AT(k, 67) = arv_hp.AT(k, 67) - 1.0;
    }
    else if(k <= marume_yr) {
      hp2.AT(k, 67) = kaite_hprd;
    }
    else {
      hp2.AT(k, 67) = kaite_hp;
    }
    
    for(int x = 68; x <= 115; x++) {
      if(idg_hp_hon8w.AT(k - 1, x - 1) < idg_hp_toku.AT(k - 1, x - 1)) {
        hp2.AT(k, x) = arv_hp.AT(k, x) - 1.0;
      }
      else if(k <= marume_yr) {
        hp2.AT(k, x) = kaite_cird;
      }
      else {
        hp2.AT(k, x) = kaite_ci;
      }
    }

    tamari_ci = sst::roundn(tamari_ci + kaite_cird - cid, 3);
  }

  hh2_1999 = 0.4e-2;
  hh2_2000 = 0.7e-2;
  hh2_2001 = 0.8e-2;

  for(k = 1; k <= 4; k++) {
    ci.AT(k) = 0.0;
    if(k == 3 || k == 4) ci.AT(k) = ci0.AT(k - 1);

    for(int x = 67; x <= 115; x++) {
      ci2.AT(k, x) = ci.AT(k);
      hp2.AT(k, x) = ci.AT(k);
    }
  }


  for(int j = 1; j <= 23; j++) {
    for(int k = 1; k <= KE; k++) {
      if(j <= 14 && j != 13) {
        if(k <= 3) {
          rv.AT(k, j) = ci.AT(k);
          if(k == 1 || k == 2) {
            rv.AT(k, j) = 0.0;
          }
        } else if(k == 4) {
          if(j == 1 || j == 10) {
            rv.AT(k, j) = (1.0 + ci0.AT(3)) * sst::roundn((1.0 + hh2_1999) * (1.0 + hh2_2000) * (1.0 + hh2_2001), 3);
            rv.AT(k, j) = sst::roundn(rv.AT(k, j), 3) - 1.0;
          } else {
            rv.AT(k, j) = hp2.AT(k, 67);
          }
        } else {
          if(j == 1 || j == 10) {
            rv.AT(k, j) = hh.AT(k);
          } else {
            rv.AT(k, j) = hp2.AT(k, 67);
          }
        }
      } else if(j == 13) {
        rv.AT(k, j) = 0.0;
      } else {
        rv.AT(k, j) = rv.AT(k, same.AT(j));
      }
    }
  }

  
  ad.AT(KIJUN) = 1.0;
  for(k = KIJUN + 1; k <= KE; k++) {
    ad.AT(k) = ad.AT(k - 1) * (1.0 + h.AT(k));
    if(k <= marume_yr){
      ad.AT(k) = sst::roundn(ad.AT(k), 3);
    }
  }

  ad2.AT(4) = 0.988;
  for(int k = 5; k <= KIJUN; k++) {
    if(k == 15){
        ad2.AT(k) = ad2.AT(k - 1) * (1.0 + hp2.AT(k, 67)) * 0.991;
    } else if(k == 19){
        ad2.AT(k) = ad2.AT(k - 1) * (1.0 + hp2.AT(k, 67)) * 0.995;
    } else if(k == 20){
        ad2.AT(k) = ad2.AT(k - 1) * (1.0 + hp2.AT(k, 67)) * 0.999;
    } else {
        ad2.AT(k) = ad2.AT(k - 1) * (1.0 + hp2.AT(k, 67));
    }
    if(k <= marume_yr) {
      ad2.AT(k) = sst::roundn(ad2.AT(k), 3);
    }
  }


  for(int j = 1; j <= 23; j++) {
    bd.AT(KIJUN, j) = 1.0;
    for(int k = KIJUN+1; k <= KE; k++) {
      bd.AT(k, j) = bd.AT(k - 1, j) * (1.0 + rv.AT(k, j));
      if(k <= marume_yr){
        bd.AT(k, j) = sst::roundn(bd.AT(k, j), 3);
      }
    }
  }

  FILE *fp_a, *fp_b;
  fp_a = fp_map["kaitea"];
  fp_b = fp_map["kaiteb"];
  if(kaite == 1) { 
    if(pseid == 0) {
      for(int k = 5; k <= FLKE; k++) {
        vector<double> vals_hh, vals_hp;
        if(5 <= k && k <= KE) {
          for(int x = 67; x <= 115; x++) {
            vals_hh.push_back(arv_hh.AT(k, x));
            vals_hp.push_back(arv_hp.AT(k, x));
          }
        } else {
          vals_hh = vector<double>(115 - 67 + 1, 0.0);
          vals_hp = vector<double>(115 - 67 + 1, 0.0);
        }
        assert(vals_hh.size() == 115 - 67 + 1);
        assert(vals_hp.size() == 115 - 67 + 1);

        fprintf(fp_b, "%d,%s\n", k, csv::join(vals_hh).c_str());
        fprintf(fp_a, "%d,%s\n", k, csv::join(vals_hp).c_str());
      } 
    }
  }

  FILE *fp_fil = fp_map["prtfil"];
  fprintf(fp_fil, "·ÐºÑÅªÍ×ÁÇ\n");
  fprintf(fp_fil, "Ç¯ÅÙ,Íø²ó¤ê,ÄÂ¶â,Êª²Á,²þÄê¡ÊÈæÎã¡Ë,²þÄêÎ¨¡Ê²Ãµë¡Ë,²þÄêÎ¨¡Ê´ðÁÃ¡Ë,²þÄêÎ¨¡ÊÊª²Á¡Ë\n");
  for(int k = 1; k <= KE; k++) {
    fprintf(fp_fil,
      "%5d,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f,%8.5f\n",
      k, ri.AT(k), h.AT(k), ci.AT(k), rv.AT(k, 1), rv.AT(k, 4), rv.AT(k,14), ci2.AT(k, 67));
  }
}


void jitsuchin_kashobun(vector<double> &jh_kaite, vector<double> &koujor) {
  
  for(int k = 5; k <= KE; k++) {
  	double h_4_3_2;
  	h_4_3_2 = (1.0 + hdum.AT(k-4)) * (1.0 + hdum.AT(k - 3)) * (1.0 + hdum.AT(k - 2));
    jh_kaite.AT(k) = pow(h_4_3_2 , 1.0/3.0);
  }

  v1_t prema = VEC(double, ECEDY);
  prema.AT(3) = 13.58e-2;

  for(int k = 4; k <= KE; k++) {
    prema.AT(k) = prema.AT(k - 1) + 0.354e-2;
    if(prema.AT(k) > 18.3e-2) prema.AT(k) = 18.3e-2;
  }

  for(int k = 5; k <= KE; k++) {
    if(k <= 6) {
      koujor.AT(k) = 1.0;
    } else {
      koujor.AT(k) = (0.910 - prema.AT(k - 3) / 2.0) / (0.910 - prema.AT(k - 4) / 2.0);
    }

  }
}
