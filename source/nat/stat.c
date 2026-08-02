#include <stdio.h>
#include <iostream>
#include <cstring>
#include "snaps.h"
#include "mkisosu.h"
#include "mkisoritu.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "mseid.h"
#include "option.h"


int Hanbetu( int shubetu );


void stat()
{
	int nendo;
	int sotai_nendo;
	int jukyu_nenrei;
	int dankai;
	int nenrei;
	int shubetu;
	int counter;
	double OutputValue;

	double Rorei_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Rorei_Kyu_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Turo_Kyu_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Gonen_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Shogai_Ippan_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Shogai_20mae_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Shogai_Kyu_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Izoku_Tuma_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Izoku_Otto_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1][2];
	double Izoku_Ko_Jukyu_Nendokan[2][SAISHUNENDO - SHONENDO + 1];

	char Shisan_Naiyou[1000];
	char NaiyouSaibou[100];

	double Rorei_kiso_bunseki[SAISHUNENDO - SHONENDO + 1][2]={0};
	double Shogai_kiso_bunseki[SAISHUNENDO - SHONENDO + 1][2][2]={0};
	double Izoku_kiso_bunseki[SAISHUNENDO - SHONENDO + 1][2][2]={0};
	int seibetu;
	int kubun;


	for( shubetu = 0 ; shubetu <= 1 ; shubetu++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			
			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				Rorei_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Rorei_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Turo_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Gonen_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Shogai_Ippan_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Shogai_20mae_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Shogai_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Izoku_Tuma_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
				Izoku_Otto_Jukyu_Nendokan[shubetu][sotai_nendo][counter] = 0.;
			}
			Izoku_Ko_Jukyu_Nendokan[shubetu][sotai_nendo] = 0.;
		}
	}


	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		if( shubetu == 2 || shubetu == 3 || shubetu == 5 || shubetu == 6 )
		{
			for( nendo = SUIKEISAISHUNENDO ; nendo >= SUIKEISHONENDO + 1 ; nendo-- )
			{
				sotai_nendo = nendo - SHONENDO;

				Hiho_Kei[shubetu][sotai_nendo][HIHO_NENREI_SUM]
				 = ( Hiho_Kei[shubetu][sotai_nendo - 1][HIHO_NENREI_SUM]
				      + Hiho_Kei[shubetu][sotai_nendo][HIHO_NENREI_SUM] ) / 2.;

				Hiho_Noufu[shubetu][sotai_nendo][HIHO_NENREI_SUM]
				 = ( Hiho_Noufu_P[shubetu][sotai_nendo - 1][HIHO_NENREI_SUM]
				      + Hiho_Noufu[shubetu][sotai_nendo][HIHO_NENREI_SUM] ) / 2.;

				for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
				{
					Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][dankai]
					 = ( Hiho_Menjo_P[shubetu][sotai_nendo - 1][HIHO_NENREI_SUM][dankai]
					      + Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][dankai] ) / 2.;
				}

				Fuka_Hiho[shubetu][sotai_nendo][HIHO_NENREI_SUM]
				 = ( Fuka_Hiho_P[shubetu][sotai_nendo - 1][HIHO_NENREI_SUM]
				      + Fuka_Hiho[shubetu][sotai_nendo][HIHO_NENREI_SUM] ) / 2.;
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;

				for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
				{
					for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
					{
						Rorei[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Turo_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Turo_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Gonen[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Gonen[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Turo_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Turo_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Gonen[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Gonen[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
							Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );
					}
				}

				for( nenrei = UNDER_63 ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
				{
					Shogai_Ippan[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM]
					 = add( Shogai_Ippan[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM] , 
						Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Shogai_20mae[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM]
					 = add( Shogai_20mae[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM] , 
						Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Shogai_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM]
					 = add( Shogai_Kyu[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM] , 
						Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Shogai_Ippan[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Ippan[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Shogai_20mae[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_20mae[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Shogai_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				for( nenrei = UNDER_63 ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
				{
					Izoku_Tuma[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM]
					 = add( Izoku_Tuma[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM] , 
						Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Izoku_Tuma[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Tuma[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				for( nenrei = UNDER_63 ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
				{
					Izoku_Otto[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM]
					 = add( Izoku_Otto[Hanbetu( shubetu )][sotai_nendo][nenrei - NENREI_SUM] , 
						Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Izoku_Otto[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Otto[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				Izoku_Ko[Hanbetu( shubetu )][sotai_nendo]
				 = add( Izoku_Ko[Hanbetu( shubetu )][sotai_nendo] , Izoku_Ko[shubetu][sotai_nendo] );

				Izoku_Ko[SHUBETU_SUM][sotai_nendo]
				 = add( Izoku_Ko[SHUBETU_SUM][sotai_nendo] , Izoku_Ko[shubetu][sotai_nendo] );

				Kafu[SHUBETU_SUM][sotai_nendo]
				 = add( Kafu[SHUBETU_SUM][sotai_nendo] , Kafu[shubetu][sotai_nendo] );

				Kafu_Kyu[SHUBETU_SUM][sotai_nendo]
				 = add( Kafu_Kyu[SHUBETU_SUM][sotai_nendo] , Kafu_Kyu[shubetu][sotai_nendo] );

				for( nenrei = UNDER_63 ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
				{
					Ichijikin[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Ichijikin[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM] , 
						Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					if( nendo == SUIKEISHONENDO + 1 )
					{
						Ichijikin[SHUBETU_SUM][1][NENREI_SUM - NENREI_SUM]
						 = Ichijikin[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM];
					}
				}
			}
		}
	}

	for( shubetu = 0 ; shubetu <= 1 ; shubetu++ )
	{
		for( nendo = SAISHUNENDO ; nendo >= SUIKEISHONENDO ; nendo-- )
		{
			sotai_nendo = nendo - SHONENDO;
			for( nenrei = UNDER_64 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				if ( nenrei == UNDER_64 )
				{
					for ( counter = 0 ; counter <= 1 ; counter++ )
					{
						for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++)
						{
							Rorei_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
							 += Rorei[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

							Rorei_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
							 += Rorei_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Rorei_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

							Turo_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
							 += Turo_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Turo_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Turo_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Turo_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

							Gonen_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
							 += Gonen[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Gonen[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Gonen[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
								 + Gonen[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM]
									[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;
						}

						Shogai_Ippan_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
						 += Shogai_Ippan[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_Ippan[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_Ippan[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu
							 + Shogai_Ippan[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu;

						Shogai_20mae_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
						 += Shogai_20mae[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_20mae[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_20mae[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu
							 + Shogai_20mae[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu;

						Shogai_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
						 += Shogai_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Shogai_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu
							 + Shogai_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu;

						Izoku_Tuma_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
						 += Izoku_Tuma[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Izoku_Tuma[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Izoku_Tuma[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu
							 + Izoku_Tuma[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu;

						Izoku_Otto_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
						 += Izoku_Otto[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Izoku_Otto[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu
							 + Izoku_Otto[shubetu * 3 + 2][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu
							 + Izoku_Otto[shubetu * 3 + 3][sotai_nendo][nenrei - 1 - NENREI_SUM].ninzu;
					}

					Izoku_Ko_Jukyu_Nendokan[shubetu][sotai_nendo]
					 += Izoku_Ko[shubetu * 3 + 2][sotai_nendo].ninzu
						 + Izoku_Ko[shubetu * 3 + 3][sotai_nendo].ninzu;
				}
				else
				{
					for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
					{
						Rorei_Jukyu_Nendokan[shubetu][sotai_nendo][0]
						 += Rorei[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
							 + Rorei[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

						Rorei_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][0]
						 += Rorei_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
							 + Rorei_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

						Turo_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][0]
						 += Turo_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
							 + Turo_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;

						Gonen_Jukyu_Nendokan[shubetu][sotai_nendo][0]
						 += Gonen[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
							 + Gonen[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM]
								[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu;
					}

					Shogai_Ippan_Jukyu_Nendokan[shubetu][sotai_nendo][0]
					 += Shogai_Ippan[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
						 + Shogai_Ippan[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu;

					Shogai_20mae_Jukyu_Nendokan[shubetu][sotai_nendo][0]
					 += Shogai_20mae[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
						 + Shogai_20mae[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu;

					Shogai_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][0]
					 += Shogai_Kyu[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
						 + Shogai_Kyu[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu;

					Izoku_Tuma_Jukyu_Nendokan[shubetu][sotai_nendo][0]
					 += Izoku_Tuma[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
						 + Izoku_Tuma[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu;

					Izoku_Otto_Jukyu_Nendokan[shubetu][sotai_nendo][0]
					 += Izoku_Otto[shubetu * 3 + 2][sotai_nendo][nenrei - NENREI_SUM].ninzu
						 + Izoku_Otto[shubetu * 3 + 3][sotai_nendo][nenrei - NENREI_SUM].ninzu;
				}
			}
		}
	}

	sprintf( Shisan_Naiyou , "\0" );

	sprintf( NaiyouSaibou , "Kisai_Shitasasae , %f\n" , Kisai_Shitasasae );
	strcat( Shisan_Naiyou , NaiyouSaibou );
	sprintf( NaiyouSaibou , "HenkouSeinendo , %d\n" , HenkouSeinendo );
	strcat( Shisan_Naiyou , NaiyouSaibou );
	sprintf( NaiyouSaibou , "Kako_Saimu , %d\n" , Kako_Saimu );
	strcat( Shisan_Naiyou , NaiyouSaibou );
	sprintf( NaiyouSaibou , "Kugiri_Nendo , %d\n" , Kugiri_Nendo );
	strcat( Shisan_Naiyou , NaiyouSaibou );
	sprintf( NaiyouSaibou , "Jyukyusha_Nomi , %d\n" , Jyukyusha_Nomi );
	strcat( Shisan_Naiyou , NaiyouSaibou );

	for( seibetu = 0 ; seibetu < 2 ; seibetu++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				sotai_nendo = nendo - SHONENDO;

				Rorei_kiso_bunseki[sotai_nendo][seibetu]
				 += Rorei[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
						[nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu;

				Rorei_kiso_bunseki[sotai_nendo][seibetu]
				 += Rorei[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
						[nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][1];

				Rorei_kiso_bunseki[sotai_nendo][seibetu]
				 += Rorei[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
						[nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae;

				Rorei_kiso_bunseki[sotai_nendo][seibetu]
				 += Rorei[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
						[nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][2];
			}
		}
	}

	for( seibetu = 0 ; seibetu < 2 ; seibetu++ )
	{
		for( kubun = 0 ; kubun < 2 ; kubun++ )
		{
			for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
				{
					sotai_nendo = nendo - SHONENDO;

					if( kubun == 0 )
					{
						Shogai_kiso_bunseki[sotai_nendo][seibetu][kubun]
						 += Shogai_Ippan[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
								[nenrei - NENREI_SUM].kihon;

						Shogai_kiso_bunseki[sotai_nendo][seibetu][kubun]
						 += Shogai_20mae[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
								[nenrei - NENREI_SUM].kihon;
					}
					else
					{
						Shogai_kiso_bunseki[sotai_nendo][seibetu][kubun]
						 += Shogai_Ippan[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
								[nenrei - NENREI_SUM].kakyu;

						Shogai_kiso_bunseki[sotai_nendo][seibetu][kubun]
						 += Shogai_20mae[(seibetu == 0 ? SHUBETU_OTOKO : SHUBETU_ONNA)][sotai_nendo]
								[nenrei - NENREI_SUM].kakyu;
					}
				}
			}
		}
	}

	for( seibetu = 0 ; seibetu < 2 ; seibetu++ )
	{
		for( kubun = 0 ; kubun < 2 ; kubun++ )
		{
			for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
				{
					sotai_nendo = nendo - SHONENDO;

					if( kubun == 0 )
					{
						if( seibetu == 0 )
						{
							Izoku_kiso_bunseki[sotai_nendo][0][kubun]
							 += Izoku_Otto[SHUBETU_ONNA][sotai_nendo][nenrei - NENREI_SUM].kihon;

							Izoku_kiso_bunseki[sotai_nendo][0][kubun]
							 += ( nenrei == UNDER_63 ? Izoku_Ko[SHUBETU_OTOKO][sotai_nendo].kihon : 0. );
						}
						if( seibetu == 1 )
						{
							Izoku_kiso_bunseki[sotai_nendo][1][kubun]
							 += Izoku_Tuma[SHUBETU_OTOKO][sotai_nendo][nenrei - NENREI_SUM].kihon;
						}
					}
					else
					{
						if( seibetu == 0 )
						{
							Izoku_kiso_bunseki[sotai_nendo][0][kubun]
							 += Izoku_Otto[SHUBETU_ONNA][sotai_nendo][nenrei - NENREI_SUM].kakyu;

							Izoku_kiso_bunseki[sotai_nendo][0][kubun]
							 += ( nenrei == UNDER_63 ? Izoku_Ko[SHUBETU_OTOKO][sotai_nendo].kakyu : 0. );
						}
						if( seibetu == 1 )
						{
							Izoku_kiso_bunseki[sotai_nendo][1][kubun]
							 += Izoku_Tuma[SHUBETU_OTOKO][sotai_nendo][nenrei - NENREI_SUM].kakyu;
						}
					}
				}
			}
		}
	}


	write_BeginData( Version , Shisan_Naiyou , fp_out[KISONENKIN] );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 1 , 1 , shubetu - 6 );
				OutputValue = Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][1]
				             + Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][2];
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le\n", OutputValue );
			}

			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 1 , 2 , shubetu - 6 );
				OutputValue = Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM].kihon;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM].kakyu;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM].kihon;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM].kakyu;
				fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
			}

			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 1 , 3 , shubetu - 6 );
				OutputValue = Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM].kihon
							 + Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM].kihon
							 + ( nenrei == UNDER_63 ? Izoku_Ko[shubetu][sotai_nendo].kihon : 0. );
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM].kakyu
							 + Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM].kakyu
							 + ( nenrei == UNDER_63 ? Izoku_Ko[shubetu][sotai_nendo].kakyu : 0. );
				fprintf( fp_out[KISONENKIN] , "%20.14le\n", OutputValue );	
			}

			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 2 , 1 , shubetu - 6 );
				OutputValue = Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
							 + Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
							 + Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu
							 + Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo
							 + Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue
				 = Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae
					 + Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae;
				fprintf( fp_out[KISONENKIN] , "%20.14le,", OutputValue );

				OutputValue = Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu;
				fprintf( fp_out[KISONENKIN] , "%20.14le\n", OutputValue );
			}

			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 2 , 2 , shubetu - 6 );

				OutputValue = Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].kihon
							 - Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].menjo_kihon;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].menjo_kihon;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].kakyu
							 - Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].menjo_kakyu;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM].menjo_kakyu;
				fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
			}

			for( shubetu = SHUBETU_OTOKO ; shubetu <= SHUBETU_ONNA ; shubetu++ )
			{
				fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d,%d,%d," , nendo , 1 , nenrei , 2 , 3 , shubetu - 6 );
				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
			}
		}

		fprintf( fp_out[KISONENKIN] , "%d," , nendo );
		OutputValue = Hiho_Noufu[2][sotai_nendo][HIHO_NENREI_SUM];
		for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
		{
			OutputValue += Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][dankai] * Hokenryou_Wariai[dankai];
		}
		fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

		OutputValue = Hiho_Noufu[5][sotai_nendo][HIHO_NENREI_SUM];
		for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
		{
			OutputValue += Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][dankai] * Hokenryou_Wariai[dankai];
		}
		fprintf( fp_out[KISONENKIN] , "%20.14le" , OutputValue );

		fprintf( fp_out[KISONENKIN] , ",%20.14le" , Hiho_Sankyu_Sum[nendo - SHONENDO]);
		fprintf( fp_out[KISONENKIN] , ",%20.14le" , Hiho_Ikukyu_Sum[nendo - SHONENDO]);
		fprintf( fp_out[KISONENKIN] , "\n");

		for( shubetu = 0 ; shubetu <= 1 ; shubetu++ )
		{
			fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d," , nendo , 2 , 1 , shubetu + 1 );
			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				OutputValue = Rorei_Jukyu_Nendokan[shubetu][sotai_nendo][counter];
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
			}

			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				OutputValue = 0.;
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
			}

			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				OutputValue = Rorei_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter];
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
			}

			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				OutputValue = Turo_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][counter];
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
			}

			OutputValue = Gonen_Jukyu_Nendokan[shubetu][sotai_nendo][0];
			fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
		}

		for( shubetu = 0 ; shubetu <= 1 ; shubetu++ )
		{
			fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d," , nendo , 2 , 2 , shubetu + 1 );

			for( counter = 0 ; counter <= 1 ; counter++ )
			{
				OutputValue = Shogai_Ippan_Jukyu_Nendokan[shubetu][sotai_nendo][counter]
			                 + Shogai_20mae_Jukyu_Nendokan[shubetu][sotai_nendo][counter];
				fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
			}

			OutputValue = Shogai_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][0];
			fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );

			OutputValue = Shogai_Kyu_Jukyu_Nendokan[shubetu][sotai_nendo][1];
			fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
		}

		fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d," , nendo , 2 , 3 , 1 );
		OutputValue = Izoku_Ko_Jukyu_Nendokan[0][sotai_nendo] + Izoku_Ko_Jukyu_Nendokan[1][sotai_nendo];
		fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
		OutputValue = Izoku_Ko_Jukyu_Nendokan[0][sotai_nendo] + Izoku_Ko_Jukyu_Nendokan[1][sotai_nendo];
		fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );

		fprintf( fp_out[KISONENKIN] , "%d,%d,%d,%d," , nendo , 2 , 3 , 2 );
		OutputValue = Izoku_Tuma_Jukyu_Nendokan[0][sotai_nendo][0] + Izoku_Tuma_Jukyu_Nendokan[1][sotai_nendo][0]
					 + Izoku_Otto_Jukyu_Nendokan[0][sotai_nendo][0] + Izoku_Otto_Jukyu_Nendokan[1][sotai_nendo][0]
					 + Izoku_Ko_Jukyu_Nendokan[0][sotai_nendo] + Izoku_Ko_Jukyu_Nendokan[1][sotai_nendo];
		fprintf( fp_out[KISONENKIN] , "%20.14le," , OutputValue );
		OutputValue = Izoku_Tuma_Jukyu_Nendokan[0][sotai_nendo][1] + Izoku_Tuma_Jukyu_Nendokan[1][sotai_nendo][1]
					 + Izoku_Otto_Jukyu_Nendokan[0][sotai_nendo][1] + Izoku_Otto_Jukyu_Nendokan[1][sotai_nendo][1]
					 + Izoku_Ko_Jukyu_Nendokan[0][sotai_nendo] + Izoku_Ko_Jukyu_Nendokan[1][sotai_nendo];
		fprintf( fp_out[KISONENKIN] , "%20.14le\n" , OutputValue );
	}

	write_BeginData( Version , Shisan_Naiyou , fp_out[DOKUZI] );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[DOKUZI] , "%d,", nendo );

		OutputValue = Fuka_Hiho[2][sotai_nendo][HIHO_NENREI_SUM] + Fuka_Hiho[5][sotai_nendo][HIHO_NENREI_SUM];
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Rorei[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Rorei_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Turo_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Kafu[SHUBETU_SUM][sotai_nendo].noufu + Kafu[SHUBETU_SUM][sotai_nendo].menjo[SUM][SUM];
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Kafu_Kyu[SHUBETU_SUM][sotai_nendo].noufu;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Kafu_Kyu[SHUBETU_SUM][sotai_nendo].menjo[SUM][SUM];
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Ichijikin[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Ichijikin[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu_fuka;
		fprintf( fp_out[DOKUZI] , "%20.14le,", OutputValue );

		OutputValue = Rorei[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][SUM]
					 + Rorei_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
					 + Rorei_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo
					 + Turo_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
					 + Turo_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo
					 + Shogai_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kihon
					 + Shogai_Kyu[SHUBETU_SUM][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kakyu;
		fprintf( fp_out[DOKUZI] , "%20.14le\n", OutputValue );
	}


	return;

}


int Hanbetu( int shubetu )
{
	int danjo;
	
	danjo = (shubetu <= 3) ? SHUBETU_OTOKO : SHUBETU_ONNA;
	return( danjo );
}
