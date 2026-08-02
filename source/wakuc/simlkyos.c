#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"


void simlkyos(void) 
{

  int   ii ;
  int   jj ;
  double TMP ;
  double TMQ ;
  double TMR ;
  double sojinko_wari[ENDY-STARTY+1] ;
  
  
  for ( seido = 4 ; seido <= 6 ; seido++ )
  {
    switch ( seido ) {
      case 4 :
        sprintf( filename, "/suuri/rev2024/wakuc/data/kyos/kok2022-%01d%01d%01d.csv", JIN , QX, NC ) ;
        break ;
      case 5 :
        sprintf( filename, "/suuri/rev2024/wakuc/data/kyos/ren2022-%01d%01d%01d.csv", JIN , QX, NC ) ;
        break ;
      case 6 :
        sprintf( filename, "/suuri/rev2024/wakuc/data/kyos/sig2022-%01d%01d%01d.csv", JIN , QX, NC ) ;
        break ;
    }
    if ( ( fp_setakyo = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "共済からのデータファイルを開けません!\n" ) ;
      exit(2) ;
    }
    karayomi( fp_setakyo ) ;
    for ( sei = 1 ; sei <= 2 ; sei++ ) {
      for ( nendo = SJINKOY ; nendo <= FJINKOY ; nendo++ ) {
        read_csv( buffer, fp_setakyo, &data_number ) ;
        if ( buffer[0] + 3 != seido ) {
          fprintf( stderr, "共済%d２号データのseido番号と整合性が取れません\n" , seido ) ;
          exit(2) ;
        }
        ii = buffer[1] ;
        jj = buffer[2] ;
        if ( jj > KIJUNMAP ) {
          for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
            kounen[seido][jj-STARTY][ii][nenrei] = buffer[ nenrei-11 ] ;
          }
        }
      }
    }
    fclose( fp_setakyo ) ;
    printf( "共済%dのreadkyos終了\n", seido ) ;
    
    if ( ENDY > FJINKOY ) {
      TMP = 0.0 ; TMQ = 0.0 ; TMR = 0.0 ;
      for ( nendo = FJINKOY - 1 ; nendo <= ENDY ; nendo++ ) {
        sojinko_wari[nendo-STARTY] = 0.0 ;
      }
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
          TMP += kounen[seido][FJINKOY-1-STARTY][sei][nenrei] ;
          TMQ += kounen[seido][FJINKOY-STARTY][sei][nenrei] ;
        }
      }
      
      if ( TMP * sojinko_c[FJINKOY-1-STARTY][0] * sojinko_c[FJINKOY-STARTY][0] > 0.0 ) {
        sojinko_wari[FJINKOY-1-STARTY] = TMP / sojinko_c[FJINKOY-1-STARTY][0] ;
        sojinko_wari[FJINKOY-STARTY] = TMQ / sojinko_c[FJINKOY-STARTY][0] ;
        TMR = sojinko_wari[FJINKOY-STARTY] / sojinko_wari[FJINKOY-1-STARTY] ;
      }
      
      for ( nendo = FJINKOY + 1 ; nendo <= ENDY ; nendo++ ) {
        sojinko_wari[nendo-STARTY] = sojinko_wari[nendo-1-STARTY] * TMR ;
      }

      for ( nendo = FJINKOY + 1 ; nendo <= ENDY ; nendo++ ) {
        for ( sei = 1 ; sei <= 2 ; sei++ ) {
          for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
            if ( sojinko_wari[FJINKOY-STARTY] * sojinko_c[FJINKOY-STARTY][0] > 0.0 ) {
              kounen[seido][nendo-STARTY][sei][nenrei]
                = kounen[seido][FJINKOY-STARTY][sei][nenrei]
                  * ( sojinko_wari[nendo-STARTY] * sojinko_c[nendo-STARTY][0] )
                  / ( sojinko_wari[FJINKOY-STARTY] * sojinko_c[FJINKOY-STARTY][0] ) ;
            }
            else {
              if ( ( sei == 1 ) && ( nenrei == 15 ) ) {
                printf( "共済 %d の %04d 年度の補正がゼロです\n", seido, nendo ) ;
                fprintf( stderr, "共済 %d の %04d 年度の補正がゼロです\n", seido, nendo ) ;
              }
              kounen[seido][nendo-STARTY][sei][nenrei] = 0.0 ;
            }
          }
        }
      }
    }
  }

  for ( seido = 4 ; seido <= 6 ; seido++ ) {
    for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
      for ( sei = 1 ; sei <= 2 ; sei++ ) {
        for ( nenrei = 70 ; nenrei <= 100 ; nenrei++ ) {
          kounen[seido][nendo-STARTY][sei][69] += kounen[seido][nendo-STARTY][sei][nenrei] ;
          kounen[seido][nendo-STARTY][sei][nenrei] = 0.0 ;
        }
      }
    }
  }
  
  for ( seido = 4 ; seido <= 6 ; seido++ ) {
    for ( nendo = STARTY ; nendo <= ENDY - 1 ; nendo++ ) {
      for ( nenrei = 15 ; nenrei <= 100 ; nenrei++ ) {
        if ( koyou_j_m[1][nendo-STARTY][2][nenrei] + koyou_j_m[2][nendo-STARTY][2][nenrei] > 0.0 ) {
          kounen[seido][nendo-STARTY][3][nenrei]
            = kounen[seido][nendo-STARTY][2][nenrei]
               * koyou_j_m[1][nendo-STARTY][3][nenrei]
               / koyou_j_m[1][nendo-STARTY][2][nenrei] ;
          kounen[seido][nendo-STARTY][4][nenrei]
            = kounen[seido][nendo-STARTY][2][nenrei]
               * koyou_j_m[1][nendo-STARTY][4][nenrei]
               / koyou_j_m[1][nendo-STARTY][2][nenrei] ;
        }
        kounen[seido][nendo-STARTY][0][nenrei]
          = kounen[seido][nendo-STARTY][1][nenrei] + kounen[seido][nendo-STARTY][2][nenrei] ;
      }
    }
  }
}
