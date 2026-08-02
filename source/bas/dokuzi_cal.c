#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mkisosu.h"
#include "mkiso.h"
#include "mecon.h"
#include "mcntl.h"


void dokuzi_cal()
{
	int nendo;
	int nenrei;
	int sotai_nendo;
	int counter;
	double Ichijikin_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][3];
	double Kafu_Cut_Nendomatu[SAISHUNENDO - SHONENDO + 1][4];

	#define SHIHARAIOKURE 2


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( counter = SUM ; counter <= FUKA ; counter++ )
		{
			Ichijikin_Cut_Nendomatu[nendo - SHONENDO][counter] = 0.;
		}
		for( counter = SUM ; counter <= OLD_MENJO ; counter++ )
		{
			Kafu_Cut_Nendomatu[nendo - SHONENDO][counter] = 0.;
		}
	}


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		Ichijikin_Cut_Nendomatu[sotai_nendo][NOUFU] = Ichijikin_Nendomatu[sotai_nendo][NOUFU];
		Ichijikin_Cut_Nendomatu[sotai_nendo][FUKA] = Ichijikin_Nendomatu[sotai_nendo][FUKA];

		for( counter = SUM ; counter <= OLD_MENJO ; counter++ )
		{
			Kafu_Cut_Nendomatu[nendo - SHONENDO][counter]
			 = Kafu_Nendomatu[sotai_nendo][counter] * Cut_ritu[sotai_nendo][UNDER_64 - UNDER_63];
		}
	}

	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67]
			 *= Cut_ritu[nendo - SHONENDO][nenrei - UNDER_63]
			    / Cut_ritu[nendo - 1 - SHONENDO][nenrei - 1 - UNDER_63];
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
				* ( SHIHARAIOKURE + kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6. ) / 12.
				+ Kafu_Cut_Nendomatu[sotai_nendo][counter] * ( 6. - SHIHARAIOKURE ) / 12.;
		}
	}


	return;

}
