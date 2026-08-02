#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mcntl.h"
#include "mecon.h"
#include "mkiso.h"
#include "option.h"
#include <cmath>

using namespace std;


void printout( int cut_ba )
{
	int nendo;
	int seido;
	int goubetu;
	int sotai_nendo;
	int shinkyu;
	int kubun;
	int tokubetu_shurui;
	double tumitateunyou;
	int kokatu_nendo;
	int outfile;
	double Temp_Ichijikin[SAISHUNENDO - SHONENDO + 1][3];
	double Temp_Kafu[SAISHUNENDO - SHONENDO + 1][4];

	if( cut_ba == 0 )
	{
		outfile = KEKKA_b;

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			Temp_Ichijikin[nendo - SHONENDO][SUM] = Ichijikin[nendo - SHONENDO][SUM];
			Temp_Ichijikin[nendo - SHONENDO][NOUFU] = Ichijikin[nendo - SHONENDO][NOUFU];
			Temp_Ichijikin[nendo - SHONENDO][FUKA] = Ichijikin[nendo - SHONENDO][FUKA];

			Temp_Kafu[nendo - SHONENDO][SUM] = Kafu[nendo - SHONENDO][SUM];
			Temp_Kafu[nendo - SHONENDO][NEW] = Kafu[nendo - SHONENDO][NEW];
			Temp_Kafu[nendo - SHONENDO][OLD_NOUFU] = Kafu[nendo - SHONENDO][OLD_NOUFU];
			Temp_Kafu[nendo - SHONENDO][OLD_MENJO] = Kafu[nendo - SHONENDO][OLD_MENJO];
		}

		for( nendo = KAISHI1 ; nendo <= SAISHUNENDO ; nendo++ )
		{
			Tumitate[nendo - SHONENDO]
			 = Tumitate[nendo - 1 - SHONENDO] * interest_rate[nendo - ECON_SHONENDO]
			  + ( Hokenryou_y[nendo - SHONENDO] + Fuka_Hokenryou_y[nendo - SHONENDO]
			     + Kyoshutukin_Kokko[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
			     + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
			     + Yuushi_Saiken[nendo - SHONENDO]
				 + Kodomo_Noufukin[nendo - SHONENDO]
		    	 - Kyoshutukin[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
			     - Ichijikin[nendo - SHONENDO][NOUFU] - Ichijikin[nendo - SHONENDO][FUKA] * 3. / 4.
			     - Kafu[nendo - SHONENDO][NEW] - Kafu[nendo - SHONENDO][OLD_NOUFU]
			     - Fuka[nendo - SHONENDO][SUM] * 3. / 4.
			     - Fukushi[nendo - SHONENDO] )
			   * pow( interest_rate[nendo - ECON_SHONENDO] , 1. / 2. );
		}
	}
	else if( cut_ba == 1 )
	{
		outfile = KEKKA_a;

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			Temp_Ichijikin[nendo - SHONENDO][SUM] = Ichijikin_Cut[nendo - SHONENDO][SUM];
			Temp_Ichijikin[nendo - SHONENDO][NOUFU] = Ichijikin_Cut[nendo - SHONENDO][NOUFU];
			Temp_Ichijikin[nendo - SHONENDO][FUKA] = Ichijikin_Cut[nendo - SHONENDO][FUKA];

			Temp_Kafu[nendo - SHONENDO][SUM] = Kafu_Cut[nendo - SHONENDO][SUM];
			Temp_Kafu[nendo - SHONENDO][NEW] = Kafu_Cut[nendo - SHONENDO][NEW];
			Temp_Kafu[nendo - SHONENDO][OLD_NOUFU] = Kafu_Cut[nendo - SHONENDO][OLD_NOUFU];
			Temp_Kafu[nendo - SHONENDO][OLD_MENJO] = Kafu_Cut[nendo - SHONENDO][OLD_MENJO];
		}
	}


	fprintf( fp_out[outfile] , "試算番号," );
	fprintf( fp_out[outfile] , "%s-%s" , Version, Version_cut );
	if( cut_ba == 0 )
	{
		fprintf( fp_out[outfile] , "b\n" );
	}
	else if( cut_ba == 1 )
	{
		fprintf( fp_out[outfile] , "a\n" );
	}

	kokatu_nendo = -1;
	for( nendo = KAISHI1 - 1 ; nendo <= SAISHUNENDO - 5 ; nendo++ )
	{
		if( Tumitate[nendo - SHONENDO] < 0.)
		{
			kokatu_nendo = nendo;

			fprintf( fp_out[OUTPUT] , "%d," , kokatu_nendo );
			break;
		}
	}

	fprintf( fp_out[outfile] , "カット終了年度," );
	if( cut_ba == 1 && CUT_KOTEI == 0 )
	{
		if( kokatu_nendo == -1 )
		{
			fprintf( fp_out[outfile] , "%d\n" , S_C_NENDO );
		}
		else
		{
			printf( "国年が%d年度に枯渇しました\n" , kokatu_nendo );
			fprintf( fp_out[outfile] , "国年が%d年度に枯渇しました\n" , kokatu_nendo );
		}
	}
	else
	{
		fprintf( fp_out[outfile] , "\n" );
	}

	fprintf( fp_out[outfile] , "最終カット率," );
	if( cut_ba == 1 && CUT_KOTEI == 0 && kako == 0 )
	{
		if( kokatu_nendo == -1 )
		{
			fprintf( fp_out[outfile] , "%20.14e\n" , 
				cut_ruiseki[S_C_NENDO - ECON_SHONENDO][S_C_NENDO - ECON_SHONENDO][UNDER_63 - NENREI_SUM] );
		}
		else
		{
			fprintf( fp_out[outfile] , "%20.14e\n" , 
				cut_ruiseki[kokatu_nendo - ECON_SHONENDO][kokatu_nendo - ECON_SHONENDO][UNDER_63 - NENREI_SUM] );
		}
	}
	else
	{
		fprintf( fp_out[outfile] , "\n" );
	}


	fprintf( fp_out[outfile] , "\n" );
	fprintf( fp_out[outfile] , "\n" );
	fclose( fp_out[OUTPUT] );



	for( shinkyu = SUM ; shinkyu <= OLD ; shinkyu++ )
	{
		switch ( shinkyu )
		{
			case SUM :
				fprintf( fp_out[outfile] , "基礎年金給付費（新法＋旧法）\n" );
				break;
			case NEW :
				fprintf( fp_out[outfile] , "基礎年金給付費（新法）\n" );
				break;
			case OLD :
				fprintf( fp_out[outfile] , "基礎年金交付金\n" );
				break;
		}

		fprintf( fp_out[outfile] , ",合計,,,,,");
		fprintf( fp_out[outfile] , ",老齢,,,,,");
		fprintf( fp_out[outfile] , ",障害,,,,,");
		fprintf( fp_out[outfile] , ",遺族,,,,,\n");

		fprintf( fp_out[outfile] , ",制度計,国年,厚年,国共,地共,私学");
		fprintf( fp_out[outfile] , ",制度計,国年,厚年,国共,地共,私学");
		fprintf( fp_out[outfile] , ",制度計,国年,厚年,国共,地共,私学");
		fprintf( fp_out[outfile] , ",制度計,国年,厚年,国共,地共,私学\n");

		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;

			fprintf( fp_out[outfile] , "%15d" , nendo );

			for( kubun = SUM ; kubun <= IZOKU ; kubun++ )
			{
				for( seido = SUM ; seido <= SHIGAKU ; seido++ )
				{
					fprintf( fp_out[outfile] , ",%20.14le" , 
						Kyufu[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][shinkyu][kubun][SUM][SUM] );
				}
			}

			fprintf( fp_out[outfile] , "\n" );
		}
	}


	fprintf( fp_out[outfile] , "基礎年金拠出金\n");
	fprintf( fp_out[outfile] , ",単価,合計,国年,厚年,国共,地共,私学\n");

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[outfile] , "%15d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , Tanka[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );
		for( seido = SUM ; seido <= SHIGAKU ; seido++ )
		{
			fprintf( fp_out[outfile] , "%20.14le," , 
				Kyoshutukin[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );
		}

		fprintf( fp_out[outfile] , "\n" );
	}


	fprintf( fp_out[outfile] , "基礎年金拠出金（国庫）\n" );
	fprintf( fp_out[outfile] , ",単価,国庫負担割合(年度末),合計,国年,厚年,国共,地共,私学," );
	fprintf( fp_out[outfile] , "合計,老齢,障害,遺族\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[outfile] , "%15d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , Tanka_Kokko[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );
		fprintf( fp_out[outfile] , "%20.14le," , Kokko_Wariai[nendo - ( SHONENDO - 1 )] );
		for( seido = SUM ; seido <= SHIGAKU ; seido++ )
		{
			fprintf( fp_out[outfile] , "%20.14le," , 
				Kyoshutukin_Kokko[seido][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );
		}

		for( kubun = SUM ; kubun <= IZOKU ; kubun++ ){
			fprintf( fp_out[outfile], "%20.14le," , 
				Kokko[SUM][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM][kubun][SUM] );
		}

		fprintf( fp_out[outfile] , "\n" );
	}


	fprintf( fp_out[outfile] , "拠出金算定対象者\n" );
	fprintf( fp_out[outfile] , ",合計,１号," );
	fprintf( fp_out[outfile] , "厚年２号,厚年３号,国共２号,国共３号,地共２号,地共３号,私学２号,私学３号," );
	fprintf( fp_out[outfile] , "産休免除者（１号再掲）,育休免除者（１号再掲）,付加納付者（１号再掲）\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[outfile] , "%15d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , SanteiTaishou[SUM][sotai_nendo][SUM] );
		fprintf( fp_out[outfile] , "%20.14le," , SanteiTaishou[KOKUNEN][sotai_nendo][1] );

		for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
		{
			for( goubetu = 2 ; goubetu <= 3 ; goubetu++ )
			{
				fprintf( fp_out[outfile] , "%20.14le," , SanteiTaishou[seido][sotai_nendo][goubetu] );
			}
		}

		fprintf( fp_out[outfile] , "%20.14le," , Sankyu_Taishou[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Ikukyu_Taishou[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Fuka_Ninzu[nendo - SHONENDO] );

		fprintf( fp_out[outfile] , "\n" );
	}


	fprintf( fp_out[outfile] , "特別国庫負担内訳\n" );
	fprintf( fp_out[outfile] , ",合計,免除,嵩上げ（納付）,嵩上げ（免除）,老福下支え,５年年金,２０歳前\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[outfile] , "%15d,", nendo );

		for( tokubetu_shurui = SUM ; tokubetu_shurui <= TOKUBETU_20MAE ; tokubetu_shurui++ )
		{
			fprintf( fp_out[outfile] , "%20.14le,", 
				Tokubetukokko[sotai_nendo][NENREI_SUM - NENREI_SUM][tokubetu_shurui][SUM] );
		}

		fprintf( fp_out[outfile] , "\n");
	}


	fprintf( fp_out[outfile] , "独自給付費等\n" );
	fprintf( fp_out[outfile] , ",死亡一時金納付分,死亡一時金付加分," );
	fprintf( fp_out[outfile] , "新法寡婦年金,旧法寡婦年金免除分以外,旧法寡婦年金免除分,付加年金," );
	fprintf( fp_out[outfile] , "１号被保険者数,保険料収入（国年）,保険料収入（付加年金）," );
	fprintf( fp_out[outfile] , "住宅融資債権,業務勘定への繰入,こども子育て特別会計から繰入\n" );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[outfile] , "%d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Ichijikin[nendo - SHONENDO][NOUFU] );
		fprintf( fp_out[outfile] , "%20.14le," , Temp_Ichijikin[nendo - SHONENDO][FUKA] );
		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[nendo - SHONENDO][NEW] );
		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[nendo - SHONENDO][OLD_NOUFU] );
		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[nendo - SHONENDO][OLD_MENJO] );
		fprintf( fp_out[outfile] , "%20.14le," , Fuka[nendo - SHONENDO][SUM] );
		fprintf( fp_out[outfile] , "%20.14le," , Hiho_Kokunen[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Hokenryou_y[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Fuka_Hokenryou_y[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Yuushi_Saiken[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , Fukushi[nendo - SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le" , Kodomo_Noufukin[nendo - SHONENDO] );

		fprintf( fp_out[outfile] , "\n");
	}


	fprintf( fp_out[outfile] , "経済前提\n" );
	fprintf( fp_out[outfile] , ",物価上昇率,賃金上昇率,運用利回り," );
	fprintf( fp_out[outfile] , "改定率（マクロ込み、67歳）,改定率（マクロ込み、68歳）,改定率（マクロ込み、88歳）," );
	fprintf( fp_out[outfile] , "特別調整率（67歳）,特別調整率（68歳）,特別調整率（88歳）\n" );

	for( nendo = ECON_SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[outfile] , "%d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , cpi_up[nendo - ECON_SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , base_up[nendo - ECON_SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , interest_rate[nendo - ECON_SHONENDO] );
		fprintf( fp_out[outfile] , "%20.14le," , kaiteiritu[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
		fprintf( fp_out[outfile] , "%20.14le," , kaiteiritu[nendo - ECON_SHONENDO][68 - UNDER_67] );
		fprintf( fp_out[outfile] , "%20.14le," , kaiteiritu[nendo - ECON_SHONENDO][88 - UNDER_67] );
		fprintf( fp_out[outfile] , "%20.14le," , T[nendo - ECON_SHONENDO][UNDER_67 - UNDER_67] );
		fprintf( fp_out[outfile] , "%20.14le," , T[nendo - ECON_SHONENDO][68 - UNDER_67] );
		fprintf( fp_out[outfile] , "%20.14le" , T[nendo - ECON_SHONENDO][88 - UNDER_67] );

		fprintf( fp_out[outfile] , "\n");
	}


	fprintf( fp_out[outfile] , "妻積（各制度への分配額）\n" );
	fprintf( fp_out[outfile] , ",国年,厚年,国共,地共,私学,妻積残額,国年積立金\n" );

	fprintf( fp_out[outfile] , "%d（原価）," , TUMATUMI_NENDO - 1 );
	fprintf( fp_out[outfile] , "%20.14e," , 0. );
	for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
	{
		fprintf( fp_out[outfile] , "%20.14e," , 0. );
	}
	fprintf( fp_out[outfile] , "%20.14e\n" , Tumatumi_2014[SUM] );

	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		fprintf( fp_out[outfile] , "%d," , nendo );

		for( seido = KOKUNEN ; seido <= SHIGAKU ; seido++ )
		{
			fprintf( fp_out[outfile] , "%20.14e," , Tumatumi[seido][nendo - TUMATUMI_NENDO] );
		}
		fprintf( fp_out[outfile] , "%20.14e," , Tumatumi[SUM][nendo - TUMATUMI_NENDO] );
		fprintf( fp_out[outfile] , "%20.14e" , Tumitate[nendo - SHONENDO] );

		fprintf( fp_out[outfile] , "\n" );
	}


	fprintf( fp_out[outfile] , "\n");



	fprintf( fp_out[outfile] , "\n" );
	fprintf( fp_out[outfile] , "収支見通し\n" );

	int shunyu_cnt = 13;
	int shishutu_cnt = 10;
	int sonota_cnt = 2;
	int i = 0;

	const char *head[]
		={
			"保険料月額" , "保険料収入（国年）" , "保険料収入（付加年金）" , "運用収入" , 
			"国庫（基礎年金）" , "国庫（特別国庫）" , 
			"国庫（死亡一時金付加分）" , "国庫（付加年金）" , "国庫（旧法寡婦年金免除分）" , 
			"住宅融資債権" , "妻積み" , "こども子育て特別会計から繰入" , "収入合計" , 
			"支出合計" , "死亡一時金納付分" , "死亡一時金付加分" , 
			"新法寡婦年金" , "旧法寡婦年金免除分以外" , "旧法寡婦年金免除分" , "付加年金" , 
			"基礎年金拠出金" , "基礎年金拠出金（特別国庫）" , "業務勘定への繰入" , 
			"年度末積立金","保険料改定率"
		 };


	fprintf( fp_out[outfile] , "," );
	for( i = 0 ; i < shunyu_cnt + shishutu_cnt + sonota_cnt ; i++ )
	{
		if( i == 0 )
		{
			fprintf( fp_out[outfile] , "収入" );
		}
		else if( i == shunyu_cnt )
		{
			fprintf( fp_out[outfile] , "支出" );
		}
		else if( i == shunyu_cnt + shishutu_cnt )
		{
			fprintf( fp_out[outfile] , "その他" );
		}
		fprintf( fp_out[outfile] , "," , head[i] );
	}
	fprintf( fp_out[outfile] , "\n" );

	fprintf( fp_out[outfile] , "年度," );
	for( i = 0 ; i < shunyu_cnt + shishutu_cnt + sonota_cnt ; i++ )
	{
		fprintf( fp_out[outfile] , "%s," , head[i] );
	}
	fprintf( fp_out[outfile] , "\n" );


	for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
	{
		sotai_nendo = nendo - SHONENDO;

		fprintf( fp_out[outfile] , "%d," , nendo );

		fprintf( fp_out[outfile] , "%20.14le," , Hokenryou_m[sotai_nendo][0] );

		fprintf( fp_out[outfile] , "%20.14le," , Hokenryou_y[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14le," , Fuka_Hokenryou_y[sotai_nendo] );

		if( nendo == SHONENDO )
		{
			tumitateunyou = 0.;
		}
		else
		{
			tumitateunyou
		 	 = Tumitate[nendo - 1 - SHONENDO] * ( interest_rate[nendo - ECON_SHONENDO] - 1 )
			  + ( Hokenryou_y[nendo - SHONENDO] + Fuka_Hokenryou_y[nendo - SHONENDO]
				 + Kyoshutukin_Kokko[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
				 + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
				 + Yuushi_Saiken[nendo - SHONENDO]
				 + Kodomo_Noufukin[nendo - SHONENDO]
				 - Kyoshutukin[KOKUNEN][nendo - SHONENDO][NENREI_SUM - NENREI_SUM][SUM]
				 - Fuka[nendo - SHONENDO][SUM] * 3. / 4.
				 - Temp_Ichijikin[nendo - SHONENDO][NOUFU] - Temp_Ichijikin[nendo - SHONENDO][FUKA] * 3. / 4.
				 - Temp_Kafu[nendo - SHONENDO][NEW] - Temp_Kafu[nendo - SHONENDO][OLD_NOUFU]
				 - Fukushi[nendo - SHONENDO] )
			  * ( pow( interest_rate[nendo - ECON_SHONENDO] , 1. / 2. ) - 1 );
		}
		fprintf( fp_out[outfile] , "%20.14le," , tumitateunyou );

		fprintf( fp_out[outfile] , "%20.14le," , 
			Kyoshutukin_Kokko[KOKUNEN][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );

		fprintf( fp_out[outfile] , "%20.14le," , 
			Tokubetukokko[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM][SUM] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Ichijikin[sotai_nendo][FUKA] / 4. );

		fprintf( fp_out[outfile] , "%20.14le," , Fuka[sotai_nendo][SUM] / 4. );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[sotai_nendo][OLD_MENJO] );

		fprintf( fp_out[outfile] , "%20.14le," , Yuushi_Saiken[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14le," , Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO] );

		fprintf( fp_out[outfile] , "%20.14le," , Kodomo_Noufukin[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14le," , 
			Hokenryou_y[sotai_nendo] + Fuka_Hokenryou_y[sotai_nendo] + tumitateunyou
			 + Kyoshutukin_Kokko[KOKUNEN][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
			 + Tokubetukokko[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM][SUM]
			 + Temp_Ichijikin[sotai_nendo][FUKA] / 4. + Fuka[sotai_nendo][SUM] / 4.
			 + Temp_Kafu[sotai_nendo][OLD_MENJO]
			 + Yuushi_Saiken[sotai_nendo] + Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO]
			 + Kodomo_Noufukin[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14le," , 
			Temp_Ichijikin[sotai_nendo][NOUFU] + Temp_Ichijikin[sotai_nendo][FUKA]
			 + Temp_Kafu[sotai_nendo][NEW] + Temp_Kafu[sotai_nendo][OLD_NOUFU] + Temp_Kafu[sotai_nendo][OLD_MENJO]
			 + Fuka[sotai_nendo][SUM]
			 + Kyoshutukin[KOKUNEN][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM]
			 + Tokubetukokko[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM][SUM]
			 + Fukushi[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Ichijikin[sotai_nendo][NOUFU] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Ichijikin[sotai_nendo][FUKA] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[sotai_nendo][NEW] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[sotai_nendo][OLD_NOUFU] );

		fprintf( fp_out[outfile] , "%20.14le," , Temp_Kafu[sotai_nendo][OLD_MENJO] );

		fprintf( fp_out[outfile] , "%20.14le," , Fuka[sotai_nendo][SUM] );

		fprintf( fp_out[outfile] , "%20.14le," , Kyoshutukin[KOKUNEN][sotai_nendo][NENREI_SUM - NENREI_SUM][SUM] );

		fprintf( fp_out[outfile] , "%20.14le," , Tokubetukokko[sotai_nendo][NENREI_SUM - NENREI_SUM][SUM][SUM] );

		fprintf( fp_out[outfile] , "%20.14le," , Fukushi[sotai_nendo] );

		fprintf( fp_out[outfile] , "%20.14e," , Tumitate[nendo - SHONENDO] );

		fprintf( fp_out[outfile] , "%20.14le," , kakaku[nendo - ECON_SHONENDO] );

		fprintf( fp_out[outfile] , ",\n" );
	}

	fclose( fp_out[outfile] );



	if( cut_ba == 0 && TOUGOU == 1 )
	{
		fprintf( fp_out[PROVIDE] , 
			"年度,保険料収入,一時金付加分国庫,付加年金国庫,その他収入（融資債権）,その他収入（妻積）\n" );
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			sotai_nendo = nendo - SHONENDO;
			fprintf( fp_out[PROVIDE] , "%d," , nendo-2000 );

			fprintf( fp_out[PROVIDE] , "%20.14le," , 
				Hokenryou_y[nendo - SHONENDO]
				 + Fuka_Hokenryou_y[nendo - SHONENDO]
				 + Kodomo_Noufukin[nendo - SHONENDO] );
			fprintf( fp_out[PROVIDE] , "%20.14le," , Ichijikin[nendo - SHONENDO][FUKA]/4);
			fprintf( fp_out[PROVIDE] , "%20.14le," , Fuka[nendo - SHONENDO][SUM]/4);
			fprintf( fp_out[PROVIDE] , "%20.14le," , Yuushi_Saiken[nendo - SHONENDO]);
			fprintf( fp_out[PROVIDE] , "%20.14le," , Tumatumi[KOKUNEN][nendo - TUMATUMI_NENDO] );
			fprintf( fp_out[PROVIDE] , "\n" );
		}
		fprintf( fp_out[PROVIDE] , "\n" );


		fprintf( fp_out[PROVIDE] , "独自給付費等（年度間値）\n" );
		fprintf( fp_out[PROVIDE] , "年度,一時金納付分,一時金付加分,付加年金," );
		fprintf( fp_out[PROVIDE] , "業務勘定への繰入\n" );
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			fprintf( fp_out[PROVIDE] , "%d," , nendo-2000 );
		
			fprintf( fp_out[PROVIDE] , "%20.14le," , Ichijikin[nendo - SHONENDO][NOUFU] );
			fprintf( fp_out[PROVIDE] , "%20.14le," , Ichijikin[nendo - SHONENDO][FUKA] );
			fprintf( fp_out[PROVIDE] , "%20.14le," , Fuka[nendo - SHONENDO][SUM] );
			fprintf( fp_out[PROVIDE] , "%20.14le\n" , Fukushi[nendo - SHONENDO] );
		}
		fprintf( fp_out[PROVIDE] , "\n" );

		fprintf( fp_out[PROVIDE] , "独自給付費等（年度末値）\n" );
		fprintf( fp_out[PROVIDE] , "年度,新法寡婦年金\n" );
		for( nendo = SHONENDO ; nendo <= SAISHUNENDO ; nendo++ )
		{
			fprintf( fp_out[PROVIDE] , "%d," , nendo-2000 );
			fprintf( fp_out[PROVIDE] , "%20.14le\n" , Kafu_Nendomatu[nendo - SHONENDO][NEW] );
		}
		fprintf( fp_out[PROVIDE] , "\n" );
	}


	return;

}
