#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mcntl.h"
#include "mkisosu.h"
#include "mkiso.h"
#include "mecon.h"
#include "mfile_open.h"


void dtst()
{
	int nendo;
	int c_nendo;
	int nenrei;
	int sotai_nendo;
	int seido;

	FILE *fp_z;
	fp_z = fp_in[zisseki_hosei];
	double buffer[BUFFER_MAX];
	int data_number;

	int hikiage_nendo = 2009;



	Tumatumi_2014[SUM] = 1552833257900;
	Tumatumi[BUNPAI][2015 - TUMATUMI_NENDO] = 159094034794;
	Tumatumi[BUNPAI][2016 - TUMATUMI_NENDO] = 159113373167;
	Tumatumi[BUNPAI][2017 - TUMATUMI_NENDO] = 155730757637;
	Tumatumi[BUNPAI][2018 - TUMATUMI_NENDO] = 155722505415;
	Tumatumi[BUNPAI][2019 - TUMATUMI_NENDO] = 155706999522;
	Tumatumi[BUNPAI][2020 - TUMATUMI_NENDO] = 155691472107;
	Tumatumi[BUNPAI][2021 - TUMATUMI_NENDO] = 155664967139;
	Tumatumi[BUNPAI][2022 - TUMATUMI_NENDO] = 155622975560;
	Tumatumi[BUNPAI][2023 - TUMATUMI_NENDO] = 155499428227;
	Tumatumi[BUNPAI][2024 - TUMATUMI_NENDO] = 155334733769;


	FUKUSHI_NENDO = 2024;
	Fukushi[FUKUSHI_NENDO - 4 - SHONENDO] = 64122425512.;
	Fukushi[FUKUSHI_NENDO - 3 - SHONENDO] = 61434162241.;
	Fukushi[FUKUSHI_NENDO - 2 - SHONENDO] = 55579456448.;
	Fukushi[FUKUSHI_NENDO - 1 - SHONENDO] = 54100000000.;
	Fukushi[FUKUSHI_NENDO - SHONENDO] = 53900000000.;


	Tumitate[2020 - SHONENDO] = 116365. * 100000000;
	Tumitate[2021 - SHONENDO] = 121176. * 100000000;
	Tumitate[2022 - SHONENDO] = 124290. * 100000000;


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		{
			tuki[sotai_nendo] = 4;
		}
	}

	for( nendo = SHONENDO - 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Kokko_Wariai[nendo - ( SHONENDO - 1 )] = 1. / 3. + 25. / 1000.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_MENJO] = 1.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_KASAAGE] = 1. / 4.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_KASAMENJO] = 1.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_SHITASASAE] = 1.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_GONEN] = 1. / 8.;
		Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_20MAE] = 38. / 100.;

		if( nendo >= hikiage_nendo )
		{
			Kokko_Wariai[nendo - ( SHONENDO - 1 )] = 1. / 2.;
			Tokubetu_Kokko_Wariai[nendo - ( SHONENDO - 1 )][TOKUBETU_20MAE] = 2. / 10.;
		}
	}


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		hosei_shin[ROREI][nendo - SHONENDO] = 1.;
		hosei_shin[SHOGAI][nendo - SHONENDO] = 1.;
		hosei_shin[IZOKU][nendo - SHONENDO] = 1.;

		for( seido = SUM ; seido <= SHIGAKU ; seido++ )
		{
			hosei_kyu[seido][nendo - SHONENDO] = 1.;
		}
	}

	read_data( buffer , fp_z , &data_number );
	for( nendo = SHONENDO + 1 ; nendo <= SHONENDO + 6 ; nendo++ )
	{
		if( read_data( buffer , fp_z , &data_number ) != EOF)
		{
			hosei_shin[ROREI][nendo - SHONENDO] = buffer[1];
			hosei_shin[SHOGAI][nendo - SHONENDO] = buffer[2];
			hosei_shin[IZOKU][nendo - SHONENDO] = buffer[3];

			hosei_kyu[KOKUNEN][ nendo - SHONENDO] = buffer[4];
			hosei_kyu[KOUNEN][nendo - SHONENDO] = buffer[5];
		}
	}


	MODEL_PENSION = 133960 / ( 0.994 * 0.996 ) ;
	MODEL_WAGE = 369915;



	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			Cut_ritu[nendo - SHONENDO][nenrei - UNDER_63] = 1.;
		}
	}


	for( c_nendo = ECON_SHONENDO ; c_nendo <= SAISHUNENDO ; c_nendo++ )
	{
		for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM] = 1.;
			}
		}
	}


	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
			kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
			kaiteiritu_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;

			T[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
		}
	}


	return;

}
