#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "glva.h"


void set_filenum(void);


void cntl(void){
	
	if(1){
		printf("\n試算の種類を指定してください。\n");
		printf("０:通常試算\n");
		printf("１:過去分試算\n");
		printf("２:受給者分試算\n");
		scanf("%d%*c",&Saimu);
	} else {
		Saimu = 0;
		printf("\n 試算の種類を「0:通常試算」に設定しました。Saimu=%d\n", Saimu);
	}
	if(Saimu<0 || Saimu>2){
		printf(" 試算の種類の設定が不適切です Saimu=%d\n", Saimu);
		exit(1);
	}
	
	if(Saimu!=0){  
		printf("基準年度を入力して下さい（２桁）\n");
		printf("  25:2025年度〜\n");
		scanf("%d%*c",&Psly);
		
		printf("障害、遺族の扱いを指定してください\n");
		printf("  2:すべて将来分として扱う\n");
		scanf("%d%*c",&Pslsi);
		
		printf("加給、振替加算等の扱いを指定してください\n");
		printf("  1:すべて将来分として扱う\n");
		scanf("%d%*c",&Pslsi2);
		
		Seitaikey = 0;
		
		printf("死亡率改善を指定してください\n");
		printf("  1:将来生命表の死亡率改善分だけ改善する方法（平行移動方式）\n");
		scanf("%d%*c",&Kzn);
		
		if(Kzn != 1){
			printf(" 想定していない設定値ですKzn=%d\n", Kzn);
			exit(1);
		}
	} else {
		Psly = Pslsi = Pslsi2 = Seitaikey = 0;
		Kzn = Kzny = 0;
	}
	
	
	if(Saimu!=1 && Saimu!=2){
		printf("\n給付水準の決定方法を選択してください\n");
		printf("  8 : 国年先決め均衡計算（有限均衡）  ＜通常計算＞ \n");
		printf("  9 : カット率ファイル指定 \n");		
		scanf("%d%*c",&Fpset);
	} else {  
		Fpset = 9;
	}
	
	if(Fpset==8 || Fpset==9){
	} else {
		printf(" 現在対応していない試算モードです。\n");
		exit(1);
	}
	
	if(1){
		printf("\n被用者保険の更なる適用拡大を行いますか？\n");
		printf("０：行わない（通常試算、2020年改正反映後）\n");
		printf("１：行う（オプション90万人ベース、企業規模要件撤廃＋非適用業種撤廃）\n");
		printf("２：行う（オプション200万人ベース、１．＋賃金要件撤廃または最賃引上げ）\n");
		printf("３：行う（オプション270万人ベース、２．＋５人未満個人も適用）\n");
		printf("４：行う（オプション860万人ベース、週10時間以上の全ての被用者）\n");
		printf("５：行う（現行制度で最低賃金が上昇した場合の効果）\n");
		scanf("%d%*c",&Flg_Part);
		if(Flg_Part<0 || Flg_Part>5){
			printf("パートフラグ設定エラー Flg_Part=%d\n", Flg_Part);
			exit(1);
		} 
	} else {
		Flg_Part = 0;
	}
	
	Part_Yr1 = 22;
	Part_Yr2 = 24;
	if(Flg_Part >= 1){
		Part_Yr3 = 27;
	}else{
		Part_Yr3 = 0;
	
	}
	
	Cbm_Pt1 = 12. * 5./6.;
    if(1){
        printf("使用するwakuk-mファイルの読み込み先を変更しますか？\n");
        printf("０:しない（通常試算）\n");
        printf("１:する（オプション、45年化）\n");
        scanf("%d%*c",&Flg_Sigo);
    } else {
        Flg_Sigo = 0;
    }

    if(Flg_Sigo == 1){
        printf("使用するwaku-mファイルの外枠番号を入力してください（４桁） \n");
        scanf("%s%*c", Wcfile2);
    }
        
	if(1){
		printf("\n標準報酬上限の見直しを行いますか？\n");
		printf("０：行わない（通常試算）\n");
		printf("１：行う（オプション、上限75万円）\n");
		printf("２：行う（オプション、上限83万円）\n");
		printf("３：行う（オプション、上限98万円）\n");
		scanf("%d%*c", &Flg_Houjou);
		if(Flg_Houjou<0 || 3<Flg_Houjou){
			printf(" 設定値が間違っています Flg_Houjou\n");
			exit(1);
		}
	} else {
		Flg_Houjou = 0;
	}
	
	if(Flg_Houjou >= 1){
	   	Houjou_Yr = 27;
		if(Flg_Houjou == 1){
			Houjou_R1 = 1.016;
			Houjou_R2 = 1.005;
		}else if(Flg_Houjou == 2){
			Houjou_R1 = 1.024;
			Houjou_R2 = 1.008;
		}else if(Flg_Houjou == 3){
			Houjou_R1 = 1.036;
			Houjou_R2 = 1.011;
		}
	} else {
		Houjou_Yr = 0;
		Houjou_R1 = 1.0;
		Houjou_R2 = 1.0;
	}
	
	
	if(1){
		printf("\n厚年勘定に国年勘定を足しこんでカット率を作成しますか？\n");
		printf("０：行わない（通常試算）\n");
		printf("１：行う（オプション準備)\n");
		scanf("%d%*c", &Touitu);
		if(Touitu<0 || Touitu>1){
			printf(" 設定値が間違っています Touitu\n");
			exit(1);
		}
	} else {
		Touitu = 0;
	}
	
	if(Touitu >= 1){
		printf("\n国年・厚年別収支見通し作成用の予備番号を入力して下さい（３桁）\n");
		scanf("%s%*c", Cutrfile5);
	}
	
	
	if(1){
		printf("\nキャリーオーバーの廃止を行いますか？\n");
		printf("０:行わない（通常試算）\n");
		printf("１:行う（参考試算）\n");
		scanf("%d%*c", &Flg_Kmakuro);
		if(Flg_Kmakuro < 0 || Flg_Kmakuro>1){
			printf(" キャリーオーバーの設定が間違っていますFlg_Kmakuro=%d\n", Flg_Kmakuro);
			exit(1);
		} 
	} else {
		Flg_Kmakuro = 0;
	}
	Kmakuro_Yr = 18;
	
	if(Flg_Kmakuro == 1){
		Kmakuro_Yr2 = 25;
	}else{
		Kmakuro_Yr2 = 0;
	}
	
	if(1){
		printf("\n名目下限の撤廃を行いますか？\n");
		printf("０：行わない（通常試算）\n");
		printf("１：行う（参考試算）\n");
		scanf("%d%*c", &Flg_Dmakuro);
		if(Flg_Dmakuro < 0 || Flg_Dmakuro>1){
			printf("  名目下限撤廃の設定が間違っていますFlg_Dmakuro=%d\n", Flg_Dmakuro);
			exit(1);
		} else if(Flg_Dmakuro==1) {
			Dmakuro_Yr = 25;
		} else {
			Dmakuro_Yr = 0;
		}
		
	} else {
		Flg_Dmakuro = 0;
		Dmakuro_Yr = 0;
	}
	
	
	zan_jimu = 0;
	
	zan_fund = 0;
	Kijun=22;
	
	kakusa = 2;

	Flg_shunor = 0;
	if(Flg_shunor == 0) Shunor = 0.997;
	
	Flg_nendo = 1;
	if(Flg_nendo == 1) nendohosei = 1.000;
	
    
	Flg_matsu = 0;
	Ca = 1.0;
	
	Nenbeex  = 0;
	Nenbeex2 = 1;
	Kkuci = 0;
	zaichou = 0;
	Sienset = 1;
	Flg_Jimu = 2;	
	Cntlset = 1 ;
	Seidn = 0;	
	Pseid = 0;
	Flg_Kaisho=2;
	Misyu = 0.;
	Tumawake = 0.;
	Kyoskijun = 15;	
}



int ii2usd(int ii){
	int usd;
	
	if(ii<0 || 4<ii){
		printf("ii2usd関数の引数が間違っています ii=%d\n", ii);
		exit(1);
	}
	
	if(Seidn!=0){
		usd=Useid;
	} else {
		if(ii==1){  
			usd=0;
		} else if(ii==2){  
			usd=1;
		} else if(ii==3){  
			usd=4;
		} else if(ii==4){  
			usd=5;
		} else {
			printf("ii2usd関数の引数が間違っています Seidn=%d, ii=%d\n", Seidn, ii);
			exit(1);
		}
	}
	return(usd);
}


int ii2psd(int ii){
	int psd;
	
	if(ii<0 || 4<ii){
		printf("ii2psd関数の引数が間違っています ii=%d\n", ii);
		exit(1);
	}
	
	if(Seidn!=0){
		if(Seidn<=4) psd=Seidn;
		else         psd=1;
	} else {
		if(ii<1 || 4<ii){
			printf("ii2psd関数の引数が間違っています Seidn=%d, ii=%d\n", Seidn, ii);
			exit(1);
		}
		psd=ii;
	}
	
	return(psd);
}



