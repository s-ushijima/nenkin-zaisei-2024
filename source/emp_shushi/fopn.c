#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "set.h"
#include "glva.h"
void alfopen(void){
	int i, is;
	char flname[100];
	char pseid_name[5][4] = {"tou","kou","kok","ren","sig"};
	char useid_name[8][4] = {"kou","kok","jnr","tob","ren","sig","nou","oku"};
	char kaisho_nm[3][2] = {"", "d", "e"};
	char nenbe[2][4] = {"", "-ex"};
	

	sprintf(flname, "%s/emp/data/u-rev/econ/econ-%s.csv", SYSPATH, Ecfile);
	if((ifp_econ=fopen(flname,"r"))==NULL){
		printf("econ-%sファイルのオープンに失敗しました。\n", Ecfile);
		exit(1);
	}
	
	
	if(Saimu==0){
			for(i=1; i<=4; i++){
				sprintf(flname, "%s/emp/rslt/u-rev/shus/shus.%s-%s-%s_%s%s",
				                 SYSPATH, Nfile, Ecfile, Wcfile, pseid_name[i], nenbe[Nenbeex]);
				if((ifp10_usys[i]=fopen(flname,"r"))==NULL){
					printf("U-sysファイルのオープンに失敗しました。(%s)\n", flname);
					exit(1);
				}
			}
	}else if(Saimu==1 || Saimu==2){
			for(i=1; i<=4; i++){
				sprintf(flname, "%s/emp/rslt/u-rev/shus/shus.%s%s-%s-%s_%s",
				                 SYSPATH, Saimushu, Nfile, Ecfile, Wcfile, pseid_name[i]);
				if((ifp10_usys[i]=fopen(flname,"r"))==NULL){
					printf("U-sysファイルのオープンに失敗しました。(%s)\n", flname);
					exit(1);
				}
			}
	}
	
	if(Saimu==0){
		sprintf(flname, "%s/bas/data/KYOSHUTUKIN%s-%s-%s-%s-%s",
		                 SYSPATH, Nfile2, Nkfile, Ecfile, Wcfile, Cutrfile4);
	} else {  
		sprintf(flname, "%s/bas/data/KYOSHUTUKIN%s%s-%s%s-%s-%s-%s",
		                 SYSPATH, Saimuski, Nfile2, Nkfile, Saimuski, Ecfile, Wcfile, Cutrfile4);
	}
	if((ifp_kyos=fopen(flname,"r"))==NULL){
		printf("基礎年金拠出金ファイルのオープンに失敗しました。(%s)\n", flname);
		exit(1);
	}
	
	
	if(Saimu==0){
			sprintf(flname, "%s/bas/rslt/TUMATUMI-%s-%s-%s-%s-%s.csv",
			                 SYSPATH, Nkfile, Ecfile, Wcfile, Cutrfile4, Tumafile);
	} else {  
			sprintf(flname, "%s/bas/rslt/TUMATUMI-%s%s-%s-%s-%s-%s.csv",
			                 SYSPATH, Nkfile, Saimuski, Ecfile, Wcfile, Cutrfile4, Tumafile);
	}
	if((ifp27_tuma=fopen(flname,"r"))==NULL){
			printf("妻積ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
	}
	
	if(Touitu>=1){
			sprintf(flname, "%s/bas/data/provide%s-%s-%s-%s-%s.csv",
		                 SYSPATH, Nfile2, Nkfile, Ecfile, Wcfile, Cutrfile4);
		if((ifp_Touitu=fopen(flname,"r"))==NULL){
			printf("provideのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}

	

	sprintf(flname, "%s/emp/data/ez-arev/nof2024.csv", SYSPATH);

	if((ifp_nofu=fopen(flname,"r"))==NULL){
		printf("納付金ファイルのオープンに失敗しました。(%s)\n", flname);
		exit(1);
	}
	
	
	sprintf(flname, "%s/emp/rslt/u-rev/kaite/kaiteb-%s-%s%s",
		             SYSPATH,Nfile, Ecfile, kaisho_nm[Flg_Kaisho]);
	
	if((ifp_kaiteb=fopen(flname,"r"))==NULL){
		printf("厚年比例の改定率ファイルのオープンに失敗しました。(%s)\n", flname);
		exit(1);
	}
	if(Cutrfile1[0]=='0'){  
		if(Saimu!=6){
			sprintf(flname, "%s/emp/rslt/u-rev/kaite/kaitea-%s-%s%s",
			                 SYSPATH, Nfile,Ecfile, kaisho_nm[Flg_Kaisho]);
		} else {
			sprintf(flname, "%s/emp/rslt/u-rev/kaite/kaitea-%s-%s%s%s",
			                 SYSPATH, Nfile,Saimushu, Ecfile, kaisho_nm[Flg_Kaisho]);
		}
		if((ifp_kaitea=fopen(flname,"r"))==NULL){
			printf("厚年定額の改定率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}else if(Cutrfile1[0]=='1'){  
		if(Flg_Kaisho==2){
			sprintf(flname, "%s/nat/data/KOKUKAITE-%s-%sE.csv", SYSPATH, Nfile,Ecfile);
		}else if(Flg_Kaisho==1){
			sprintf(flname, "%s/nat/data/KOKUKAITE-%s-%sD.csv", SYSPATH, Nfile,Ecfile);
		}else{
			sprintf(flname, "%s/nat/data/KOKUKAITE-%s-%s.csv", SYSPATH, Nfile,Ecfile);
		}
		if((ifp_kokukaite=fopen(flname,"r"))==NULL){
			printf("国年の改定率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}
	
	
	if(Fpset!=9){
		if(Flg_Sigo == 0){
			sprintf(flname, "%s/wakuc/rslt/ver_4_1/rslt%s/waku%s-m.csv",SYSPATH, Wcfile, Wcfile);
		}else if(Flg_Sigo == 1){
			sprintf(flname, "%s/wakuc/rslt/ver_4_1/rslt%s/waku%s-m.csv",SYSPATH, Wcfile2, Wcfile2);
		}
		if((ifp_wakum=fopen(flname,"r"))==NULL){
			printf("毎年のスライド調整率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}
	
	if(Cutrfile1[0]=='1' && Fpset==8){
		sprintf(flname, "%s/bas/rslt/cuta-%s-%s-%s-%s-%s%s%s-%s.csv",
				SYSPATH, Nfile2, Nkfile, Ecfile, Wcfile, Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
		if((ifp_bas_cuta=fopen(flname,"r"))==NULL){
			printf("国年のカット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}else if(Fpset == 9){
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cutb-%s-%s-%s-%s-%s%s%s-%s.csv",
	                     SYSPATH, Nfile3, Nkfile, Ecfile, Wcfile,
	                     Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
		if((ifp_asys_cutb=fopen(flname,"r"))==NULL){
			printf("厚年比例のカット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cuta-%s-%s-%s-%s-%s%s%s-%s.csv",
	                     SYSPATH, Nfile3, Nkfile, Ecfile, Wcfile,
	                     Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
		if((ifp_asys_cuta=fopen(flname,"r"))==NULL){
			printf("厚年定額のカット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}
	
	
	if(Fpset!=9){	
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cuta-%s-%s-%s-%s-%s%s%s-%s.csv",
	                     SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
	                     Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
		if((ofp_cuta=fopen(flname,"w"))==NULL){
			printf("カット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cutb-%s-%s-%s-%s-%s%s%s-%s.csv",
		                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
		                 Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
		if((ofp_cutb=fopen(flname,"w"))==NULL){
			printf("カット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}
	
	if(Touitu>=1){	
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cuta-%s-%s-%s-%s-%s%s%s-%s.csv",
	                     SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
	                     Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile5);
		if((ofp_cuta2=fopen(flname,"w"))==NULL){
			printf("カット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
		sprintf(flname, "%s/emp/rslt/ez_arev/cutr/cutb-%s-%s-%s-%s-%s%s%s-%s.csv",
		                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
		                 Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile5);
		if((ofp_cutb2=fopen(flname,"w"))==NULL){
			printf("カット率ファイルのオープンに失敗しました。(%s)\n", flname);
			exit(1);
		}
	}
	
	
	
	is=0;
	
	if(Saimu==0){  
			for(i=is; i<=4; i++){
				sprintf(flname, "%s/emp/rslt/ez_arev/shushi/01shushi.%s-%s-%s-%s-%s%s%s-%s%s_%02d%s.csv",
				                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
    				             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4,
        				         kaisho_nm[Flg_Kaisho], Fpset, pseid_name[i]);
				if((ofp01_shushi[i]=fopen(flname,"w"))==NULL){
					printf("収支出力用ファイルのオープンに失敗しました。(%s)\n", flname);
					exit(1);
				}
			}
			sprintf(flname, "%s/emp/rslt/ez_arev/shushi/03summary.%s-%s-%s-%s-%s%s%s-%s_%02dsum.csv",
				                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
    				             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4, Fpset);
			if((ofp03_summary=fopen(flname,"w"))==NULL){
					printf("収支サマリファイル03のオープンに失敗しました。(%s)\n", flname);
					exit(1);
			}
		
		if(Nenbeex2==1){
				for(i=is; i<=4; i++){
					sprintf(flname, "%s/emp/rslt/ez_arev/shushi/90nenbe.%s-%s-%s-%s-%s%s%s-%s%s_%02d%s.csv",
					                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
	    				             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4,
	        				         kaisho_nm[Flg_Kaisho], Fpset, pseid_name[i]);
					if((ofp90_nenbe[i]=fopen(flname,"w"))==NULL){
						printf("年齢別収支出力用ファイルのオープンに失敗しました。(%s)\n", flname);
						exit(1);
					}
				}
		}
	}else if(Saimu==1 || Saimu==2){
			for(i=is; i<=4; i++){
				sprintf(flname, "%s/emp/rslt/ez_arev/shushi/01shushi.%s%s-%s-%s-%s-%s%s%s-%s%s_%02d%s.csv",
			         	         SYSPATH, Saimushu, Nfile, Nkfile, Ecfile, Wcfile,
	    			             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4,
	    			             kaisho_nm[Flg_Kaisho], Fpset, pseid_name[i]);
				if((ofp01_shushi[i]=fopen(flname,"w"))==NULL){
					printf("収支出力用ファイルのオープンに失敗しました。(%s)\n", flname);
					exit(1);
				}
			}
			sprintf(flname, "%s/emp/rslt/ez_arev/shushi/03summary.%s%s-%s-%s-%s-%s%s%s-%s_%02dsum.csv",
				                 SYSPATH, Saimushu, Nfile, Nkfile, Ecfile, Wcfile,
	    			             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4, Fpset);
			if((ofp03_summary=fopen(flname,"w"))==NULL){
					printf("収支サマリファイル03のオープンに失敗しました。(%s)\n", flname);
					exit(1);
			}
		
		if(Nenbeex2==1){
				for(i=is; i<=4; i++){
					sprintf(flname, "%s/emp/rslt/ez_arev/shushi/90nenbe.%s%s-%s-%s-%s-%s%s%s-%s%s_%02d%s.csv",
					                 SYSPATH, Saimushu, Nfile, Nkfile, Ecfile, Wcfile,
	    				             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4,
	        				         kaisho_nm[Flg_Kaisho], Fpset, pseid_name[i]);
					if((ofp90_nenbe[i]=fopen(flname,"w"))==NULL){
						printf("年齢別収支出力用ファイルのオープンに失敗しました。(%s)\n", flname);
						exit(1);
					}
				}
		}
	}
	
	sprintf(flname, "%s/emp/rslt/ez_arev/cutr/Tokutyo.%s-%s-%s-%s-%s%s%s_%s.csv",
	                 SYSPATH, Nfile, Nkfile, Ecfile, Wcfile,
	   	             Cutrfile1, Cutrfile2, Cutrfile3, Cutrfile4);
	if((ofp_Tokutyo=fopen(flname,"w"))==NULL){
		printf("特別調整率のオープンに失敗しました。(%s)\n", flname);
		exit(1);
	}
}
