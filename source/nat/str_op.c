#include <iostream>
#include "snaps.h"
#include "mkisoritu.h"
#include "mkisosu.h"
#include "mcntl.h"

#define SHIHARAIOKURE 2


struct hihokensha scalar( double scalar , struct hihokensha InputStruct )
{
	struct hihokensha OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.kikan = scalar * InputStruct.kikan;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko] = scalar * InputStruct.menjo[dankai][kokko];
		}
	}
	OutputStruct.gakusei = scalar * InputStruct.gakusei;
	OutputStruct.wakamono = scalar * InputStruct.wakamono;
	OutputStruct.fuka = scalar * InputStruct.fuka;
	
	return( OutputStruct );
}


struct hihokensha scalar_2( double scalar , struct hihokensha InputStruct , int nendo )
{
	struct hihokensha OutputStruct;
	int dankai;
	int kokko1;
	int kokko2;
	
	if( nendo <= TOKUTEI_NENDO )
	{
		kokko1 = 1;
		kokko2 = 2;
	}
	else
	{
		kokko1 = 2;
		kokko2 = 1;
	}

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.kikan = scalar * InputStruct.kikan;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		if( nendo == TOKUTEI_NENDO )
		{
			OutputStruct.menjo[dankai][kokko1]
			 = scalar * InputStruct.menjo[dankai][kokko1] * ( TOKUTEI_TUKI - 4 ) / 12.;

			OutputStruct.menjo[dankai][kokko2]
			 = scalar * InputStruct.menjo[dankai][kokko2] * ( 16 - TOKUTEI_TUKI ) / 12.;
		}
		else
		{
			OutputStruct.menjo[dankai][kokko1] = scalar * InputStruct.menjo[dankai][kokko1];
			OutputStruct.menjo[dankai][kokko2] = 0.;
		}
		OutputStruct.menjo[dankai][SUM] = OutputStruct.menjo[dankai][kokko1] + OutputStruct.menjo[dankai][kokko2];
	}
	OutputStruct.gakusei = scalar * InputStruct.gakusei;
	OutputStruct.wakamono = scalar * InputStruct.wakamono;
	OutputStruct.fuka = scalar * InputStruct.fuka;

	return( OutputStruct );
}


struct hihokensha add( struct hihokensha InputStruct1 , struct hihokensha InputStruct2 )
{
	struct hihokensha OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.kikan = InputStruct1.kikan + InputStruct2.kikan;
	OutputStruct.noufu = InputStruct1.noufu + InputStruct2.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = InputStruct1.menjo[dankai][kokko] + InputStruct2.menjo[dankai][kokko];
		}
	}
	OutputStruct.gakusei = InputStruct1.gakusei + InputStruct2.gakusei;
	OutputStruct.wakamono = InputStruct1.wakamono + InputStruct2.wakamono;
	OutputStruct.fuka = InputStruct1.fuka + InputStruct2.fuka;

	return( OutputStruct );
}


struct hihokensha average_by_ninzu( struct hihokensha InputStruct )
{
	struct hihokensha OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.kikan = (InputStruct.ninzu > 0.) ? InputStruct.kikan / InputStruct.ninzu : 0.;
	OutputStruct.noufu = (InputStruct.ninzu > 0.) ? InputStruct.noufu / InputStruct.ninzu : 0.;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = (InputStruct.ninzu > 0.) ? InputStruct.menjo[dankai][kokko] / InputStruct.ninzu : 0.;
		}
	}
	OutputStruct.gakusei = (InputStruct.ninzu > 0.) ? InputStruct.gakusei / InputStruct.ninzu : 0.;
	OutputStruct.wakamono = (InputStruct.ninzu > 0.) ? InputStruct.wakamono / InputStruct.ninzu : 0.;
	OutputStruct.fuka = (InputStruct.ninzu > 0.) ? InputStruct.fuka / InputStruct.ninzu : 0.;
	
	return( OutputStruct );
}


struct rorei scalar( double scalar , struct rorei InputStruct )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko] = scalar * InputStruct.menjo[dankai][kokko];
		}
	}
	OutputStruct.rofuku_shitasasae = scalar * InputStruct.rofuku_shitasasae;
	OutputStruct.fuka = scalar * InputStruct.fuka;

	return( OutputStruct );
}


struct rorei add( struct rorei InputStruct1 , struct rorei InputStruct2 )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu + InputStruct2.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = InputStruct1.menjo[dankai][kokko] + InputStruct2.menjo[dankai][kokko];
		}
	}
	OutputStruct.rofuku_shitasasae = InputStruct1.rofuku_shitasasae + InputStruct2.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct1.fuka + InputStruct2.fuka;

	return( OutputStruct );
}


struct rorei multiply( struct rorei InputStruct1 , struct rorei InputStruct2 )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct1.ninzu * InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu * InputStruct2.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = InputStruct1.menjo[dankai][kokko] * InputStruct2.menjo[dankai][kokko];
		}
	}
	OutputStruct.rofuku_shitasasae = InputStruct1.rofuku_shitasasae * InputStruct2.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct1.fuka * InputStruct2.fuka;

	return( OutputStruct );
}


struct rorei nendokan( struct rorei InputStruct1 , struct rorei InputStruct2 , double kaiteiritu )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.noufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = ( InputStruct1.menjo[dankai][kokko] * ( SHIHARAIOKURE + 6. * kaiteiritu )
				 + InputStruct2.menjo[dankai][kokko] * ( 6. - SHIHARAIOKURE ) ) / 12.;
		}
	}

	OutputStruct.rofuku_shitasasae
	 = ( InputStruct1.rofuku_shitasasae * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.rofuku_shitasasae * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.fuka
	 = ( InputStruct1.fuka * ( SHIHARAIOKURE + 6. ) + InputStruct2.fuka * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct rorei nendokan_64( struct rorei InputStruct1 , struct rorei InputStruct2 , 
	struct rorei InputStruct3 , double kaiteiritu )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2.;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.noufu + InputStruct3.noufu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = ( InputStruct1.menjo[dankai][kokko] * ( SHIHARAIOKURE + 6. * kaiteiritu )
				 + ( InputStruct2.menjo[dankai][kokko] + InputStruct3.menjo[dankai][kokko] )
					 * ( 6. - SHIHARAIOKURE ) ) / 12.;
		}
	}

	OutputStruct.rofuku_shitasasae
	 = ( InputStruct1.rofuku_shitasasae * ( SHIHARAIOKURE + 6. * kaiteiritu )
	      + ( InputStruct2.rofuku_shitasasae + InputStruct3.rofuku_shitasasae ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.fuka
	 = ( InputStruct1.fuka * ( SHIHARAIOKURE + 6. )
		 + ( InputStruct2.fuka + InputStruct3.fuka ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct rorei adjustbenefit( double scalar , struct rorei InputStruct )
{
	struct rorei OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko] = scalar * InputStruct.menjo[dankai][kokko];
		}
	}
	OutputStruct.rofuku_shitasasae = scalar * InputStruct.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct.fuka;

	return( OutputStruct );
}


struct rorei_kyu scalar( double scalar , struct rorei_kyu InputStruct )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	OutputStruct.menjo = scalar * InputStruct.menjo;
	OutputStruct.kasa_noufu = scalar * InputStruct.kasa_noufu;
	OutputStruct.kasa_menjo = scalar * InputStruct.kasa_menjo;
	OutputStruct.rofuku_shitasasae = scalar * InputStruct.rofuku_shitasasae;
	OutputStruct.fuka = scalar * InputStruct.fuka;

	return( OutputStruct );
}


struct rorei_kyu add( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu + InputStruct2.noufu;
	OutputStruct.menjo = InputStruct1.menjo + InputStruct2.menjo;
	OutputStruct.kasa_noufu = InputStruct1.kasa_noufu + InputStruct2.kasa_noufu;
	OutputStruct.kasa_menjo = InputStruct1.kasa_menjo + InputStruct2.kasa_menjo;
	OutputStruct.rofuku_shitasasae = InputStruct1.rofuku_shitasasae + InputStruct2.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct1.fuka + InputStruct2.fuka;

	return( OutputStruct );
}


struct rorei_kyu multiply( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu * InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu * InputStruct2.noufu;
	OutputStruct.menjo = InputStruct1.menjo * InputStruct2.menjo;
	OutputStruct.kasa_noufu = InputStruct1.kasa_noufu * InputStruct2.kasa_noufu;
	OutputStruct.kasa_menjo = InputStruct1.kasa_menjo * InputStruct2.kasa_menjo;
	OutputStruct.rofuku_shitasasae = InputStruct1.rofuku_shitasasae * InputStruct2.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct1.fuka * InputStruct2.fuka;

	return( OutputStruct );
}


struct rorei_kyu nendokan( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 , double kaiteiritu )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.noufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo
	 = ( InputStruct1.menjo * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.menjo * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kasa_noufu
	 = ( InputStruct1.kasa_noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.kasa_noufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kasa_menjo
	 = ( InputStruct1.kasa_menjo * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.kasa_menjo * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.rofuku_shitasasae
	 = ( InputStruct1.rofuku_shitasasae * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.rofuku_shitasasae * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.fuka
	 = ( InputStruct1.fuka * ( SHIHARAIOKURE + 6. ) + InputStruct2.fuka * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct rorei_kyu nendokan_64( struct rorei_kyu InputStruct1 , struct rorei_kyu InputStruct2 , 
	struct rorei_kyu InputStruct3 , double kaiteiritu )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2.;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.noufu + InputStruct3.noufu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo
	 = ( InputStruct1.menjo * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.menjo + InputStruct3.menjo ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kasa_noufu
	 = ( InputStruct1.kasa_noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kasa_noufu + InputStruct3.kasa_noufu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kasa_menjo
	 = ( InputStruct1.kasa_menjo * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kasa_menjo + InputStruct3.kasa_menjo ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.rofuku_shitasasae
	 = ( InputStruct1.rofuku_shitasasae * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.rofuku_shitasasae + InputStruct3.rofuku_shitasasae ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.fuka
	 = ( InputStruct1.fuka * ( SHIHARAIOKURE + 6. )
		 + ( InputStruct2.fuka + InputStruct3.fuka ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct rorei_kyu adjustbenefit( double scalar , struct rorei_kyu InputStruct )
{
	struct rorei_kyu OutputStruct;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	OutputStruct.menjo = scalar * InputStruct.menjo;
	OutputStruct.kasa_noufu = scalar * InputStruct.kasa_noufu;
	OutputStruct.kasa_menjo = scalar * InputStruct.kasa_menjo;
	OutputStruct.rofuku_shitasasae = scalar * InputStruct.rofuku_shitasasae;
	OutputStruct.fuka = InputStruct.fuka;

	return( OutputStruct );
}


struct gonen scalar( double scalar , struct gonen InputStruct )
{
	struct gonen OutputStruct;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;

	return( OutputStruct );
}


struct gonen add( struct gonen InputStruct1 , struct gonen InputStruct2 )
{
	struct gonen OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu + InputStruct2.noufu;
	
	return( OutputStruct );
}


struct gonen nendokan( struct gonen InputStruct1 , struct gonen InputStruct2 , double kaiteiritu )
{
	struct gonen OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2. ;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.noufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct gonen nendokan_64( struct gonen InputStruct1 , struct gonen InputStruct2 , 
	struct gonen InputStruct3 , double kaiteiritu )
{
	struct gonen OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2. ;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.noufu + InputStruct3.noufu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct gonen adjustbenefit( double scalar , struct gonen InputStruct )
{
	struct gonen OutputStruct;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;

	return( OutputStruct );
}


struct shogai scalar( double scalar , struct shogai InputStruct )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.kihon = scalar * InputStruct.kihon;
	OutputStruct.kakyu = scalar * InputStruct.kakyu;
	OutputStruct.menjo_kihon = scalar * InputStruct.menjo_kihon;
	OutputStruct.menjo_kakyu = scalar * InputStruct.menjo_kakyu;

	return( OutputStruct );
}


struct shogai add( struct shogai InputStruct1 , struct shogai InputStruct2 )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.kihon = InputStruct1.kihon + InputStruct2.kihon;
	OutputStruct.kakyu = InputStruct1.kakyu + InputStruct2.kakyu;
	OutputStruct.menjo_kihon = InputStruct1.menjo_kihon + InputStruct2.menjo_kihon;
	OutputStruct.menjo_kakyu = InputStruct1.menjo_kakyu + InputStruct2.menjo_kakyu;

	return( OutputStruct );
}


struct shogai multiply( struct shogai InputStruct1 , struct shogai InputStruct2 )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu * InputStruct2.ninzu;
	OutputStruct.kihon = InputStruct1.kihon * InputStruct2.kihon;
	OutputStruct.kakyu = InputStruct1.kakyu * InputStruct2.kakyu;
	OutputStruct.menjo_kihon = InputStruct1.menjo_kihon * InputStruct2.menjo_kihon;
	OutputStruct.menjo_kakyu = InputStruct1.menjo_kakyu * InputStruct2.menjo_kakyu;

	return( OutputStruct );
}


struct shogai nendokan( struct shogai InputStruct1 , struct shogai InputStruct2 , 
	double kaiteiritu1 , double kaiteiritu2 )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;

	OutputStruct.kihon
	 = ( InputStruct1.kihon * ( SHIHARAIOKURE + 6. * kaiteiritu1 )
		 + InputStruct2.kihon * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kakyu
	 = ( InputStruct1.kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu2 )
		 + InputStruct2.kakyu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo_kihon
	 = ( InputStruct1.menjo_kihon * ( SHIHARAIOKURE + 6. * kaiteiritu1 )
		 + InputStruct2.menjo_kihon * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo_kakyu
	 = ( InputStruct1.menjo_kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu2 )
		 + InputStruct2.menjo_kakyu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct shogai nendokan_64( struct shogai InputStruct1 , struct shogai InputStruct2 , 
	struct shogai InputStruct3 , double kaiteiritu )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2.;

	OutputStruct.kihon
	 = ( InputStruct1.kihon * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kihon + InputStruct3.kihon ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kakyu
	 = ( InputStruct1.kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kakyu + InputStruct3.kakyu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo_kihon
	 = ( InputStruct1.menjo_kihon * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.menjo_kihon + InputStruct3.menjo_kihon ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.menjo_kakyu
	 = ( InputStruct1.menjo_kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.menjo_kakyu + InputStruct3.menjo_kakyu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct shogai adjustbenefit( double scalar , struct shogai InputStruct )
{
	struct shogai OutputStruct;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.kihon = scalar * InputStruct.kihon;
	OutputStruct.kakyu = scalar * InputStruct.kakyu;
	OutputStruct.menjo_kihon = scalar * InputStruct.menjo_kihon;
	OutputStruct.menjo_kakyu = scalar * InputStruct.menjo_kakyu;

	return( OutputStruct );
}


struct izoku scalar( double scalar , struct izoku InputStruct )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.kihon = scalar * InputStruct.kihon;
	OutputStruct.kakyu = scalar * InputStruct.kakyu;

	return( OutputStruct );
}


struct izoku add( struct izoku InputStruct1 , struct izoku InputStruct2 )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.kihon = InputStruct1.kihon + InputStruct2.kihon;
	OutputStruct.kakyu = InputStruct1.kakyu + InputStruct2.kakyu;

	return( OutputStruct );
}


struct izoku multiply( struct izoku InputStruct1 , struct izoku InputStruct2 )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu * InputStruct2.ninzu;
	OutputStruct.kihon = InputStruct1.kihon * InputStruct2.kihon;
	OutputStruct.kakyu = InputStruct1.kakyu * InputStruct2.kakyu;

	return( OutputStruct );
}


struct izoku nendokan( struct izoku InputStruct1 , struct izoku InputStruct2 , 
	double kaiteiritu1 , double kaiteiritu2 )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;

	OutputStruct.kihon
	 = ( InputStruct1.kihon * ( SHIHARAIOKURE + 6. * kaiteiritu1 )
		 + InputStruct2.kihon * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kakyu
	 = ( InputStruct1.kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu2 )
		 + InputStruct2.kakyu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct izoku nendokan_64( struct izoku InputStruct1 , struct izoku InputStruct2 , 
	struct izoku InputStruct3 , double kaiteiritu )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2.;

	OutputStruct.kihon
	 = ( InputStruct1.kihon * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kihon + InputStruct3.kihon ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kakyu
	 = ( InputStruct1.kakyu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kakyu + InputStruct3.kakyu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct izoku adjustbenefit( double scalar , struct izoku InputStruct )
{
	struct izoku OutputStruct;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.kihon = scalar * InputStruct.kihon;
	OutputStruct.kakyu = scalar * InputStruct.kakyu;

	return( OutputStruct );
}


struct kafu scalar( double scalar , struct kafu InputStruct )
{
	struct kafu OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = scalar * InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko] = scalar * InputStruct.menjo[dankai][kokko];
		}
	}

	return( OutputStruct );
}


struct kafu add( struct kafu InputStruct1, struct kafu InputStruct2 )
{
	struct kafu OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu + InputStruct2.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = InputStruct1.menjo[dankai][kokko] + InputStruct2.menjo[dankai][kokko];
		}
	}

	return( OutputStruct );
}


struct kafu multiply( struct kafu InputStruct1 , struct kafu InputStruct2 )
{
	struct kafu OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct1.ninzu * InputStruct2.ninzu;
	OutputStruct.noufu = InputStruct1.noufu * InputStruct2.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = InputStruct1.menjo[dankai][kokko] * InputStruct2.menjo[dankai][kokko];
		}
	}

	return( OutputStruct );
}


struct kafu nendokan( struct kafu InputStruct1, struct kafu InputStruct2 , double kaiteiritu )
{
	struct kafu OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;

	OutputStruct.noufu
	 = ( InputStruct1.noufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.noufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko]
			 = ( InputStruct1.menjo[dankai][kokko] * ( SHIHARAIOKURE + 6. * kaiteiritu )
				 + InputStruct2.menjo[dankai][kokko] * ( 6. - SHIHARAIOKURE ) ) / 12.;
		}
	}

	return( OutputStruct );
}


struct kafu adjustbenefit( double scalar, struct kafu InputStruct )
{
	struct kafu OutputStruct;
	int dankai;
	int kokko;

	OutputStruct.ninzu = InputStruct.ninzu;
	OutputStruct.noufu = scalar * InputStruct.noufu;
	for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
	{
		for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
		{
			OutputStruct.menjo[dankai][kokko] = scalar * InputStruct.menjo[dankai][kokko];
		}
	}

	return( OutputStruct );
}


struct ichijikin add( struct ichijikin InputStruct1, struct ichijikin InputStruct2 )
{
	struct ichijikin OutputStruct;

	OutputStruct.ninzu = InputStruct1.ninzu + InputStruct2.ninzu;
	OutputStruct.kyufu = InputStruct1.kyufu + InputStruct2.kyufu;
	OutputStruct.kyufu_fuka = InputStruct1.kyufu_fuka + InputStruct2.kyufu_fuka;

	return( OutputStruct );
}


struct ichijikin nendokan( struct ichijikin InputStruct1 , struct ichijikin InputStruct2 , double kaiteiritu )
{
	struct ichijikin OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu ) / 2.;
	OutputStruct.kyufu
	 = ( InputStruct1.kyufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + InputStruct2.kyufu * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kyufu_fuka
	 = ( InputStruct1.kyufu_fuka * ( SHIHARAIOKURE + 6. )
		 + InputStruct2.kyufu_fuka * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}


struct ichijikin nendokan_64( struct ichijikin InputStruct1 , struct ichijikin InputStruct2 , 
	struct ichijikin InputStruct3 , double kaiteiritu )
{
	struct ichijikin OutputStruct;

	OutputStruct.ninzu = ( InputStruct1.ninzu + InputStruct2.ninzu + InputStruct3.ninzu ) / 2.;

	OutputStruct.kyufu
	 = ( InputStruct1.kyufu * ( SHIHARAIOKURE + 6. * kaiteiritu )
		 + ( InputStruct2.kyufu + InputStruct3.kyufu ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	OutputStruct.kyufu_fuka
	 = ( InputStruct1.kyufu_fuka * ( SHIHARAIOKURE + 6. )
		 + ( InputStruct2.kyufu_fuka + InputStruct3.kyufu_fuka ) * ( 6. - SHIHARAIOKURE ) ) / 12.;

	return( OutputStruct );
}
