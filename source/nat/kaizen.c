#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mkisoritu.h"

using namespace std;


void kaizen()
{
	int data_number;
	int nendo;
	int nenrei;
	int seibetu;
	double buffer[120];


	if( read_data( buffer , fp_in[LIFETABLE] , &data_number ) != EOF )
	{
		
	}
	else
	{
		cout << "LIFETABLEファイル読込途中にＥＯＦを検出しました" << endl;
		exit( 1 );
	}

	for( seibetu = 0 ; seibetu <= 1 ; seibetu++ )
	{
		for( nendo = SHIKKENRITU_MIN ; nendo <= SHIKKENRITU_MAX ; nendo++ )
		{
			if( read_data( buffer , fp_in[LIFETABLE] , &data_number ) != EOF )
			{
				for( nenrei = 0 + 1 ; nenrei <= MAX_ROREI_JUKYU - 1 + 1 ; nenrei++ )
				{
					q[nendo - SHIKKENRITU_MIN][nenrei - 1][seibetu] = buffer[nenrei];
					q[nendo - SHIKKENRITU_MIN][nenrei - 1][seibetu] /= 100000.;
				}
			}
			else
			{
				cout << "LIFETABLEファイル読込途中にＥＯＦを検出しました" << endl;
				exit( 1 );
			}
		}
	}

	for( seibetu = 0 ; seibetu <= 1 ; seibetu++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][seibetu] = 0.;
			}
		}
	}

	if( read_data( buffer , fp_in[IZOKU_KEINEN] , &data_number ) != EOF )
	{
		
	}
	else
	{
		printf( "有配偶率ファイル読込途中にＥＯＦを検出しました\n" );
		exit( 1 );
	}

	for( seibetu = 0 ; seibetu <= 1 ; seibetu++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp_in[IZOKU_KEINEN] , &data_number ) != EOF && 
				buffer[0] == seibetu && buffer[1] == nenrei )
			{
				for( nendo = I_KEINEN_SHONENDO ; nendo <= I_KEINEN_SAISHUNENDO ; nendo++ )
				{
					Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][seibetu]
					 = buffer[nendo - I_KEINEN_SHONENDO + 2];
				}
			}
			else
			{
				printf( "有配偶率ファイル読込途中にＥＯＦを検出しました\n" );
				exit( 1 );
			}
		}
	}

	for( seibetu = 0 ; seibetu <= 1 ; seibetu++ )
	{
		for( nendo = I_KEINEN_SAISHUNENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][seibetu]
				 = Izoku_Keinen[I_KEINEN_SAISHUNENDO - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][seibetu];
			}
		}
	}


	return;

}
