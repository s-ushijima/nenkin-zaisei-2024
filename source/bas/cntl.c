#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "snaps.h"
#include "mkiso.h"
#include "mkisosu.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "option.h"

using namespace std;


void cntl( int argc , char *argv[] )
{
	int HIKISU = 17;

	printf( "argc=%d\n" , argc );

	if( argc != HIKISU + 1 )
	{
		printf( "入力された引数が異なります。\n" );
		exit(1);
	}


	kako = atoi( argv[9] );

	if( kako == 0 )
	{
		strcpy( HIYOUSYADATA , argv[3] );
		strcpy( KOKUNENDATA , argv[4] );
	}
	else if( kako == 1 )
	{
		sprintf( HIYOUSYADATA , "%s%s" , KAKO , argv[3] );
		sprintf( KOKUNENDATA , "%s%s" , argv[4] , KAKO );
		strcpy( HIYOUSYADATA_Jurai_KAKO , argv[3] );
		strcpy( KOKUNENDATA_Jurai_KAKO , argv[4] );
	}
	else if( kako == 2 )
	{
		sprintf( HIYOUSYADATA , "%s%s" , KAKO_J , argv[3] );
		sprintf( KOKUNENDATA , "%s%s" , argv[4] , KAKO_J );
		strcpy( HIYOUSYADATA_Jurai_KAKO , argv[3] );
		strcpy( KOKUNENDATA_Jurai_KAKO , argv[4] );
	}

	strcpy( ECON , argv[5] );
	strcpy( SOTOWAKU , argv[6] );
	strcpy( YOBI , argv[8] );
	CARRY = atoi( argv[10] );
	D_MACRO = atoi( argv[11] );
	Option = atoi( argv[12] );
	OPTION_START = atoi( argv[13] );
	OP_HIKIAGE_KANKAKU = atoi( argv[14] );
	TOUGOU = atoi( argv[15] );
	CUT_KOTEI = atoi( argv[16] );
	CUT_ONE_SHUTU = atoi( argv[17] );

	if( Option == 1 )
	{
		strcpy( SOTOWAKU_CUT , argv[7] );
	}
	else
	{
		strcpy( SOTOWAKU_CUT , SOTOWAKU );
	}

	sprintf( Version , "%s-%s-%s-%s" , HIYOUSYADATA , KOKUNENDATA , ECON , SOTOWAKU );

	if ( kako >= 1 )
	{
		sprintf( Version_Jurai , "%s-%s-%s-%s" , HIYOUSYADATA_Jurai_KAKO , KOKUNENDATA_Jurai_KAKO , ECON , SOTOWAKU );
	}

	sprintf( Version_cut , "%s-%s","1120", YOBI );


	T_NENDO = 2120;
	T_DOAI = 1;

	if( CARRY == 1 ){
		Kurikoshim = 1;
	} else {
		Kurikoshim = 0;
	}

	D_M_NENDO = 2025;

	KAISHI1 = 2023;
	KAISHI2 = 2004;
	C_NENDO = 2004;

	MARUME_NENDO = 2025;


	return;

}
