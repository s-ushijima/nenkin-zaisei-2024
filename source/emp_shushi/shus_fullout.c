#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"

void shus_fullout(int);
void shus_nenbeout(int);
static double d4x[5][4][14][8][ENDY-STTY+1][116];
static double d4a[5][4][14][8][ENDY-STTY+1];
static double d65[5][4][14][8][ENDY-STTY+1];
static double dkof[5][3][ENDY-STTY+1];
static double ddaik[5][ENDY-STTY+1];


void shus_fullout(int mode){
	FILE *ofp;
	int s, i, j, k, x;
	int dx;
	double riv, bpre, bend, dtemp, dtemp2;
	int is, ie, ii, se;
	
	is=0;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		
		for(s=0; s<4; s++){
			for(i=0; i<14; i++){
				for(j=0; j<8; j++){
					for(k=0; k<ENDY-STTY+1; k++){
						for(x=0; x<116; x++){
							d4x[ii][s][i][j][k][x] = 0.;
						}
						d4a[ii][s][i][j][k] = 0.;
						d65[ii][s][i][j][k] = 0.;
					}
				}
			}
		}
		for(i=0; i<3; i++){
			for(k=0; k<ENDY-STTY+1; k++){
				dkof[ii][i][k] = 0.;
			}
		}
		
		if(ii==0) continue;
		
		if(ii==1) se=3;
		else      se=2;
		
		for(s=0; s<=se; s++){
			for(i=0; i<=13; i++){
				for(j=1; j<=7; j++){
					if(j==2) continue;
					for(k=Ks+1; k<=Ke; k++){
					for(x=XA-1; x<=XB; x++){
						dx = MAX(x, 67);
						if(j==1){
							riv = Krb[k-ECSTY][dx-ECXA] * (Escutrrh[k-ECSTY][dx-ECXA]/Escutrrh[k-1-ECSTY][dx-1-ECXA]);
							bpre = D3bxtp[ii][s][i][j][k-1-STTY][x-1] * Escutrrh[k-1-ECSTY][dx-1-ECXA];
							bend = D3bxtp[ii][s][i][j][k-STTY][x] * Escutrrh[k-ECSTY][dx-ECXA];
						} else if (j!=5){
							riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrt[k-ECSTY][dx-ECXA]/Escutrrt[k-1-ECSTY][dx-1-ECXA]);
							bpre = D3bxtp[ii][s][i][j][k-1-STTY][x-1] * Escutrrt[k-1-ECSTY][dx-1-ECXA];
							bend = D3bxtp[ii][s][i][j][k-STTY][x] * Escutrrt[k-ECSTY][dx-ECXA];
						} else {
							riv = Kra[k-ECSTY][67-ECXA] * (Escutrrt[k-ECSTY][67-ECXA]/Escutrrt[k-1-ECSTY][67-ECXA]);
							bpre = D3bxtp[ii][s][i][j][k-1-STTY][x-1] * Escutrrt[k-1-ECSTY][67-ECXA];
							bend = D3bxtp[ii][s][i][j][k-STTY][x] * Escutrrt[k-ECSTY][67-ECXA];
						}
						if(Flg_matsu == 0){
							dtemp = (bpre * 2.0 + bpre * riv * 6.0 + bend * 4.0) / 12.0 * nendohosei / 1.0E+8;
						}else if(Flg_matsu == 1){
							dtemp = bend * nendohosei / 1.0E+8;
						}
						
						d4x[ii][s][i][j][k-STTY][x]          = dtemp;
						d4x[ii][s][i][0][k-STTY][x]         += dtemp;
						if(j>2) d4x[ii][s][i][2][k-STTY][x] += dtemp;
						
						d4a[ii][s][i][j][k-STTY]            += dtemp;
						d4a[ii][s][i][0][k-STTY]            += dtemp;
						if(j>2) d4a[ii][s][i][2][k-STTY]    += dtemp;
						
						if(x>=65){
							d65[ii][s][i][j][k-STTY]          += dtemp;
							d65[ii][s][i][0][k-STTY]          += dtemp;
							if(j>2) d65[ii][s][i][2][k-STTY]  += dtemp;
						}
						
							d4x[0][s][i][j][k-STTY][x]         += dtemp;
							d4x[0][s][i][0][k-STTY][x]         += dtemp;
							if(j>2) d4x[0][s][i][2][k-STTY][x] += dtemp;
							
							d4a[0][s][i][j][k-STTY]            += dtemp;
							d4a[0][s][i][0][k-STTY]            += dtemp;
							if(j>2) d4a[0][s][i][2][k-STTY]    += dtemp;
							
							if(x>=65){
								d65[0][s][i][j][k-STTY]          += dtemp;
								d65[0][s][i][0][k-STTY]          += dtemp;
								if(j>2) d65[0][s][i][2][k-STTY]  += dtemp;
							}
					}
					}
				}
			}
		}
		
		
		for(i=1; i<=2; i++){
			for(k=Ks+1; k<=Ke; k++){
				for(x=XA-1; x<=XB; x++){
					dx = MAX(x, 67);
					if(i==1){
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrt[k-ECSTY][dx-ECXA]/Escutrrt[k-1-ECSTY][dx-1-ECXA]);
						bpre = Kofte[ii][0][0][k-1-STTY][x-1] * Escutrrt[k-1-ECSTY][dx-1-ECXA];
						bend = Kofte[ii][0][0][k-STTY][x] * Escutrrt[k-ECSTY][dx-ECXA];
					} else {
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrt[k-ECSTY][dx-ECXA]/Escutrrt[k-1-ECSTY][dx-1-ECXA]);
						bpre = Kofkk[ii][0][0][k-1-STTY][x-1] * Escutrrt[k-1-ECSTY][dx-1-ECXA];
						bend = Kofkk[ii][0][0][k-STTY][x] * Escutrrt[k-ECSTY][dx-ECXA];
					}
					if(Flg_matsu == 0){
						dtemp = (bpre * 2.0 + bpre * riv * 6.0 + bend * 4.0) / 12.0 / 1.0E+8;
					}
					
					dkof[ii][i][k-STTY] += dtemp;
					dkof[ii][0][k-STTY] += dtemp;
					
					dkof[0][i][k-STTY] += dtemp;
					dkof[0][0][k-STTY] += dtemp;
				}
			}
		}
	}
	
	for(ii=is; ii<=ie; ii++){
		ofp = ofp01_shushi[ii];
		
		fprintf(ofp, "\n¾ÜºÙ¼ý»Ù");
		if(mode==0) fprintf(ofp, "¡Ú¥¹¥é¥¤¥ÉÄ´À°Á°¡Û\n");
		else        fprintf(ofp, "¡Ú¥¹¥é¥¤¥ÉÄ´À°¸å¡Û\n");
		fprintf(ofp, "Ç¯ÅÙ,");
		fprintf(ofp, "´ðÁÃÇ¯¶â¸òÉÕ¶â,Âå¹ÔÁêÅöµëÉÕ,ÆÈ¼«¹ç·×,µìË¡Ï·Îð,µìË¡¾ã³²,µìË¡°äÂ²,,");
		
		fprintf(ofp, "Ï·Âà,Ï·ºß,ÄÌÂà,ÄÌºß,¾ã³²,°äÂ²,");
		fprintf(ofp, "Ï·Âà­¡,Ï·ºß­¡,ÄÌÂà­¡,ÄÌºß­¡,¾ã³²­¡,°äÂ²­¡,");
		fprintf(ofp, "Ï·Âà­¢,Ï·ºß­¢,ÄÌÂà­¢,ÄÌºß­¢,¾ã³²­¢,°äÂ²­¢,");
		fprintf(ofp, "Ï·Âà­£,Ï·ºß­£,ÄÌÂà­£,ÄÌºß­£,¾ã³²­£,°äÂ²­£,");
		fprintf(ofp, "65-Ï·Âà,65-Ï·ºß,65-ÄÌÂà,65-ÄÌºß,65-¾ã³²,65-°äÂ²,,");
		
		fprintf(ofp, "ÈæÏ·Âà,ÈæÏ·ºß,ÈæÄÌÂà,ÈæÄÌºß,Èæ¾ã³²,Èæ°äÂ²,");
		fprintf(ofp, "65-ÈæÏ·Âà,65-ÈæÏ·ºß,65-ÈæÄÌÂà,65-ÈæÄÌºß,65-Èæ¾ã³²,65-Èæ°äÂ²,,");
		
		fprintf(ofp, "¤½¤ÎÂ¾·×,Äê³Û,·Ð²áÅª²Ã»»,²Ãµë,°äÂ²²Ã»»,ºÇÄãÊÝ¾ã,");
		fprintf(ofp, "65-¤½¤ÎÂ¾·×,65-Äê³Û,65-·Ð²áÅª²Ã»»,65-²Ãµë,65-°äÂ²²Ã»»,65-ºÇÄãÊÝ¾ã,,");
		
		fprintf(ofp, "¿·Ï·Âà·×,¿·Ï·ºß·×,¿·ÄÌÂà·×,¿·ÄÌºß·×,");
		fprintf(ofp, "µìÏ·Âà·×,µìÏ·ºß·×,µìÄÌÂà·×,µìÄÌºß·×,");
		fprintf(ofp, "¿·¾ã³²·×,µì¾ã³²·×,¿·°äÂ²·×,µì°äÂ²·×,µìÄÌ°ä·×,");
		fprintf(ofp, "¿·Ï·ÂàÈæ,¿·Ï·ºßÈæ,¿·ÄÌÂàÈæ,¿·ÄÌºßÈæ,");
		fprintf(ofp, "µìÏ·ÂàÈæ,µìÏ·ºßÈæ,µìÄÌÂàÈæ,µìÄÌºßÈæ,");
		fprintf(ofp, "¿·¾ã³²Èæ,µì¾ã³²Èæ,¿·°äÂ²Èæ,µì°äÂ²Èæ,µìÄÌ°äÈæ,");
		fprintf(ofp, "¿·Ï·ÂàÂ¾,¿·Ï·ºßÂ¾,¿·ÄÌÂàÂ¾,¿·ÄÌºßÂ¾,");
		fprintf(ofp, "µìÏ·ÂàÂ¾,µìÏ·ºßÂ¾,µìÄÌÂàÂ¾,µìÄÌºßÂ¾,");
		fprintf(ofp, "¿·¾ã³²Â¾,µì¾ã³²Â¾,¿·°äÂ²Â¾,µì°äÂ²Â¾,µìÄÌ°äÂ¾,");
		fprintf(ofp, "¿·Ï·ÂàÄê,¿·Ï·ºßÄê,¿·ÄÌÂàÄê,¿·ÄÌºßÄê,");
		fprintf(ofp, "µìÏ·ÂàÄê,µìÏ·ºßÄê,µìÄÌÂàÄê,µìÄÌºßÄê,");
		fprintf(ofp, "¿·¾ã³²Äê,µì¾ã³²Äê,¿·°äÂ²Äê,µì°äÂ²Äê,µìÄÌ°äÄê,");
		fprintf(ofp, "¿·Ï·Âà·Ð,¿·Ï·ºß·Ð,¿·ÄÌÂà·Ð,¿·ÄÌºß·Ð,");
		fprintf(ofp, "µìÏ·Âà·Ð,µìÏ·ºß·Ð,µìÄÌÂà·Ð,µìÄÌºß·Ð,");
		fprintf(ofp, "¿·¾ã³²·Ð,µì¾ã³²·Ð,¿·°äÂ²·Ð,µì°äÂ²·Ð,µìÄÌ°ä·Ð,");
		fprintf(ofp, "¿·Ï·Âà²Ã,¿·Ï·ºß²Ã,¿·ÄÌÂà²Ã,¿·ÄÌºß²Ã,");
		fprintf(ofp, "µìÏ·Âà²Ã,µìÏ·ºß²Ã,µìÄÌÂà²Ã,µìÄÌºß²Ã,");
		fprintf(ofp, "¿·¾ã³²²Ã,µì¾ã³²²Ã,¿·°äÂ²²Ã,µì°äÂ²²Ã,µìÄÌ°ä²Ã,");
		fprintf(ofp, "¿·Ï·Âà°ä²Ã,¿·Ï·ºß°ä²Ã,¿·ÄÌÂà°ä²Ã,¿·ÄÌºß°ä²Ã,");
		fprintf(ofp, "µìÏ·Âà°ä²Ã,µìÏ·ºß°ä²Ã,µìÄÌÂà°ä²Ã,µìÄÌºß°ä²Ã,");
		fprintf(ofp, "¿·¾ã³²°ä²Ã,µì¾ã³²°ä²Ã,¿·°äÂ²°ä²Ã,µì°äÂ²°ä²Ã,µìÄÌ°ä°ä²Ã,");
		fprintf(ofp, "¿·Ï·ÂàºÇ,¿·Ï·ºßºÇ,¿·ÄÌÂàºÇ,¿·ÄÌºßºÇ,");
		fprintf(ofp, "µìÏ·ÂàºÇ,µìÏ·ºßºÇ,µìÄÌÂàºÇ,µìÄÌºßºÇ,");
		fprintf(ofp, "¿·¾ã³²ºÇ,µì¾ã³²ºÇ,¿·°äÂ²ºÇ,µì°äÂ²ºÇ,µìÄÌ°äºÇ,");
		fprintf(ofp, "\n");
		
		for(k=FLKS; k<=FLKE; k++){
			fprintf(ofp, "%3d,", k);
			fprintf(ofp, "%20.13e,%20.13e,", dkof[ii][0][k-STTY], ddaik[ii][k-STTY]);
			fprintf(ofp, "%20.13e,", d4a[ii][0][0][0][k-STTY]);		
			dtemp = 0.;
			for(i=5; i<=8; i++) dtemp += d4a[ii][0][i][0][k-STTY];
			fprintf(ofp, "%20.13e,",dtemp);
			fprintf(ofp, "%20.13e,",d4a[ii][0][10][0][k-STTY]);
			fprintf(ofp, "%20.13e,",d4a[ii][0][12][0][k-STTY]+d4a[ii][0][13][0][k-STTY]);
			fprintf(ofp,  ",");
			
			for(s=0; s<=3; s++){
				for(i=1; i<=4; i++){
					fprintf(ofp,"%20.13e,",d4a[ii][s][i][0][k-STTY]+d4a[ii][s][i+4][0][k-STTY]);
				}
				fprintf(ofp,"%20.13e,",d4a[ii][s][ 9][0][k-STTY]+d4a[ii][s][10][0][k-STTY]);
				dtemp = 0.;
				for(i=11; i<=13; i++) dtemp += d4a[ii][s][i][0][k-STTY];
				fprintf(ofp,"%20.13e,",dtemp);
			}
			for(i=1; i<=4; i++){
				fprintf(ofp,"%20.13e,",d65[ii][0][i][0][k-STTY]+d65[ii][0][i+4][0][k-STTY]);
			}
			fprintf(ofp,"%20.13e,",d65[ii][0][ 9][0][k-STTY]+d65[ii][0][10][0][k-STTY]);
			dtemp = 0.;
			for(i=11; i<=13; i++) dtemp += d65[ii][0][i][0][k-STTY];
			fprintf(ofp,"%20.13e,",dtemp);
			fprintf(ofp, ",");
			
			for(i=1; i<=4; i++){
				fprintf(ofp,"%20.13e,",d4a[ii][0][i][1][k-STTY]+d4a[ii][0][i+4][1][k-STTY]);
			}
			fprintf(ofp,"%20.13e,",d4a[ii][0][ 9][1][k-STTY]+d4a[ii][0][10][1][k-STTY]);
			dtemp = 0.;
			for(i=11; i<=13; i++) dtemp += d4a[ii][0][i][1][k-STTY];
			fprintf(ofp,"%20.13e,",dtemp);
			for(i=1; i<=4; i++){
				fprintf(ofp,"%20.13e,",d65[ii][0][i][1][k-STTY]+d65[ii][0][i+4][1][k-STTY]);
			}
			fprintf(ofp,"%20.13e,",d65[ii][0][ 9][1][k-STTY]+d65[ii][0][10][1][k-STTY]);
			dtemp = 0.;
			for(i=11; i<=13; i++) dtemp += d65[ii][0][i][1][k-STTY];
			fprintf(ofp,"%20.13e,",dtemp);
			fprintf(ofp, ",");
			
			for(j=2; j<=7; j++) fprintf(ofp, "%20.13e,", d4a[ii][0][0][j][k-STTY]);
			for(j=2; j<=7; j++) fprintf(ofp, "%20.13e,", d65[ii][0][0][j][k-STTY]);
			fprintf(ofp, ",");
			
			for(j=0; j<=7; j++){
				for(i=1; i<=13; i++){
					fprintf(ofp, "%20.13e,", d4a[ii][0][i][j][k-STTY]);
				}
			}
			
			fprintf(ofp, "\n");
		}
		fprintf(ofp, "\n");
		
	}
	
	if(Nenbeex2==1){
		if(Flg_matsu==0){
			shus_nenbeout(mode);
		}
	}
	
	if((Saimu==0 || Saimu==1 || Saimu==2) && mode==1){
		for(ii=1; ii<=4; ii++){
			for(i=1; i<=13; i++){
				if(i==1 || i==2 || i==5 || i==6){
					j=0;
				} else if(i==3 || i==4 || i==7 || i==8){
					j=1;
				} else if(i<=10){
					j=2;
				} else {
					j=3;
				}
				for(k=Ks; k<=Ke; k++){
					Ukyu[1][ii][j][k-STTY] += d4a[ii][0][i][0][k-STTY];
					Ukyu[1][0][j][k-STTY]  += d4a[ii][0][i][0][k-STTY];
				}
			}
		}
	}
}



void shus_nenbeout(int mode){
	FILE *ofp;
	double dtemp;
	int s, i, j, k, x;
	int is, ie, ii;
	char sei[3][10]    = {"0¹ç·×", "1ÃËÀ­", "2½÷À­"};
	char kyufus[4][10] = {"0¹ç·×", "1Ï·Îð", "2¾ã³²", "3°äÂ²"};
	char newold[3][10] = {"0¹ç·×", "1¿·Ë¡", "2µìË¡"};
	char zaitai[4][10] = {"0¹ç·×", "1Âà¿¦", "2ºß¿¦", "3¾ã°ä"};
	char shurui[8][10] = {"0¹ç·×", "1ÈæÎã", "2Â¾·×", "3Äê³Û", "4·Ð²Ã", "5²Ãµë", "6°ä²Ã", "7ºÇÊÝ"};
	int i2k[14] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3};
	int i2n[14] = { 0, 1, 1, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2, 2};
	int i2z[14] = { 0, 1, 2, 1, 2, 1, 2, 1, 2, 3, 3, 3, 3, 3};
	
	
	is=0;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		ofp = ofp90_nenbe[ii];
		
		if(Flg_matsu == 0){
			if(mode==0) fprintf(ofp, "¡Ú¥¹¥é¥¤¥ÉÄ´À°Á°¡Û\n");
			else        fprintf(ofp, "¡Ú¥¹¥é¥¤¥ÉÄ´À°¸å¡Û\n");
		}
		
		
		fprintf(ofp, "Ç¯ÅÙ,À­ÊÌ,µëÉÕ¼ïÊÌ,¿·µìÊÌ,ºßÂàÊÌ,¼ïÎà,Ç¯Îð,µëÉÕÈñ\n");
		for(s=1; s<=2; s++){
			for(i=1; i<=13; i++){
				for(j=1; j<=7; j++){
					for(k=Ks+1; k<=Ke; k++){
						for(x=XA-1; x<=XB; x++){
							fprintf(ofp, "%d,%s,%s,%s,%s,%s,",
							        k, sei[s], kyufus[i2k[i]], newold[i2n[i]], zaitai[i2z[i]], shurui[j]);
							
							if(s==1 && (ii==0 || ii==1)){
								dtemp = d4x[ii][1][i][j][k-STTY][x] + d4x[ii][3][i][j][k-STTY][x];
							}else{
								dtemp = d4x[ii][s][i][j][k-STTY][x];
							}
							fprintf(ofp, "%d,%20.13e\n", x, dtemp);
						}
					}
				}
			}
		}
	}
}

