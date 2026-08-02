#include "_prototype.h"
#include <iostream>
#include <vector>

void func_orig::func06a(int arg06a1, std::vector<int> const& arg06a2, std::vector<class02> & arg06a3, std::vector<std::vector<std::string>> const& arg06a4, std::vector<std::vector<int>> & arg06a5, std::vector<std::vector<int>> & arg06a6, int arg06a7, int arg06a8) {
  int var06a1 = 0;
  if ( arg06a7 == 0 ){
    var06a1 = 414;
  } else {
    if ( arg06a8 >= 51 ){
      var06a1 = 414;
    } else if ( arg06a8 == 49 || arg06a8 == 50 ){
      var06a1 = 426;
    } else if ( arg06a8 == 47 || arg06a8 == 48 ){
      var06a1 = 438;
    } else if ( arg06a8 == 45 || arg06a8 == 46 ){
      var06a1 = 450;
    } else if ( arg06a8 == 43 || arg06a8 == 44 ){
      var06a1 = 462;
    } else {
      var06a1 = 474;
    }
  }
  for (int i = 0; i<arg06a1; ++i) {
    if ( arg06a3[i].get_var007() != 80 && arg06a3[i].get_var007() != 90 && arg06a3[i].get_var007() != 99 && arg06a3[i].get_var035() == 9 && arg06a3[i].get_var037() != 1 && arg06a3[i].get_var038() <= var06a1 ) {
      for (int k = 0; k < 10; ++k) {
        if ( k == 0 || k == 1 || k == 9 ) {
          if ( arg06a5[func_orig::func09a(arg06a3[i].get_var007())][k] < std::stoi(arg06a4[func_orig::func09a(arg06a3[i].get_var007())][k]) ) {
            arg06a3[i].set_var008(arg06a2[k]);
            ++arg06a5[func_orig::func09a(arg06a3[i].get_var007())][k];
            --arg06a6[func_orig::func09a(arg06a3[i].get_var007())][k];
            arg06a3[i].set_var037(1);
            break;
          }
        }
      }
    }
  }
}

void func_orig::func06b(int arg06b1, int arg06b2, std::vector<int> const& arg06b3, std::vector<class02> & arg06b4, std::vector<std::vector<std::string>> const& arg06b5, std::vector<std::vector<int>> & arg06b6, std::vector<std::vector<int>> & arg06b7) {
  for (int i = 0; i<arg06b2; ++i) {
    if ( arg06b4[i].get_var007() != 80 && arg06b4[i].get_var007() != 90 && arg06b4[i].get_var007() != 99 && arg06b4[i].get_var035() == 9 && arg06b4[i].get_var037() != 1 && arg06b4[i].get_var038() <= ( 120 - ( 70 - arg06b1 ) * 12 ) ) {
      for (int k = 0; k < 10; ++k) {
        if ( k == 0 || k == 9 ) {
          if ( arg06b6[func_orig::func09a(arg06b4[i].get_var007())][k] < std::stoi(arg06b5[func_orig::func09a(arg06b4[i].get_var007())][k]) ) {
            arg06b4[i].set_var008(arg06b3[k]);
            ++arg06b6[func_orig::func09a(arg06b4[i].get_var007())][k];
            --arg06b7[func_orig::func09a(arg06b4[i].get_var007())][k];
            arg06b4[i].set_var037(1);
            break;
          }
        }
      }
    }
  }
}
