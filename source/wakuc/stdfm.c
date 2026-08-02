#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "set.h"


double raund( double a, int b ) {
  double c ;
  int d ;
  int i ;
  int S ;
  S = 1 ;
  if ( b > 0 ) {
    for ( i = 1 ; i <= b ; i++ ) {
      S *=10 ;
    }
    a = a * S ;
	if ( a > 0.0 ) {
      d = (int)( a + 0.5 ) ;
	}
    else {
	  d = (int)( a - 0.5 ) ;
	}
    c = (double) d / S ;
    return(c) ;
  }
  else if ( b == 0 ) {
	if ( a > 0.0 ) {
      d = (int)( a + 0.5 ) ;
	}
    else {
	  d = (int)( a - 0.5 ) ;
	}
    c = (double) d / 1 ;
    return(c) ;
  }
  else {
    for ( i = -1 ; i >= b ; i-- ) {
      S *= 10 ;
    }
    a = a / S ;
	if ( a > 0.0 ) {
	  d = (int)( a + 0.5 ) ;
	}
	else {
	  d = (int)( a - 0.5 ) ;
	}
    c = (double) d * S ;
    return(c) ;
  }
}


int read_csv( double buffer[], FILE *fp, int *data_number_ptr ) {
  int c ;
  int previous_c ;
  int data_number ;
  int comma_number ;
  char s[BUFFER_MAX] ;
  char *sptr ;
  
  data_number = -1 ;
  comma_number = 0 ;
  sptr = s; 
  
  while ( ( ( c = fgetc(fp) ) != EOF ) && ( c != '\n' ) ) {
    if ( c == ',' )  {
      if ( ++comma_number > DATA_MAX ) {
        printf( "エラー(in read_data) １行の中のカンマの数が%d個を超えています。", DATA_MAX ) ; 
        exit(1) ;
      }
      if ( sptr - s > BUFFER_MAX - 1 ) {
        printf("エラー(in read_data) １つのデータの文字数が%d個を超えています。", BUFFER_MAX-1 ) ; 
        exit(1) ;
      }
      
      *sptr = '\0' ;
      
      buffer[++data_number] = atof(s) ;
      
      sptr = s ;
    }
    else {
      *sptr++ = c ;
    }
    previous_c = c ;
  }
  
  if ( previous_c != ',' ) {
    if ( ++comma_number > DATA_MAX ) {
      printf( "エラー(in read_data) １行の中のカンマの数が%d個を超えています。", DATA_MAX ) ; 
      exit(1);
    }
    if ( sptr - s > BUFFER_MAX - 1 )  {    
      printf( "エラー(in read_data) １つのデータの文字数が%d個を超えています。\n", BUFFER_MAX-1 ) ; 
      exit(1) ;
    }
    
    *sptr = '\0' ;
    
    buffer[++data_number] = atof(s) ;
  }
  
  *data_number_ptr = data_number ;
  
  if ( c == EOF ) {
    return(EOF) ;
  }
  else {
    return(0) ;
  }
}


void karayomi( FILE *fp ) {
  int c ;
  while ( ( ( c = fgetc(fp) ) != EOF ) && ( c != '\n' ) ) {
  }
}
