#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "set.h"
#include "cntl.h"
#include "file_open.h"

void readdata(void)
{
  
  int ii ;
  int jj ;
  int kk ;
  char filename[250] ;
  char pathname[250] ;
  previous_buffer0 = -1000 ;


  sprintf( pathname, "/suuri/rev2024/wakuc/rslt/ver_4_1/" ) ;
  mkdir( pathname, 0755 ) ;
  sprintf( pathname, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d", BANGO ) ;
  mkdir( pathname, 0755 ) ;
  sprintf( filename, "/suuri/rev2024/wakuc/rslt/ver_4_1/rslt%04d/waku%04d-err.csv" , BANGO, BANGO ) ;
  if ( ( fp_err = fopen( filename, "w" ) ) == NULL ) {
    fprintf( stderr, "出力用ファイルを開けません\n" ) ;
    exit(2) ;
  }

  for ( sei = 1 ; sei <= 2 ; sei++ ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/sinj/pop%01d-%01d%01d%01d.csv", sei, JIN, QX, NC ) ;
    if ( ( fp_jinko = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "性別%01d, 出生%01d, 死亡%01d, 入国%01dの人口ファイルを開けません!\n", sei, JIN, QX, NC ) ;
      exit(2) ;
    }
    karayomi( fp_jinko ) ;
    previous_buffer0 = -1000 ;
    while ( ( read_csv( buffer, fp_jinko, &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) ) {
      ii = (int)(buffer[0]) ;
	  jj = (int)(buffer[1]) ;
      if ( ( ii < STARTY ) || ( ii > ENDY ) ) {
        fprintf( stderr, "性別%01d, 出生%01d, 死亡%01d, 入国%01dの人口ファイルに不適切な年度が入っています!\n", sei, JIN, QX, NC ) ;
        exit(2) ;
      }
	  if ( jj != sei ) {
        fprintf( stderr, "性別%01d, 出生%01d, 死亡%01d, 入国%01dの人口ファイルに不適切な性別が入っています!\n", sei, JIN, QX, NC ) ;
        exit(2) ;
      }
      sojinko_c[ii-STARTY][jj] = buffer[2] ;
      for ( nenrei = 0 ; nenrei <= 120 ; nenrei++ ) {
        jinko_c[ii-STARTY][jj][nenrei] = buffer[nenrei+3] ;
      }
      previous_buffer0 = buffer[0] ;
    }
    fclose( fp_jinko ) ;
  }
  
  sprintf( filename, "/suuri/rev2024/wakuc/data/sinj/wari-2020.csv" ) ;
  if ( ( fp_jinkow = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "人口割合ファイルを開けません!\n" ) ;
    exit(2) ;
  }
  karayomi( fp_jinkow ) ;
  previous_buffer0 = -1000 ;
  while ( ( read_csv( buffer, fp_jinkow, &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) ) {
    nenrei = (int)(buffer[0]) ;
    if ( ( nenrei < 0 ) || ( nenrei > 120 ) ) {
      fprintf( stderr, "人口割合ファイルに不適切な年齢が入っています!\n" ) ;
      exit(2) ;
    }
    jinko_wari[1][nenrei] = buffer[1] ;
    jinko_wari[2][nenrei] = buffer[2] ;
    jinko_wari[3][nenrei] = buffer[2] ;
    jinko_wari[4][nenrei] = buffer[2] ;
  }
  fclose( fp_jinkow ) ;
  
  sprintf( filename, "/suuri/rev2024/wakuc/data/sinj/yuhaigr_suikei-2020.csv" ) ;
  if ( ( fp_jinkoy = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "女性有配偶割合 (推計) ファイルを開けません!\n" ) ;
    exit(2) ;
  }
  karayomi( fp_jinkoy ) ;
  previous_buffer0 = -1000 ;
  while ( ( read_csv( buffer, fp_jinkoy, &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) ) {
    ii = (int)(buffer[0]) ;
    jj = (int)(buffer[1]) ;
    if ( ( ii < STARTY ) || ( ii > ENDY ) ) {
      fprintf( stderr, "女性有配偶 (推計) ファイルに不適切な年度が入っています!\n" ) ;
      exit(2) ;
    }
    if ( jj != 2 ) {
      fprintf( stderr, "女性有配偶 (推計) ファイルに不適切な性別が入っています!\n" ) ;
      exit(2) ;
    }
    for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
      yuhaig_r[ii-STARTY][nenrei] = buffer[nenrei-12] ;
    }
    previous_buffer0 = buffer[0] ;
  }
  fclose( fp_jinkoy ) ;

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/roudou2024-%01d.csv", ROUDR ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "労働力率ファイル (ケース毎) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ROUDYR ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ROUDYR ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        roud_r[nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
          TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/syugyor2024-%01d.csv", ROUDR ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "就業率ファイル (ケース毎) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ROUDYR ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ROUDYR ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        syugyo_r[nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/koyour2022.csv" ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "雇用者割合ファイル (実績) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ENDY ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        koyou_r[nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/seikir2022.csv" ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "正規雇用者割合ファイル (実績) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ROUDYR ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ROUDYR ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        seiki_hiseiki_r[1][nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/hiseikifurur2022.csv" ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "非正規フル雇用者割合ファイル (実績) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ROUDYR ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ROUDYR ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        seiki_hiseiki_r[2][nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }
  for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = 0.0 ;
      }
    }
  }
  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/hiseikitanr2022.csv" ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "非正規短時間雇用者割合ファイル (実績) を開けません!\n" ) ;
    exit(2) ;
  }
  read_roud( fp_roudritu, STARTY, ROUDYR ) ;
  fclose( fp_roudritu ) ;
  for ( nendo = STARTY ; nendo <= ROUDYR ; nendo++ ) {
    for ( sei = 1 ; sei <= 4 ; sei++ ) {
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        seiki_hiseiki_r[3][nendo-STARTY][sei][nenrei] = TEMP[nendo-STARTY][sei][nenrei] ;
      }
    }
  }

  sprintf( filename, "/suuri/rev2024/wakuc/data/roud2024/syosettei2022-%01d.csv", ROUDR ) ;
  if ( ( fp_roudritu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "諸設定値ファイル (ケース毎) を開けません!\n" ) ;
    exit(2) ;
  }
  karayomi( fp_roudritu );
  karayomi( fp_roudritu );
  for ( jj = STARTY ; jj <= ROUDYR ; jj++ ) {
    read_csv( buffer, fp_roudritu, &data_number ) ;
    nendo = buffer[0] ;
    kk = buffer[1] ;
	if( kk != ROUDR ) {
	  fprintf( stderr, "諸設定値ファイルの内容が労働力率の設定と一致しません!\n" ) ;
      exit(2) ;
    }
    hiseiki_tan_r_all[nendo-STARTY] = buffer[2] ;
    heikinh_c[1][nendo-STARTY] = buffer[3] ;
    heikinh_c[2][nendo-STARTY] = buffer[4] ;
    heikinh_c[3][nendo-STARTY] = buffer[5] ;
    heikinh_c[4][nendo-STARTY] = buffer[6] ;
    heikinh_c[5][nendo-STARTY] = buffer[7] ;
    heikinh_c[6][nendo-STARTY] = buffer[8] ;
    heikinh_c[7][nendo-STARTY] = buffer[9] ;
    heikinh_c[8][nendo-STARTY] = buffer[10] ;
    heikinh_c[9][nendo-STARTY] = buffer[11] ;
    hiseiki_jikan_r[1][nendo-STARTY] = buffer[12] + buffer[13] ;
    hiseiki_jikan_r[2][nendo-STARTY] = buffer[14] ;
    hiseiki_jikan_r[3][nendo-STARTY] = buffer[15] ;
    hiseiki_jikan_r[4][nendo-STARTY] = buffer[16] ;
    kounenteki_c[1][nendo-STARTY] = buffer[17] ;
    kounenteki_c[2][nendo-STARTY] = buffer[18] ;
    kounenteki_c[3][nendo-STARTY] = buffer[19] ;
    kounenteki_c[4][nendo-STARTY] = buffer[20] ;
    kounenteki_c[5][nendo-STARTY] = buffer[21] ;
    kounenteki_c[6][nendo-STARTY] = buffer[22] ;
  }
  fclose( fp_roudritu ) ;

  for ( jj = STARTY ; jj <= KIJUNMAP - 1 ; jj++ ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/map/%02dmap.csv" , jj ) ;
    if ( ( fp_map = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "%02d年度被保険者数を開けません!\n", jj ) ;
      exit(2) ;
    }
    read_map( fp_map, jj ) ;
    fclose( fp_map ) ;
  }
  if ( MODE45 == 1 ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/map/%02dmap-45.csv", KIJUNMAP ) ;
  }
  else {
    sprintf( filename, "/suuri/rev2024/wakuc/data/map/%02dmap.csv", KIJUNMAP ) ;
  }
  if ( ( fp_map = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "%02d年度被保険者数を開けません!\n", KIJUNMAP ) ;
    exit(2) ;
  }
  read_map( fp_map, KIJUNMAP ) ;
  fclose( fp_map ) ;

  sprintf( filename, "/suuri/rev2024/wakuc/data/prev/ichiyuhaigr2022.csv" ) ;
  if ( ( fp_ichiyu = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "１号有配偶率ファイルを開けません!\n" ) ;
    exit(2) ;
  }
  karayomi( fp_ichiyu ) ;
  for ( ii = 20 ; ii <= 69 ; ii++ ) {
    read_csv( buffer, fp_ichiyu, &data_number ) ;
    nenrei = buffer[0] ;
    ichiyuhaigr[nenrei] = buffer[1] ;
  }
  fclose( fp_ichiyu ) ;

  if( MODE45 == 1 ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/prev/ichisanxend2022.csv" ) ;
    if ( ( fp_jogen = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "１・３号上限年齢ファイルを開けません!\n" ) ;
      exit(2) ;
    }
    karayomi( fp_jogen ) ;
    for ( ii = STARTY ; ii <= 2050 ; ii++ ) {
      read_csv( buffer, fp_jogen, &data_number ) ;
      nendo = buffer[0] ;
      xend[nendo-STARTY] = buffer[1] ;
    }
    fclose( fp_jogen ) ;
    for ( nendo = 2051 ; nendo <= ENDY ; nendo++ ) {
      xend[nendo-STARTY] = xend[nendo-1-STARTY] ;
    }
  }
  else {
    for ( nendo = STARTY ; nendo <= ENDY ; nendo++ ) {
      xend[nendo-STARTY] = 60 ; 
    }
  }

  sprintf( filename, "/suuri/rev2024/wakuc/data/map/cut_jisseki.csv" ) ;
  if ( ( fp_cut = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "調整率実績ファイルを開けません!\n" ) ;
    exit(2) ;
  }
  for ( ii = CNENDO ; ii <= CUT_JY ; ii++ ) {
    read_csv( buffer, fp_cut, &data_number );
    nendo = buffer[0] ;
    cutritu[nendo-CNENDO] = buffer[1] ;
  }
  fclose( fp_cut ) ;

  sprintf( filename, "/suuri/rev2024/wakuc/data/part/partnin2020-2024.csv" ) ;
  if ( ( fp_part = fopen( filename, "r" ) ) == NULL ) {
    fprintf( stderr, "パート入力ファイル (１段階) を開けません!\n" ) ;
    exit(2) ;
  }
  karayomi( fp_part ) ;  
  for ( kubun = 1 ; kubun <= 11 ; kubun++ ) {
    read_csv( buffer, fp_part, &data_number ) ;
    ii = (int) buffer[0] ;
    kbetu_partkiso[1][ii][1][1][1] = (double) buffer[1] ;
    kbetu_partkiso[1][ii][2][1][1] = (double) buffer[2] ;
    kbetu_partkiso[1][ii][7][1][1] = (double) buffer[3] ;
    kbetu_partkiso[2][ii][1][1][1] = (double) buffer[4] ;
    kbetu_partkiso[2][ii][2][1][1] = (double) buffer[5] ;
    kbetu_partkiso[2][ii][7][1][1] = (double) buffer[6] ;
    kbetu_partkiso[1][ii][1][2][1] = (double) buffer[7] ;
    kbetu_partkiso[1][ii][2][2][1] = (double) buffer[8] ;
    kbetu_partkiso[1][ii][7][2][1] = (double) buffer[9] ;
    kbetu_partkiso[2][ii][1][2][1] = (double) buffer[10] ;
    kbetu_partkiso[2][ii][2][2][1] = (double) buffer[11] ;
    kbetu_partkiso[2][ii][7][2][1] = (double) buffer[12] ;
    kbetu_partkiso[1][ii][1][3][1] = (double) buffer[13] ;
    kbetu_partkiso[1][ii][2][3][1] = (double) buffer[14] ;
    kbetu_partkiso[1][ii][7][3][1] = (double) buffer[15] ;
    kbetu_partkiso[2][ii][1][3][1] = (double) buffer[16] ;
    kbetu_partkiso[2][ii][2][3][1] = (double) buffer[17] ;
    kbetu_partkiso[2][ii][7][3][1] = (double) buffer[18] ;
  }
  fclose( fp_part ) ;

  if ( PART >= 1 ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/part/partnin2020-2027-%01d.csv", MODE ) ;
    if ( ( fp_part = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "パート入力ファイル (１段階) を開けません!\n" ) ;
      exit(2) ;
    }
    karayomi( fp_part ) ;  
    for ( kubun = 1 ; kubun <= 11 ; kubun++ ) {
      read_csv( buffer, fp_part, &data_number ) ;
      ii = (int) buffer[0] ;
      kbetu_partkiso[1][ii][1][1][2] = (double) buffer[1] ;
      kbetu_partkiso[1][ii][2][1][2] = (double) buffer[2] ;
      kbetu_partkiso[1][ii][7][1][2] = (double) buffer[3] ;
      kbetu_partkiso[2][ii][1][1][2] = (double) buffer[4] ;
      kbetu_partkiso[2][ii][2][1][2] = (double) buffer[5] ;
      kbetu_partkiso[2][ii][7][1][2] = (double) buffer[6] ;
      kbetu_partkiso[1][ii][1][2][2] = (double) buffer[7] ;
      kbetu_partkiso[1][ii][2][2][2] = (double) buffer[8] ;
      kbetu_partkiso[1][ii][7][2][2] = (double) buffer[9] ;
      kbetu_partkiso[2][ii][1][2][2] = (double) buffer[10] ;
      kbetu_partkiso[2][ii][2][2][2] = (double) buffer[11] ;
      kbetu_partkiso[2][ii][7][2][2] = (double) buffer[12] ;
      kbetu_partkiso[1][ii][1][3][2] = (double) buffer[13] ;
      kbetu_partkiso[1][ii][2][3][2] = (double) buffer[14] ;
      kbetu_partkiso[1][ii][7][3][2] = (double) buffer[15] ;
      kbetu_partkiso[2][ii][1][3][2] = (double) buffer[16] ;
      kbetu_partkiso[2][ii][2][3][2] = (double) buffer[17] ;
      kbetu_partkiso[2][ii][7][3][2] = (double) buffer[18] ;
    }
    fclose( fp_part ) ;
  }

  if ( PART == 2 ) {
    sprintf( filename, "/suuri/rev2024/wakuc/data/part/partnin2020-2029-%01d.csv", MODE ) ;
    if ( ( fp_part = fopen( filename, "r" ) ) == NULL ) {
      fprintf( stderr, "パート入力ファイル（２段階）を開けません!\n" ) ;
      exit(2) ;
    }
    karayomi( fp_part ) ;  
    for ( kubun = 1 ; kubun <= 11 ; kubun++ ) {
      read_csv( buffer, fp_part, &data_number ) ;
      ii = (int) buffer[0] ;
      kbetu_partkiso[1][ii][1][1][3] = (double) buffer[1] ;
      kbetu_partkiso[1][ii][2][1][3] = (double) buffer[2] ;
      kbetu_partkiso[1][ii][7][1][3] = (double) buffer[3] ;
      kbetu_partkiso[2][ii][1][1][3] = (double) buffer[4] ;
      kbetu_partkiso[2][ii][2][1][3] = (double) buffer[5] ;
      kbetu_partkiso[2][ii][7][1][3] = (double) buffer[6] ;
      kbetu_partkiso[1][ii][1][2][3] = (double) buffer[7] ;
      kbetu_partkiso[1][ii][2][2][3] = (double) buffer[8] ;
      kbetu_partkiso[1][ii][7][2][3] = (double) buffer[9] ;
      kbetu_partkiso[2][ii][1][2][3] = (double) buffer[10] ;
      kbetu_partkiso[2][ii][2][2][3] = (double) buffer[11] ;
      kbetu_partkiso[2][ii][7][2][3] = (double) buffer[12] ;
      kbetu_partkiso[1][ii][1][3][3] = (double) buffer[13] ;
      kbetu_partkiso[1][ii][2][3][3] = (double) buffer[14] ;
      kbetu_partkiso[1][ii][7][3][3] = (double) buffer[15] ;
      kbetu_partkiso[2][ii][1][3][3] = (double) buffer[16] ;
      kbetu_partkiso[2][ii][2][3][3] = (double) buffer[17] ;
      kbetu_partkiso[2][ii][7][3][3] = (double) buffer[18] ;
    }
    fclose( fp_part ) ;
  }
}


void read_roud( FILE *fp, int ynendo1, int ynendo2 ) {
  
  int  ii ;
  int  jj ;
  double  buffer[DATA_MAX] ;
  int     data_number      ;

  karayomi( fp ) ;
  for ( jj = 1 ; jj <= 3 ; jj++ ) {
    karayomi( fp ) ;
    karayomi( fp ) ;
    for ( ii = ynendo1 ; ii <= ynendo2 ; ii++ ) {
      read_csv( buffer, fp, &data_number ) ;
      nendo = buffer[0] ;
      sei = buffer[1] ;
      for ( nenrei = 15 ; nenrei <= 105 ; nenrei++ ) {
        TEMP[nendo-STARTY][sei][nenrei] = buffer[nenrei-12] ;
      }
    }
  }
}


void read_map( FILE *fp, int nendo ) {
  
  int  ii ;
  int  jj ;
  double  buffer[DATA_MAX] ;
  int     data_number      ;

  karayomi( fp ) ;
  for( jj = 1 ; jj <= 2 ; jj++ ) {
    karayomi( fp );
	karayomi( fp );
    for ( ii = 15 ; ii <= 89 ; ii++ ) {
      read_csv( buffer, fp, &data_number ) ;
      nenrei = buffer[0] ;
      kounen[2][nendo-STARTY][jj][nenrei] = buffer[1] ;
      kounen[3][nendo-STARTY][jj][nenrei] = buffer[2] ;
      kounen[4][nendo-STARTY][jj][nenrei] = buffer[3] ;
      kounen[5][nendo-STARTY][jj][nenrei] = buffer[4] ;
      kounen[6][nendo-STARTY][jj][nenrei] = buffer[5] ;
      partnin[nendo-STARTY][jj][nenrei][0][0][0] = buffer[6] ;
      kounen[1][nendo-STARTY][jj][nenrei]
	  = kounen[2][nendo-STARTY][jj][nenrei] + kounen[3][nendo-STARTY][jj][nenrei] ;
      kounen[0][nendo-STARTY][jj][nenrei]
      = kounen[1][nendo-STARTY][jj][nenrei] + kounen[4][nendo-STARTY][jj][nenrei]
      + kounen[5][nendo-STARTY][jj][nenrei] + kounen[6][nendo-STARTY][jj][nenrei] ;
      sangou[1][nendo-STARTY][jj][nenrei] = buffer[7] ;
      sangou[4][nendo-STARTY][jj][nenrei] = buffer[8] ;
      sangou[5][nendo-STARTY][jj][nenrei] = buffer[9] ;
      sangou[6][nendo-STARTY][jj][nenrei] = buffer[10] ;
      sangou[0][nendo-STARTY][jj][nenrei]
      = sangou[1][nendo-STARTY][jj][nenrei] + sangou[4][nendo-STARTY][jj][nenrei]
      + sangou[5][nendo-STARTY][jj][nenrei] + sangou[6][nendo-STARTY][jj][nenrei] ;
      ichigou[1][nendo-STARTY][jj][nenrei] = buffer[11] ;
      ichigou[2][nendo-STARTY][jj][nenrei] = buffer[12] ;
      ichigou[0][nendo-STARTY][jj][nenrei]
      = ichigou[1][nendo-STARTY][jj][nenrei] + ichigou[2][nendo-STARTY][jj][nenrei] ;
    }
  }
  for ( nenrei = 15 ; nenrei <= 89 ; nenrei++ ) {
    for ( seido = 0 ; seido <= 6 ; seido++ ) {
      kounen[seido][nendo-STARTY][0][nenrei]
      = kounen[seido][nendo-STARTY][1][nenrei] + kounen[seido][nendo-STARTY][2][nenrei] ;
      sangou[seido][nendo-STARTY][0][nenrei]
      = sangou[seido][nendo-STARTY][1][nenrei] + sangou[seido][nendo-STARTY][2][nenrei] ;
    }
    for ( seido = 0 ; seido <= 2 ; seido++ ) {
      ichigou[seido][nendo-STARTY][0][nenrei]
      = ichigou[seido][nendo-STARTY][1][nenrei] + ichigou[seido][nendo-STARTY][2][nenrei] ;
    }
    partnin[nendo-STARTY][0][nenrei][0][0][0]
    = partnin[nendo-STARTY][1][nenrei][0][0][0] + partnin[nendo-STARTY][2][nenrei][0][0][0];
  }
}
