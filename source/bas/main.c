#define MCNTL_H_INCLUDED
#define MECON_H_INCLUDED
#define MFILE_OPEN_H_INCLUDED
#define MKISO_H_INCLUDED
#define MKISOSU_H_INCLUDED
#define OPTION_H_INCLUDED
#define SNAPS_H_INCLUDED
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mcntl.h"
#include "mecon.h"
#include "mkisosu.h"
#include "mfile_open.h"
#include "mkiso.h"
#include "option.h"

using namespace std;


int main( int argc , char *argv[] )
{
	int seido;

	cout << "start" << endl;
	cout << "cntl" << endl;
	cntl( argc , argv );

	cout << "The version number of this run is " << Version << "-" << Version_cut << "." << endl;

	cout << "file_open" << endl;
	file_open( argv[1] , fp_in  , infile_name );
	file_open( argv[2] , fp_out , outfile_name );

	cout << "dtst" << endl;
	dtst();

	fclose( fp_in[zisseki_hosei] );


	cout << "econ" << endl;
	econ();

	fclose( fp_in[KEIZAI] );
	fclose( fp_in[KAITEI] );
	fclose( fp_in[TANNEN_CUT] );


	cout << "read kokunen_jisseki" << endl;
	ReadKokunen_jisseki();

	for( seido = KOUNEN ; seido <= SHIGAKU ; seido++ )
	{
		switch( seido ) 
		{
			case KOUNEN :
				cout << "read kounen" << endl;
				break;

			case KOKKYO :
				cout << "read kokkyo" << endl;
				break;

			case CHIKYO :
				cout << "read chikyo" << endl;
				break;

			case SHIGAKU :
				cout << "read shigaku" << endl;
				break;

			default :
				cout << "指定外の数字を検出しました" << endl;
				exit( 1 );
		}

		ReadHiyousha( seido );
	}


	cout << "waku" << endl;
	waku();

	for( seido = KOKUNEN_1GOU ; seido <= SHIGAKU_3GOU ; seido++ )
	{
		fclose( fp_in[seido] );
	}


	cout << "tumatumi_cal_jisseki" << endl;
	tumatumi_cal_jisseki();


	cout << "給付水準調整前 給付費" << endl;
	Atamawari();


	cout << "read_flie" << endl;
	read_file();

	fclose( fp_in[0] );


	cout << "flie_write_kakyu" << endl;
	file_write_kakyu();


	cout << "printout" << endl;
	printout( 0 );


	cout << "カットファイル作成" << endl;

	if( kako == 0 )
	{
		if( CUT_KOTEI == 0 )
		{
			cout << "方式１（有限均衡・積立度合）" << endl;
			cout << "tyousei" << endl;
			tyousei();

			cout << "file_write" << endl;
			file_write_cut();

			fprintf( fp_out[SETTEI] , "カット終了年度     %d\n" , S_C_NENDO );
		}

		if( CUT_KOTEI == 1 )
		{
			cout << "read_cut" << endl;
			read_cut();

			cout << "dokuzi_cal" << endl;
			dokuzi_cal();
		}
	}
	else if( kako >= 1 )
	{
		cout << "過去債務推計" << endl;

		cout << "read_cut" << endl;
		read_cut();

		cout << "dokuzi_cal" << endl;
		dokuzi_cal();
	}

	cout << "給付水準調整後 給付費" << endl;
	cout << "頭割り" << endl;
	Atamawari();

	cout << "printout" << endl;
	printout( 1 );

	fprintf( fp_out[SETTEI] , "\n" );

	cout << "end" << endl;

}
