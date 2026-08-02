#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glvam.h"



void init_gval(void);	 
void set_filenum(void);  

void cntl(void);	     
void econ(void);	     
void rdfl(void);	     
void shus(void);	     
void alfopen(void);	     
void alfclose(void);	 
void flck(void);         


int main(int ac, char **av){
	
	printf("\n<< 初期化等の処理 >>\n\n");
	init_gval();
	
	printf("<< Cntl開始 >>\n");
	cntl();
	set_filenum();
	
	printf("\n<< FileOpen開始 >>\n\n");
	alfopen();
	
	printf("<< FileCheck開始 >>\n\n");
	flck();
	
	printf("<< Econ開始 >>\n\n");
	econ();
	
	printf("<< Rdfl開始 >>\n\n");
	rdfl();
	
	printf("<< Shus開始 >>\n\n");
	shus();
	
	printf("\n<< FileClose開始 >>\n\n");
	alfclose();
	
	return 0;
}



void init_gval(void){

	int k, x;
	
	for(k=ECSTY; k<=ECEDY; k++){
		for(x=ECXA; x<116; x++){
			Kra[k-ECSTY][x-ECXA] = Krb[k-ECSTY][x-ECXA] = 1.0;
			
			Scutrrh[k-ECSTY][x-ECXA] = Scutrrt[k-ECSTY][x-ECXA] = 1.0;
			Scutrrki[k-ECSTY][x-ECXA] = 1.0;
			Escutrrh[k-ECSTY][x-ECXA] = Escutrrt[k-ECSTY][x-ECXA] = 1.0;
			Tokutyo[k-ECSTY][x-ECXA] = 1.0;
		}
	}
}



void set_filenum(){
	
	int itemp, itemp2;
	char ctemp[10];
	
	printf("\n試算番号を入力して下さい\n");
	scanf("%s%*c", Nfile);
	
	strcpy(Nfile2, Nfile);
	
	strcpy(Nfile3, Nfile);
	
	strcpy(Nkfile, Nfile);
	
	printf("\n経済前提番号を入力して下さい（４桁）\n");
	scanf("%s%*c", Ecfile);
	
	printf("\n外枠番号を入力して下さい（４桁）\n");
	scanf("%s%*c", Wcfile);
	itemp=atoi(Wcfile);
	if(itemp<1000 || 9999<itemp){
		printf("  外枠番号の設定が不適切です。\n");
		exit(1);
	}

	strcpy(Cutrfile1, "1");
	
	strcpy(Cutrfile2, "1");
	
	strcpy(Cutrfile3, "20");
	
	printf("  均衡終了年度を［%d］年度に設定しました\n", atoi(Cutrfile3)+2100);
	
	printf("\n予備番号を入力して下さい（３桁）\n");
	scanf("%s%*c", Cutrfile4);
	
	
	strcpy(Sifile, "100");
	
	if(Saimu==0){  
		Saimushu[0] = '\0';
	}else if(Saimu==1){  
		if(Pslsi==2 && Pslsi2==1){
			if (Psly==25 && Kzn==1){
				strcpy(Saimushu, "AK");
			}else {
				printf("現在対応できていない組み合わせです。Saimu=%d, Pslsi=%d, Pslsi2=%d, Kzn=%d\n",
				                                            Saimu, Pslsi, Pslsi2, Kzn);
				exit(1);
			}
		} else {
				printf("現在対応できていない組み合わせです。Saimu=%d, Pslsi=%d, Pslsi2=%d\n",
				                                            Saimu, Pslsi, Pslsi2);
				exit(1);
		}
	}else if(Saimu==2){  
		if(Pslsi==2 && Pslsi2==1){
			if (Psly==25 && Kzn==1){
				strcpy(Saimushu, "AJ");
			} else {
				printf("現在対応できていない組み合わせです。Saimu=%d, Pslsi=%d, Pslsi2=%d, Kzn=%d\n",
				                                            Saimu, Pslsi, Pslsi2, Kzn);
				exit(1);
			}
		} else {
				printf("現在対応できていない組み合わせです。Saimu=%d, Pslsi=%d, Pslsi2=%d\n",
				                                            Saimu, Pslsi, Pslsi2);
				exit(1);
		}
	}
	
	if(strcmp(Saimushu,"10")!=0){
		strcpy(Saimuski, Saimushu);
	}else{
		strcpy(Saimuski, "");
	}
	
	strcpy(Tumafile, "00");
	printf("\n 妻積用ファイル番号を[%s]に設定しています\n", Tumafile);
		
	
	Siencha[0] = '\0';
}



void print_number(void){
	char ctemp[MAX_REC_LEN+1];
	
	sprintf(ctemp,"%s-%s-%s-%s-%s [%s%s%s], Part=%d, Dmakuro=%d, Jimu=%d",
	  Nfile, Nkfile, Wcfile, Ecfile, Cutrfile4, Cutrfile1, Cutrfile2, Cutrfile3,
	  Flg_Part, Flg_Dmakuro, Flg_Jimu);
	
	  printf("\n%s : 妻[%s]\n", ctemp, Tumafile);
}

