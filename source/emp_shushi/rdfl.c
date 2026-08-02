#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "glva.h"

void rdfl_u_sys(void);   
void rdfl_kyos(void);    
void rdfl_sien(void);    
void rdfl_cut(void);     

void rdfl(void){
	
	rdfl_u_sys();
	
	rdfl_kyos();
	
	rdfl_sien();
	
	rdfl_cut();
}


void rdfl_u_sys(void){
	
	FILE *ifp;
	char rec[MAX_REC_LEN+1];
	double dtemp[100], tem_cbmpt;
	int num_dtemp;
	
	int k, s, ii, x, ui, uj;  
	int is, ie;
	double snc[ENDY-STTY+1]={0.};
	
	num_dtemp = sizeof dtemp / sizeof dtemp[0];
	
	is=1;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		ifp = ifp10_usys[ii];
		
		fgets(rec, MAX_REC_LEN, ifp);
		rd_drec(rec, dtemp, num_dtemp);
		if(ii==is){
			Ks = (int) dtemp[0];
			Ke = (int) dtemp[1];
			if(Ks<STTY || ENDY<Ke){
				printf("KsがSTTYより小さい、又は、KeがENDYより大きいです。\n");
				exit(1);
			}
		} else {
			if(Ks!=(int)dtemp[0] || Ke!=(int)dtemp[1]){
				printf("u-sysの出力ファイル間でKs,Keの整合性がありませんKs=%d,%d, Ke=%d,%d\n",
				        Ks, (int)dtemp[0], Ke, (int)dtemp[1]);
				exit(1);
			}
		}
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=1; k<=Ke; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違います(rdfl_u_sys:経済前提), K=%d\n", k);
				exit(1);
			}
			if(k>=Ks && (nround(dtemp[1],12)!=nround(Ri[k-ECSTY],5) ||
			                            nround(dtemp[2],12)!=nround(H[k-ECSTY],5) )  ){
				printf("u-sysファイルと設定したeconファイルの経済前提（賃金、利回り）が一致しません。K=%d \n", k);
				printf("Ri:%.14f ?= %.14f, H:%.14f ?= %.14f\n", dtemp[1], Ri[k-ECSTY], dtemp[2], H[k-ECSTY]);
				exit(1);
			}
		}
		
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=FLKS; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違いますAp, K=%d\n", k);
				exit(1);
			}
			
			for(s=0; s<=3; s++){
				Ap[ii][s][k-STTY] = dtemp[s+1];
			}
			for(s=1; s<=3; s++){	
				Apdum[ii][s][k-STTY] = dtemp[s+4];
			}
		}
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=FLKS; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違いますAp65, K=%d\n", k);
				exit(1);
			}
			
			for(s=0; s<=3; s++){
				Ap65[ii][s][k-STTY] = dtemp[s+1];
				Ap70[ii][s][k-STTY] = dtemp[s+5];
			}
		}
		
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=FLKS; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違いますA60, K=%d\n", k);
				exit(1);
			}
			for(s=0; s<=3; s++){
				A[ii][s][k-STTY] = dtemp[s+1];
			}
			for(s=1; s<=3; s++){	
				Adum[ii][s][k-STTY] = dtemp[s+4];
			}
			for(s=0; s<=3; s++){
				A60[ii][s][k-STTY] = dtemp[s+8];
				A65[ii][s][k-STTY] = dtemp[s+12];
				A70[ii][s][k-STTY] = dtemp[s+16];
			}
		}
		
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=FLKS; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違いますAiku, K=%d\n", k);
				exit(1);
			}
			for(s=0; s<=3; s++){
				Aiku[ii][s][k-STTY] = dtemp[s+1];
			}
			for(s=1; s<=3; s++){
				Aikudum[ii][s][k-STTY] = dtemp[s+4];
			}
		}
		
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=FLKS; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("年度が違いますAal, K=%d\n", k);
				exit(1);
			}
			for(s=0; s<=3; s++){
				Aal[ii][s][k-STTY] = dtemp[s+1];
			}
		}
		
		
		if(ii==1){
			    fgets(rec, MAX_REC_LEN, ifp);
			    fgets(rec, MAX_REC_LEN, ifp);
			    k = Part_Yr2;												
				fgets(rec, MAX_REC_LEN, ifp);
				rd_drec(rec, dtemp, num_dtemp);
				if((int)dtemp[0] != k){
					printf("年度が違いますPart, K=%d <> %d\n", k, (int)dtemp[0]);
					exit(1);
				}
				for(s=0; s<=3; s++){
					Apart[s][k-STTY]    = dtemp[s+ 1] * Cbm_Pt1 / 12.0;
					Aikupart[s][k-STTY] = dtemp[s+ 5] * Cbm_Pt1 / 12.0;
					A60part[s][k-STTY]  = dtemp[s+ 9] * Cbm_Pt1 / 12.0;
					A65part[s][k-STTY]  = dtemp[s+13] * Cbm_Pt1 / 12.0;
					A70part[s][k-STTY]  = dtemp[s+17] * Cbm_Pt1 / 12.0;
				}
				if(Flg_Part>=1){
					k = Part_Yr3;
					fgets(rec, MAX_REC_LEN, ifp);
					rd_drec(rec, dtemp, num_dtemp);
					if((int)dtemp[0] != k){
						printf("年度が違いますPart, K=%d <> %d\n", k, (int)dtemp[0]);
						exit(1);
					}
					for(s=0; s<=3; s++){
						Apart[s][k-STTY]    = dtemp[s+ 1] * Cbm_Pt1 / 12.0;
						Aikupart[s][k-STTY] = dtemp[s+ 5] * Cbm_Pt1 / 12.0;
						A60part[s][k-STTY]  = dtemp[s+ 9] * Cbm_Pt1 / 12.0;
						A65part[s][k-STTY]  = dtemp[s+13] * Cbm_Pt1 / 12.0;
						A70part[s][k-STTY]  = dtemp[s+17] * Cbm_Pt1 / 12.0;
					}
				}
		}
		
		for(s=0; s<=3; s++){
			for(k=Ks; k<=Ke; k++){
				if(ii==1) snc[k-STTY] = Shunor;
				else      snc[k-STTY] = 1.0;
				
				An[ii][s][k-STTY]    = A[ii][s][k-STTY] * snc[k-STTY];
				Aniku[ii][s][k-STTY] = Aiku[ii][s][k-STTY] * snc[k-STTY];
				if(ii==1){
					Anpart[s][k-STTY] = Apart[s][k-STTY] * snc[k-STTY];
					Anikupart[s][k-STTY] = Aikupart[s][k-STTY] * snc[k-STTY];
				}
			}
		}
		
		
				
		for(x=XA-1; x<=XB; x++){
			for(s=1; s<=3; s++){
				fgets(rec, MAX_REC_LEN, ifp);
				fgets(rec, MAX_REC_LEN, ifp);
				for(k=FLKS; k<=FLKE; k++){
					fgets(rec, MAX_REC_LEN, ifp);
					if(k<Ks || k>Ke) continue;
					
					rd_drec(rec, dtemp, num_dtemp);
					if((int)dtemp[0] != k){
						printf("年度が違いますT4X, K=%d\n", k);
						exit(1);
					}
					for(ui=0; ui<=6; ui++){
						T4xtp[ii][s][ui][k-STTY][x]  = dtemp[ui+1];
						T4xtp[ii][0][ui][k-STTY][x] += dtemp[ui+1];
					}
				}
			}
		}
		
		for(x=XA-1; x<=XB; x++){
			for(s=0; s<=3; s++){
				for(ui=0; ui<=13; ui++){
					fgets(rec, MAX_REC_LEN, ifp);
					fgets(rec, MAX_REC_LEN, ifp);
					for(k=FLKS; k<=FLKE; k++){
						fgets(rec, MAX_REC_LEN, ifp);
						if(k<Ks || k>Ke) continue;
						
						rd_drec(rec, dtemp, num_dtemp);
						if((int)dtemp[0] != k){
							printf("年度が違いますD3BX, K=%d\n", k);
							exit(1);
						}
						Kfpbxtp[ii][s][ui][7][k-STTY][x] = dtemp[1];
						D3bxtp[ii][s][ui][1][k-STTY][x]  = dtemp[2];
						for(uj=3; uj<=7; uj++){
							D3bxtp[ii][s][ui][uj][k-STTY][x] = dtemp[uj];
						}
						Kofbxtp[ii][s][ui][k-STTY][x] = dtemp[8];
						Kofte[ii][s][ui][k-STTY][x]   = dtemp[9];
						Kofkk[ii][s][ui][k-STTY][x]   = dtemp[10];
						
						if(ii==1){
							Kfpbxtp[0][s][ui][7][k-STTY][x] += dtemp[1];
							D3bxtp[0][s][ui][1][k-STTY][x]  += dtemp[2];
							for(uj=3; uj<=7; uj++){
								D3bxtp[0][s][ui][uj][k-STTY][x] += dtemp[uj];
							}
							Kofbxtp[0][s][ui][k-STTY][x] += dtemp[8];
							Kofte[0][s][ui][k-STTY][x]   += dtemp[9];
							Kofkk[0][s][ui][k-STTY][x]   += dtemp[10];
						}
					}
				}
			}
		}
		
		for(x=XA-1; x<=XB; x++){
			for(ui=0; ui<=13; ui++){
				fgets(rec, MAX_REC_LEN, ifp);
				fgets(rec, MAX_REC_LEN, ifp);
				for(k=FLKS; k<=FLKE; k++){
					fgets(rec, MAX_REC_LEN, ifp);
					if(k<Ks || k>Ke) continue;
					
					rd_drec(rec, dtemp, num_dtemp);
					if((int)dtemp[0] != k){
						printf("年度が違いますKFPBX, K=%d <> %d\n", k, (int)dtemp[0]);
						exit(1);
					}
					for(s=0; s<=3; s++){
						for(uj=1; uj<=2; uj++){
							Kfpbxtp[ii][s][ui][uj][k-STTY][x] = dtemp[s*2+uj];
							if(ii==1)
							  Kfpbxtp[0][s][ui][uj][k-STTY][x] += dtemp[s*2+uj];
						}
					}
				}
			}
		}
		for(s=0; s<=3; s++){
			if(s==3 && ii>1) break;
				for(k=Ks; k<=Ke; k++){
					Ap[ii][s][k-STTY] -= Ap70[ii][s][k-STTY];
					Ap70[ii][s][k-STTY]=0.;
				}
			}
	}  
}



void rdfl_kyos(void){  
	FILE *ifp;
	char rec[MAX_REC_LEN+1];
	double dtemp[100];
	int num_dtemp;
	
	int sh;
	int ss, ii, x , k;
	
	num_dtemp = sizeof dtemp / sizeof dtemp[0];
	
	ifp = ifp_kyos;
	
	if(Touitu==0){
		for(sh=0; sh<2; sh++){
			fgets(rec, MAX_REC_LEN, ifp);
			for(ss=0; ss<=6; ss++){
				for(ii=1; ii<=4; ii++){
					for(k=FLKS-5; k<=FLKE; k++){
						fgets(rec, MAX_REC_LEN, ifp);
						if(k<Ks || k>Ke) continue;
					
						rd_drec(rec, dtemp, num_dtemp);
						if((int)dtemp[0] != k || (int)dtemp[1] != ss || (int)dtemp[2] != ii){
							printf("基礎年金拠出金の読ませ方が違います。, K=%d\n", k);
							printf("%s", rec);
							exit(1);
						}
						for(x=XA-1; x<=XB; x++){
							if(ii<=2){
								Kyosdx[sh][ss][ii-1][k-STTY][x] = dtemp[4+x-(XA-1)];
							}else{
								Kfkyosdx[sh][ss][ii-3][k-STTY][x] = dtemp[4+x-(XA-1)];
							}
						}
					}
				}
			}
		}
	}
	else if(Touitu>=1){
		for(sh=0; sh<2; sh++){
			fgets(rec, MAX_REC_LEN, ifp);
			for(ss=0; ss<=8; ss++){
				for(ii=1; ii<=4; ii++){
					for(k=FLKS-5; k<=FLKE; k++){
						fgets(rec, MAX_REC_LEN, ifp);
						if(k<Ks || k>Ke) continue;
					
						rd_drec(rec, dtemp, num_dtemp);
						if((int)dtemp[0] != k || (int)dtemp[1] != ss || (int)dtemp[2] != ii){
							printf("基礎年金拠出金の読ませ方が違います。, K=%d\n", k);
							printf("%s", rec);
							exit(1);
						}
						for(x=XA-1; x<=XB; x++){
							if(ii<=2){
								Kyosdx[sh][ss][ii-1][k-STTY][x] = dtemp[4+x-(XA-1)];
							}else{
								Kfkyosdx[sh][ss][ii-3][k-STTY][x] = dtemp[4+x-(XA-1)];
							}
						}
					}
				}
			}
		}
	}
	
		ifp = ifp27_tuma;
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=15; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("妻積ファイルの読ませ方が違います k=%d, %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			
			for(ii=1; ii<=4; ii++){
				Tumazumi[ii][k-STTY]  = dtemp[ii+1];
			}
		}
	
	if(Touitu>=1){
		ifp = ifp_Touitu;
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=20; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("provideファイルの読ませ方が違います k=%d, %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			
			for(ii=0; ii<=4; ii++){
			  Kokusyushi[ii][k-STTY]  = dtemp[ii+1];
			}
		}
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=20; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("provideファイルの読ませ方が違います k=%d, %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			
			for(ii=0; ii<=3; ii++){
			  Kokusyushi[ii+5][k-STTY]  = dtemp[ii+1];
			}
		}
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		for(k=20; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<Ks || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("provideファイルの読ませ方が違います k=%d, %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			Kokusyushi[9][k-STTY]  = dtemp[1];
			
		}
	}
}


void rdfl_sien(void){
	FILE *ifp;
	char rec[MAX_REC_LEN+1];
	double dtemp[100];
	int num_dtemp;
	
	int k;
	
	num_dtemp = sizeof dtemp / sizeof dtemp[0];
	
		ifp = ifp_nofu;
		
		fgets(rec, MAX_REC_LEN, ifp);
		fgets(rec, MAX_REC_LEN, ifp);
		
		for(k=22; k<=55; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<STTY || k>ENDY) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("納付金の読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			
			Nofu[1][k-STTY] = dtemp[1];
			Jyutaku[k-STTY] = dtemp[2];
			Nofu[0][k-STTY] = dtemp[1];
		}
}

void rdfl_cut(void){  
	FILE *ifp;
	char rec[MAX_REC_LEN+1];
	double dtemp[100];
	int num_dtemp;
	
	int k, x;
	
	num_dtemp = sizeof dtemp / sizeof dtemp[0];
	
	
	
	ifp = ifp_kaiteb;
	for(k=5; k<=FLKE; k++){
		fgets(rec, MAX_REC_LEN, ifp);
		if(k<ECSTY || k>Ke) continue;
		
		rd_drec(rec, dtemp, num_dtemp);
		if((int)dtemp[0] != k){
			printf("厚年比例改定率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
			exit(1);
		}
		for(x=67; x<=XB; x++) Krb[k-ECSTY][x-ECXA] = dtemp[1+(x-67)];
		
	}
	
	
	if(Cutrfile1[0]=='0'){  
		ifp = ifp_kaitea;
		
		for(k=5; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("厚年定額改定率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			for(x=67; x<=XB; x++) Kra[k-ECSTY][x-ECXA] = dtemp[1+(x-67)];
		}
	}else if(Cutrfile1[0]=='1'){  
		ifp = ifp_kokukaite;
		
		for(k=5; k<=FLKE; k++){  
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>Ke) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("国年改定率ファイルの読ませ方が違います。, K=%d\n", k);
				exit(1);
			}
			for(x=67; x<=XB; x++) Kra[k-ECSTY][x-ECXA] = dtemp[1+(x-67)];
			
		}
	}else{
		printf("Cutrfile1(厚年先決めor国年先決め)がうまく設定されていません。\n");
		exit(1);
	}
	
	for(k=MAX(5,ECSTY); k<=Ke; k++){
		for(x=ECXA; x<67; x++){
			Kra[k-ECSTY][x-ECXA] = Kra[k-ECSTY][67-ECXA];
			Krb[k-ECSTY][x-ECXA] = Krb[k-ECSTY][67-ECXA];
		}
	}
	
	
	
	if(Fpset!=9){
		ifp = ifp_wakum;
		
		for(k=5; k<=FLKE; k++){  
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>ECEDY) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k+2000){
				printf("調整率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]-2000);
				exit(1);
			}
			Scutrk1[k-ECSTY] = dtemp[1];  
		}
	}
	
	
	if(Fpset==8 && Cutrfile1[0]=='1'){ 
		ifp = ifp_bas_cuta;
		
		for(k=5; k<=FLKE; k++){	
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>ECEDY) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("国年カット率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			for(x=XA-1; x<=115; x++) Scutrrki[k-ECSTY][x-ECXA] = dtemp[1+(x-(XA-1))];
			
		}
	}
	
	if(Fpset == 9){ 
		ifp = ifp_asys_cutb;
		
		for(k=5; k<=FLKE; k++){
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>ECEDY) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("厚年比例カット率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			for(x=XA-1; x<=115; x++) Scutrrh[k-ECSTY][x-ECXA] = dtemp[1+(x-(XA-1))];
			
		}
		
		ifp = ifp_asys_cuta;
		
		for(k=5; k<=FLKE; k++){	
			fgets(rec, MAX_REC_LEN, ifp);
			if(k<ECSTY || k>ECEDY) continue;
			
			rd_drec(rec, dtemp, num_dtemp);
			if((int)dtemp[0] != k){
				printf("厚年定額カット率ファイルの読ませ方が違います。, K=%d <> %d\n", k, (int)dtemp[0]);
				exit(1);
			}
			for(x=XA-1; x<=115; x++){
				Scutrrt[k-ECSTY][x-ECXA] = dtemp[1+(x-(XA-1))];
			}
		}
	}
}

