#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


void waku()
{
	int nendo;
	int sotai_nendo;
	int nenrei;
	int seibetu;
	int shubetu;
	int waku_seido;
	int waku_seido_2gou;
	int waku_seido_p;
	int counter;
	double buffer[BUFFER_MAX];
	int data_number;
	FILE *fp;


	for( shubetu = 0 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		for( nendo = SOTOWAKU_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SOTOWAKU_SHONENDO;

			for( nenrei = MIN_WAKU_NENREI ; nenrei <= MAX_WAKU_NENREI ; nenrei++ )
			{
				Sotowaku[shubetu][sotai_nendo][nenrei - MIN_WAKU_NENREI] = 0.;
				Sotowaku_Jurai[shubetu][sotai_nendo][nenrei - MIN_WAKU_NENREI] = 0.;
			}
		}
	}

	for( seibetu = 0 ; shubetu <= 2 ; seibetu++ )
	{
		for( nendo = SOTOWAKU_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SOTOWAKU_SHONENDO;

			for( nenrei = MIN_WAKU_NENREI ; nenrei <= MAX_WAKU_NENREI ; nenrei++ )
			{
				Sotowaku_2gou[seibetu][sotai_nendo][nenrei - MIN_WAKU_NENREI] = 0.;
			}
		}
	}

	for( waku_seido = 0 ; waku_seido <= 2 ; waku_seido++ )
	{
		switch( waku_seido )
		{
			case 0:
				fp = fp_in[SOTOWAKU_JINKO];
				break;

			case 1:
				fp = fp_in[SOTOWAKU_1GOU];
				break;

			case 2:
				fp = fp_in[SOTOWAKU_3GOU];
				break;
		}

		for( counter = 1 ; counter <= 2 ; counter++ )
		{
			read_data( buffer , fp , &data_number );
		}

		for( seibetu = 0 ; seibetu <= 2 ; seibetu++ )
		{
			for( nendo = SOTOWAKU_SHONENDO ; nendo <= SOTOWAKU_SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SOTOWAKU_SHONENDO;

				if( read_data( buffer , fp , &data_number ) != EOF && buffer[1] == seibetu && buffer[2] == nendo )
				{
					if( seibetu >= 1 )
					{
						for( nenrei = MIN_WAKU_NENREI - 11 ; nenrei <= MAX_WAKU_NENREI - 11 ; nenrei++ )
						{
							Sotowaku[( seibetu - 1 ) * 3 + waku_seido + 1][sotai_nendo][nenrei + 11 - MIN_WAKU_NENREI]
							 = buffer[nenrei];
						}
					}
				}
				else
				{
					cout << "外枠ファイル読込中にＥＯＦを検出しました" << endl;
					exit( 1 );
				}
			}
		}

	}

	for( waku_seido_2gou = 1 ; waku_seido_2gou <= 4 ; waku_seido_2gou++ )
	{
		switch( waku_seido_2gou )
		{
			case 1:
				fp = fp_in[SOTOWAKU_2GOU_KOU];
				break;

			case 2:
				fp = fp_in[SOTOWAKU_2GOU_KOK];
				break;

			case 3:
				fp = fp_in[SOTOWAKU_2GOU_REN];
				break;

			case 4:
				fp = fp_in[SOTOWAKU_2GOU_SIG];
				break;
		}

		for( counter = 1 ; counter <= 2 ; counter++ )
		{
			read_data( buffer , fp , &data_number );
		}

		for( seibetu = 0 ; seibetu <= 2 ; seibetu++ )
		{
			for( nendo = SOTOWAKU_SHONENDO ; nendo <= SOTOWAKU_SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SOTOWAKU_SHONENDO;

				if( read_data( buffer , fp , &data_number ) != EOF && buffer[1] == seibetu && buffer[2] == nendo )
				{
					if( seibetu >= 1 )
					{
						for( nenrei = MIN_WAKU_NENREI - 11 ; nenrei <= MAX_WAKU_NENREI - 11 ; nenrei++ )
						{
							Sotowaku_2gou[seibetu][sotai_nendo][nenrei + 11 - MIN_WAKU_NENREI] += buffer[nenrei];
						}
					}
				}
				else
				{
					cout << "外枠ファイル読込中にＥＯＦを検出しました" << endl;
					exit( 1 );
				}
			}
		}

	}

	if( Option == 1 )
	{
		for( waku_seido = 0 ; waku_seido <= 2 ; waku_seido++ )
		{
			switch(waku_seido)
			{
				case 0:
					fp = fp_in[SOTOWAKU_JINKO_JURAI];
					break;

				case 1:
					fp = fp_in[SOTOWAKU_1GOU_JURAI];
					break;

				case 2:
					fp = fp_in[SOTOWAKU_3GOU_JURAI];
					break;
			}

			for( counter = 1 ; counter <= 2 ; counter++ )
			{
				read_data( buffer , fp , &data_number );
			}

			for( seibetu = 0 ; seibetu <= 2 ; seibetu++ )
			{
				for( nendo = SOTOWAKU_SHONENDO ; nendo <= SOTOWAKU_SAISHUNENDO ; nendo++ )
				{
					sotai_nendo = nendo - SOTOWAKU_SHONENDO;

					if( read_data( buffer , fp , &data_number ) != EOF && buffer[1] == seibetu && buffer[2] == nendo )
					{
						if( seibetu >= 1 )
						{
							for( nenrei = MIN_WAKU_NENREI - 11 ; nenrei <= MAX_WAKU_NENREI - 11 ; nenrei++ )
							{
								Sotowaku_Jurai[( seibetu - 1 ) * 3 + waku_seido + 1][sotai_nendo][nenrei + 11 - MIN_WAKU_NENREI]
								 = buffer[nenrei];
							}
						}
					}
					else
					{
						cout << "外枠ファイル読込中にＥＯＦを検出しました" << endl;
						exit( 1 );
					}
				}
			}
		}
	}


	return;

}
