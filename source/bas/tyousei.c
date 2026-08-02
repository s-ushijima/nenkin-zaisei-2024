#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mkiso.h"
#include "mkisosu.h"
#include "mecon.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "option.h"

using namespace std;


void tyousei()
{
	int nendo;
	int nenrei;
	int c_nendo;
	int counter;

	double cut_ruiseki_a[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1];
	double cut_ruiseki_b[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1];
	double Kiso_Cut_Jisshitu[SAISHUNENDO - SHONENDO + 1];
	double Kiso_Cut[SAISHUNENDO - SHONENDO + 1];
	double Shishutu_Jisshitu[SAISHUNENDO - SHONENDO + 1];
	double Shishutu[SAISHUNENDO - SHONENDO + 1];


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Kiso_Cut_Jisshitu[nendo - SHONENDO] = 0.;
		Kiso_Cut[nendo - SHONENDO] = 0.;
		Shishutu_Jisshitu[nendo - SHONENDO] = 0.;
		Shishutu[nendo - SHONENDO] = 0.;
	}

	for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Tumitate[nendo - SHONENDO]
		 = Tumitate[nendo - 1 - SHONENDO] * interest_rate[nendo - ECON_SHONENDO]
		  + ( Hokenryou_y[nendo - SHONENDO] + Fuka_Hokenryou_y[nendo - SHONENDO]
		     + Kyoshutukin_Kokko[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
		     + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
		     + Yuushi_Saiken[nendo - SHONENDO]
			 + Kodomo_Noufukin[nendo - SHONENDO]
		     - Kyoshutukin[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
		     - Ichijikin[nendo - SHONENDO][NOUFU] - Ichijikin[nendo - SHONENDO][FUKA] * 3. / 4.
		     - Kafu[nendo - SHONENDO][NEW] - Kafu[nendo - SHONENDO][OLD_NOUFU]
		     - Fuka[nendo - SHONENDO][SUM] * 3. / 4.
		     - Fukushi[nendo - SHONENDO] )
		   * pow( interest_rate[nendo - ECON_SHONENDO] , 1. / 2. );
	}

	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			kaiteiritu_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67]
			 = kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67];
		}
	}

	for( c_nendo = C_NENDO + 1 ; c_nendo <= T_NENDO ; c_nendo++ )
	{

		for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			kaiteiritu_cut[c_nendo - ECON_SHONENDO][nenrei - UNDER_67]
			 = kaiteiritu[c_nendo - ECON_SHONENDO][nenrei - UNDER_67]
				/ pre_cut[c_nendo - ECON_SHONENDO][nenrei - UNDER_67];
		}

		Atamawari_cut( c_nendo );

		for( nendo = KAISHI1 ; nendo <= T_NENDO ; nendo++ )
		{
			Kiso_Cut_Jisshitu[nendo - SHONENDO]
			 = Kyoshutukin_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM]
			    - Kyoshutukin_Kokko_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM];

			Kiso_Cut[nendo - SHONENDO]
			 = Kyoshutukin_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM]
			    + Tokubetukokko_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM];

			Fukushi_Cut[nendo - SHONENDO] = Fukushi[nendo - SHONENDO];

			Shishutu_Jisshitu[nendo - SHONENDO]
			 = Kiso_Cut_Jisshitu[nendo - SHONENDO]
			    + Ichijikin_Cut[nendo - SHONENDO][NOUFU] + Ichijikin_Cut[nendo - SHONENDO][FUKA] * 3. / 4.
			    + Kafu_Cut[nendo - SHONENDO][NEW] + Kafu_Cut[nendo - SHONENDO][OLD_NOUFU]
			    + Fuka[nendo - SHONENDO][SUM] * 3. / 4.
			    + Fukushi[nendo - SHONENDO];

			Shishutu[nendo - SHONENDO]
			 = Kiso_Cut[nendo - SHONENDO]
				+ Ichijikin_Cut[nendo - SHONENDO][SUM]
				+ Kafu_Cut[nendo - SHONENDO][SUM]
				+ Fuka[nendo - SHONENDO][SUM]
				+ Fukushi[nendo - SHONENDO];

			Tumitate[nendo - SHONENDO]
			 = Tumitate[nendo - 1 - SHONENDO] * interest_rate[nendo - ECON_SHONENDO]
			  + ( Hokenryou_y[nendo - SHONENDO] + Fuka_Hokenryou_y[nendo - SHONENDO]
			     + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
			     + Yuushi_Saiken[nendo - SHONENDO]
			     + Kodomo_Noufukin[nendo - SHONENDO]
		         - Shishutu_Jisshitu[nendo - SHONENDO] )
		       * pow( interest_rate[nendo - ECON_SHONENDO] , 1. / 2. );
		}

		if( Tumitate[T_NENDO - 1 - SHONENDO] < Shishutu[T_NENDO - SHONENDO] * T_DOAI )
		{
			if( c_nendo >= T_NENDO )
			{
				cout << "調整できません" << endl;
				fprintf( fp_out[SETTEI] , "調整期間中に調整出来ず\n" );
				break;
			}
		}
		else if( c_nendo >= 2024 )
		{
			break;
		}
	}

	S_C_NENDO = c_nendo;
	cout << "マクロ経済スライド終了年度 " << S_C_NENDO << endl;


	if( S_C_NENDO > 2024 )
	{
		for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				cut_ruiseki_b[nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
				 = cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM];

				cut_ruiseki_a[nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
				 = cut_ruiseki[S_C_NENDO - 1 - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM];
			}
		}

		counter = 1;

		while( counter <= 128 )
		{
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
				{
					cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
					 = ( cut_ruiseki_a[nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
					      + cut_ruiseki_b[nendo - ECON_SHONENDO][nenrei - NENREI_SUM] ) / 2.;
				}
			}

			for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				kaiteiritu_cut[S_C_NENDO - ECON_SHONENDO][nenrei - UNDER_67]
				 = kaiteiritu[S_C_NENDO - ECON_SHONENDO][nenrei - UNDER_67]
				    * cut_ruiseki[S_C_NENDO - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][nenrei - NENREI_SUM]
				    / cut_ruiseki[S_C_NENDO - 1 - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][nenrei - NENREI_SUM];
			}

			Atamawari_cut( S_C_NENDO );

			for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				Kiso_Cut_Jisshitu[nendo - SHONENDO]
				 = Kyoshutukin_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM]
				    - Kyoshutukin_Kokko_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM];

				Kiso_Cut[nendo - SHONENDO]
				 = Kyoshutukin_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM]
				    + Tokubetukokko_Cut[nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM];

				Fukushi_Cut[nendo - SHONENDO] = Fukushi[nendo - SHONENDO];

				Shishutu_Jisshitu[nendo - SHONENDO]
				 = Kiso_Cut_Jisshitu[nendo - SHONENDO]
				    + Ichijikin_Cut[nendo - SHONENDO][NOUFU] + Ichijikin_Cut[nendo - SHONENDO][FUKA] * 3. / 4.
				    + Kafu_Cut[nendo - SHONENDO][NEW] + Kafu_Cut[nendo - SHONENDO][OLD_NOUFU]
				    + Fuka[nendo - SHONENDO][SUM] * 3. / 4.
				    + Fukushi[nendo - SHONENDO];

				Shishutu[nendo - SHONENDO]
				 = Kiso_Cut[nendo - SHONENDO] + Ichijikin_Cut[nendo - SHONENDO][0] + Kafu_Cut[nendo - SHONENDO][0]
				    + Fukushi[nendo - SHONENDO] + Fuka[nendo - SHONENDO][SUM];

				Tumitate[nendo - SHONENDO]
			 	 = Tumitate[nendo - 1 - SHONENDO] * interest_rate[nendo - ECON_SHONENDO]
				  + ( Hokenryou_y[nendo - SHONENDO] + Fuka_Hokenryou_y[nendo - SHONENDO]
				     + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
				     + Yuushi_Saiken[nendo - SHONENDO]
				     + Kodomo_Noufukin[nendo - SHONENDO]
				     - Shishutu_Jisshitu[nendo - SHONENDO] )
				   * pow( interest_rate[nendo - ECON_SHONENDO] , 1. / 2. );
			}

			if( Tumitate[T_NENDO - 1 - SHONENDO] < Shishutu[T_NENDO - SHONENDO] * T_DOAI )
			{
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
					{
						cut_ruiseki_a[nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
						 = cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM];
					}
				}
			}
			else
			{
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
					{
						cut_ruiseki_b[nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
						 = cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM];
					}
				}
			}
			counter++;
		}
	}


	printf( "最終カット率 %11.9e\n" , 
		cut_ruiseki[S_C_NENDO - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][UNDER_63 - NENREI_SUM] );

	printf( "代替率換算 %f％\n" , 
		MODEL_PENSION * cut_ruiseki[S_C_NENDO - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][UNDER_63 - NENREI_SUM]
		 / MODEL_WAGE * 100.0 );

	fprintf( fp_out[OUTPUT] , "%s-%s," , Version, Version_cut );
	fprintf( fp_out[OUTPUT] , "%f," , 
		MODEL_PENSION * cut_ruiseki[S_C_NENDO - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][UNDER_63 - NENREI_SUM]
		 / MODEL_WAGE * 100.0 );
	fprintf( fp_out[OUTPUT] , "%d," ,S_C_NENDO );


	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67]
			 = kaiteiritu_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67];
		}
	}


	return;

}
