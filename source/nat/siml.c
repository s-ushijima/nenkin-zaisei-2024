#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mkisosu.h"
#include "mkisoritu.h"
#include "mecon.h"
#include "mcntl.h"
#include "mseid.h"
#include "mfile_open.h"
#include "option.h"

using namespace std;


int Shibou_Kubun( int nendo , double noufu_kikan , int option );

double Nendomatu_Tyousei_Keisu( int nendo , int nenrei );


void siml( int nendo , int shubetu )
{
	int sotai_nendo;
	int nenrei_tuma;
	int nenrei_otto;
	int nenrei_ko;
	int nenrei_kafu;
	int jukyu_nenrei;
	int seinendo;
	int dankai;
	int kokko;
	int kikan;
	int nenrei;
	int tokyu;
	int seibetu;

	struct hihokensha Hiho_Zennen = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Hiho_Gokei = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Taiki_Zennen = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Taiki_Gokei = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Noufu_Jokyo[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Hihokensha_Shibou[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1]
			 = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Taikisha_Shibou[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1]
			 = {0.,0.,0.,{0.},0.,0.,0.};
	static double Hiho_Zanzon[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	static double Taiki_Zanzon[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	static double Saikanyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	static double Shinkikanyu[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1];
	static double Dattaisha_Gokei[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	static double Dattaisha_Seizon[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	static double Hasseisha_Shogai[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	double Hiho_Zanzon_Gokei;
	double Taiki_Zanzon_Gokei;
	double Saikanyu_Gokei;
	double Noufu_Kikan;
	double Noufu_Kikan_Fuka;
	double Bunpu_Tuma[MAX_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU + 1];
	double Bunpu_Otto[MAX_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU + 1];
	double Bunpu_Kafu[MAX_KAFU_JUKYU - MIN_KAFU_JUKYU + 1];
	double Bunpu_Ko[MAX_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU + 1];
	double Hiho_Zanzon_P[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1] = {0.};
	double Taiki_Zanzon_P[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1] = {0.};
	struct hihokensha Hiho_Zennen2 = {0.,0.,0.,{0.},0.,0.,0.};
	struct hihokensha Hiho_Gokei2 = {0.,0.,0.,{0.},0.,0.,0.};
	double Hiho_Zanzon2[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1] = {0.};
	double Shinkikanyu2[MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1] = {0.};
	double Hiho_Zanzon_Gokei2 = {0.};
	struct rorei Rorei_Shinki[KURI_AGE_SAGE_SHIKYU_KUBUN]= {0.,0.,{0.},0.,0.};
	struct shogai Shogai_Ippan_Shinki[MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU] = {0.,0.,0.,0.,0.};
	struct shogai Shogai_20mae_Shinki[MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU] = {0.,0.,0.,0.,0.};
	struct izoku Izoku_Tuma_Shinki[MAX_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU + 1] = {0.,0.,0.};
	struct izoku Izoku_Otto_Shinki[MAX_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU + 1] = {0.,0.,0.};
	struct izoku Izoku_Ko_Shinki[MAX_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU + 1] = {0.,0.,0.};
	struct kafu Kafu_Shinki[MAX_KAFU_JUKYU - MIN_KAFU_JUKYU + 1] = {0.,0.,{0.}};
	double Temp_Shogai_Kyu_Nendomatu = {0.};
	double Temp_Izoku_Shinki_ninzu = {0.};


	sotai_nendo = nendo - SHONENDO;
	if( sotai_nendo < 0 )
	{
		cout << "年度エラー" << endl;
		exit( 1 );
	}

	if( shubetu == 2 || shubetu == 3 )
	{
		seibetu = OTOKO;
	}
	else if( shubetu == 5 || shubetu == 6 )
	{ 
		seibetu = ONNA;
	}
	else
	{
	 	seibetu = 0;
	}

	if( Kako_Saimu == 0 || nendo <= Kugiri_Nendo )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].ninzu = 0.;

			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].kikan = 1.;

			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].noufu
			 = Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][NOUFU];

			for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
				{
					if( dankai == ZENGAKU )
					{
						Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].menjo[dankai][kokko]
						 = Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_HOUTEI]
						    + Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][MENJO_SHINSEI];
					}
					else
					{
						Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].menjo[dankai][kokko]
						 = Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][dankai];
					}
				}
			}

			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].gakusei
			 = Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][GAKUSEI];

			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].wakamono
			 = Noufuritu[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI][WAKAMONO];

			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka
			 = Noufuritu_Fuka[shubetu][sotai_nendo][nenrei - MIN_HIHO_NENREI];
		}
	}
	else
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].ninzu = 0.;
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].kikan = 1.;
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].noufu = 0.;
			for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
				{
					Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].menjo[dankai][kokko] = 0.;
				}
			}
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].gakusei = 0.;
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].wakamono = 0.;
			Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka = 0.;
		}
	}

	for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
	{
		Hiho_Zanzon_Gokei  = 0.;

		Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][0] = 0.;

		for( kikan = 1 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			if( nenrei == MIN_HIHO_NENREI )
			{
				Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] = 0.;
			}
			else
			{
				Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
				 = Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1].ninzu;

				if( kikan == MAX_HIHO_KIKAN )
				{
					Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
					 += Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu;
				}

				Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
				 *= ( 1. - Dattairyoku_Gokei[sotai_nendo][nenrei - MIN_HIHO_NENREI] );
			}

			Hiho_Zanzon_Gokei += Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan];
		}

		Taiki_Zanzon_Gokei = 0.;

		for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			if( nenrei == MIN_HIHO_NENREI )
			{
				Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] = 0.;
				Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu = 0.;
			}
			else
			{
				Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
				 = Taikisha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu
				    * ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] );

				Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
				 = Taikisha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu
				    - Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan];
			}

			Taiki_Zanzon_Gokei += Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan];
		}

 		if( Option == 1 )
		{
			Hiho_Zanzon_Gokei2 = 0.;

			Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][0] = 0.;

			for( kikan = 1 ; kikan <= MAX_HIHO_KIKAN - 1 ; kikan++ )
			{
				if( nenrei == MIN_HIHO_NENREI )
				{
					Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan] = 0.;
				}
				else
				{
					Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan]
					 = Hihokensha2[nendo - 1 -SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1].ninzu ;

					if( kikan == MAX_HIHO_KIKAN )
					{
						Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan]
						 += Hihokensha2[nendo - 1 -SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu;
					}

					Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan]
					 *= ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] );
				}

				Hiho_Zanzon_Gokei2 += Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan];
			}
		}

		if( Option == 1 && extenda( nendo , nenrei ) != 1 )
		{
			if( Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] 
			     < Hiho_Zanzon_Gokei + Hiho_Zanzon_Gokei2 )
			{
				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
					 *= fdiv( Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI]
					           - Hiho_Zanzon_Gokei2 , 
					          Hiho_Zanzon_Gokei );
				}
			}
		}
		else
		{
			if( Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] < Hiho_Zanzon_Gokei )
			{
				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan]
					 *= fdiv( Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] , 
					          Hiho_Zanzon_Gokei );
				}
			}
		}

		Saikanyu_Gokei
		 = min( ( Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] - Hiho_Zanzon_Gokei )
				 * Saikanyuritu[sotai_nendo][nenrei - MIN_HIHO_NENREI] , Taiki_Zanzon_Gokei );

		for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			Saikanyu[nenrei - MIN_HIHO_NENREI][kikan]
			 = Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] * fdiv( Saikanyu_Gokei , Taiki_Zanzon_Gokei) ;

			Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] -= Saikanyu[nenrei - MIN_HIHO_NENREI][kikan];
		}

		Shinkikanyu[nenrei - MIN_HIHO_NENREI]
		 = Sotowaku[shubetu][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI]
		    - Saikanyu[nenrei - MIN_HIHO_NENREI][0];

		for( kikan = 1 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			Shinkikanyu[nenrei - MIN_HIHO_NENREI]
			 -= Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] + Saikanyu[nenrei - MIN_HIHO_NENREI][kikan];

			if( Option == 1 && extendb( nendo , nenrei ) == 1 )
			{
				Shinkikanyu[nenrei - MIN_HIHO_NENREI]
				 -= Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan];
			}
		}

		for( kikan = MAX_HIHO_KIKAN ; kikan >= 1 ; kikan-- )
		{
			Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
			 = Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] + Saikanyu[nenrei - MIN_HIHO_NENREI][kikan];

			if( Option == 1 )
			{
				if( nenrei <= OP_MAX_KYOSHUTU_NENREI )
				{
					Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					 = Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan];
				}
			}

			if( nenrei == MIN_HIHO_NENREI )
			{
				Dattaisha_Gokei[nenrei - MIN_HIHO_NENREI][kikan] = 0.;
			}
			else
			{
				 Dattaisha_Gokei[nenrei - MIN_HIHO_NENREI][kikan]
				  = Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1].ninzu
				    - Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan];

				if( kikan == MAX_HIHO_KIKAN )
				{
					Dattaisha_Gokei[nenrei - MIN_HIHO_NENREI][kikan]
					 += Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu;
				}
			}

			Hasseisha_Shogai[nenrei - MIN_HIHO_NENREI][kikan]
			 = Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1].ninzu
			    * Hasseiryoku_Shogai[sotai_nendo][nenrei - MIN_HIHO_NENREI];

			if( kikan == MAX_HIHO_KIKAN )
			{
				Hasseisha_Shogai[nenrei - MIN_HIHO_NENREI][kikan]
				 += Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu
				     * Hasseiryoku_Shogai[sotai_nendo][nenrei - MIN_HIHO_NENREI];
			}

			Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
			 = Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1].ninzu
			    * Dattairyoku_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];

			if( kikan == MAX_HIHO_KIKAN )
			{
				Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
				 += Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan].ninzu
				     * Dattairyoku_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];
			}

			Dattaisha_Seizon[nenrei - MIN_HIHO_NENREI][kikan]
			 = Dattaisha_Gokei[nenrei - MIN_HIHO_NENREI][kikan]
			    - Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu;

			Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
			 = Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] + Dattaisha_Seizon[nenrei - MIN_HIHO_NENREI][kikan];

			if( Option == 1 )
			{
				if( extendb( nendo , nenrei ) == 1 )
				{
					Shinkikanyu2[nenrei - MIN_HIHO_NENREI]
					 += Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Hassei_Wariai_Rorei[sotai_nendo][nenrei - MIN_ROREI_JUKYU];
				}
			}
		}

		Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][0].ninzu
		 = Shinkikanyu[nenrei - MIN_HIHO_NENREI] + Saikanyu[nenrei - MIN_HIHO_NENREI][0];

		if( Option == 1 )
		{
			if( extendb( nendo , nenrei ) == 1 )
			{
				Shinkikanyu2[nenrei - MIN_HIHO_NENREI]
				 += Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][0].ninzu
				     * Hassei_Wariai_Rorei[sotai_nendo][nenrei - MIN_ROREI_JUKYU];
			}

			Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][0].ninzu
			 = Shinkikanyu2[nenrei - MIN_HIHO_NENREI];
		}

		Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][0].ninzu = Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][0];

		Dattaisha_Gokei[nenrei - MIN_HIHO_NENREI][0] = 0.;
		Dattaisha_Seizon[nenrei - MIN_HIHO_NENREI][0] = 0.;
		Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][0].ninzu = 0.;
		Hasseisha_Shogai[nenrei - MIN_HIHO_NENREI][0] = 0.;

	}


	for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
	{
		for( kikan = MAX_HIHO_KIKAN ; kikan >= 0 ; kikan-- )
		{
			if( nenrei == MIN_HIHO_NENREI )
			{
				Hiho_Zennen = Hihokensha_Zero;
				Taiki_Zennen = Taikisha_Zero;
			}
			else
			{
				if( kikan == 0 )
				{
					Hiho_Zennen = Hihokensha_Zero;
				}
				else
				{
					Hiho_Zennen = Hihokensha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan - 1];
				}

				Taiki_Zennen = Taikisha[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI][kikan];
			}

			Hiho_Gokei = add( scalar( Saikanyu[nenrei - MIN_HIHO_NENREI][kikan] , Taiki_Zennen ) ,
						      scalar( Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] , Hiho_Zennen ) );

			if( kikan == 0 )
			{
				Hiho_Gokei
				 = add( Hiho_Gokei ,
				        scalar_2( ( Saikanyu[nenrei - MIN_HIHO_NENREI][kikan]
								     + Shinkikanyu[nenrei - MIN_HIHO_NENREI] ) * 0.5 ,
								  Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );
			}
			else
			{
				Hiho_Gokei
				 = add( Hiho_Gokei ,
			            scalar_2( Saikanyu[nenrei - MIN_HIHO_NENREI][kikan] * 0.5
				                   + Hiho_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] ,
			                      Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );
			}

			Hiho_Gokei.ninzu = Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

			Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan] = average_by_ninzu( Hiho_Gokei );

			Taiki_Gokei
			 = add( scalar( Taiki_Zanzon[nenrei - MIN_HIHO_NENREI][kikan] , Taiki_Zennen ) ,
			        scalar( Dattaisha_Seizon[nenrei - MIN_HIHO_NENREI][kikan] , Hiho_Zennen ) );

			Taiki_Gokei
			 = add( Taiki_Gokei ,
			        scalar_2( Dattaisha_Seizon[nenrei - MIN_HIHO_NENREI][kikan] * 0.5 ,
			                  Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );

			Taiki_Gokei.ninzu = Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;
			Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan] = average_by_ninzu( Taiki_Gokei );

			Hiho_Zennen.ninzu = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu;

			Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan]
			 = add( Hiho_Zennen , scalar_2( 0.5 , Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );

			Taiki_Zennen.ninzu = Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu;
			Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan] = Taiki_Zennen;

		}
	}

	if( Option == 1 )
	{
		for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
		{
			for( kikan = MAX_HIHO_KIKAN ; kikan >= 0 ; kikan-- )
			{
				if( kikan >= 1 && nenrei >= MIN_HIHO_NENREI + 1 )
				{
					Hiho_Zennen2 = Hihokensha2[nendo - 1 - SHONENDO][nenrei - 1 - MIN_HIHO_NENREI ][kikan - 1];
				}
				else
				{
					Hiho_Zennen2 = Hihokensha_Zero;
				}

				Hiho_Gokei2 = scalar( Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan] , Hiho_Zennen2 );

				if( kikan > 0 )
				{
					if( extendb( nendo , nenrei ) == 1 )
					{
						Hiho_Gokei2 = add( Hiho_Gokei2 ,
											scalar_2( Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan] , 
														Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );
					}
					else if( extendc( nendo , nenrei ) == 1 )
					{
						Hiho_Gokei2 = add( Hiho_Gokei2 ,
											scalar_2( Hiho_Zanzon2[nenrei - MIN_HIHO_NENREI][kikan] * 0.5 , 
														Noufu_Jokyo[nenrei - MIN_HIHO_NENREI] , nendo ) );
					}
				}

				Hiho_Gokei2.ninzu = Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;
				Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan] = average_by_ninzu( Hiho_Gokei2 );
			}
		}
	}

	for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
	{
		for( tokyu = 1 ; tokyu <= 2 ;tokyu++ )
		{
			Shogai_20mae_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
		}
	}

	if( ( shubetu == 2 || shubetu == 5 ) && ( Kako_Saimu == 0 || nendo <= Kugiri_Nendo ) )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
			{
				Shogai_20mae_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
				 = ( Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 2 - MIN_WAKU_NENREI]
				      + Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
				      + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
				      + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 4.
				    * Hassei_Wariai_20mae[sotai_nendo][nenrei - MIN_HIHO_NENREI]
				    * Tokyu_Wariai_20mae[sotai_nendo][tokyu];

				Shogai_20mae_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].kihon
				 = Shogai_20mae_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
				    * Full_Pension[sotai_nendo][nenrei] * Shogai_Bairitu[tokyu];
			}
		}
	}

	for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
	{
		for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
		{
			Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
		}
	}

	if( Kako_Saimu == 0 || nendo <= Kugiri_Nendo )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
			{
				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					if( nenrei < 60)
					{
						Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
					 	 += Hasseisha_Shogai[nenrei - MIN_HIHO_NENREI][kikan]
						     * Tokyu_Wariai_Ippan[sotai_nendo][tokyu];
					}
				}

				if( nenrei >= 60 && ( shubetu == 2 || shubetu == 5 ) )
				{
					Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
					 = ( ( Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 2 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 4.
					     - Sotowaku_2gou[seibetu][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI] )
					   * Hasseiryoku_Shogai[sotai_nendo][nenrei - MIN_HIHO_NENREI]
					   * Tokyu_Wariai_Ippan[sotai_nendo][tokyu];
				}

				Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].kihon
				 = Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
				    * Full_Pension[sotai_nendo][nenrei]
				    * Shogai_Bairitu[tokyu];
			}
		}
	}

	for( nenrei_tuma = MIN_IZOKU_TUMA_JUKYU ; nenrei_tuma <= MAX_IZOKU_TUMA_JUKYU ; nenrei_tuma++ )
	{
		Izoku_Tuma_Shinki[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU] = Izoku_Zero;
	}

	for( nenrei_otto = MIN_IZOKU_OTTO_JUKYU ; nenrei_otto <= MAX_IZOKU_OTTO_JUKYU ; nenrei_otto++ )
	{
		Izoku_Otto_Shinki[nenrei_otto - MIN_IZOKU_OTTO_JUKYU] = Izoku_Zero;
	}

	for( nenrei_ko = MIN_IZOKU_KO_JUKYU ; nenrei_ko <= MAX_IZOKU_KO_JUKYU ; nenrei_ko++ )
	{
		Izoku_Ko_Shinki[nenrei_ko - MIN_IZOKU_KO_JUKYU] = Izoku_Zero;
	}

	if( shubetu == 2 && ( Kako_Saimu == 0 || nendo <= Kugiri_Nendo ) )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( nenrei_tuma = MIN_IZOKU_TUMA_JUKYU ; nenrei_tuma <= MAX_IZOKU_TUMA_JUKYU ; nenrei_tuma++ )
			{
				if( nenrei_tuma == (int)Sokan_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI] )
				{
					Bunpu_Tuma[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU]
					 = Sokan_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI] - nenrei_tuma;
				}
				else if( nenrei_tuma == (int)Sokan_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI] + 1 )
				{
					Bunpu_Tuma[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU]
					 = nenrei_tuma - Sokan_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI];
				}
				else
				{
					Bunpu_Tuma[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU] = 1.;
				}

				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					if( nenrei < 60 )
					{
						Temp_Izoku_Shinki_ninzu
						 = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						    * Hassei_Wariai_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						    * ( 1. - Bunpu_Tuma[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU] );

						Izoku_Tuma_Shinki[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU].ninzu
						 += Temp_Izoku_Shinki_ninzu;

						Izoku_Tuma_Shinki[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU].kihon
						 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
					}
				}

				if( nenrei >= 60 && nenrei <= 64 )
				{
					Temp_Izoku_Shinki_ninzu
					 = ( ( Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 2 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 4.
					     - Sotowaku_2gou[seibetu][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI] )
					   * q[( nendo <= SHIKKENRITU_MAX ? nendo : SHIKKENRITU_MAX ) - SHIKKENRITU_MIN][nenrei][seibetu]
					   * Hassei_Wariai_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI]
					   * ( 1. - Bunpu_Tuma[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU] );

					Izoku_Tuma_Shinki[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU].ninzu
					 += Temp_Izoku_Shinki_ninzu;

					Izoku_Tuma_Shinki[nenrei_tuma - MIN_IZOKU_TUMA_JUKYU].kihon
					 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
				}
			}

			for( nenrei_ko = MIN_IZOKU_KO_JUKYU ; nenrei_ko <= MAX_IZOKU_KO_JUKYU ; nenrei_ko++ )
			{
				if( nenrei_ko == (int)Sokan_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI] )
				{
					Bunpu_Ko[nenrei_ko - MIN_IZOKU_KO_JUKYU]
					 = Sokan_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI] - nenrei_ko;
				}
				else if( nenrei_ko == (int)Sokan_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI] + 1 )
				{
					Bunpu_Ko[nenrei_ko - MIN_IZOKU_KO_JUKYU]
					 = nenrei_ko - Sokan_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI];
				}
				else
				{
					Bunpu_Ko[nenrei_ko - MIN_IZOKU_KO_JUKYU] = 1.;
				}

				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					if( nenrei < 60 )
					{
						Temp_Izoku_Shinki_ninzu
						 = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						    * Hassei_Wariai_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						    * ( 1. - Bunpu_Ko[nenrei_ko - MIN_IZOKU_KO_JUKYU] );

						Izoku_Ko_Shinki[nenrei_ko - MIN_IZOKU_KO_JUKYU].ninzu
						 += Temp_Izoku_Shinki_ninzu;

						Izoku_Ko_Shinki[nenrei_ko - MIN_IZOKU_KO_JUKYU].kihon
						 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
					}
				}

				if( nenrei >= 60 && nenrei <= 64 )
				{
					Temp_Izoku_Shinki_ninzu
					 = ( ( Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 2 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 4.
					     - Sotowaku_2gou[seibetu][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI] )
					   * q[( nendo <= SHIKKENRITU_MAX ? nendo : SHIKKENRITU_MAX ) - SHIKKENRITU_MIN][nenrei][seibetu]
					   * Hassei_Wariai_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI]
					   * ( 1. - Bunpu_Ko[nenrei_ko - MIN_IZOKU_KO_JUKYU] );

					Izoku_Ko_Shinki[nenrei_ko - MIN_IZOKU_KO_JUKYU].ninzu
					 += Temp_Izoku_Shinki_ninzu;

					Izoku_Ko_Shinki[nenrei_ko - MIN_IZOKU_KO_JUKYU].kihon
					 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
				}
			}
		}

	}

	if( (shubetu == 5 || shubetu == 6) && ( Kako_Saimu == 0 || nendo <= Kugiri_Nendo ) )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( nenrei_otto = MIN_IZOKU_OTTO_JUKYU ; nenrei_otto <= MAX_IZOKU_OTTO_JUKYU ; nenrei_otto++ )
			{
				if( nenrei_otto == (int)Sokan_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI] )
				{
					Bunpu_Otto[nenrei_otto - MIN_IZOKU_OTTO_JUKYU]
					 = Sokan_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI] - nenrei_otto;
				}
				else if( nenrei_otto == (int)Sokan_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI] + 1 )
				{
					Bunpu_Otto[nenrei_otto - MIN_IZOKU_OTTO_JUKYU]
					 = nenrei_otto - Sokan_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI];
				}
				else
				{
					Bunpu_Otto[nenrei_otto - MIN_IZOKU_OTTO_JUKYU] = 1.;
				}

				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					if( nenrei < 60 )
					{
						Temp_Izoku_Shinki_ninzu
						 = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						    * Hassei_Wariai_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						    * ( 1. - Bunpu_Otto[nenrei_otto - MIN_IZOKU_OTTO_JUKYU] );

						Izoku_Otto_Shinki[nenrei_otto - MIN_IZOKU_OTTO_JUKYU].ninzu
						 += Temp_Izoku_Shinki_ninzu;

						Izoku_Otto_Shinki[nenrei_otto - MIN_IZOKU_OTTO_JUKYU].kihon
						 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
					}
				}

				if( ( nenrei >= 60 && nenrei <= 64 ) && shubetu == 5 )
				{
					Temp_Izoku_Shinki_ninzu
					 = ( ( Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 2 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI]
					        + Sotowaku[shubetu - 1][nendo - SOTOWAKU_SHONENDO][nenrei - MIN_WAKU_NENREI] ) / 4.
					     - Sotowaku_2gou[seibetu][nendo - 1 - SOTOWAKU_SHONENDO][nenrei - 1 - MIN_WAKU_NENREI] )
					   * q[( nendo <= SHIKKENRITU_MAX ? nendo : SHIKKENRITU_MAX ) - SHIKKENRITU_MIN][nenrei][seibetu]
					   * Hassei_Wariai_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI]
					   * ( 1. - Bunpu_Otto[nenrei_otto - MIN_IZOKU_OTTO_JUKYU] );

					Izoku_Otto_Shinki[nenrei_otto - MIN_IZOKU_OTTO_JUKYU].ninzu
					 += Temp_Izoku_Shinki_ninzu;

					Izoku_Otto_Shinki[nenrei_otto - MIN_IZOKU_OTTO_JUKYU].kihon
					 += Temp_Izoku_Shinki_ninzu * Full_Pension[sotai_nendo][nenrei];
				}
			}
		}

	}

	for( nenrei_kafu = MIN_KAFU_JUKYU ; nenrei_kafu <= MAX_KAFU_JUKYU ; nenrei_kafu++ )
	{
		Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU] = Kafu_Zero;
	}

	if( shubetu == 2 && ( Kako_Saimu == 0 || nendo <= Kugiri_Nendo ) )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			seinendo = nendo - nenrei;

			for( nenrei_kafu = MIN_KAFU_JUKYU ; nenrei_kafu <= MAX_KAFU_JUKYU ; nenrei_kafu++ )
			{
				if( nenrei_kafu == (int)Sokan_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI] )
				{
					Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU]
					 = Sokan_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI] - nenrei_kafu;
				}
				else if( nenrei_kafu == (int)Sokan_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI] + 1 )
				{
					Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU]
					 = nenrei_kafu - Sokan_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI];
				}
				else
				{
					Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] = 1.;
				}

				for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
				{
					Noufu_Kikan = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu
					               + Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].gakusei
					               + Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].wakamono;

					for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
					{
						for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++)
						{
							Noufu_Kikan += Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko];
						}
					}

					if( Noufu_Kikan >= 10. )
					{
						Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].ninzu
						 += Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

						Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].noufu
						 += 3. / 4. * Full_Pension[sotai_nendo][nenrei]
						     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
						     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

						for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
						{
							for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
							{
								Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].noufu
								 += 3. / 4. * Hokenryou_Wariai[dankai] * Full_Pension[sotai_nendo][nenrei]
								     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
							  	     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
							    	 * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

								Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].menjo[dankai][kokko]
								 += 3. / 4. * Kokko_Wariai[kokko] * ( 1. - Hokenryou_Wariai[dankai] )
								     * Full_Pension[sotai_nendo][nenrei]
								     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
								     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );
							}
						}
					}

					Noufu_Kikan = Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu
						           + Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].gakusei
						           + Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].wakamono;

					for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
					{
						for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
						{
							Noufu_Kikan += Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko];
						}
					}

					if( Noufu_Kikan >= 10. )
					{
						Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].ninzu
						 += Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

						Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].noufu
						 += 3. / 4. * Full_Pension[sotai_nendo][nenrei]
						     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
						     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

						for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
						{
							for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
							{
								Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].noufu
								 += 3. / 4. * Hokenryou_Wariai[dankai] * Full_Pension[sotai_nendo][nenrei]
								     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
								     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );

								Kafu_Shinki[nenrei_kafu - MIN_KAFU_JUKYU].menjo[dankai][kokko]
								 += 3. / 4. * Kokko_Wariai[kokko] * ( 1. - Hokenryou_Wariai[dankai] )
								     * Full_Pension[sotai_nendo][nenrei]
								     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI]
								     * ( 1. - Bunpu_Kafu[nenrei_kafu - MIN_KAFU_JUKYU] );
							}
						}
					}

				}
			}
		}
	}

	if( ( shubetu == 2 || shubetu == 5 ) && ( Kako_Saimu == 0 || nendo <= Kugiri_Nendo ) )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
			{
				Noufu_Kikan = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu;

				for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
				{
					for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
					{
						Noufu_Kikan += Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
						                * Hokenryou_Wariai[dankai];
					}
				}

				if( Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka == 0. )
				{
					Noufu_Kikan_Fuka = 0.;
				}
				else
				{
					Noufu_Kikan_Fuka = Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].fuka
					                    / Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka;
				}

				if( Noufu_Kikan >= 3. )
				{
					Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].ninzu
					 += Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];

					Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].kyufu
					 += Tanka_Shibou[sotai_nendo][Shibou_Kubun( nendo , Noufu_Kikan , Option )]
					     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];

					if( Noufu_Kikan_Fuka >= 3. )
					{
						Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].kyufu_fuka
						 += Tanka_Shibou_Fuka
						     * Hihokensha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka;
					}
				}

				Noufu_Kikan = Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].noufu;

				for( dankai = 1 ; dankai < MENJO_DANKAI ; dankai++ )
				{
					for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
					{
						Noufu_Kikan += Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
						                * Hokenryou_Wariai[dankai];
					}
				}

				if( Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka == 0. )
				{
					Noufu_Kikan_Fuka = 0.;
				}
				else
				{
					Noufu_Kikan_Fuka = Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].fuka
					                    / Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka;
				}

				if( Noufu_Kikan >= 3. )
				{
					Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].ninzu
					 += Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];

					Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].kyufu
					 += Tanka_Shibou[sotai_nendo][Shibou_Kubun( nendo , Noufu_Kikan , Option )]
					     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
					     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI];

					if( Noufu_Kikan_Fuka >= 3. )
					{
						Ichijikin_Nendomatu[sotai_nendo][nenrei - MIN_HIHO_NENREI].kyufu_fuka
						 += Tanka_Shibou_Fuka
						     * Taikisha_Shibou[nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI]
						     * Noufu_Jokyo[nenrei - MIN_HIHO_NENREI].fuka;
					}
				}

			}
		}
	}

	for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
	{
		Rorei_Shinki[jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Zero;

		if( Option == 1 )
		{
			Rorei_Shinki2[jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Zero;
		}
	}

	if( Kako_Saimu == 0 || Jyukyusha_Nomi == 0 || nendo <= Kugiri_Nendo )
	{
		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= 70 ; nenrei++ )
		{
			jukyu_nenrei = nenrei;
			seinendo = nendo - nenrei;

			for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
			{
				Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].ninzu
				 += Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

				Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].noufu
				 += Full_Pension[sotai_nendo][nenrei]
				     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
				     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].noufu
				     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
				     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

				for( dankai = ZENGAKU ; dankai <= MENJO_1_4 ; dankai++ )
				{
					for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
					{
						Rorei_Shinki[nenrei- MIN_ROREI_JUKYU].noufu
						 += Full_Pension[sotai_nendo][nenrei]
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Hokenryou_Wariai[dankai]
						     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
						     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

						Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
						 += Full_Pension[sotai_nendo][nenrei]
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Kokko_Wariai[kokko]
						     * ( 1. - Hokenryou_Wariai[dankai] )
						     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
						     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];
			 		}
				}

				Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].fuka
				 += Full_Pension_Fuka
				     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
				     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].fuka
				     * Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

				Taikisha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
				 *= ( 1. - Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU] );


				if( Option == 1 )
				{
					if( extendb( nendo , nenrei ) == 1 )
					{
						Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].ninzu
						 += Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

						Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].noufu
						 += Full_Pension[sotai_nendo][nenrei]
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].noufu
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
					  	     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

						for( dankai = ZENGAKU ; dankai <= MENJO_1_4 ; dankai++ )
						{
							for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
							{
								Rorei_Shinki[nenrei- MIN_ROREI_JUKYU].noufu
								 += Full_Pension[sotai_nendo][nenrei]
								     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
								     * Hokenryou_Wariai[dankai]
								     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

								Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
								 += Full_Pension[sotai_nendo][nenrei]
								     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
								     * Kokko_Wariai[kokko]
								     * ( 1. - Hokenryou_Wariai[dankai] )
								     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
								     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];
				 			}
						}

						Rorei_Shinki[nenrei - MIN_ROREI_JUKYU].fuka
						 += Full_Pension_Fuka
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].fuka
						     * Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						     * Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU];

						Hihokensha[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu
						 *= ( 1. - Hassei_Wariai_Rorei[sotai_nendo][jukyu_nenrei - MIN_ROREI_JUKYU] );
					}

					if( nenrei == 65 )
					{
						Rorei_Shinki2[nenrei - MIN_ROREI_JUKYU].ninzu
						 += Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

						Rorei_Shinki2[nenrei - MIN_ROREI_JUKYU].noufu
						 += Full_Pension[sotai_nendo][nenrei]
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].noufu
						     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
						     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

						for( dankai = ZENGAKU ; dankai <= MENJO_1_4 ; dankai++ )
						{
							for( kokko = 1 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
							{
								Rorei_Shinki2[nenrei- MIN_ROREI_JUKYU].noufu
								 += Full_Pension[sotai_nendo][nenrei]
								     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
								     * Hokenryou_Wariai[dankai]
								     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
							  	     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

								Rorei_Shinki2[nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
								 += Full_Pension[sotai_nendo][nenrei]
								     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
								     * Kokko_Wariai[kokko]
								     * ( 1. - Hokenryou_Wariai[dankai] )
								     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].menjo[dankai][kokko]
								     / Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
								     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;
					 		}
						}

						Rorei_Shinki2[nenrei - MIN_ROREI_JUKYU].fuka
						 += Full_Pension_Fuka
						     * Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][seibetu - 1]
						     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].fuka
						     * Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu;

						Hihokensha2[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan].ninzu = 0.;
					}
				}

			}
		}
	}

	for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
	{
		for( nenrei = MAX_ROREI_JUKYU ; nenrei >= MIN_ROREI_JUKYU + 1 ; nenrei-- )
		{
			Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] ) ,
					   Rorei_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			Rorei_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] ) ,
					   Rorei_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			Turo_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] ) ,
					   Turo_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			Gonen_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] ) ,
					   Gonen_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			Rorei_Ichibu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Rorei[sotai_nendo][nenrei - MIN_HIHO_NENREI] ) ,
					   Rorei_Ichibu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ) );

			seinendo =  nendo - nenrei;
			if( seinendo >= SUIKEISHONENDO - 64 && seinendo <= SUIKEISHONENDO - 60 && nenrei == 65 )
			{
				Rorei_Ichibu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = multiply( Rorei_Ichibu_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ,
					   Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )][jukyu_nenrei - MIN_ROREI_JUKYU] );
			}

			if( nenrei - jukyu_nenrei == 0 )
			{
				Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
				 = add( Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ,
					   Rorei_Shinki[jukyu_nenrei - MIN_ROREI_JUKYU] );
			}

			if( Option == 1 )
			{
				if( nenrei == 65 && jukyu_nenrei == 65 )
				{
					Rorei_Shinki2[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu = 0.;
					Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
					 = add( Rorei_Nendomatu[sotai_nendo][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] ,
						   Rorei_Shinki2[jukyu_nenrei - MIN_ROREI_JUKYU] );
				}
			}

		}

		if( jukyu_nenrei == MIN_ROREI_JUKYU )
		{
			Rorei_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Shinki[jukyu_nenrei - MIN_ROREI_JUKYU];
		}
		else
		{
			Rorei_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Zero;
		}

		Rorei_Ichibu_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU]
		 = Rorei_Zero;

		Rorei_Kyu_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
		 = Rorei_Kyu_Zero;

		Turo_Kyu_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
		 = Rorei_Kyu_Zero;

		Gonen_Nendomatu[sotai_nendo][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
		 = Gonen_Zero;

	}

	if( Option == 1 )
	{
		if( nendo >= OPTION_START && nendo <= OPTION_START + OP_HIKIAGE_KANKAKU * 4 )
		{
			for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
			{
				for( nenrei = MAX_SHOGAI_JUKYU ; nenrei >= MIN_SHOGAI_JUKYU + 1 ; nenrei-- )
				{
					Shogai_Ippan_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu].kihon
					 *= Nendomatu_Tyousei_Keisu( nendo , nenrei );

					Shogai_20mae_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu].kihon
					 *= Nendomatu_Tyousei_Keisu( nendo , nenrei );
				}
			}

			for( nenrei = MAX_IZOKU_TUMA_JUKYU ; nenrei >= MIN_IZOKU_TUMA_JUKYU + 1 ; nenrei-- )
			{
				Izoku_Tuma_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_TUMA_JUKYU].kihon
				 *= Nendomatu_Tyousei_Keisu( nendo , nenrei );
			}
			for( nenrei = MAX_IZOKU_OTTO_JUKYU ; nenrei >= MIN_IZOKU_OTTO_JUKYU + 1 ; nenrei-- )
			{
				Izoku_Otto_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_OTTO_JUKYU].kihon
				 *= Nendomatu_Tyousei_Keisu( nendo , nenrei );
			}
			for( nenrei = MAX_IZOKU_KO_JUKYU ; nenrei >= MIN_IZOKU_KO_JUKYU + 1 ; nenrei-- )
			{
				Izoku_Ko_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_KO_JUKYU].kihon
				 *= Nendomatu_Tyousei_Keisu( nendo , nenrei );
			}
		}
	}

	for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
	{
		for( nenrei = MAX_SHOGAI_JUKYU ; nenrei >= MIN_SHOGAI_JUKYU + 1 ; nenrei-- )
		{
			Shogai_Ippan_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
					   scalar( ( 1. - Shikkenritu_Ippan[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] ) ,
						   Shogai_Ippan_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu] ) ) ,
			        Shogai_Ippan_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu] );

			Shogai_20mae_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
					   scalar( ( 1. - Shikkenritu_20mae[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] ) ,
						   Shogai_20mae_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu] ) ) ,
			        Shogai_20mae_Shinki[nenrei - MIN_SHOGAI_JUKYU][tokyu]);

			Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Ippan[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] ) ,
					   Shogai_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu] ) );

			Shogai_Ippan_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].kakyu
			 = Shogai_Ippan_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
			    * ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
				     * Kakyu_Wariai_Ippan_12shi[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
				      * Kakyu_Wariai_Ippan_3shiiko[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] );

			Shogai_20mae_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].kakyu
			 = Shogai_20mae_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
			    * ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
				     * Kakyu_Wariai_20mae_12shi[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
				      * Kakyu_Wariai_20mae_3shiiko[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] );

			Temp_Shogai_Kyu_Nendomatu
			 = Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].ninzu
				* ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
				     * Kakyu_Wariai_Ippan_12shi[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
				      * Kakyu_Wariai_Ippan_3shiiko[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU] );

			Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].kakyu
			 = min( Temp_Shogai_Kyu_Nendomatu , 
				   Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].kakyu );

			if( Shogai_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu].kakyu == 0. )
			{
				Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].menjo_kakyu = 0.;
			}
			else
			{
				Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].menjo_kakyu
				 = Shogai_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU][tokyu].kakyu
				    * Shogai_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu].menjo_kakyu
				    / Shogai_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu].kakyu;
			}
		}

		Shogai_Ippan_Nendomatu[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu]
		 = Shogai_Ippan_Shinki[MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu];

		Shogai_20mae_Nendomatu[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu]
		 = Shogai_20mae_Shinki[MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu];

		Shogai_Kyu_Nendomatu[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu]
		 = Shogai_Zero;

		Shogai_Ippan_Nendomatu[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu].kakyu
		 = Shogai_Ippan_Shinki[MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu].ninzu
			* ( Kakyu_Tanka_12shi[sotai_nendo][MIN_SHOGAI_JUKYU]
			     * Kakyu_Wariai_Ippan_12shi[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU]
			   + Kakyu_Tanka_3shiiko[sotai_nendo][MIN_SHOGAI_JUKYU]
			      * Kakyu_Wariai_Ippan_3shiiko[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU] );

		Shogai_20mae_Nendomatu[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu].kakyu
		 = Shogai_20mae_Shinki[MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU][tokyu].ninzu
			* ( Kakyu_Tanka_12shi[sotai_nendo][MIN_SHOGAI_JUKYU]
			     * Kakyu_Wariai_20mae_12shi[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU]
			   + Kakyu_Tanka_3shiiko[sotai_nendo][MIN_SHOGAI_JUKYU]
			      * Kakyu_Wariai_20mae_3shiiko[sotai_nendo][MIN_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU] );
	}


	for( nenrei = MAX_IZOKU_TUMA_JUKYU ; nenrei >= MIN_IZOKU_TUMA_JUKYU + 1 ; nenrei-- )
	{
		Izoku_Tuma_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU]
		 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Tuma[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU] ) ,
					   Izoku_Tuma_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_TUMA_JUKYU] ) ) ,
		        Izoku_Tuma_Shinki[nenrei - MIN_IZOKU_TUMA_JUKYU] );

		Izoku_Tuma_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU].kakyu
		 = Izoku_Tuma_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU].ninzu
			* ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
			     * Kakyu_Wariai_Tuma_12shi[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU]
			   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
			      * Kakyu_Wariai_Tuma_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU] );
	}

	Izoku_Tuma_Nendomatu[sotai_nendo][MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU]
	 = Izoku_Tuma_Shinki[MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU];

	Izoku_Tuma_Nendomatu[sotai_nendo][MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU].kakyu
	 = Izoku_Tuma_Shinki[MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU].ninzu
		* ( Kakyu_Tanka_12shi[sotai_nendo][MIN_IZOKU_TUMA_JUKYU]
		     * Kakyu_Wariai_Tuma_12shi[sotai_nendo][MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU]
		   + Kakyu_Tanka_3shiiko[sotai_nendo][MIN_IZOKU_TUMA_JUKYU]
		      * Kakyu_Wariai_Tuma_3shiiko[sotai_nendo][MIN_IZOKU_TUMA_JUKYU - MIN_IZOKU_TUMA_JUKYU] );

	for( nenrei = MAX_IZOKU_OTTO_JUKYU ; nenrei >= MIN_IZOKU_OTTO_JUKYU + 1 ; nenrei-- )
	{
		Izoku_Otto_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
		 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Otto[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU] ) ,
					   Izoku_Otto_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_OTTO_JUKYU] ) ) ,
		        Izoku_Otto_Shinki[nenrei - MIN_IZOKU_OTTO_JUKYU] );

		Izoku_Otto_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU].kakyu
		 = Izoku_Otto_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU].ninzu
			* ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
			     * Kakyu_Wariai_Otto_12shi[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
			   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
			      * Kakyu_Wariai_Otto_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU] );
	}

	Izoku_Otto_Nendomatu[sotai_nendo][MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU]
	 = Izoku_Otto_Shinki[MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU];

	Izoku_Otto_Nendomatu[sotai_nendo][MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU].kakyu
	 = Izoku_Otto_Shinki[MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU].ninzu
		* ( Kakyu_Tanka_12shi[sotai_nendo][MIN_IZOKU_OTTO_JUKYU]
		     * Kakyu_Wariai_Otto_12shi[sotai_nendo][MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU]
		   + Kakyu_Tanka_3shiiko[sotai_nendo][MIN_IZOKU_OTTO_JUKYU]
		      * Kakyu_Wariai_Otto_3shiiko[sotai_nendo][MIN_IZOKU_OTTO_JUKYU - MIN_IZOKU_OTTO_JUKYU] );

	for( nenrei = MAX_IZOKU_KO_JUKYU ; nenrei >= MIN_IZOKU_KO_JUKYU + 1 ; nenrei-- )
	{
		Izoku_Ko_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU]
		 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] ,
				   scalar( ( 1. - Shikkenritu_Ko[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU] ) ,
					   Izoku_Ko_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_IZOKU_KO_JUKYU] ) ) ,
		        Izoku_Ko_Shinki[nenrei - MIN_IZOKU_KO_JUKYU] );

		Izoku_Ko_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU].kakyu
		 = Izoku_Ko_Nendomatu[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU].ninzu
			* ( Kakyu_Tanka_12shi[sotai_nendo][nenrei]
			     * Kakyu_Wariai_Ko_12shi[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU]
			   + Kakyu_Tanka_3shiiko[sotai_nendo][nenrei]
			      * Kakyu_Wariai_Ko_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU] );
	}

	Izoku_Ko_Nendomatu[sotai_nendo][MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU]
	 = Izoku_Ko_Shinki[MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU];

	Izoku_Ko_Nendomatu[sotai_nendo][MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU].kakyu
	 = Izoku_Ko_Shinki[MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU].ninzu
		* ( Kakyu_Tanka_12shi[sotai_nendo][MIN_IZOKU_KO_JUKYU]
		     * Kakyu_Wariai_Ko_12shi[sotai_nendo][MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU]
		   + Kakyu_Tanka_3shiiko[sotai_nendo][MIN_IZOKU_KO_JUKYU]
		      * Kakyu_Wariai_Ko_3shiiko[sotai_nendo][MIN_IZOKU_KO_JUKYU - MIN_IZOKU_KO_JUKYU] );

	for( nenrei = MAX_KAFU_JUKYU ; nenrei >= MIN_KAFU_JUKYU + 1 ; nenrei-- )
	{
		Kafu_Nendomatu[sotai_nendo][nenrei - MIN_KAFU_JUKYU]
		 = add( adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67] ,
				   scalar( ( 1. - Shikkenritu_Kafu[sotai_nendo][nenrei - MIN_KAFU_JUKYU] ) ,
					   Kafu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_KAFU_JUKYU] ) ) ,
		        Kafu_Shinki[nenrei - MIN_KAFU_JUKYU] );

		Kafu_Kyu_Nendomatu[sotai_nendo][nenrei - MIN_KAFU_JUKYU]
		 = adjustbenefit( kaiteiritu_tannen[nendo - ECON_SHONENDO][UNDER_67] ,
			   scalar( ( 1. - Shikkenritu_Kafu[sotai_nendo][nenrei - MIN_KAFU_JUKYU] ) ,
				   Kafu_Kyu_Nendomatu[sotai_nendo - 1][nenrei - 1 - MIN_KAFU_JUKYU] ) );
	}

	Kafu_Nendomatu[sotai_nendo][MIN_KAFU_JUKYU - MIN_KAFU_JUKYU] = Kafu_Shinki[MIN_KAFU_JUKYU - MIN_KAFU_JUKYU];
	Kafu_Kyu_Nendomatu[sotai_nendo][MIN_KAFU_JUKYU - MIN_KAFU_JUKYU] = Kafu_Zero;



	return;


}


int Shibou_Kubun( int nendo , double noufu_kikan , int option )
{
	int kubun;
	
	if( noufu_kikan < 15. )
	{
		kubun = 0;
	}
	else if( noufu_kikan < 20. )
	{
		kubun = 1;
	}
	else if( noufu_kikan < 25. )
	{
		kubun = 2;
	}
	else if( noufu_kikan < 30. )
	{
		kubun = 3;
	}
	else if( noufu_kikan < 35. )
	{
		kubun = 4;
	}
	else if( noufu_kikan < 40. )
	{
		kubun = 5;
	}
	else
	{
		if( option == 1 && nendo >= OPTION_START )
		{
			kubun = 6;
		}
		else
		{
			kubun = 5;
		}
	}


	return kubun;

}


double Nendomatu_Tyousei_Keisu( int nendo , int nenrei )
{
	double fraction ;


	if( nendo == OPTION_START && nenrei <= 60 )
	{
		fraction = 41 / 40.;
	}
	else if( nendo == OPTION_START + OP_HIKIAGE_KANKAKU && nenrei <= 61 )
	{
		fraction = 42 / 41.;
	}
	else if( nendo == OPTION_START + OP_HIKIAGE_KANKAKU * 2 && nenrei <= 62 )
	{
		fraction = 43 / 42.;
	}
	else if( nendo == OPTION_START + OP_HIKIAGE_KANKAKU * 3 && nenrei <= 63 )
	{
		fraction = 44 / 43.;
	}
	else if( nendo == OPTION_START + OP_HIKIAGE_KANKAKU * 4 && nenrei <= 64 )
	{
		fraction = 45 / 44.;
	}
	else
	{
		fraction = 1.;
	}

	return fraction;

}
