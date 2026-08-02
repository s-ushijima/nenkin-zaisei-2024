#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "cntl.h"


void simlkou(void) 
{

  double  TMP ;
  double  TMQ ;
  int     ii  ;
  double  kounen_cho[ENDY-STARTY+1][5][121] ;
  double  rk_sen[ENDY-STARTY+1][5][121] ;
  double  partyuhaigr_m[ENDY-STARTY+1][121] ;
  
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 0 ; nenrei <= 120 ; nenrei++ ) {
      partyuhaigr_m[nendo-STARTY+1][nenrei] = 0.0 ;
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        kounen_cho[nendo-STARTY][sei][nenrei] = 0.0 ;
        rk_sen[nendo-STARTY][sei][nenrei] = 0.0 ; 
      }
    }
  }
  
  for ( nendo = ROUDYR + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( ii = 1 ; ii <= 6 ; ii++ ) {
      kounenteki_c[ii][nendo-STARTY] = kounenteki_c[ii][nendo-1-STARTY] ;
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( ii = 1 ; ii <= 6 ; ii++ ) {
      kounenteki_m[ii][nendo-STARTY]
       = ( kounenteki_c[ii][nendo-STARTY] + kounenteki_c[ii][nendo+1-STARTY] ) / 2.0 ;
    }
  }

  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( sei = 1 ; sei <= 2 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      	 partnin[nendo-STARTY][sei][nenrei][0][0][0]
          = partnin[KIJUNMAP-STARTY][sei][nenrei][0][0][0]
             * ( koyou_j_m[4][nendo-STARTY][sei][nenrei] + koyou_j_m[5][nendo-STARTY][sei][nenrei] )
      	     / ( koyou_j_m[4][KIJUNMAP-STARTY][sei][nenrei] + koyou_j_m[5][KIJUNMAP-STARTY][sei][nenrei] ) ;
      }
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      TMP = 0.0 ;  TMQ = 0.0 ;
      TMP = koyou_j_m[4][nendo-STARTY][3][nenrei] + koyou_j_m[5][nendo-STARTY][3][nenrei] ; 
      TMQ = koyou_j_m[4][nendo-STARTY][4][nenrei] + koyou_j_m[5][nendo-STARTY][4][nenrei] ; 
      if ( TMP + TMQ > 0.0 ) {
        partyuhaigr_m[nendo-STARTY][nenrei] = TMP / ( TMP + TMQ ) ;
      }
      else {
        partyuhaigr_m[nendo-STARTY][nenrei] = 0.0 ;
      }
      partnin[nendo-STARTY][3][nenrei][0][0][0]
       =  partnin[nendo-STARTY][2][nenrei][0][0][0] * partyuhaigr_m[nendo-STARTY][nenrei] ;
      partnin[nendo-STARTY][4][nenrei][0][0][0]
       =  partnin[nendo-STARTY][2][nenrei][0][0][0] * ( 1.0 - partyuhaigr_m[nendo-STARTY][nenrei] ) ;
      partnin[nendo-STARTY][0][nenrei][0][0][0]
	   =  partnin[nendo-STARTY][1][nenrei][0][0][0] + partnin[nendo-STARTY][2][nenrei][0][0][0] ;
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        if ( nendo <= KIJUNMAP ) {
          TMP = 0.0 ; 
          for ( ii = 1 ; ii <= 6 ; ii++ ) {
            TMP += koyou_j_m[ii][nendo-STARTY][sei][nenrei] * kounenteki_m[ii][nendo-STARTY] ;
          }
          if ( TMP > 0.0 ) {
            kounen_cho[nendo-STARTY][sei][nenrei]
             = ( kounen[1][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0]
               + kounen[4][nendo-STARTY][sei][nenrei]
			   + kounen[5][nendo-STARTY][sei][nenrei]
			   + kounen[6][nendo-STARTY][sei][nenrei] ) / TMP ;
          }
          else {
            kounen_cho[nendo-STARTY][sei][nenrei] = 0.0 ;
          }
        }
        else {
          if ( nenrei <= 69 ) {
            kounen_cho[nendo-STARTY][sei][nenrei] = kounen_cho[nendo-1-STARTY][sei][nenrei] ;
          }
          else {
            if( kounen_cho[nendo-1-STARTY][sei][nenrei] < kounen_cho[nendo-1-STARTY][sei][nenrei-1] ) {
              kounen_cho[nendo-STARTY][sei][nenrei] = kounen_cho[nendo-1-STARTY][sei][nenrei] ;
            }
            else {
              kounen_cho[nendo-STARTY][sei][nenrei] = kounen_cho[nendo-1-STARTY][sei][nenrei-1] ;
            }
          }
        }
      }
      kounen_cho[nendo-STARTY][3][nenrei] = kounen_cho[nendo-STARTY][2][nenrei] ;
      kounen_cho[nendo-STARTY][4][nenrei] = kounen_cho[nendo-STARTY][2][nenrei] ;
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        kounen[1][nendo-STARTY][sei][nenrei]
         = ( koyou_j_m[1][nendo-STARTY][sei][nenrei] * kounenteki_m[1][nendo-STARTY] 
           + koyou_j_m[2][nendo-STARTY][sei][nenrei] * kounenteki_m[2][nendo-STARTY]
           + koyou_j_m[3][nendo-STARTY][sei][nenrei] * kounenteki_m[3][nendo-STARTY]
           + koyou_j_m[4][nendo-STARTY][sei][nenrei] * kounenteki_m[4][nendo-STARTY]
           + koyou_j_m[5][nendo-STARTY][sei][nenrei] * kounenteki_m[5][nendo-STARTY]
           + koyou_j_m[6][nendo-STARTY][sei][nenrei] * kounenteki_m[6][nendo-STARTY] ) * kounen_cho[nendo-STARTY][sei][nenrei]
           - partnin[nendo-STARTY][sei][nenrei][0][0][0]
           - kounen[4][nendo-STARTY][sei][nenrei]
           - kounen[5][nendo-STARTY][sei][nenrei]
           - kounen[6][nendo-STARTY][sei][nenrei] ;
	  }
	  kounen[1][nendo-STARTY][0][nenrei]
       = kounen[1][nendo-STARTY][1][nenrei] + kounen[1][nendo-STARTY][2][nenrei] ;
	}
  }
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 70 ; nenrei <= 100 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        if ( kounen[1][nendo-STARTY][sei][nenrei] > kounen[1][nendo-1-STARTY][sei][nenrei-1] * 0.98 ) {
          kounen[1][nendo-STARTY][sei][nenrei] = kounen[1][nendo-1-STARTY][sei][nenrei-1] * 0.98 ; 
        }
	  }
	  kounen[1][nendo-STARTY][2][nenrei]
	   = kounen[1][nendo-STARTY][3][nenrei] + kounen[1][nendo-STARTY][4][nenrei] ;
	  for ( sei = 1 ; sei <= 4 ; sei++ ) {
        kounen_cho[nendo-STARTY][sei][nenrei]
         = kounen[1][nendo-STARTY][sei][nenrei] 
            / ( koyou_j_m[1][nendo-STARTY][sei][nenrei] * kounenteki_m[1][nendo-STARTY]
              + koyou_j_m[2][nendo-STARTY][sei][nenrei] * kounenteki_m[2][nendo-STARTY]
              + koyou_j_m[3][nendo-STARTY][sei][nenrei] * kounenteki_m[3][nendo-STARTY]
              + koyou_j_m[4][nendo-STARTY][sei][nenrei] * kounenteki_m[4][nendo-STARTY]
              + koyou_j_m[5][nendo-STARTY][sei][nenrei] * kounenteki_m[5][nendo-STARTY]
              + koyou_j_m[6][nendo-STARTY][sei][nenrei] * kounenteki_m[6][nendo-STARTY] ) ;
      }
      kounen[1][nendo-STARTY][0][nenrei]
       = kounen[1][nendo-STARTY][1][nenrei] + kounen[1][nendo-STARTY][2][nenrei] ;
	}
  }

  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 69 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        koyou_j_m[8][nendo-STARTY][sei][nenrei]
         =  koyou_j_m[1][nendo-STARTY][sei][nenrei]
          * kounenteki_m[1][nendo-STARTY]
          * kounen_cho[nendo-STARTY][sei][nenrei] ;
        koyou_j_m[9][nendo-STARTY][sei][nenrei]
         =  koyou_j_m[2][nendo-STARTY][sei][nenrei]
          * kounenteki_m[2][nendo-STARTY]
          * kounen_cho[nendo-STARTY][sei][nenrei] ;
        koyou_j_m[10][nendo-STARTY][sei][nenrei]
         = ( koyou_j_m[3][nendo-STARTY][sei][nenrei] * kounenteki_m[3][nendo-STARTY]
           + koyou_j_m[4][nendo-STARTY][sei][nenrei] * kounenteki_m[4][nendo-STARTY]
           + koyou_j_m[5][nendo-STARTY][sei][nenrei] * kounenteki_m[5][nendo-STARTY]
           + koyou_j_m[6][nendo-STARTY][sei][nenrei] * kounenteki_m[6][nendo-STARTY] )
           * kounen_cho[nendo-STARTY][sei][nenrei] ;
        koyou_j_m[7][nendo-STARTY][sei][nenrei]
         =  koyou_j_m[8][nendo-STARTY][sei][nenrei]
          + koyou_j_m[9][nendo-STARTY][sei][nenrei]
          + koyou_j_m[10][nendo-STARTY][sei][nenrei] ;
      }
      for ( ii = 7 ; ii <= 10 ; ii++ ) {
        koyou_j_m[ii][nendo-STARTY][0][nenrei]
         = koyou_j_m[ii][nendo-STARTY][1][nenrei] + koyou_j_m[ii][nendo-STARTY][2][nenrei] ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= KIJUNMAP ; nendo++ ) {
	for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
	  for ( sei = 1 ; sei <= 2 ; sei++ ) {
        if ( kounen[1][nendo-STARTY][sei][nenrei] > 0.0 ) {
          rk_sen[nendo-STARTY][sei][nenrei]
           = kounen[3][nendo-STARTY][sei][nenrei] / kounen[1][nendo-STARTY][sei][nenrei] ; 
		}
      }
	}
  }
  for ( nendo = KIJUNMAP + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      if ( nenrei <= 29 ) {
        for ( ii = STARTY ; ii <= KIJUNMAP ; ii++ ) {
          rk_sen[nendo-STARTY][1][nenrei] += rk_sen[ii-STARTY][1][nenrei] ;
        }
        rk_sen[nendo-STARTY][1][nenrei] /= KIJUNMAP - STARTY + 1 ;
      }
      else if ( nenrei >= 85 ) {
        rk_sen[nendo-STARTY][1][nenrei] = 0.0 ;
      }
      else {
        rk_sen[nendo-STARTY][1][nenrei] = rk_sen[nendo-1 -STARTY][1][nenrei-1] ;
      }
      
      for ( sei = 2 ; sei <= 4 ; sei++ ) {
        rk_sen[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        kounen[3][nendo-STARTY][sei][nenrei]
         = kounen[1][nendo-STARTY][sei][nenrei] * rk_sen[nendo-STARTY][sei][nenrei] ;
        kounen[2][nendo-STARTY][sei][nenrei]
         = kounen[1][nendo-STARTY][sei][nenrei] - kounen[3][nendo-STARTY][sei][nenrei] ;
      }
      kounen[3][nendo-STARTY][0][nenrei]
       = kounen[3][nendo-STARTY][1][nenrei] + kounen[3][nendo-STARTY][2][nenrei] ;
      kounen[2][nendo-STARTY][0][nenrei]
       = kounen[2][nendo-STARTY][1][nenrei] + kounen[2][nendo-STARTY][2][nenrei] ;
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    TMP = 0.0 ;  TMQ = 0.0 ;
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
        soroudh_m[6][nendo-STARTY][sei][nenrei]
         = koyou_j_m[8][nendo-STARTY][sei][nenrei] * heikinh_m[1][nendo-STARTY] ; 
        soroudh_m[7][nendo-STARTY][sei][nenrei]
         = koyou_j_m[9][nendo-STARTY][sei][nenrei] * heikinh_m[2][nendo-STARTY] ; 
        soroudh_m[8][nendo-STARTY][sei][nenrei]
         = koyou_j_m[10][nendo-STARTY][sei][nenrei] * heikinh_m[8][nendo-STARTY] ; 
        soroudh_m[9][nendo-STARTY][sei][nenrei]
         =  soroudh_m[6][nendo-STARTY][sei][nenrei]
          + soroudh_m[7][nendo-STARTY][sei][nenrei]
          + soroudh_m[8][nendo-STARTY][sei][nenrei] ;
        if ( sei == 0 ) {
       	  if ( nenrei <= 69 ) {
            TMP += koyou_j_m[7][nendo-STARTY][0][nenrei] ;
            TMQ += soroudh_m[9][nendo-STARTY][0][nenrei] ;
          }
        }
      }
    }
    heikinh_m[10][nendo-STARTY] = TMQ / TMP ;
  }
  
  for ( nendo = STARTY + 1 ; nendo <= ENDY - 1 ; nendo++ ) {
    TMP = 0.0 ;  TMQ = 0.0 ;
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
        for ( ii = 8 ; ii <= 10 ; ii++ ) {
          koyou_j_c[ii][nendo-STARTY][sei][nenrei] 
           = ( koyou_j_m[ii][nendo-1-STARTY][sei][nenrei] + koyou_j_m[ii][nendo-STARTY][sei][nenrei] ) / 2.0 ;
        }
        koyou_j_c[7][nendo-STARTY][sei][nenrei]
         = koyou_j_c[8][nendo-STARTY][sei][nenrei]
         + koyou_j_c[9][nendo-STARTY][sei][nenrei]
         + koyou_j_c[10][nendo-STARTY][sei][nenrei] ;
        soroudh_c[6][nendo-STARTY][sei][nenrei]
         = koyou_j_c[8][nendo-STARTY][sei][nenrei] * heikinh_c[1][nendo-STARTY] ; 
        soroudh_c[7][nendo-STARTY][sei][nenrei]
         = koyou_j_c[9][nendo-STARTY][sei][nenrei] * heikinh_c[2][nendo-STARTY] ; 
        soroudh_c[8][nendo-STARTY][sei][nenrei]
         = koyou_j_c[10][nendo-STARTY][sei][nenrei] * heikinh_c[8][nendo-STARTY] ; 
        soroudh_c[9][nendo-STARTY][sei][nenrei]
         =  soroudh_c[6][nendo-STARTY][sei][nenrei]
          + soroudh_c[7][nendo-STARTY][sei][nenrei]
          + soroudh_c[8][nendo-STARTY][sei][nenrei] ;
        if ( sei == 0 ) {
          if ( nenrei <= 69 ) {
            TMP += koyou_j_c[7][nendo-STARTY][0][nenrei] ;
            TMQ += soroudh_c[9][nendo-STARTY][0][nenrei] ;
          }
        }
      }
    }
    heikinh_c[10][nendo-STARTY] = TMQ / TMP ;
  }
  
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
        kounen[1][nendo-STARTY][sei][nenrei]
         = kounen[2][nendo-STARTY][sei][nenrei] + kounen[3][nendo-STARTY][sei][nenrei] ;
        kounen[0][nendo-STARTY][sei][nenrei]
         = kounen[1][nendo-STARTY][sei][nenrei] ;
        if ( nenrei <= 69 ) {
          nigou[nendo-STARTY][sei][nenrei] = kounen[1][nendo-STARTY][sei][nenrei] ;
        }
        else {
          nigou[nendo-STARTY][sei][nenrei] = 0.0 ;
        }
        for ( seido = 4 ; seido <= 6 ; seido++ ) {
          nigou[nendo-STARTY][sei][nenrei] += kounen[seido][nendo-STARTY][sei][nenrei] ;
          kounen[0][nendo-STARTY][sei][nenrei] += kounen[seido][nendo-STARTY][sei][nenrei] ;
        }
      }
    }
  }
}
