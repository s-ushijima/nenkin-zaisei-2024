#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mkisosu.h"
#include "mkisoritu.h"
#include "option.h"

using namespace std;


static int MAX_NENREI[SAISHUNENDO - SHONENDO + 1][MENJO_JOKYO];
static int MAX_NENREI_BEFORE[MENJO_JOKYO] = {70,70,60,60,60,60,60,60,30,60,60};
static int MAX_NENREI_AFTER [MENJO_JOKYO] = {70,70,60,60,60,60,60,60,50,60,60};
static int MAX_NENREI_OP[SAISHUNENDO - SHONENDO + 1][MENJO_JOKYO] = {0};


void noufuritu_3gou_cal( int shubetu );

void noufuritu_1gou_cal();

int noufu_menjo_set( int seibetu , FILE *fp , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

int	noufu_mokuhyo_set( FILE *fp , double noufu_mokuhyo[SAISHUNENDO - SHONENDO + 1] );

int tuinou_set( int seibetu , FILE *fp, 
	double tuinouritu_zisseki[SEIBETU][TUINOU_NENSU_KUBUN][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

int maternity_set( FILE *fp , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

int fuka_set( int shubetu , FILE *fp , int option , 
	double noufuritu_fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

void taishou_hosei_jisseki( int seibetu , int nendo , 
	double taishou_mokuhyo[SEIBETU][SAISHUNENDO - SHONENDO + 1][MENJO_JOKYO] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

void taishou_hosei( int seibetu , int nendo_jisseki , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double taishou_wariai_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double hiho_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

void zengaku_noufu_cal( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

double sankyu_taishou_cal( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

double ikukyu_taishou_cal_f( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double sankyu_mae_taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] ,
	double hiho_ikukyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

double ikukyu_taishou_cal_m( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] ,
	double hiho_ikukyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

void noufu_hosei( int nendo , double noufu_mokuhyo[SAISHUNENDO - SHONENDO + 1] , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double hiho_hosei[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

void noufuritu_hiho_make( int seibetu , 
	double noufuritu_hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] );

double tuinou_make( int seibetu , int nendo , int nenrei , int menjo_jokyo , 
	double tuinouritu_zisseki[SEIBETU][TUINOU_NENSU_KUBUN][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

double noufuritu_cal( int seibetu , int nendo , int nenrei , int noufu_kubun , 
	double noufuritu_hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double tuinouritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

double taishou_wariai_cal( int seibetu , int nendo , int nenrei , int menjo_jokyo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double tuinouritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] );

void fuka_check( int nendo , double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double noufuritu_fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );

int seibetu_to_shubetu_1gou( int seibetu );

void bunpu_data_out( FILE *fp , 
	double Noufuritu[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double Noufuritu_Fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] );


void noufuritu()
{
	int shubetu;
	int nendo;
	int menjo_jokyo;

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( menjo_jokyo = SUM ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( nendo < WAKAMONO_HENKO_NENDO )
			{
				MAX_NENREI[nendo - SHONENDO][menjo_jokyo] = MAX_NENREI_BEFORE[menjo_jokyo];
			}
			else
			{
				MAX_NENREI[nendo - SHONENDO][menjo_jokyo] = MAX_NENREI_AFTER[menjo_jokyo];
			}

			if( menjo_jokyo != SUM && menjo_jokyo != NOUFU && menjo_jokyo != WAKAMONO )
			{
				MAX_NENREI_OP[nendo - SHONENDO][menjo_jokyo]
				= MAX_NENREI[nendo - SHONENDO][menjo_jokyo] + encho_year( nendo );
			}
			else
			{
				MAX_NENREI_OP[nendo - SHONENDO][menjo_jokyo]
				= MAX_NENREI[nendo - SHONENDO][menjo_jokyo];
			}
		}
	}

	noufuritu_3gou_cal( OTOKO_3GOU );
	noufuritu_3gou_cal( ONNA_3GOU );

	noufuritu_1gou_cal();


	return;

}


void noufuritu_3gou_cal( int shubetu )
{
	int nendo;
	int nenrei;
	int menjo_jokyo;
	int MAX_3GOU_NENREI;

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{ 
		MAX_3GOU_NENREI = 60 + encho_year( nendo );

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( menjo_jokyo = SUM ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
			{
				if( nenrei <= MAX_3GOU_NENREI )
				{
					if( menjo_jokyo == NOUFU )
					{
						Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 1.;
					}
					else
					{
						Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
					}
				}
				else
				{
					Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
				}
			}
		}
	}


	return;	

}


void noufuritu_1gou_cal()
{
	using namespace std;

	int nendo;
	int nenrei;
	int seibetu;
	int shubetu;
	int i;
	double d;
	int menjo_jokyo;
	int noufu_kubun;

	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double hiho_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double hiho_jurai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double hiho_jurai_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double jinko[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double jinko_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double sankyu_mae_taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double sankyu_mae_taishou_wariai_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double sankyu_mae_taishou_wariai_shonendo[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] = {0.};
	double noufuritu_shonendo[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] = {0.};
	double noufuritu_hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] = {0.};
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double tuinouritu_zisseki[SEIBETU][TUINOU_NENSU_KUBUN][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double tuinouritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] = {0.};
	double noufu_mokuhyo_saishu[SAISHUNENDO - SHONENDO + 1] = {0.};


	for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
	{
		shubetu = seibetu_to_shubetu_1gou( seibetu );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( menjo_jokyo = SUM ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
				{
					Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
				}

			Noufuritu_Fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = 0.;

			}
		}
	}


	for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
	{
		shubetu = seibetu_to_shubetu_1gou( seibetu );

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			hiho[seibetu][nenrei - MIN_HIHO_NENREI]
			= Sotowaku[shubetu][SUIKEISHONENDO - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI];

			jinko[seibetu][nenrei - MIN_HIHO_NENREI]
			= Sotowaku[shubetu - 1][SUIKEISHONENDO - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI];

			if( Option == 1 )
			{
				hiho_jurai[seibetu][nenrei - MIN_HIHO_NENREI]
				= Sotowaku_Jurai[shubetu][SUIKEISHONENDO - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI];
			}
		}

		noufu_menjo_set( seibetu , fp_in[NOUFU_MENJO_WARIAI] , 
						 noufuritu_shonendo , sankyu_mae_taishou_wariai_shonendo );

		if( shubetu == ONNA_1GOU )
		{
			maternity_set( fp_in[BIRTH] , maternity_ratio );
		}

		tuinou_set( seibetu , fp_in[TUINOU] , tuinouritu_zisseki );

		fuka_set( shubetu , fp_in[FUKANOUFU] , Option , Noufuritu_Fuka );

	}

	noufu_mokuhyo_set( fp_in[MOKUHYOUNOUFUSAISHU] , noufu_mokuhyo_saishu );

	if( Part >= 1 )
	{
		for( nendo = Part_Year ; nendo <= SAISHUNENDO ; nendo++ )
		{
			if( Part == 1 )
			{
				noufu_mokuhyo_saishu[nendo - SHONENDO] += 0.003;
			}
			else if( Part == 2 )
			{
				noufu_mokuhyo_saishu[nendo - SHONENDO] += 0.006;
			}
			else if( Part == 3 )
			{
				noufu_mokuhyo_saishu[nendo - SHONENDO] += 0.011;
			}
			else if( Part == 4 )
			{
				noufu_mokuhyo_saishu[nendo - SHONENDO] += 0.032;
			}
			else if( Part == 5 )
			{
				noufu_mokuhyo_saishu[nendo - SHONENDO] += 0.002;
			}
		}
	}

	for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
		{
			shubetu = seibetu_to_shubetu_1gou( seibetu );

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				hiho_zennen[seibetu][nenrei - MIN_HIHO_NENREI]
				= hiho[seibetu][nenrei - MIN_HIHO_NENREI];

				jinko_zennen[seibetu][nenrei - MIN_HIHO_NENREI]
				= jinko[seibetu][nenrei - MIN_HIHO_NENREI];

				if( nenrei == MIN_HIHO_NENREI )
				{
					hiho[seibetu][nenrei - MIN_HIHO_NENREI]
					= Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] / 2.;
				}
				else
				{
					hiho[seibetu][nenrei - MIN_HIHO_NENREI]
					= ( Sotowaku[shubetu][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
						+ Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 2.;
				}

				jinko[seibetu][nenrei - MIN_HIHO_NENREI]
				= Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI];

				if( Option == 1 )
				{
					hiho_jurai_zennen[seibetu][nenrei - MIN_HIHO_NENREI]
					= hiho_jurai[seibetu][nenrei - MIN_HIHO_NENREI];

					if( nenrei == MIN_HIHO_NENREI )
					{
						hiho_jurai[seibetu][nenrei - MIN_HIHO_NENREI]
						= Sotowaku_Jurai[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] / 2.;
					}
					else
					{
						hiho_jurai[seibetu][nenrei - MIN_HIHO_NENREI]
						= ( Sotowaku_Jurai[shubetu][nendo -1 - SOTOWAKU_SHONENDO][nenrei -1 - MIN_WAKU_NENREI]
							+ Sotowaku_Jurai[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 2.;
					}
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
				{
					sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					= sankyu_mae_taishou_wariai_shonendo[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];

					if( nenrei > MAX_NENREI_OP[nendo - SHONENDO][menjo_jokyo] )
					{
						sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
					}
				}
			}

			if( nendo == WAKAMONO_HENKO_NENDO )
			{
				for( nenrei = MAX_NENREI_BEFORE[WAKAMONO] ; nenrei < MAX_NENREI_AFTER[WAKAMONO] ; nenrei++ )
				{
					sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][WAKAMONO] *= WAKAMONO_HENKO_RITU;
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
				{
					noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
					= noufuritu_shonendo[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun];

					if( nenrei > MAX_NENREI_OP[nendo - SHONENDO][noufu_kubun] )
					{
						noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] = 0.;
					}
				}
			}

		}


		for( seibetu = ONNA ; seibetu >= OTOKO ; seibetu-- )
		{
			shubetu = seibetu_to_shubetu_1gou( seibetu );

			if( Option != 1 )
			{
				if( nendo > NENDO_JISSEKI )
				{
					taishou_hosei( seibetu , nendo , sankyu_mae_taishou_wariai , sankyu_mae_taishou_wariai_zennen ,
								   hiho , hiho_zennen , jinko , jinko_zennen );
				}

				for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
				{
					for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
					{
						sankyu_mae_taishou_wariai_zennen[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						= sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
					}
				}
			}
			else
			{
				if( nendo > NENDO_JISSEKI )
				{
					taishou_hosei( seibetu , nendo , sankyu_mae_taishou_wariai , sankyu_mae_taishou_wariai_zennen ,
								   hiho_jurai , hiho_jurai_zennen , jinko , jinko_zennen );
				}

				for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
				{
					for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
					{
						sankyu_mae_taishou_wariai_zennen[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						= sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
					}
				}

				for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
				{
					for( menjo_jokyo = MENJO_3_4 ; menjo_jokyo <= GAKUSEI ; menjo_jokyo++ )
					{
						if( extendc( nendo , nenrei ) == 1 )
						{
							sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
							= sankyu_mae_taishou_wariai[seibetu][MAX_KYOSHUTU_NENREI - MIN_HIHO_NENREI][menjo_jokyo];
						}

						if( extendb( nendo , nenrei ) == 1 )
						{
							d = 0.;
							for( i = MAX_KYOSHUTU_NENREI - 5 ; i < MAX_KYOSHUTU_NENREI ; i++ )
							{
								d += sankyu_mae_taishou_wariai[seibetu][i - MIN_HIHO_NENREI][menjo_jokyo];
							}
							d /= 5.;

							sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = d;
						}
					}
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( menjo_jokyo = SUM ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
				{
					taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					= sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
				}
			}

			if( shubetu == 5 )
			{
				Hiho_Sankyu_Sum[nendo - SHONENDO]
				= sankyu_taishou_cal( seibetu , nendo , taishou_wariai , maternity_ratio , hiho );

				if( nendo >= IKUKYU_HENKO_NENDO )
				{
					Hiho_Ikukyu_Sum[nendo - SHONENDO]
					= ikukyu_taishou_cal_f( seibetu , nendo , taishou_wariai , sankyu_mae_taishou_wariai , 
											maternity_ratio , hiho , Hiho_Ikukyu );
				}
			}

			if( shubetu == 2 && nendo >= IKUKYU_HENKO_NENDO )
			{
				Hiho_Ikukyu_Sum[nendo - SHONENDO]
				+= ikukyu_taishou_cal_m( seibetu , nendo , taishou_wariai , hiho , Hiho_Ikukyu );
			}

		}


		if( Option != 1 )
		{
			noufu_hosei( nendo , noufu_mokuhyo_saishu , noufuritu , taishou_wariai , hiho , hiho );
		}
		else
		{
			noufu_hosei( nendo , noufu_mokuhyo_saishu , noufuritu , taishou_wariai , hiho , hiho_jurai );

			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				shubetu = seibetu_to_shubetu_1gou( seibetu );

				for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
				{
					for( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
					{
						if( extendc( nendo , nenrei ) == 1 )
						{
							noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
							= noufuritu[seibetu][MAX_KYOSHUTU_NENREI - MIN_HIHO_NENREI][noufu_kubun];
						}

						if( extendb( nendo , nenrei ) == 1 )
						{
							d = 0.;
							for( i = MAX_KYOSHUTU_NENREI - 5 ; i < MAX_KYOSHUTU_NENREI ; i++ )
							{
								d += noufuritu[seibetu][i - MIN_HIHO_NENREI][noufu_kubun];
							}
							d /= 5.;

							noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] = d;
						}

					}
				}
			}
		}

		if( Option == 1 )
		{
			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				zengaku_noufu_cal( seibetu , nendo , taishou_wariai );
			}
		}

		fuka_check( nendo , noufuritu , taishou_wariai , Noufuritu_Fuka );

		for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
		{
			shubetu = seibetu_to_shubetu_1gou( seibetu );

			noufuritu_hiho_make( seibetu , noufuritu_hiho , taishou_wariai , noufuritu );

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
				{
					tuinouritu[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					= tuinou_make( seibetu , nendo , nenrei , menjo_jokyo , tuinouritu_zisseki , taishou_wariai );
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				for( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
				{
					Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][noufu_kubun]
					= noufuritu_cal( seibetu , nendo , nenrei , noufu_kubun , noufuritu_hiho , taishou_wariai , 
									 tuinouritu );
				}

				for( menjo_jokyo = NOUFU_KUBUN ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
				{
					Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo] 
					= taishou_wariai_cal( seibetu , nendo , nenrei , menjo_jokyo , taishou_wariai , tuinouritu );
				}
			}

		}

	}

	bunpu_data_out( fp_out[BUNPU] , Noufuritu , Noufuritu_Fuka );


	return;

}


int noufu_menjo_set( int seibetu , FILE *fp , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int shubetu;
	int nenrei;
	int noufu_kubun;
	int menjo_jokyo;
	int data_number;
	double buffer[BUFFER_MAX];
	int SKIP_ROW = 2;
	int NOUFURITU_COLUMN = 1;
	int TAISHOU_COLUMN = 5;


	shubetu = seibetu_to_shubetu_1gou( seibetu );

	if( shubetu == OTOKO_1GOU )
	{
		data_skip( fp , SKIP_ROW );
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		buffer_set2( buffer , fp , &data_number , shubetu , nenrei , "年齢別納付率・対象割合" );

		for( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
		{
			noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
			= buffer[NOUFURITU_COLUMN + noufu_kubun];
		}

		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo == IKUKYU )
			{
				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
			}
			else
			{
				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				= buffer[TAISHOU_COLUMN + menjo_jokyo];
			}
		}
	}


	return 0;

}


int noufu_mokuhyo_set( FILE *fp , double noufu_mokuhyo[SAISHUNENDO - SHONENDO + 1] )
{

	int nendo;
	int data_number;
	double buffer[BUFFER_MAX];

	int SKIP_ROW = 1;
	int MOKUHYO_COLUMN = 1;


	data_skip( fp , SKIP_ROW );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		buffer_set1( buffer , fp , &data_number , nendo , "目標納付率");
		noufu_mokuhyo[nendo - SHONENDO] = buffer[MOKUHYO_COLUMN];
	}


	return 0;

}


int tuinou_set(int seibetu , FILE *fp ,
	double tuinouritu_zisseki[SEIBETU][TUINOU_NENSU_KUBUN][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int shubetu;
	int nenrei;
	int menjo_jokyo;
	int data_number;
	int counter;
	double buffer[BUFFER_MAX];
	int SKIP_ROW = 2;

	shubetu = seibetu_to_shubetu_1gou( seibetu );

	if( shubetu == OTOKO_1GOU )
	{
		data_skip( fp , SKIP_ROW );
	}


	buffer_set1( buffer , fp , &data_number , shubetu , "追納率" );

	for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
	{
		for( counter = 1 ; counter <= 2 ; counter ++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				if( menjo_jokyo == IKUKYU )
				{
					tuinouritu_zisseki[seibetu][counter][nenrei - MIN_HIHO_NENREI][menjo_jokyo] = 0.;
				}
				else
				{
					tuinouritu_zisseki[seibetu][counter][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					= buffer[( menjo_jokyo - 1 ) * 2 + counter];
				}
			}
		}
	}


	return 0;

}


int taishou_mokuhyo_set( int seibetu , FILE *fp , 
	double taishou_mokuhyo[SEIBETU][SAISHUNENDO - SHONENDO + 1][MENJO_JOKYO] )
{
	int shubetu;
	int nendo;
	int menjo_jokyo;
	int data_number;
	double buffer[BUFFER_MAX];

	int SKIP_ROW = 1;


	shubetu = seibetu_to_shubetu_1gou( seibetu );

	if( shubetu == OTOKO_1GOU )
	{
		data_skip( fp , SKIP_ROW );
	}

	for( nendo = SUIKEISHONENDO ; nendo <= NENDO_JISSEKI ; nendo++ )
	{
		buffer_set2( buffer , fp , &data_number , shubetu , nendo , "足下の免除状況別対象者数" ); 

		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != NOUFU && menjo_jokyo != IKUKYU )
			{
				taishou_mokuhyo[seibetu][nendo - SHONENDO][menjo_jokyo] = buffer[menjo_jokyo + 1];
			}
		}
	}


	return 0;

}


int maternity_set( FILE *fp , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int nendo;
	int nenrei;
	int menjo_jokyo;
	int data_number;
	double buffer[BUFFER_MAX];
	double birth_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	int SKIP_ROW = 2;
	int MIN_BIRTH_NENREI = 15;
	int MAX_BIRTH_NENREI = 50;

	double hosei[MENJO_JOKYO] = { 0. , 1. , 1. , 1. , 1. , 1. , 1. , 0. , 1. , 0. , 0. };

	data_skip( fp, SKIP_ROW );

	for( nenrei = MIN_BIRTH_NENREI ; nenrei < MAX_BIRTH_NENREI ; nenrei++ )
	{
		buffer_set1( buffer , fp , &data_number , nenrei , "出生率" );

		if( nenrei >= (int) max( MIN_HIHO_NENREI , MIN_BIRTH_NENREI ) && 
			nenrei <  (int) min( MAX_HIHO_NENREI , MAX_BIRTH_NENREI ) )
		{
			for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				birth_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[nendo - SHONENDO + 1];
				birth_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] *= 2. / 3.;
			}
		}
	}

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei < MAX_HIHO_NENREI ; nenrei++ )
		{
			for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
			{
				maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				= birth_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] * hosei[menjo_jokyo];
			}
		}
	}


	return 0;

}


int fuka_set( int shubetu , FILE *fp , int option , 
	double noufuritu_fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nendo;
	int nenrei;
	int data_number;
	double buffer[BUFFER_MAX];
	int i;
	double d;

	int SKIP_ROW = 1;

	if( shubetu == 2 )
	{
		data_skip( fp, SKIP_ROW );
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		buffer_set2( buffer , fp , &data_number , shubetu , nenrei , "付加年金納付率" ); 
		noufuritu_fuka[shubetu][SHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
	}

	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			noufuritu_fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
			= noufuritu_fuka[shubetu][SHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI];
		}
	}

	if( option == 1 )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
			{
				if( extendc( nendo , nenrei ) == 1 )
				{
					Noufuritu_Fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
					= Noufuritu_Fuka[shubetu][nendo - SHONENDO][MAX_KYOSHUTU_NENREI - MIN_HIHO_NENREI];
				}

				if( extendb( nendo , nenrei ) == 1 )
				{
					d = 0.;
					for( i = MAX_KYOSHUTU_NENREI - 5 ; i < MAX_KYOSHUTU_NENREI ; i++ )
					{
						d += Noufuritu_Fuka[shubetu][nendo - SHONENDO][i - MIN_HIHO_NENREI];
					}
					d /= 5.;

					Noufuritu_Fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = d;
				}
			}
		}
	}


	return 0;

}


void taishou_hosei_jisseki( int seibetu , int nendo , 
	double taishou_mokuhyo[SEIBETU][SAISHUNENDO - SHONENDO + 1][MENJO_JOKYO] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nenrei;
	int menjo_jokyo;
	double mokuhyo;
	double gokei;
	double non_gokei;


	for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
	{
		if( menjo_jokyo != NOUFU && menjo_jokyo != IKUKYU )
		{
			mokuhyo = taishou_mokuhyo[seibetu][nendo - SHONENDO][menjo_jokyo];

			gokei = 0.;
			non_gokei = 0.;
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI[nendo - SHONENDO][menjo_jokyo] ; nenrei++ )
			{
				gokei += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						 * hiho[seibetu][nenrei - MIN_HIHO_NENREI];
				non_gokei += ( 1.0 - taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] )
							* hiho[seibetu][nenrei - MIN_HIHO_NENREI];
			}

			if( menjo_jokyo == GAKUSEI )
			{
				for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI[nendo - SHONENDO][menjo_jokyo] ; nenrei++ )
				{
					taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] *= fdiv( mokuhyo , gokei );
				}
			}
			else
			{
				if( mokuhyo <= gokei )
				{
					for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI[nendo - SHONENDO][menjo_jokyo] ; nenrei++ )
					{
						taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] *= fdiv( mokuhyo , gokei );
					}
				}
				else
				{
					for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI[nendo - SHONENDO][menjo_jokyo] ; nenrei++ )
					{
						taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						+= ( 1.0 - taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] )
						  * fdiv( mokuhyo - gokei , non_gokei );
					}
				}
			}
		}
	}

	zengaku_noufu_cal( seibetu , nendo , taishou_wariai );


	return;

}


void taishou_hosei( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double taishou_wariai_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double hiho_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double jinko_zennen[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nenrei;
	int menjo_jokyo;
	double menjo_sum;
	double r;


	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo == MENJO_HOUTEI || 
				( menjo_jokyo == GAKUSEI && ( Part != 4 || nendo < Part_Year || nendo > Part_Year + 1 ) ) )
			{
				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] 
				= taishou_wariai_zennen[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				  * hiho_zennen[seibetu][nenrei - MIN_HIHO_NENREI] 
				  * fdiv( jinko[seibetu][nenrei - MIN_HIHO_NENREI] , 
						  jinko_zennen[seibetu][nenrei - MIN_HIHO_NENREI] );

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				*= fdiv( 1.0 , hiho[seibetu][nenrei - MIN_HIHO_NENREI] );
			}
			else if( menjo_jokyo != NOUFU )
			{
				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				= taishou_wariai_zennen[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
			}
		}

		menjo_sum = 0.;
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != NOUFU )
			{
				menjo_sum += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
			}
		}

		if( menjo_sum > 1. )
		{
			printf ( "免除割合が１を超えています：性別%d, 年度%d, 年齢%d\n", seibetu , nendo , nenrei );

			r = ( menjo_sum - 1. + EPSILON ) 
				/ ( taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI]
					+ taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][GAKUSEI] );

			taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI] *= 1 - r;
			taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][GAKUSEI] *= 1 - r;
		}
	}

	zengaku_noufu_cal( seibetu , nendo , taishou_wariai );


	return;

}


void zengaku_noufu_cal( int seibetu , int nendo ,
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int shubetu;
	int nenrei;
	int menjo_jokyo;


	shubetu = seibetu_to_shubetu_1gou( seibetu );

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][NOUFU] = 1.;

		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != NOUFU )
			{
				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][NOUFU]
				-= taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
			}
		}

		if( taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][NOUFU] < 0. )
		{
			printf ( "種別%d, 年度%d, 年齢%dの全額納付対象割合がマイナスです\n", shubetu , nendo , nenrei );
			exit(1);
		}

	}


	return;

}


double sankyu_taishou_cal( int seibetu , int nendo ,
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nenrei;
	int menjo_jokyo;
	double sankyu_ninzu = 0.;


	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
			{
				sankyu_ninzu += hiho[seibetu][nenrei - MIN_HIHO_NENREI] 
						* taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						* maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
						* 1. / 3.;

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][SANKYU] 
					+= taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					 * maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					 * 1. / 3.;

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo] 
					-= taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					 * maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					 * 1. / 3.;
			}
		}
	}


	return sankyu_ninzu;

}


double ikukyu_taishou_cal_f( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double sankyu_mae_taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double maternity_ratio[SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] ,
	double hiho_ikukyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nenrei;
	int menjo_jokyo;
	double ikukyu_ninzu = 0.;
	double eikyo_ritu;


	if( nendo == IKUKYU_HENKO_NENDO )
	{
		eikyo_ritu = IKUKYU_HENKO_RITU;
	}
	else
	{
		eikyo_ritu = 1.;
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		hiho_ikukyu[nenrei - MIN_HIHO_NENREI] = 0.;
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
			{
				hiho_ikukyu[nenrei - MIN_HIHO_NENREI]
				 += hiho[seibetu][nenrei - MIN_HIHO_NENREI]
					* sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					* maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
					* 3. / 4. * eikyo_ritu;

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][IKUKYU]
				 += sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * 3. / 4. * eikyo_ritu;

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				 -= sankyu_mae_taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * maternity_ratio[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * 3. / 4. * eikyo_ritu;
			}
		}

		ikukyu_ninzu += hiho_ikukyu[nenrei - MIN_HIHO_NENREI];
	}


	return ikukyu_ninzu;

}


double ikukyu_taishou_cal_m( int seibetu , int nendo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] ,
	double hiho_ikukyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int nenrei;
	int menjo_jokyo;
	double ikukyu_ninzu = 0.;
	double hiho_ninzu;
	double ratio;

	double hosei[MENJO_JOKYO] = { 0. , 1. , 1. , 1. , 1. , 1./4., 1. , 0. , 1. , 0. , 0. };

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		hiho_ninzu = 0.;
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
			{
				hiho_ninzu += hiho[seibetu][nenrei - MIN_HIHO_NENREI]
							* taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
							* hosei[menjo_jokyo];
			}
		}
		ratio = hiho_ikukyu[nenrei - MIN_HIHO_NENREI] * 4. / 3.;
		ratio /= hiho_ninzu;

		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
			{
				ikukyu_ninzu += hiho[seibetu][nenrei - MIN_HIHO_NENREI]
								* taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
								* ratio * hosei[menjo_jokyo];

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][IKUKYU]
				 += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * ratio * hosei[menjo_jokyo];

				taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				 -= taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo]
				    * ratio * hosei[menjo_jokyo];
			}
		}
	}


	return ikukyu_ninzu;

}


void noufu_hosei( int nendo , double noufu_mokuhyo[SAISHUNENDO - SHONENDO + 1] , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] ,
	double hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] , 
	double hiho_hosei[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int seibetu;
	int nenrei;
	int noufu_kubun;
	double mokuhyo;
	double gokei;
	double non_gokei;
	double hikiageritu;
	double ninzu;
	double noufu_taishou;
	double noufusha[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] = {0.};
	double noufu_taishousha[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] = {0.};


	mokuhyo = 0.;
	gokei = 0.;
	non_gokei = 0.;
	noufu_taishou = 0.;

	for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
	{
		for ( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI[nendo - SHONENDO][noufu_kubun] ; nenrei++ )
			{
				noufu_taishou += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
								 * hiho_hosei[seibetu][nenrei - MIN_HIHO_NENREI];

				gokei += noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
						 * taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
						 * hiho_hosei[seibetu][nenrei - MIN_HIHO_NENREI];

				non_gokei += (1.0 - noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] )
							 * taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
							 * hiho_hosei[seibetu][nenrei - MIN_HIHO_NENREI];
			}
		}
	}

	mokuhyo = noufu_mokuhyo[nendo - SHONENDO] * noufu_taishou;


	if ( mokuhyo <= gokei )
	{
		for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
		{
			for ( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
			{
				for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI_OP[nendo - SHONENDO][noufu_kubun] ; nenrei++ )
				{
					noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] *= fdiv( mokuhyo , gokei );
				}
			}
		}
	}
	else
	{
		hikiageritu = fdiv( mokuhyo - gokei , non_gokei );

		for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
		{
			for ( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
			{
				for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_NENREI_OP[nendo - SHONENDO][noufu_kubun] ; nenrei++ )
				{
					ninzu = hiho[seibetu][nenrei - MIN_HIHO_NENREI]
							* taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
							* noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
						    + hiho[seibetu][nenrei - MIN_HIHO_NENREI]
							  * taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
							  * ( 1.0 - noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] )
							  * hikiageritu;

					noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
					= fdiv( ninzu , hiho[seibetu][nenrei - MIN_HIHO_NENREI]
									* taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun] );
				}
			}
		}
	}


	return;

}


void fuka_check( int nendo , double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double noufuritu_fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	int seibetu;
	int shubetu;
	int nenrei;
	double noufu;


	for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
	{
		shubetu = seibetu_to_shubetu_1gou( seibetu );

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			noufu = taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][NOUFU]
					* noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][NOUFU];

			noufu += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][SANKYU];
			noufu += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][IKUKYU];

			if( noufu < noufuritu_fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] )
			{
				printf( "付加納付率が上限を超えたため補正：性別%d, 年度%d, 年齢%d\n" , seibetu , nendo , nenrei );
				noufuritu_fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = noufu;
			}
		}
	}


	return;

}


void noufuritu_hiho_make( int seibetu , 
	double noufuritu_hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double noufuritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] )
{
	int nenrei;
	int noufu_kubun;


	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( noufu_kubun = START ; noufu_kubun < NOUFU_KUBUN ; noufu_kubun++ )
		{
			noufuritu_hiho[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
			 = taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun]
				* noufuritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun];

			noufuritu_hiho[seibetu][nenrei - MIN_HIHO_NENREI][SUM]
			 += noufuritu_hiho[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun];
		}
	}


	return;

}


double tuinou_make( int seibetu , int nendo , int nenrei , int menjo_jokyo , 
	double tuinouritu_zisseki[SEIBETU][TUINOU_NENSU_KUBUN][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int counter;
	int tuinou_kubun;
	double value = 0.;

	if( menjo_jokyo != NOUFU && menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
	{
		for( counter = 0 ; counter <= TUINOU_NENSU ; counter++ )
		{
			tuinou_kubun = ( counter == 0 ) ? 1 : 2;

			value += tuinouritu_zisseki[seibetu][tuinou_kubun][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
		}

		value *= taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
	}


	return value;

}


double noufuritu_cal( int seibetu , int nendo , int nenrei , int noufu_kubun , 
	double noufuritu_hiho[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][NOUFU_KUBUN] , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double tuinouritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	int menjo_jokyo;
	double value=0.;


	if( noufu_kubun >= NOUFU_KUBUN )
	{
		printf( "noufuiritu_calは保険料納付のある区分が計算対象です：noufu_kubun=%d\n", noufu_kubun );
		exit(1);
	}


	value = noufuritu_hiho[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun];


	if( noufu_kubun == NOUFU )
	{
		for( menjo_jokyo = START ; menjo_jokyo < MENJO_JOKYO ; menjo_jokyo++ )
		{
			if( menjo_jokyo != NOUFU && menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
			{
				value += tuinouritu[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
			}
		}

		value += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][SANKYU];

		if( nendo >= IKUKYU_HENKO_NENDO )
		{
			value += taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][IKUKYU];
		}

	}
	else
	{
		value -= tuinouritu[seibetu][nenrei - MIN_HIHO_NENREI][noufu_kubun];
	}


	return value;

}


double taishou_wariai_cal( int seibetu , int nendo, int nenrei , int menjo_jokyo , 
	double taishou_wariai[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double tuinouritu[SEIBETU][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] )
{
	double value = 0.;


	if( menjo_jokyo < NOUFU_KUBUN || menjo_jokyo >= MENJO_JOKYO )
	{
		printf( "taishou_wariai_calは保険料納付のない区分が計算対象です：menjo_jokyo=%d\n", menjo_jokyo );
		exit(1);
	}


	value = taishou_wariai[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];

	if( menjo_jokyo != SANKYU && menjo_jokyo != IKUKYU )
	{
		value -= tuinouritu[seibetu][nenrei - MIN_HIHO_NENREI][menjo_jokyo];
	}


	return value;

}


int seibetu_to_shubetu_1gou( int seibetu )
{
	int value;

	if( seibetu == OTOKO )
	{
		value = OTOKO_1GOU;
	}
	else if( seibetu == ONNA )
	{
		value = ONNA_1GOU;
	}
	else
	{
		printf( "性別が範囲外です：seibetu=%d\n", seibetu );
		exit(1);
	}

	return value;

}


void bunpu_data_out( FILE *fp , 
	double Noufuritu[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MENJO_JOKYO] , 
	double Noufuritu_Fuka[MAX_SHUBETU][SAISHUNENDO - SHONENDO + 1][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] )
{
	const char *hyoto[] = {
		"性","年度","年齢",
		"11","12","13","14","15","16","17","18","19","20"
	};

	int i;
	int seibetu;
	int shubetu;
	int nendo;
	int nenrei;
	int hyoto_num;


	hyoto_num = ( sizeof hyoto ) / ( sizeof hyoto[0] );

	for( i = 0 ; i < hyoto_num - 1 ; i++ )
	{
		fprintf( fp , "%s,", hyoto[i] );
	}
	fprintf( fp , "%s\n", hyoto[hyoto_num - 1] );

	for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
	{
		shubetu = seibetu_to_shubetu_1gou( seibetu );

		for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				fprintf( fp , "%d, %d, %d", seibetu , nendo , nenrei );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][NOUFU]
						 - Noufuritu_Fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu_Fuka[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_SHINSEI] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_3_4] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_1_2] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_1_4] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][GAKUSEI] );

				fprintf( fp , ", %11.9e", 
						 Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][WAKAMONO] );

				fprintf( fp , ", %11.9e", 
						 1. - Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][NOUFU]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_SHINSEI]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_3_4]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_1_2]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][MENJO_1_4]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][GAKUSEI]
							- Noufuritu[shubetu][nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][WAKAMONO] );

				fprintf( fp , "\n" );
			}
		}
	}


	return;

}
