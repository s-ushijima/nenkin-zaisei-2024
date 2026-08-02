#include <cstring>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "snaps.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "option.h"

using namespace std;


void cntl( int argc , char *argv[] )
{
	int HIKISU = 15;

	if( argc != HIKISU + 1 )
	{
		printf( "入力された引数が異なります。\n" );
		exit(1);
	}

	Kako_Saimu = atoi( argv[8] ); 
	if( Kako_Saimu == 0 )
	{
		strcpy( KOKUNEN , argv[3] );
		Jyukyusha_Nomi = 0;
	}
	else if( Kako_Saimu == 1 )
	{
		sprintf( KOKUNEN , "%s%s", argv[3] , KAKO );
		Jyukyusha_Nomi = 0;
	}
	else if( Kako_Saimu == 2 )
	{
		sprintf( KOKUNEN , "%s%s", argv[3], KAKO_J );
		Kako_Saimu = 1;
		Jyukyusha_Nomi = 1;
	}

	strcpy( ECON , argv[4] );
	strcpy( SOTOWAKU , argv[5] );
	strcpy( BIRTHFILE , argv[6] );
	strcpy( DEATH , argv[7] );
	TINSURA = atoi( argv[9] );
	Part = atoi( argv[10] );
	Part_Year = atoi( argv[11] );
	Option = atoi( argv[12] );
	OPTION_START = atoi( argv[13] );
	OP_HIKIAGE_KANKAKU = atoi( argv[14] );
	strcpy( SOTOWAKU_JURAI , argv[15] );

	sprintf( Version , "%s-%s-%s" , KOKUNEN , ECON , SOTOWAKU );

	Kugiri_Nendo = 2024;

	Kisai_Shitasasae = 0.80;


	return;

}
