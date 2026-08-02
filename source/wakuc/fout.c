#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"

void fout(void)
{

  char    filename[250] ;
  int     ii ;
  int     bunrui ;
  double  nenrei_kei_ninzu[69][ENDY-STARTY+1][5] ;
  double  nenrei_betu_ninzu[121] ;
  int     XEND ;


  for ( bunrui = 0 ; bunrui <= 57 ; bunrui++ ) {
    sprintf ( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-%02d.csv", BANGO, BANGO, bunrui ) ;
    if ( ( fp_wakuout = fopen(filename, "w" ) ) == NULL ) {
      fprintf( stderr, "出力wakuファイルを開けません!\n" ) ;
      exit (2) ;
    }
    fprintf( fp_wakuout , "試算番号, BANGO=, %d\n", BANGO ) ;
    fprintf( fp_wakuout , "分類,性,年度,計," ) ;
    for ( ii = 15 ; ii <= 99 ; ii++ ) {
      fprintf( fp_wakuout , "%02d," , ii ) ;
    }
    fprintf( fp_wakuout , "100\n" ) ;

    for ( sei = 0 ; sei <= 4 ; sei++ ) {
      for ( nendo = KS ; nendo <= KF ; nendo++ ) {
        nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] = 0.0 ;
        for ( nenrei = 15 ; nenrei <= 120 ; nenrei++ ) {
          nenrei_betu_ninzu[nenrei] = 0.0 ;
          switch ( bunrui ) {
            case 0:
              nenrei_betu_ninzu[nenrei]
               =  ichigou[0][nendo-STARTY][sei][nenrei] + nigou[nendo-STARTY][sei][nenrei]
                + sangou[0][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
              if ( MODE45 == 1 ) {
                XEND = xend[nendo-STARTY] ;
                if ( nenrei >= XEND ) {
                  nenrei_betu_ninzu[nenrei]
                   =  ichigou[2][nendo-STARTY][sei][nenrei] + nigou[nendo-STARTY][sei][nenrei]
                    + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
                }
              }
              break ;
            case 1:
              nenrei_betu_ninzu[nenrei]
               = kounen[0][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
              if ( nenrei >= 70 ) {
                nenrei_betu_ninzu[nenrei] -= kounen[1][nendo-STARTY][sei][nenrei] ;
              }
              break ;
            case 2:
              if ( ( nenrei >= 15 ) && ( nenrei < 65 ) ) {
                nenrei_betu_ninzu[nenrei]
                 = kounen[0][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 3:
              if( nenrei < 70 ) {
			    nenrei_betu_ninzu[nenrei]
                 = kounen[1][nendo-STARTY][sei][nenrei] + partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
			  break ;
            case 4:
              if ( nenrei >= 70 ) {
                nenrei_betu_ninzu[nenrei] = kounen[1][nendo-STARTY][sei][nenrei] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 5:
              nenrei_betu_ninzu[nenrei] = kounen[2][nendo-STARTY][sei][nenrei] ;
              break ;
            case 6:
              nenrei_betu_ninzu[nenrei] = kounen[3][nendo-STARTY][sei][nenrei] ;
              break ;
            case 7:
              nenrei_betu_ninzu[nenrei] = partnin[nendo-STARTY][sei][nenrei][0][0][0] ;
              break ;
            case 8:
              nenrei_betu_ninzu[nenrei] = kounen[4][nendo-STARTY][sei][nenrei] ;
              break ;
            case 9:
              nenrei_betu_ninzu[nenrei] = kounen[5][nendo-STARTY][sei][nenrei] ;
              break ;
            case 10:
              nenrei_betu_ninzu[nenrei] = kounen[6][nendo-STARTY][sei][nenrei] ;
              break ;
            case 11:
              nenrei_betu_ninzu[nenrei] = ichigou[0][nendo-STARTY][sei][nenrei] ;
              break ;
            case 12:
              nenrei_betu_ninzu[nenrei] = ichigou[1][nendo-STARTY][sei][nenrei] ;
              break ;
            case 13:
              nenrei_betu_ninzu[nenrei] = ichigou[2][nendo-STARTY][sei][nenrei] ;
              break ;
            case 14:
              nenrei_betu_ninzu[nenrei] = sangou[0][nendo-STARTY][sei][nenrei] ;
              break ;
            case 15:
              nenrei_betu_ninzu[nenrei] = sangou[1][nendo-STARTY][sei][nenrei] ;
              break ;
            case 16:
              nenrei_betu_ninzu[nenrei] = sangou[4][nendo-STARTY][sei][nenrei] ;
              break ;
            case 17:
              nenrei_betu_ninzu[nenrei] = sangou[5][nendo-STARTY][sei][nenrei] ;
              break ;
            case 18:
              nenrei_betu_ninzu[nenrei] = sangou[6][nendo-STARTY][sei][nenrei] ;
              break ;
            case 19:
              if ( nenrei < 70 ) {
                nenrei_betu_ninzu[nenrei] = mika_soto[nendo-STARTY][sei][nenrei] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 20:
              nenrei_betu_ninzu[nenrei] = jinko_c[nendo-STARTY][sei][nenrei] ;
              break ;
            case 21:
              nenrei_betu_ninzu[nenrei] = jinko_m[nendo-STARTY][sei][nenrei] ;
              break ;
            case 22:
              nenrei_betu_ninzu[nenrei] = partnin[nendo-STARTY][sei][nenrei][0][0][1] ;
              break ;
            case 23:
              nenrei_betu_ninzu[nenrei] = partnin[nendo-STARTY][sei][nenrei][1][0][1] ;
              break ;
            case 24:
              nenrei_betu_ninzu[nenrei] = partnin[nendo-STARTY][sei][nenrei][2][0][1] ;
              break ;
            case 25:
              nenrei_betu_ninzu[nenrei] = partnin[nendo-STARTY][sei][nenrei][7][0][1] ;
              break ;
            case 26:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
				 = partnin[nendo-STARTY][sei][nenrei][0][0][2] - partnin[nendo-STARTY][sei][nenrei][0][0][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 27:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][0][2] - partnin[nendo-STARTY][sei][nenrei][1][0][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 28:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][0][2] - partnin[nendo-STARTY][sei][nenrei][2][0][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 29:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][0][2] - partnin[nendo-STARTY][sei][nenrei][7][0][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 30:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][2][2] - partnin[nendo-STARTY][sei][nenrei][0][2][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 31:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][1][2] - partnin[nendo-STARTY][sei][nenrei][0][1][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 32:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][3][2] - partnin[nendo-STARTY][sei][nenrei][0][3][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 33:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][2][2] - partnin[nendo-STARTY][sei][nenrei][1][2][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 34:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][1][2] - partnin[nendo-STARTY][sei][nenrei][1][1][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 35:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][3][2] - partnin[nendo-STARTY][sei][nenrei][1][3][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 36:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][2][2] - partnin[nendo-STARTY][sei][nenrei][2][2][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 37:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][1][2] - partnin[nendo-STARTY][sei][nenrei][2][1][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 38:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][3][2] - partnin[nendo-STARTY][sei][nenrei][2][3][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 39:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][2][2] - partnin[nendo-STARTY][sei][nenrei][7][2][1] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 40:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][1][2] - partnin[nendo-STARTY][sei][nenrei][7][1][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 41:
              if ( PART >= 1 && nendo >= PARTYR1 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][3][2] - partnin[nendo-STARTY][sei][nenrei][7][3][1] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 42:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][0][3] - partnin[nendo-STARTY][sei][nenrei][0][0][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 43:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][0][3] - partnin[nendo-STARTY][sei][nenrei][1][0][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 44:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][0][3] - partnin[nendo-STARTY][sei][nenrei][2][0][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 45:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][0][3] - partnin[nendo-STARTY][sei][nenrei][7][0][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 46:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][2][3] - partnin[nendo-STARTY][sei][nenrei][0][2][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 47:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][1][3] - partnin[nendo-STARTY][sei][nenrei][0][1][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 48:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][0][3][3] - partnin[nendo-STARTY][sei][nenrei][0][3][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 49:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][2][3] - partnin[nendo-STARTY][sei][nenrei][1][2][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 50:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][1][3] - partnin[nendo-STARTY][sei][nenrei][1][1][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 51:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][1][3][3] - partnin[nendo-STARTY][sei][nenrei][1][3][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 52:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][2][3] - partnin[nendo-STARTY][sei][nenrei][2][2][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 53:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][1][3] - partnin[nendo-STARTY][sei][nenrei][2][1][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 54:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][2][3][3] - partnin[nendo-STARTY][sei][nenrei][2][3][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 55:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][2][3] - partnin[nendo-STARTY][sei][nenrei][7][2][2] ;
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 56:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][1][3] - partnin[nendo-STARTY][sei][nenrei][7][1][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
            case 57:
              if ( PART == 2 && nendo >= PARTYR2 ) { 
                nenrei_betu_ninzu[nenrei]
                 = partnin[nendo-STARTY][sei][nenrei][7][3][3] - partnin[nendo-STARTY][sei][nenrei][7][3][2] ; 
              }
              else {
                nenrei_betu_ninzu[nenrei] = 0.0 ;
              }
              break ;
          }
          nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] += nenrei_betu_ninzu[nenrei] ;
          if ( nenrei > 100 ) {
            nenrei_betu_ninzu[100] += nenrei_betu_ninzu[nenrei] ;
          }
        }
        fprintf( fp_wakuout , "%4d,%1d,%4d,", bunrui , sei , nendo ) ;
        fprintf( fp_wakuout , "%lf,", raund( nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] , 0 ) ) ;
        for ( nenrei = 15 ; nenrei <= 99 ; nenrei++ ) {
          fprintf( fp_wakuout , "%lf,", raund( nenrei_betu_ninzu[nenrei] , 0 ) ) ;
        }
        fprintf( fp_wakuout , "%lf\n", raund( nenrei_betu_ninzu[100] , 0 ) ) ;
      }
    }
    fclose( fp_wakuout ) ;
  }


  sprintf( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-nenreikei.csv", BANGO , BANGO ) ;
  if ( ( fp_wakuout = fopen(filename, "w" ) ) == NULL ) {
    fprintf( stderr, "出力wakuファイルを開けません!\n" ) ;
    exit (2) ;
  }
  fprintf( fp_wakuout , "年度末,試算番号,BANGO=,%d\n", BANGO ) ;
  for ( sei = 0 ; sei <= 4 ; sei++ ) {
	switch ( sei ) {
	  case 0:  fprintf( fp_wakuout , "男女計," ) ;  break ;
	  case 1:  fprintf( fp_wakuout , "男," ) ;  break ;
	  case 2:  fprintf( fp_wakuout , "女," ) ;  break ;
	  case 3:  fprintf( fp_wakuout , "女有配偶," ) ;  break ;
	  case 4:  fprintf( fp_wakuout , "女無配偶," ) ;  break ;
    }
    fprintf( fp_wakuout , "公的計,被用者計,国年２号,旧厚(70未満),旧厚(70以上),旧厚12種(パート含まず),旧厚3種,旧厚短時間(今後の適用拡大対象者を含む),国共2号,地共2号,私学2号,") ;
    fprintf( fp_wakuout , "1号計,1号(一般),1号(任意),3号計,旧厚3号,国共3号,地共3号,私学3号,人口差分,人口央,人口末,") ;
    fprintf( fp_wakuout , "適用拡大202410計,適用拡大202410元１号,適用拡大202410元３号,適用拡大202410元その他,") ;
    fprintf( fp_wakuout , "適用拡大１段階目計,適用拡大１段階目元１号,適用拡大１段階目元３号,適用拡大１段階目元その他,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元週30時間以上,適用拡大１段階目元週20〜30時間,適用拡大１段階目元週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元１号週30時間以上,適用拡大１段階目元１号週20〜30時間,適用拡大１段階目元１号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元３号週30時間以上,適用拡大１段階目元３号週20〜30時間,適用拡大１段階目元３号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元その他週30時間以上,適用拡大１段階目元その他週20〜30時間,適用拡大１段階目元その他週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目計,適用拡大２段階目元１号,適用拡大２段階目元３号,適用拡大２段階目元その他,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元週30時間以上,適用拡大２段階目元週20〜30時間,適用拡大２段階目元週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元１号週30時間以上,適用拡大２段階目元１号週20〜30時間,適用拡大２段階目元１号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元３号週30時間以上,適用拡大２段階目元３号週20〜30時間,適用拡大２段階目元３号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元その他週30時間以上,適用拡大２段階目元その他週20〜30時間,適用拡大２段階目元その他週20時間未満\n") ;
    for ( nendo = KS ; nendo <= KF ; nendo++ ) {
      fprintf( fp_wakuout , "%4d,", nendo ) ;
      for ( bunrui = 0 ; bunrui <= 56 ; bunrui++ ) {
        fprintf( fp_wakuout , "%lf,", raund( nenrei_kei_ninzu[bunrui][nendo-STARTY][sei], 0 ) ) ;
      }
      fprintf( fp_wakuout , "%lf,\n", raund( nenrei_kei_ninzu[57][nendo-STARTY][sei], 0 ) ) ;
    }
  }
  fclose( fp_wakuout ) ;

  sprintf( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-nenkeikan.csv", BANGO, BANGO ) ;
  if ( ( fp_wakuout = fopen( filename, "w" ) ) == NULL ) {
    fprintf( stderr, "出力wakuファイルを開けません!\n" ) ;
    exit (2) ;
  }
  fprintf( fp_wakuout , "年度間, 試算番号, BANGO=, %d\n", BANGO ) ;
  for ( sei = 0 ; sei <= 4 ; sei++ ) {
	switch ( sei ) {
	  case 0:  fprintf( fp_wakuout , "男女計, " ) ;  break ;
	  case 1:  fprintf( fp_wakuout , "男, " ) ;  break ;
	  case 2:  fprintf( fp_wakuout , "女, " ) ;  break ;
	  case 3:  fprintf( fp_wakuout , "女有配偶, " ) ;  break ;
	  case 4:  fprintf( fp_wakuout , "女無配偶, " ) ;  break ;
    }
    fprintf( fp_wakuout , "公的計,被用者計,国年２号,旧厚(70未満),旧厚(70以上),旧厚12種(パート含まず),旧厚3種,旧厚短時間(今後の適用拡大対象者を含む),国共2号,地共2号,私学2号,") ;
    fprintf( fp_wakuout , "1号計,1号(一般),1号(任意),3号計,旧厚3号,国共3号,地共3号,私学3号,人口差分,人口央,人口末,") ;
    fprintf( fp_wakuout , "適用拡大202410計,適用拡大202410元１号,適用拡大202410元３号,適用拡大202410元その他,") ;
    fprintf( fp_wakuout , "適用拡大１段階目計,適用拡大１段階目元１号,適用拡大１段階目元３号,適用拡大１段階目元その他,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元週30時間以上,適用拡大１段階目元週20〜30時間,適用拡大１段階目元週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元１号週30時間以上,適用拡大１段階目元１号週20〜30時間,適用拡大１段階目元１号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元３号週30時間以上,適用拡大１段階目元３号週20〜30時間,適用拡大１段階目元３号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大１段階目元その他週30時間以上,適用拡大１段階目元その他週20〜30時間,適用拡大１段階目元その他週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目計,適用拡大２段階目元１号,適用拡大２段階目元３号,適用拡大２段階目元その他,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元週30時間以上,適用拡大２段階目元週20〜30時間,適用拡大２段階目元週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元１号週30時間以上,適用拡大２段階目元１号週20〜30時間,適用拡大２段階目元１号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元３号週30時間以上,適用拡大２段階目元３号週20〜30時間,適用拡大２段階目元３号週20時間未満,") ;
    fprintf( fp_wakuout , "適用拡大２段階目元その他週30時間以上,適用拡大２段階目元その他週20〜30時間,適用拡大２段階目元その他週20時間未満\n") ;
    for ( nendo = KS ; nendo <= KF ; nendo++ ) {
      fprintf( fp_wakuout , "%4d,", nendo ) ;
      for ( bunrui = 0 ; bunrui <= 56 ; bunrui++ ) {
        fprintf( fp_wakuout , "%lf,", raund( ( nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] + nenrei_kei_ninzu[bunrui][nendo-1-STARTY][sei] ) / 2.0 , 0 ) ) ;
      }
      fprintf( fp_wakuout , "%lf,\n", raund( ( nenrei_kei_ninzu[57][nendo-STARTY][sei] + nenrei_kei_ninzu[57][nendo-1-STARTY][sei] ) / 2.0 , 0 ) ) ;
    }
  }
  fclose( fp_wakuout ) ;
  
  
  sprintf( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-settei.csv", BANGO, BANGO ) ;
  if ( ( fp_wakuout = fopen( filename, "w" ) ) == NULL ) {
    fprintf( stderr, "出力wakuファイルを開けません!\n" ) ;
    exit (2) ;
  }
  fprintf( fp_wakuout , "試算番号,BANGO=,%d\n", BANGO ) ;
  fprintf( fp_wakuout , "開始年度,STARTY=,%d\n", STARTY ) ;
  fprintf( fp_wakuout , "終了年度,ENDY=,%d\n", ENDY ) ;
  fprintf( fp_wakuout , "計算モード,MODE=,%d\n", MODE ) ;
  fprintf( fp_wakuout , "基準年度,KIJUN=,%d\n", KIJUN ) ;
  fprintf( fp_wakuout , "出力開始年度,KS=,%d\n", KS ) ;
  fprintf( fp_wakuout , "出力終了年度,KF=,%d\n", KF ) ;
  fprintf( fp_wakuout , "出生率の設定,JIN=,%d\n", JIN ) ;
  fprintf( fp_wakuout , "死亡率の設定,QX=,%d\n", QX ) ;
  fprintf( fp_wakuout , "入国超過の設定,NC=,%d\n", NC ) ;
  fprintf( fp_wakuout , "人口推計開始年度,SJINKOY=,%d\n", SJINKOY ) ;
  fprintf( fp_wakuout , "有配偶率年度,YUHAIGY=,%d\n", YUHAIGY ) ;
  fprintf( fp_wakuout , "労働力率,ROUDR=,%d\n", ROUDR ) ;
  fprintf( fp_wakuout , "労働力率年度,ROUDYR=,%d\n", ROUDYR ) ;
  fprintf( fp_wakuout , "パート適用導入の有無,PART=,%d\n",PART ) ;
  fprintf( fp_wakuout , "パート適用導入年度1,PARTYR1=,%d\n",PARTYR1 ) ;
  fprintf( fp_wakuout , "パート適用導入年度2,PARTYR2=,%d\n",PARTYR2 ) ;
  fprintf( fp_wakuout , "パート基礎数値の年度,PARTKYR=,%d\n",PARTKYR ) ;
  fprintf( fp_wakuout , "45年化,MODE45=,%d\n",MODE45 ) ;
  fclose( fp_wakuout ) ;
}
