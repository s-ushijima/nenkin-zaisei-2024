#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"


void flck(void){
	FILE *ifp;
	int i, j, is, ie;
	char char_buffer[500];
	int seido, system, jouhou;
	int Done;
	
	if(Seidn!=0){
		is=ie=0;
	} else {
		if(Cntlset==1) is=0;
		else           is=1;
		ie=4;
	}
	
	for(i=0; i<=5; i++){  
		if(Seidn!=0 && i>=1 && i<=4) continue;
		if(Seidn==0 && i==0) continue;
		
		if(i>=0 && i<=4){
			ifp = ifp10_usys[i];
		} else if(i==5) {
			ifp = ifp_kyos;
		} else {
			printf("想定外のループです(flck.c)\n");
			exit(1);
		}
		
		Done = 0;
		while(Done == 0){
			if(fgets( char_buffer , 499 , ifp ) == NULL ) break;
			if( char_buffer[0] == '#' ){
				sscanf( char_buffer, "#%d-%d-%d" , &seido , &system , &jouhou );
				if( seido == 99 ){
					Done++;
				}
			}
			if(Done == 0){
				if(i!=5){
					fprintf(ofp01_shushi[i], "%s", char_buffer);
					if(Cntlset==1)
					  fprintf(ofp01_shushi[0], "%s", char_buffer);
				} else {
					for(j=is; j<=ie; j++){
						fprintf(ofp01_shushi[j], "%s", char_buffer);
					}
				}
			}
		}
		if(Done == 0){
			printf("うまくファイルが読み込めていません。\n");
			exit(1);
		}
	}
	
	for(i=is; i<=ie; i++){
		fprintf(ofp01_shushi[i], "#03-0002-0001\n");
		fprintf(ofp01_shushi[i], "#03-0002-0002\n");
		fprintf(ofp01_shushi[i], "#03-0002-0003\n");
		fprintf(ofp01_shushi[i], "#99-0000-0000\n");
		
		if(Saimu==0){
			fprintf(ofp01_shushi[i], "%s, %s, %s\n", Nfile, Nfile2, Nfile3);
		} else {
			fprintf(ofp01_shushi[i], "%s, %s, %s, %s\n", Saimushu, Nfile, Nfile2, Nfile3);
		}
		
		fprintf(ofp01_shushi[i], "%s, %s\n", Ecfile, Wcfile);
		
		if(Saimu==0){
			fprintf(ofp01_shushi[i], "%s\n", Nkfile);
		} else {
			fprintf(ofp01_shushi[i], "%s, %s\n", Saimuski, Nkfile);
		}
		
		fprintf(ofp01_shushi[i], "%s, 予備:, %s, Cntlset:, %d, Seidn:, %d,  ii:, %d\n",
		                          Sifile, Cutrfile4, Cntlset, Seidn, i);
		
		fprintf(ofp01_shushi[i], "\n");
	}
}

