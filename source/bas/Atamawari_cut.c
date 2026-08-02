#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mcntl.h"
#include "mkisosu.h"
#include "mkiso.h"
#include "mecon.h"


#define SHIHARAIOKURE 2


void Atamawari_cut( int c_nendo )
{
	int nendo;
	int nenrei;
	int sotai_nendo;
	int counter;
	int shikyu_keitai;

	double Kyufu_Cut[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double Kyufu_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double Kyufu_Cut_Nendomatu_P[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double kokko_Cut[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double kokko_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double kokko_Cut_Nendomatu_P[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double Tokubetukokko_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double Tokubetukokko_Cut_Nendomatu_P[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI];
	double Ichijikin_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][3];
	double Kafu_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][4];


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				Kyufu_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				Kyufu_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				kokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				kokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				kokko_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				Tokubetukokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				Tokubetukokko_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
			}
			Kyoshutukin_Cut[sotai_nendo][nenrei - NENREI_SUM] = 0.;
			Kyoshutukin_Kokko_Cut[sotai_nendo][nenrei - NENREI_SUM] = 0.;
		}
	}

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kyufu_Nendomatu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];

				Kyufu_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kyufu_Nendomatu_P[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];

				kokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kokko_Nendomatu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];

				kokko_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kokko_Nendomatu_P[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];

				Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Tokubetukokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][SUM][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];

				Tokubetukokko_Cut_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Tokubetukokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][SUM][shikyu_keitai]
					* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO]
						[( shikyu_keitai == KAKYU ? UNDER_63 : nenrei ) - NENREI_SUM];
			}
		}
	}

	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		
		for( nenrei = UNDER_64 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				if( nenrei == UNDER_64 )
				{
					Kyufu_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Kyufu_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ ( Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - 1 - NENREI_SUM][shikyu_keitai]
							+ Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] )
						* ( 6. - SHIHARAIOKURE ) / 12.;

					kokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = kokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ ( kokko_Cut_Nendomatu[sotai_nendo][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						+ kokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] )
						* ( 6. - SHIHARAIOKURE ) / 12.;

					Tokubetukokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Tokubetukokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ ( Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - 1 - NENREI_SUM][shikyu_keitai]
							+ Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] )
						* ( 6. - SHIHARAIOKURE ) / 12.;
				}
				else if( nenrei <= 67 )
				{
					Kyufu_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Kyufu_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;

					kokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = kokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ kokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;

					Tokubetukokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Tokubetukokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
						+ Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;
				}
				else
				{
					Kyufu_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Kyufu_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE
							+ kaiteiritu_cut[nendo - ECON_SHONENDO]
								[( shikyu_keitai == KAKYU ? UNDER_67 : nenrei ) - UNDER_67] * 6. ) / 12.
						+ Kyufu_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;

					kokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = kokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE
							+ kaiteiritu_cut[nendo - ECON_SHONENDO]
								[( shikyu_keitai == KAKYU ? UNDER_67 : nenrei ) - UNDER_67] * 6. ) / 12.
						+ kokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;

					Tokubetukokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Tokubetukokko_Cut_Nendomatu_P[sotai_nendo - 1][nenrei - 1 - NENREI_SUM][shikyu_keitai]
						* ( SHIHARAIOKURE
							+ kaiteiritu_cut[nendo - ECON_SHONENDO]
								[( shikyu_keitai == KAKYU ? UNDER_67 : nenrei ) - UNDER_67] * 6. ) / 12.
						+ Tokubetukokko_Cut_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						* ( 6. - SHIHARAIOKURE ) / 12.;
				}

				Kyufu_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
				 += Kyufu_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

				kokko_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
				 += kokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

				Tokubetukokko_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
				 += Tokubetukokko_Cut[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];
			}
		}
    }


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		Kyoshutukin_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM]
		 = Kyufu_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
			* SanteiTaishou[KOKUNEN][sotai_nendo][SUM] / SanteiTaishou[SUM][sotai_nendo][SUM];

		Kyoshutukin_Kokko_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM]
		 = kokko_Cut[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
			* SanteiTaishou[KOKUNEN][sotai_nendo][SUM] / SanteiTaishou[SUM][sotai_nendo][SUM];
	}


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		Ichijikin_Cut_Nendomatu[sotai_nendo][NOUFU] = Ichijikin_Nendomatu[sotai_nendo][NOUFU];
		Ichijikin_Cut_Nendomatu[sotai_nendo][FUKA] = Ichijikin_Nendomatu[sotai_nendo][FUKA];

		Ichijikin_Cut_Nendomatu[sotai_nendo][SUM]
		 = Ichijikin_Cut_Nendomatu[sotai_nendo][NOUFU] + Ichijikin_Cut_Nendomatu[sotai_nendo][FUKA];

		for( counter = SUM ; counter <= OLD_MENJO ; counter++ )
		{
			Kafu_Cut_Nendomatu[nendo - SHONENDO][counter]
			 = Kafu_Nendomatu[sotai_nendo][counter]
				* cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO][UNDER_64 - NENREI_SUM];
		}
	}

	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		Ichijikin_Cut[sotai_nendo][NOUFU]
		 = Ichijikin_Cut_Nendomatu[sotai_nendo - 1][NOUFU] * ( SHIHARAIOKURE + 6. ) / 12.
			+ Ichijikin_Cut_Nendomatu[sotai_nendo][NOUFU] * ( 6. - SHIHARAIOKURE ) / 12.;

		Ichijikin_Cut[sotai_nendo][FUKA]
		 = Ichijikin_Cut_Nendomatu[sotai_nendo - 1][FUKA] * ( SHIHARAIOKURE + 6. ) / 12.
			+ Ichijikin_Cut_Nendomatu[sotai_nendo][FUKA] * ( 6. - SHIHARAIOKURE ) / 12.;

		Ichijikin_Cut[sotai_nendo][SUM]
		 = Ichijikin_Cut[sotai_nendo][NOUFU] + Ichijikin_Cut[sotai_nendo][FUKA];

		for( counter = SUM ; counter <= OLD_MENJO ; counter++ )
		{
			Kafu_Cut[sotai_nendo][counter]
			 = Kafu_Cut_Nendomatu[sotai_nendo - 1][counter]
				* ( SHIHARAIOKURE + kaiteiritu_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
				+ Kafu_Cut_Nendomatu[sotai_nendo][counter] * ( 6. - SHIHARAIOKURE ) / 12.;
		}
	}


	return;

}
