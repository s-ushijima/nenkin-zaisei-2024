#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
namespace sst = sepsstd;

void seps::sepsd(void) {
  try {
    seps::fopn();
    cout << "fopn 終了" << "\n";

    seps::flck();
    cout << "flck 終了" << "\n";

        seps::waku();
        cout << "waku 終了" << "\n";
    
    seps::econ();
    cout << "econ 終了" << "\n";
    
      seps::seid();
      cout << "seid 終了" << "\n";
      
      seps::krgn();
      cout << "krgn 終了" << "\n";
      

      cout << "種別についてのループを実行します（s: 0 -> 3）" << "\n";
      #ifdef DEBUG
      cout << "[debug] 計算の進捗については PROG.log に出力しています。" << "\n";
      #endif 

      FILE *fp = fp_map["prog"];

      GLOBAL_FOR(s, 1, 3) {
        if(pseid != 0 && s >= 3) break;

        if(s <= 3) s2 = s;
        
        #ifdef DEBUG
        fprintf(fp, "[kiso] pseid = %d, s = %d\n", pseid, s);
        #endif
        seps::kiso();

        k = KIJUN;

        if(pseid == 0) {
          xend = 90;
        } else {
          xend = 75;
        }
        tend = xend - 15;

        if(s <= 3) {
          #ifdef DEBUG
          fprintf(fp, "[dtst] pseid = %d, s = %d, k = %d\n", pseid, s, k);
          #endif
          seps::dtst();
        }


        #ifdef DEBUG
        fprintf(fp, "[shke] pseid = %d, s = %d, k = %d\n", pseid, s, k);
        #endif
        seps::shke();

        cout << sst::format("(pseid, s) = (%d, %d) 推計中\n", pseid, s);

        GLOBAL_FOR(k, KIJUN + 1, KE) {
          #ifdef DEBUG
          fprintf(fp, "[siml] pseid = %d, s = %d, k = %d\n", pseid, s, k);
          #endif
          seps::siml();

          #ifdef DEBUG
          fprintf(fp, "[shke] pseid = %d, s = %d, k = %d\n", pseid, s, k);
          #endif
          seps::shke();
        }
      }

        if(key == 11 || key == 12 || key == 13) {
          seps::outkn();
          cout << "outkn 終了" << "\n";
        }

        
        if(flg_toukei == 0){
	        seps::rousaki();
	        cout << "rousaki 終了" << "\n";
	    }

        if(key == 11 || key == 13) {
          seps::pstat();
          cout << "pstat 終了" << "\n";
        }
      
      seps::stat();
      cout << "stat 終了" << "\n";
    


      seps::crshfl();
      cout << "crshfl 終了" << "\n";
    

    if(key == 11) {
      seps::outhou();
      cout << "outhou 終了" << "\n";
    }

    fcls();
    cout << "fcls 終了" << "\n";
  }
  
  catch (const std::exception &ex) {
    clog << ex.what() << "\n";
    clog << "推計中に例外が発生したので開いているファイルを閉じます。\n";
    fcls();
    throw; 
  }
  catch (...) {
    clog << "推計中に例外が発生したので開いているファイルを閉じます。\n";
    fcls();
    throw; 
  }
}
