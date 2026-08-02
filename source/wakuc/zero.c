#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "cntl.h"

void zero(void) 
{
  
  int  zkubun ;
  int  pkubun ;
  int  tkubun ;
  int  ykubun ;
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 0 ; nenrei <= 120 ; nenrei++ ) {
        jinko_c[nendo-STARTY][sei][nenrei] = 0.0 ; 
        jinko_m[nendo-STARTY][sei][nenrei] = 0.0 ; 
        sojinko_c[nendo-STARTY][sei] = 0.0 ;
        jinko_wari[sei][nenrei] = 0.0 ;
        yuhaig_r[nendo-STARTY][nenrei] = 0.0 ;
        roud_r[nendo-STARTY][sei][nenrei] = 0.0 ; 
        roud_j_c[nendo-STARTY][sei][nenrei] = 0.0 ; 
        roud_j_m[nendo-STARTY][sei][nenrei] = 0.0 ; 
        syugyo_r[nendo-STARTY][sei][nenrei] = 0.0 ;
        syugyo_j_c[nendo-STARTY][sei][nenrei] = 0.0 ;
        syugyo_j_m[nendo-STARTY][sei][nenrei] = 0.0 ;
        koyou_r[nendo-STARTY][sei][nenrei] = 0.0 ;
        hiseiki_tan_r_all[nendo-STARTY] = 0.0 ;
        for ( zkubun = 0 ; zkubun <= 3 ; zkubun++ ) {
          seiki_hiseiki_r[zkubun][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        for ( zkubun = 0 ; zkubun <= 4 ; zkubun++ ) {
          hiseiki_jikan_r[zkubun][nendo-STARTY] = 0.0 ;
    	}
        for ( zkubun = 0 ; zkubun <= 10 ; zkubun++ ) {
          heikinh_c[zkubun][nendo-STARTY] = 0.0 ;
          heikinh_m[zkubun][nendo-STARTY] = 0.0 ;
        }
        for ( zkubun = 0 ; zkubun <= 10 ; zkubun++ ) {
          koyou_j_c[zkubun][nendo-STARTY][sei][nenrei] = 0.0 ;
          koyou_j_m[zkubun][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        for ( zkubun = 0 ; zkubun <= 9 ; zkubun++ ) {
          soroudh_c[zkubun][nendo-STARTY][sei][nenrei] = 0.0 ;
          soroudh_m[zkubun][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        jieigyo_j_c[nendo-STARTY][sei][nenrei] = 0.0 ;
        jieigyo_j_m[nendo-STARTY][sei][nenrei] = 0.0 ;
        nigou[nendo-STARTY][sei][nenrei] = 0.0 ;
        for (seido = 0 ; seido <= 6 ; seido++ ) {
          kounen[seido][nendo-STARTY][sei][nenrei] = 0.0 ;
          sangou[seido][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        for (seido = 0 ; seido <= 2 ; seido++ ) {
          ichigou[seido][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        for ( zkubun = 0 ; zkubun <= 9 ; zkubun++ ) {
          kounenteki_c[zkubun][nendo-STARTY] = 0.0 ;
          kounenteki_m[zkubun][nendo-STARTY] = 0.0 ;
        }
        mika_soto[nendo-STARTY][sei][nenrei] = 0.0 ;
        ichiyuhaigr[nenrei] = 0.0 ;
        xend[nendo-STARTY] = 0 ;
        for ( pkubun = 0 ; pkubun <= 7 ; pkubun++ ) {
          for ( tkubun = 0 ; tkubun <= 3 ; tkubun++ ) {
            for ( ykubun= 0 ; ykubun <= 3 ; ykubun++ ) { 
              partnin[nendo-STARTY][sei][nenrei][pkubun][tkubun][ykubun] = 0.0 ;
              p_wari[nendo-STARTY][sei][nenrei][pkubun][tkubun][ykubun] = 0.0 ;
            }
          }
        }
      }
      for ( kubun = 0 ; kubun <= 16 ; kubun++ ) {
        for ( pkubun = 0 ; pkubun <= 7 ; pkubun++ ) {
          for ( tkubun = 0 ; tkubun <= 3 ; tkubun++ ) {
            for ( ykubun = 0 ; ykubun <= 3 ; ykubun++ ) { 
              kbetu_partnin[nendo-STARTY][sei][kubun][pkubun][tkubun][ykubun] = 0.0 ;
              kbetu_partkiso[sei][kubun][pkubun][tkubun][ykubun] = 0.0 ;
            }
          }
        }
      }
    }
  }
  for ( nendo = CNENDO ; nendo <= ENDY ; nendo++ ) {
    cutritu[nendo - CNENDO] = 0.0;
  }
}
