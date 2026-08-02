#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#ifdef SEPS_GLOBAL
  #define EXTERN 
#else
  #define EXTERN extern
#endif 

#include "_const.h"
#include "_vecarray.h"
#include <fstream>
#include <string>
#include <iostream>
#include <map>
using namespace std;

EXTERN int
  key, iname, iecon, iwname, konen, seidn, seidver;



EXTERN int
  kver, oldflg,
  psly, pslsi, pslsi2, seitaikey, kzn, kzny,
  seimei, seiy, kaite, zairo, chinsura,
  nenbeex, nenbe65, xb, xa, daik14,
  cht_flg, furikae_flg,kkuci,
  zaiteiyr, koza70, kozaiex2, kozaexyr,
  hiho70yr, flg_hiho70, flg_hiho,
  izokyuyr, jiiku2yr, flg_kaisho, flg_sankyu, sankyuyr,
  flg_fusiizo, fusiizoyr, flg_part, partyr1, partyr2, partyr3, partyr4,
  pahosei1, houjou, houjouyr, flg_hsr, hsr_endy, canyr,
  flg_sigo, atamauchi, flg_kozax, kozaxyr, kozax, flg_kozabase, kozabaseyr,
  flg_teizabase, teizabaseyr,flg_zaikai, zaikaiyr, flg_krgnr, krgnyr,flg_jshahosei,
  flg_saikanyu, flg_gtest, flg_bzwtest, flg_tuuroutest, flg_siktuika, flg_changekiso,flg_toukei,flg_hantei,
  flg_izoku, flg_shougai, flg_115, flg_kyuuzai,flg_zantei1, flg_zantei2, flg_kurisage, flg_tests,
  flg_okure, flg_taiki75, flg_inout,
  xend, tend;

EXTERN double
  hikrate, houjour1, houjour2, vvm, hsr_r, saikanyu;

EXTERN v4_t partbbn, partbbn2;

EXTERN v2_t kflcan;

EXTERN int
  xr, xxr, xrb, it;
EXTERN double
  tn, ta,
  pro, pros, pslr;
EXTERN v1_t tz;
EXTERN v3_t chwd;

EXTERN map<string, FILE*> fp_map;

EXTERN map<string, string> readpath_map;

EXTERN bool pstat_written;

EXTERN int pseid, k, s, s2;

EXTERN string cseid[8];

EXTERN v3_t
  pop, l, lpt, lpt1, lpt2, lpt2i,
  lpt2p, lpt3, lpt4;

EXTERN v1_t
  ri, h, ci0, dir, jz_shk,
  hh, ci,hdum,
  ad, ad2;
EXTERN double
  hh2_1999,
  hh2_2000,
  hh2_2001;

EXTERN v2_t
  ci2, hp2,
  bd;

EXTERN v1_t
  pre, pres,
  flt,
  adt, sadt, cadt,
  wife,
  can, can2,
  ha, hb,
  ema, emb, emc,
  ee;

EXTERN double
  pra, prb, pras, prbs,
  fl1, fl, minb,
  cad,
  wif,
  senll,
  srv;

EXTERN v4_t
  rs, sikr;

EXTERN v5_t
  sik, nos;

EXTERN v3_t
  qp, routsu;

EXTERN v5_t riss, nos2;
EXTERN v4_t rigd, rigk, rigbe;
EXTERN v3_t rkrsg, rig2;

EXTERN v2_t
  q2, ns, rt,
  cl, cl2,
  ikucoe, jiiku;

EXTERN v3_t
  u, q, rc,
  yx, br,
  bn, bnpt,
  dmpt2;

EXTERN v4_t kd;


EXTERN v2_t
  g, ge,
  gpt, bb, bbpt,
  gd;

EXTERN v3_t
  r, pshn;

EXTERN v4_t
  hn, z, ze, psz, psze,
  f, f_hik, f_min,
  kakor;

EXTERN v5_t
  w, we;

EXTERN v1_t
  rsen, pshnsen;

EXTERN v2_t
  hnsen, fsen, fsenhik, fsenmin;

EXTERN v3_t fkouzai2;

EXTERN v2_t kakorsn;
EXTERN v3_t vmini;

EXTERN v3_t t4k, t6dk;
EXTERN v4_t hn2k, t6k;
EXTERN v3_t t4, t6d;
EXTERN v4_t hn2, t6;
EXTERN v3_t rhantei, rhantei0;
EXTERN v4_t fhantei;

EXTERN v4_t 
  gee, geept, kfpr , g2, ge2, gz2, gn2, gez2, 
  bb2, z2, ze2, w2, we2,
  g3, gnp3, gpt3, bb3, bbnp3, bbpt3;  
EXTERN v2_t
  at,
  ap, ap65, ap70, ap75, ap85,
  appart, appart65, appart70, appart75, appart85,
  a, aiku, aal,
  a60, a65, a70, a75, a85,
  apdum, ap65dum, ap70dum, ap75dum, ap85dum,
  appartdum, appart65dum, appart70dum, appart75dum, appart85dum,
  adum, aikudum,
  a60dum, a65dum, a70dum, a75dum, a85dum;
EXTERN v3_t ax, gx, gtal, gztal, gntal, gnntal, getal, gnn2;
EXTERN v2_t
  apart, aikupart,
  a60part, a65part, a70part, a75part, a85part;

EXTERN v3_t fpart;
EXTERN v4_t j;
EXTERN v5_t j2, j3;

EXTERN v1_t parrater, parratet;
EXTERN v5_t d3, d3x, d3xs;

EXTERN v4_t okisor;
EXTERN v5_t okiso2x, dk3x;

EXTERN v3_t y, ypt, rn, pshnn, fpart2, fpart3;
EXTERN v2_t
  bbnp, gzpt, gnpt, 
  fsenn, fsennhik, fsennmin,
  hnsenn, kakorsnn;
EXTERN v1_t gnnpt, rsenn, pshnsenn;
EXTERN v4_t fn, fnhik, fnmin, hnn, kakorn;

EXTERN v1_t gnn;
EXTERN v2_t gn, gz, gez, ye;
EXTERN v3_t seiz;

EXTERN v5_t kfprx;

EXTERN v5_t kuri;


EXTERN v2_t
  apdmy, ap65dmy,
  ap70dmy, ap75dmy,
  ap85dmy, atdmy,
  admy, aikudmy,
  aaldmy;
EXTERN v5_t
  d3xdmy, kfprxdmy;

#undef EXTERN
#endif
