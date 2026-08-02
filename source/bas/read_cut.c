#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mkisosu.h"

void read_cut()
{
	double buffer[100];
	int data_number;
	int nendo;
	int counter;
	int nenrei;
	int cutfile;
	double previous_buffer;

	previous_buffer = -1000.;

	cutfile = CUT;
	if( kako >= 1 ){
		cutfile = CUT_K;
	}

	while( ( read_data( buffer , fp_in[cutfile] , &data_number ) != EOF ) && ( buffer[0] > previous_buffer ) )
	{
		nendo = (int)( buffer[0] ) + 2000;
		if( nendo >= SHONENDO && nendo <= SAISHUNENDO )
		{
			for( nenrei = 1 ; nenrei <= MAX_JUKYU - UNDER_63 + 1 ; nenrei++ )
			{
				Cut_ritu[nendo - SHONENDO][nenrei - 1] = buffer[nenrei];
			}
		}
		previous_buffer = buffer[0];
	}

	for( counter = R_S_C_NENDO + 1 ; counter <= SAISHUNENDO ; counter++ )
	{
		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			if( nenrei <= UNDER_67 )
			{
				Cut_ritu[counter - SHONENDO][nenrei - UNDER_63]
				 = Cut_ritu[counter - 1 - SHONENDO][nenrei - UNDER_63];
			}
			else
			{
				Cut_ritu[counter - SHONENDO][nenrei - UNDER_63]
				 = Cut_ritu[counter - 1 - SHONENDO][nenrei - 1 - UNDER_63];
			}
		}
	}

	fclose( fp_in[CUT] );
	fclose( fp_in[CUT_K] );


	return;

}
