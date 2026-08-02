#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mfile_open.h"
#include "mecon.h"
#include "mkisosu.h"
#include "mcntl.h"


void file_write_cut()
{
	int nendo;
	int nenrei;
	double shutu;
	shutu = 1.0;

	for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			Cut_ritu[nendo - SHONENDO][nenrei - UNDER_63]
			 = cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM];
		}
	}

	for( nendo = 2005 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[CUTA] , "%4d," , nendo - 2000 );

		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
		{
			if( CUT_ONE_SHUTU == 1)
			{
				fprintf( fp_out[CUTA]  , "%20.14le," , shutu );
			}
			else
			{
				fprintf( fp_out[CUTA]  , "%20.14le," , 
					cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM] );
			}
		}

		if( CUT_ONE_SHUTU == 1 ){
			fprintf( fp_out[CUTA]  , "%20.14le\n" , shutu  );
		}
		else
		{
			fprintf( fp_out[CUTA]  , "%20.14le\n" , 
				cut_ruiseki[S_C_NENDO - ECON_SHONENDO][nendo - ECON_SHONENDO][MAX_JUKYU - NENREI_SUM] );
		}
	}

	fclose( fp_out[CUTA] );

}
