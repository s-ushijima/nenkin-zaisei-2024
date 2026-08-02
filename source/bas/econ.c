#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mecon.h"


double round( double a , int n );

void econ_read( FILE *fp , double cpi_up[] , double base_up_real[] , double interest_rate_real[] );

void kaitei_read( FILE *fp , double kaiteiritu[][MAX_JUKYU - UNDER_67 + 1] );

void cut_read( FILE *fp , double max_cut_rate[] );

void kakaku_make( double kakaku[] , double base_up_k[] , 
	double base_up_real[] , double cpi_up[] , int marume_nendo );


void econ()
{
	double buffer[100];
	int data_number;
	int nendo;
	int counter;
	int nenrei;
	int c_nendo;
	double max_cut_rate[SAISHUNENDO - ECON_SHONENDO + 1];
	double base_up_real[SAISHUNENDO - ECON_SHONENDO + 1];
	double interest_rate_real[SAISHUNENDO - ECON_SHONENDO + 1];


	econ_read( fp_in[KEIZAI] , cpi_up , base_up_real , interest_rate_real );

	kaitei_read( fp_in[KAITEI] , kaiteiritu );

	cut_read( fp_in[TANNEN_CUT] , max_cut_rate );


	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		base_up[nendo - ECON_SHONENDO] = base_up_real[nendo - ECON_SHONENDO] * cpi_up[nendo - ECON_SHONENDO];

		interest_rate[nendo - ECON_SHONENDO]
		 = interest_rate_real[nendo - ECON_SHONENDO] * cpi_up[nendo - ECON_SHONENDO];
	}


	kakaku_make( kakaku , base_up_k , base_up_real , cpi_up , MARUME_NENDO );


	if( Kurikoshim == 0 )
	{
		for( nendo = C_NENDO + 1 ; nendo <= KAISHI1 - 1 ; nendo++ )
		{
			for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
			}
		}

		for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			if( nendo == 2022 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
				}
			}
			else if( nendo == 2023 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = ( 1 / 0.994 );
				}
			}
			else if( nendo == 2024 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = ( 1 / 0.996 );
				}
			}
			else
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67]
					= max( 1.0 , min( max_cut_rate[nendo - ECON_SHONENDO] , kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67] ) );
				}
			}
		}
	}
	else if( Kurikoshim == 1 )
	{
		for( nendo = C_NENDO + 1 ; nendo <= KAISHI1 - 1 ; nendo++ )
		{
			for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
				T[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
			}
		}

		for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			if( nendo == 2022 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
					T[nendo - ECON_SHONENDO][nenrei - UNDER_67] = ( 1 / 0.997 );
				}
			}
			else if( nendo == 2023 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = ( 1 / 0.994 );
					T[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
				}
			}
			else if( nendo == 2024 )
			{
				for( nenrei = UNDER_67 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] = ( 1 / 0.996 );
					T[nendo - ECON_SHONENDO][nenrei - UNDER_67] = 1.;
				}
			}
			else
			{
				pre_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67]
				 = max( 1.0 , min( max_cut_rate[nendo - ECON_SHONENDO] / T[nendo - 1 - ECON_SHONENDO][UNDER_67 - UNDER_67]
				                 , kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] ) );

				T[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67]
				 = T[nendo - 1 - ECON_SHONENDO][UNDER_67 - UNDER_67] / max_cut_rate[nendo - ECON_SHONENDO]
				 * pre_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] ;

				for( nenrei = UNDER_67 + 1 ; nenrei <= MAX_JUKYU ; nenrei++ )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67]
					 = max( 1.0 , min( max_cut_rate[nendo - ECON_SHONENDO] / T[nendo - 1 - ECON_SHONENDO][nenrei - 1 - UNDER_67]
					                 , kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67] ) );

					T[nendo - ECON_SHONENDO][nenrei - UNDER_67]
					 = T[nendo - 1 - ECON_SHONENDO][nenrei - 1 - UNDER_67] / max_cut_rate[nendo - ECON_SHONENDO]
					 * pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67] ;
				}
			}
		}
	}


	if( D_MACRO == 1 )
	{
		for( nendo = D_M_NENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			if( nendo == D_M_NENDO )
			{
				pre_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67]
				 = max( 1.0 , max_cut_rate[nendo - ECON_SHONENDO]
				    / T[nendo - 1 - ECON_SHONENDO][UNDER_67 - UNDER_67] );
			}
			else
			{
				pre_cut[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67]
				 = max( 1.0 , max_cut_rate[nendo - ECON_SHONENDO] );
			}

			for( nenrei = UNDER_67 + 1 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				if( nendo == D_M_NENDO )
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67]
					 = max( 1.0 , max_cut_rate[nendo - ECON_SHONENDO]
					    / T[nendo - 1 - ECON_SHONENDO][nenrei - 1 - UNDER_67] );
				}
				else
				{
					pre_cut[nendo - ECON_SHONENDO][nenrei - UNDER_67]
					 = max( 1.0 , max_cut_rate[nendo - ECON_SHONENDO] );
				}
			}
		}
	}

	for( counter = C_NENDO + 1 ; counter <= SAISHUNENDO ; counter++ )
	{
		for( nendo = counter ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( c_nendo = counter ; c_nendo <= SAISHUNENDO ; c_nendo++ )
				{
					if( nenrei <= (int)( min( ( nendo + 67 - counter ) , MAX_JUKYU ) ) )
					{
						cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
						 /= pre_cut[counter - ECON_SHONENDO][UNDER_67 - UNDER_67];
					}
					else
					{
						cut_ruiseki[c_nendo - ECON_SHONENDO][nendo - ECON_SHONENDO][nenrei - NENREI_SUM]
						 /= pre_cut[counter - ECON_SHONENDO][nenrei - (int)min( ( nendo + 67 - counter ) , MAX_JUKYU ) ];
					}
				}
			}
		}
	}


	return;

}


double round( double a , int n )
{
 	double  b;
 	char    buf[256] = {'\0'};
 	char    *p;

	sprintf( buf , "%.*f" , n , a );
	b = strtod( buf , &p );

	return b;
}


void econ_read( FILE *fp , double cpi_up[] , double base_up_real[] , double interest_rate_real[] )
{
	int counter;
	int data_number;
	double buffer[16];
	int nendo;

	while ( ( read_data( buffer , fp , &data_number ) != EOF ) )
	{
		nendo = (int)( buffer[0] ) + 2000;
		cpi_up[nendo - ECON_SHONENDO] = 1. + buffer[6] / 100.;
		base_up_real[nendo - ECON_SHONENDO] = 1. + buffer[5] / 100.;
		interest_rate_real[nendo - ECON_SHONENDO] = 1. + buffer[2] / 100.;
	}

	for( counter = nendo + 1 ; counter <= SAISHUNENDO ; counter++ )
	{
		cpi_up[counter - ECON_SHONENDO] = cpi_up[nendo - ECON_SHONENDO];
		base_up_real[counter - ECON_SHONENDO] = base_up_real[nendo - ECON_SHONENDO];
		interest_rate_real[counter - ECON_SHONENDO] = interest_rate_real[nendo - ECON_SHONENDO];
	}

	return;
}


void kaitei_read( FILE *fp , double kaiteiritu[][MAX_JUKYU - UNDER_67 + 1] )
{
	int data_number;
	double buffer[100];
	int nendo;
	int nenrei;

	while( ( read_data( buffer, fp , &data_number ) != EOF ) )
	{
		nendo = (int)(buffer[0]) + 2000;
		for( nenrei = 1 ; nenrei <= MAX_JUKYU - UNDER_67 + 1 ; nenrei++ )
		{
			kaiteiritu[nendo - ECON_SHONENDO][nenrei - 1] = buffer[nenrei];
		}
	}

	return;
}


void cut_read( FILE *fp , double max_cut_rate[] )
{
	int counter;
	int data_number;
	double buffer[100];
	int nendo;

	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		max_cut_rate[nendo - ECON_SHONENDO] = 1.;
	}

	while( ( read_data( buffer , fp , &data_number ) != EOF ) )
	{
		nendo = (int)(buffer[0]);
		if( nendo >= ECON_SHONENDO )
		{
			max_cut_rate[nendo - ECON_SHONENDO] = 1. + buffer[1];
		}
	}

	for( counter = nendo + 1 ; counter <= SAISHUNENDO ; counter++ )
	{
		max_cut_rate[counter - ECON_SHONENDO] = max_cut_rate[nendo - ECON_SHONENDO];
	}

	return;
}


void kakaku_make( double kakaku[] , double base_up_k[] , 
	double base_up_real[] , double cpi_up[] , int marume_nendo )
{
	int nendo;
	double base_up_avg[SAISHUNENDO - ECON_SHONENDO + 1];

	for( nendo = ECON_SHONENDO + 5 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		base_up_avg[nendo - ECON_SHONENDO]
 		 = base_up_real[nendo - 5 - ECON_SHONENDO] * base_up_real[nendo - 4 - ECON_SHONENDO]
		   * base_up_real[nendo - 3 - ECON_SHONENDO];

		base_up_avg[nendo - ECON_SHONENDO] = pow( base_up_avg[nendo - ECON_SHONENDO] , 1. / 3. );

		if( nendo <= marume_nendo )
		{
			base_up_avg[nendo - ECON_SHONENDO]
			 = round( base_up_avg[nendo - ECON_SHONENDO] , 3 );
		}

		if( nendo == 2018 )
		{
			base_up_avg[nendo - ECON_SHONENDO] = 0.992;
		}
	}

	for( nendo = ECON_SHONENDO + 5 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		if( nendo == 2006 || nendo == 2007 )
		{
			base_up_k[nendo - ECON_SHONENDO] = cpi_up[nendo - 2 - ECON_SHONENDO];
		}
		else
		{
			base_up_k[nendo - ECON_SHONENDO]
			 = base_up_avg[nendo - ECON_SHONENDO] * cpi_up[nendo - 2 - ECON_SHONENDO];

			if( nendo <= marume_nendo )
			{
				base_up_k[nendo - ECON_SHONENDO] = round( base_up_k[nendo - ECON_SHONENDO] , 3 );
			}
		}
	}

	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		if( nendo <= KAKAKU_NENDO )
		{
			kakaku[nendo - ECON_SHONENDO] = 1.;
		}
		else if( nendo == KAKAKU_NENDO + 1 )
		{
			kakaku[nendo - ECON_SHONENDO] = 1.;
		}
		else
		{
			kakaku[nendo - ECON_SHONENDO]
			 = kakaku[nendo - 1 - ECON_SHONENDO] * base_up_k[nendo - ECON_SHONENDO];

			if( nendo <= marume_nendo )
			{
				kakaku[nendo - ECON_SHONENDO] = round( kakaku[nendo - ECON_SHONENDO], 3 );
			}
		}
	}

	return ;

}
