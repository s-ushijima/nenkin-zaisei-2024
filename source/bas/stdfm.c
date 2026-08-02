#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "snaps.h"
#include "mcntl.h"

using namespace std;


int read_str( char buffer[][BUFFER_MAX] , FILE *fp , int *data_number_ptr )
{
	int c;
	int previous_c;
	int data_number;
	int comma_number;
	char s[BUFFER_MAX];
	char *sptr;


	data_number = -1;
	comma_number = 0;
	sptr = s;

	while( ( ( c = fgetc(fp) ) != EOF) && (c != '\n') )
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


	value = read_str( buffer_str , fp , data_number_ptr );


	for (i = 0 ; i <= *data_number_ptr ;i++)
	{
		buffer[i] = atof(buffer_str[i]);
	}

	return( value );

}


int chg_str(char *buf, const char *str1, const char *str2)
{
	char tmp[BUFFER_MAX];
	char *p;

	while( ( p = strstr( buf, str1 ) ) != NULL ) 
	{
		*p = '\0';
		p += strlen(str1);
		strcpy(tmp, p);
		strcat(buf, str2);
		strcat(buf, tmp);
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
			sscanf( char_buffer, "#%d-%d-%d" , &seido , &system , &jouhou );
			if( seido == 99 )
			{
				Done = 1;
			}
		}
	}
}


void write_BeginData( FILE *fp )
{
	time_t w_time;
	struct tm *w_tm;

	time( &w_time );
	w_tm = localtime( &w_time );

	fprintf( fp , "%s", asctime( w_tm ) );

	fprintf( fp , "#99-0000-0000\n" );
}


int Round( double a , int b )
{
	int c;
	int d;
	int i;
	int S;

	S = 1;
	for( i = 1 ; i <= b ; i++ )
	{
		S *= 10;
	}
	a /= S;
	d = (int)( a + 0.5 );
	c = d * S;

	return( c );
}


double max( double a , double b )
{
	return( ( a > b ) ? a : b );
}


double min( double a , double b )
{
	return( ( a < b ) ? a : b );
}
