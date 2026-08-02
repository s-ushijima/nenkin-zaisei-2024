#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mkiso.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mecon.h"
#include "mcntl.h"

using namespace std;


void read_file()
{
	#define SHIHARAIOKURE 2

	double buffer[DATA_MAX];
	double previous_buffer0;
	int nendo;
	int data_number;
	int nenrei;
	int counter;
	int sotai_nendo;


	for( nendo = FUKUSHI_NENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Fukushi[nendo - SHONENDO] = Fukushi[nendo - 1 - SHONENDO] * cpi_up[nendo - ECON_SHONENDO];
	}

	for( nendo = FUKUSHI_NENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Fukushi[nendo - SHONENDO] *= ( Hiho_Kokunen[nendo - SHONENDO] / Hiho_Kokunen[FUKUSHI_NENDO - SHONENDO] );
	}


	previous_buffer0 = -1000.;

	read_headder( fp_in[DOKUZI] );

	while( ( read_data( buffer , fp_in[DOKUZI] , &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) )
	{
		nendo = (int)(buffer[0]);
		if( nendo >= SHONENDO && nendo <= SAISHUNENDO )
		{
			Fuka_Ninzu[nendo - SHONENDO] = buffer[1];
			Fuka_Nendomatu[nendo - SHONENDO][NEW] = buffer[2];
			Fuka_Nendomatu[nendo - SHONENDO][OLD_ROREI] = buffer[3];
			Fuka_Nendomatu[nendo - SHONENDO][OLD_TURO] = buffer[4];

			Kafu_Nendomatu[nendo - SHONENDO][NEW] = buffer[5];
			Kafu_Nendomatu[nendo - SHONENDO][OLD_NOUFU] = buffer[6];
			Kafu_Nendomatu[nendo - SHONENDO][OLD_MENJO] = buffer[7];

			Ichijikin_Nendomatu[nendo - SHONENDO][NOUFU] = buffer[8];
			Ichijikin_Nendomatu[nendo - SHONENDO][FUKA] = buffer[9];
		}
		previous_buffer0 = buffer[0];
	}

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Fuka_Nendomatu[nendo - SHONENDO][SUM]
		 = Fuka_Nendomatu[nendo - SHONENDO][NEW]
		    + Fuka_Nendomatu[nendo - SHONENDO][OLD_ROREI]
		    + Fuka_Nendomatu[nendo - SHONENDO][OLD_TURO];

		Kafu_Nendomatu[nendo - SHONENDO][SUM]
		 = Kafu_Nendomatu[nendo - SHONENDO][NEW]
		    + Kafu_Nendomatu[nendo - SHONENDO][OLD_NOUFU]
		    + Kafu_Nendomatu[nendo - SHONENDO][OLD_MENJO];

		Ichijikin_Nendomatu[nendo - SHONENDO][SUM]
		 = Ichijikin_Nendomatu[nendo - SHONENDO][NOUFU]
		    + Ichijikin_Nendomatu[nendo - SHONENDO][FUKA];
	}

	fclose( fp_in[DOKUZI] );


	for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		Ichijikin[sotai_nendo][NOUFU]
		 = Ichijikin_Nendomatu[sotai_nendo - 1][NOUFU] * ( SHIHARAIOKURE + 6. ) / 12.
			+ Ichijikin_Nendomatu[sotai_nendo][NOUFU] * ( 6 - SHIHARAIOKURE ) / 12.;

		Ichijikin[sotai_nendo][FUKA]
		 = Ichijikin_Nendomatu[sotai_nendo - 1][FUKA] * ( SHIHARAIOKURE + 6 ) / 12.
			+ Ichijikin_Nendomatu[sotai_nendo][FUKA] * ( 6 - SHIHARAIOKURE ) / 12.;

		Ichijikin[sotai_nendo][SUM]
		 = Ichijikin[sotai_nendo][NOUFU] + Ichijikin[sotai_nendo][FUKA];

		for( counter = SUM ; counter <= OLD_MENJO ; counter++ )
		{
			Kafu[sotai_nendo][counter]
			 = Kafu_Nendomatu[sotai_nendo - 1][counter]
				* ( SHIHARAIOKURE + kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] * 6 ) / 12.
				+ Kafu_Nendomatu[sotai_nendo][counter] * ( 6 - SHIHARAIOKURE ) / 12.;
		}

		for( counter = SUM ; counter <= OLD_TURO ; counter++ )
		{
			Fuka[sotai_nendo][counter]
			 = Fuka_Nendomatu[sotai_nendo - 1][counter] * ( SHIHARAIOKURE + 6 ) / 12.
				+ Fuka_Nendomatu[sotai_nendo][counter] * ( 6 - SHIHARAIOKURE ) / 12.;
		}
	}



	previous_buffer0 = -1000.;

	while( ( read_data( buffer , fp_in[YUUSHI] , &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) )
	{
		nendo = (int)(buffer[0]);
		if( nendo >= SHONENDO && nendo <= SAISHUNENDO )
		{
			Yuushi_Saiken[nendo - SHONENDO] = buffer[1] * 1000000.;
		}
		previous_buffer0 = buffer[0];
	}

	fclose( fp_in[YUUSHI] );


	previous_buffer0 = -1000.;

	while( ( read_data( buffer , fp_in[HOKEN] , &data_number ) != EOF ) && ( buffer[0] > previous_buffer0 ) )
	{
		nendo = (int)( buffer[0] );
		if( nendo >= SHONENDO )
		{
			Hokenryou_m[nendo - SHONENDO][0] = buffer[1];
			Fuka_Hokenryou_m[nendo - SHONENDO] = buffer[2];
		}
		previous_buffer0 = buffer[0];
	}

	fclose( fp_in[HOKEN] );



	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Hokenryou_m[nendo - SHONENDO][1]
		 = Hokenryou_m[nendo - SHONENDO][0] * kakaku[nendo - ECON_SHONENDO];

		if( nendo <= MARUME_NENDO )
		{
			Hokenryou_m[nendo - SHONENDO][1] = Round( Hokenryou_m[nendo - SHONENDO][1] , 1 );
		}
	}

	for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		Hokenryou_y[nendo - SHONENDO]
		 = Hokenryou_m[nendo - 1 - SHONENDO][1]
			* ( SanteiTaishou[KOKUNEN][nendo - 1 - SHONENDO][1]
				- Sankyu_Taishou[nendo - 1 - SHONENDO] - Ikukyu_Taishou[nendo - 1 - SHONENDO] )
		  + Hokenryou_m[nendo - SHONENDO][1]
			* ( SanteiTaishou[KOKUNEN][nendo - SHONENDO][1]
				- Sankyu_Taishou[nendo - SHONENDO] - Ikukyu_Taishou[nendo - SHONENDO] ) * 11.;

		Kodomo_Noufukin[nendo - SHONENDO]
		 = Hokenryou_m[nendo - 1 - SHONENDO][1] * Ikukyu_Taishou[nendo - 1 - SHONENDO]
			+ Hokenryou_m[nendo - SHONENDO][1] * Ikukyu_Taishou[nendo - SHONENDO] * 11.;

		Fuka_Hokenryou_y[nendo - SHONENDO]
		 = Fuka_Hokenryou_m[nendo - 1 - SHONENDO] * Fuka_Ninzu[nendo - 1 - SHONENDO]
			+ Fuka_Hokenryou_m[nendo - SHONENDO] * Fuka_Ninzu[nendo - SHONENDO] * 11.;
	}



	return;

}
