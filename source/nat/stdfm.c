#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include "snaps.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


int read_str( char buffer[][BUFFER_MAX] , FILE *fp , int *data_number_ptr )
{
	int c;
	int previous_c;
	int data_number;
	int comma_number;
	char s[BUFFER_MAX];
	char *sptr;

	using namespace std;

	data_number = -1;
	comma_number = 0;
	sptr = s;

	while( ( ( c = fgetc(fp) ) != EOF ) && ( c != '\n' ) )
	{
		if( c == ',' )
		{
			if( ++comma_number > DATA_MAX )
			{
				cout << "エラー(in read_data) １行の中のカンマの数が" << DATA_MAX << "個を超えています" << endl;
				cout << 1 <<endl;
				exit( 1 );
			}

			if( sptr - s > BUFFER_MAX - 1 )
			{
				cout << "エラー(in read_data) １つのデータの文字数が" << BUFFER_MAX - 1 << "個を超えています" << endl;
				cout << 2 <<endl;
				exit( 1 );
			}

			*sptr = '\0';

			data_number++;
			strcpy(	&(buffer[data_number][0]) , s );

			sptr = s;
		}
		else
		{
			*sptr++ = c;
		}

		previous_c = c;
	}

	if( previous_c != ',' )
	{
		if( ++comma_number > DATA_MAX )
		{
			cout << "エラー(in read_data) １行の中のカンマの数が" << DATA_MAX << "個を超えています" << endl;
				cout << 3 <<endl;
			exit( 1 );
		}

		if( sptr - s > BUFFER_MAX - 1 )
		{
			cout << "エラー(in read_data) １つのデータの文字数が" << BUFFER_MAX - 1 << "個を超えています" << endl;
				cout << 4 <<endl;
			exit( 1 );
		}

		*sptr = '\0';

		data_number++;
		strcpy(	&(buffer[data_number][0]) , s );
	}

	*data_number_ptr = data_number;

	if( c == EOF )
	{
		return(EOF);
	}
	else
	{
		return(0);
	}

}


int read_data( double buffer[] , FILE *fp , int *data_number_ptr )
{
	char buffer_str[DATA_MAX][BUFFER_MAX];
	int i;
	int value;

	using namespace std;

	value = read_str( buffer_str , fp , data_number_ptr );

	for (i = 0 ; i <= *data_number_ptr ; i++ )
	{
		buffer[i] = atof(buffer_str[i]);
	}

	return(value);

}


int buffer_set1( double buffer[] , FILE *fp ,int *data_number_ptr , int buf_0 , const char *msg )
{
	if( read_data (buffer , fp , data_number_ptr ) != EOF )
	{
		if( (int) buffer[0] != buf_0 )
		{
			printf( "%sデータが不正です。buffer[0]=%d\n" , msg,buffer[0] );
			exit(1);
		}
	}
	else
	{
			printf( "%sデータ読み込み中にEOFを検出しました。\n" );
			exit(1);
	}

	return 0;
}


int buffer_set2( double buffer[] , FILE *fp ,int *data_number_ptr , int buf_0 ,int buf_1 , const char *msg )
{
	if( read_data (buffer , fp , data_number_ptr ) != EOF )
	{
		if( (int) buffer[0] != buf_0 || (int) buffer[1] != buf_1 )
		{
			printf( "%sデータが不正です。buffer[0]=%d , buffer[1]=%d\n" , msg,buffer[0] , buffer[1] );
			exit(1);
		}
	}
	else
	{
			printf( "%sデータ読み込み中にEOFを検出しました。\n" );
			exit(1);
	}

	return 0;
}


int data_skip( FILE *fp, int cnt )
{
	int i;
	double buffer[BUFFER_MAX];
	int data_number;

	for ( i = 0 ; i < cnt ; i++ )
	{
		read_data ( buffer , fp , &data_number );
	}

	return 0;
}


int chg_str( char *buf , const char *str1 , const char *str2 )
{
	char tmp[BUFFER_MAX];
	char *p;

	while( (p = strstr(buf, str1)) != NULL )
	{
		*p = '\0';
		p += strlen( str1 );
		strcpy( tmp , p );
		strcat( buf , str2 );
		strcat( buf , tmp );
	}

		return 0;

}


void read_headder( FILE *fp )
{
	char char_buffer[257];
	int seido;
	int system;
	int jouhou;
	int Done;
	
	Done = 0;
	
	while( Done == 0 && fgets( char_buffer , 256 , fp ) != NULL )
	{
		if( char_buffer[0] == '#' )
		{
			sscanf( char_buffer , "#%d-%d-%d" , &seido , &system , &jouhou );
			if( seido == 99 )
			{
				Done = 1;
			}
		}
	}
}


void write_BeginData( char ver[] , char ShisanNaiyou[] , FILE *fp )
{
	time_t w_time;
	struct tm *w_tm;

	time( &w_time );
	w_tm = localtime( &w_time );

	fprintf( fp , "%s\n", asctime( w_tm ) );

	fprintf( fp , "%s\n" , ver );
	fprintf( fp , "%s" , ShisanNaiyou );

	fprintf( fp , "#99-0000-0000\n" );
}


double max( double a , double b )
{
	return( ( a > b ) ? a : b );
}


double min( double a , double b )
{
	return( ( a < b ) ? a : b );
}


double fdiv( double a ,double b )
{
	if( fabs( b ) < EPSILON )
	{
		return 0.;
	}
	else
	{
		return a / b ;
	}
}


double array_sum( double x[] , int min , int max )
{
	int i;
	double sum = 0.;

	for( i = min ; i < max ; i++ )
	{
		sum += x[i];
	}

	return sum;

}


int encho_year( int nendo )
{
	int r = 0;
	int max_hikiage_nensu = OP_MAX_KYOSHUTU_NENREI - MAX_KYOSHUTU_NENREI;


	if( Option == 1 )
	{
		while( nendo >= OPTION_START + r * OP_HIKIAGE_KANKAKU )
		{
			r++;

			if( r >= max_hikiage_nensu )
			{
				break;
			}
		}
	}


	return r;

}


int encho_nensu( int nendo , int nenrei )
{
	int k = 0;
	int max_hikiage_nensu = OP_MAX_KYOSHUTU_NENREI - MAX_KYOSHUTU_NENREI;


	if( Option == 1 )
	{
		while( k < encho_year( nendo - nenrei + 60 + k ) )
		{
			k++;

			if( k >= max_hikiage_nensu )
			{
				break;
			}
		}
	}


	return k;

}


int extenda( int nendo , int nenrei )
{
	int counter = 0;

	if( Option == 1 )
	{
		if( encho_nensu( nendo , nenrei ) > 0 && nenrei <= 65 
			&& nenrei >= 60 + encho_nensu( nendo , nenrei ) )
		{
			counter = 1;
		}
	}


	return counter;

}


int extendb( int nendo , int nenrei )
{
	int counter = 0;

	if( Option == 1 )
	{
		if( nenrei >= 60 && nenrei < 60 + encho_nensu( nendo , nenrei ) )
		{
			counter = 1;
		}
	}


	return counter;

}


int extendc( int nendo , int nenrei )
{
	int counter = 0;

	if( Option == 1 )
	{
		if( encho_nensu( nendo , nenrei ) > 0 && nenrei == 60 + encho_nensu( nendo , nenrei ) )
		{
			counter = 1;
		}
	}


	return counter;

}


int extendd( int nendo , int nenrei )
{
	int counter = 0;

	if( Option == 1 )
	{
		if( encho_nensu( nendo , nenrei ) > 0 && nenrei > 65 && nenrei <= 70 )
		{
			counter = 1;
		}
	}


	return counter;

}
