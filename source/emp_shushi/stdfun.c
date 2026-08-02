#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int  rd_drec(char *, double *, int);
void rd_crec(char *, char *, int, int);
void strncpy2(char *, char *, int, int);  
void rd_header(FILE *);
double nround(double, int);


int rd_drec(char *rec, double *ddata, int num_data){
	
	int num_comma;
	int i, j;
	char ctemp[102];	
	
	i = j = 0;
	num_comma = 0;
	ctemp[0] = '\0';
	while(rec[i] != '\0'){
		if(rec[i] == ',' || rec[i] == '\n'){
			ctemp[j] = '\0';
			ddata[num_comma] = atof(ctemp);
			if(num_comma<num_data){
		    	num_comma++;
		    	j = 0;
		    	i++;
			}else{
				printf("rd_drec()が読み込み可能データ数を超えています。[%s]\n", rec);
				exit(1);
			}
		}else{
			ctemp[j] = rec[i];
			j++;
			i++;
			if(j>100){
				printf("読み込みデータの桁数がrd_drec()内のバッファー以上です。\n");
				exit(1);
			}
		}
	}
	return(num_comma);
}


void rd_crec(char *rec, char *cdata, int len_cdata, int loca){
	int num_comma;
	int i, j;
	char ctemp[102];
	
	i = j = 0;
	num_comma = 0;
	
	while(rec[i] != '\0'){
		if(rec[i]==',' || rec[i]=='\n'){
			num_comma++;
			ctemp[j] = '\0';
			if(num_comma==loca){
				if(j<len_cdata){
					strcpy(cdata, ctemp);
					return;
				} else {
					printf("rd_crec:投入データの桁数が代入用変数のサイズを超えています。[%s]\n", ctemp);
					exit(1);
				}
			}else{
				j=0;
				i++;
			}
		} else {
			ctemp[j] = rec[i];
			j++;
			i++;
			if(j>100){
				printf("読み込みデータの桁数がrd_crec()内のバッファー以上です。\n");
				exit(1);
			}
		}
	}
	
	printf("rd_crec:データがありませんでした。\n");
	exit(1);
}


void strncpy2(char *ostr, char *istr, int sh, int len){
	int i;
	
	sh--;
	for(i=0; i<len; i++) ostr[i] = istr[i-sh];
	ostr[len] = '\0';
}


void rd_header( FILE *fp ){
	char char_buffer[500];
	int seido;
	int system;
	int jouhou;
	int Done;
	
	Done = 0;
	
	while( Done == 0 && fgets( char_buffer , 499 , fp ) != NULL ){
		if( char_buffer[0] == '#' )		{
			sscanf( char_buffer, "#%d-%d-%d" , &seido , &system , &jouhou );
			if( seido == 99 ){
				Done = 1;
			}
		}
	}
	if( Done == 0){
		printf("うまくファイルが読み込めていません。\n");
		exit(1);
	}
}




double nround(double x, int n){
	double dtemp;
	
	dtemp = pow(10.0, (double)n);
	
	x *= dtemp;
	
	x = round(x) / dtemp;
	
	return(x);
}



