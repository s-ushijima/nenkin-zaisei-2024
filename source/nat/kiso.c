#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mkisoritu.h"
#include "mkisosu.h"
#include "option.h"

using namespace std;


void readkiso_error( int shurui );


void kiso( int shubetu )
{
	int nenrei;
	int nendo;
	int sotai_nendo;
	int counter;
	double buffer[BUFFER_MAX];
	int data_number;
	int dankai;
	int kokko;
	int tokyu;
	int seinendo;
	int jukyu_nenrei;
	double shikkenritu[MAX_ROREI_JUKYU - 0 + 1][4];
	double kyufu_temp[KURI_AGE_SAGE_SHIKYU_KUBUN][2];

	FILE *fp[14];


	for( counter = 0 ; counter <= 3 ; counter++ )
	{
		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			shikkenritu[nenrei - 0][counter] = 0.;
		}
	}

	switch( shubetu )
	{
		case 2 :
			for( counter = 0 ; counter < 13 ; counter++ )
			{
				fp[counter] = fp_in[KISO_1M + counter];
			}
			break;
		case 3 :
			for( counter = 0 ; counter < 3 ; counter++ )
			{
				fp[counter] = fp_in[KISO_3M + counter];
			}
			break;
		case 5 :
			for( counter = 0 ; counter < 13 ; counter++ )
			{
				fp[counter] = fp_in[KISO_1F + counter];
			}
			break;
		case 6 :
			for( counter = 0 ; counter < 4 ; counter++ )
			{
				fp[counter] = fp_in[KISO_3F + counter];
			}
			break;
		default :
			cout << "指定外のshubetu " << shubetu << " を読み込みました" << endl;
			exit(1);
	}

	for( sotai_nendo = 0 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			Saikanyuritu[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
		}
	}

	read_data( buffer , fp[0] , &data_number );
	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		if( read_data( buffer , fp[0] , &data_number ) != EOF && buffer[0] == 1 && buffer[1] == nenrei )
		{
			Dattairyoku_Gokei[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
		}
		else
		{
			readkiso_error(1);
		}
	}
	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		if( read_data( buffer , fp[0] , &data_number ) != EOF && buffer[0] == 2 && buffer[1] == nenrei )
		{
			Dattairyoku_Shibou[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
		}
		else
		{
			readkiso_error(2);
		}
	}

	for( nendo = SHONENDO + 1 ; nendo <= SHIKKENRITU_MAX ; nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( shubetu <= 3 )
			{
				Dattairyoku_Shibou[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Dattairyoku_Shibou[0][nenrei - MIN_HIHO_NENREI] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][0]
				    / q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][0];
			}
			else
			{
				Dattairyoku_Shibou[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Dattairyoku_Shibou[0][nenrei - MIN_HIHO_NENREI] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][1]
				    / q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][1];
			}

			Dattairyoku_Gokei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
			 = Dattairyoku_Gokei[0][nenrei - MIN_HIHO_NENREI]
			    - Dattairyoku_Shibou[0][nenrei - MIN_HIHO_NENREI]
			    + Dattairyoku_Shibou[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI];

			if( nenrei >= 65 || ( ( shubetu == 3 || shubetu == 6 ) && nenrei >= 60 ) )
			{
				Dattairyoku_Gokei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = 1.;
			}
		}
	}

	for( nendo = SHIKKENRITU_MAX + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			Dattairyoku_Shibou[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
			 = Dattairyoku_Shibou[SHIKKENRITU_MAX - SHONENDO][nenrei - MIN_HIHO_NENREI];

			Dattairyoku_Gokei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
			 = Dattairyoku_Gokei[SHIKKENRITU_MAX - SHONENDO][nenrei - MIN_HIHO_NENREI];
		}
	}

	if( Option == 1 )
	{
		for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MAX_HIHO_NENREI ; nenrei >= MIN_HIHO_NENREI ; nenrei-- )
			{
				if( extendb( nendo , nenrei ) == 1 )
				{
					Dattairyoku_Gokei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
					 = Dattairyoku_Gokei[nendo - SHONENDO][59 - MIN_HIHO_NENREI];
				}

				if( extendc( nendo , nenrei ) == 1 )
				{
					Dattairyoku_Gokei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
					 = Dattairyoku_Gokei[nendo - SHONENDO][60 - MIN_HIHO_NENREI];
				}
			}
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[1] , &data_number );
		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= 70 ; nenrei++ )
		{	
			if( read_data( buffer , fp[1] , &data_number ) != EOF && buffer[0] == 4 && buffer[1] == nenrei )
			{
				Hassei_Wariai_Rorei[0][nenrei - MIN_ROREI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(4);
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_ROREI_JUKYU ; nenrei <= 70 ; nenrei++ )
			{
				Hassei_Wariai_Rorei[sotai_nendo][nenrei - MIN_ROREI_JUKYU]
				 = Hassei_Wariai_Rorei[0][nenrei - MIN_ROREI_JUKYU];
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[2] , &data_number );
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp[2] , &data_number ) != EOF && buffer[0] == 5 && buffer[1] == nenrei )
			{
				Hasseiryoku_Shogai[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(5);
			}
		}
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp[2] , &data_number ) != EOF && buffer[0] == 6 && buffer[1] == nenrei )
			{
				Hassei_Wariai_20mae[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(6);
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hasseiryoku_Shogai[sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 = Hasseiryoku_Shogai[0][nenrei - MIN_HIHO_NENREI];

				Hassei_Wariai_20mae[sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_20mae[0][nenrei - MIN_HIHO_NENREI];
			}
		}

	}

	if( shubetu == 2)
	{
		read_data( buffer , fp[3] , &data_number );
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp[3] , &data_number ) != EOF && buffer[0] == 7 && buffer[1] == nenrei )
			{
				Hassei_Wariai_Tuma[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(7);
			}
		}

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp[3] , &data_number ) != EOF && buffer[0] == 8 && buffer[1] == nenrei )
			{
				Hassei_Wariai_Ko[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(8);
			}
		}

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			if( read_data( buffer , fp[3] , &data_number ) != EOF && buffer[0] == 9 && buffer[1] == nenrei )
			{
				Hassei_Wariai_Kafu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(9);
			}
		}

		for( nendo = SAISHUNENDO ; nendo >= SUIKEISHONENDO ; nendo-- )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Tuma[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_Tuma[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI]
				    * Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0]
				       / Izoku_Keinen[I_KEINEN_SHONENDO + 1 - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0];

				Hassei_Wariai_Ko[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_Ko[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI]
				    * Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0]
				       / Izoku_Keinen[I_KEINEN_SHONENDO + 1 - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0];

				Hassei_Wariai_Kafu[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_Kafu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI]
				    * Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0]
				       / Izoku_Keinen[I_KEINEN_SHONENDO + 1 - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][0];

				if( nendo <= TANSHUKU_NENDO - 1 && nenrei <= 44 )
				{
					Hassei_Wariai_Kafu[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = 0.;
				}

			}
		}

		for( sotai_nendo = 0 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
			}
		}

	}

	if( shubetu == 5 || shubetu == 6 )
	{
		if( shubetu == 5)
		{
			read_data( buffer , fp[3] , &data_number );
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				if( read_data( buffer , fp[3] , &data_number ) != EOF && buffer[0] == 7 && buffer[1] == nenrei )
				{
					Hassei_Wariai_Otto[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(7);
				}
			}
		}
		else
		{
			read_data( buffer , fp[1] , &data_number );
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				if( read_data( buffer , fp[1] , &data_number ) != EOF && buffer[0] == 7 && buffer[1] == nenrei )
				{
					Hassei_Wariai_Otto[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(7);
				}
			}
		}

		for( nendo = SAISHUNENDO ; nendo >= SUIKEISHONENDO ; nendo-- )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Otto[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_Otto[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI]
				    * Izoku_Keinen[nendo - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][1]
				    / Izoku_Keinen[I_KEINEN_SHONENDO + 1 - I_KEINEN_SHONENDO][nenrei - MIN_HIHO_NENREI][1];
			}
		}

		for( sotai_nendo = 0 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
				Hassei_Wariai_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
				Hassei_Wariai_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[4] , &data_number );
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{	
			if( read_data( buffer , fp[4] , &data_number ) != EOF && buffer[0] == 10 && buffer[1] == nenrei )
			{
				Hassei_Wariai_Shibou[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
			}
			else
			{
				readkiso_error(10);
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI]
				 = Hassei_Wariai_Shibou[0][nenrei - MIN_HIHO_NENREI];
			}
		}

	}
	else
	{
		for( sotai_nendo = 0 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Hassei_Wariai_Shibou[sotai_nendo][nenrei - MIN_HIHO_NENREI] = 0.;
			}
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[5] , &data_number );
		if( read_data( buffer , fp[5] , &data_number ) != EOF && buffer[0] == 11 )
		{
			Tokyu_Wariai_Ippan[0][1] = buffer[1];
			Tokyu_Wariai_Ippan[0][2] = 1. - buffer[1];
		}
		else
		{
			readkiso_error(11);
		}

		if( read_data( buffer , fp[5] , &data_number ) != EOF && buffer[0] == 12 )
		{
			Tokyu_Wariai_20mae[0][1] = buffer[1];
			Tokyu_Wariai_20mae[0][2] = 1. - buffer[1];
		}
		else
		{
			readkiso_error(12);
		}

		Tokyu_Wariai_Ippan[0][0] = 0.;
		Tokyu_Wariai_20mae[0][0] = 0.;

		for( counter = 0 ; counter < 3 ; counter++ )
		{
			for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
			{
				Tokyu_Wariai_Ippan[sotai_nendo][counter] = Tokyu_Wariai_Ippan[0][counter];
				Tokyu_Wariai_20mae[sotai_nendo][counter] = Tokyu_Wariai_20mae[0][counter];
			}
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[6] , &data_number );

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 13 && buffer[1] == nenrei )
			{
				Kakyu_Wariai_Ippan_12shi[0][nenrei - MIN_SHOGAI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(13);
			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 14 && buffer[1] == nenrei )
			{
				Kakyu_Wariai_Ippan_3shiiko[0][nenrei - MIN_SHOGAI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(14);
			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 15 && buffer[1] == nenrei )
			{
				Kakyu_Wariai_20mae_12shi[0][nenrei - MIN_SHOGAI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(15);
			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 16 && buffer[1] == nenrei )
			{
				Kakyu_Wariai_20mae_3shiiko[0][nenrei - MIN_SHOGAI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(16);
			}
		}

		if( shubetu == 2 )
		{
			for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 17 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Tuma_12shi[0][nenrei - MIN_IZOKU_TUMA_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(17);
				}
			}

			for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 18 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Tuma_3shiiko[0][nenrei - MIN_IZOKU_TUMA_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(18);
				}
			}

			for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 19 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Ko_12shi[0][nenrei - MIN_IZOKU_KO_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(19);
				}
			}

			for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 20 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Ko_3shiiko[0][nenrei - MIN_IZOKU_KO_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(20);
				}
			}

		}

		if( shubetu == 5 )
		{
			for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 17 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Otto_12shi[0][nenrei - MIN_IZOKU_OTTO_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(17);
				}
			}
			for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[6] , &data_number ) != EOF && buffer[0] == 18 && buffer[1] == nenrei )
				{
					Kakyu_Wariai_Otto_3shiiko[0][nenrei - MIN_IZOKU_OTTO_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(18);
				}
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
			{
				Kakyu_Wariai_Ippan_12shi[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				 = Kakyu_Wariai_Ippan_12shi[0][nenrei - MIN_SHOGAI_JUKYU];

				Kakyu_Wariai_Ippan_3shiiko[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				 = Kakyu_Wariai_Ippan_3shiiko[0][nenrei - MIN_SHOGAI_JUKYU];

				Kakyu_Wariai_20mae_12shi[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				 = Kakyu_Wariai_20mae_12shi[0][nenrei - MIN_SHOGAI_JUKYU];

				Kakyu_Wariai_20mae_3shiiko[sotai_nendo][nenrei - MIN_SHOGAI_JUKYU]
				 = Kakyu_Wariai_20mae_3shiiko[0][nenrei - MIN_SHOGAI_JUKYU];
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
			{
				Kakyu_Wariai_Tuma_12shi[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU]
				 = Kakyu_Wariai_Tuma_12shi[0][nenrei - MIN_IZOKU_TUMA_JUKYU];

				Kakyu_Wariai_Tuma_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU]
				 = Kakyu_Wariai_Tuma_3shiiko[0][nenrei - MIN_IZOKU_TUMA_JUKYU];
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
			{
				Kakyu_Wariai_Otto_12shi[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
				 = Kakyu_Wariai_Otto_12shi[0][nenrei - MIN_IZOKU_OTTO_JUKYU];

				Kakyu_Wariai_Otto_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
				 = Kakyu_Wariai_Otto_3shiiko[0][nenrei - MIN_IZOKU_OTTO_JUKYU];
			}
		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
			{
				Kakyu_Wariai_Ko_12shi[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU]
				 = Kakyu_Wariai_Ko_12shi[0][nenrei - MIN_IZOKU_KO_JUKYU];

				Kakyu_Wariai_Ko_3shiiko[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU]
				 = Kakyu_Wariai_Ko_3shiiko[0][nenrei - MIN_IZOKU_KO_JUKYU];
			}
		}
	}

	if( shubetu == 2 || shubetu == 5)
	{
		if( shubetu == 2 )
		{
			read_data( buffer , fp[7] , &data_number );

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{	
				if( read_data( buffer, fp[7] , &data_number ) != EOF && buffer[0] == 21 && buffer[1] == nenrei )
				{
					Sokan_Tuma[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(21);
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				if( read_data( buffer, fp[7] , &data_number ) != EOF && buffer[0] == 22 && buffer[1] == nenrei )
				{
					Sokan_Ko[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(22);
				}
			}

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				if( read_data( buffer, fp[7] , &data_number ) != EOF && buffer[0] == 23 && buffer[1] == nenrei )
				{
					Sokan_Kafu[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(23);
				}
			}

		}

		if( shubetu == 5 )
		{
			read_data( buffer , fp[7] , &data_number );

			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{	
				if( read_data( buffer, fp[7] , &data_number ) != EOF && buffer[0] == 21 && buffer[1] == nenrei )
				{
					Sokan_Otto[0][nenrei - MIN_HIHO_NENREI] = buffer[2];
				}
				else
				{
					readkiso_error(21);
				}
			}

		}

		for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
			{
				Sokan_Tuma[sotai_nendo][nenrei - MIN_HIHO_NENREI] = Sokan_Tuma[0][nenrei - MIN_HIHO_NENREI];
				Sokan_Otto[sotai_nendo][nenrei - MIN_HIHO_NENREI] = Sokan_Otto[0][nenrei - MIN_HIHO_NENREI];
				Sokan_Ko[sotai_nendo][nenrei - MIN_HIHO_NENREI] = Sokan_Ko[0][nenrei - MIN_HIHO_NENREI];
				Sokan_Kafu[sotai_nendo][nenrei - MIN_HIHO_NENREI] = Sokan_Kafu[0][nenrei - MIN_HIHO_NENREI];
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[8] , &data_number );

		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[8] , &data_number ) != EOF && buffer[0] == 24 && buffer[1] == nenrei )
			{
				shikkenritu[nenrei - 0][0] = buffer[2];
			}
			else
			{
				readkiso_error(24);
			}
		}

		for( nendo = SUIKEISHONENDO ; nendo <= SHIKKENRITU_MAX ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= 104 ; nenrei++ )
			{
				if( shubetu <= 3 )
				{
					Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
					 = shikkenritu[nenrei - 0][0] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][0]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][0] ) / 3. );
				}
				else
				{
					Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
					 = shikkenritu[nenrei - 0][0] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][1]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][1] ) / 3. );
				}
			}

			for( nenrei = 105 ; nenrei <= MAX_ROREI_JUKYU - 1 ; nenrei++ )
			{
				Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = shikkenritu[nenrei - 0][0]
				    * Shikkenritu_Rorei[nendo - SHONENDO][104 - MIN_HIHO_NENREI] / shikkenritu[104 - 0][0];
			}

			Shikkenritu_Rorei[nendo - SHONENDO][MAX_ROREI_JUKYU - MIN_HIHO_NENREI] = 1.;

		}

		for( nendo = SHIKKENRITU_MAX + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI]
				 = Shikkenritu_Rorei[SHIKKENRITU_MAX - SHONENDO][nenrei - MIN_HIHO_NENREI];
			}
		}

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				if( Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] > 1. )
				{
					Shikkenritu_Rorei[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = 1.;
				}
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[9] , &data_number );

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[9] , &data_number ) != EOF && buffer[0] == 25 && buffer[1] == nenrei )
			{
				shikkenritu[nenrei - 0][1] = buffer[2];
			}
			else
			{
				readkiso_error(25);
			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[9] , &data_number ) != EOF && buffer[0] == 26 && buffer[1] == nenrei )
			{
				shikkenritu[nenrei - 0][2] = buffer[2];
			}
			else
			{
				readkiso_error(26);
			}
		}

		for( nendo = SUIKEISHONENDO ; nendo <= SHIKKENRITU_MAX ; nendo++ )
		{
			for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= 104 ; nenrei++ )
			{
				if( shubetu <= 3 )
				{
					Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
					 = shikkenritu[nenrei - 0][1] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][0]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][0] ) / 3. );

					Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
					 = shikkenritu[nenrei - 0][2] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][0]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][0]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][0] ) / 3. );
				}
				else
				{
					Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
					 = shikkenritu[nenrei - 0][1] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][1]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][1] ) / 3. );

					Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
					 = shikkenritu[nenrei - 0][2] * q[nendo - SHIKKENRITU_MIN][nenrei - 0][1]
					    / ( ( q[LIFETABLE_NENDO - 1 - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO - SHIKKENRITU_MIN][nenrei - 0][1]
					          + q[LIFETABLE_NENDO + 1 - SHIKKENRITU_MIN][nenrei - 0][1] ) / 3. );
				}
			}

			for( nenrei = 105 ; nenrei <= MAX_SHOGAI_JUKYU - 1 ; nenrei++ )
			{
				Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
				 = shikkenritu[nenrei - 0][1]
				    * Shikkenritu_Ippan[nendo - SHONENDO][104 - MIN_SHOGAI_JUKYU] / shikkenritu[104 - 0][1];

				Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
				 = shikkenritu[nenrei - 0][2]
				    * Shikkenritu_20mae[nendo - SHONENDO][104 - MIN_SHOGAI_JUKYU] / shikkenritu[104 - 0][2];
			}

			Shikkenritu_Ippan[nendo - SHONENDO][MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU] = 1.;
			Shikkenritu_20mae[nendo - SHONENDO][MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU] = 1.;
		}

		for( nendo = SHIKKENRITU_MAX + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
			{
				Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
				 = Shikkenritu_Ippan[SHIKKENRITU_MAX - SHONENDO][nenrei - MIN_SHOGAI_JUKYU];

				Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU]
				 = Shikkenritu_20mae[SHIKKENRITU_MAX - SHONENDO][nenrei - MIN_SHOGAI_JUKYU];
			}
		}

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
			{
				if( Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU] > 1. )
				{
					Shikkenritu_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU] = 1.;
				}
				if( Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU] > 1. )
				{
					Shikkenritu_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU] = 1.;
				}
			}
		}

	}

	if( shubetu == 2 || shubetu == 5)
	{
		read_data( buffer , fp[10] , &data_number );

		if( shubetu == 2 )
		{
			for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[10] , &data_number ) != EOF && buffer[0] == 27 && buffer[1] == nenrei )
				{
					Shikkenritu_Tuma[0][nenrei - MIN_IZOKU_TUMA_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(27);
				}
			}
			Shikkenritu_Tuma[0][18 - MIN_IZOKU_TUMA_JUKYU] = Shikkenritu_Tuma[0][20 - MIN_IZOKU_TUMA_JUKYU];
			Shikkenritu_Tuma[0][19 - MIN_IZOKU_TUMA_JUKYU] = Shikkenritu_Tuma[0][20 - MIN_IZOKU_TUMA_JUKYU];

			for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[10] , &data_number ) != EOF && buffer[0] == 28 && buffer[1] == nenrei )
				{
					 Shikkenritu_Ko[0][nenrei - MIN_IZOKU_KO_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(28);
				}
			}

			for( nenrei = MIN_KAFU_JUKYU ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[10] , &data_number ) != EOF && buffer[0] == 29 && buffer[1] == nenrei )
				{
					Shikkenritu_Kafu[0][nenrei - MIN_KAFU_JUKYU] = buffer[2];
				}
				else
				{
					readkiso_error(29);
				}
			}

			for( sotai_nendo = 1 ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
			{
				for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
				{
					Shikkenritu_Tuma[sotai_nendo][nenrei - MIN_IZOKU_TUMA_JUKYU]
					 = Shikkenritu_Tuma[0][nenrei - MIN_IZOKU_TUMA_JUKYU];
				}

				for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
				{
					Shikkenritu_Ko[sotai_nendo][nenrei - MIN_IZOKU_KO_JUKYU]
					 = Shikkenritu_Ko[0][nenrei - MIN_IZOKU_KO_JUKYU];
				}

				for( nenrei = MIN_KAFU_JUKYU ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
				{
					Shikkenritu_Kafu[sotai_nendo][nenrei - MIN_KAFU_JUKYU]
					 = Shikkenritu_Kafu[0][nenrei - MIN_KAFU_JUKYU];
				}
			}

		}

		if( shubetu == 5 )
		{
			for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[10] , &data_number ) != EOF && buffer[0] == 27 && buffer[1] == nenrei )
				{
					shikkenritu[nenrei - 0][3] = buffer[2];
				}
				else
				{
					readkiso_error(27);
				}
			}

			for( sotai_nendo = 1 ; sotai_nendo <= 2014 + 19 - SHONENDO ; sotai_nendo++ )
			{
				for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
				{
					Shikkenritu_Otto[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
					 = ( ( 2014 + 19 - SHONENDO - sotai_nendo ) * shikkenritu[nenrei - 0][3]
					     + sotai_nendo * Shikkenritu_Tuma[0][nenrei - 2 - MIN_IZOKU_TUMA_JUKYU] )
					   / (double)( 2014 + 19 - SHONENDO );
				}
			}
			for( sotai_nendo = 2014 + 19 + 1 - SHONENDO ; sotai_nendo <= SAISHUNENDO - SHONENDO ; sotai_nendo++ )
			{
				for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
				{
					Shikkenritu_Otto[sotai_nendo][nenrei - MIN_IZOKU_OTTO_JUKYU]
					 = Shikkenritu_Otto[2014 + 19 - SHONENDO][nenrei - MIN_IZOKU_OTTO_JUKYU];
				}
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[11] , &data_number );

		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 301 && buffer[1] == nenrei )
			{
				Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].ninzu = buffer[2];
				Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu = buffer[3];
				for( dankai = 0 ; dankai <= 1 ; dankai++ )
				{
					for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
					{
						Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
						 = buffer[4];
					}
				}
				for( dankai = 2 ; dankai < MENJO_DANKAI ; dankai++ )
				{
					for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
					{
						Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
						 = buffer[5];
					}
				}
				Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae = buffer[6];
				Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].fuka = buffer[7];
			}
			else
			{
				readkiso_error(301);
			}
		}
	}
	else
	{
		read_data( buffer , fp[shubetu / 3] , &data_number );

		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[shubetu / 3] , &data_number ) != EOF && 
				buffer[0] == 301 && buffer[1] == nenrei )
			{
				Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu = buffer[2];
			}
			else
			{
				readkiso_error(301);
			}
		}
	}

	for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].ninzu
			 = Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].ninzu;

			Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu
			 = Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu;

			for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
				{
					Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
					 = Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko];
				}
			}

			Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].fuka
			 = Shikyuritu_Rorei[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].fuka;

			if( nenrei >= MIN_ROREI_JUKYU + 1 )
			{
				Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae
				 = Shikyuritu_Rorei[nendo - 1 - SHONENDO][nenrei - 1 - MIN_ROREI_JUKYU].rofuku_shitasasae;
			}
			else
			{
				Shikyuritu_Rorei[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae = 1.;
			}
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 302 && buffer[1] == nenrei )
			{
				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].ninzu = buffer[2];
				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu = buffer[3];
				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo = buffer[4];
				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].kasa_noufu = buffer[5];
				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].kasa_menjo = buffer[6];

				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae
				 = buffer[7];

				Shikyuritu_Rorei_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].fuka = buffer[8];
			}
			else
			{
				readkiso_error(302);
			}
		}

		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 303 && buffer[1] == nenrei )
			{
				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].ninzu = buffer[2];
				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].noufu = buffer[3];
				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].menjo = buffer[4];
				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].kasa_noufu = buffer[5];
				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].kasa_menjo = buffer[6];

				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae
				 = buffer[7];

				Shikyuritu_Turo_Kyu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU].fuka = buffer[8];
			}
			else
			{
				readkiso_error(303);
			}
		}

		for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_ROREI_JUKYU + 1 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				Shikyuritu_Rorei_Kyu[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU]
				 = Shikyuritu_Rorei_Kyu[nendo - 1 - SHONENDO][nenrei - 1 - MIN_ROREI_JUKYU];

				Shikyuritu_Turo_Kyu[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU]
				 = Shikyuritu_Turo_Kyu[nendo - 1 - SHONENDO][nenrei - 1 - MIN_ROREI_JUKYU];
			}

			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].ninzu = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].noufu = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].menjo = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].kasa_noufu = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].kasa_menjo = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].rofuku_shitasasae = 1.;
			Shikyuritu_Rorei_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].fuka = 1.;

			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].ninzu = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].noufu = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].menjo = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].kasa_noufu = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].kasa_menjo = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].rofuku_shitasasae = 1.;
			Shikyuritu_Turo_Kyu[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU].fuka = 1.;
		}

		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 304 && buffer[1] == nenrei )
			{
				Shikyuritu_Gonen[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU] = buffer[2];
			}
			else
			{
				readkiso_error(304);
			}
		}

		for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = MIN_ROREI_JUKYU + 1 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				Shikyuritu_Gonen[nendo - SHONENDO][nenrei - MIN_ROREI_JUKYU]
				 = Shikyuritu_Gonen[nendo - 1 - SHONENDO][nenrei - 1 - MIN_ROREI_JUKYU];
			}

			Shikyuritu_Gonen[nendo - SHONENDO][MIN_ROREI_JUKYU - MIN_ROREI_JUKYU] = 1.;
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 305 && buffer[1] == nenrei )
			{
				Shikyuritu_Shogai_Ippan[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][1] = buffer[4];
				Shikyuritu_Shogai_Ippan[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][2] = buffer[5];
				Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][1] = buffer[2];
				Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][2] = buffer[3];
			}
			else
			{
				readkiso_error(305);
			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 306 && buffer[1] == nenrei )
			{
				Shikyuritu_Shogai_20mae[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][1] = buffer[4];
				Shikyuritu_Shogai_20mae[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][2] = buffer[5];
				Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][1] = buffer[2];
				Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][2] = buffer[3];
			}
			else
			{
				readkiso_error(306);
			}
		}

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
			{
				for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= SUIKEISHONENDO - N_O_NENDO ; nenrei++ )
				{
					Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
				 	 = Shikyuritu_Shogai_Ippan[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];

					Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 = Shikyuritu_Shogai_20mae[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];

					if( shubetu == 2 )
					{
						if( ( nendo - nenrei == 1953 || nendo - nenrei == 1954 ) && 
							( nenrei >= 60 && nenrei <= 60 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1955 || nendo - nenrei == 1956 ) && 
							( nenrei >= 60 && nenrei <= 61 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1957 || nendo - nenrei == 1958 ) && 
							( nenrei >= 60 && nenrei <= 62 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1959 || nendo - nenrei == 1960 ) && 
							( nenrei >= 60 && nenrei <= 63 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( nendo - nenrei >= 1961 && ( nenrei >= 60 && nenrei <= 64 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
					}
					if( shubetu == 5 )
					{
						if( ( nendo - nenrei == 1958 || nendo - nenrei == 1959 ) && 
							( nenrei >= 60 && nenrei <= 60 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1960 || nendo - nenrei == 1961 ) && 
							( nenrei >= 60 && nenrei <= 61 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1962 || nendo - nenrei == 1963 ) && 
							( nenrei >= 60 && nenrei <= 62 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( ( nendo - nenrei == 1964 || nendo - nenrei == 1965 ) && 
							( nenrei >= 60 && nenrei <= 63 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
						if( nendo - nenrei >= 1966 && ( nenrei >= 60 && nenrei <= 64 ) )
						{
							Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
					 		= Shikyuritu_Shogai_Ippan_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
							Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
							 = Shikyuritu_Shogai_20mae_keinen[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						}
					}
				}

				for( nenrei = SUIKEISHONENDO - N_O_NENDO + 1 ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
				{
					if( nendo >= SHONENDO + 1 && nendo <= SUIKEISHONENDO )
					{
						Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_Ippan[nendo - 1 - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
						Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_20mae[nendo - 1 - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
					}
					if( nendo >= SUIKEISHONENDO + 1 )
					{
						Shikyuritu_Shogai_Ippan[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_Ippan[nendo - 1 - SHONENDO][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu];
						Shikyuritu_Shogai_20mae[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_20mae[nendo - 1 - SHONENDO][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu];
					}
				}

			}
		}

		for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 307 && buffer[1] == nenrei )
			{
				Shikyuritu_Shogai_Kyu[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][1] = buffer[2];
				Shikyuritu_Shogai_Kyu[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][2] = buffer[3];
			}
			else
			{
				readkiso_error(307);
			}
		}

		for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( tokyu = 1 ; tokyu <= 2 ; tokyu++ )
			{
				for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
				{
					if( nenrei == MIN_SHOGAI_JUKYU )
					{
						Shikyuritu_Shogai_Kyu[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu] = 1.;
					}
					else if( nenrei == 65 )
					{
						Shikyuritu_Shogai_Kyu[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_Kyu[SHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu];
					}
					else
					{
						Shikyuritu_Shogai_Kyu[nendo - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
						 = Shikyuritu_Shogai_Kyu[nendo - 1 - SHONENDO][nenrei - 1 - MIN_SHOGAI_JUKYU][tokyu];
					}
				}
			}
		}

	}

	if( shubetu == 2 || shubetu == 5 )
	{
		if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 308 && buffer[1] == 308 )
		{
			if( shubetu == 2 )
			{
				Shikyuritu_Tuma[SHONENDO - SHONENDO] = buffer[2];
				Shikyuritu_Ko[SHONENDO - SHONENDO] = buffer[3];
			}
			if( shubetu == 5 )
			{
				Shikyuritu_Otto[SHONENDO - SHONENDO] = buffer[2];
			}
		}
		else
		{
			readkiso_error(308);
		}

		if( shubetu == 2 )
		{
			for( nenrei = 60 ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[11] , &data_number ) != EOF && buffer[0] == 309 && buffer[1] == nenrei )
				{
					Shikyuritu_Kafu[SHONENDO - SHONENDO][nenrei - 60] = buffer[2];
				}
				else
				{
					readkiso_error(309);
				}
			}
		}

		for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			Shikyuritu_Tuma[nendo - SHONENDO] = Shikyuritu_Tuma[SHONENDO - SHONENDO];
			Shikyuritu_Otto[nendo - SHONENDO] = Shikyuritu_Otto[SHONENDO - SHONENDO];
			Shikyuritu_Ko[nendo - SHONENDO] = Shikyuritu_Ko[SHONENDO - SHONENDO];
		}

		for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = 60 ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
			{
				Shikyuritu_Kafu[nendo - SHONENDO][nenrei - 60] = Shikyuritu_Kafu[SHONENDO - SHONENDO][nenrei - 60];

				if( Option == 1 )
				{
					if( extendb( nendo , nenrei ) == 1 )
					{
						Shikyuritu_Kafu[nendo - SHONENDO][nenrei - 60] = 0.;
					}
				}
			}
		}

	}

 	for( seinendo = SUIKEISHONENDO - MAX_ROREI_JUKYU ; seinendo <= SUIKEISAISHUNENDO - MIN_ROREI_JUKYU ; seinendo++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
			Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
				[jukyu_nenrei - MIN_ROREI_JUKYU].ninzu
			 = 1.;

			Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
				[jukyu_nenrei - MIN_ROREI_JUKYU].noufu
			 = 1.;

			for( dankai = 0 ; dankai < MENJO_DANKAI ; dankai++ )
			{
				for( kokko = 0 ; kokko <= KOKKO_HIKIAGE - 1 ; kokko++ )
				{
					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[dankai][kokko]
					 = 1.;
				}
			}
			Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
				[jukyu_nenrei - MIN_ROREI_JUKYU].rofuku_shitasasae
			 = 1.;

			Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
				[jukyu_nenrei - MIN_ROREI_JUKYU].fuka
			 = 1.;
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[12] , &data_number );

		for( seinendo = SUIKEISHONENDO - 64 ; seinendo <= SUIKEISHONENDO - 60 ; seinendo++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 64 ; jukyu_nenrei++ )
			{
				if( read_data( buffer , fp[12] , &data_number ) != EOF && 
					buffer[0] == seinendo && buffer[1] == jukyu_nenrei )
				{
					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].noufu
					 = buffer[2];

					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[ZENGAKU][1]
					 = buffer[3];

					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[MENJO_3_4][1]
					 = buffer[4];

					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[MENJO_1_2][1]
					 = buffer[5];

					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].menjo[MENJO_1_4][1]
					 = buffer[6];

					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].fuka
					 = buffer[7];
				}
				else
				{
					readkiso_error(31);
				}
			}
		}
	}
	else
	{
		read_data( buffer , fp[( shubetu / 3 ) + 1] , &data_number );
		for( seinendo = SUIKEISHONENDO - 64 ; seinendo <= SUIKEISHONENDO - 60 ; seinendo++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 64 ; jukyu_nenrei++ )
			{
				if( read_data( buffer , fp[( shubetu / 3 ) + 1] , &data_number ) != EOF && 
					buffer[0] == seinendo && buffer[1] == jukyu_nenrei )
				{
					Kakudai_Ichibu[seinendo - ( SUIKEISHONENDO - MAX_ROREI_JUKYU )]
						[jukyu_nenrei - MIN_ROREI_JUKYU].noufu
					 = buffer[2];
				}
				else
				{
					readkiso_error(31);
				}
			}
		}
	}

	read_data( buffer , fp_in[WARIBIKI] , &data_number );
	if( shubetu == 2 )
	{
		for( counter = 0 ; counter <= 1 ; counter++ )
		{
			for( jukyu_nenrei = 66 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				for( nendo = SUIKEISHONENDO + 1 ; nendo <= SUIKEISHONENDO + 10 ; nendo++ )
				{
					if( read_data( buffer , fp_in[WARIBIKI] , &data_number ) != EOF && 
						buffer[0] == counter && buffer[1] == jukyu_nenrei && buffer[2] == nendo	)
					{
						Waribikiritu[counter][0][jukyu_nenrei - 66][nendo - SUIKEISHONENDO - 1] = buffer[3];
						Waribikiritu[counter][1][jukyu_nenrei - 66][nendo - SUIKEISHONENDO - 1] = buffer[4];
					}
					else
					{
						printf( "割引率ファイル読込途中にＥＯＦを検出しました\n" );
						exit( 1 );
					}
				}
			}
		}
	}

	read_data( buffer , fp_in[KYUFU] , &data_number );

	if( shubetu == 2 )
	{
		for( counter = 0 ; counter <= 1 ; counter++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				if( read_data( buffer , fp_in[KYUFU] , &data_number ) != EOF && 
					buffer[0] == counter && buffer[1] == jukyu_nenrei )
				{
					kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][counter] = buffer[2];
				}
				else
				{
					printf( "給付率ファイル読込途中にＥＯＦを検出しました\n" );
					exit( 1 );
				}
			}
		}

		for( seinendo = SUIKEISHONENDO - 70 ; seinendo <= SUIKEISAISHUNENDO - MIN_ROREI_JUKYU ; seinendo++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				if( seinendo < HenkouSeinendo )
				{
					Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];

					Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];

					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];

					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];

				}
				else
				{
					Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][1];

					Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][1];
				}
			}
		}
	}

	read_data( buffer , fp_in[KYUFU2] , &data_number );

	if( shubetu == 2 )
	{
		for( counter = 0 ; counter <= 1 ; counter++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				if( read_data( buffer , fp_in[KYUFU2] , &data_number ) != EOF && 
					buffer[0] == counter && buffer[1] == jukyu_nenrei )
				{
					kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][counter] = buffer[2];
				}
				else
				{
					printf( "給付率ファイル読込途中にＥＯＦを検出しました\n" );
					exit( 1 );
				}
			}
		}

		for( seinendo = SUIKEISHONENDO - 70 ; seinendo <= SUIKEISAISHUNENDO - MIN_ROREI_JUKYU ; seinendo++ )
		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				if( seinendo < HenkouSeinendo )
				{
					Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];

					Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][0];
				}
				else
				{
					Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][1];

					Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = kyufu_temp[jukyu_nenrei - MIN_ROREI_JUKYU][1];
				}
			}
		}
	}

	if( shubetu == 2 )
	{

		for( seinendo = SUIKEISHONENDO - 70 ; seinendo <= SUIKEISAISHUNENDO - MIN_ROREI_JUKYU ; seinendo++ )

		{
			for( jukyu_nenrei = 60 ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
			{
				if( seinendo >= 1962 )
				{
					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0];

					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = Kyufu_ritu2[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1];
				}
				else
				{
					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0]
					 = Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][0];

					Kyufu_ritu[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1]
					 = Kyufu_ritu1[jukyu_nenrei - MIN_ROREI_JUKYU][seinendo - ( SUIKEISHONENDO - 70 )][1];
				}
			}
		}
	}


	return;

}


void readkiso_error( int shurui )
{
	printf( "基礎率ファイル読み込み中にＥＯＦを検出しました。 基礎率種類は、%d\n" , shurui );
	exit(1);
}
