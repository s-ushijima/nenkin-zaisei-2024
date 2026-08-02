#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "cntl.h"


void setjinko(void) 
{

  int  TMP ;

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 2 ; sei++ ) {
      for ( nenrei = 106 ; nenrei <= 120 ; nenrei++ ) {
        if ( jinko_c[nendo-STARTY][sei][nenrei] > 0.0 ) {
          jinko_c[nendo-STARTY][sei][105] += jinko_c[nendo-STARTY][sei][nenrei] ;
          jinko_c[nendo-STARTY][sei][nenrei] = 0.0 ;
        }
      }
    }
  }
  for ( nendo = YUHAIGY + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 0 ; nenrei <= 105 ; nenrei++ ) {
      yuhaig_r[nendo-STARTY][nenrei] = yuhaig_r[nendo-1-STARTY][nenrei] ;
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 0 ; nenrei <= 105 ; nenrei++ ) {
      jinko_c[nendo-STARTY][3][nenrei]
       = jinko_c[nendo-STARTY][2][nenrei] * yuhaig_r[nendo-STARTY][nenrei] ;
      jinko_c[nendo-STARTY][4][nenrei]
       = jinko_c[nendo-STARTY][2][nenrei] - jinko_c[nendo-STARTY][3][nenrei] ;
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 0 ; nenrei <= 105 ; nenrei++ ) {
      jinko_c[nendo-STARTY][0][nenrei]
       = jinko_c[nendo-STARTY][1][nenrei] + jinko_c[nendo-STARTY][2][nenrei] ;
    }
  }
  if ( STARTY != SJINKOY ) {
    fprintf( stderr, "推計初年度 (STARTY) が人口のスタート年度 (JINKOY) と一致していません\n" ) ;
    exit(2) ;
  }
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 0 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 3 ; sei++ ) {
        if ( nenrei + SJINKOY - nendo > 0 ) {
          TMP = 0 ;
          TMP = nenrei + SJINKOY - nendo ;
          if ( nenrei < 105 ) {
            jinko_m[nendo-STARTY][sei][nenrei]
             = ( jinko_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMP-1] )
               + jinko_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMP] 
               + jinko_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMP-1] )
               + jinko_c[nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMP] ) / 2.0 ;
          }
          else if ( nenrei == 105 ) { 
            jinko_m[nendo-STARTY][sei][nenrei]
             = ( jinko_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMP-1] )
               + jinko_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMP] 
               + jinko_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMP-1] )
               + jinko_c[nendo-STARTY+1][sei][nenrei] * jinko_wari[sei][TMP-1] ) / 2.0 ;
          }
        }
        else {
          if ( ( nenrei > 0 ) && ( nenrei < 105 ) ) {
            jinko_m[nendo-STARTY][sei][nenrei]
             = ( jinko_c[nendo-STARTY][sei][nenrei-1]
               + jinko_c[nendo-STARTY][sei][nenrei] 
               + jinko_c[nendo-STARTY+1][sei][nenrei]
               + jinko_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
          }
          else if ( nenrei == 0 ) {
            jinko_m[nendo-STARTY][sei][nenrei]
             = ( jinko_c[nendo-STARTY][sei][nenrei] 
               + jinko_c[nendo-STARTY][sei][nenrei] 
               + jinko_c[nendo-STARTY+1][sei][nenrei]
               + jinko_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
          }
          else if ( nenrei == 105 ) {
            jinko_m[nendo-STARTY][sei][nenrei]
             = ( jinko_c[nendo-STARTY][sei][nenrei-1]
               + jinko_c[nendo-STARTY][sei][nenrei] 
               + jinko_c[nendo-STARTY+1][sei][nenrei]
               + jinko_c[nendo-STARTY+1][sei][nenrei] ) / 4.0 ;
          }
        }
      }
      jinko_m[nendo-STARTY][4][nenrei]
       = jinko_m[nendo-STARTY][2][nenrei] - jinko_m[nendo-STARTY][3][nenrei] ; 
      jinko_m[nendo-STARTY][0][nenrei]
       = jinko_m[nendo-STARTY][1][nenrei] + jinko_m[nendo-STARTY][2][nenrei] ; 
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    sojinko_c[nendo-STARTY][0]
     = sojinko_c[nendo-STARTY][1] + sojinko_c[nendo-STARTY][2] ;
  }
}
