#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


int encho_year( int nendo );


void waku()
{
	int nendo;
	int sotai_nendo;
	int nenrei;
	int seibetu;
	int seido;
	int goubetu;
	int counter;
	int counter2;
	int waku_seido;
	double buffer[BUFFER_MAX];
	int data_number;


	for( waku_seido = SOTOWAKU_START ; waku_seido <= SHIGAKU_3GOU ; waku_seido++ )
	{
		for( counter = 1 ; counter <= 2 ; counter++ )
		{
			read_data( buffer , fp_in[waku_seido] , &data_number );
		}
		for( seibetu = SUM ; seibetu <= ONNA ; seibetu++ )
		{
			for( nendo = SOTOWAKU_SHONENDO ; nendo <= SOTOWAKU_SAISHUNENDO ; nendo++ )
			{
				if( read_data( buffer , fp_in[waku_seido] , &data_number ) != EOF
					 && buffer[1] == seibetu && buffer[2] == nendo )
				{
					if( seibetu >= OTOKO && nendo >= SHONENDO )
					{
						if( Option == 0 )
						{
							if( waku_seido == KOKUNEN_1GOU )
							{
								Hiho_Kokunen[nendo - SHONENDO] += buffer[3];
							}
 							else if( waku_seido <= SHIGAKU_2GOU )
							{
								for( nenrei = MIN_HIHO_NENREI - 11 ; nenrei <= 59 - 11 ; nenrei++ )
								{
									SanteiTaishou[waku_seido - SOTOWAKU_START + 1][nendo - SHONENDO][2]
									 += buffer[nenrei];
								}
							}
	 						else
							{
								for( nenrei = MIN_HIHO_NENREI - 11 ; nenrei <= 59 - 11 ; nenrei++ )
								{
									SanteiTaishou[waku_seido - SOTOWAKU_START - 3][nendo - SHONENDO][3]
									 += buffer[nenrei];
								}
							}
						}
						else if( Option == 1 )
						{
							if( waku_seido == KOKUNEN_1GOU )
							{
								Hiho_Kokunen[nendo - SHONENDO] += buffer[3];
							}
 							else if( waku_seido <= SHIGAKU_2GOU )
							{
								for( nenrei = MIN_HIHO_NENREI - 11 ; nenrei <= 59 - 11 + encho_year( nendo ) ; nenrei++ )
								{
									SanteiTaishou[waku_seido - SOTOWAKU_START + 1][nendo - SHONENDO][2]
									 += buffer[nenrei];
								}
							}
	 						else
							{
								for( nenrei = MIN_HIHO_NENREI - 11 ; nenrei <= 59 - 11 + encho_year( nendo ) ; nenrei++ )
								{
									SanteiTaishou[waku_seido - SOTOWAKU_START - 3][nendo - SHONENDO][3]
									 += buffer[nenrei];
								}
							}
						}
					}
				}
				else
				{
					printf( "外枠ファイル読込中にＥＯＦを検出しました。枠制度番号は %d\n" , waku_seido );
					exit( 1 );
				}
			}
		}
	}

	for( nendo = SAISHUNENDO ; nendo >= SHONENDO + 1 ; nendo-- )
	{
		sotai_nendo = nendo - SHONENDO;

		Hiho_Kokunen[sotai_nendo] = ( Hiho_Kokunen[sotai_nendo - 1] + Hiho_Kokunen[sotai_nendo] ) / 2.;

		for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
		{
			for( goubetu = 1 ; goubetu <= 3 ; goubetu++ )
			{
				SanteiTaishou[seido][sotai_nendo][goubetu]
				 = ( SanteiTaishou[seido][sotai_nendo - 1][goubetu]
					 + SanteiTaishou[seido][sotai_nendo][goubetu] ) / 2.;
			}
		}
	}

	for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
	{
		for( goubetu = 2 ; goubetu <= 3 ; goubetu++ )
		{
			SanteiTaishou[seido][SHONENDO - SHONENDO][goubetu] = 0.;
		}
	}
	Hiho_Kokunen[SHONENDO - SHONENDO] = 0.;

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
		{
			for( goubetu = 1 ; goubetu <= 3 ; goubetu++ )
			{
				SanteiTaishou[seido][sotai_nendo][SUM] += SanteiTaishou[seido][sotai_nendo][goubetu];
			}
		}

		for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
		{
			for( goubetu = SUM ; goubetu <= 3 ; goubetu++ )
			{
				SanteiTaishou[SUM][sotai_nendo][goubetu] += SanteiTaishou[seido][sotai_nendo][goubetu];
			}
		}
	}

	return;

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
