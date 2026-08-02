#include <cstdio>
#include <cstring>
#include <iostream>
#include "snaps.h"
#include "mkisosu.h"
#include "mecon.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "option.h"


void clear_kyufu( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
						[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] );

void clear_kokko( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
						[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] );

void clear_kyoshutukin( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1]
								[MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI] );

void clear_tanka( double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI] );

void clear_tokubetukokko( double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
								[TOKUBETU_SHURUI][SHIKYU_KEITAI] );

void cal_kyufu_nendomatu( int nendo , int nenrei , int seibetu , int P , 
	double kyufu_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
	double rorei_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][NOUFU_JOTAI_SHIN] ,
	double shogai_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][KYUFU_HOUHOU][SHIKYU_KEITAI] ,
	double izoku_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][SHIKYU_KEITAI] ,
	double rorei_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][NOUFU_JOTAI_KYU] ,
	double shogai_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double izoku_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double furikae_kasan[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU]
			[KYUFU_KUBUN - 1] ,
	double tokubetu_kokko_wariai[SAISHUNENDO - ( SHONENDO - 1 ) + 1][TOKUBETU_SHURUI] );

void cal_tokubetukokko_nendonmatu( int nendo , int nenrei , int seibetu , int P , 
	double tokubetukokko_nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
	double rorei_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][NOUFU_JOTAI_SHIN] ,
	double shogai_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][KYUFU_HOUHOU][SHIKYU_KEITAI] ,
	double rorei_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][NOUFU_JOTAI_KYU] ,
	double shogai_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double izoku_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double tokubetu_kokko_wariai[SAISHUNENDO - ( SHONENDO - 1 ) + 1][TOKUBETU_SHURUI] );

void cal_sum_kyufu( int nendo , 
	double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] );

void cal_sum_kokko( int nendo , 
	double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] );

void cal_sum_tokubetukokko( int nendo , 
	double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] );

void cal_kyufu_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double kyufu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kyufu_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kyufu_nendomatu_P[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] );

void cal_kokko_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double kokko[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kokko_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kokko_nendomatu_P[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] );

void cal_tokubetukokko_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double tokubetukokko[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double tokubetukokko_nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double tokubetukokko_nendomatu_P[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] );


void Atamawari()
{
	int nendo;
	int nenrei;
	int seido;
	int shinkyu;
	int kubun;
	int taishou;
	int tokubetu_shurui;
	int sotai_nendo;
	int seibetu;
	int shikyu_keitai;
	int noufu_joutai;
	int SHIHARAIOKURE = 2;


	clear_kyufu( Kyufu );
	clear_kyufu( Kyufu_Nendomatu );
	clear_kyufu( Kyufu_Nendomatu_P );

	clear_kyufu( Kasanmae_Kyufu );
	clear_kyufu( Kasanmae_Kyufu_Nendomatu );
	clear_kyufu( Kasanmae_Kyufu_Nendomatu_P );

	clear_kokko( Kokko );
	clear_kokko( Kokko_Nendomatu );
	clear_kokko( Kokko_Nendomatu_P );

	clear_kyoshutukin( Kyoshutukin );
	clear_kyoshutukin( Kyoshutukin_Nendomatu );
	clear_kyoshutukin( Kyoshutukin_Nendomatu_P );

	clear_kyoshutukin( Kyoshutukin_Kokko );
	clear_kyoshutukin( Kyoshutukin_Kokko_Nendomatu );
	clear_kyoshutukin( Kyoshutukin_Kokko_Nendomatu_P );

	clear_tanka( Tanka );
	clear_tanka( Tanka_Nendomatu );
	clear_tanka( Tanka_Nendomatu_P );

	clear_tanka( Tanka_Kokko );
	clear_tanka( Tanka_Kokko_Nendomatu );
	clear_tanka( Tanka_Kokko_Nendomatu_P );

	clear_tokubetukokko( Tokubetukokko );
	clear_tokubetukokko( Tokubetukokko_Nendomatu );
	clear_tokubetukokko( Tokubetukokko_Nendomatu_P );


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;
		
		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( seibetu = OTOKO ; seibetu <= ONNA ; seibetu++ )
			{
				cal_kyufu_nendomatu( nendo , nenrei , seibetu , 0 , 
					Kyufu_Nendomatu , Rorei_New , Shogai_New , Izoku_New , Rorei_Old , Shogai_Old , Izoku_Old , 
					FurikaeKasan , Tokubetu_Kokko_Wariai );

				cal_kyufu_nendomatu( nendo , nenrei , seibetu , 0 , 
					Kasanmae_Kyufu_Nendomatu , Rorei_New , Shogai_New , Izoku_New , Rorei_Old , Shogai_Old , 
					Izoku_Old , FurikaeKasan , Tokubetu_Kokko_Wariai );

				cal_tokubetukokko_nendonmatu( nendo , nenrei , seibetu , 0 , 
					Tokubetukokko_Nendomatu , Rorei_New , Shogai_New , Rorei_Old , Shogai_Old , Izoku_Old , 
					Tokubetu_Kokko_Wariai );

				cal_kyufu_nendomatu( nendo , nenrei , seibetu , 1 , 
					Kyufu_Nendomatu_P , Rorei_New , Shogai_New , Izoku_New , Rorei_Old , Shogai_Old , Izoku_Old , 
					FurikaeKasan , Tokubetu_Kokko_Wariai );

				cal_kyufu_nendomatu( nendo , nenrei , seibetu , 1 , 
					Kasanmae_Kyufu_Nendomatu_P , Rorei_New , Shogai_New , Izoku_New , Rorei_Old , Shogai_Old , 
					Izoku_Old , FurikaeKasan , Tokubetu_Kokko_Wariai );

				cal_tokubetukokko_nendonmatu( nendo , nenrei , seibetu , 1 , 
					Tokubetukokko_Nendomatu_P , Rorei_New , Shogai_New , Rorei_Old , Shogai_Old , Izoku_Old , 
					Tokubetu_Kokko_Wariai );
			}


			for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
			{
				for( shinkyu = NEW ; shinkyu <= OLD ; shinkyu++ )
				{
					for( kubun = ROREI ; kubun <= IZOKU ; kubun++ )
					{
						for( taishou = KYOSHUTU ; taishou <= TOKUBETU ; taishou++ )
						{
							for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
							{
								if( shikyu_keitai == KAKYU )
								{
									Kasanmae_Kyufu_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];

									Kasanmae_Kyufu_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];

									Kyufu_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];

									Kyufu_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];
								}
								else
								{
									Kasanmae_Kyufu_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];

									Kasanmae_Kyufu_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];

									Kyufu_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];

									Kyufu_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
									 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];
								}

								if( taishou == KYOSHUTU )
								{
									Kokko_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][shikyu_keitai]
									 = Kasanmae_Kyufu_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM]
										   [shinkyu][kubun][taishou][shikyu_keitai]
									    * Kokko_Wariai[nendo - (SHONENDO - 1)];

									Kokko_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										[shinkyu][kubun][shikyu_keitai]
									 = Kasanmae_Kyufu_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM]
										   [shinkyu][kubun][taishou][shikyu_keitai]
									    * Kokko_Wariai[nendo - (SHONENDO - 1)];
								}
							}
						}
					}
				}
			}

			for( tokubetu_shurui = TOKUBETU_MENJO ; tokubetu_shurui <= TOKUBETU_20MAE ; tokubetu_shurui++ )
			{
				for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
				{
					if( shikyu_keitai == KAKYU )
					{
						Tokubetukokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai]
						 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];

						Tokubetukokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai]
						 *= Cut_ritu[sotai_nendo][UNDER_63  - UNDER_63];
					}
					else
					{
						Tokubetukokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai]
						 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];

						Tokubetukokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai]
						 *= Cut_ritu[sotai_nendo][nenrei - UNDER_63];
					}
				}
			}

		}


		cal_sum_kyufu( nendo , Kyufu_Nendomatu );
		cal_sum_kyufu( nendo , Kyufu_Nendomatu_P );
		cal_sum_kyufu( nendo , Kasanmae_Kyufu_Nendomatu );
		cal_sum_kyufu( nendo , Kasanmae_Kyufu_Nendomatu_P );

		cal_sum_kokko( nendo , Kokko_Nendomatu );
		cal_sum_kokko( nendo , Kokko_Nendomatu_P );

		cal_sum_tokubetukokko( nendo , Tokubetukokko_Nendomatu );
		cal_sum_tokubetukokko( nendo , Tokubetukokko_Nendomatu_P );

	}


	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = UNDER_64 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			cal_kyufu_nendokan( nendo , nenrei , SHIHARAIOKURE , Kasanmae_Kyufu , 
				Kasanmae_Kyufu_Nendomatu , Kasanmae_Kyufu_Nendomatu_P , kaiteiritu );

			cal_kyufu_nendokan( nendo , nenrei , SHIHARAIOKURE , Kyufu , 
				Kyufu_Nendomatu , Kyufu_Nendomatu_P , kaiteiritu );

			cal_kokko_nendokan( nendo , nenrei , SHIHARAIOKURE , Kokko ,
				Kokko_Nendomatu , Kokko_Nendomatu_P , kaiteiritu );

			cal_tokubetukokko_nendokan( nendo , nenrei ,SHIHARAIOKURE , Tokubetukokko , 
				Tokubetukokko_Nendomatu , Tokubetukokko_Nendomatu_P , kaiteiritu );
		}
	}


	for( nendo = SHONENDO + 1 ; nendo <= SAISHUNENDO ; nendo++ )
	{
		cal_sum_kyufu( nendo , Kyufu );
		cal_sum_kyufu( nendo , Kasanmae_Kyufu );

		cal_sum_kokko( nendo , Kokko );

		cal_sum_tokubetukokko( nendo , Tokubetukokko );
	}


	for( nendo = SHONENDO + 1 ; nendo <= SUIKEISAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		for( nenrei = UNDER_64 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				Tanka[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kyufu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
				    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12.;

				Tanka_Kokko[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 = Kokko[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
				    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12;

				for( seido = SUM ; seido <= SHIGAKU ; seido++ )
				{
					Kyoshutukin[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = SanteiTaishou[seido][sotai_nendo][SUM]
					    * Tanka[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12;

					Kyoshutukin_Kokko[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = SanteiTaishou[seido][sotai_nendo][SUM]
					    * Tanka_Kokko[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12;
				}
			}
		}


		for( seido = SUM ; seido <= SHIGAKU ; seido++ )
		{
			for( nenrei = UNDER_64 ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
				{
					Kyoshutukin[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

					Kyoshutukin_Kokko[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin_Kokko[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];
				}
			}
		}

		for( nenrei = UNDER_64 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				Tanka[sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
				 += Tanka[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

				Tanka_Kokko[sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
				 += Tanka_Kokko[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];
			}
		}

		for( nenrei = UNDER_63 ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				if( SanteiTaishou[SUM][sotai_nendo][SUM] > 0. )
				{
					Tanka_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Kyufu_Nendomatu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
					    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12.;

					Tanka_Kokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = Kokko_Nendomatu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
					    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12.;
				}
				else
				{
					Tanka_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
					Tanka_Kokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				}

				if( nendo == SAISHUNENDO )
				{
					if( SanteiTaishou[SUM][sotai_nendo][SUM] > 0. )
					{
						Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = Kyufu_Nendomatu_P[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
						    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12.;

						Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = Kokko_Nendomatu[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
						    / SanteiTaishou[SUM][sotai_nendo][SUM] / 12.;
					}
					else
					{
						Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
						Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
					}
				}
				else
				{
					if( SanteiTaishou[SUM][sotai_nendo + 1][SUM] > 0. )
					{
						Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = Kyufu_Nendomatu_P[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][KYOSHUTU][shikyu_keitai]
						    / SanteiTaishou[SUM][sotai_nendo + 1][SUM] / 12.;

						Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = Kokko_Nendomatu_P[SUM][sotai_nendo][nenrei - NENREI_SUM][SUM][SUM][shikyu_keitai]
						    / SanteiTaishou[SUM][sotai_nendo + 1][SUM] / 12.;
					}
					else
					{
						Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
						Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
					}
				}

				for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
				{
					Kyoshutukin_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
				 	 = SanteiTaishou[seido][sotai_nendo][SUM]
					    * Tanka_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;

					Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
					 = SanteiTaishou[seido][sotai_nendo][SUM]
					    * Tanka_Kokko_Nendomatu[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;

					if( nendo == SAISHUNENDO )
					{
						Kyoshutukin_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = SanteiTaishou[seido][sotai_nendo][SUM]
						    * Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;

						Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = SanteiTaishou[seido][sotai_nendo][SUM]
						    * Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;
					}
					else
					{
						Kyoshutukin_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = SanteiTaishou[seido][sotai_nendo + 1][SUM]
						    * Tanka_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;

						Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai]
						 = SanteiTaishou[seido][sotai_nendo + 1][SUM]
						    * Tanka_Kokko_Nendomatu_P[sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai] * 12.;
					}

					Kyoshutukin_Nendomatu[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

					Kyoshutukin_Nendomatu_P[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

					Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin_Kokko_Nendomatu[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];

					Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shikyu_keitai]
					 += Kyoshutukin_Kokko_Nendomatu_P[seido][sotai_nendo][nenrei - NENREI_SUM][shikyu_keitai];
				}
			}
		}

	}


	return;


}


void clear_kyufu( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
								[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] )
{
	int seido;
	int nendo;
	int nenrei;
	int shinkyu;
	int kubun;
	int taishou;
	int shikyu_keitai;

	for( seido = SUM ; seido <= SHIGAKU ; seido++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( shinkyu = SUM ; shinkyu <= OLD ; shinkyu++ )
				{
					for( taishou = SUM ; taishou <= TOKUBETU ; taishou++ )
					{
						for( kubun = SUM ; kubun <= IZOKU ; kubun++ )
						{
							for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
							{
								array[seido][nendo - SHONENDO][nenrei - NENREI_SUM][shinkyu]
									[kubun][taishou][shikyu_keitai]
								 = 0.;
							}
						}
					}
				}
			}
		}
	}


	return;

}


void clear_kokko( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
								[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] )
{
	int seido;
	int nendo;
	int nenrei;
	int shinkyu;
	int kubun;
	int shikyu_keitai;

	for( seido = SUM ; seido <= SHIGAKU ; seido++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( shinkyu = SUM ; shinkyu <= OLD ; shinkyu++ )
				{
					for( kubun = SUM ; kubun <= IZOKU ; kubun++ )
					{
						for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
						{
							array[seido][nendo - SHONENDO][nenrei - NENREI_SUM][shinkyu]
								[kubun][shikyu_keitai]
							 = 0.;
						}
					}
				}
			}
		}
	}


	return;

}


void clear_kyoshutukin( double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1]
									[MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI] )
{
	int seido;
	int nendo;
	int nenrei;
	int shikyu_keitai;

	for( seido = SUM ; seido <= SHIGAKU ; seido++ )
	{
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
			{
				for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
				{
					array[seido][nendo - SHONENDO][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
				}
			}
		}
	}


	return;

}


void clear_tanka( double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SHIKYU_KEITAI] )
{
	int nendo;
	int nenrei;
	int shikyu_keitai;

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
			{
				array[nendo - SHONENDO][nenrei - NENREI_SUM][shikyu_keitai] = 0.;
			}
		}
	}


	return;

}


void clear_tokubetukokko( double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
										[TOKUBETU_SHURUI][SHIKYU_KEITAI] )
{
	int nendo;
	int nenrei;
	int tokubetu_shurui;
	int shikyu_keitai;

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = NENREI_SUM ; nenrei <= MAX_JUKYU ; nenrei++ )
		{
			for( tokubetu_shurui = SUM ; tokubetu_shurui <= TOKUBETU_20MAE ; tokubetu_shurui++ )
			{
				for( shikyu_keitai = SUM ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
				{
					array[nendo - SHONENDO][nenrei - NENREI_SUM][tokubetu_shurui][shikyu_keitai] = 0.;
				}
			}
		}
	}


	return;

}


void cal_kyufu_nendomatu( int nendo , int nenrei , int seibetu , int P , 
	double kyufu_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
	double rorei_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][NOUFU_JOTAI_SHIN] ,
	double shogai_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][KYUFU_HOUHOU][SHIKYU_KEITAI] ,
	double izoku_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][SHIKYU_KEITAI] ,
	double rorei_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][NOUFU_JOTAI_KYU] ,
	double shogai_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double izoku_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double furikae_kasan[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU]
			[KYUFU_KUBUN - 1] ,
	double tokubetu_kokko_wariai[SAISHUNENDO - ( SHONENDO - 1 ) + 1][TOKUBETU_SHURUI] )
{
	int seido;
	int noufu_joutai;
	int shikyu_keitai;
	int p = 0;

	if( nendo != SAISHUNENDO && P == 1 )
	{
		p = 1;
	}


	kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][ROREI][KYOSHUTU][KIHON]
	 += rorei_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][NOUFU];

	kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][ROREI][KYOSHUTU][KIHON]
	 += ( rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][NOUFU]
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][KASANOUFU]
		    * ( 1. - tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_KASAAGE] )
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][GONEN]
		    * ( 1. - tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_GONEN] ) );

	for( noufu_joutai = MENJO_ZENHAN ; noufu_joutai <= MENJO_KOUHAN ; noufu_joutai++ )
	{
		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][ROREI][TOKUBETU][KIHON]
		 += rorei_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][noufu_joutai];
	}

	kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][ROREI][TOKUBETU][KIHON]
	 += ( rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][MENJO]
		   * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO]
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][KASANOUFU]
		    * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_KASAAGE]
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][KASAMENJO]
		    * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_KASAMENJO]
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][ROFUKU_SHITASASAE]
		    * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_SHITASASAE]
		 + rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][GONEN]
		    * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_GONEN] );

	for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
	{
		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][SHOGAI][KYOSHUTU][shikyu_keitai]
		 += ( shogai_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][IPPAN][shikyu_keitai]
			 + shogai_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][HATACHIMAE][shikyu_keitai]
			    * ( 1. - tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_20MAE] ) ) ;

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][SHOGAI][KYOSHUTU][shikyu_keitai]
		 += shogai_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][NOUFU];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][SHOGAI][TOKUBETU][shikyu_keitai]
 		 += shogai_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][HATACHIMAE][shikyu_keitai]
	    	 * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_20MAE];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][SHOGAI][TOKUBETU][shikyu_keitai]
		 += shogai_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][MENJO]
		     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][IZOKU][KYOSHUTU][shikyu_keitai]
		 += izoku_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][IZOKU][KYOSHUTU][shikyu_keitai]
		 += izoku_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][NOUFU];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][IZOKU][TOKUBETU][shikyu_keitai]
		 += izoku_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][MENJO]
		     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO];
	}


	for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
	{
		kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][ROREI][KYOSHUTU][KIHON]
		 += rorei_new[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][NOUFU];

		kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][ROREI][KYOSHUTU][KIHON]
		 += ( rorei_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][NOUFU]
			 + rorei_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][KASANOUFU]
			 + rorei_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][GONEN] );

		kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][ROREI][KYOSHUTU][KAKYU]
		 += rorei_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][KAKYU_NOUFU];

		for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
		{
			kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][SHOGAI][KYOSHUTU][shikyu_keitai]
			 += ( shogai_new[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][IPPAN][shikyu_keitai]
				 + shogai_new[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][HATACHIMAE][shikyu_keitai] );

			kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][SHOGAI][KYOSHUTU][shikyu_keitai]
			 += shogai_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][NOUFU];

			kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][IZOKU][KYOSHUTU][shikyu_keitai]
			 += izoku_new[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai];

			kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM][OLD][IZOKU][KYOSHUTU][shikyu_keitai]
			 += izoku_old[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][NOUFU];
		}
	}


	for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
	{
		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][ROREI][KYOSHUTU][KIHON]
		 += furikae_kasan[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][ROREI];

		kyufu_nendomatu[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][NEW][SHOGAI][KYOSHUTU][KIHON]
		 += furikae_kasan[seido][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][SHOGAI];
	}


	return;

}


void cal_tokubetukokko_nendonmatu( int nendo , int nenrei , int seibetu , int P , 
	double tokubetukokko_nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
	double rorei_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][NOUFU_JOTAI_SHIN] ,
	double shogai_new[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][KYUFU_HOUHOU][SHIKYU_KEITAI] ,
	double rorei_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1][SEIBETU][NOUFU_JOTAI_KYU] ,
	double shogai_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double izoku_old[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SEIBETU][SHIKYU_KEITAI][NOUFU_JOTAI_KYU - 6] ,
	double tokubetu_kokko_wariai[SAISHUNENDO - ( SHONENDO - 1 ) + 1][TOKUBETU_SHURUI] )
{
	int noufu_joutai;
	int shikyu_keitai;
	int tokubetu_shurui;
	int p = 0;

	if( nendo != SAISHUNENDO && P == 1 )
	{
		p = 1;
	}


	for( noufu_joutai = MENJO_ZENHAN ; noufu_joutai <= MENJO_KOUHAN ; noufu_joutai++ )
	{
		tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][TOKUBETU_MENJO][KIHON]
		 += rorei_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][noufu_joutai];
	}

	tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][TOKUBETU_MENJO][KIHON]
	 += rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][MENJO]
	     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO];

	for( tokubetu_shurui = TOKUBETU_KASAAGE ; tokubetu_shurui <= TOKUBETU_GONEN ; tokubetu_shurui++ )
	{
		tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][tokubetu_shurui][KIHON]
		 += rorei_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][tokubetu_shurui + 3]
		     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][tokubetu_shurui];
	}

	for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
	{
		tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][TOKUBETU_20MAE][shikyu_keitai]
 	 	+= shogai_new[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][HATACHIMAE][shikyu_keitai]
	    	 * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_20MAE];

		tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][TOKUBETU_MENJO][shikyu_keitai]
		 += shogai_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][MENJO]
		     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO];

		tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM][TOKUBETU_MENJO][shikyu_keitai]
		 += izoku_old[KOKUNEN][nendo - SHONENDO][nenrei - NENREI_SUM][seibetu][shikyu_keitai][MENJO]
		     * tokubetu_kokko_wariai[nendo + p - ( SHONENDO - 1 )][TOKUBETU_MENJO];
	}


	return;

}


void cal_sum_kyufu( int nendo , 
	double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] )
{
	int seido[3];
	int nenrei[3];
	int shinkyu[3];
	int kubun[3];
	int taishou[3];
	int shikyu_keitai[3];

	for( seido[0] = KOKUNEN ; seido[0] <= SHIGAKU ; seido[0]++ )
	{
		for( nenrei[0] = UNDER_63 ; nenrei[0] <= MAX_JUKYU ; nenrei[0]++ )
		{
			for( shinkyu[0] = NEW ; shinkyu[0] <= OLD ; shinkyu[0]++ )
			{
				for( kubun[0] = ROREI ; kubun[0] <= IZOKU ; kubun[0]++ )
				{
					for( taishou[0] = KYOSHUTU ; taishou[0] <= TOKUBETU ; taishou[0]++ )
					{
						for( shikyu_keitai[0] = KIHON ; shikyu_keitai[0] <= KAKYU ; shikyu_keitai[0]++ )
						{

	for( seido[1] = 0 ; seido[1] <= 1 ; seido[1]++ )
	{
		if( seido[1] == 0 ){ seido[2] = SUM; }
		else{ seido[2] = seido[0]; }

		for( nenrei[1] = 0 ; nenrei[1] <= 1 ; nenrei[1]++ )
		{
			if( nenrei[1] == 0 ){ nenrei[2] = NENREI_SUM; }
			else{ nenrei[2] = nenrei[0]; }

			for( shinkyu[1] = 0 ; shinkyu[1] <= 1 ; shinkyu[1]++ )
			{
				if( shinkyu[1] == 0 ){ shinkyu[2] = SUM; }
				else{ shinkyu[2] = shinkyu[0]; }

				for( kubun[1] = 0 ; kubun[1] <= 1 ; kubun[1]++ )
				{
					if( kubun[1] == 0 ){ kubun[2] = SUM; }
					else{ kubun[2] = kubun[0]; }

					for( taishou[1] = 0 ; taishou[1] <= 1 ; taishou[1]++ )
					{
						if( taishou[1] == 0 ){ taishou[2] = SUM; }
						else{ taishou[2] = taishou[0]; }

						for( shikyu_keitai[1] = 0 ; shikyu_keitai[1] <= 1 ; shikyu_keitai[1]++ )
						{
							if( shikyu_keitai[1] == 0 ){ shikyu_keitai[2] = SUM; }
							else{ shikyu_keitai[2] = shikyu_keitai[0]; }

							if( seido[1] == 1 && shinkyu[1] == 1 && kubun[1] == 1 && 
								taishou[1] == 1 && shikyu_keitai[1] == 1 )
							{
								continue;
							}
							else
							{
								array[seido[2]][nendo - SHONENDO][nenrei[2] - NENREI_SUM]
									[shinkyu[2]][kubun[2]][taishou[2]][shikyu_keitai[2]]
								 += array[seido[0]][nendo - SHONENDO][nenrei[0] - NENREI_SUM]
									    [shinkyu[0]][kubun[0]][taishou[0]][shikyu_keitai[0]];
							}

						}
					}
				}
			}
		}
	}

						}
					}
				}
			}
		}
	}


	return;

}


void cal_sum_kokko( int nendo , 
	double array[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] )
{
	int seido[3];
	int nenrei[3];
	int shinkyu[3];
	int kubun[3];
	int shikyu_keitai[3];

	for( seido[0] = KOKUNEN ; seido[0] <= SHIGAKU ; seido[0]++ )
	{
		for( nenrei[0] = UNDER_63 ; nenrei[0] <= MAX_JUKYU ; nenrei[0]++ )
		{
			for( shinkyu[0] = NEW ; shinkyu[0] <= OLD ; shinkyu[0]++ )
			{
				for( kubun[0] = ROREI ; kubun[0] <= IZOKU ; kubun[0]++ )
				{
					for( shikyu_keitai[0] = KIHON ; shikyu_keitai[0] <= KAKYU ; shikyu_keitai[0]++ )
					{

	for( seido[1] = 0 ; seido[1] <= 1 ; seido[1]++ )
	{
		if( seido[1] == 0 ){ seido[2] = SUM; }
		else{ seido[2] = seido[0]; }

		for( nenrei[1] = 0 ; nenrei[1] <= 1 ; nenrei[1]++ )
		{
			if( nenrei[1] == 0 ){ nenrei[2] = NENREI_SUM; }
			else{ nenrei[2] = nenrei[0]; }

			for( shinkyu[1] = 0 ; shinkyu[1] <= 1 ; shinkyu[1]++ )
			{
				if( shinkyu[1] == 0 ){ shinkyu[2] = SUM; }
				else{ shinkyu[2] = shinkyu[0]; }

				for( kubun[1] = 0 ; kubun[1] <= 1 ; kubun[1]++ )
				{
					if( kubun[1] == 0 ){ kubun[2] = SUM; }
					else{ kubun[2] = kubun[0]; }

					for( shikyu_keitai[1] = 0 ; shikyu_keitai[1] <= 1 ; shikyu_keitai[1]++ )
					{
						if( shikyu_keitai[1] == 0 ){ shikyu_keitai[2] = SUM; }
						else{ shikyu_keitai[2] = shikyu_keitai[0]; }

						if( seido[1] == 1 && shinkyu[1] == 1 && kubun[1] == 1 && 
							shikyu_keitai[1] == 1 )
						{
							continue;
						}
						else
						{
							array[seido[2]][nendo - SHONENDO][nenrei[2] - NENREI_SUM]
								[shinkyu[2]][kubun[2]][shikyu_keitai[2]]
							 += array[seido[0]][nendo - SHONENDO][nenrei[0] - NENREI_SUM]
								    [shinkyu[0]][kubun[0]][shikyu_keitai[0]];
						}

					}
				}
			}
		}
	}

					}
				}
			}
		}
	}


	return;

}


void cal_sum_tokubetukokko( int nendo , 
	double array[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] )
{
	int nenrei[3];
	int tokubetu_shurui[3];
	int shikyu_keitai[3];

	for( nenrei[0] = UNDER_63 ; nenrei[0] <= MAX_JUKYU ; nenrei[0]++ )
	{
		for( tokubetu_shurui[0] = TOKUBETU_MENJO ; tokubetu_shurui[0] <= TOKUBETU_20MAE ; tokubetu_shurui[0]++ )
		{
			for( shikyu_keitai[0] = KIHON ; shikyu_keitai[0] <= KAKYU ; shikyu_keitai[0]++ )
			{

	for( nenrei[1] = 0 ; nenrei[1] <= 1 ; nenrei[1]++ )
	{
		if( nenrei[1] == 0 ){ nenrei[2] = NENREI_SUM; }
		else{ nenrei[2] = nenrei[0]; }

		for( tokubetu_shurui[1] = 0 ; tokubetu_shurui[1] <= 1 ; tokubetu_shurui[1]++ )
		{
			if( tokubetu_shurui[1] == 0 ){ tokubetu_shurui[2] = SUM; }
			else{ tokubetu_shurui[2] = tokubetu_shurui[0]; }

			for( shikyu_keitai[1] = 0 ; shikyu_keitai[1] <= 1 ; shikyu_keitai[1]++ )
			{
				if( shikyu_keitai[1] == 0 ){ shikyu_keitai[2] = SUM; }
				else{ shikyu_keitai[2] = shikyu_keitai[0]; }

				if( tokubetu_shurui[1] == 1 && shikyu_keitai[1] == 1 )
				{
					continue;
				}
				else
				{
					array[nendo - SHONENDO][nenrei[2] - NENREI_SUM]
						[tokubetu_shurui[2]][shikyu_keitai[2]]
					 += array[nendo - SHONENDO][nenrei[0] - NENREI_SUM]
						    [tokubetu_shurui[0]][shikyu_keitai[0]];
				}

			}
		}
	}

			}
		}
	}


	return;

}


void cal_kyufu_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double kyufu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kyufu_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kyufu_nendomatu_P[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][KYUFU_TAISHOU][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] )
{
	int seido;
	int shinkyu;
	int kubun;
	int taishou;
	int shikyu_keitai;
	double zennen;
	double tounen;
	double kaitei;


	for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
	{
		for( shinkyu = NEW ; shinkyu <= OLD ; shinkyu++ )
		{
			for( kubun = ROREI ; kubun <= IZOKU ; kubun++ )
			{
				for( taishou = KYOSHUTU ; taishou <= TOKUBETU ; taishou++ )
				{
					for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
					{
						zennen = kyufu_nendomatu_P[seido][nendo - 1 - SHONENDO][nenrei - 1 - NENREI_SUM]
									[shinkyu][kubun][taishou][shikyu_keitai];

						if( nenrei == UNDER_64 )
						{
							tounen = kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - 1 - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai]
							         + kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
										   [shinkyu][kubun][taishou][shikyu_keitai];
						}
						else
						{
							tounen = kyufu_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
										[shinkyu][kubun][taishou][shikyu_keitai];
						}

						if( nenrei <= UNDER_67 || shikyu_keitai == KAKYU )
						{
							kaitei = kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67];
						}
						else
						{
							kaitei = kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67];
						}

						kyufu[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
							[shinkyu][kubun][taishou][shikyu_keitai]
						 = zennen * ( shiharaiokure + 6 * kaitei ) / 12.
						   + tounen * ( 6 - shiharaiokure ) / 12.;
					}
				}
			}
		}
	}


	return;

}


void cal_kokko_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double kokko[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kokko_nendomatu[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kokko_nendomatu_P[SEIDO_KUBUN][SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[SHINKYU][KYUFU_KUBUN][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] )
{
	int seido;
	int shinkyu;
	int kubun;
	int shikyu_keitai;
	double zennen;
	double tounen;
	double kaitei;


	for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
	{
		for( shinkyu = NEW ; shinkyu <= OLD ; shinkyu++ )
		{
			for( kubun = ROREI ; kubun <= IZOKU ; kubun++ )
			{
				for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
				{
					zennen = kokko_nendomatu_P[seido][nendo - 1 - SHONENDO][nenrei - 1 - NENREI_SUM]
								[shinkyu][kubun][shikyu_keitai];

					if( nenrei == UNDER_64 )
					{
						tounen = kokko_nendomatu[seido][nendo - SHONENDO][nenrei - 1 - NENREI_SUM]
									[shinkyu][kubun][shikyu_keitai]
						         + kokko_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
									   [shinkyu][kubun][shikyu_keitai];
					}
					else
					{
						tounen = kokko_nendomatu[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
									[shinkyu][kubun][shikyu_keitai];
					}

					if( nenrei <= UNDER_67 || shikyu_keitai == KAKYU )
					{
						kaitei = kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67];
					}
					else
					{
						kaitei = kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67];
					}

					kokko[seido][nendo - SHONENDO][nenrei - NENREI_SUM]
						[shinkyu][kubun][shikyu_keitai]
					 = zennen * ( shiharaiokure + 6 * kaitei ) / 12.
					   + tounen * ( 6 - shiharaiokure ) / 12.;
				}
			}
		}
	}


	return;

}


void cal_tokubetukokko_nendokan( int nendo , int nenrei , int shiharaiokure , 
		double tokubetukokko[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double tokubetukokko_nendomatu[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double tokubetukokko_nendomatu_P[SAISHUNENDO - SHONENDO + 1][MAX_JUKYU - NENREI_SUM + 1]
			[TOKUBETU_SHURUI][SHIKYU_KEITAI] ,
		double kaiteiritu[SAISHUNENDO - ECON_SHONENDO + 1][MAX_JUKYU - UNDER_67 + 1] )
{
	int tokubetu_shurui;
	int shikyu_keitai;
	double zennen;
	double tounen;
	double kaitei;


	for( tokubetu_shurui = TOKUBETU_MENJO ; tokubetu_shurui <= TOKUBETU_20MAE ; tokubetu_shurui++ )
	{
		for( shikyu_keitai = KIHON ; shikyu_keitai <= KAKYU ; shikyu_keitai++ )
		{
			zennen = tokubetukokko_nendomatu_P[nendo - 1 - SHONENDO][nenrei - 1 - NENREI_SUM]
						[tokubetu_shurui][shikyu_keitai];

			if( nenrei == UNDER_64 )
			{
				tounen = tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - 1 - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai]
				         + tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM]
							   [tokubetu_shurui][shikyu_keitai];
			}
			else
			{
				tounen = tokubetukokko_nendomatu[nendo - SHONENDO][nenrei - NENREI_SUM]
							[tokubetu_shurui][shikyu_keitai];
			}

			if( nenrei <= UNDER_67 || shikyu_keitai == KAKYU )
			{
				kaitei = kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67];
			}
			else
			{
				kaitei = kaiteiritu[nendo - ECON_SHONENDO][nenrei - UNDER_67];
			}

			tokubetukokko[nendo - SHONENDO][nenrei - NENREI_SUM]
				[tokubetu_shurui][shikyu_keitai]
			 = zennen * ( shiharaiokure + 6 * kaitei ) / 12.
			   + tounen * ( 6 - shiharaiokure ) / 12.;
		}
	}


	return;

}
