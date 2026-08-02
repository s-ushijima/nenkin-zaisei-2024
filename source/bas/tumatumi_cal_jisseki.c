#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mkisosu.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mecon.h"
#include "option.h"


void tumatumi_cal_jisseki()
{
	int nendo;
	int seido;
	int data_number;
	double buffer[DATA_MAX];


	for( nendo = TUMATUMI_NENDO ; nendo <= TUMATUMI_NENDO + TUMATUMI_KIKAN - 1 ; nendo++ )
	{
		if( nendo == TUMATUMI_NENDO )
		{
			Tumatumi[SUM][nendo - TUMATUMI_NENDO]
			 = Tumatumi_2014[SUM] - ( Tumatumi_2014[SUM] * 1. / TUMATUMI_KIKAN );
		}
		else
		{
			Tumatumi[SUM][nendo - TUMATUMI_NENDO]
			 = Tumatumi[SUM][nendo - 1 - TUMATUMI_NENDO] - ( Tumatumi_2014[SUM] * 1. / TUMATUMI_KIKAN );
		}
	}


	for( nendo = KAISHI1- 1 ; nendo <= TUMATUMI_NENDO + TUMATUMI_KIKAN - 1 ; nendo++ )
	{
		Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
		 = Tumatumi[BUNPAI][nendo - TUMATUMI_NENDO] / 2. 
		    * SanteiTaishou[KOKUNEN][nendo - SHONENDO][1] / SanteiTaishou[SUM][nendo - SHONENDO][SUM];

		for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
		{
			Tumatumi[seido][nendo - TUMATUMI_NENDO]
			 = Tumatumi[BUNPAI][nendo - TUMATUMI_NENDO] / 2.
			    * ( SanteiTaishou[seido][nendo - SHONENDO][SUM] / SanteiTaishou[SUM][nendo - SHONENDO][SUM]
			         + ( ( SanteiTaishou[seido][nendo - SHONENDO][2] + SanteiTaishou[seido][nendo - SHONENDO][3] )
			             / ( SanteiTaishou[SUM][nendo - SHONENDO][2] + SanteiTaishou[SUM][nendo - SHONENDO][3] ) ) );
		}
	}


	fprintf( fp_out[TUMATUMI_OUT] , "%d," , TUMATUMI_NENDO - 1 - 2000 );
	fprintf( fp_out[TUMATUMI_OUT] , "%20.14e," , 0. );
	for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
	{
		fprintf( fp_out[TUMATUMI_OUT] , "%20.14e," , 0. );
	}
	fprintf( fp_out[TUMATUMI_OUT] , "%20.14e\n" , Tumatumi_2014[SUM] );

	for( nendo = TUMATUMI_NENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[TUMATUMI_OUT] , "%d," , nendo - 2000 );
		for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
		{
			fprintf( fp_out[TUMATUMI_OUT] , "%20.14e," , Tumatumi[seido][nendo - TUMATUMI_NENDO] );
		}
		fprintf( fp_out[TUMATUMI_OUT] , "%20.14e\n" , Tumatumi[SUM][nendo - TUMATUMI_NENDO] );
	}
	fclose(fp_out[TUMATUMI_OUT]);

}
