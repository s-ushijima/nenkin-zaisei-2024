#include <iostream>
#include "snaps.h"
#include "mseid.h"
#include "mcntl.h"
#include "option.h"


void seid( )
{
	int nendo;
	int nenrei;
	int seinendo;


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( seinendo = N_O_NENDO ; seinendo <= SAISHUNENDO ; seinendo++ )
		{
			if( seinendo <= 1941 )
			{
				Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO] = 25 + seinendo - N_O_NENDO;
			}
			else
			{
				Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO] = 40;
			}
		}

		if( Option == 1 && nendo >= OPTION_START )
		{
			for( seinendo = OPTION_START - 60 ; seinendo <= SAISHUNENDO ; seinendo++ )
			{
				Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO]
				 = 40 + min( encho_nensu( seinendo , 0 ) , encho_year( nendo ) );
			}
		}
	}


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( seinendo = N_O_NENDO ; seinendo <= SAISHUNENDO ; seinendo++ )
		{
			Full_Pension_Shonendo[nendo - SHONENDO][seinendo - N_O_NENDO] = 780900.;
		}

		if( Option == 1 && nendo >= OPTION_START )
		{
			for( seinendo = OPTION_START - 60 ; seinendo <= SAISHUNENDO ; seinendo++ )
			{
				Full_Pension_Shonendo[nendo - SHONENDO][seinendo - N_O_NENDO]
				 *= Kanou_Nensu[nendo - SHONENDO][seinendo - N_O_NENDO] / 40.;
			}
		}
	}


	Full_Pension_Fuka = 2400.;

	Kakyu_Tanka_12shi_Shonendo = 224700.;

	Kakyu_Tanka_3shiiko_Shonendo = 74900.;

	Tanka_Shibou_Shonendo[0]  = 120000.;
	Tanka_Shibou_Shonendo[1]  = 145000.;
	Tanka_Shibou_Shonendo[2]  = 170000.;
	Tanka_Shibou_Shonendo[3]  = 220000.;
	Tanka_Shibou_Shonendo[4]  = 270000.;
	Tanka_Shibou_Shonendo[5]  = 320000.;

	Tanka_Shibou_Shonendo[6]  = 320000.;
	if( Option == 1 )
	{
		Tanka_Shibou_Shonendo[6]  = 370000.;
	}

	Tanka_Shibou_Fuka = 8500.;

	Hokenryou_Wariai[SUM] = 0.;
	Hokenryou_Wariai[ZENGAKU] = 0.;
	Hokenryou_Wariai[MENJO_3_4] = 0.25;
	Hokenryou_Wariai[MENJO_1_2] = 0.5;
	Hokenryou_Wariai[MENJO_1_4] = 0.75;

	Shogai_Bairitu[0] = 0.;
	Shogai_Bairitu[1] = 1.25;
	Shogai_Bairitu[2] = 1.00;

	Kokko_Wariai[1] = 1. / 3.;
	Kokko_Wariai[2] = 1. / 2.;

}
