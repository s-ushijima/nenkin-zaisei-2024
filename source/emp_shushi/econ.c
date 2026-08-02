#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"

#define KAKAKU 24 

double jh_kaite(int);  

void econ(void){
	FILE *ifp;
	double dtemp[7], Ridum, Cidum, Hdum;
	int num_dtemp;
	char rec[MAX_REC_LEN+1];
	int k;
	
	double kaite_hp;  
	double kaite_ci;  
	
	num_dtemp = sizeof dtemp / sizeof dtemp[0];
	for(k=0; k<ECEDY-ECSTY+1; k++){
		Id_Hhd[k] = 1.;
		Id_Cid[k] = 1.;
		Id_Cid_2[k] = 1.;
	}
	
	
	ifp = ifp_econ;
	k = 1;  
	while(fgets(rec, MAX_REC_LEN, ifp)!=NULL){
		rd_drec(rec, dtemp, num_dtemp);
		if( k!=(int)dtemp[0]){
			printf("Econの年度が違います。(%d<>%d)\n", k, (int)dtemp[0]);
			exit(1);
		}else{
			Ridum = 0.;
			Hdum  = 0.;
			Cidum = 0.;
			Ridum = dtemp[1]/100.;
			Hdum  = dtemp[5]/100.;
			Cidum = dtemp[6]/100.;
			Ri[k-ECSTY] = (1.+Ridum) * (1.+Cidum) -1.;
			H[k-ECSTY]  = (1.+Hdum)  * (1.+Cidum) -1.;
			Ci[k-ECSTY] = Cidum;
		}
		k++;
	}
	while(k<=ECEDY){
		Ri[k-ECSTY] = Ri[k-1-ECSTY];
		H[k-ECSTY]  = H[k-1-ECSTY];
		Ci[k-ECSTY] = Ci[k-1-ECSTY];
		k++;
	}
   
	for(k=1; k<=ECEDY; k++){
	    HCdum[k-ECSTY] = (1.+H[k-ECSTY]) / (1.+Ci[k-ECSTY]) ;
		if(k == 1)   Ri[k-ECSTY] =  1.99/100.,   H[k-ECSTY] =  0.38/100.;
	    if(k == 2)   Ri[k-ECSTY] =  0.21/100.,   H[k-ECSTY] = -0.66/100.;
	    if(k == 3)   Ri[k-ECSTY] =  4.91/100.,   H[k-ECSTY] = -0.61/100.;
	    if(k == 4)   Ri[k-ECSTY] =  2.73/100.,   H[k-ECSTY] = -0.18/100.;
	    if(k == 5)   Ri[k-ECSTY] =  6.82/100.,   H[k-ECSTY] = -0.24/100.;
	    if(k == 6)   Ri[k-ECSTY] =  3.10/100.,   H[k-ECSTY] = -0.25/100.;
	    if(k == 7)   Ri[k-ECSTY] = -3.54/100.,   H[k-ECSTY] = -0.46/100.;
	    if(k == 8)   Ri[k-ECSTY] = -6.83/100.,   H[k-ECSTY] = -0.49/100.;
	    if(k == 9)   Ri[k-ECSTY] =  7.54/100.,   H[k-ECSTY] = -3.03/100.;
	    if(k == 10)  Ri[k-ECSTY] = -0.26/100.,   H[k-ECSTY] = -0.44/100.;
	    if(k == 11)  Ri[k-ECSTY] =  2.17/100.,   H[k-ECSTY] = -0.08/100.;
	    if(k == 12)  Ri[k-ECSTY] =  9.57/100.,   H[k-ECSTY] = -0.32/100.;
	    if(k == 13)  Ri[k-ECSTY] =  8.22/100.,   H[k-ECSTY] = -0.14/100.;
	    if(k == 14)  Ri[k-ECSTY] = 11.61/100.,   H[k-ECSTY] =  1.06/100.;
	    if(k == 15)  Ri[k-ECSTY] = -3.14/100.,   H[k-ECSTY] =  0.33/100.;
	    if(k == 16)  Ri[k-ECSTY] =  5.30/100.,   H[k-ECSTY] = -0.05/100.;
	    if(k == 17)  Ri[k-ECSTY] =  6.50/100.,   H[k-ECSTY] =  0.26/100.;
	    if(k == 18)  Ri[k-ECSTY] =  1.42/100.,   H[k-ECSTY] =  0.79/100.;
	    if(k == 19)  Ri[k-ECSTY] = -4.96/100.,   H[k-ECSTY] =  0.60/100.;
	    if(k == 20)  Ri[k-ECSTY] = 23.90/100.,   H[k-ECSTY] = -0.52/100.;
	    if(k == 21)  Ri[k-ECSTY] =  5.19/100.,   H[k-ECSTY] =  1.04/100.;
	    if(k == 22)  Ri[k-ECSTY] =  1.44/100.,   H[k-ECSTY] =  1.39/100.;
		Ri2[k-ECSTY] = pow(1.+Ri[k-ECSTY], 0.5) - 1.;
	}
	
	Id_Hhd[5-ECSTY] = 1.;
	
	for(k=6; k<=ECEDY; k++){
		if(k<=KAKAKU+1){
			kaite_ci = nround(Ci[k-2-ECSTY], 3);
			kaite_hp = nround((1.0+kaite_ci) * nround(1.0+jh_kaite(k-1),3), 3) - 1.;
			if(k<=7) kaite_hp = kaite_ci;
			if(k==18) kaite_hp = -0.009;
			
			Id_Hhd[k-ECSTY] = nround(Id_Hhd[k-1-ECSTY] * (1.0 + kaite_hp), 3);
		} else {
			kaite_ci = Ci[k-2-ECSTY];
			kaite_hp = (1.0+kaite_ci) * (1.0+jh_kaite(k-1)) - 1.;  
			
			Id_Hhd[k-ECSTY] = Id_Hhd[k-1-ECSTY] * (1.0 + kaite_hp);
		}
		
		if(k>KAKAKU){
			Id_Cid[k-ECSTY] = Id_Cid[k-1-ECSTY] * (1. + Ci[k-1-ECSTY]);
		}
		
		if(zan_jimu == 0){
			if(k>24){
				Id_Cid_2[k-ECSTY] = Id_Cid_2[k-1-ECSTY] * (1. + Ci[k-ECSTY]);
			}
		}
	}
	
	
	dtemp[0] = Id_Hhd[KAKAKU-ECSTY];  
	if(dtemp[0] > 0.){
		for(k=ECSTY; k<=ECEDY; k++) Id_Hhd[k-ECSTY] /= dtemp[0];
	} else {
		printf("保険料改定率(%f)、価格基準年度(%d)の設定がおかしいです\n", dtemp[0], KAKAKU);
		exit(1);
	}
	
}


double jh_kaite(int k){
	double djh;
	int n;
	
	if(k<=4 || ECEDY<k){
		printf("econ.c中のjh_kaite()の引数年度が想定範囲外です。\n");
		exit(1);
	}else{
		djh = 1.;
		for(n=2; n<=4; n++){
	 		djh *= HCdum[k-n-ECSTY];
	 	}
	 	djh = pow(djh, 1. / 3.) - 1.;
	}
	return(djh);
}

