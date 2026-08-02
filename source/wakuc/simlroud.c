#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
#include "cntl.h"


void simlroud(void) 
{

  double  TMP ;
  double  TMQ ; 
  double  TMR ;
  int     ii , TMS ;
  
  
  for ( nendo = ROUDYR + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        roud_r[nendo-STARTY][sei][nenrei] = roud_r[nendo-1-STARTY][sei][nenrei] ;
        syugyo_r[nendo-STARTY][sei][nenrei] = syugyo_r[nendo-1-STARTY][sei][nenrei] ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        roud_j_c[nendo-STARTY][sei][nenrei]
         = jinko_c[nendo-STARTY][sei][nenrei] * roud_r[nendo-STARTY][sei][nenrei] ;
        syugyo_j_c[nendo-STARTY][sei][nenrei]
         = jinko_c[nendo-STARTY][sei][nenrei] * syugyo_r[nendo-STARTY][sei][nenrei] ;
        koyou_j_c[0][nendo-STARTY][sei][nenrei]
         = syugyo_j_c[nendo-STARTY][sei][nenrei] * koyou_r[nendo-STARTY][sei][nenrei] ;
      }
      roud_j_c[nendo-STARTY][2][nenrei]
       = roud_j_c[nendo-STARTY][3][nenrei] + roud_j_c[nendo-STARTY][4][nenrei] ;
      roud_j_c[nendo-STARTY][0][nenrei]
       = roud_j_c[nendo-STARTY][1][nenrei] + roud_j_c[nendo-STARTY][2][nenrei] ;
      syugyo_j_c[nendo-STARTY][2][nenrei]
       = syugyo_j_c[nendo-STARTY][3][nenrei] + syugyo_j_c[nendo-STARTY][4][nenrei] ;
      syugyo_j_c[nendo-STARTY][0][nenrei]
       = syugyo_j_c[nendo-STARTY][1][nenrei] + syugyo_j_c[nendo-STARTY][2][nenrei] ;
	  koyou_j_c[0][nendo-STARTY][2][nenrei]
       = koyou_j_c[0][nendo-STARTY][3][nenrei] + koyou_j_c[0][nendo-STARTY][4][nenrei] ;
	  koyou_j_c[0][nendo-STARTY][0][nenrei]
       = koyou_j_c[0][nendo-STARTY][1][nenrei] + koyou_j_c[0][nendo-STARTY][2][nenrei] ;
    }
  }
    
  for ( nendo = KIJUN +1 ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        for ( ii= 1 ; ii <= 3 ; ii++ ) {
          seiki_hiseiki_r[ii][nendo-STARTY][sei][nenrei] = seiki_hiseiki_r[ii][nendo-1-STARTY][sei][nenrei] ;
        }
      }
    }
  }
  for ( nendo = ROUDYR + 1 ; nendo <= ENDY ; nendo++ ) {
    hiseiki_tan_r_all[nendo-STARTY] = hiseiki_tan_r_all[nendo-1-STARTY] ;
    for ( ii = 1 ; ii <= 4 ; ii++ ) {
      hiseiki_jikan_r[ii][nendo-STARTY] = hiseiki_jikan_r[ii][nendo-1-STARTY] ;
    }
  }
  
  for ( nendo = KIJUN + 1 ; nendo <= ENDY ; nendo++ ) {
    TMP = 0.0 ; TMQ = 0.0 ; TMR = 0.0 ;
    if ( nendo <= ROUDYR ) {
	  if ( hiseiki_tan_r_all[nendo-STARTY] > hiseiki_tan_r_all[KIJUN-STARTY] ) {
        for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
          TMP += koyou_j_c[0][nendo-STARTY][0][nenrei] * hiseiki_tan_r_all[nendo-STARTY] ; 
		  TMQ +=  koyou_j_c[0][nendo-STARTY][1][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][1][nenrei] 
                + koyou_j_c[0][nendo-STARTY][3][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][3][nenrei] 
                + koyou_j_c[0][nendo-STARTY][4][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][4][nenrei] ;
          TMR +=  koyou_j_c[0][nendo-STARTY][3][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][3][nenrei] ;
          if ( nenrei >= 60 ) {
            TMR +=  koyou_j_c[0][nendo-STARTY][1][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][1][nenrei] 
                  + koyou_j_c[0][nendo-STARTY][4][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][4][nenrei] ;
          }
	    }
        if ( TMP > TMQ ) { 
          for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
            seiki_hiseiki_r[3][nendo-STARTY][3][nenrei] *= 1 + ( TMP - TMQ ) / TMR ;
            if( nenrei >= 60 ) {
              seiki_hiseiki_r[3][nendo-STARTY][1][nenrei] *= 1 + ( TMP - TMQ ) / TMR ;
              seiki_hiseiki_r[3][nendo-STARTY][4][nenrei] *= 1 + ( TMP - TMQ ) / TMR ;
            }
          }
        }
      }
	}
    else {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
          seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] = seiki_hiseiki_r[3][ROUDYR-STARTY][sei][nenrei] ;
        }
      }
    }
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        if ( seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] + seiki_hiseiki_r[1][nendo-STARTY][sei][nenrei] > 1.0 ) {
          seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] = 1.0 - seiki_hiseiki_r[1][nendo-STARTY][sei][nenrei] ;
        }
        seiki_hiseiki_r[2][nendo-STARTY][sei][nenrei]
         = 1.0 - seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] - seiki_hiseiki_r[1][nendo-STARTY][sei][nenrei] ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        koyou_j_c[1][nendo-STARTY][sei][nenrei]
         = koyou_j_c[0][nendo-STARTY][sei][nenrei] * seiki_hiseiki_r[1][nendo-STARTY][sei][nenrei] ;
        koyou_j_c[2][nendo-STARTY][sei][nenrei]
         = koyou_j_c[0][nendo-STARTY][sei][nenrei] * seiki_hiseiki_r[2][nendo-STARTY][sei][nenrei] ;
        for( ii = 3 ; ii <= 6 ; ii++ ){
          koyou_j_c[ii][nendo-STARTY][sei][nenrei]
           = koyou_j_c[0][nendo-STARTY][sei][nenrei] * seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] * hiseiki_jikan_r[ii-2][nendo-STARTY] ;
        }
      }
      for ( ii = 1 ; ii <= 6 ; ii++ ) {
        koyou_j_c[ii][nendo-STARTY][2][nenrei]
         = koyou_j_c[ii][nendo-STARTY][3][nenrei] + koyou_j_c[ii][nendo-STARTY][4][nenrei] ;
      }
      for ( ii = 1 ; ii <= 6 ; ii++ ) {
        koyou_j_c[ii][nendo-STARTY][0][nenrei]
         = koyou_j_c[ii][nendo-STARTY][1][nenrei] + koyou_j_c[ii][nendo-STARTY][2][nenrei] ;
      }
    }
  }
    
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        jieigyo_j_c[nendo-STARTY][sei][nenrei]
         = syugyo_j_c[nendo-STARTY][sei][nenrei] - koyou_j_c[0][nendo-STARTY][sei][nenrei] ;
      }
    }
  }
  
  for ( nendo = ROUDYR + 1 ; nendo <= ENDY ; nendo++ ) {
    for ( ii = 1 ; ii <= 9 ; ii++ ) {
      heikinh_c[ii][nendo-STARTY] = heikinh_c[ii][nendo-1-STARTY] ;
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        soroudh_c[1][nendo-STARTY][sei][nenrei]
         = koyou_j_c[1][nendo-STARTY][sei][nenrei] * heikinh_c[1][nendo-STARTY] ;
        soroudh_c[2][nendo-STARTY][sei][nenrei]
         = koyou_j_c[2][nendo-STARTY][sei][nenrei] * heikinh_c[2][nendo-STARTY] ;
        soroudh_c[3][nendo-STARTY][sei][nenrei]
         = koyou_j_c[3][nendo-STARTY][sei][nenrei] * heikinh_c[3][nendo-STARTY]
         + koyou_j_c[4][nendo-STARTY][sei][nenrei] * heikinh_c[4][nendo-STARTY]
         + koyou_j_c[5][nendo-STARTY][sei][nenrei] * heikinh_c[5][nendo-STARTY]
         + koyou_j_c[6][nendo-STARTY][sei][nenrei] * heikinh_c[6][nendo-STARTY] ;
        soroudh_c[4][nendo-STARTY][sei][nenrei]
         = jieigyo_j_c[nendo-STARTY][sei][nenrei] * heikinh_c[7][nendo-STARTY] ;
        soroudh_c[0][nendo-STARTY][sei][nenrei]
         = soroudh_c[1][nendo-STARTY][sei][nenrei] + soroudh_c[2][nendo-STARTY][sei][nenrei]
         + soroudh_c[3][nendo-STARTY][sei][nenrei] + soroudh_c[4][nendo-STARTY][sei][nenrei] ;
      }
      for ( ii = 0 ; ii <= 4 ; ii++ ) {
        soroudh_c[ii][nendo-STARTY][2][nenrei]
         = soroudh_c[ii][nendo-STARTY][3][nenrei] + soroudh_c[ii][nendo-STARTY][4][nenrei] ;
        soroudh_c[ii][nendo-STARTY][0][nenrei]
         = soroudh_c[ii][nendo-STARTY][1][nenrei] + soroudh_c[ii][nendo-STARTY][2][nenrei] ;
      }
    }
  }

  if ( STARTY != SJINKOY ) {
    fprintf( stderr, "推計初年度 (STARTY) が人口のスタート年度 (JINKOY) と一致していません\n" ) ;
    exit(2) ;
  }

  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 3 ; sei++ ) {
        if ( nenrei + SJINKOY - nendo > 0 ) {
          TMS = 0 ;
          TMS = nenrei + SJINKOY - nendo ;
          if ( ( nenrei > 15 ) && ( nenrei < 105 ) ) {
            roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + roud_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + roud_j_c[nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + syugyo_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            for ( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
                 + koyou_j_c[ii][nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            }
          }
          else if ( nenrei == 15 ) {
            roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS] )
               + roud_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + roud_j_c[nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS] )
               + syugyo_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            for ( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS] )
                 + koyou_j_c[ii][nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei+1] * jinko_wari[sei][TMS] ) / 2.0 ;
            }
          }
          else if ( nenrei == 105 ) {
            roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + roud_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + roud_j_c[nendo-STARTY+1][sei][nenrei] * jinko_wari[sei][TMS-1] ) / 2.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + syugyo_j_c[nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] * jinko_wari[sei][TMS-1] ) / 2.0 ;
            for ( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei-1] * ( 1.0 - jinko_wari[sei][TMS-1] )
                 + koyou_j_c[ii][nendo-STARTY][sei][nenrei] * jinko_wari[sei][TMS]
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] * ( 1.0 - jinko_wari[sei][TMS-1] )
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] * jinko_wari[sei][TMS-1] ) / 2.0 ;
            }
          }
        }
        else {
          if ( ( nenrei > 15 ) && ( nenrei < 105 ) ) {
		    roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei-1] + roud_j_c[nendo-STARTY][sei][nenrei]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] + roud_j_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei-1] + syugyo_j_c[nendo-STARTY][sei][nenrei]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] + syugyo_j_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            for ( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei-1] + koyou_j_c[ii][nendo-STARTY][sei][nenrei] 
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            }
          }
          else if ( nenrei == 15 ) {
            roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei] + roud_j_c[nendo-STARTY][sei][nenrei]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] + roud_j_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei] + syugyo_j_c[nendo-STARTY][sei][nenrei]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] + syugyo_j_c[nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            for( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei] + koyou_j_c[ii][nendo-STARTY][sei][nenrei] 
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei+1] ) / 4.0 ;
            }
          }
          else if ( nenrei == 105 ) {
            roud_j_m[nendo-STARTY][sei][nenrei]
             = ( roud_j_c[nendo-STARTY][sei][nenrei-1] + roud_j_c[nendo-STARTY][sei][nenrei]
               + roud_j_c[nendo-STARTY+1][sei][nenrei] + roud_j_c[nendo-STARTY+1][sei][nenrei] ) / 4.0 ;
            syugyo_j_m[nendo-STARTY][sei][nenrei]
             = ( syugyo_j_c[nendo-STARTY][sei][nenrei-1] + syugyo_j_c[nendo-STARTY][sei][nenrei]
               + syugyo_j_c[nendo-STARTY+1][sei][nenrei] + syugyo_j_c[nendo-STARTY+1][sei][nenrei] ) / 4.0 ;
            for( ii = 0 ; ii <= 6 ; ii++ ) {
              koyou_j_m[ii][nendo-STARTY][sei][nenrei]
               = ( koyou_j_c[ii][nendo-STARTY][sei][nenrei-1] + koyou_j_c[ii][nendo-STARTY][sei][nenrei] 
                 + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] + koyou_j_c[ii][nendo-STARTY+1][sei][nenrei] ) / 4.0 ;
            }
          }
        }
      }
      roud_j_m[nendo-STARTY][4][nenrei]
       = roud_j_m[nendo-STARTY][2][nenrei] - roud_j_m[nendo-STARTY][3][nenrei] ;
      roud_j_m[nendo-STARTY][0][nenrei]
       = roud_j_m[nendo-STARTY][1][nenrei] + roud_j_m[nendo-STARTY][2][nenrei] ;
      syugyo_j_m[nendo-STARTY][4][nenrei]
       = syugyo_j_m[nendo-STARTY][2][nenrei] - syugyo_j_m[nendo-STARTY][3][nenrei] ;
      syugyo_j_m[nendo-STARTY][0][nenrei]
       = syugyo_j_m[nendo-STARTY][1][nenrei] + syugyo_j_m[nendo-STARTY][2][nenrei] ;
      for ( ii = 0 ; ii <= 6 ; ii++ ) {
        koyou_j_m[ii][nendo-STARTY][4][nenrei]
         = koyou_j_m[ii][nendo-STARTY][2][nenrei] - koyou_j_m[ii][nendo-STARTY][3][nenrei] ;
        koyou_j_m[ii][nendo-STARTY][0][nenrei]
         = koyou_j_m[ii][nendo-STARTY][1][nenrei] + koyou_j_m[ii][nendo-STARTY][2][nenrei] ;
      }
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 0 ; sei <= 4 ; sei++ ) {
        jieigyo_j_m[nendo-STARTY][sei][nenrei]
         = syugyo_j_m[nendo-STARTY][sei][nenrei] - koyou_j_m[0][nendo-STARTY][sei][nenrei] ;
      }
    }
  }
    
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( ii = 1 ; ii <= 9 ; ii++ ) {
      heikinh_m[ii][nendo-STARTY]
       = ( heikinh_c[ii][nendo-STARTY] + heikinh_c[ii][nendo+1-STARTY] ) / 2.0 ;
    }
  }
  
  for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      for ( sei = 1 ; sei <= 4 ; sei++ ) {
        soroudh_m[1][nendo-STARTY][sei][nenrei]
         = koyou_j_m[1][nendo-STARTY][sei][nenrei] * heikinh_m[1][nendo-STARTY] ;
        soroudh_m[2][nendo-STARTY][sei][nenrei]
         = koyou_j_m[2][nendo-STARTY][sei][nenrei] * heikinh_m[2][nendo-STARTY] ;
        soroudh_m[3][nendo-STARTY][sei][nenrei]
         = koyou_j_m[3][nendo-STARTY][sei][nenrei] * heikinh_m[3][nendo-STARTY]
         + koyou_j_m[4][nendo-STARTY][sei][nenrei] * heikinh_m[4][nendo-STARTY]
         + koyou_j_m[5][nendo-STARTY][sei][nenrei] * heikinh_m[5][nendo-STARTY]
         + koyou_j_m[6][nendo-STARTY][sei][nenrei] * heikinh_m[6][nendo-STARTY] ;
        soroudh_m[4][nendo-STARTY][sei][nenrei]
         = jieigyo_j_m[nendo-STARTY][sei][nenrei] * heikinh_m[7][nendo-STARTY] ;
        soroudh_m[0][nendo-STARTY][sei][nenrei]
         = soroudh_m[1][nendo-STARTY][sei][nenrei] + soroudh_m[2][nendo-STARTY][sei][nenrei]
         + soroudh_m[3][nendo-STARTY][sei][nenrei] + soroudh_m[4][nendo-STARTY][sei][nenrei] ;
      }
      for ( ii = 0 ; ii <= 4 ; ii++ ) {
        soroudh_m[ii][nendo-STARTY][2][nenrei]
          = soroudh_m[ii][nendo-STARTY][3][nenrei] + soroudh_m[ii][nendo-STARTY][4][nenrei] ;
        soroudh_m[ii][nendo-STARTY][0][nenrei]
          = soroudh_m[ii][nendo-STARTY][1][nenrei] + soroudh_m[ii][nendo-STARTY][2][nenrei] ;
      }
    }
  }
}
