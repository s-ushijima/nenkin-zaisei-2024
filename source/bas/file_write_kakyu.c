#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "mecon.h"
#include "option.h"


void file_write_kakyu()
{
	int nendo;
	int seido;
	int sotai_nendo;
	int nenrei;
	int shikyu_keitai;

	write_BeginData( fp_out[KYOSHUTUKIN] );

	for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
	{
		fprintf( fp_out[KYOSHUTUKIN] , "shikyu_keitai:%d\n" , shikyu_keitai );

		for( seido = KOUNEN ; seido <= KOKKYO ; seido++ )
		{
			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu_P[seido][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu_P[seido][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu[seido][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 2 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}
		}

		for( seido = 6 ; seido <= 7 ; seido++ )
		{
			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido - 4 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}
		}

		for( seido = CHIKYO ; seido <= SHIGAKU ; seido++ )
		{
			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu_P[seido][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu_P[seido][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu[seido][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , seido , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}
		}

		for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
		{
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 1 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 1 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
		{
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 2 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 2 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
		{
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 3 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 3 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
		{
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 4 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 6 , 4 );
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
			}
			fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
		}

		if( TOUGOU == 1)
		{
			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu_P[KOKUNEN][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu_P[KOKUNEN][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Nendomatu[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Nendomatu[KOKUNEN][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu_P[KOKUNEN][sotai_nendo - 1][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu_P[KOKUNEN][sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 7 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Kyoshutukin_Kokko_Nendomatu[KOKUNEN][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Kyoshutukin_Kokko_Nendomatu[KOKUNEN][sotai_nendo][MAX_JUKYU - NENREI_SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 1 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Tokubetukokko_Nendomatu_P[sotai_nendo - 1][nenrei - NENREI_SUM][SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Tokubetukokko_Nendomatu_P[sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 2 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Tokubetukokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Tokubetukokko_Nendomatu[sotai_nendo][MAX_JUKYU - NENREI_SUM][SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 3 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Tokubetukokko_Nendomatu_P[sotai_nendo - 1][nenrei - NENREI_SUM][SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Tokubetukokko_Nendomatu_P[sotai_nendo - 1][MAX_JUKYU - NENREI_SUM][SUM][shikyu_keitai] );
			}

			for( nendo = 2010 ; nendo <= SUIKEISHONENDO - 1 ; nendo++ )
			{
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 0. );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 0. );
			}

			for( nendo = SUIKEISHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
			{
				sotai_nendo = nendo - SHONENDO;
				fprintf( fp_out[KYOSHUTUKIN] , "%d,%d,%d," , nendo - 2000 , 8 , 4 );
				for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU - 1 ; nenrei++ )
				{
					fprintf( fp_out[KYOSHUTUKIN] , "%20.14le,", 
						Tokubetukokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][SUM][shikyu_keitai] );
				}
				fprintf( fp_out[KYOSHUTUKIN] , "%20.14le\n", 
					Tokubetukokko_Nendomatu[sotai_nendo][MAX_JUKYU - NENREI_SUM][SUM][shikyu_keitai] );
			}
		}
	}

	fclose( fp_out[KYOSHUTUKIN] );


	return;

}
