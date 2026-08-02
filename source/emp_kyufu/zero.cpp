#include "sepscommon.h"
#include "sepslib.h"

void seps::zero_init(void) {
  partbbn  = VEC(double, 1, 1, 10, 2);
  partbbn2 = VEC(double, 1, 1, 10, 2);
  
    kflcan  = VEC(double, ENDY, C19(ENDY));
    
  pstat_written = false;

  xr = 0;
  xxr = 0;
  xrb = 0;
  it = 0;
  tn = 0.0;
  ta = 0.0;
  pro = 0.0;
  pros = 0.0;

  pslr = 0.0;
  tz = VEC(double, 4);

  kfprx = VEC(double, ENDY, 115, 6, 13, 8);

  apdmy   = VEC(double, ENDY, 11);
  ap65dmy = VEC(double, ENDY, 6);
  ap70dmy = VEC(double, ENDY, 6);
  ap75dmy = VEC(double, ENDY, 6);
  ap85dmy = VEC(double, ENDY, 6);
  atdmy   = VEC(double, ENDY, 17);
  admy    = VEC(double, ENDY, 11);
  aikudmy = VEC(double, ENDY, 6);
  aaldmy  = VEC(double, ENDY, 6);
}


void seps::zero_sepsd(void) {
  chwd  = VEC(double, 115, 100, 3);

  pop   = VEC(double, ENDY, 2, 115);
  l     = VEC(double, ENDY, 3, 115);
  lpt   = VEC(double, ENDY, 3, 115);
  lpt1  = VEC(double, ENDY, 3, 115);
  lpt2  = VEC(double, ENDY, 3, 115);
  lpt2i = VEC(double, ENDY, 3, 115);
  lpt2p = VEC(double, ENDY, 3, 115);
  lpt3  = VEC(double, ENDY, 3, 115);
  lpt4  = VEC(double, ENDY, 3, 115);

  ri      = VEC(double, ECEDY);
  h       = VEC(double, ECEDY);
  ci0     = VEC(double, ECEDY);
  dir     = VEC(double, ECEDY);
  jz_shk  = VEC(double, ECEDY);
  hh      = VEC(double, ECEDY);
  ci      = VEC(double, ECEDY);
  hdum    = VEC(double, ECEDY);
  ci2     = VEC(double, ECEDY, 115);
  hp2     = VEC(double, ECEDY, 115);
  ad      = VEC(double, ENDY);
  ad2     = VEC(double, ENDY);
  bd      = VEC(double, ENDY, 23);

  pre     = VEC(double, C19(-54));
  pres    = VEC(double, C19(-54));
  flt     = VEC(double, C19(ENDY));
  pra = prb = pras = prbs = 0.0;
  fl1 = fl = minb = 0.0;
  adt     = VEC(double, 3);
  sadt    = VEC(double, C19(ENDY));
  cadt    = VEC(double, C19(ENDY));
  cad = wif = 0.0;
  wife    = VEC(double, C19(ENDY));
  can     = VEC(double, C19(ENDY));
  can2    = VEC(double, C19(ENDY));
  senll = 0.0;
  ha      = VEC(double, 3);
  hb      = VEC(double, 3);
  ema     = VEC(double, 3);
  emb     = VEC(double, 3);
  emc     = VEC(double, 3);
  srv = 0.0;
  ee      = VEC(double, 2);
  rs      = VEC(double, 3, ENDY, 115, 4);
  sik     = VEC(double, ENDY, 115, 2, 19, 2);
  sikr     = VEC(double, 69, 2, 17, 2);
  routsu  = VEC(double, 2, 4, 3);
  nos     = VEC(double, ENDY, 69, 2, 17, 2);
  qp      = VEC(double, 100, 130, 2);

  riss    = VEC(double, ENDY, 70, 65, 3, 1);
  nos2    = VEC(double, ENDY, 69, 2, 4, 2);
  rigd    = VEC(double, 3, 70, 70, 1);
  rigk    = VEC(double, 3, 70, 70, 1);
  rigbe   = VEC(double, 3, 70, 70, 1);
  rkrsg   = VEC(double, 70, 3, 2);
  rig2    = VEC(double, 70, 3, 4);

  jiiku   = VEC(double, ENDY, 115);
  ikucoe  = VEC(double, ENDY, 115);
  q2      = VEC(double, ENDY, 115);
  ns      = VEC(double, ENDY, 115);
  rt      = VEC(double, ENDY, 115);
  cl      = VEC(double, ENDY, 3);
  cl2     = VEC(double, ENDY, 3);
  u       = VEC(double, ENDY, 115, 3);
  rc      = VEC(double, 3, ENDY, 115);
  q       = VEC(double, ENDY, 115, 3);
  yx      = VEC(double, ENDY, 115, 1);
  br      = VEC(double, ENDY, 115, 3);
  bn      = VEC(double, ENDY, 115, 3);
  bnpt    = VEC(double, ENDY, 115, 2);
  dmpt2   = VEC(double, ENDY, 115, 2);
  kd      = VEC(double, ENDY, 6, 4, 115);

  g       = VEC(double, 115, 100);
  ge      = VEC(double, 115, 100);
  gpt     = VEC(double, 115, 100);
  bb      = VEC(double, 115, 100);
  bbpt    = VEC(double, 115, 100);
  gd      = VEC(double, 65, 100);
  r       = VEC(double, 115, 15, 13);
  pshn    = VEC(double, 115, 15, 13);
  hn      = VEC(double, 115, 15, 13, 4);
  z       = VEC(double, 115, 100, 1, 9);
  ze      = VEC(double, 115, 100, 1, 9);
  psz     = VEC(double, 115, 100, 1, 7);
  psze    = VEC(double, 115, 100, 1, 7);
  f       = VEC(double, 115, 15, 13, 23);
  f_hik   = VEC(double, 115, 15, 13, 23);
  f_min   = VEC(double, 115, 15, 13, 23);
  w       = VEC(double, 115, 100, 0, 7, 3);
  we      = VEC(double, 115, 100, 0, 7, 3);
  rsen    = VEC(double, 70);
  hnsen   = VEC(double, 70, 2);
  pshnsen = VEC(double, 70);
  fsen    = VEC(double, 70, 23);
  fsenhik = VEC(double, 70, 23);
  fsenmin = VEC(double, 70, 23);
  fkouzai2 = VEC(double, 84, 15, 2);

 
  t4k     = VEC(double, 115, 15, 13);
  hn2k    = VEC(double, 115, 15, 13, 2);
  t6k     = VEC(double, 115, 15, 13, 23);
  
  t4      = VEC(double, 115, 15, 13);
  hn2     = VEC(double, 115, 15, 13, 2);
  t6      = VEC(double, 115, 15, 13, 23);
  rhantei = VEC(double, 115, 15, 4);
  rhantei0= VEC(double, 115, 15, 4);
  fhantei = VEC(double, 115, 15, 4, 23);

  gee     = VEC(double, ENDY, 3, 115, 100);
  geept   = VEC(double, ENDY, 3, 115, 100);
  g2      = VEC(double, ENDY, 3, 115, 100);
  ge2     = VEC(double, ENDY, 3, 115, 100);
  gz2     = VEC(double, ENDY, 3, 115, 100);
  gn2     = VEC(double, ENDY, 3, 115, 100);
  gez2    = VEC(double, ENDY, 3, 115, 100);
  
  bb2     = VEC(double, ENDY, 3, 115, 100);
  z2      = VEC(double, ENDY, 3, 115, 100);
  ze2     = VEC(double, ENDY, 3, 115, 100);
  w2      = VEC(double, ENDY, 3, 115, 100);
  we2     = VEC(double, ENDY, 3, 115, 100);
  
  g3      = VEC(double, ENDY, 3, 115, 100);
  gnp3    = VEC(double, ENDY, 3, 115, 100);
  gpt3    = VEC(double, ENDY, 3, 115, 100);
  bb3     = VEC(double, ENDY, 3, 115, 100);
  bbnp3   = VEC(double, ENDY, 3, 115, 100);
  bbpt3   = VEC(double, ENDY, 3, 115, 100);
  
  kfpr   = VEC(double, ENDY, 6, 13, 8);
  at          = VEC(double, ENDY, 3);
  ap          = VEC(double, ENDY, 3);
  ap65        = VEC(double, ENDY, 3);
  ap70        = VEC(double, ENDY, 3);
  ap75        = VEC(double, ENDY, 3);
  ap85        = VEC(double, ENDY, 3);
  appart      = VEC(double, ENDY, 3);
  appart65    = VEC(double, ENDY, 3);
  appart70    = VEC(double, ENDY, 3);
  appart75    = VEC(double, ENDY, 3);
  appart85    = VEC(double, ENDY, 3);
  a           = VEC(double, ENDY, 3);
  aiku        = VEC(double, ENDY, 3);
  aal         = VEC(double, ENDY, 3);
  a60         = VEC(double, ENDY, 3);
  a65         = VEC(double, ENDY, 3);
  a70         = VEC(double, ENDY, 3);
  a75         = VEC(double, ENDY, 3);
  a85         = VEC(double, ENDY, 3);
  apdum       = VEC(double, ENDY, 3);
  ap65dum     = VEC(double, ENDY, 3);
  ap70dum     = VEC(double, ENDY, 3);
  ap75dum     = VEC(double, ENDY, 3);
  ap85dum     = VEC(double, ENDY, 3);
  appartdum   = VEC(double, ENDY, 3);
  appart65dum = VEC(double, ENDY, 3);
  appart70dum = VEC(double, ENDY, 3);
  appart75dum = VEC(double, ENDY, 3);
  appart85dum = VEC(double, ENDY, 3);
  adum        = VEC(double, ENDY, 3);
  aikudum     = VEC(double, ENDY, 3);
  a60dum      = VEC(double, ENDY, 3);
  a65dum      = VEC(double, ENDY, 3);
  a70dum      = VEC(double, ENDY, 3);
  a75dum      = VEC(double, ENDY, 3);
  a85dum      = VEC(double, ENDY, 3);

  ax          = VEC(double, ENDY, 75, 3);
  gx          = VEC(double, ENDY, 75, 3);
  
  gtal        = VEC(double, ENDY, 75, 3);
  gztal       = VEC(double, ENDY, 75, 3);
  gntal       = VEC(double, ENDY, 75, 3);
  getal       = VEC(double, ENDY, 75, 3);
  

  apart       = VEC(double, ENDY, 3);
  aikupart    = VEC(double, ENDY, 3);
  a60part     = VEC(double, ENDY, 3);
  a65part     = VEC(double, ENDY, 3);
  a70part     = VEC(double, ENDY, 3);
  a75part     = VEC(double, ENDY, 3);
  a85part     = VEC(double, ENDY, 3);

  fpart       = VEC(double, 70, 15, 2);
  fpart2      = VEC(double, 70, 15, 2);
  fpart3      = VEC(double, 70, 15, 2);
  j           = VEC(double, 30, 3, 4, 15);
  j2          = VEC(double, 30, 3, 70, 15, 4);
  j3          = VEC(double, 30, 3, 70, 15, 4);

  parrater    = VEC(double, 2);
  parratet    = VEC(double, 2);
  d3      = VEC(double, ENDY, 6, 13, 58, 2);
  d3x     = VEC(double, ENDY, 115, 6, 13, 58); 
  d3xs    = VEC(double, ENDY, 115, 6, 13, 58);

  okisor  = VEC(double, ENDY, 2, 13, 4);
  okiso2x = VEC(double, ENDY, 115, 2, 3, 6);
  dk3x    = VEC(double, ENDY, 115, 2, 6, 10);

  y       = VEC(double, 115, 100, 3);
  ypt     = VEC(double, 115, 100, 3);
  rn      = VEC(double, 115, 100, 13);
  pshnn   = VEC(double, 115, 15, 13);

  bbnp    = VEC(double, 115, 100);
  gzpt    = VEC(double, 115, 100);
  gnpt    = VEC(double, 115, 100);

  fsenn     = VEC(double, 70, 23);
  fsennhik  = VEC(double, 70, 23);
  fsennmin  = VEC(double, 70, 23);
  hnsenn    = VEC(double, 70, 2);
  
  gnnpt     = VEC(double, 115);
  rsenn     = VEC(double, 70);
  pshnsenn  = VEC(double, 70);

  fn        = VEC(double, 115, 15, 13, 23);
  fnhik     = VEC(double, 115, 15, 13, 23);
  fnmin     = VEC(double, 115, 15, 13, 23);
  hnn       = VEC(double, 115, 15, 13, 2);

  gn        = VEC(double, 115, 100);
  gnn       = VEC(double, 115);
  gz        = VEC(double, 115, 100);
  gez       = VEC(double, 115, 100);
  ye        = VEC(double, 115, 100);
  seiz      = VEC(double, 115, 100, 20);

  kuri        = VEC(double,  ENDY, 2, 10, 70, 15);

  kfprx   = VEC(double, ENDY, 115, 6, 13, 8);

}
