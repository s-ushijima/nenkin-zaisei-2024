#define SEPS_GLOBAL       
#include "sepscommon.h"   
#include "sepslib.h"      
#include <iostream>       
#include <cassert>        

using namespace std;      
namespace sst = sepsstd;  

int main(void) {
  
  if (true) {
    cout
      << "試算モード(KEY番号)を設定して下さい" << "\n"
      << "11: 通常試算" << "\n"
      << "12: 過去分試算" << "\n"
      << "13: 受給者分試算" << "\n";
    cin >> key;
  } else {
    key = 11;
  }
  
  cout << "\n";
  cout << "試算番号を設定して下さい(整数：４桁)" << "\n";
  cin >> iname;
  cout << "経済要素ファイル番号を設定して下さい(整数：４桁)" << "\n";
  cin >> iecon;
  cout << "外枠の試算番号を設定して下さい(整数：４桁)" << "\n";
  cin >> iwname;
  assert(iwname >= 1000);

 
      seidver = 1;

  seps::zero_init();

  seps::cntl();


  cout << "各制度についての推計を実行します。" << "\n";
  GLOBAL_FOR(pseid, 0, 5) {
  
    if(pseid == 2 || pseid == 3) continue;

    if(pseid == 0) {
      konen = 1;
    } else {
      konen = 0;
    }

    bool key_condition;
    key_condition =
      key == 11 || key == 12 || key == 13;
    
    
    if(key_condition) {
      
      if(pseid == 0)      cout << "--- 厚生年金の推計を開始します ---" << "\n";
      else if(pseid == 1) cout << "--- 国家公務員共済組合の推計を開始します ---" << "\n";
      else if(pseid == 4) cout << "--- 地方公務員共済組合の推計を開始します ---" << "\n";
      else if(pseid == 5) cout << "--- 私立学校共済組合の推計を開始します ---" << "\n";
      

      seps::zero_sepsd();
      seps::sepsd();
    }
  }
  
  return 0; 
}
