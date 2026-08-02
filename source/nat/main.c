#define MSEID_H_INCLUDED
#define MKISOSU_H_INCLUDED
#define MKISORITU_H_INCLUDED
#define MFILE_OPEN_H_INCLUDED
#define MECON_H_INCLUDED
#define MCNTL_H_INCLUDED
#define SNAPS_H_INCLUDED
#define OPTION_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "snaps.h"
#include "mseid.h"
#include "mcntl.h"
#include "mfile_open.h"
#include "mecon.h"
#include "mkisoritu.h"
#include "mkisosu.h"
#include "option.h"


int main( int argc , char *argv[] )
{
	int nendo;
	int shubetu;

	using namespace std;


	cout << "start" << endl;

	cout << "cntl" << endl;
	cntl( argc , argv );

	printf("The version number of this run is %s.\n", Version) ;

	cout << "file open" << endl;
	file_open( argv[1] , fp_in  , infile_name);
	file_open( argv[2] , fp_out , outfile_name);

	cout << "seid" << endl;
	seid();

	cout << "econ" << endl;
	econ();

	cout << "waku" << endl;
	waku();

	cout << "kaizen" << endl;
	kaizen();

	cout << "noufuritu" << endl;
	noufuritu();

	for( shubetu = 1 ; shubetu <= MAX_SHUBETU - 1 ; shubetu++ )
	{
		if( PerformSiml( shubetu ) )
		{
			switch( shubetu )
			{
				case 2 :
					cout << "１号男子推計" << endl;
					break ;

				case 3 :
					cout << "３号男子推計" << endl;
					break ;

				case 5 :
					cout << "１号女子推計" << endl;
					break ;

				case 6 :
					cout << "３号女子推計" << endl;
					break ;

				default :
					cout << "想定外のshubetuコードを認識 shubetuは " << shubetu << endl;
					exit( 1 );
			}

			cout << "dtst" << endl;
			dtst( shubetu );

			cout << "kiso" << endl;
			kiso( shubetu );

			cout << "shke・siml" << endl;
			shke( SUIKEISHONENDO , shubetu );

			for( nendo = SUIKEISHONENDO + 1 ; nendo <= SUIKEISAISHUNENDO ; nendo++ )
			{
				siml( nendo , shubetu );
				shke( nendo , shubetu );
			}
		}
	}

	cout << "stat" << endl;
	stat();

	cout << "printout" << endl;
	printout();

	cout << "end" << endl;

}


int PerformSiml( int shubetu )
{
	int perform;

	switch( shubetu )
	{
		case 2 :
		case 3 :
		case 5 :
		case 6 :
			perform = 1;
			break ;
		default :
			perform = 0;
			break ;
	}
	return( perform );
}
