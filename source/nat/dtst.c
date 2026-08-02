#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mcntl.h"

using namespace std;


void readkisosu_error( int shurui );


void dtst( int shubetu ) 
{
	int nendo;
	int nenrei;
	int counter;
	int counter2;
	int data_number;
	int member;
	int jukyu_nenrei;
	int tokyu;
	int kikan;
	int kubun;
	double buffer[53];
	FILE *fp[13];

	struct hihokensha H_temp[2][MAX_HIHO_NENREI - MIN_HIHO_NENREI + 1][MAX_HIHO_KIKAN + 1];
	struct rorei R_temp[2][MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN];
	struct rorei_kyu K_temp[2][MAX_ROREI_JUKYU - MIN_ROREI_JUKYU + 1][KURI_AGE_SAGE_SHIKYU_KUBUN];
	struct shogai S_temp[3][MAX_SHOGAI_JUKYU - MIN_SHOGAI_JUKYU + 1][SHOGAI_TOKYU];

	switch( shubetu )
	{
		case 2 :
			for( counter = 0 ; counter < 13 ; counter++ )
			{
				fp[counter] = fp_in[DTST_1M + counter];
			}
			break;
		case 3 :
			for( counter = 0 ; counter < 4 ; counter++ )
			{
				fp[counter] = fp_in[DTST_3M + counter];
			}
			break;
		case 5 :
			for( counter = 0 ; counter < 11 ; counter++ )
			{
				fp[counter] = fp_in[DTST_1F + counter];
			}
			break;
		case 6 :
			for( counter = 0 ; counter < 4 ; counter++ )
			{
				fp[counter] = fp_in[DTST_3F + counter];
			}
			break;
		default :
			cout << "指定外のshubetu " << shubetu << " を読み込みました" << endl;
			exit(1);
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		kubun = 14;
	}
	else
	{
		kubun = 3;
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			H_temp[0][nenrei - MIN_HIHO_NENREI][kikan] = Hihokensha_Zero;
			H_temp[1][nenrei - MIN_HIHO_NENREI][kikan] = Taikisha_Zero;
			Hihokensha[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan] = Hihokensha_Zero;
			Taikisha[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan] = Taikisha_Zero;
		}
	}

	for( counter2 = 0 ; counter2 <= 1 ; counter2++ )
	{
		read_data( buffer , fp[counter2] , &data_number );

		for( member = 1 ; member <= kubun ; member++ )
		{
			for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI - 1 ; nenrei++ )
			{
				if( read_data( buffer , fp[counter2] , &data_number ) != EOF )
				{
					if( buffer[0] != counter2 + 1 || buffer[1] != member )
					{
						cout << "被保険者あるいは待期者の読込が正常に行われていません "
							 << buffer[0] << " " << buffer[1] << " " << member << " " << nenrei << endl;
						exit( 1 );
					}
					else
					{
						for( counter = 0 ; counter <= MAX_HIHO_KIKAN - 1 ; counter++ )
						{
							switch( member )
							{
								case 1 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].ninzu
									 = buffer[counter + 3];
									break;

								case 2 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].kikan
									 = buffer[counter + 3] / 12.;
									break;

								case 3 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].noufu
									 = buffer[counter + 3] / 12.;
									break;

								case 4 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[ZENGAKU][1]
									 = buffer[counter + 3] / 12.;
									break;

								case 5 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_3_4][1]
									 = buffer[counter + 3] / 12.;
									break;

								case 6 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_1_2][1]
									 = buffer[counter + 3] / 12.;
									break;

								case 7 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_1_4][1]
									 = buffer[counter + 3] / 12.;
									break;

								case 8 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].gakusei
									 = buffer[counter + 3] / 12.;
									break;

								case 9 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].wakamono
									 = buffer[counter + 3] / 12.;
									break;

								case 10 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].fuka
									 = buffer[counter + 3] / 12.;
									break;

								case 11 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[ZENGAKU][2]
									 = buffer[counter + 3] / 12.;
									break;

								case 12 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_3_4][2]
									 = buffer[counter + 3] / 12.;
									break;

								case 13 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_1_2][2]
									 = buffer[counter + 3] / 12.;
									break;

								case 14 :
									H_temp[counter2][nenrei - MIN_HIHO_NENREI][counter].menjo[MENJO_1_4][2]
									 = buffer[counter + 3] / 12.;
									break;
							}
						}
					}
				}
				else
				{
					readkisosu_error( counter2 + 1 );
				}
			}
		}
	}

	for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
	{
		for( kikan = 0 ; kikan <= MAX_HIHO_KIKAN ; kikan++ )
		{
			Hihokensha[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan]
			 = H_temp[0][nenrei - MIN_HIHO_NENREI][kikan];

			Taikisha[SUIKEISHONENDO - SHONENDO][nenrei - MIN_HIHO_NENREI][kikan]
			 = H_temp[1][nenrei - MIN_HIHO_NENREI][kikan];
		}
	}

	 for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
			R_temp[0][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Zero;
			R_temp[1][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Zero;
			Rorei_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Zero;

			Rorei_Ichibu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU]
				[jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Zero;
		}
	}

	for( counter2 = 0 ; counter2 <= 1 ; counter2++ )
	{
		if( shubetu == 2 || shubetu == 5 )
		{
			read_data( buffer , fp[counter2 + 2] , &data_number );

			for( member = 1 ; member <= 12 ; member++ )
			{
				for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
				{
					if( read_data( buffer , fp[counter2 + 2] , &data_number ) != EOF )
					{
						if( buffer[0] != counter2 + 3 || buffer[1] != member)
						{
							cout << "老齢基礎年金または老齢基礎年金（一部繰り上げ者）の読込が正常に行われていません "
								 << buffer[0] << " " << buffer[1] << " " << member << " " << buffer[3] <<  endl;
							exit( 1 );
						}
						else
						{
							for( counter = 0 ; counter <= 10 ; counter++ )
							{
								switch( member )
								{
									case 1 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].ninzu
										 = buffer[counter + 3];
										break;

									case 2 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].noufu
										 = buffer[counter + 3];
										break;

									case 3 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[ZENGAKU][1]
										 = buffer[counter + 3];
 										break;

									case 4 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_3_4][1]
										 = buffer[counter + 3];
 										break;

									case 5 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_1_2][1]
										 = buffer[counter + 3];
 										break;

									case 6 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_1_4][1]
										 = buffer[counter + 3];
 										break;

									case 7 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].rofuku_shitasasae
										 = buffer[counter + 3];
										break;

									case 8 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].fuka
										 = buffer[counter + 3];
										break;

									case 9 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[ZENGAKU][2]
										 = buffer[counter + 3];
 										break;

									case 10 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_3_4][2]
										 = buffer[counter + 3];
 										break;

									case 11 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_1_2][2]
										 = buffer[counter + 3];
 										break;

									case 12 :
										R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo[MENJO_1_4][2]
										 = buffer[counter + 3];
 										break;
								}
							}
						}
					}
					else
					{
						readkisosu_error( counter2 + 3 );
					}
				}
			}
		}
		else if( shubetu == 3 || shubetu == 6 )
		{
			read_data( buffer , fp[counter2 + 2] , &data_number );

			for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[counter2 + 2] , &data_number ) != EOF )
				{
					if( buffer[0] != counter2 + 3 || buffer[1] != 2 )
					{
						cout << "老齢基礎年金または老齢基礎年金（一部繰り上げ者）の読込が正常に行われていません "
							 << buffer[0] << " " << buffer[1] << " " << member << " " << buffer[3] <<  endl;
						exit( 1 );
					}
					else
					{
						for( counter = 0 ; counter <= 10 ; counter++ )
						{
							R_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].noufu = buffer[counter + 3];
						}
					}
				}
				else
				{
					readkisosu_error( counter2 + 3 );
				}
			}
		}
	}

	 for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
			Rorei_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = R_temp[0][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU];

			Rorei_Ichibu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU]
				[jukyu_nenrei - MIN_ROREI_JUKYU]
			 = R_temp[1][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU];
		}
	}

	for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
			K_temp[0][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Kyu_Zero;
			K_temp[1][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU] = Rorei_Kyu_Zero;
			Rorei_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Kyu_Zero;
			Turo_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Rorei_Kyu_Zero;
		}
	}

	for( counter2 = 0 ; counter2 <= 1 ; counter2++ )
	{
		if( shubetu == 2 || shubetu == 5 )
		{
			read_data( buffer , fp[counter2 + 4] , &data_number );

			for( member = 1 ; member <= 7 ; member++ )
			{
				for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
				{
					if( read_data( buffer , fp[counter2 + 4] , &data_number ) != EOF )
					{
						if( buffer[0] != counter2 + 5 || buffer[1] != member )
						{
							cout << "旧法老齢あるいは通算老齢の読込が正常に行われていません "
								 << buffer[0] << " " << buffer[1] << endl;
							exit( 1 );
						}
						else
						{
							for( counter = 0 ; counter <= 10 ; counter++ )
							{
								switch( member )
								{
									case 1 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].ninzu
										 = buffer[counter + 3];
										break;

									case 2 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].noufu
										 = buffer[counter + 3];
										break;

									case 3 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].menjo
										 = buffer[counter + 3];
										break;

									case 4 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].kasa_noufu
										 = buffer[counter + 3];
										break;

									case 5 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].kasa_menjo
										 = buffer[counter + 3];
										break;

									case 6 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].rofuku_shitasasae
										 = buffer[counter + 3];
										break;

									case 7 :
										K_temp[counter2][nenrei - MIN_ROREI_JUKYU][counter].fuka
										 = buffer[counter + 3];
										break;
								}
							}
						}
					}
					else
					{
						readkisosu_error( counter2 + 4 );
					}
				}
			}
		}
	}

	for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
			Rorei_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = K_temp[0][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU];

			Turo_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = K_temp[1][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU];
		}
	}

	for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
	{
		for( jukyu_nenrei = MIN_ROREI_JUKYU ; jukyu_nenrei <= 70 ; jukyu_nenrei++ )
		{
	 		Gonen_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][jukyu_nenrei - MIN_ROREI_JUKYU]
			 = Gonen_Zero;
		}
	}

	if( shubetu == 2 || shubetu == 5 )
	{
		read_data( buffer , fp[6] , &data_number );

		for( nenrei = MIN_ROREI_JUKYU ; nenrei <= MAX_ROREI_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[6] , &data_number ) != EOF )
			{
				if( buffer[0] != 7 )
				{
					cout << "５年年金の読込が正常に行われていません " << buffer[0] << endl;
					exit( 1 );
				}
				else
				{
					Gonen_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][65 - MIN_ROREI_JUKYU].ninzu
					 = buffer[2];

					Gonen_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_ROREI_JUKYU][65 - MIN_ROREI_JUKYU].noufu
					 = buffer[3];
				}
			}
			else
			{
				readkisosu_error( 6 );
			}
		}
	}

	for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
	{
		for( tokyu = 0 ; tokyu <= 2 ; tokyu++ )
		{
			S_temp[0][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
			S_temp[1][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
			S_temp[2][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
			Shogai_Ippan_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
			Shogai_20mae_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
			Shogai_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu] = Shogai_Zero;
		}
	}

	for( counter2 = 0 ; counter2 <= 2 ; counter2++ )
	{
		if( shubetu == 2 || shubetu == 5 )
		{
			read_data( buffer , fp[counter2 + 7] , &data_number );

			for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
			{
				if( read_data( buffer , fp[counter2 + 7] , &data_number ) != EOF )
				{
					if( buffer[0] != counter2 + 8 )
					{
						cout << "障害基礎（一般）、障害基礎（２０歳前）または旧法障害の読込が正常に行われていません "
							 << buffer[0] << endl;
						exit( 1 );
					}
					else
					{
						for( counter = 0 ; counter <= 9 ; counter++ )
						{
							switch( counter % 5 )
							{
								case 0 :
									S_temp[counter2][nenrei - MIN_SHOGAI_JUKYU][counter / 5 + 1].ninzu
									 = buffer[counter + 2];
									break;

								case 1 :
									S_temp[counter2][nenrei - MIN_SHOGAI_JUKYU][counter / 5 + 1].kihon
									 = buffer[counter + 2];
									break;

								case 2 :
									S_temp[counter2][nenrei - MIN_SHOGAI_JUKYU][counter / 5 + 1].kakyu
									 = buffer[counter + 2];
									break;

								case 3 :
									S_temp[counter2][nenrei - MIN_SHOGAI_JUKYU][counter / 5 + 1].menjo_kihon
									 = buffer[counter + 2];
									break;

								case 4 :
									S_temp[counter2][nenrei - MIN_SHOGAI_JUKYU][counter / 5 + 1].menjo_kakyu
									 = buffer[counter + 2];
									break;
							}
						}
					}
				}
				else
				{
					readkisosu_error( counter2 + 7 );
				}
			}
		}
	}

	for( nenrei = MIN_SHOGAI_JUKYU ; nenrei <= MAX_SHOGAI_JUKYU ; nenrei++ )
	{
		for( tokyu = 0 ; tokyu <= 2 ; tokyu++ )
		{
			Shogai_Ippan_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = S_temp[0][nenrei - MIN_SHOGAI_JUKYU][tokyu];

			Shogai_20mae_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = S_temp[1][nenrei - MIN_SHOGAI_JUKYU][tokyu];

			Shogai_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_SHOGAI_JUKYU][tokyu]
			 = S_temp[2][nenrei - MIN_SHOGAI_JUKYU][tokyu];
		}
	}

	for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
	{
		Izoku_Tuma_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_TUMA_JUKYU] = Izoku_Zero;
	}

	for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
	{
		Izoku_Otto_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_OTTO_JUKYU] = Izoku_Zero;
	}

	if( shubetu == 2 )
	{
		read_data( buffer , fp[10] , &data_number );

		for( nenrei = MIN_IZOKU_TUMA_JUKYU ; nenrei <= MAX_IZOKU_TUMA_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[10] , &data_number ) != EOF )
			{
				if( buffer[0] != 11 )
				{
					cout << "遺族（妻）の読込が正常に行われていません " << buffer[0] << endl;
					exit( 1 );
				}
				else
				{
					for( counter = 0 ; counter <= 2 ; counter++ )
					{
						switch( counter )
						{
							case 0 :
								Izoku_Tuma_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_TUMA_JUKYU].ninzu
								 = buffer[counter + 2];
								break;

							case 1 :
								Izoku_Tuma_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_TUMA_JUKYU].kihon
								 = buffer[counter + 2];
								break;

							case 2 :
								Izoku_Tuma_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_TUMA_JUKYU].kakyu
								 = buffer[counter + 2];
								break;
						}
					}
				}
			}
			else
			{
				readkisosu_error( 10 );
			}
		}
	}

	if( shubetu == 5 )
	{
		read_data( buffer , fp[10] , &data_number );

		for( nenrei = MIN_IZOKU_OTTO_JUKYU ; nenrei <= MAX_IZOKU_OTTO_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[10] , &data_number ) != EOF )
			{
				if( buffer[0] != 11 )
				{
					cout << "遺族（夫）の読込が正常に行われていません " << buffer[0] << endl;
					exit( 1 );
				}
				else
				{
					for( counter = 0 ; counter <= 2 ; counter++ )
					{
						switch( counter )
						{
							case 0 :
								Izoku_Otto_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_OTTO_JUKYU].ninzu
								 = buffer[counter + 2];
								break;

							case 1 :
								Izoku_Otto_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_OTTO_JUKYU].kihon
								 = buffer[counter + 2];
								break;

							case 2 :
								Izoku_Otto_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei- MIN_IZOKU_OTTO_JUKYU].kakyu
								 = buffer[counter + 2];
								break;
						}
					}
				}
			}
			else
			{
				readkisosu_error( 10 );
			}
		}
	}

	for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
	{
		Izoku_Ko_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_KO_JUKYU] = Izoku_Zero;
	}

	if( shubetu == 2 )
	{
		read_data( buffer , fp[11] , &data_number );

		for( nenrei = MIN_IZOKU_KO_JUKYU ; nenrei <= MAX_IZOKU_KO_JUKYU ; nenrei++ )
		{
			if( read_data( buffer , fp[11] , &data_number ) != EOF )
			{
				if( buffer[0] != 12 )
				{
					cout << "遺族（子）の読込が正常に行われていません " << buffer[0] << endl;
					exit( 1 );
				}
				else
				{
					for( counter = 0 ; counter <= 2 ; counter++ )
					{
						switch( counter )
						{
							case 0 :
								Izoku_Ko_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_KO_JUKYU].ninzu
								 = buffer[counter + 2];
								break;

							case 1 :
								Izoku_Ko_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_KO_JUKYU].kihon
								 = buffer[counter + 2];
								break;

							case 2 :
								Izoku_Ko_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_IZOKU_KO_JUKYU].kakyu
								 = buffer[counter + 2];
								break;
						}
					}
				}
			}
			else
			{
				readkisosu_error( 11 );
			}
		}
	}

	for( nenrei = MIN_KAFU_JUKYU ; nenrei <= MAX_KAFU_JUKYU ; nenrei++ )
	{
		Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU] = Kafu_Zero;
		Kafu_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU] = Kafu_Zero;
	}

	if( shubetu == 2 )
	{
		read_data( buffer , fp[12] , &data_number );

		for( nenrei = MIN_KAFU_JUKYU ; nenrei <= 69 ; nenrei++ )
		{
			if( read_data( buffer , fp[12] , &data_number ) != EOF )
			{
				if( buffer[0] != 13 )
				{
					cout << "寡婦年金の読込が正常に行われていません" << buffer[0] << endl;
					exit( 1 );
				}
				else
				{
					if( nenrei <= 64 )
					{
						for( counter = 0 ; counter <= 13 ; counter++ )
						{
							switch( counter )
							{
								case 0 :
									Kafu_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU].ninzu
									 = buffer[counter + 2];
									break;

								case 1 :
									Kafu_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU].noufu
									 = buffer[counter + 2];
									break;

								case 2 :
									Kafu_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[ZENGAKU][1]
									 = buffer[counter + 2];
									break;

								case 3 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU].ninzu
									 = buffer[counter + 2];
									break;

								case 4 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO][nenrei - MIN_KAFU_JUKYU].noufu
									 = buffer[counter + 2];
									break;

								case 5 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[ZENGAKU][1]
									 = buffer[counter + 2];
									break;

								case 6 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_3_4][1]
									 = buffer[counter + 2];
									break;

								case 7 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_1_2][1]
									 = buffer[counter + 2];
									break;

								case 8 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_1_4][1]
									 = buffer[counter + 2];
									break;

								case 9 :
									Kafu_Kyu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[ZENGAKU][2]
									 = buffer[counter + 2];
									break;

								case 10 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[ZENGAKU][2]
									 = buffer[counter + 2];
									break;

								case 11 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_3_4][2]
									 = buffer[counter + 2];
									break;

								case 12 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_1_2][2]
									 = buffer[counter + 2];
									break;

								case 13 :
									Kafu_Nendomatu[SUIKEISHONENDO - SHONENDO]
										[nenrei - MIN_KAFU_JUKYU].menjo[MENJO_1_4][2]
									 = buffer[counter + 2];
									break;
							}
						}
					}
				}
			}
			else
			{
				readkisosu_error( 12 );
			}
		}
	}

	for( nendo= SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		for( nenrei = MIN_HIHO_NENREI ; nenrei <= MAX_HIHO_NENREI ; nenrei++ )
		{
			Ichijikin_Nendomatu[nendo - SHONENDO][nenrei - MIN_HIHO_NENREI] = Ichijikin_Zero;
		}
	}


	return;

}


void readkisosu_error( int shurui )
{
	cout << "基礎数ファイル読み込み中にＥＯＦを検出しました。 基礎数種類は、" << shurui << endl;
	exit(1);
}
