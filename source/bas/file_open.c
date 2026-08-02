#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include "snaps.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


void file_get( FILE *fp , FILE *fp_io[] , char file_name[][BUFFER_MAX] );

int digit_chk( char *digit_str );


void file_open( char *file_list , FILE *fp_io[] , char file_name[][BUFFER_MAX] )
{
	FILE *fp;

	if( ( fp = fopen( file_list , "r" ) ) == NULL )
	{
		printf( "ファイルリストのオープンに失敗しました (%s)\n" , file_list);
		exit(1);
	}

	file_get( fp , fp_io , file_name );

	fclose( fp );


	return;

}


void file_get( FILE *fp , FILE *fp_io[] , char file_name[][BUFFER_MAX] )
{
	char buffer[DATA_MAX][BUFFER_MAX];
	int data_number;
	int cnt = 0;
	int number;
	int NUM_COLUMN = 0;
	int READ_WRITE_COLUMN = 1;
	int DIR_COLUMN = 2;
	int FILE_COLUMN = 3;
	int MODE_COLUMN = 4;


	read_str( buffer , fp , &data_number );

	while( read_str( buffer , fp , &data_number ) != EOF )
	{
		cnt++;

		if( strcmp( buffer[READ_WRITE_COLUMN] , "B" ) == 0 )
		{
			if( CUT_KOTEI == 1 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "1" );
			}
			else if( CUT_KOTEI == 0 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "0" );
			}
		}

		if( strcmp( buffer[READ_WRITE_COLUMN] , "C" ) == 0 )
		{
			if( kako == 1 || kako == 2 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "1" );
			}
			else if( kako == 0 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "0" );
			}
		}

		if( strcmp( buffer[READ_WRITE_COLUMN] , "D" ) == 0 )
		{
			if( TOUGOU == 1 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "1" );
			}
			else if( TOUGOU == 0 )
			{
				strcpy( buffer[READ_WRITE_COLUMN] , "0" );
			}
		}

		if( atoi( buffer[READ_WRITE_COLUMN] ) == 1 )
		{
			if( digit_chk( buffer[NUM_COLUMN] ) == 0 )
			{
				printf( "%d番目のファイルリストが取得できません。\n" , cnt );
				exit( 1 );
			}

			number = atoi( buffer[NUM_COLUMN] );

			sprintf( file_name[number] , "%s%s", buffer[DIR_COLUMN] , buffer[FILE_COLUMN] );

			chg_str( file_name[number] , "{HIYOUSYADATA}" , HIYOUSYADATA );
			chg_str( file_name[number] , "{KOKUNENDATA}" , KOKUNENDATA );
			chg_str( file_name[number] , "{ECON}" , ECON );
			chg_str( file_name[number] , "{SOTOWAKU}" , SOTOWAKU );
			chg_str( file_name[number] , "{SOTOWAKU_CUT}" , SOTOWAKU_CUT );
			chg_str( file_name[number] , "{Version}" , Version );
			chg_str( file_name[number] , "{Version_cut}" , Version_cut );
			chg_str( file_name[number] , "{Version_Jurai}" , Version_Jurai );
			chg_str( file_name[number] , "{KAKO}" , KAKO );
			chg_str( file_name[number] , "{YOBI}" , YOBI );

			if ( ( fp_io[number] = fopen( file_name[number] , buffer[MODE_COLUMN]) ) == NULL )
			{
				printf( "%sの取得に失敗しました\n" , file_name[number] );
				exit( 1 );
			}
		}
	}


	return;

}


int digit_chk( char *digit_str )
{
	int i;

	for( i = 0 ; i < strlen( digit_str ) ; i++ )
	{
		if( isdigit( digit_str[i] ) == 0 )
		{
			return 0;
		}
	}

	return 1;

}
