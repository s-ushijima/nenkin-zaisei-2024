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


void readerror_jisseki( int i );


void ReadKokunen_jisseki()
{
	int nendo;
	int seibetu;
	int nenrei;
	int counter;
	int sotai_nendo;
	int data_number;
	double buffer[DATA_MAX];


	read_headder( fp_in[KOKUNEN] );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 1 && buffer[5] == seibetu )
					{
						Rorei_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][NOUFU] = buffer[6] * hosei_shin[ROREI][sotai_nendo];
						Rorei_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO_ZENHAN] = buffer[7] * hosei_shin[ROREI][sotai_nendo];
						Rorei_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO_KOUHAN] = buffer[8] * hosei_shin[ROREI][sotai_nendo];
						FurikaeKasan[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][ROREI] = buffer[9] * hosei_shin[ROREI][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は新法老齢基礎年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 1 );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 2 && buffer[5] == seibetu )
					{
						Shogai_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][IPPAN][KIHON] = buffer[6] * hosei_shin[SHOGAI][sotai_nendo];
						Shogai_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][IPPAN][KAKYU] = buffer[7] * hosei_shin[SHOGAI][sotai_nendo];
						FurikaeKasan[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][SHOGAI] = buffer[8] * hosei_shin[SHOGAI][sotai_nendo];
						Shogai_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][HATACHIMAE][KIHON] = buffer[9] * hosei_shin[SHOGAI][sotai_nendo];
						Shogai_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][HATACHIMAE][KAKYU] = buffer[10] * hosei_shin[SHOGAI][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は新法障害基礎年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 2 );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 1 && buffer[4] == 3 && buffer[5] == seibetu )
					{
						Izoku_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON] = buffer[6] * hosei_shin[IZOKU][sotai_nendo];
						Izoku_New[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU] = buffer[7] * hosei_shin[IZOKU][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は新法遺族基礎年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 3 );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 1 && buffer[5] == seibetu )
					{
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][NOUFU] = buffer[6] * hosei_kyu[KOKUNEN][sotai_nendo];
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][MENJO] = buffer[7] * hosei_kyu[KOKUNEN][sotai_nendo];
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KASANOUFU] = buffer[8] * hosei_kyu[KOKUNEN][sotai_nendo];
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KASAMENJO] = buffer[9] * hosei_kyu[KOKUNEN][sotai_nendo];
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][ROFUKU_SHITASASAE] = buffer[10] * hosei_kyu[KOKUNEN][sotai_nendo];
						Rorei_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][GONEN] = buffer[11] * hosei_kyu[KOKUNEN][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は旧法老齢・通老年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 4 );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 2 && buffer[5] == seibetu )
					{
						Shogai_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][NOUFU] = buffer[6] * hosei_kyu[KOKUNEN][sotai_nendo];
						Shogai_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][MENJO] = buffer[7] * hosei_kyu[KOKUNEN][sotai_nendo];
						Shogai_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][NOUFU] = buffer[8] * hosei_kyu[KOKUNEN][sotai_nendo];
						Shogai_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][MENJO] = buffer[9] * hosei_kyu[KOKUNEN][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は旧法障害年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 5 );
				}
			}

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				if( read_data( buffer , fp_in[KOKUNEN] , &data_number ) != EOF )
				{
					if( buffer[0] == nendo && buffer[1] == 1 && buffer[2] == nenrei && buffer[3] == 2 && buffer[4] == 3 && buffer[5] == seibetu )
					{
						Izoku_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][NOUFU] = buffer[6] * hosei_kyu[KOKUNEN][sotai_nendo];
						Izoku_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KIHON][MENJO] = buffer[7] * hosei_kyu[KOKUNEN][sotai_nendo];
						Izoku_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][NOUFU] = buffer[8] * hosei_kyu[KOKUNEN][sotai_nendo];
						Izoku_Old[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][seibetu][KAKYU][MENJO] = buffer[9] * hosei_kyu[KOKUNEN][sotai_nendo];
					}
					else if( sotai_nendo >= 0 )
					{
						cout << "正常に読めていません 読込箇所は旧法遺族年金" << endl;
						exit(1);
					}
				}
				else
				{
					readerror_jisseki( 6 );
				}
			}
		}

		if( read_data( buffer, fp_in[KOKUNEN] , &data_number ) != EOF )
		{
			if( buffer[0] == nendo )
			{
				SanteiTaishou[KOKUNEN][sotai_nendo][1] += buffer[1];
				SanteiTaishou[KOKUNEN][sotai_nendo][1] += buffer[2];

				Sankyu_Taishou[sotai_nendo] += buffer[3];
				Ikukyu_Taishou[sotai_nendo] += buffer[4];
			}
			else if( sotai_nendo >= 0 )
			{
				cout << "正常に読めていません 読込箇所は拠出金算定対象者数" << endl;
				exit(1);
			}
		}
		else
		{
			readerror_jisseki( 7 );
		}

		for( counter = 1 ; counter <= 6 ; counter++ )
		{
			if( read_data( buffer, fp_in[KOKUNEN] , &data_number ) != EOF )
			{
			
			}
			else
			{
				readerror_jisseki( 8 );
			}
		}
	}
	fclose( fp_in[KOKUNEN] );

}


void readerror_jisseki( int i )
{
	cout << "国民年金ファイルの入力中にエラーが発生しました。エラー箇所は " << i << endl;
	exit(1);
}
