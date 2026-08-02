#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"


void shus_shushi(int ks, int ke){
	int k;
	int is, ie, ii;
	
	is=1;
	ie=4;
	
	for(k=ks; k<=ke; k++){
		for(ii=is; ii<=ie; ii++){
			Cc[ii][4][k-STTY]  =  Cc[ii][5][k-STTY] + Cc[ii][6][k-STTY]
			                    + Cc[ii][7][k-STTY] + Cc[ii][8][k-STTY];
			Cc[ii][12][k-STTY] =  Cc[ii][13][k-STTY] + Cc[ii][14][k-STTY] + Cc[ii][15][k-STTY];
			Cc[ii][11][k-STTY] =  Cc[ii][12][k-STTY] + Cc[ii][16][k-STTY]
			                    + Cc[ii][17][k-STTY] + Cc[ii][18][k-STTY];
			Cc[ii][3][k-STTY]  =  Cc[ii][20][k-1-STTY] * Ri[k-ECSTY]
					            + (  Cc[ii][1][k-STTY]  + Cc[ii][4][k-STTY] + Cc[ii][9][k-STTY]
					            + Cc[ii][10][k-STTY] - Cc[ii][11][k-STTY]         ) * Ri2[k-ECSTY];	
			Cc[ii][3][k-STTY]  += Cc[ii][30][k-STTY] * Ri2[k-ECSTY];
			
			Cc[ii][0][k-STTY]  =  Cc[ii][1][k-STTY] + Cc[ii][3][k-STTY]  + Cc[ii][4][k-STTY]
				                + Cc[ii][9][k-STTY] + Cc[ii][10][k-STTY];
			Cc[ii][0][k-STTY] += Cc[ii][30][k-STTY];
			Cc[ii][19][k-STTY] =  Cc[ii][0][k-STTY] - Cc[ii][11][k-STTY];
			
			if(k > Kijun){
				Cc[ii][20][k-STTY] = Cc[ii][20][k-1-STTY] + Cc[ii][19][k-STTY];
			} else {
				Cc[ii][0][k-STTY] = Cc[ii][3][k-STTY] = Cc[ii][19][k-STTY] = 0.;
			}
			
				if(ii==1){
					Cc[0][0][k-STTY]  = Cc[ii][0][k-STTY];
					Cc[0][3][k-STTY]  = Cc[ii][3][k-STTY];
					Cc[0][4][k-STTY]  = Cc[ii][4][k-STTY];
					Cc[0][11][k-STTY] = Cc[ii][11][k-STTY];
					Cc[0][12][k-STTY] = Cc[ii][12][k-STTY];
					Cc[0][19][k-STTY] = Cc[ii][19][k-STTY];
					Cc[0][20][k-STTY] = Cc[ii][20][k-STTY];
				} else {
						Cc[0][0][k-STTY]  += Cc[ii][0][k-STTY];
						Cc[0][3][k-STTY]  += Cc[ii][3][k-STTY];
						Cc[0][4][k-STTY]  += Cc[ii][4][k-STTY];
						Cc[0][11][k-STTY] += Cc[ii][11][k-STTY];
						Cc[0][12][k-STTY] += Cc[ii][12][k-STTY];
						Cc[0][19][k-STTY] += Cc[ii][19][k-STTY];
						Cc[0][20][k-STTY] += Cc[ii][20][k-STTY];
				}
		}
	}
}



void shus_ave(int ks, int ke, int calhh, int calhp){
	int k, jj, x, dx;
	int is, ie, ii, hh;
	
	int etoc[14] = {13,14,15,6,7,8,16,5,16,5,16,5,16,5};
	double riv,bpre, bend;
	
	
	is=0;
	ie=4;
	
	if(Touitu==0){
	 for(ii=is; ii<=ie; ii++){
		for(jj=0; jj<=7; jj++){
			if(calhh<=0 && (jj==0 || jj==3)) continue;
			if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
			for(k=ks; k<=ke; k++){
				Cc[ii][etoc[jj]][k-STTY] = 0.;
			}
		}
		
		if(ii==0) continue;
		
		for(jj=0; jj<=9; jj++){
			if(calhh<=0 && (jj==0 || jj==3)) continue;
			if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
			for(k=ks; k<=ke; k++){
				for(x=66; x<=XB; x++){
					if(jj==2 || jj==8 || jj==9) dx=67;
					else                        dx=x;
					
					if(jj==0 || jj==3){
						riv = Krb[k-ECSTY][dx-ECXA] * (Escutrrh[k-ECSTY][dx-ECXA]/Escutrrh[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-1-STTY][x-1] * Escutrrh[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj][k-STTY][x] * Escutrrh[k-ECSTY][dx-ECXA];
					} else if (jj==1 || jj==2 || jj==4 || jj==5){
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrt[k-ECSTY][dx-ECXA]/Escutrrt[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-1-STTY][x-1] * Escutrrt[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj][k-STTY][x] * Escutrrt[k-ECSTY][dx-ECXA];
					} else if(jj==6 || jj==7 || jj==8 || jj==9) {
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrt[k-ECSTY][dx-ECXA]/Escutrrt[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-STTY][x-1] * Escutrrt[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj+4][k-STTY][x] * Escutrrt[k-ECSTY][dx-ECXA];
					}
					
					if(Flg_matsu == 0){
						Cc[ii][etoc[jj]][k-STTY] += (bpre * 2. + bpre * riv * 6. + bend * 4.) / 12.;
					}
				}
				if(jj<=2){
					Cc[ii][etoc[jj]][k-STTY] *= nendohosei;
				}
			}
		}
			for(jj=0; jj<=7; jj++){
				if(calhh<=0 && (jj==0 || jj==3)) continue;
				if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
				for(k=ks; k<=ke; k++){
						Cc[0][etoc[jj]][k-STTY] += Cc[ii][etoc[jj]][k-STTY];
				}
			}
	 }
    }
    else if(Touitu>=1){
	 for(ii=is; ii<=ie; ii++){
		for(jj=0; jj<=7; jj++){
			if(calhh<=0 && (jj==0 || jj==3)) continue;
			if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
			for(k=ks; k<=ke; k++){
				Cc[ii][etoc[jj]][k-STTY] = 0.;
			}
		}
		
		if(ii==0) continue;
		
		for(jj=0; jj<=9; jj++){
			if(calhh<=0 && (jj==0 || jj==3)) continue;
			if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
			for(k=ks; k<=ke; k++){
				for(x=66; x<=XB; x++){
					if(jj==2 || jj==8 || jj==9) dx=67;
					else                        dx=x;
					
					if(jj==0 || jj==3){
						riv = Krb[k-ECSTY][dx-ECXA] * (Escutrrh[k-ECSTY][dx-ECXA]/Escutrrh[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-1-STTY][x-1] * Escutrrh[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj][k-STTY][x] * Escutrrh[k-ECSTY][dx-ECXA];
					} else if (jj==1 || jj==2 || jj==4 || jj==5){
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrh[k-ECSTY][dx-ECXA]/Escutrrh[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-1-STTY][x-1] * Escutrrh[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj][k-STTY][x] * Escutrrh[k-ECSTY][dx-ECXA];
					} else if(jj==6 || jj==7 || jj==8 || jj==9) {
						riv = Kra[k-ECSTY][dx-ECXA] * (Escutrrh[k-ECSTY][dx-ECXA]/Escutrrh[k-1-ECSTY][dx-1-ECXA]);
						bpre = E3dxb[ii][jj][k-STTY][x-1] * Escutrrh[k-1-ECSTY][dx-1-ECXA];
						bend = E3dxb[ii][jj+4][k-STTY][x] * Escutrrh[k-ECSTY][dx-ECXA];
					}
					if(Flg_matsu == 0){
						Cc[ii][etoc[jj]][k-STTY] += (bpre * 2. + bpre * riv * 6. + bend * 4.) / 12.;
					}
				}
				if(jj<=2){
					Cc[ii][etoc[jj]][k-STTY] *= nendohosei;
				}
			}
		}
			for(jj=0; jj<=7; jj++){
				if(calhh<=0 && (jj==0 || jj==3)) continue;
				if(calhp<=0 && (jj==1 || jj==2 || jj>=4)) continue;
				for(k=ks; k<=ke; k++){
						Cc[0][etoc[jj]][k-STTY] += Cc[ii][etoc[jj]][k-STTY];
				}
			}
	 }	 
    }
}


void shus_calc0(void){
	shus_ave(Ks+1, Ke, 1, 1);
	shus_shushi(Ks+1, Ke);
}



int shus_calc8(void){
	int k, x, dx;
	int flg_end, kk, kn, kend, n , k1, k_jisseki;
	double rh[ECEDY-ECSTY+1][116-ECXA];
	double rrh_max[116-ECXA], rrh_min[116-ECXA], dtemp, dtemp2;
	double dcutr;
	double r, r0, r1, f, f0, f1;
	int ii;
	
	
	ii=0;
	
	k_jisseki = 24;

	kend = atoi(Cutrfile3) + 100;
	kn = kend + 1;
	
	for(k=5; k<=Ke; k++){
		for(x=ECXA; x<=XB; x++){
			if(x<68){
				dx = 67;
				dcutr = MAX(0.0, Scutrk1[k-ECSTY]);
			} else {
				dx = x;
				dcutr = MAX(0.0, Scutrk1[k-ECSTY]);
			}
			if((k >= Kmakuro_Yr && Flg_Dmakuro != 1) || (Flg_Dmakuro == 1 && k <= Dmakuro_Yr)){
				dcutr = (1.0 + dcutr) / Tokutyo[k-1-ECSTY][MAX(ECXA,x-1)-ECXA] - 1.0;
			}
			if(Flg_Dmakuro != 1 || k < Dmakuro_Yr){
				
				rh[k-ECSTY][x-ECXA] = 1.0 + MAX(0.0, MIN(dcutr, Krb[k-ECSTY][dx-ECXA]-1.0));
				if(k==14 && x<=76) rh[k-ECSTY][x-ECXA]=nround(0.978/0.9761,3);
				
			}
			 else {
				rh[k-ECSTY][x-ECXA] = 1.0 + MAX(0.0, dcutr);
			}
			if(k >= Kmakuro_Yr){
				Tokutyo[k-ECSTY][x-ECXA] = rh[k-ECSTY][x-ECXA] / (1.0 + dcutr);
				if(k==23) Tokutyo[k-ECSTY][x-ECXA]=1.0;
		  		if(k==24) Tokutyo[k-ECSTY][x-ECXA]=1.0;
				
				if(Tokutyo[k-ECSTY][x-ECXA]<-0. || Tokutyo[k-ECSTY][x-ECXA]>1.){
					printf("特別調整率エラー x=%d, k=%d, %.f\n", x, k, Tokutyo[k-ECSTY][x-ECXA]);
					exit(1);
				}
			}
		
			if(k==23) rh[k-ECSTY][x-ECXA]=1.0/0.994;
		  	if(k==24) rh[k-ECSTY][x-ECXA]=1.0/0.996;
		  
		  if(Flg_Kmakuro == 1){
			if(k >= Kmakuro_Yr2){
				Tokutyo[k-ECSTY][x-ECXA]= 1.0;
			}
		  }
		}
		
		if(k<=Kijun){
			Escutrrh[k-ECSTY][XA-1-ECXA] = 1;
			for(x=XA; x<=XB; x++){
				Escutrrh[k-ECSTY][x-ECXA] = 1;
			}
		} else {
			Escutrrh[k-ECSTY][XA-1-ECXA] = Escutrrh[k-1-ECSTY][XA-1-ECXA];
			for(x=XA; x<=XB; x++){
				Escutrrh[k-ECSTY][x-ECXA] = Escutrrh[k-1-ECSTY][x-1-ECXA];
			}
		}
		for(x=XA-1; x<=XB; x++){
			Escutrrt[k-ECSTY][x-ECXA] = Scutrrki[k-ECSTY][x-ECXA];
		}
	}
	
	shus_ave(Kijun, Ke, 1, 1);
	shus_shushi(Kijun+1, Ke);
	f0 = 0.0;
	f1 = Cc[ii][20][kend-1-STTY]-Cc[ii][11][kend-STTY] * Ca;
	
	flg_end = 1;
	for(k=Kijun+1; k<Ke && flg_end>0; k++){
		Escutrrh[k-ECSTY][XA-1-ECXA] = Escutrrh[k-1-ECSTY][XA-1-ECXA] / rh[k-ECSTY][XA-1-ECXA];
		for(x=XA; x<=XB; x++){
			Escutrrh[k-ECSTY][x-ECXA] = Escutrrh[k-1-ECSTY][x-1-ECXA] / rh[k-ECSTY][x-ECXA];
		}
		for(kk=k+1; kk<=Ke; kk++){
			Escutrrh[kk-ECSTY][XA-1-ECXA] = Escutrrh[kk-1-ECSTY][XA-1-ECXA];
			for(x=XA; x<=XB; x++){
				Escutrrh[kk-ECSTY][x-ECXA] = Escutrrh[kk-1-ECSTY][x-1-ECXA];
			}
		}
		shus_ave(k, Ke, 1, 1);
		shus_shushi(k, Ke);
		f0 = f1;
		f1 = Cc[ii][20][kend-1-STTY]-Cc[ii][11][kend-STTY] * Ca;
		if(f1 >= 0.0 && k >= k_jisseki){
			kn = k;
			flg_end = 0;
		}
	}
	if(kn > kend || flg_end>0){
		printf("最終年度まで調整しても均衡できませんでした\n");
		return(1);
	}
	
	for(x=XA-1; x<=XB; x++){
		rrh_max[x-ECXA] = Escutrrh[kn-ECSTY][x-ECXA];
		rrh_min[x-ECXA] = Escutrrh[kn-1-ECSTY][MAX(x-1, XA-1)-ECXA];
	}
	
	
	if(kn > k_jisseki) flg_end = 1;
	else               flg_end = 0;
	r0 = 0.0; r1 = 1.0;
	for(n=0; n<62 && flg_end>0; n++){
		printf("%2d年度%2d回目の反復計算 ", kn, n+1);
		if(n<14){
			if(f1 == f0){
				printf("（エラー）分母がゼロになり発散しています\n");
			}
			r = r1 - f1 * (r1-r0)/(f1-f0);
		} else {
			r = (r1 + r0) / 2.0;	printf("<2分法>");
		}
		for(x=XA-1; x<=XB; x++){
			Escutrrh[kn-ECSTY][x-ECXA] = rrh_min[x-ECXA] * (1.0-r) + rrh_max[x-ECXA] * r;
		}
		for(kk=kn+1; kk<=Ke; kk++){
			Escutrrh[kk-ECSTY][XA-1-ECXA] = Escutrrh[kk-1-ECSTY][XA-1-ECXA];
			for(x=XA; x<=XB; x++){
				Escutrrh[kk-ECSTY][x-ECXA] = Escutrrh[kk-1-ECSTY][x-1-ECXA];
			}
		}
		shus_ave(kn, Ke, 1, 1);
		shus_shushi(kn, Ke);
		f = Cc[ii][20][kend-1-STTY] - Cc[ii][11][kend-STTY] * Ca;
		printf("r = %15.13f (%9.7f), f = %f\n", r, r1-r0, f);
		if(fabs(Cc[ii][20][kend-1-STTY]/Cc[ii][11][kend-STTY] - Ca) < 0.5E-13){
			flg_end = 0;
		} else if (f * f0 > 0.0) {
			r0 = r; f0 = f;
		} else {
			r1 = r; f1 = f;
		}
	}
	if (flg_end>0){
		printf("収束しませんでした\n");
		return(1);
	}
	if(Touitu>=1){
		for(k=5; k<=Ke; k++){
			for(x=XA-1; x<=XB; x++){
				Escutrrt[k-ECSTY][x-ECXA] = Escutrrh[k-ECSTY][x-ECXA];
			}
		}
	}

	print_number();
	printf(" 最終代替率\n");
	
	dtemp = (Mhirei[Ke-STTY][0]*Escutrrh[Ke-ECSTY][67-ECXA] + Mkiso[Ke-STTY]*Escutrrt[Ke-ECSTY][67-ECXA])
		       / Kw[Ke-STTY][0] *100.;
	printf("  一元化モデル：%.13f \n", dtemp);
	
	dtemp = Mhirei[Ke-STTY][0]*Escutrrh[Ke-ECSTY][67-ECXA] / Kw[Ke-STTY][0] *100.;
	dtemp2= Mkiso[Ke-STTY]    *Escutrrt[Ke-ECSTY][67-ECXA] / Kw[Ke-STTY][0] *100.;
	printf("      うち比例：%.13f , うち基礎：%.13f\n", dtemp, dtemp2);		
	printf(" 最終カット率  厚年： %.14f,      国年： %.14f\n",
	       1.0-Escutrrh[kend-ECSTY][67-ECXA], 1.0-Escutrrt[kend-ECSTY][67-ECXA]);
	
	return(0);	
}




void shus_calc9(void){
	int k, x;
	
	print_number();
	for(k=5; k<=Ke; k++){
		for(x=XA-1; x<=XB; x++){
			Escutrrh[k-ECSTY][x-ECXA] = Scutrrh[k-ECSTY][x-ECXA];
			Escutrrt[k-ECSTY][x-ECXA] = Scutrrt[k-ECSTY][x-ECXA];
		}
	}
	shus_ave(Kijun, Ke, 1, 1);
	shus_shushi(Kijun+1, Ke);
}


void shus_smodel(void){
	int k, i, k_last;
	int mdlk;
	double kasho, mihanei;
	
	mdlk = 24;
	kasho = 0.813;
	mihanei = 0.985;
	
	W[mdlk-STTY][0] = 455000.;
	W[mdlk-STTY][1] = 443000.;
	W[mdlk-STTY][2] = 580000.;
	W[mdlk-STTY][3] = 174000.;
	W[mdlk-STTY][4] = 305000.;
	
	Mkiso[mdlk-STTY] = 136000. * mihanei / 0.994 / 0.996;
	
	for(i=0; i<5; i++){
		Kw[mdlk-STTY][i]= round(W[mdlk-STTY][i] * kasho);
		Mhirei[mdlk-STTY][i]
		  = round(W[mdlk-STTY][i] * 5.481E-3 * 0.926 * 40.) / 0.994 / 0.996;
	}
	
	for(k=mdlk+1; k<=Ke; k++){
		if(kakusa == 2){
			for(i=0; i<5; i++){
				W[k-STTY][i] = (1.0+H[k-1-ECSTY]) * W[k-1-STTY][i];
			}
		}  
		
		for(i=0; i<5; i++){
			Kw[k-STTY][i] = Kw[k-1-STTY][i] * W[k-STTY][i] / W[k-1-STTY][i]
			                 * (0.91-Prema[1][k-1-STTY]/2.) / (0.91-Prema[1][k-2-STTY]/2.);
			Mhirei[k-STTY][i] = Mhirei[k-1-STTY][i] * Kw[k-STTY][i] / Kw[k-1-STTY][i];
		}
		Mkiso[k-STTY] = Mkiso[k-1-STTY] * (1.0+H[k-1-ECSTY])
		               * (0.91-Prema[1][k-1-STTY]/2.) / (0.91-Prema[1][k-2-STTY]/2.) ; 
	}
}
