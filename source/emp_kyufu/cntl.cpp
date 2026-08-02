#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <cassert>
using namespace std;

static void set_kflcan(void);

void seps::cntl(void) {
    
  if(key == 12 || key == 13) {
    cout << "\n"
      << "基準年度を指定してください" << "\n"
      << "  25: 2025年度〜" << "\n";
    cin >> psly;
  }else {
    psly = 0;
  }
  
  if(key == 12 || key == 13) {
    cout << "基準年度：" << psly + 2000 << "年度" << "\n";
  }
  
  if(key == 12 || key == 13) {
    cout
      << "障害、遺族の扱いを指定してください" << "\n"
      << "  2: すべて将来分として扱う" << "\n";
    cin >> pslsi;
    cout
      << "加給、振替加算等の扱いを指定してください" << "\n"
      << "  1: すべて将来分として扱う" << "\n";
    cin >> pslsi2;
  } else {
    pslsi = 0;
    pslsi2 = 0;
  }
  
  
  
  if(true) {
    cout
      << "将来生命表の設定をして下さい" << "\n"
      << "  4: 新人口2023.4(死亡中位）" << "\n"
      << "  5: 新人口2023.4(死亡高位)" << "\n"
      << "  6: 新人口2023.4(死亡低位)" << "\n";
    cin >> seimei;
    assert(4 <= seimei && seimei <= 6);
  } else {
    seimei = 4;
  }
  
  if(4 <= seimei && seimei <= 6) {
    seiy = 70;
  }
  
	kzn = 1;
  
  if(true) {
    cout 
      << "被用者保険の更なる適用拡大を行いますか？" << "\n"
      << "  0: 行わない(通常試算、2020年改正反映後)" << "\n"
      << "  1: 行う（オプション90万人、企業規模要件撤廃＋５人以上非適用業種廃止）" << "\n"
      << "  2: 行う（オプション200万人、１＋賃金要件撤廃または最賃引上げ）" << "\n"
      << "  3: 行う（オプション270万人、２＋５人未満個人事業所も適用)" << "\n"
      << "  4: 行う（オプション860万人、週10時間以上の全ての被用者)" << "\n"
      << "  5: 行う（現行制度で最低賃金が上昇した場合の効果)" << "\n";
    cin >> flg_part;
  } else {
    flg_part = 0;
  }
  assert(0 <= flg_part && flg_part <= 5);
  
  partyr1 = 16; 
  partyr2 = 22; 
  partyr3 = 24; 
  
  if(flg_part >= 1){
	  partyr4 = 27;
  }else{
  	  partyr4 = KE+2;
  }
 
  if(true) {
    cout
      << "基礎年金の45年化を行いますか？" << "\n"
      << "  0: 行わない（通常試算）" << "\n"
      << "  1: 行う（オプション、45年化）" << "\n";
    cin >> flg_sigo;
  } else {
    flg_sigo = 0;
  }
  assert(0 <= flg_sigo && flg_sigo <= 1);
  
  canyr = 31; 

  set_kflcan();
  
 
  
  if(true) {
    cout
      << "高在老（65歳以上）の廃止を行いますか？" << "\n"
      << "  0: 行わない（通常試算）" << "\n"
      << "  1: 行う(オプション)" << "\n";
    cin >> flg_kozax;
  } else {
    flg_kozax = 0;
  }
  assert(0 <= flg_kozax && flg_kozax <= 1);
  
  if(flg_kozax == 1) {
    kozaxyr = 27;
  } else {
    kozaxyr = KE + 1;
  }
  
  kozax = 65;
  
  if(true) {
    cout 
      << "標報月額の上限の引き上げを行いますか？" << "\n"
      << "  0: 行わない（通常試算）" << "\n"
      << "  1: 行う（オプション、上限75万円）" << "\n"
      << "  2: 行う（オプション、上限83万円）" << "\n"
      << "  3: 行う（オプション、上限98万円）" << "\n";
     cin >> houjou;
  } else {
    houjou = 0;
  }
  
  assert(0 <= houjou && houjou <= 3);
  
  if(houjou >= 1) {
	houjouyr = 27;
	if(houjou == 1){
		houjour1 = 1.016;
		houjour2 = 1.005;
	} else if(houjou == 2){
		houjour1 = 1.024;
		houjour2 = 1.008;
	} else if(houjou == 3){
		houjour1 = 1.036;
		houjour2 = 1.011;
	}
  }
   
  
  if(true) {
    cout 
      << "生存脱退力の経年変化を行いますか" << "\n"
      << "  0: 行う（労働参加進展）" << "\n"
      << "  1: 行う（労働参加漸進）" << "\n"
      << "  2: 行わない（労働参加現状）" << "\n";
     cin >> flg_inout;
  }
  
  flg_hantei = 0;
  flg_okure = 0;
  flg_kurisage = 0;
  flg_tuuroutest = 0;
  flg_hsr = 0;
  hsr_endy = 40;
  hsr_r = 1.3e-2;
  flg_siktuika = 0;
  flg_toukei = 0;
  flg_gtest = 0;
  flg_bzwtest = 0;
  chinsura = 1;
  kaite = 1;
  nenbeex = 0;
  xb = 115;
  xa = 64;
  cht_flg = 1;
  hikrate = 0.95;
  flg_hiho70 = 0;
  hiho70yr = KE + 1;
  flg_kaisho = 2;
  flg_sankyu = 1;
  nenbe65 =0;
}

static void set_kflcan() {
 int k, kx;
 double kmax;
  for(kx = -74; kx <= ENDY; kx++) {
    for(k = STTY; k <= ENDY; k++) {
      kflcan.AT(k, C19(kx)) = 40.0; 
    }
  }
  
  if(flg_sigo >= 1) {
    for(kx = canyr - 60; kx <= ENDY; kx++) {
      for(k = canyr; k <= ENDY; k++) {
        if (k - kx < 0) continue; 

        kmax = 40.0;
        if(flg_sigo >= 1) {
           
           if     (canyr <= k && k <= canyr + 2)  kmax = 41.0;
           else if(k <= canyr + 5)                kmax = 42.0;
           else if(k <= canyr + 8)                kmax = 43.0;
           else if(k <= canyr + 11)               kmax = 44.0;
           else if(canyr + 12 <= k)               kmax = 45.0;
        
           if     (canyr + 0 - 60 <= kx && kx <= canyr + 1 - 60) kflcan.AT(k, C19(kx)) = min(41.0, kmax);
           else if(canyr + 2 - 60 <= kx && kx <= canyr + 3 - 60) kflcan.AT(k, C19(kx)) = min(42.0, kmax);
           else if(canyr + 4 - 60 <= kx && kx <= canyr + 5 - 60) kflcan.AT(k, C19(kx)) = min(43.0, kmax);
           else if(canyr + 6 - 60 <= kx && kx <= canyr + 7 - 60) kflcan.AT(k, C19(kx)) = min(44.0, kmax);
           else if(canyr + 8 - 60 <= kx)                         kflcan.AT(k, C19(kx)) = min(45.0, kmax);
        }
      }
    }
  }
}
