#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"



void roudfout(void)
{

  char    filename[250]    ; 
  int     ii ;
  int     bunrui ;
  double  nenrei_kei_ninzu[46][ENDY-STARTY+1][5]  ;
  double  nenrei_betu_ninzu[121] ;


  for ( bunrui=0; bunrui<=39; bunrui++ ) {
    sprintf(filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/wakuroud%04d-%02d.csv", BANGO, BANGO, bunrui ) ;
    if ((fp_wakuout = fopen(filename, "w")) == NULL) {
      fprintf(stderr, "出力wakuファイルを開けません!\n");
      exit (2);
    }
    fprintf(fp_wakuout , "試算番号,BANGO=,%d\n", BANGO );
    fprintf(fp_wakuout , "分類,性,年度,計," );
    for ( ii=15; ii<=99; ii++ ) {
      fprintf(fp_wakuout , "%02d," , ii );
    }
    fprintf(fp_wakuout , "100\n" );
    
    for ( sei=0; sei<=4; sei++ ) {
      for ( nendo=KS ; nendo<=KF ; nendo++ ) {
        nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] = 0.0 ;
        for ( nenrei=15; nenrei<=120; nenrei++ ) {
          nenrei_betu_ninzu[nenrei] = 0.0 ;
          switch ( bunrui ) {
            case 0:
              nenrei_betu_ninzu[nenrei] = jinko_c[nendo-STARTY][sei][nenrei] ;
              break ;
            case 1:
              nenrei_betu_ninzu[nenrei] = jinko_m[nendo-STARTY][sei][nenrei] ;
              break ;
            case 2:
              nenrei_betu_ninzu[nenrei] = roud_j_c[nendo-STARTY][sei][nenrei] ;
              break ;
            case 3:
              nenrei_betu_ninzu[nenrei] = roud_j_m[nendo-STARTY][sei][nenrei] ;
              break ;
            case 4:
              nenrei_betu_ninzu[nenrei] = syugyo_j_c[nendo-STARTY][sei][nenrei]  ;
              break ;
            case 5:
              nenrei_betu_ninzu[nenrei] = syugyo_j_m[nendo-STARTY][sei][nenrei] ;
              break ;
            case 6:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[0][nendo-STARTY][sei][nenrei] ;
              break ;
            case 7:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[0][nendo-STARTY][sei][nenrei] ;
              break ;
            case 8:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[1][nendo-STARTY][sei][nenrei] ;
              break ;
            case 9:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[1][nendo-STARTY][sei][nenrei] ;
              break ;
            case 10:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[2][nendo-STARTY][sei][nenrei] ;
              break ;
            case 11:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[2][nendo-STARTY][sei][nenrei] ;
              break ;
            case 12:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[6][nendo-STARTY][sei][nenrei] ;
              break ;
            case 13:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[6][nendo-STARTY][sei][nenrei] ;
              break ;
            case 14:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[4][nendo-STARTY][sei][nenrei]+koyou_j_c[5][nendo-STARTY][sei][nenrei] ;
              break ;
            case 15:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[4][nendo-STARTY][sei][nenrei]+koyou_j_m[5][nendo-STARTY][sei][nenrei] ;
              break ;
            case 16:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[3][nendo-STARTY][sei][nenrei] ;
              break ;
            case 17:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[3][nendo-STARTY][sei][nenrei] ;
              break ;
            case 18:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[7][nendo-STARTY][sei][nenrei] ;
              break ;
            case 19:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[7][nendo-STARTY][sei][nenrei] ;
              break ;
            case 20:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[8][nendo-STARTY][sei][nenrei] ;
              break ;
            case 21:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[8][nendo-STARTY][sei][nenrei] ;
              break ;
            case 22:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[9][nendo-STARTY][sei][nenrei] ;
              break ;
            case 23:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[9][nendo-STARTY][sei][nenrei] ;
              break ;
            case 24:
              nenrei_betu_ninzu[nenrei] = koyou_j_c[10][nendo-STARTY][sei][nenrei] ;
              break ;
            case 25:
              nenrei_betu_ninzu[nenrei] = koyou_j_m[10][nendo-STARTY][sei][nenrei] ;
              break ;
            case 26:
              nenrei_betu_ninzu[nenrei] = jieigyo_j_c[nendo-STARTY][sei][nenrei] ;
              break ;
            case 27:
              nenrei_betu_ninzu[nenrei] = jieigyo_j_m[nendo-STARTY][sei][nenrei] ;
              break ;
            case 28:
              nenrei_betu_ninzu[nenrei] = soroudh_c[0][nendo-STARTY][sei][nenrei] * 12 / 10000 ;
              break ;
            case 29:
              nenrei_betu_ninzu[nenrei] = soroudh_m[0][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 30:
              nenrei_betu_ninzu[nenrei] = soroudh_c[1][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 31:
              nenrei_betu_ninzu[nenrei] = soroudh_m[1][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 32:
              nenrei_betu_ninzu[nenrei] = soroudh_c[2][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 33:
              nenrei_betu_ninzu[nenrei] = soroudh_m[2][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 34:
              nenrei_betu_ninzu[nenrei] = soroudh_c[3][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 35:
              nenrei_betu_ninzu[nenrei] = soroudh_m[3][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 36:
              nenrei_betu_ninzu[nenrei] = soroudh_c[4][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 37:
              nenrei_betu_ninzu[nenrei] = soroudh_m[4][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 38:
              nenrei_betu_ninzu[nenrei] = soroudh_c[9][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
            case 39:
              nenrei_betu_ninzu[nenrei] = soroudh_m[9][nendo-STARTY][sei][nenrei] * 12 / 10000  ;
              break ;
          }
          nenrei_kei_ninzu[bunrui][nendo-STARTY][sei] += nenrei_betu_ninzu[nenrei] ;
          if ( nenrei>100 ) {
            nenrei_betu_ninzu[100] += nenrei_betu_ninzu[nenrei] ;
          }
        }
        fprintf(fp_wakuout , "roud-%2d,%1d,%4d,", bunrui , sei , nendo );
        fprintf(fp_wakuout , "%lf,", raund(nenrei_kei_ninzu[bunrui][nendo-STARTY][sei],0) );
        for ( nenrei=15; nenrei<=99; nenrei++ ){
          fprintf(fp_wakuout , "%lf,", raund(nenrei_betu_ninzu[nenrei],0) );
        }
        fprintf(fp_wakuout , "%lf\n", raund(nenrei_betu_ninzu[100],0) );
      }
    }
    fclose( fp_wakuout ) ;
  }
  
  
  sprintf(filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-roudkei.csv", BANGO, BANGO ) ;
  if ((fp_wakuout = fopen(filename, "w")) == NULL) {
    fprintf(stderr, "出力wakuファイルを開けません!\n");
    exit (2);
  }
  fprintf(fp_wakuout , "15歳以上全年齢,試算番号,BANGO=,%d,", BANGO );
  fprintf(fp_wakuout , "出生率,JIN=,%d,", JIN );
  fprintf(fp_wakuout , "死亡率,QX=,%d,", QX );
  fprintf(fp_wakuout , "労働力率,ROUDR=,%d\n", ROUDR );
  for ( sei = 0 ; sei <= 4 ; sei++ ) {
    switch ( sei ) {
	  case 0:  fprintf( fp_wakuout , "男女計, " ) ;  break ;
	  case 1:  fprintf( fp_wakuout , "男, " ) ;  break ;
	  case 2:  fprintf( fp_wakuout , "女, " ) ;  break ;
	  case 3:  fprintf( fp_wakuout , "女有配偶, " ) ;  break ;
	  case 4:  fprintf( fp_wakuout , "女無配偶, " ) ;  break ;
    }
    fprintf(fp_wakuout , ",人口央,人口末,労働力人口央,労働力人口末,就業者央,就業者末,") ;
    fprintf(fp_wakuout , "総雇用者数央,総雇用者数末,正規雇用者数央,正規雇用者数末,非正規（フル）雇用者数央,非正規（フル）雇用者数末,") ;
    fprintf(fp_wakuout , "非正規（30〜34時間）雇用者数央,非正規（30〜34時間）雇用者数末,非正規（20〜29時間）雇用者数央,非正規（20〜29時間）雇用者数末,") ;
    fprintf(fp_wakuout , "非正規（20時間未満）雇用者数央,非正規（20時間未満）雇用者数末,") ;
    fprintf(fp_wakuout , "被用者数央,被用者数末,正規被用者数央,正規被用者数末,非正規（フル）被用者数央,非正規（フル）被用者数末,") ;
    fprintf(fp_wakuout , "非正規（フル以外）被用者数央,非正規（フル以外）被用者数末,自営業者数央,自営業者数末,") ;
    fprintf(fp_wakuout , "総労働時間央,総労働時間末,正規労働時間央,正規労働時間末,非正規（フル）労働時間央,非正規（フル）労働時間末,") ;
    fprintf(fp_wakuout , "非正規（フル以外）労働時間央,非正規（フル以外）労働時間末,自営労働時間央,自営労働時間末,被用者労働時間央,被用者労働時間末,被用者平均労働時間央\n") ;
    for ( nendo = KS ; nendo <= KF ; nendo++ ) {
      fprintf( fp_wakuout , "%4d, 0,", nendo ) ;
      for ( bunrui = 0 ; bunrui <= 39 ; bunrui++ ) {
        fprintf( fp_wakuout , "%lf,", raund( nenrei_kei_ninzu[bunrui][nendo-STARTY][sei], 0 ) ) ;
      }
      fprintf( fp_wakuout , "%lf \n", raund( heikinh_c[10][nendo-STARTY] * 1000000, 0 ) ) ;
    }
  }
  fclose( fp_wakuout ) ;
}
