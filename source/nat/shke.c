#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkisoritu.h"
#include "mkisosu.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "option.h"

using namespace std;


void shke( int nendo , int shubetu )
{
	int sotai_nendo;
	int nenrei;
	int jukyu_nenrei;
	int kikan ;
	int dankai;
	int kokko;
	int tokyu;
	int seibetu;
	int counter;

	struct rorei Rorei_Shikyu[MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN]
		 = {0.,0.,{0.},0.,0.};

	struct rorei_kyu Rorei_Kyu_Shikyu[MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN]
		 = {0.,0.,0.,0.,0.,0.,0.};

	struct rorei_kyu Turo_Kyu_Shikyu[MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN]
		 = {0.,0.,0.,0.,0.,0.,0.};

	struct gonen Gonen_Shikyu[MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN] = {0.,0.};
	struct shogai Shogai_Ippan_Shikyu[MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU] = {0.,0.,0.,0.,0.};
	struct shogai Shogai_20mae_Shikyu[MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU] = {0.,0.,0.,0.,0.};
	struct shogai Shogai_Kyu_Shikyu[MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU] = {0.,0.,0.,0.,0.};
	struct izoku Izoku_Tuma_Shikyu[MAX_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU + 1] = {0.,0.,0.};
	struct izoku Izoku_Otto_Shikyu[MAX_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU + 1] = {0.,0.,0.};
	struct izoku Izoku_Ko_Shikyu[MAX_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU + 1] = {0.,0.,0.};
	struct kafu Kafu_Shikyu[MAX_KAFU_JUKYU - MIN_KAFU_JUKYU + 1] = {0.,0.,{0.}};
	struct kafu Kafu_Kyu_Shikyu[MAX_KAFU_JUKYU - MIN_KAFU_JUKYU + 1] = {0.,0.,{0.}};



	if( shubetu <= 3 )
	{
		seibetu = 0;
	}
	else
	{
		seibetu = 1;
	}

	sotai_nendo = nendo - SHONENDO;
	if( sotai_nendo < 0 )
	{
		cout << "年度エラー" << endl;
		exit( 1 );
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			Hiho_Kei[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
			 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

			Hiho_Noufu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
			 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
			     * Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][NOUFU];

			Fuka_Hiho[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
			 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
			     * Noufuritu_Fuka[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

			if( Option == 1 && extendb( nendo , nenrei ) == 1 )
			{
				Hiho_Kei[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

				Hiho_Noufu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][NOUFU];

				Fuka_Hiho[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu_Fuka[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];
			}

			if( nenrei == MAX_HIHO_NENREI )
			{
				Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
				Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
			}
			else if( nendo == SAISHUNENDO )
			{
				Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][NOUFU];

				Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu_Fuka[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI];

				if( Option == 1 && extendb( nendo , nenrei ) == 1 )
				{
					Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
					 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][NOUFU];

					Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
					 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Noufuritu_Fuka[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI];
				}
			}
			else
			{
				Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][NOUFU];

				Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Noufuritu_Fuka[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI];

				if( Option == 1 && extendb( nendo , nenrei ) == 1 )
				{
					Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
					 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][NOUFU];

					Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI]
					 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Noufuritu_Fuka[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI];
				}
			}

			for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				if( dankai == ZENGAKU )
				{
					Hiho_Menjo[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
					 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * ( Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI]
					          + Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_SHINSEI] );
				}
				else
				{
					Hiho_Menjo[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
					 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai];
				}

				if( Option == 1 && extendb( nendo , nenrei ) == 1 )
				{
					if( dankai == ZENGAKU )
					{
						Hiho_Menjo[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * ( Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI]
						          + Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_SHINSEI] );
					}
					else
					{
						Hiho_Menjo[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai];
					}
				}

				if( nenrei == MAX_HIHO_NENREI )
				{
					Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai] = 0.;
				}
				else if( nendo == SAISHUNENDO )
				{
					if( dankai == ZENGAKU )
					{
						Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu 
						    * ( Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][MENJO_HOUTEI]
						      + Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][MENJO_SHINSEI] );
					}
					else
					{
						Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha[sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][kikan].ninzu
						     * Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][dankai];
					}

					if( Option == 1 && extendb( nendo , nenrei ) == 1 )
					{
						if( dankai == ZENGAKU )
						{
							Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
							 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu 
							    * ( Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][MENJO_HOUTEI]
							      + Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][MENJO_SHINSEI] );
						}
						else
						{
							Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
							 += Hihokensha2[sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][kikan].ninzu
							     * Noufuritu[shubetu][sotai_nendo][nenrei + 1 - MIN_HIHO_NENREI][dankai];
						}
					}
				}
				else
				{
					if( dankai == ZENGAKU )
					{
						Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu 
						    * ( Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][MENJO_HOUTEI]
						      + Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][MENJO_SHINSEI] );
					}
					else
					{
						Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
						 += Hihokensha[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][dankai];
					}

					if( Option == 1 && extendb( nendo , nenrei ) == 1 )
					{
						if( dankai == ZENGAKU )
						{
							Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
							 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu 
							    * ( Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][MENJO_HOUTEI]
							      + Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][MENJO_SHINSEI] );
						}
						else
						{
							Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai]
							 += Hihokensha2[sotai_nendo][nenrei - MIN_HIHO_NENREI][kikan].ninzu
							     * Noufuritu[shubetu][sotai_nendo + 1][nenrei + 1 - MIN_HIHO_NENREI][dankai];
						}
					}
				}
			}

		}
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		Hiho_Kei[shubetu][sotai_nendo][HIHO_NENREI_SUM]
		 += Hiho_Kei[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

		Hiho_Noufu[shubetu][sotai_nendo][HIHO_NENREI_SUM]
		 += Hiho_Noufu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

		Fuka_Hiho[shubetu][sotai_nendo][HIHO_NENREI_SUM]
		 += Fuka_Hiho[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

		Hiho_Noufu_P[shubetu][sotai_nendo][HIHO_NENREI_SUM]
		 += Hiho_Noufu_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

		Fuka_Hiho_P[shubetu][sotai_nendo][HIHO_NENREI_SUM]
		 += Fuka_Hiho_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];

		for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
		{
			Hiho_Menjo[shubetu][sotai_nendo][HIHO_NENREI_SUM][dankai]
			 += Hiho_Menjo[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai];

			Hiho_Menjo_P[shubetu][sotai_nendo][HIHO_NENREI_SUM][dankai]
			 += Hiho_Menjo_P[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai];
		}
	}

	for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
	{
		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = multiply( Shikyuritu_Rorei[sotai_nendo][nenrei - MIN_ROREI_JUKYU] ,
				add( Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ,
					Rorei_Ichibu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			Rorei_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = multiply( Shikyuritu_Rorei_Kyu[sotai_nendo][nenrei - MIN_ROREI_JUKYU] ,
			             Rorei_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

			Turo_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = multiply( Shikyuritu_Turo_Kyu[sotai_nendo][nenrei - MIN_ROREI_JUKYU] ,
			             Turo_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

			Gonen_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = scalar( Shikyuritu_Gonen[sotai_nendo][nenrei - MIN_ROREI_JUKYU] ,
			           Gonen_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

			if( ( jukyu_nenrei == 66 && nendo - nenrei == SUIKEISHONENDO + 1 - 66 ) ||
				( jukyu_nenrei == 67 && nendo - nenrei == SUIKEISHONENDO + 1 - 67 ) ||
				( jukyu_nenrei == 68 && nendo - nenrei == SUIKEISHONENDO + 1 - 68 ) ||
				( jukyu_nenrei == 69 && nendo - nenrei == SUIKEISHONENDO + 1 - 69 ) ||
				( jukyu_nenrei == 70 && nendo - nenrei == SUIKEISHONENDO + 1 - 70 ) )
			{
				if( nendo >= SUIKEISHONENDO + 1 && nendo <= SUIKEISHONENDO + 10 )
				{
					Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
					 *= Waribikiritu[seibetu][0][jukyu_nenrei - 66][nendo - SUIKEISHONENDO - 1];

					Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
					 = adjustbenefit( Waribikiritu[seibetu][1][jukyu_nenrei - 66][nendo - SUIKEISHONENDO - 1] ,
					                  Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );
				}
				else if( nendo > SUIKEISHONENDO + 10 )
				{
					Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
					 *= Waribikiritu[seibetu][0][jukyu_nenrei - 66][1];

					Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
					 = adjustbenefit( Waribikiritu[seibetu][1][jukyu_nenrei - 66][9] ,
					                  Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );
				}
			}

			if( nenrei <= 63 )
			{
				Rorei[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Rorei[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Rorei_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Rorei_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Rorei_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Turo_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Turo_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Turo_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Gonen[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Gonen[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Gonen_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );
			}
			else
			{
				Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Rorei_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Rorei_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Rorei_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Turo_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Turo_Kyu_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );

				Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Gonen[shubetu][sotai_nendo][nenrei - NENREI_SUM][jukyu_nenrei - MIN_ROREI_JUKYU] ,
				        Gonen_Shikyu[nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] );
			}

		}
	}

	for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
	{
		for( nenrei = UNDER_63 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
				{
					Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[SUM][kokko]
					 += Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
							[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko];

					Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[dankai][SUM]
					 += Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
							[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko];

					Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[SUM][SUM]
					 += Rorei[shubetu][sotai_nendo][nenrei - NENREI_SUM]
							[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko];
				}
			}
		}
	}


	for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
	{
		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			Shogai_Ippan_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = scalar( Shikyuritu_Shogai_Ippan[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] ,
			           Shogai_Ippan_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] );

			Shogai_20mae_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = scalar( Shikyuritu_Shogai_20mae[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] ,
			           Shogai_20mae_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] );

			Shogai_Kyu_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = scalar( Shikyuritu_Shogai_Kyu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] ,
			           Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu] );

			if( nenrei <= 63 )
			{
				Shogai_Ippan[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
				 = add( Shogai_Ippan[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
				        Shogai_Ippan_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );
				
				Shogai_20mae[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
				 = add( Shogai_20mae[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
				        Shogai_20mae_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );
				
				Shogai_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
				 = add( Shogai_Kyu[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
				        Shogai_Kyu_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );
			}
			else
			{
				Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM]
				 = add( Shogai_Ippan[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
				        Shogai_Ippan_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );

				Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM]
				 = add( Shogai_20mae[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
				        Shogai_20mae_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );

				Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM]
				 = add( Shogai_Kyu[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
				        Shogai_Kyu_Shikyu[nenrei - MIN_SHOGAI_JUKYU][tokyu] );
			}
		}
	}

	for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
	{
		Izoku_Tuma_Shikyu[nenrei - MIN_IZOKU_TUMA_JUKYU]
		 = scalar( Shikyuritu_Tuma[sotai_nendo] , Izoku_Tuma_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU] );

		if( nenrei <= 63 )
		{
			Izoku_Tuma[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
			 = add( Izoku_Tuma[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
			        Izoku_Tuma_Shikyu[nenrei - MIN_IZOKU_TUMA_JUKYU] );
		}
		else
		{
			Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM]
			 = add( Izoku_Tuma[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
			        Izoku_Tuma_Shikyu[nenrei - MIN_IZOKU_TUMA_JUKYU] );
		}
	}

	for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
	{
		Izoku_Otto_Shikyu[nenrei - MIN_IZOKU_OTTO_JUKYU]
		 = scalar( Shikyuritu_Otto[sotai_nendo] , Izoku_Otto_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU] );
		
		if( nenrei <= 63 )
		{
			Izoku_Otto[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
			 = add( Izoku_Otto[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
			        Izoku_Otto_Shikyu[nenrei - MIN_IZOKU_OTTO_JUKYU] );
		}
		else
		{
			Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM]
			 = add( Izoku_Otto[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
			        Izoku_Otto_Shikyu[nenrei - MIN_IZOKU_OTTO_JUKYU] );
		}
	}

	for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
	{
		Izoku_Ko_Shikyu[nenrei - MIN_IZOKU_KO_JUKYU]
		 = scalar( Shikyuritu_Ko[nendo - SHONENDO] , Izoku_Ko_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU] );

		Izoku_Ko[shubetu][sotai_nendo]
		 = add( Izoku_Ko[shubetu][sotai_nendo] , Izoku_Ko_Shikyu[nenrei - MIN_IZOKU_KO_JUKYU] );
	}

	for( nenrei = 60 ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
	{
		Kafu_Shikyu[nenrei - MIN_KAFU_JUKYU]
		 = scalar( Shikyuritu_Kafu[nendo - SHONENDO][nenrei - 60] , 
		           Kafu_Nendomatu[sotai_nendo][nenrei - MIN_KAFU_JUKYU] );

		Kafu_Kyu_Shikyu[nenrei - MIN_KAFU_JUKYU]
		 = scalar( Shikyuritu_Kafu[nendo - SHONENDO][nenrei - 60] ,
		           Kafu_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_KAFU_JUKYU] );

		Kafu[shubetu][sotai_nendo]
		 = add( Kafu[shubetu][sotai_nendo] , Kafu_Shikyu[nenrei - MIN_KAFU_JUKYU] );

		Kafu_Kyu[shubetu][sotai_nendo]
		 = add( Kafu_Kyu[shubetu][sotai_nendo] , Kafu_Kyu_Shikyu[nenrei - MIN_KAFU_JUKYU] );
	}

	for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			Kafu[shubetu][sotai_nendo].menjo[SUM][kokko]
			 += Kafu[shubetu][sotai_nendo].menjo[dankai][kokko];

			Kafu_Kyu[shubetu][sotai_nendo].menjo[SUM][kokko]
			 += Kafu_Kyu[shubetu][sotai_nendo].menjo[dankai][kokko];

			Kafu[shubetu][sotai_nendo].menjo[dankai][SUM] += Kafu[shubetu][sotai_nendo].menjo[dankai][kokko];

			Kafu_Kyu[shubetu][sotai_nendo].menjo[dankai][SUM] += Kafu_Kyu[shubetu][sotai_nendo].menjo[dankai][kokko];

			Kafu[shubetu][sotai_nendo].menjo[SUM][SUM] += Kafu[shubetu][sotai_nendo].menjo[dankai][kokko];

			Kafu_Kyu[shubetu][sotai_nendo].menjo[SUM][SUM] += Kafu_Kyu[shubetu][sotai_nendo].menjo[dankai][kokko];
		}
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		if( nenrei <= 63 )
		{
			Ichijikin[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM]
			 = add( Ichijikin[shubetu][sotai_nendo][UNDER_63 - NENREI_SUM] ,
			        Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI] );
		}
		else
		{
			Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM]
			 = add( Ichijikin[shubetu][sotai_nendo][nenrei - NENREI_SUM] ,
			        Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI] );
		}
	}


	return;

}
