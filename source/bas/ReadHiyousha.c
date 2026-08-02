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


void readerror_h( int seido );


void ReadHiyousha( int seido )
{
	int nendo;
	int nenrei;
	int seibetu;
	int counter;
	int sotai_nendo;
	int data_number;
	double buffer[DATA_MAX];


	read_headder( fp_in[seido] );

	while( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
	{
		if( buffer[0] == SUIKEISHONENDO -2000 - 1 && buffer[1] == 2 && buffer[2] == 3 && buffer[3] == 2 )
		{
			break;
		}
	}

	for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 1 && buffer[5] == seibetu )
						{
							Rorei_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][NOUFU] = buffer[6] * hosei_shin[ROREI][sotai_nendo];
							Rorei_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO_ZENHAN] = buffer[7] * hosei_shin[ROREI][sotai_nendo];
							Rorei_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO_KOUHAN] = buffer[8] * hosei_shin[ROREI][sotai_nendo];
							FurikaeKasan[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][ROREI] = buffer[9] * hosei_shin[ROREI][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は新法老齢基礎年金" << endl;
							exit(1);
						}
					}
				}
				else
				{
					readerror_h( seido );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 2 && buffer[5] == seibetu )
						{
							Shogai_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][IPPAN][KIHON] = buffer[6] * hosei_shin[SHOGAI][sotai_nendo];
							Shogai_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][IPPAN][KAKYU] = buffer[7] * hosei_shin[SHOGAI][sotai_nendo];
							FurikaeKasan[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][SHOGAI] = buffer[8] * hosei_shin[SHOGAI][sotai_nendo];
							Shogai_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][HATACHIMAE][KIHON] = buffer[9] * hosei_shin[SHOGAI][sotai_nendo];
							Shogai_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][HATACHIMAE][KAKYU] = buffer[10] * hosei_shin[SHOGAI][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は新法障害基礎年金" << endl;
							exit(1);
						}
					}
				}
				else
				{
					readerror_h( seido );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 3 && buffer[5] == seibetu )
						{
							Izoku_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON] = buffer[6] * hosei_shin[IZOKU][sotai_nendo];
							Izoku_New[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU] = buffer[7] * hosei_shin[IZOKU][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は新法遺族基礎年金" << endl;
							exit(1);
						}
					}
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 1 && buffer[5] == seibetu )
						{
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][NOUFU] = buffer[6] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO] = buffer[7] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU_NOUFU] = buffer[8] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU_MENJO] = buffer[9] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KASANOUFU] = buffer[10] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KASAMENJO] = buffer[11] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][ROFUKU_SHITASASAE] = buffer[12] * hosei_kyu[seido][sotai_nendo];
							Rorei_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][GONEN] = buffer[13] * hosei_kyu[seido][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は旧法老齢・通老年金" << endl;
							exit(1);
						}
					}
				}
				else
				{
					readerror_h( seido );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 2 && buffer[5] == seibetu )
						{
							Shogai_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][NOUFU] = buffer[6] * hosei_kyu[seido][sotai_nendo];
							Shogai_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][MENJO] = buffer[7] * hosei_kyu[seido][sotai_nendo];
							Shogai_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][NOUFU] = buffer[8] * hosei_kyu[seido][sotai_nendo];
							Shogai_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][MENJO] = buffer[9] * hosei_kyu[seido][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は旧法障害年金" << endl;
							exit(1);
						}
					}
				}
				else
				{
					readerror_h( seido );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
				{
					if( sotai_nendo >= 0 )
					{
						if( buffer[0] == nendo - 2000 && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 3 && buffer[5] == seibetu )
						{
							Izoku_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][NOUFU] = buffer[6] * hosei_kyu[seido][sotai_nendo];
							Izoku_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][MENJO] = buffer[7] * hosei_kyu[seido][sotai_nendo];
							Izoku_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][NOUFU] = buffer[8] * hosei_kyu[seido][sotai_nendo];
							Izoku_Old[seido][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][MENJO] = buffer[9] * hosei_kyu[seido][sotai_nendo];
						}
						else
						{
							cout << "正常に読めていません 読込箇所は旧法遺族年金" << endl;
							exit(1);
						}
					}
				}
				else
				{
					readerror_h( seido );
				}
			}
		}

		for( counter = 1 ; counter <= 6 ; counter++ )
		{
			if( read_data( buffer , fp_in[seido] , &data_number ) != EOF )
			{
			}
			else
			{
				readerror_h( seido );
			}
		}
	}
	fclose( fp_in[seido] );

}


void readerror_h(int seido)
{
	cout << "制度番号＝ " << seido << " ファイルの入力中にエラーが発生しました" << endl;
	exit(1);
}
