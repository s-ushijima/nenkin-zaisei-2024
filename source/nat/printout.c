#include <stdio.h>
#include <iostream>
#include "snaps.h"
#include "mcntl.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mecon.h"


void printout()
{
	int nendo;
	int nenrei;
	int jukyu_nenrei;
	int sotai_nendo;
	int shubetu;
	double sum;
	double average;

	double zoubun = 0.;
	zoubun = 1.0 / 100;

	fprintf( fp_out[PRINT_ROREI_SHINKI] , ", shubetu, nendo, nenrei, jukyu_nenrei, noufu\n" );

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		if( shubetu == 2 || shubetu == 3 || shubetu == 5 || shubetu == 6 )
		{
			for( nendo = SAISHUNENDO ; nendo >= SHONENDO ; nendo-- )
			{
				sotai_nendo = nendo - SHONENDO;
				for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
				{
					for( nenrei = MAX_ROREI_JUKYU ; nenrei >= UNDER_64 ; nenrei-- )
					{
						if( nenrei == UNDER_64 )
						{
							Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan_64( Rorei[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Rorei[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

							Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan_64( Rorei_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Rorei_Kyu[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

							Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan_64( Turo_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Turo_Kyu[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

							Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan_64( Gonen[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Gonen[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
						}
						else
						{
							Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan( Rorei[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] );

							Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan( Rorei_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] );

							Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan( Turo_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] );

							Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
							 = nendokan( Gonen[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
							              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] );
						}

						fprintf( fp_out[PRINT_ROREI_SHINKI] , "3, %d, %d, %d, %d, %f\n" , shubetu, nendo, nenrei, jukyu_nenrei, Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU].noufu );
						Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );

						Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM]
						 = add( Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM] ,
						         Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] );
					}
				}


				for( nenrei = MAX_SHOGAI_JUKYU ; nenrei >= UNDER_64 ; nenrei-- )
				{
					if( nenrei == UNDER_64 )
					{
						Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Shogai_Ippan[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_Ippan[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

						Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Shogai_20mae[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_20mae[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

						Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Shogai_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_Kyu[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}
					else
					{
						Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan( Shogai_Ippan[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						              Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] , 
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

						Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan( Shogai_20mae[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						              Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] , 
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

						Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan( Shogai_Kyu[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						              Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] , 
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}

					Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] ,
					         Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] ,
					         Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] ,
					         Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				for( nenrei = MAX_IZOKU_TUMA_JUKYU ;  nenrei >= UNDER_64 ; nenrei-- )
				{
					if( nenrei == UNDER_64 )
					{
						Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Izoku_Tuma[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						                 Izoku_Tuma[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}
					else
					{
						Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan( Izoku_Tuma[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						              Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}

					Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] , Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				for( nenrei = MAX_IZOKU_OTTO_JUKYU ;  nenrei >= UNDER_64 ; nenrei-- )
				{
					if( nenrei == UNDER_64 )
					{
						Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Izoku_Otto[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						                 Izoku_Otto[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						                 kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}
					else
					{
						Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan( Izoku_Otto[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						              Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei <= UNDER_67 ? UNDER_67 - UNDER_67 : nenrei - UNDER_67] ,
						              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
					}

					Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
					Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] , Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}

				Izoku_Ko[shubetu][sotai_nendo]
				 = nendokan( Izoku_Ko[shubetu][sotai_nendo - 1] , Izoku_Ko[shubetu][sotai_nendo] ,
				 	      kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] ,
				              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

				Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo] = add( Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo] , Izoku_Ko[shubetu][sotai_nendo] );


				Kafu[shubetu][sotai_nendo]
				 = nendokan( Kafu[shubetu][sotai_nendo - 1] , Kafu[shubetu][sotai_nendo] ,
				 	      kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
				Kafu_Kyu[shubetu][sotai_nendo]
				 = nendokan( Kafu_Kyu[shubetu][sotai_nendo - 1] , Kafu_Kyu[shubetu][sotai_nendo] ,
				              kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );

				Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo]
				 = add( Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo] , Kafu[shubetu][sotai_nendo] );
				Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo]
				 = add( Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo] , Kafu_Kyu[shubetu][sotai_nendo] );


				for( nenrei = MAX_HIHO_NENREI ; nenrei >= UNDER_64 ;  nenrei-- )
				{
					if( nenrei == UNDER_64 )
					{
						Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						 = nendokan_64( Ichijikin[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
						 		 Ichijikin[shubetu][sotai_nendo][nenrei - 1 - NENREI_SUM] ,
						                 Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] , 1.  );
					}
					else
					{
							Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM]
							 = nendokan( Ichijikin[shubetu][sotai_nendo - 1][nenrei - 1 - NENREI_SUM] ,
							 	      Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] , 1.  );
					}

					Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM] , Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] );

					Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM]
					 = add( Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM] , Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] );
				}
			}
		}
	}

	fprintf( fp_out[PRINT_HIHO] , "被保険者数  種別=0（総計）\n" );
	fprintf( fp_out[PRINT_HIHO] , "年度,被保険者数,納付ﾒ数,全額免除ﾒ数,3/4免除ﾒ数,半額免除ﾒ数,1/4免除ﾒ数,付加被保険者数\n" );
	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		fprintf( fp_out[PRINT_HIHO] , "%d," , nendo );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Kei[2][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Kei[3][sotai_nendo][HIHO_NENREI_SUM]
		                                   + Hiho_Kei[5][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Kei[6][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Noufu[2][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Noufu[3][sotai_nendo][HIHO_NENREI_SUM]
		                                   + Hiho_Noufu[5][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Noufu[6][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] + Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU]
		                                   + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] + Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4]
		                                   + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] + Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2]
		                                   + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] + Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4]
		                                   + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f\n" , Fuka_Hiho[2][sotai_nendo][HIHO_NENREI_SUM] + Fuka_Hiho[3][sotai_nendo][HIHO_NENREI_SUM]
		                                    + Fuka_Hiho[5][sotai_nendo][HIHO_NENREI_SUM] + Fuka_Hiho[6][sotai_nendo][HIHO_NENREI_SUM] );
	}
	fprintf( fp_out[PRINT_HIHO] , "被保険者数  種別=1（１号計）\n" );
	fprintf( fp_out[PRINT_HIHO] , "年度,被保険者数,納付ﾒ数,全額免除ﾒ数,3/4免除ﾒ数,半額免除ﾒ数,1/4免除ﾒ数,付加被保険者数\n" );
	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		fprintf( fp_out[PRINT_HIHO] , "%d," , nendo );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Kei[2][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Kei[5][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Noufu[2][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Noufu[5][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[2][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] + Hiho_Menjo[5][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f\n" , Fuka_Hiho[2][sotai_nendo][HIHO_NENREI_SUM] + Fuka_Hiho[5][sotai_nendo][HIHO_NENREI_SUM] );
	}
	for( shubetu = 2 ; shubetu <= 3 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_HIHO] , "被保険者数  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_HIHO] , "年度,被保険者数,納付ﾒ数,全額免除ﾒ数,3/4免除ﾒ数,半額免除ﾒ数,1/4免除ﾒ数,付加被保険者数\n" );
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[PRINT_HIHO] , "%d," , nendo );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Kei[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Noufu[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] );
			fprintf( fp_out[PRINT_HIHO] , "%f\n" , Fuka_Hiho[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
		}
	}
	fprintf( fp_out[PRINT_HIHO] , "被保険者数  種別=4（３号計）\n" );
	fprintf( fp_out[PRINT_HIHO] , "年度,被保険者数,納付ﾒ数,全額免除ﾒ数,3/4免除ﾒ数,半額免除ﾒ数,1/4免除ﾒ数,付加被保険者数\n" );
	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		fprintf( fp_out[PRINT_HIHO] , "%d," , nendo );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Kei[3][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Kei[6][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Noufu[3][sotai_nendo][HIHO_NENREI_SUM] + Hiho_Noufu[6][sotai_nendo][HIHO_NENREI_SUM] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] );
		fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[3][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] + Hiho_Menjo[6][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] );
		fprintf( fp_out[PRINT_HIHO] , "%f\n" , Fuka_Hiho[3][sotai_nendo][HIHO_NENREI_SUM] + Fuka_Hiho[6][sotai_nendo][HIHO_NENREI_SUM] );
	}
	for( shubetu = 5 ; shubetu <= 6 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_HIHO] , "被保険者数  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_HIHO] , "年度,被保険者数,納付ﾒ数,全額免除ﾒ数,3/4免除ﾒ数,半額免除ﾒ数,1/4免除ﾒ数,付加被保険者数\n" );
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[PRINT_HIHO] , "%d," , nendo );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Kei[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Noufu[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][ZENGAKU] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_3_4] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_2] );
			fprintf( fp_out[PRINT_HIHO] , "%f," , Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][MENJO_1_4] );
			fprintf( fp_out[PRINT_HIHO] , "%f\n" , Fuka_Hiho[shubetu][sotai_nendo][HIHO_NENREI_SUM] );
		}
	}


	fprintf( fp_out[PRINT_ROREI] , "新法老齢年金  種別=0\n");
	fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,下支え分,平均年金額,付加年金\n" );
	
	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
		       + Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][SUM]
		       + Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae ;
		
		if( Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
		{
			average = sum / Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}
		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][SUM] );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
		fprintf( fp_out[PRINT_ROREI] , "%f," , average );
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Rorei[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "新法老齢年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,下支え分,平均年金額,付加年金\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
			       + Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][SUM]
			       + Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae;

			if( Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
			{
				average = sum / Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
			}
			else
			{
				average = 0.;
			} 
			fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo[SUM][SUM] );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
			fprintf( fp_out[PRINT_ROREI] , "%f," , average );
			fprintf( fp_out[PRINT_ROREI] , "%f\n" , Rorei[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
		}
	}

	fprintf( fp_out[PRINT_ROREI] , "旧法老齢年金  種別=0\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,嵩上げ納付分,嵩上げ免除分,下支え分,平均年金額,付加年金\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
		       + Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
		       + Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu
		       + Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo
		       + Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae;

		if( Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
		{
			average = sum / Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
		fprintf( fp_out[PRINT_ROREI] , "%f," , average );
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Rorei_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "旧法老齢年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,嵩上げ納付分,嵩上げ免除分,下支え分,平均年金額,付加年金\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
			       + Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
			       + Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu
			       + Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo 
			       + Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae ;

			if( Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
			{
				average = sum / Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
			fprintf( fp_out[PRINT_ROREI] , "%f," , average );
			fprintf( fp_out[PRINT_ROREI] , "%f\n" , Rorei_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
		}
	}

	fprintf( fp_out[PRINT_ROREI] , "旧法通老年金  種別=0\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,嵩上げ納付分,嵩上げ免除分,下支え分,平均年金額,付加年金\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
		       + Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
		       + Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu
		       + Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo 
		       + Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae ;

		if( Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
		{
			average = sum / Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
		fprintf( fp_out[PRINT_ROREI] , "%f," , average );
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Turo_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "旧法通老年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,納付分,免除分,嵩上げ納付分,嵩上げ免除分,下支え分,平均年金額,付加年金\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
			       + Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo
			       + Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu
			       + Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo 
			       + Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae ;

			if( Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
			{
				average = sum / Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , sum );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].menjo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].kasa_menjo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].rofuku_shitasasae );
			fprintf( fp_out[PRINT_ROREI] , "%f," , average );
			fprintf( fp_out[PRINT_ROREI] , "%f\n" , Turo_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].fuka );
		}
	}

	fprintf( fp_out[PRINT_ROREI] , "５年年金  種別=0\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		if( Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
		{
			average = Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
			           / Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
		fprintf( fp_out[PRINT_ROREI] , "%f," , Gonen[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "５年年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_ROREI] , "年度,受給ﾒ数,年金額,平均年金額\n" );
		
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			if( Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu > 0. )
			{
				average = Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu
				           / Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].ninzu );
			fprintf( fp_out[PRINT_ROREI] , "%f," , Gonen[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM][KURI_AGE_SAGE_SUM].noufu );
			fprintf( fp_out[PRINT_ROREI] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_ROREI] , "基礎年金満額（基本額）\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,67歳以下," );
	for( nenrei = 68 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d歳," , nenrei );
	}
	fprintf( fp_out[PRINT_ROREI] , "%d歳\n" , MAX_ROREI_JUKYU );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		for( nenrei = UNDER_67 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
		{
			fprintf( fp_out[PRINT_ROREI] , "%f," , Full_Pension[nendo - SHONENDO][nenrei - UNDER_67] );
		}
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Full_Pension[nendo - SHONENDO][MAX_ROREI_JUKYU - UNDER_67] );
	}

	fprintf( fp_out[PRINT_ROREI] , "基礎年金満額（加給額１、２子）\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,67歳以下," );
	for( nenrei = 68 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d歳," , nenrei );
	}
	fprintf( fp_out[PRINT_ROREI] , "%d歳\n" , MAX_ROREI_JUKYU );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		for( nenrei = UNDER_67 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
		{
			fprintf( fp_out[PRINT_ROREI] , "%f," , Kakyu_Tanka_12shi[nendo - SHONENDO][nenrei - UNDER_67] );
		}
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Kakyu_Tanka_12shi[nendo - SHONENDO][MAX_ROREI_JUKYU - UNDER_67] );
	}

	fprintf( fp_out[PRINT_ROREI] , "基礎年金満額（加給額３子以降）\n" );
	fprintf( fp_out[PRINT_ROREI] , "年度,67歳以下," );
	for( nenrei = 68 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d歳," , nenrei );
	}
	fprintf( fp_out[PRINT_ROREI] , "%d歳\n" , MAX_ROREI_JUKYU );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[PRINT_ROREI] , "%d," , nendo );
		for( nenrei = UNDER_67 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
		{
			fprintf( fp_out[PRINT_ROREI] , "%f," , Kakyu_Tanka_3shiiko[nendo - SHONENDO][nenrei - UNDER_67] );
		}
		fprintf( fp_out[PRINT_ROREI] , "%f\n" , Kakyu_Tanka_3shiiko[nendo - SHONENDO][MAX_ROREI_JUKYU - UNDER_67] );
	}

	fprintf( fp_out[PRINT_SHOGAI] , "新法障害年金（一般）  種別=0\n" );
	fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
		       + Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

		if( Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_SHOGAI] , "新法障害年金（一般）  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
			       + Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;
			
			if( Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Ippan[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_SHOGAI] , "新法障害年金（２０歳前）  種別=0\n" );
	fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
		       + Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

		if( Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_SHOGAI] , "新法障害年金（２０歳前）  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
			       + Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

			if( Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_20mae[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_SHOGAI] , "旧法障害年金 種別=0\n" );
	fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,免除額（基本の再掲）,免除額（加給の再掲）,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
		       + Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

		if( Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kihon );
		fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kakyu );
		fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_SHOGAI] , "旧法障害年金 種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_SHOGAI] , "年度,受給ﾒ数,年金額,基本額,加給額,免除額（基本の再掲）,免除額（加給の再掲）,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
			       + Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

			if( Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_SHOGAI] , "%d," , nendo );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , sum );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kihon );
			fprintf( fp_out[PRINT_SHOGAI] , "%f," , Shogai_Kyu[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].menjo_kakyu );
			fprintf( fp_out[PRINT_SHOGAI] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（妻）  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
		       + Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

		if( Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（妻）  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
			       + Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

			if( Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Tuma[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（夫）  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
		       + Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

		if( Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（夫）  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon
			       + Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu;

			if( Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kihon );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Otto[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kakyu );
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（子）  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].kihon + Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].kakyu;

		if( Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu > 0. )
		{
			average = sum / Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].kihon );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[SHUBETU_SUM_NENDOKAN][sotai_nendo].kakyu );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , "新法遺族年金（子）  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,基本額,加給額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Izoku_Ko[shubetu][sotai_nendo].kihon + Izoku_Ko[shubetu][sotai_nendo].kakyu;

			if( Izoku_Ko[shubetu][sotai_nendo].ninzu > 0. )
			{
				average = sum / Izoku_Ko[shubetu][sotai_nendo].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[shubetu][sotai_nendo].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[shubetu][sotai_nendo].kihon );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Izoku_Ko[shubetu][sotai_nendo].kakyu );
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , "新法寡婦年金  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,納付額,免除額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].noufu + Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].menjo[SUM][SUM];

		if( Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu > 0. )
		{
			average = sum / Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].noufu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[SHUBETU_SUM_NENDOKAN][sotai_nendo].menjo[SUM][SUM] );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , "新法寡婦年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,納付額,免除額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Kafu[shubetu][sotai_nendo].noufu + Kafu[shubetu][sotai_nendo].menjo[SUM][SUM];

			if( Kafu[shubetu][sotai_nendo].ninzu > 0. )
			{
				average = sum / Kafu[shubetu][sotai_nendo].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[shubetu][sotai_nendo].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[shubetu][sotai_nendo].noufu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu[shubetu][sotai_nendo].menjo[SUM][SUM]);
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , "旧法寡婦年金  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,納付額,免除額,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].noufu
		       + Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].menjo[SUM][SUM];

		if( Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu > 0. )
		{
			average = sum / Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].noufu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[SHUBETU_SUM_NENDOKAN][sotai_nendo].menjo[SUM][SUM] );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , "旧法寡婦年金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額,納付額,免除額,平均年金額\n" );

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Kafu_Kyu[shubetu][sotai_nendo].noufu + Kafu_Kyu[shubetu][sotai_nendo].menjo[SUM][SUM];

			if( Kafu_Kyu[shubetu][sotai_nendo].ninzu > 0. )
			{
				average = sum / Kafu_Kyu[shubetu][sotai_nendo].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[shubetu][sotai_nendo].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[shubetu][sotai_nendo].noufu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Kafu_Kyu[shubetu][sotai_nendo].menjo[SUM][SUM] );
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}

	fprintf( fp_out[PRINT_IZOKU] , " 死亡一時金  種別=0\n" );
	fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額（計）,年金額納付分,年金額付加分,平均年金額\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		sum = Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu 
		       + Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu_fuka;

		if( Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
		{
			average = sum / Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
		}
		else
		{
			average = 0.;
		}

		fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu );
		fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[SHUBETU_SUM_NENDOKAN][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu_fuka );
		fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
	}

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		fprintf( fp_out[PRINT_IZOKU] , " 死亡一時金  種別=%d\n" , shubetu );
		fprintf( fp_out[PRINT_IZOKU] , "年度,受給ﾒ数,年金額（計）,年金額納付分,年金額付加分,平均年金額\n" );
			
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			sum = Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu 
			       + Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu_fuka;

			if( Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu > 0. )
			{
				average = sum / Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu;
			}
			else
			{
				average = 0.;
			}

			fprintf( fp_out[PRINT_IZOKU] , "%d," , nendo );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].ninzu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , sum );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu );
			fprintf( fp_out[PRINT_IZOKU] , "%f," , Ichijikin[shubetu][sotai_nendo][NENREI_SUM - NENREI_SUM].kyufu_fuka );
			fprintf( fp_out[PRINT_IZOKU] , "%f\n" , average );
		}
	}
}
