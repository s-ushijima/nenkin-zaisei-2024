#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "cntl.h"


void simlichisan(void) 
{

  double  TMP  ;
  double  TMQ  ;
  int     ii   ;
  int     XEND ;
  double  r_ichigouni[5][121] ;
  double  r_mika_soto[ENDY-STARTY+1][5][121] ; 
  double  keisu ;


  for ( nenrei = 0 ; nenrei <= 100 ; nenrei++ ) {
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      r_ichigouni[sei][nenrei] = 0.0 ;
      for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
        r_mika_soto[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= KIJUNMAP ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      for ( ii = 1 ; ii <= 2 ; ii++ ) {
        ichigou[ii][nendo-STARTY][3][nenrei] = ichigou[ii][nendo-STARTY][2][nenrei] * ichiyuhaigr[nenrei] ;
        ichigou[ii][nendo-STARTY][4][nenrei] = ichigou[ii][nendo-STARTY][2][nenrei] * ( 1.0 - ichiyuhaigr[nenrei] ) ;
      }
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        ichigou[0][nendo-STARTY][sei][nenrei]
         = ichigou[1][nendo-STARTY][sei][nenrei] + ichigou[2][nendo-STARTY][sei][nenrei] ;
      }
      for ( ii = 0 ; ii <= 6 ; ii++ ) {
        sangou[ii][nendo-STARTY][3][nenrei] = sangou[ii][nendo-STARTY][2][nenrei] ;
        sangou[ii][nendo-STARTY][4][nenrei] = 0.0 ;
      }
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        sangou[0][nendo-STARTY][sei][nenrei] = sangou[1][nendo-STARTY][sei][nenrei] ;
        for ( seido = 4 ; seido <= 6 ; seido++ ) {
          sangou[0][nendo-STARTY][sei][nenrei] += sangou[seido][nendo-STARTY][sei][nenrei] ;
        }
      }
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        mika_soto[nendo-STARTY][sei][nenrei]
         =  jinko_m[nendo-STARTY][sei][nenrei] - ichigou[0][nendo-STARTY][sei][nenrei]
          - nigou[nendo-STARTY][sei][nenrei] - sangou[0][nendo-STARTY][sei][nenrei]
          - partnin[nendo-STARTY][sei][nenrei][0][0][0] ; 
        r_mika_soto[nendo-STARTY][sei][nenrei]
         = mika_soto[nendo-STARTY][sei][nenrei] / jinko_m[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( sei = 1 ; sei <= 2 ; sei++ ) {
    for ( nenrei = 20 ; nenrei <= 69 ; nenrei++ ) {
      if ( nenrei <= 59 ) {
        r_ichigouni[sei][nenrei]
         = ichigou[2][KIJUNMAP-STARTY][sei][nenrei] / jinko_m[KIJUNMAP-STARTY][sei][nenrei] ;
      }
      else {
        r_ichigouni[sei][nenrei]
         = ichigou[2][KIJUNMAP-STARTY][sei][nenrei]
          / ( jinko_m[KIJUNMAP-STARTY][sei][nenrei] - nigou[KIJUNMAP-STARTY][sei][nenrei]
            - partnin[KIJUNMAP-STARTY][sei][nenrei][0][0][0] ) ;
	  }
    }
  }
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 20 ; nenrei <= 69 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        if ( nenrei <= 59 ) {
          ichigou[2][nendo-STARTY][sei][nenrei]
           = jinko_m[nendo-STARTY][sei][nenrei] * r_ichigouni[sei][nenrei] ;
        }
        else {
		  ichigou[2][nendo-STARTY][sei][nenrei]
		   = ( jinko_m[nendo-STARTY][sei][nenrei] - nigou[nendo-STARTY][sei][nenrei]
             - partnin[nendo-STARTY][sei][nenrei][0][0][0] )
			 * r_ichigouni[sei][nenrei] ;
		}
      }
      ichigou[2][nendo-STARTY][3][nenrei]
       = ichigou[2][nendo-STARTY][2][nenrei] * ichiyuhaigr[nenrei]
          * ( jinko_m[nendo-STARTY][3][nenrei] / jinko_m[nendo-STARTY][2][nenrei] )
		  / ( jinko_m[KIJUNMAP-STARTY][3][nenrei] / jinko_m[KIJUNMAP-STARTY][2][nenrei] );
      ichigou[2][nendo-STARTY][4][nenrei]
       = ichigou[2][nendo-STARTY][2][nenrei] - ichigou[2][nendo-STARTY][3][nenrei] ;
      ichigou[2][nendo-STARTY][0][nenrei]
       = ichigou[2][nendo-STARTY][1][nenrei] + ichigou[2][nendo-STARTY][2][nenrei] ;
    }
  }
  
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 20 ; nenrei <= 64 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        if ( nenrei <= 20 + 1 ) {
          r_mika_soto[nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        else {
		  if ( nendo >= 2040 ) {
			keisu = 0.0 ;
		  }
		  else {
			keisu = ( double ) ( 2040 - nendo ) / ( double ) ( 2040 - nendo + 1 ) ;
		  }
      	  r_mika_soto[nendo-STARTY][sei][nenrei]
           =  r_mika_soto[nendo-1-STARTY][sei][nenrei-1] * keisu ;
        }
        mika_soto[nendo-STARTY][sei][nenrei]
         = jinko_m[nendo-STARTY][sei][nenrei] * r_mika_soto[nendo-STARTY][sei][nenrei] ;
      }
	  if ( nenrei - ( nendo - KIJUNMAP ) > 20 ) {
        mika_soto[nendo-STARTY][4][nenrei] 
         =  mika_soto[nendo-STARTY][2][nenrei]
	  	  * ( mika_soto[KIJUNMAP-STARTY][4][nenrei-(nendo-KIJUNMAP)] / mika_soto[KIJUNMAP-STARTY][2][nenrei-(nendo-KIJUNMAP)] )
          * ( jinko_m[nendo-STARTY][4][nenrei] / jinko_m[nendo-STARTY][2][nenrei] )
		  / ( jinko_m[KIJUNMAP-STARTY][4][nenrei-(nendo-KIJUNMAP)] / jinko_m[KIJUNMAP-STARTY][2][nenrei-(nendo-KIJUNMAP)] ) ;
	  }
	  else {
        mika_soto[nendo-STARTY][4][nenrei] 
         =  mika_soto[nendo-STARTY][2][nenrei] * ( jinko_m[nendo-STARTY][4][nenrei] / jinko_m[nendo-STARTY][2][nenrei] ) ;
	  }
      mika_soto[nendo-STARTY][3][nenrei] 
       = mika_soto[nendo-STARTY][2][nenrei] - mika_soto[nendo-STARTY][4][nenrei] ;
      mika_soto[nendo-STARTY][0][nenrei] 
       = mika_soto[nendo-STARTY][1][nenrei] + mika_soto[nendo-STARTY][2][nenrei] ;
    }
  }
  
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY ; nendo++ ) {
    XEND = xend[nendo-STARTY] ;
    for ( nenrei = 20 ; nenrei <= XEND - 1 ; nenrei++ ) {
      if ( kounen[1][KIJUNMAP-STARTY][3][nenrei] + partnin[KIJUNMAP-STARTY][3][nenrei][0][0][0] > 0.0 ) {
        sangou[1][nendo-STARTY][1][nenrei]
         =  sangou[1][KIJUNMAP-STARTY][1][nenrei]
          * ( kounen[1][nendo-STARTY][3][nenrei] + partnin[nendo-STARTY][3][nenrei][0][0][0] )
          / ( kounen[1][KIJUNMAP-STARTY][3][nenrei] + partnin[KIJUNMAP-STARTY][3][nenrei][0][0][0]) ;
      }
      else {
        sangou[1][nendo-STARTY][1][nenrei] = 0.0 ;
      }
      sangou[3][nendo-STARTY][1][nenrei] = 0.0 ;
      sangou[2][nendo-STARTY][1][nenrei] = sangou[1][nendo-STARTY][1][nenrei] ;
      for ( seido = 4 ; seido <= 6 ; seido++ ) {
        if ( kounen[seido][KIJUNMAP-STARTY][3][nenrei] > 0.0 ) {
          sangou[seido][nendo-STARTY][1][nenrei]
           =  sangou[seido][KIJUNMAP-STARTY][1][nenrei]
            * kounen[seido][nendo-STARTY][3][nenrei] / kounen[seido][KIJUNMAP-STARTY][3][nenrei] ;
        }
        else {
          sangou[seido][nendo-STARTY][1][nenrei] = 0.0 ;
        }
      }
      sangou[0][nendo-STARTY][1][nenrei] = sangou[1][nendo-STARTY][1][nenrei] ;
      for ( seido = 4 ; seido <= 6 ; seido++ ) {
        sangou[0][nendo-STARTY][1][nenrei] += sangou[seido][nendo-STARTY][1][nenrei] ;
      }
    }
  }
  
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY ; nendo++ ) {
    XEND = xend[nendo-STARTY] ; 
    for ( nenrei = 20 ; nenrei <= XEND - 1 ; nenrei++ ) {
      TMP = jinko_m[KIJUNMAP-STARTY][3][nenrei] - nigou[KIJUNMAP-STARTY][3][nenrei] - partnin[KIJUNMAP-STARTY][3][nenrei][0][0][0] ;
      TMQ = jinko_m[nendo-STARTY][3][nenrei] - nigou[nendo-STARTY][3][nenrei] - partnin[nendo-STARTY][3][nenrei][0][0][0] ;
      if ( ( TMP > 0.0 ) && ( TMQ > 0.0 ) ) {
        sangou[0][nendo-STARTY][3][nenrei]
         =  sangou[0][KIJUNMAP-STARTY][3][nenrei] * TMQ / TMP 
          * ( ( nigou[nendo-STARTY][1][nenrei] + partnin[nendo-STARTY][1][nenrei][0][0][0] ) / jinko_m[nendo-STARTY][1][nenrei] )
          / ( ( nigou[KIJUNMAP-STARTY][1][nenrei] + partnin[KIJUNMAP-STARTY][1][nenrei][0][0][0] ) / jinko_m[KIJUNMAP-STARTY][1][nenrei] ) ;
      }
      else { 
        sangou[0][nendo-STARTY][3][nenrei] = 0.0 ;
      }
      sangou[0][nendo-STARTY][4][nenrei] = 0.0 ;
      sangou[0][nendo-STARTY][2][nenrei] = sangou[0][nendo-STARTY][3][nenrei] ;
      
      sangou[1][nendo-STARTY][3][nenrei]
       =  sangou[0][nendo-STARTY][3][nenrei]
         * ( kounen[1][nendo-STARTY][1][nenrei] + partnin[nendo-STARTY][1][nenrei][0][0][0] )
         / ( nigou[nendo-STARTY][1][nenrei] + partnin[nendo-STARTY][1][nenrei][0][0][0] ) ;
      sangou[1][nendo-STARTY][4][nenrei] = 0.0 ;
      sangou[1][nendo-STARTY][2][nenrei] = sangou[1][nendo-STARTY][3][nenrei] ;
      sangou[3][nendo-STARTY][3][nenrei]
       =  sangou[0][nendo-STARTY][3][nenrei]
        * kounen[3][nendo-STARTY][1][nenrei] / ( nigou[nendo-STARTY][1][nenrei] + partnin[nendo-STARTY][1][nenrei][0][0][0] ) ; 
      sangou[3][nendo-STARTY][4][nenrei] = 0.0 ;
      sangou[3][nendo-STARTY][2][nenrei] = sangou[3][nendo-STARTY][3][nenrei] ;
      for ( sei = 2 ; sei <= 4 ; sei++ ) { 
        sangou[2][nendo-STARTY][sei][nenrei]
         = sangou[1][nendo-STARTY][sei][nenrei] - sangou[3][nendo-STARTY][sei][nenrei] ;
      }
      for ( seido = 4 ; seido <= 6 ; seido++ ) {
        sangou[seido][nendo-STARTY][3][nenrei]
         =  sangou[0][nendo-STARTY][3][nenrei]
          * kounen[seido][nendo-STARTY][1][nenrei] / ( nigou[nendo-STARTY][1][nenrei] +  partnin[nendo-STARTY][1][nenrei][0][0][0] );
        sangou[seido][nendo-STARTY][4][nenrei] = 0.0 ;
        sangou[seido][nendo-STARTY][2][nenrei] = sangou[seido][nendo-STARTY][3][nenrei] ;
      }
	  if ( MODE45 == 1 ) {
        for ( sei = 1 ; sei <= 3 ; sei++ ){
          for ( seido = 0 ; seido <= 6 ; seido++ ) {
            if ( nenrei >= 45 && nenrei <= 49 ) {
              sangou[seido][nendo-STARTY][sei][nenrei] *= 1.0 + ( XEND - 60 ) / 5.0 * 0.003 ;
            }
            else if ( nenrei >= 50 && nenrei <= 54 ) {
              sangou[seido][nendo-STARTY][sei][nenrei] *= 1.0 + ( XEND - 60 ) / 5.0 * 0.011 ;
            }
            else if ( nenrei >= 55 && nenrei <= 59 ) {
              sangou[seido][nendo-STARTY][sei][nenrei] *= 1.0 + ( XEND - 60 ) / 5.0 * 0.063 ;
            }
          }
        }
      }
      for ( seido = 0 ; seido <= 6 ; seido++ ) {
        sangou[seido][nendo-STARTY][0][nenrei]
         = sangou[seido][nendo-STARTY][1][nenrei] + sangou[seido][nendo-STARTY][2][nenrei] ;
      }
    }
  }
  
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY - 1 ; nendo++ ) {
    XEND = xend[nendo-STARTY] ; 
    for ( nenrei = 20 ; nenrei <= XEND - 1 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        TMP =  jinko_m[nendo-STARTY][sei][nenrei] - mika_soto[nendo-STARTY][sei][nenrei]
             - nigou[nendo-STARTY][sei][nenrei] - partnin[nendo-STARTY][sei][nenrei][0][0][0]
             - sangou[0][nendo-STARTY][sei][nenrei] - ichigou[2][nendo-STARTY][sei][nenrei] ;
        if ( TMP < 0.0 ) {
          fprintf( stderr, "%d年度 性%d 年齢%dの１号一般がマイナス!\n", nendo, sei, nenrei ) ;
          ichigou[1][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        else {
          ichigou[1][nendo-STARTY][sei][nenrei] = TMP ;
        }
      }
      ichigou[1][nendo-STARTY][2][nenrei]
       = ichigou[1][nendo-STARTY][3][nenrei] + ichigou[1][nendo-STARTY][4][nenrei] ;
      ichigou[1][nendo-STARTY][0][nenrei]
       = ichigou[1][nendo-STARTY][1][nenrei] + ichigou[1][nendo-STARTY][2][nenrei] ;
    }
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 20 ; nenrei <= 69 ; nenrei++ ) {
        ichigou[0][nendo-STARTY][sei][nenrei]
         = ichigou[1][nendo-STARTY][sei][nenrei] + ichigou[2][nendo-STARTY][sei][nenrei] ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    XEND = xend[nendo-STARTY] ; 
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 0 ; nenrei <= 19 ; nenrei++ ) {
        mika_soto[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
      for ( nenrei = XEND ; nenrei <= 100 ; nenrei++ ) {
        mika_soto[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  
  XEND = xend[KIJUNMAP-STARTY] ; 
  for ( sei = 0 ; sei <= 4 ; sei++ ) {
    for ( nenrei = XEND ; nenrei <= 100 ; nenrei++ ) {
      for ( seido = 0 ; seido <= 6 ; seido++ ) {
        sangou[seido][KIJUNMAP-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
}
