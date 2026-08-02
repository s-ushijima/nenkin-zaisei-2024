#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"


void shus_econ_out(void){
	int k;
	int is, ie, ii;
	FILE *ofp;
	
	is=0;
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		ofp = ofp01_shushi[ii];
		
		fprintf(ofp, "·ÐºÑÁ°ÄóÅù\n");
		fprintf(ofp, "Ç¯ÅÙ,Êª²Á,ÄÂ¶â,±¿ÍÑÍø²ó¤ê,ÈæÎã²þÄêÎ¨,ÈæÎã´ûºÛ68ºÐ,´ðÁÃ²þÄêÎ¨,´ðÁÃ´ûºÛ68ºÐ,\n");
		for(k=5; k<=Ke; k++){
			fprintf(ofp, "%3d, %5.2f, %5.2f, %5.2f, ", k, Ci[k-ECSTY]*100.0, H[k-ECSTY]*100.0, Ri[k-ECSTY]*100.0);
			fprintf(ofp, "%5.2f, %5.2f, %5.2f, %5.2f,\n",
			    (Krb[k-ECSTY][67-ECXA]-1.0)*100.0,(Krb[k-ECSTY][68-ECXA]-1.0)*100.0,
			    (Kra[k-ECSTY][67-ECXA]-1.0)*100.0,(Kra[k-ECSTY][68-ECXA]-1.0)*100.0);
		}
		fprintf(ofp, "\n");
	}
}



void shus_nin_out(void){  
	int s, i, k, x;
	int is, ie, ii;
	int s2;
	double t4sx[5][4][7][ENDY-STTY+1];
	FILE *ofp;
	
	for(ii=0; ii<5; ii++){
		for(s=0; s<4; s++){
			for(i=0; i<7; i++){
				for(k=0; k<ENDY-STTY+1; k++){
					t4sx[ii][s][i][k] = 0.;
				}
			}
		}
	}
	
	is=1;  
	ie=4;
	
	for(ii=is; ii<=ie; ii++){
		if(ii<=1) s2 = 3;
		else      s2 = 2;
		
		for(s=0; s<=s2; s++){
			for(i=0; i<7; i++){
				for(k=Ks+1; k<=Ke; k++){					
						for(x=XA-1; x<=XB; x++){
							t4sx[ii][s][i][k-STTY] += T4xtp[ii][s][i][k-STTY][x];
							t4sx[0][s][i][k-STTY] += T4xtp[ii][s][i][k-STTY][x];
						}
				}
			}
		}
		
		for(s=0; s<=s2; s++){
			for(k=Ks+1; k<=Ke; k++){
					Ap[0][s][k-STTY]   += Ap[ii][s][k-STTY];
					Ap65[0][s][k-STTY] += Ap65[ii][s][k-STTY];
			}
		}
	}
	
	is=0;
	
	for(ii=is; ii<=ie; ii++){
		ofp = ofp01_shushi[ii];
		
		if(ii<=1) s2 = 3;
		else      s2 = 2;
		
		fprintf(ofp, "Ç¯ÅÙ,ÈïÊÝ¸±¼Ô,Ï·Îð,Ï·ºß,ÄÌÏ·,ÄÌºß,¾ã³²,°äÂ²,");
		fprintf(ofp, "ÈïÊÝ¸±¼Ô¡¦ÃË,ÈïÊÝ¸±¼Ô¡¦½÷,");
		fprintf(ofp, "65ºÐ°Ê¾åÈïÊÝ¸±¼Ô¡¦ÃË,65ºÐ°Ê¾åÈïÊÝ¸±¼Ô¡¦½÷,");
		fprintf(ofp, "Ï·Îð­¡,Ï·ºß­¡,ÄÌÏ·­¡,ÄÌºß­¡,¾ã³²­¡,°äÂ²­¡,");
		fprintf(ofp, "Ï·Îð­¢,Ï·ºß­¢,ÄÌÏ·­¢,ÄÌºß­¢,¾ã³²­¢,°äÂ²­¢,");
		if(s2==3){
			fprintf(ofp, "Ï·Îð­£,Ï·ºß­£,ÄÌÏ·­£,ÄÌºß­£,¾ã³²­£,°äÂ²­£");
		}
		fprintf(ofp, "\n");
		
		for(k=FLKS; k<=FLKE; k++){
			fprintf(ofp, "%3d,", k);
			fprintf(ofp, "%14.8e,", Ap[ii][0][k-STTY]);
			for(i=1; i<=6; i++) fprintf(ofp, "%14.8e,", t4sx[ii][0][i][k-STTY]);
			fprintf(ofp, "%14.8e,%14.8e,", Ap[ii][1][k-STTY]  +Ap[ii][3][k-STTY],   Ap[ii][2][k-STTY]);
			fprintf(ofp, "%14.8e,%14.8e,", Ap65[ii][1][k-STTY]+Ap65[ii][3][k-STTY], Ap65[ii][2][k-STTY]);
			for(s=1; s<=s2; s++){
				for(i=1; i<=6; i++){
					fprintf(ofp, "%14.8e,", t4sx[ii][s][i][k-STTY]);
				}
			}
			fprintf(ofp, "\n");
		}
	}
	
	if(Saimu==0 ||Saimu==1 || Saimu==2){
		
		for(ii=1; ii<=4 ; ii++){
			for(i=1; i<=6 ; i++){
				if(i==1 || i==2){
					s=0;
				} else if (i<=4){
					s=1;
				} else {
					s=i-3;
				}
				for(k=FLKS; k<=FLKE; k++){
					Ukyu[0][ii][s][k-STTY] += t4sx[ii][0][i][k-STTY];
					Ukyu[0][0][s][k-STTY]  += t4sx[ii][0][i][k-STTY];
				}
			}
		}
	}
}



void shus_shushiout(int mode){
	int k, i;
	int kend_t, kend_h;
	double dtemp;
	FILE *ofp;
	int is, ie, ii, psd;
	double tanni[31];
	
	for(i=0; i<31; i++){
		if(i<=25 || i==30){
			tanni[i] = 1.0E-8;
		}else if(i==27 || i==28){
			tanni[i] = 1.0E+2;
		}else{
			tanni[i] = 1.0;
		}
	}
	
	is=0;
	ie=4;
	
	if(mode==1){
		kend_h = 0;
		dtemp = Escutrrh[Ke-1-ECSTY][67-ECXA];
		for(k=Ke-1; k>=Ks+1; k--){
			if(Escutrrh[k-1-ECSTY][67-ECXA]-dtemp>1.0E-13){
				kend_h = k;
				break;
			} else {
				dtemp = Escutrrh[k-1-ECSTY][67-ECXA];
			}
		}
		kend_t = 0;
		dtemp = Escutrrt[Ke-1-ECSTY][67-ECXA];
		for(k=Ke-1; k>=Ks+1; k--){
			if(Escutrrt[k-1-ECSTY][67-ECXA]-dtemp>1.0E-13){
				kend_t = k;
				break;
			} else {
				dtemp = Escutrrt[k-1-ECSTY][67-ECXA];
			}
		}
	}
	
	for(ii=is; ii<=ie; ii++){
		ofp = ofp01_shushi[ii];
		
		if(mode==1){
			if(ii==1) printf(" Ä´À°ºÇ½ªÇ¯ÅÙ ");
			fprintf(ofp, "\nÄ´À°ºÇ½ªÇ¯ÅÙ, ");
			
			if(kend_h!=0 && kend_h!=Ke-1){
				if(ii==1)  printf(" ¸üÇ¯¡§%3d (%.13f) ", kend_h, Escutrrh[MAX(0,kend_h-ECSTY)][67-ECXA]*100.);
				fprintf(ofp, " ¸üÇ¯, %3d, %20.14e, ", kend_h, Escutrrh[MAX(0,kend_h-ECSTY)][67-ECXA]);
			} else {
				if(ii==1) printf(" ¸üÇ¯¡§ -  (%20.14e)", Escutrrh[Ke-1-ECSTY][67-ECXA]);
				fprintf(ofp, " ¸üÇ¯, - , - , ");
			}
			
			if(kend_t!=0 && kend_t!=Ke-1){
				if(ii==1)  printf(" ¹ñÇ¯¡§%3d (%.13f)\n", kend_t, Escutrrt[MAX(0,kend_t-ECSTY)][67-ECXA]*100.);
				fprintf(ofp, " ¹ñÇ¯, %3d, %20.14e\n", kend_t, Escutrrt[MAX(0,kend_t-ECSTY)][67-ECXA]);
			} else {
				if(ii==1) printf(" ¹ñÇ¯¡§ -  (%20.14e)\n", Escutrrt[Ke-1-ECSTY][67-ECXA]);
				fprintf(ofp, " ¹ñÇ¯, - , - \n");
			}
		}
		
		fprintf(ofp, "\n");
		
		
		if(mode==0){
			fprintf(ofp, "\n¼ý»Ù¸«ÄÌ¤·¡Ú¥¹¥é¥¤¥ÉÄ´À°Á°¡Û\n");
		} else {
			fprintf(ofp, "\n¼ý»Ù¸«ÄÌ¤·¡Ú¥¹¥é¥¤¥ÉÄ´À°¸å¡Û\n");
		}
		
		fprintf(ofp,"Ç¯ÅÙ,¼ýÆþ·×,ÊÝ¸±ÎÁ¼ýÆþ,(ºÆ)¾å¾è¤»Ê¬,±¿ÍÑ¼ýÆþ,¹ñ¸ËÉéÃ´,");
		fprintf(ofp, "(ºÆ)¹ñ¸Ë´ðÁÃ,(ºÆ)¹ñ¸Ë·Ð²áÈæÎã,(ºÆ)¹ñ¸Ë·Ð²áÄê³Û,");
		fprintf(ofp, "(ºÆ)¹ñ¸Ë¤«¤µ¾å¤²,»Ù±ç³Û¼ýÆþ,Ç¼ÉÕ¶â,");
		fprintf(ofp, "»Ù½Ð·×,ÆÈ¼«µëÉÕ,(ºÆ)ÆÈ¼«ÈæÎã,(ºÆ)ÆÈ¼«Äê³Û·Ï,");
		fprintf(ofp, "(ºÆ)ÆÈ¼«²Ãµë,´ðÁÃÇ¯¶âµò½Ð¶â,»öÌ³Èñ,»Ù±ç³Û»Ù½Ð,");
		fprintf(ofp, "¼ý»Ùº¹,Ç¯ÅÙËöÀÑÎ©¶â,ÀÑÎ©¶â(¸½ºß²Á³Ê),");
		fprintf(ofp, "(ºÆ)¥Ñ¡¼¥ÈÊÝ¸±ÎÁ,ÁíÊó½·Áí³Û,ÁíÊó½·³Û,°é»ùÊó½·³Û,ÀÑÎ©ÅÙ¹ç,ÊÝ¸±ÎÁÎ¨,Éê²ÝÊÝ¸±ÎÁÎ¨,,");
		fprintf(ofp, "ºÊÀÑ¤ßÊ¬ÇÛÅù,\n");
		
		
		for(k=FLKS; k<=FLKE; k++){
			
			if(k>=ECSTY && k<=ECEDY){
				Cc[ii][21][k-STTY] = Cc[ii][20][k-STTY] / Id_Hhd[k-ECSTY];
			} else {
				Cc[ii][21][k-STTY] = 0.;
			}
			if(Cc[ii][11][k-STTY]>0.){
				Cc[ii][26][k-STTY] = Cc[ii][20][k-1-STTY] / Cc[ii][11][k-STTY];
			} else {
				Cc[ii][26][k-STTY] = 0.;
			}
			if(ii==0) psd=1;
			else      psd=ii2psd(ii);
			
			if(k>=ECSTY && k<=ECEDY){
					Cc[ii][27][k-STTY] = Prema[psd][k-STTY];
			}
			
			if(Cc[ii][23][k-STTY]>0.){
				Cc[ii][28][k-STTY] = ( Cc[ii][11][k-STTY] - Cc[ii][2][k-STTY] - Cc[ii][4][k-STTY]
				                      -Cc[ii][9][k-STTY] - Cc[ii][10][k-STTY])
			        	            / Cc[ii][24][k-STTY];
			} else {
				Cc[ii][28][k-STTY] = 0.;
			}
			
			fprintf(ofp, "%3d,", k);
			for(i=0; i<31; i++){
				if(ii==1 || k!=Kyoskijun-1 || i!=30){
					fprintf(ofp, "%20.13e,", Cc[ii][i][k-STTY] * tanni[i]);
				} else {
					fprintf(ofp, "%20.13e,", Siwake[ii] * tanni[i]);
				}
			}
			fprintf(ofp, "\n");
		}
	}
}



void shus_cutout(void){
	
	int k, i;
	FILE *ofp;
	
	ofp = ofp_cuta;
	
	for(k=5; k<=8; k++){
		fprintf(ofp, "%4d,", k);
		for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", 1.);
		fprintf(ofp, "\n");
	}
	for(k=9; k<=FLKE; k++){
		fprintf(ofp, "%4d,", k);
		for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", Escutrrt[k-ECSTY][i-ECXA]);
		fprintf(ofp, "\n");
	}
	
	ofp = ofp_cutb;
	
	for(k=5; k<=8; k++){
		fprintf(ofp, "%4d,", k);
		for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", 1.);
		fprintf(ofp, "\n");
	}
	for(k=9; k<=FLKE; k++){
		fprintf(ofp, "%4d,", k);
		for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", Escutrrh[k-ECSTY][i-ECXA]);
		fprintf(ofp, "\n");
	}
	
	
	if(Touitu>=1){
	   ofp = ofp_cuta2;
	
	   for(k=5; k<=8; k++){
		    fprintf(ofp, "%4d,", k);
		    for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", 1.);
		    fprintf(ofp, "\n");
	   }
	   for(k=9; k<=FLKE; k++){
		   fprintf(ofp, "%4d,", k);
		   for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", Escutrrt[k-ECSTY][i-ECXA]);
	       fprintf(ofp, "\n");
	   }
	
	   ofp = ofp_cutb2;
	
	   for(k=5; k<=8; k++){
		   fprintf(ofp, "%4d,", k);
		   for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", 1.);
		   fprintf(ofp, "\n");
	   }
	   for(k=9; k<=FLKE; k++){
		   fprintf(ofp, "%4d,", k);
		   for(i=63; i<=115; i++) fprintf(ofp, "%20.14e,", Escutrrh[k-ECSTY][i-ECXA]);
		   fprintf(ofp, "\n");
	   }
	}
	
}



void shus_summary(void){
	FILE *ofp;
	int k, ii, i, k_model;
	int kend_t, kend_h;
	double r1, r1h, r1k, r2, r2h ,r2k;
	double dtemp;
	
	ofp=ofp03_summary;
	
	
	if(Saimu==0){
		fprintf(ofp, "%s, %s, %s\n", Nfile, Nfile2, Nfile3);
	} else {
		fprintf(ofp, "%s, %s, %s, %s\n", Saimushu, Nfile, Nfile2, Nfile3);
	}
	fprintf(ofp, "%s, %s\n", Ecfile, Wcfile);
	if(Saimu==0){
		fprintf(ofp, "%s\n", Nkfile);
	} else {
		fprintf(ofp, "%s, %s\n", Saimuski, Nkfile);
	}
	
	fprintf(ofp, "%s, Í½È÷:, %s, Cntlset:, %d, Seidn:, %d\n",
	                          Sifile, Cutrfile4, Cntlset, Seidn);
	
	fprintf(ofp, "\n");
	fprintf(ofp, "Flg_Part,%d,, Flg_Dmakuro,%d\n\n", Flg_Part, Flg_Dmakuro);
	
	kend_h = 0;
	dtemp = Escutrrh[Ke-1-ECSTY][67-ECXA];
	for(k=Ke-1; k>=Ks+1; k--){
		if(Escutrrh[k-1-ECSTY][67-ECXA]-dtemp>1.0E-13){
			kend_h = k;

			break;
		} else {
			dtemp = Escutrrh[k-1-ECSTY][67-ECXA];
		}
	}
	kend_t = 0;
	dtemp = Escutrrt[Ke-1-ECSTY][67-ECXA];
	for(k=Ke-1; k>=Ks+1; k--){
		if(Escutrrt[k-1-ECSTY][67-ECXA]-dtemp>1.0E-13){
			kend_t = k;
			break;
		} else {
			dtemp = Escutrrt[k-1-ECSTY][67-ECXA];
		}
	}
	
	fprintf(ofp, "½ªÎ»Ç¯ÅÙ¡§,¸üÇ¯,%d,%20.14e,¹ñÇ¯,%d, %20.14e\n\n",
	         kend_h, 1.0-Escutrrh[Ke-ECSTY][67-ECXA], kend_t, 1.0-Escutrrt[Ke-ECSTY][67-ECXA]);
	
	fprintf(ofp, "·ÐºÑÁ°ÄóÅù\n");
	fprintf(ofp, "Ç¯ÅÙ,Êª²Á,ÄÂ¶â,±¿ÍÑÍø²ó¤ê,ÈæÎã²þÄêÎ¨,ÈæÎã´ûºÛ68ºÐ,´ðÁÃ²þÄêÎ¨,´ðÁÃ´ûºÛ68ºÐ,");
	fprintf(ofp, "¥â¥Ç¥ëÇ¯¶â³Û,¤¦¤ÁÈæÎã,¤¦¤Á´ðÁÃ,²Ä½èÊ¬½êÆÀ,");
	fprintf(ofp, "½êÆÀÂåÂØÎ¨,¤¦¤ÁÈæÎã,¤¦¤Á´ðÁÃ,¡Ê»²¹Í¡Ë½êÆÀÂåÂØÎ¨(°ì¸µ²½Á°),");
	fprintf(ofp, "ÈæÎã¥«¥Ã¥È67,ÈæÎã¥«¥Ã¥È68,´ðÁÃ¥«¥Ã¥È67,´ðÁÃ¥«¥Ã¥È68,m¥Õ¥¡¥¤¥ë,");
	fprintf(ofp, "¥â¥Ç¥ëÇ¯¶â³Û¡ÊÊª²Á³ä¤êÌá¤·¡Ë,¤¦¤ÁÈæÎã¡ÊÊª²Á³ä¤êÌá¤·¡Ë,¤¦¤Á´ðÁÃ¡ÊÊª²Á³ä¤êÌá¤·¡Ë,²Ä½èÊ¬½êÆÀ¡ÊÊª²Á³ä¤êÌá¤·¡Ë\n");
	
	k_model = 24;
	
	r1 = r1h = r1k = r2 = r2h = r2k =0.;
	for(k=5; k<=Ke; k++){
		fprintf(ofp, "%3d, %5.2f, %5.2f, %5.2f, ", k, Ci[k-ECSTY]*100.0, H[k-ECSTY]*100.0, Ri[k-ECSTY]*100.0);
		fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, ",
		    (Krb[k-ECSTY][67-ECXA]-1.0)*100.0,(Krb[k-ECSTY][68-ECXA]-1.0)*100.0,
		    (Kra[k-ECSTY][67-ECXA]-1.0)*100.0,(Kra[k-ECSTY][68-ECXA]-1.0)*100.0);
		if(k>=k_model){
			r1h = Mhirei[k-STTY][0]*Escutrrh[k-ECSTY][67-ECXA];
			r1k = Mkiso[k-STTY]    *Escutrrt[k-ECSTY][67-ECXA];
			r2h = Mhirei[k-STTY][1]*Escutrrh[k-ECSTY][67-ECXA];
			r2k = Mkiso[k-STTY]    *Escutrrt[k-ECSTY][67-ECXA];
		}
		if(k==k_model){
			r1h = nround(r1h, 0);
			r2h = nround(r2h, 0);
			r1k = nround(r1k, 0);
			r2k = nround(r2k, 0);
		}
		r1 = r1h + r1k;
		r2 = r2h + r2k;
		if(k>=k_model){
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, ", r1, r1h, r1k, Kw[k-STTY][0]);
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, ",
			  r1/Kw[k-STTY][0]*100., r1h/Kw[k-STTY][0]*100., r1k/Kw[k-STTY][0]*100., r2/Kw[k-STTY][1]*100.);
		}else {
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, ", 0., 0., 0., 0.);
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, ", 0., 0., 0., 0.);
		}
		fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, %20.14e,",
		    Escutrrh[k-ECSTY][67-ECXA], Escutrrh[k-ECSTY][68-ECXA],
		    Escutrrt[k-ECSTY][67-ECXA], Escutrrt[k-ECSTY][68-ECXA],
		    Scutrk1[k-ECSTY]);
		if(k>=k_model){
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e,\n",
			  r1/Id_Cid[k-ECSTY], r1h/Id_Cid[k-ECSTY], r1k/Id_Cid[k-ECSTY], Kw[k-STTY][0]/Id_Cid[k-ECSTY]);
		} else {
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e,\n", 0., 0., 0., 0.);
		}
	}
	fprintf(ofp, "\n");
	
	fprintf(ofp, "\n,Á´¸üÇ¯,,,,,µì¸üÇ¯,,,,,¹ñ¶¦,,,,,ÃÏ¶¦,,,,,»ä³Ø,,,,,\n");
	fprintf(ofp, "Ç¯ÅÙ,");
	for(ii=0; ii<=4; ii++) fprintf(ofp, "ÈïÊÝ¸±¼Ô,Ï·ÎðÁêÅö,ÄÌÏ·ÁêÅö,¾ã³²,°äÂ²,");
	fprintf(ofp, "\n");
	for(k=FLKS; k<=FLKE; k++){
		fprintf(ofp, "%3d,", k);
		Ap[0][0][k-STTY] = Ap[1][0][k-STTY];
		for(ii=2; ii<=4; ii++) Ap[0][0][k-STTY] += Ap[ii][0][k-STTY]; 
		for(ii=0; ii<=4; ii++){
			fprintf(ofp, "%20.14e, %20.14e, %20.14e, %20.14e, %20.14e,", Ap[ii][0][k-STTY],
			  Ukyu[0][ii][0][k-STTY],Ukyu[0][ii][1][k-STTY],
			  Ukyu[0][ii][2][k-STTY],Ukyu[0][ii][3][k-STTY]);
		}
		fprintf(ofp, "\n");
	}
	fprintf(ofp, "\n");
	
	
	fprintf(ofp, "¼ý»Ù[Á´¸üÇ¯£±:tou]\n\n");
	fprintf(ofp, "Ç¯ÅÙ,");
	fprintf(ofp, "¼ýÆþ·×, ÊÝ¸±ÎÁ, ±¿ÍÑ¼ýÆþ, ¹ñ¸ËÉéÃ´, ¤¦¤Á´ðÁÃ, ¤¦¤Á·Ð²áÅª¹ñ¸Ë, »Ù±çÆþ, Ç¼ÉÕ¶â,");
	fprintf(ofp, "»Ù½Ð·×,ÆÈ¼«µëÉÕ,´ðÁÃÇ¯¶âµò½Ð¶â,Ê¡»ã,»Ù±ç½Ð,¼ý»Ùº¹,");
	fprintf(ofp, "ÀÑÎ©¶â, ¸½ºß²ÁÃÍ, ÁíÊó½·, ÁíÊó½·(°é»ùÅù½ü¤¯), ÊÝ¸±ÎÁÎ¨,ºÊÀÑ¤ß,½»ÂðÍ»»ñ¡ÊÊÌ·Ç¡Ë,,");
	fprintf(ofp, "Ï·ÎðÁêÅö,ÄÌÏ·ÁêÅö,¾ã³²,°äÂ²\n");
	for(k=FLKS; k<=FLKE; k++){
		fprintf(ofp, "%3d,", k);
		for(i=0; i<=30; i++){
			if(i==2 || i==7 || i==8 || (i>=13 && i<=15) || i==22 || (i>=25 && i!=27 && i!=30)){
				continue;
			}
			if(i==6){
				dtemp = Cc[0][6][k-STTY] + Cc[0][7][k-STTY] + Cc[0][8][k-STTY];
			} else {
				dtemp = Cc[0][i][k-STTY];
			}
			if(i!=27) dtemp /= 1.0E+8;
			else      dtemp *= 100.;
			fprintf(ofp, "%20.14e,", dtemp);
		}
		fprintf(ofp, "%20.14e,,", Jyutaku[k-STTY]/1.0E+8);
		for(i=0; i<=3; i++){
			fprintf(ofp, "%20.14e,", 0.);
		}
		fprintf(ofp, "\n");
	}
	fprintf(ofp, "\n\n");
	
	for(k=FLKS; k<=Kyoskijun; k++){
		for(i=0; i<=30; i++){
			if(k!=Kyoskijun || (i!=20 && i!=21)){
				Cc[0][i][k-STTY] = 0.;
			}
			if(k==Kyoskijun) Dc[0][i]  =0.;
			if(i!=0 && i!=3 && i!=19 && i!=20 && i!=21 && (i<=25 || i==30)){
				for(ii=1; ii<=4; ii++){
					Cc[0][i][k-STTY] += Cc[ii][i][k-STTY];
					if(k==Kyoskijun) Dc[0][i] += Dc[ii][i];
				}
			}
		}
	}
	Jisout[0] = 0.;
	for(ii=2; ii<=4; ii++) Jisout[0] += Jisout[ii];
	
	for(ii=0; ii<=4; ii++){
		fprintf(ofp, "\n");
		if(ii==0) fprintf(ofp, "¼ý»Ù[Á´¸üÇ¯£²:¼ý»ÙÍÑ]\n\n");
		if(ii==1) fprintf(ofp, "¼ý»Ù[µì¸üÇ¯]\n\n");
		if(ii==2) fprintf(ofp, "¼ý»Ù[¹ñ¶¦ºÑ]\n\n");
		if(ii==3) fprintf(ofp, "¼ý»Ù[ÃÏ¶¦ºÑ]\n\n");
		if(ii==4) fprintf(ofp, "¼ý»Ù[»ä³Ø¶¦ºÑ]\n\n");
		fprintf(ofp, "Ç¯ÅÙ,");
		fprintf(ofp, "¼ýÆþ·×, ÊÝ¸±ÎÁ, ±¿ÍÑ¼ýÆþ, ¹ñ¸ËÉéÃ´, ¤¦¤Á´ðÁÃ, ¤¦¤Á·Ð²áÅª¹ñ¸Ë, »Ù±çÆþ, Ç¼ÉÕ¶â,");
		fprintf(ofp, "»Ù½Ð·×,ÆÈ¼«µëÉÕ,´ðÁÃÇ¯¶âµò½Ð¶â,Ê¡»ã,»Ù±ç½Ð,¼ý»Ùº¹,");
		fprintf(ofp, "ÀÑÎ©¶â, ¸½ºß²ÁÃÍ, ÁíÊó½·, ÁíÊó½·(°é»ùÅù½ü¤¯), ÊÝ¸±ÎÁÎ¨,ºÊÀÑ¤ß,½»ÂðÍ»»ñ¡ÊÊÌ·Ç¡Ë,,");
		fprintf(ofp, "Ï·ÎðÁêÅö,ÄÌÏ·ÁêÅö,¾ã³²,°äÂ²\n");
		for(k=FLKS; k<=FLKE; k++){
			fprintf(ofp, "%3d,", k);
			for(i=0; i<=30; i++){
				if(i==2 || i==7 || i==8 || (i>=13 && i<=15) || i==22 || (i>=25 && i!=27 && i!=30)){
					continue;
				}
				if(i==6){
					dtemp = Cc[ii][6][k-STTY] + Cc[ii][7][k-STTY] + Cc[ii][8][k-STTY];
				} else {
					dtemp = Cc[ii][i][k-STTY];
				}
				if(i!=27) dtemp /= 1.0E+8;
				else      dtemp *= 100.;
				fprintf(ofp, "%20.14e,", dtemp);
			}
			if(ii<=1){
				fprintf(ofp, "%20.14e,,", Jyutaku[k-STTY]/1.0E+8);
			} else {
				fprintf(ofp, "%20.14e,,", 0.);
			}
			for(i=0; i<=3; i++){
				fprintf(ofp, "%20.14e,", Ukyu[1][ii][i][k-STTY]);
			}
			fprintf(ofp, "\n");
		}
		fprintf(ofp, "\n\n");
	}
}

void shus_Tokutyoout(void){
	
	int k, x;
	FILE *ofp;
	
	ofp = ofp_Tokutyo;
	
	for(k=5; k<=Ke; k++){
		fprintf(ofp, "%d,", k);
		for(x=67; x<=XB; x++){
			 fprintf(ofp, "%.15f,", Tokutyo[k-ECSTY][x-ECXA]);
		}
		fprintf(ofp, "\n");
	}
	

}



