#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"

void cutout(void) 
{

  char    filename[250] ; 
  int     XEND   ;
  double  JYUMYO ;
  double  TMP[ENDY-STARTY+1] ; 
  double  TMQ[ENDY-STARTY+1] ; 
  int     TMQEND ;
  int     ii ;
  double  cutritu2[ENDY-CNENDO+1] ;
  double  kouteki[ENDY-STARTY+1][2] ;
  double  kouteki_cent[ENDY-STARTY+1][2] ;


  sprintf( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-m.csv", BANGO, BANGO ) ;
  if ( ( fp_cutout = fopen( filename, "w" ) ) == NULL ) {
    fprintf( stderr, "出力cutファイルを開けません!\n" ) ;
    exit (2) ;
  }

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( ii = 0 ; ii <= 1 ; ii++ ) {
      kouteki[nendo-STARTY][ii] = 0.0 ;
      kouteki_cent[nendo-STARTY][ii] = 0.0 ;
    }
    TMP[nendo - STARTY] = 0.0 ;
    TMQ[nendo - STARTY] = 0.0 ;
  }
  for ( nendo = CNENDO ; nendo <= ENDY ; nendo++ ) {
    cutritu2[nendo - CNENDO] = 0.0 ;
  }

  JYUMYO = 0.997 ;

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    XEND = xend[nendo-STARTY] ;
    for ( ii = 0 ; ii <= 1 ; ii++ ) {
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        for ( nenrei = 15 ; nenrei <= 110 ; nenrei++ ) {
          if ( nenrei < 70 ) {
            kouteki[nendo-STARTY][ii]
            += kounen[1][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
          }
          for ( seido = 4 ; seido <= 6 ; seido++ ) {
            kouteki[nendo-STARTY][ii] += kounen[seido][nendo-STARTY][sei][nenrei] ;
          }
          if ( ( nenrei >= 20 ) && ( nenrei < XEND ) ) {
            kouteki[nendo-STARTY][ii] += sangou[0][nendo-STARTY][sei][nenrei] ;
          }
          if ( ( nenrei >= 20 ) && ( nenrei < XEND ) ) {
            kouteki[nendo-STARTY][ii] += ichigou[1][nendo-STARTY][sei][nenrei] ;
          }
          if ( ( nenrei >= 20 ) && ( nenrei < 70 ) ) {
            kouteki[nendo-STARTY][ii] += ichigou[2][nendo-STARTY][sei][nenrei] ;
          }
		}
      }
    }
  }
  
  for ( ii = 0 ; ii <= 1 ; ii++ ) {
    kouteki_cent[STARTY-STARTY][ii]   = 67636858.0 ;
	kouteki_cent[STARTY+1-STARTY][ii] = 67446262.0 ;
	kouteki_cent[STARTY+2-STARTY][ii] = 67435295.0 ;
  }
  for ( nendo = STARTY + 3 ; nendo <= ENDY ; nendo++ ) {
    for ( ii = 0 ; ii <= 1 ; ii++ ) {
      kouteki_cent[nendo-STARTY][ii]
       = ( kouteki[nendo-1-STARTY][ii] + kouteki[nendo-STARTY][ii] ) / 2.0 ;
    }
  }
  
  for ( nendo = CUT_JY + 1 ; nendo <= ENDY ; nendo++ ) {
    if ( kouteki_cent[nendo-5-STARTY][0] > 0.0 ) {
      TMQEND = xend[nendo-2-STARTY] ;
      if ( MODE45 == 1 ) {
    	if ( ( TMQEND > 60 ) && ( nendo - 6 >= STARTY ) ) {
          for ( nenrei = 60 ; nenrei <= TMQEND - 1 ; nenrei++ ) {
            TMP[nendo-STARTY]
            += (  ichigou[1][nendo-6-STARTY][0][nenrei] + ichigou[1][nendo-5-STARTY][0][nenrei]
                 + sangou[0][nendo-6-STARTY][0][nenrei] +  sangou[0][nendo-5-STARTY][0][nenrei] ) / 2.0 ;
            TMQ[nendo-STARTY]
            += (  ichigou[1][nendo-3-STARTY][0][nenrei] + ichigou[1][nendo-2-STARTY][0][nenrei]
                 + sangou[0][nendo-3-STARTY][0][nenrei] +  sangou[0][nendo-2-STARTY][0][nenrei] ) / 2.0 ;
	      }
        }
      }
      cutritu[nendo-CNENDO] = pow( ( kouteki_cent[nendo-2-STARTY][0] - TMQ[nendo-STARTY] )
        	                     / ( kouteki_cent[nendo-5-STARTY][0] - TMP[nendo-STARTY] ) , 1.0 / 3.0 ) * JYUMYO ;
    }
    else {
      fprintf( stderr, "%02d年度の公的年金被保険者数が正しくありません!\n", nendo - 5 ) ;
      exit (2) ;
    }
  }

  for ( nendo = CNENDO ; nendo <= ENDY ; nendo++ ) {
    if ( cutritu[nendo-CNENDO] > 1.0 ) {
      cutritu[nendo-CNENDO] = 1.0 ;
    }
    cutritu2[nendo-CNENDO] = 1.0 / cutritu[nendo-CNENDO] - 1.0 ;
  }
  for ( nendo = CNENDO ; nendo <= ENDY ; nendo++ ) {
    cutritu[nendo-CNENDO] = raund( cutritu[nendo-CNENDO] , 6 ) ;
    cutritu2[nendo-CNENDO] = raund( cutritu2[nendo-CNENDO] , 4 ) ;
  }

  for ( nendo = CNENDO ; nendo <= KF ; nendo++ ) {
    fprintf( fp_cutout, "%4d,%7.6f\n", nendo, cutritu2[nendo-CNENDO] ) ;
  }
  fclose( fp_cutout ) ;
}
