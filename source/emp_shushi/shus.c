#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"

void shus_init(void);    
void init_premium(void); 
void shus_premium(void); 
void shus_fukkjn(void);  
 
void shus_econ_out(void); 
void shus_nin_out(void);  
void shus_shushiout(int); 
void shus_cutout(void);   

void shus_summary(void);  
void shus_Tokutyoout(void);

void shus_fullout(int);  

void shus_calc0(void);	
int  shus_calc8(void);	
void shus_calc9(void);	

void shus_smodel(void);  

void shus(void){
	shus_init();
	init_premium();
	shus_smodel();
	
	shus_premium();
	
	shus_fukkjn();
	
	shus_econ_out();
	shus_nin_out();  
	
	shus_calc0();       
	shus_shushiout(0);  
	shus_fullout(0);    
	
	if(Fpset==8) shus_calc8();
	
	if(Fpset==9) shus_calc9();
	
	shus_shushiout(1);
	shus_fullout(1);
	
	if(Fpset!=9) shus_cutout();
	
	shus_Tokutyoout();
		
	
	if(Saimu==0 || Saimu==1 || Saimu==2) shus_summary();
    
}



void shus_init(void){
	int jj, k, x, dx;
	int ii, is, ie, usd;
	
	is=1;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		
		usd=ii2usd(ii);
		
		for(k=Ks; k<=Ke; k++){
			for(x=XA-1; x<=XB; x++){
				if(x<67){ dx = 66; } else { dx = x; }
				
				E3dxb[ii][0][k-STTY][dx] += D3bxtp[ii][0][0][1][k-STTY][x];
				E3dxb[ii][1][k-STTY][dx] +=( D3bxtp[ii][0][0][3][k-STTY][x] + D3bxtp[ii][0][0][4][k-STTY][x]
				                            +D3bxtp[ii][0][0][6][k-STTY][x] + D3bxtp[ii][0][0][7][k-STTY][x]);
				E3dxb[ii][2][k-STTY][dx] += D3bxtp[ii][0][0][5][k-STTY][x];
				E3dxb[ii][3][k-STTY][dx] += Kfpbxtp[ii][0][0][1][k-STTY][x];
				E3dxb[ii][4][k-STTY][dx] += Kfpbxtp[ii][0][0][2][k-STTY][x];
				E3dxb[ii][5][k-STTY][dx] += Kfpbxtp[ii][0][0][7][k-STTY][x];
				
				E3dxb[ii][6][k-STTY][dx] += Kyosdx[0][usd][0][k-STTY][x];
				E3dxb[ii][7][k-STTY][dx] += Kfkyosdx[0][usd][0][k-STTY][x];
				E3dxb[ii][8][k-STTY][dx] += Kyosdx[1][usd][0][k-STTY][x];
				E3dxb[ii][9][k-STTY][dx] += Kfkyosdx[1][usd][0][k-STTY][x];
				E3dxb[ii][10][k-STTY][dx]+= Kyosdx[0][usd][1][k-STTY][x];
				E3dxb[ii][11][k-STTY][dx]+= Kfkyosdx[0][usd][1][k-STTY][x];
				E3dxb[ii][12][k-STTY][dx]+= Kyosdx[1][usd][1][k-STTY][x];
				E3dxb[ii][13][k-STTY][dx]+= Kfkyosdx[1][usd][1][k-STTY][x];
			}
		}
	}

	if (Touitu>=1){
		for(k=Ks; k<=Ke; k++){
			for(x=XA-1; x<=XB; x++){
				if(x<67){ dx = 66; } else { dx = x; }
				E3dxb[1][6][k-STTY][dx] += (Kyosdx[0][7][0][k-STTY][x]+Kyosdx[0][8][0][k-STTY][x]);
				E3dxb[1][7][k-STTY][dx] += (Kfkyosdx[0][7][0][k-STTY][x]+Kfkyosdx[0][8][0][k-STTY][x]);
				E3dxb[1][8][k-STTY][dx] += (Kyosdx[1][7][0][k-STTY][x]+Kyosdx[1][8][0][k-STTY][x]);
				E3dxb[1][9][k-STTY][dx] += (Kfkyosdx[1][7][0][k-STTY][x]+Kfkyosdx[1][8][0][k-STTY][x]);
				E3dxb[1][10][k-STTY][dx]+= (Kyosdx[0][7][1][k-STTY][x]+Kyosdx[0][8][1][k-STTY][x]);
				E3dxb[1][11][k-STTY][dx]+= (Kfkyosdx[0][7][1][k-STTY][x]+Kfkyosdx[0][8][1][k-STTY][x]);
				E3dxb[1][12][k-STTY][dx]+= (Kyosdx[1][7][1][k-STTY][x]+Kyosdx[1][8][1][k-STTY][x]);
				E3dxb[1][13][k-STTY][dx]+= (Kfkyosdx[1][7][1][k-STTY][x]+Kfkyosdx[1][8][1][k-STTY][x]);
				
			}
			E3dxb[1][2][k-STTY][66] += (Kokusyushi[9][k-STTY]/nendohosei);
		}
	}
	
	for(ii=1; ii<=4; ii++){
	for(jj=0; jj<=13; jj++){
	for(k=Ks; k<=Ke; k++){
			for(x=66; x<=XB; x++){
				E3dxb[0][jj][k-STTY][x] += E3dxb[ii][jj][k-STTY][x];
			}
	}
	}
	}
}

void init_premium(void){
	int ii, k;
	double dtemp1, dtemp2;
	
	if(Ks<10 || Ks<STTY){
		printf("【警告】保険料率が正しくセットできていません\n");
	}
	
	dtemp1 = 0.1358;
	dtemp2 = 0.1496;
	for(k=4; k<=ENDY; k++){
	    dtemp1 += 0.00354;
	    dtemp2 += 0.00248;
		if(k>=STTY){
			Prema[1][k-STTY] = MIN(0.183, dtemp1);
			Prema[5][k-STTY] = MIN(0.183, dtemp2);
		}
	}
	dtemp1 = 0.15154;
	dtemp2 = 0.1223;
	for(k=10; k<=ENDY; k++){
		dtemp1 += 0.00354;
		dtemp2 += 0.00354;
		if(k>=STTY){
			Prema[2][k-STTY] = Prema[3][k-STTY] = MIN(0.183, dtemp1);
			Prema[4][k-STTY] = MIN(0.183, dtemp2);
		}
	}
	
	for(ii=1; ii<=5; ii++){	 
		if(ii==1 || ii==5 ){  
			dtemp1=6.0;
			dtemp2=6.0;
		} else if(ii==2 || ii==3){  
			dtemp1=5.0;
			dtemp2=7.0;
		} else if(ii==4){
			dtemp1= 1.0;
			dtemp2=11.0;
		}
		for(k=Ks+1; k<=ENDY; k++){
			Premb[ii][k-STTY] = (dtemp1 * Prema[ii][k-1-STTY] + dtemp2 * Prema[ii][k-STTY] ) / 12.;
		}
	}
}


void shus_premium(void){	
	int k, s;
	int is, ie, ii, se;
	double prem[3];	
	double dtemp;

	is=1;
	ie=4;
	
	if(Flg_Houjou>=1){
		for(ii=is; ii<=ie; ii++){
			if(ii==1) se=3;
			else      se=2;
			for(s=1; s<=se; s++){
				for(k=Ks; k<=Ke; k++){
					if(k==Houjou_Yr){
                      if(s==1||s==3){
						An[ii][s][k-STTY]    *= 1.0 + (Houjou_R1 - 1.0) / 2.0;
						Aniku[ii][s][k-STTY] *= 1.0 + (Houjou_R1 - 1.0) / 2.0;
						A[ii][s][k-STTY]     *= 1.0 + (Houjou_R1 - 1.0) / 2.0;
						Aiku[ii][s][k-STTY]  *= 1.0 + (Houjou_R1 - 1.0) / 2.0;
                      } else {
						An[ii][s][k-STTY]    *= 1.0 + (Houjou_R2 - 1.0) / 2.0;
						Aniku[ii][s][k-STTY] *= 1.0 + (Houjou_R2 - 1.0) / 2.0;
						A[ii][s][k-STTY]     *= 1.0 + (Houjou_R2 - 1.0) / 2.0;
						Aiku[ii][s][k-STTY]  *= 1.0 + (Houjou_R2 - 1.0) / 2.0;
                      }
					  if(k==Part_Yr2 || k==Part_Yr3){
                          if(s==1||s==3){
							Anpart[s][k-STTY]    *= Houjou_R1;
							Anikupart[s][k-STTY] *= Houjou_R1;
							Apart[s][k-STTY]     *= Houjou_R1;
							Aikupart[s][k-STTY]  *= Houjou_R1;
                          } else {
							Anpart[s][k-STTY]    *= Houjou_R2;
							Anikupart[s][k-STTY] *= Houjou_R2;
							Apart[s][k-STTY]     *= Houjou_R2;
							Aikupart[s][k-STTY]  *= Houjou_R2;
                          }
					  }
					}else if(k>Houjou_Yr){
                      if(s==1||s==3){
						An[ii][s][k-STTY]    *= Houjou_R1;
						Aniku[ii][s][k-STTY] *= Houjou_R1;
						A[ii][s][k-STTY]     *= Houjou_R1;
						Aiku[ii][s][k-STTY]  *= Houjou_R1;
                      } else {
						An[ii][s][k-STTY]    *= Houjou_R2;
						Aniku[ii][s][k-STTY] *= Houjou_R2;
						A[ii][s][k-STTY]     *= Houjou_R2;
						Aiku[ii][s][k-STTY]  *= Houjou_R2;
                      }
					  if(k==Part_Yr2 || k==Part_Yr3){
                          if(s==1||s==3){
							Anpart[s][k-STTY]    *= Houjou_R1;
							Anikupart[s][k-STTY] *= Houjou_R1;
							Apart[s][k-STTY]     *= Houjou_R1;
							Aikupart[s][k-STTY]  *= Houjou_R1;
                          } else {
							Anpart[s][k-STTY]    *= Houjou_R2;
							Anikupart[s][k-STTY] *= Houjou_R2;
							Apart[s][k-STTY]     *= Houjou_R2;
							Aikupart[s][k-STTY]  *= Houjou_R2;
                          }
					  }
					}
				}
			}
            for(k=Ks; k<=Ke; k++){
              An[ii][0][k-STTY]    = An[ii][1][k-STTY] + An[ii][2][k-STTY] +An[ii][3][k-STTY];
			  Aniku[ii][0][k-STTY] = Aniku[ii][1][k-STTY] + Aniku[ii][2][k-STTY] + Aniku[ii][3][k-STTY];
			  A[ii][0][k-STTY]     = A[ii][1][k-STTY] + A[ii][2][k-STTY] + A[ii][3][k-STTY];
			  Aiku[ii][0][k-STTY]  = Aiku[ii][1][k-STTY] + Aiku[ii][2][k-STTY] + Aiku[ii][3][k-STTY];
			  Anpart[0][k-STTY]    = Anpart[1][k-STTY] + Anpart[2][k-STTY] + Anpart[3][k-STTY];
			  Anikupart[0][k-STTY] = Anikupart[1][k-STTY] + Anikupart[2][k-STTY] + Anikupart[3][k-STTY];
			  Apart[0][k-STTY]     = Apart[1][k-STTY] + Apart[2][k-STTY] + Apart[3][k-STTY];
			  Aikupart[0][k-STTY]  = Aikupart[1][k-STTY] + Aikupart[2][k-STTY] + Aikupart[3][k-STTY];
            }
		}
	}
	
	
	for(ii=is; ii<=ie; ii++){
		for(k=Ks+1; k<=Ke; k++){
			if(ii==1){	
				prem[1]  = An[ii][0][k-STTY] * Premb[1][k-STTY];
				prem[2]  = An[ii][3][k-STTY] * (Premb[5][k-STTY]-Premb[1][k-STTY]);
				
				Cc[ii][1][k-STTY] = prem[1] + prem[2];
				Cc[ii][2][k-STTY] = prem[2];
				
				
				if(k==Part_Yr2 || k==Part_Yr3){
					dtemp=Cbm_Pt1;
					
					if(dtemp<=6.0){
						dtemp=Prema[1][k-STTY];
					}
					else{
						dtemp=((dtemp-6.0)*Prema[1][k-1-STTY]+6.0*Prema[1][k-STTY])/dtemp;
					}
					
					Cc[ii][22][k-STTY] = Anpart[0][k-STTY] * dtemp;
					Cc[ii][1][k-STTY] += Cc[ii][22][k-STTY];
					for(s=0; s<=3; s++){
						A[ii][s][k-STTY]    += Apart[s][k-STTY];
						Aiku[ii][s][k-STTY] += Aikupart[s][k-STTY];
						A60[ii][s][k-STTY]  += A60part[s][k-STTY];
						A65[ii][s][k-STTY]  += A65part[s][k-STTY];
						A70[ii][s][k-STTY]  += A70part[s][k-STTY];
						
						An[ii][s][k-STTY]    += Anpart[s][k-STTY];
						Aniku[ii][s][k-STTY] += Anikupart[s][k-STTY];
					}
				}
			} else {
				Cc[ii][1][k-STTY] = An[ii][0][k-STTY] * Premb[ii2psd(ii)][k-STTY];
			}
			
			Cc[ii][23][k-STTY] = A[ii][0][k-STTY] + Aiku[ii][0][k-STTY];
			Cc[ii][24][k-STTY] = An[ii][0][k-STTY]   ;
			Cc[ii][25][k-STTY] = Aniku[ii][0][k-STTY];
		}
	}

	if (Touitu>=1){
		for(k=Ks+1; k<=Ke; k++){
			Cc[1][1][k-STTY] += Kokusyushi[0][k-STTY];
		}
	}
		
	for(ii=1; ii<=4; ii++){
		for(k=Ks+1; k<=Ke; k++){
				Cc[0][1][k-STTY] += Cc[ii][1][k-STTY];
				if(ii==1) Cc[0][2][k-STTY] += Cc[ii][2][k-STTY];
				if((k==Part_Yr2 || k==Part_Yr3) && ii==1){
					Cc[0][22][k-STTY] += Cc[ii][22][k-STTY];
				}
				Cc[0][23][k-STTY] += Cc[ii][23][k-STTY];
				Cc[0][24][k-STTY] += Cc[ii][24][k-STTY];
				Cc[0][25][k-STTY] += Cc[ii][25][k-STTY];
		}
	}
}



void shus_fukkjn(void){
	int k, ii, is, ie, psd;
	double Kokufund;
	
	is=1;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		psd=ii2psd(ii);

		if(zan_fund == 0){
			if(Kijun==22) Cc[1][20][22-STTY] = 2088227.0E+8;
			if(Kijun==22) Cc[2][20][22-STTY] =   84763.0E+8;
			if(Kijun==22) Cc[3][20][22-STTY] =  250513.0E+8;
			if(Kijun==22) Cc[4][20][22-STTY] =   31275.0E+8;
		}
		
		for(k=Ks+1; k<=Ke; k++){
			
				Cc[ii][ 9][k-STTY] = 0;
				Cc[ii][10][k-STTY] = Nofu[psd][k-STTY];
				
				if(ii==1){
					if(k==21) Cc[ii][17][k-STTY] = 1787.94E+8;
					if(k==22) Cc[ii][17][k-STTY] = 1698.49E+8;
					if(k==23) Cc[ii][17][k-STTY] = 2000.00E+8;
					if(k>=24) Cc[ii][17][k-STTY] = 2300.00E+8;
				} else if(ii==2){
					if(k==21) Cc[ii][17][k-STTY] =  48.95E+8;
					if(k>=22) Cc[ii][17][k-STTY] =  52.56E+8;
				} else if(ii==3){
					if(k==21) Cc[ii][17][k-STTY] =  73.59E+8;
					if(k>=22) Cc[ii][17][k-STTY] =  75.30E+8;
				} else if(ii==4){
					if(k==21) Cc[ii][17][k-STTY] =  26.93E+8;
					if(k>=22) Cc[ii][17][k-STTY] =  29.49E+8;
				}
				
				
				if(zan_jimu == 0){
					if(k>=25){
						Cc[ii][17][k-STTY]=Cc[ii][17][24-STTY]/Ap[ii][0][24-STTY]*Ap[ii][0][k-STTY]*Id_Cid_2[k-ECSTY];
					}
				}
				Cc[ii][18][k-STTY] = 0;
		}
	}

	if(Touitu>=1){
		
		if(Kijun==21){ 
			Np[23][21-STTY] = 121176.0E+8;
			Cc[1][20][21-STTY] += 121176.0E+8 ;
		}
		if(Kijun==22){ 
			Np[23][22-STTY] = 124290.0E+8;
			Cc[1][20][22-STTY] += 124290.0E+8 ;
		}
		
		for(k=Ks+1; k<=Ke; k++){
			Cc[1][ 9][k-STTY] += (Kokusyushi[1][k-STTY]+Kokusyushi[2][k-STTY]);
			Cc[1][10][k-STTY] += Kokusyushi[3][k-STTY];
			Cc[1][17][k-STTY] += (Kokusyushi[5][k-STTY]+Kokusyushi[6][k-STTY]+Kokusyushi[7][k-STTY]+Kokusyushi[8][k-STTY]);
		}
	}

		for(ii=1; ii<=4; ii++){
			for(k=Ks+1; k<=Ke; k++){				
					Cc[0][9][k-STTY] +=Cc[ii][9][k-STTY];
					Cc[0][10][k-STTY]+=Cc[ii][10][k-STTY];
					Cc[0][17][k-STTY]+=Cc[ii][17][k-STTY];
					if(ii==1) Cc[0][20][k-STTY] = Cc[ii][20][k-STTY];
					Cc[ii][30][k-STTY] = Tumazumi[ii][k-STTY];
					Cc[0][30][k-STTY] += Tumazumi[ii][k-STTY];
			}
		}
	 	if(Touitu>=1){
			for(k=Ks+1; k<=Ke; k++){
				Cc[1][30][k-STTY] += Kokusyushi[4][k-STTY];
				Cc[0][30][k-STTY] += Kokusyushi[4][k-STTY];
			}
		}
}

