#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "snaps.h"
#include "mseid.h"
#include "mecon.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "option.h"

using namespace std;


double round( double a , int n );

double pension_marume( double a );

double kaiteiritu_marume( int nendo ,int marume_nendo , double a );

void econ_read( FILE *fp , double cpi_up[] , double base_up_real[] );

void index_make( double base_up_real[] , double cpi_up[] , 
	double base_up_index[] , double cpi_up_index[] , int marume_nendo );

double kaiteiritu_make_before( int nenrei , double base_up_index , double cpi_up_index );

double kaiteiritu_make( int nenrei , double base_up_index , double cpi_up_index );

double marume_hantei( int nendo , int marume_nendo , int marume_flg , double pension );

void rslt_out( FILE *fp , double output_array[][MAX_ROREI_JUKYU + 1] , 
	int shonendo , int array_shonendo , int saishunendo );

void kaitei_out( FILE *fp , double output_array[][MAX_ROREI_JUKYU + 1] , 
	int shonendo , int array_shonendo , int saishunendo , const char *title );

void ichijikin_out( FILE *fp , double shibou[][SHIBOU_KUBUN] , 
	int shonendo , int array_shonendo , int saishunendo , const char *title , int option );


void econ()
{
	int CAL_START = 2004;
	int MARUME_NENDO = 2024;

	int nendo;
	int nenrei;
	int seinendo;
	int kubun;
	int marume_flg[SAISHUNENDO - SHONENDO + 1][MAX_ROREI_JUKYU + 1];

	double cpi_up[SAISHUNENDO - ECON_SHONENDO + 1];
	double base_up_real[SAISHUNENDO - ECON_SHONENDO + 1];
	double cpi_up_index[SAISHUNENDO - ECON_SHONENDO + 1];
	double base_up_index[SAISHUNENDO - ECON_SHONENDO + 1];
	double kaiteiritu_ruiseki[SAISHUNENDO - ECON_SHONENDO + 1][MAX_ROREI_JUKYU + 1];
	double Pension_Temp;
	double Tanka_12shi;
	double Tanka_3shiiko;

	int TINSURA_NENDO = TINSURA_KAISHI;


	econ_read( fp_in[KEIZAI] , cpi_up , base_up_real );

	index_make( base_up_real , cpi_up , base_up_index , cpi_up_index , MARUME_NENDO );

	nendo = CAL_START;

	for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] = 1.;
		kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei] = 1.;
	}

	for( nendo = CAL_START + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( TINSURA == 1){
				if( nendo < TINSURA_NENDO )
				{
					kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei]
					 = kaiteiritu_make_before( nenrei , base_up_index[nendo - ECON_SHONENDO] , 
												cpi_up_index[nendo - ECON_SHONENDO] );
				}
				else
				{
					kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei]
					 = kaiteiritu_make( nenrei , base_up_index[nendo - ECON_SHONENDO] , 
										cpi_up_index[nendo - ECON_SHONENDO] );
				}
			}
			else
			{
				kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei]
				 = kaiteiritu_make_before( nenrei , base_up_index[nendo - ECON_SHONENDO] , 
											cpi_up_index[nendo - ECON_SHONENDO] );
			}

			if( nendo == 2015 )
			{
				kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] *= 0.991;
				kaiteiritu_marume( nendo , MARUME_NENDO , kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] );
			}
			else if( nendo == 2019 )
			{
				kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] *= 0.995;
				kaiteiritu_marume( nendo , MARUME_NENDO , kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] );
			}
			else if( nendo == 2020 )
			{
				kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] *= 0.999;
				kaiteiritu_marume( nendo , MARUME_NENDO , kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] );
			}

			kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei]
			 = kaiteiritu_marume( nendo , MARUME_NENDO ,
			   kaiteiritu_ruiseki[nendo - 1 - ECON_SHONENDO][(int)max( nenrei - 1 , 0 )]
			   * kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei] );

			if( kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei]
				 < Kisai_Shitasasae * kaiteiritu_ruiseki[nendo - ECON_SHONENDO][UNDER_67] )
			{
				kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei]
				 = Kisai_Shitasasae * kaiteiritu_ruiseki[nendo - ECON_SHONENDO][UNDER_67];

				kaiteiritu_tannen[nendo - ECON_SHONENDO][nenrei]
				 = kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei]
				   / kaiteiritu_ruiseki[nendo - 1 - ECON_SHONENDO][(int)max( nenrei - 1 , 0 )];
			}
		}
	}

	for( nendo = SHONENDO ; nendo <= MARUME_NENDO ; nendo++ )
	{
		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			marume_flg[nendo - SHONENDO][nenrei] = 1;
		}
	}

	for( nendo = MARUME_NENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( marume_flg[nendo - 1 - SHONENDO][(int)max( nenrei - 1 , 0 )] == 1 && 
				fabs( kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei]
				- kaiteiritu_ruiseki[nendo - 1 - ECON_SHONENDO][(int)max( nenrei - 1 , 0 )] ) < EPSILON )
			{
				marume_flg[nendo - SHONENDO][nenrei] = 1;
			}
			else
			{
				marume_flg[nendo - SHONENDO][nenrei] = 0;
			}
		}
	}

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			seinendo = nendo - nenrei;

			Pension_Temp = Full_Pension_Shonendo[nendo - SHONENDO][seinendo < N_O_NENDO ? 0 : seinendo - N_O_NENDO]
				 			* kaiteiritu_ruiseki[nendo - ECON_SHONENDO][nenrei];

			Full_Pension[nendo - SHONENDO][nenrei]
			 = marume_hantei( nendo , MARUME_NENDO , marume_flg[nendo - SHONENDO][nenrei] , Pension_Temp );

			Tanka_12shi = Kakyu_Tanka_12shi_Shonendo
						  * kaiteiritu_ruiseki[nendo - ECON_SHONENDO][UNDER_67];

			Tanka_3shiiko = Kakyu_Tanka_3shiiko_Shonendo
							* kaiteiritu_ruiseki[nendo - ECON_SHONENDO][UNDER_67];

			Kakyu_Tanka_12shi[nendo - SHONENDO][nenrei]
			 = marume_hantei( nendo , MARUME_NENDO , marume_flg[nendo - SHONENDO][UNDER_67] , Tanka_12shi );

			Kakyu_Tanka_3shiiko[nendo - SHONENDO][nenrei]
			 = marume_hantei( nendo , MARUME_NENDO , marume_flg[nendo - SHONENDO][UNDER_67] , Tanka_3shiiko );
		}

		for( kubun = 0 ; kubun < SHIBOU_KUBUN ; kubun++ )
		{
			Tanka_Shibou[nendo - SHONENDO][kubun] = Tanka_Shibou_Shonendo[kubun];
		}
	}

	rslt_out( fp_out[KAITEI] , kaiteiritu_tannen , CAL_START + 1 , ECON_SHONENDO , SAISHUNENDO );

	kaitei_out( fp_out[PENSION] , 
		kaiteiritu_tannen , CAL_START , ECON_SHONENDO , SAISHUNENDO , "Ç¯¶â³Û²þÄêÎ¨" );
	kaitei_out( fp_out[PENSION] , 
		kaiteiritu_ruiseki , CAL_START , ECON_SHONENDO , SAISHUNENDO , "ÎßÀÑ²þÄêÎ¨" );
	kaitei_out( fp_out[PENSION] , 
		Full_Pension , SHONENDO , SHONENDO , SAISHUNENDO , "´ðÁÃÇ¯¶âÃ±²Á" );
	kaitei_out( fp_out[PENSION] , 
		Kakyu_Tanka_12shi   , SHONENDO , SHONENDO , SAISHUNENDO , "²ÃµëÃ±²Á¡ÊÂè£±¡¦£²»Ò¡Ë" );
	kaitei_out( fp_out[PENSION] , 
		Kakyu_Tanka_3shiiko , SHONENDO , SHONENDO , SAISHUNENDO , "²ÃµëÃ±²Á¡ÊÂè£³»Ò°Ê¹ß¡Ë" );
	ichijikin_out( fp_out[PENSION] , Tanka_Shibou , SHONENDO , SHONENDO , SAISHUNENDO , "»àË´°ì»þ¶âÃ±²Á" , Option );


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


double pension_marume( double a )
{
	double b;

	b = floor( ( a + 50. ) / 100. ) * 100;

	return b;
}


double kaiteiritu_marume( int nendo , int marume_nendo , double a )
{
	if( nendo <= marume_nendo )
	{
		a = round( a , 3 );
	}

	return a;
}


void econ_read( FILE *fp , double cpi_up[] , double base_up_real[] )
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
	}

	for( counter = nendo + 1 ; counter <= SAISHUNENDO ; counter++ )
	{
		cpi_up[counter - ECON_SHONENDO] = cpi_up[nendo - ECON_SHONENDO];
		base_up_real[counter - ECON_SHONENDO] = base_up_real[nendo - ECON_SHONENDO];
	}

	return;
}


void index_make( double base_up_real[] , double cpi_up[] , 
	double base_up_index[] , double cpi_up_index[] , int marume_nendo )
{
	int HIKIAGE_START = 2003;
	int HIKIAGE_END = 2017;
	int nendo;

	double HOKENRYO[ 2017 - 2003 + 1 ]
		= { 0.1358 , 0.13934 , 0.14288 , 0.14642 , 0.14996 , 0.1535 , 0.15704 , 
			0.16058 , 0.16412 , 0.16766 , 0.1712 , 0.17474 , 0.17828 , 0.18182 , 0.183 };

	double  KASYOBUN_START = 0.910;

	double kashobun_henka[SAISHUNENDO - ECON_SHONENDO + 1];
	double base_up_avg[SAISHUNENDO - ECON_SHONENDO + 1];

	for( nendo = ECON_SHONENDO + 4 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		if( nendo == 2005 || nendo == 2006 )
		{
			base_up_avg[nendo - ECON_SHONENDO] = 1.;
			kashobun_henka[nendo - ECON_SHONENDO] = 1.;
		}
		else
		{
			base_up_avg[nendo - ECON_SHONENDO]
	 		 = base_up_real[nendo - 4 - ECON_SHONENDO] * base_up_real[nendo - 3 - ECON_SHONENDO]
			   * base_up_real[nendo - 2 - ECON_SHONENDO];

			base_up_avg[nendo - ECON_SHONENDO] = pow( base_up_avg[nendo - ECON_SHONENDO] , 1. / 3. );

			if( nendo < HIKIAGE_END + 4 )
			{
				kashobun_henka[nendo - ECON_SHONENDO]
				 = ( ( KASYOBUN_START - HOKENRYO[nendo - 3 -HIKIAGE_START] / 2. )
				   / ( KASYOBUN_START - HOKENRYO[nendo - 4 - HIKIAGE_START] / 2. ) );
			}
			else
			{
				kashobun_henka[nendo - ECON_SHONENDO] = 1.;
			}
		}

		base_up_avg[nendo - ECON_SHONENDO]
		 = kaiteiritu_marume( nendo , marume_nendo , base_up_avg[nendo - ECON_SHONENDO] );

		kashobun_henka[nendo - ECON_SHONENDO]
		 = kaiteiritu_marume( nendo , marume_nendo , kashobun_henka[nendo - ECON_SHONENDO] );
	}

	for( nendo = ECON_SHONENDO + 4 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		base_up_index[nendo - ECON_SHONENDO]
			= cpi_up[nendo - 1 - ECON_SHONENDO] * kashobun_henka[nendo - ECON_SHONENDO]
			   * base_up_avg[nendo - ECON_SHONENDO];

		cpi_up_index[nendo - ECON_SHONENDO] = cpi_up[nendo - 1 - ECON_SHONENDO];

		base_up_index[nendo - ECON_SHONENDO]
		 = kaiteiritu_marume( nendo , marume_nendo , base_up_index[nendo - ECON_SHONENDO] );

		cpi_up_index[nendo - ECON_SHONENDO]
		 = kaiteiritu_marume( nendo , marume_nendo ,cpi_up_index[nendo - ECON_SHONENDO] );
	}

	return ;

}


double kaiteiritu_make_before( int nenrei , double base_up_index , double cpi_up_index )
{
	double kaiteiritu;

	if(nenrei == UNDER_67)
	{
		if( base_up_index < 1. && base_up_index < cpi_up_index )
		{
			if(cpi_up_index > 1.)
			{
				kaiteiritu = 1.;
			}
			else
			{
				kaiteiritu = cpi_up_index;
			}
		}
		else
		{
			kaiteiritu = base_up_index;
		}
	}
	else
	{
		if( cpi_up_index > base_up_index && base_up_index >= 1. )
		{
			kaiteiritu = base_up_index;
		}
		else if( cpi_up_index > 1.&&  base_up_index < 1.)
		{
			kaiteiritu = 1.;
		}
		else
		{
			kaiteiritu = cpi_up_index;
		}
	}

	return kaiteiritu;

}


double kaiteiritu_make( int nenrei , double base_up_index , double cpi_up_index )
{
	double kaiteiritu;

	if( nenrei <= UNDER_67 )
	{
		kaiteiritu = base_up_index;
	}
	else
	{
		if( cpi_up_index > base_up_index )
		{
			kaiteiritu = base_up_index;
		}
		else
		{
			kaiteiritu = cpi_up_index;
		}
	}

	return kaiteiritu;

}


double marume_hantei( int nendo , int marume_nendo , int marume_flg , double pension )
{
	double a;

	if( nendo <= marume_nendo )
	{
		a = pension_marume( pension );
	}
	else if( marume_flg == 1 )
	{
		a = max( pension , pension_marume( pension ) );
	}
	else
	{
		a = pension;
	}

	return a;

}


void rslt_out( FILE *fp , double output_array[][MAX_ROREI_JUKYU + 1] , 
	int shonendo , int array_shonendo , int saishunendo )
{
	int nendo;
	int nenrei;


	for( nendo = shonendo ; nendo <= saishunendo ; nendo++ )
	{

		fprintf( fp , "%d," ,  nendo - 2000 ); 

		for( nenrei = UNDER_67 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			fprintf( fp , "%20.14e," , output_array[nendo - array_shonendo][nenrei] );
		}

		fprintf( fp , "\n" );
	}

	return ;

}


void kaitei_out( FILE *fp , double output_array[][MAX_ROREI_JUKYU + 1] , 
	int shonendo , int array_shonendo , int saishunendo , const char *title )
{
	int nendo;
	int nenrei;


	fprintf( fp , "%s\n%s" , title , "Ç¯ÅÙ¡Ê²¼2·å¡Ë" );

	for ( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		fprintf( fp , ",%dºÐ" , nenrei );
	}

	fprintf( fp , "\n" );

	for( nendo = shonendo ; nendo <= saishunendo ; nendo++ )
	{

		fprintf( fp , "%d," ,  nendo - 2000 ); 

		for( nenrei = 0 ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			fprintf( fp , "%20.14e," , output_array[nendo - array_shonendo][nenrei] );
		}

		fprintf( fp , "\n" );
	}

	return ;

}


void ichijikin_out( FILE *fp , double shibou[][SHIBOU_KUBUN] , 
	int shonendo , int array_shonendo , int saishunendo , const char *title , int option )
{
	const char *ichijikin_kubun[]={ "36·î°Ê¾å180·îÌ¤Ëþ" , "180·î°Ê¾å240·îÌ¤Ëþ" , "240·î°Ê¾å300·îÌ¤Ëþ" , 
									"300·î°Ê¾å360·îÌ¤Ëþ" , "360·î°Ê¾å420·îÌ¤Ëþ" , "420·î°Ê¾å" };

	int kubun;
	int nendo;

	fprintf( fp , "%s\n%s" , title , "Ç¯ÅÙ¡Ê²¼2·å¡Ë" );

	for( kubun = 0 ; kubun < SHIBOU_KUBUN - 1 ; kubun++ )
	{
		fprintf( fp , ",%s" , ichijikin_kubun[kubun] );
	}

	if( option == 1 )
	{
		fprintf( fp , "480·îÌ¤Ëþ,480·î°Ê¾å" );
	}

	fprintf( fp , "\n" );


	for ( nendo = shonendo ; nendo <= saishunendo ; nendo++ )
	{
		fprintf( fp , "%d" , nendo - 2000 );
		
		for( kubun = 0 ; kubun < SHIBOU_KUBUN - 1 ; kubun++ )
		{
			fprintf( fp , ",%20.14e" , shibou[nendo - array_shonendo][kubun] );
		}

		if( option == 1 )
		{
			fprintf( fp , ",%20.14e" , shibou[nendo - array_shonendo][SHIBOU_KUBUN - 1] );
		}

		fprintf( fp , "\n" );
	}

	return;

}
