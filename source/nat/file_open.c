#include <cstring>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "snaps.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


int digit_chk(char *digit_str);


void file_open( char *file_list , FILE *fp_io[] , char file_name[][BUFFER_MAX] )
{
	FILE *fp;
	char buffer[DATA_MAX][BUFFER_MAX];
	int data_number;
	int cnt;
	int number;

	int NUM_COLUMN = 0;
	int READ_WRITE_COLUMN = 1;
	int DIR_COLUMN = 2;	
	int FILE_COLUMN = 3;
	int MODE_COLUMN = 4;


	if( ( fp = fopen( file_list , "r" ) ) == NULL )
	{
		printf( "ファイルリストのオープンに失敗しました (%s)\n" , file_list);
		exit(1);
	}


	read_str( buffer , fp , &data_number );

	cnt = 0;

	while( read_str( buffer , fp , &data_number ) != EOF )
	{
		cnt++;

		if( atoi( buffer[READ_WRITE_COLUMN] ) == 1 )
		{
			if( digit_chk( buffer[NUM_COLUMN] ) == 0 )
			{
				printf( "%d番目のファイルリストが取得できません。\n" , cnt );
				exit(1);
			}

			number = atoi( buffer[NUM_COLUMN] );

			sprintf( file_name[number] , "%s%s", buffer[DIR_COLUMN] , buffer[FILE_COLUMN] );

			chg_str( file_name[number] , "{KOKUNEN}" , KOKUNEN );
			chg_str( file_name[number] , "{ECON}" , ECON );
			chg_str( file_name[number] , "{SOTOWAKU}" , SOTOWAKU );
			chg_str( file_name[number] , "{SOTOWAKU_JURAI}" , SOTOWAKU_JURAI );
			chg_str( file_name[number] , "{Version}" , Version );
			chg_str( file_name[number] , "{KAKO}" , KAKO );
			chg_str( file_name[number] , "{BIRTHFILE}" , BIRTHFILE );
			chg_str( file_name[number] , "{DEATH}" , DEATH );

			if ( ( fp_io[number] = fopen( file_name[number] , buffer[MODE_COLUMN] ) ) == NULL )
			{
				printf( "%sの取得に失敗しました\n" , file_name[number] );
				exit(1);
			}
		}
	}

	fclose( fp );


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
