#include "_prototype.h"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

int main(void) {
  class01 object01a, object01b, object01c, object01d, object01e, object01f;
  object01a.input_value001("object01a");
  object01b.input_value001("object01b");
  if ( object01b.value001 >= 1 ){
    if ( ( object01a.value001 / 100 ) % 10 != object01b.value001 ){
      std::exit(1);
    }
  }
  object01c.input_value001("object01c");
  if ( object01b.value001 == 0 ){
    if ( !( ( ( object01a.value001 / 100 ) % 10 == 0 && object01c.value001 == 0 || ( object01a.value001 / 100 ) % 10 == 5 && object01c.value001 == 1 ) ) ){
      std::exit(1);
    }
  } else {
    if ( object01c.value001 == 1 ){
      std::exit(1);
    }
  }
  object01d.input_value001("object01d");
  object01e.input_value001("object01e");
  object01f.input_value001("object01f");
  time_t time1, time2;
  time1 = time(NULL);
  std::vector<int> vector001 = {11,12,13,14,15,16,17,18,19,20,31,32,33,34,40,50,60,70,80,99};
  std::vector<int> vector002 = {1,2};
  std::vector<int> vector003 = {17,27,37,47,57,62};
  int main_var001 = 65;
  std::vector<std::vector<std::string>> vector004 = func_orig::func03b(func_orig::func04t(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector005 = func_orig::func03b(func_orig::func04u(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector006 = func_orig::func03b(func_orig::func04v(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector007 = func_orig::func03b(func_orig::func04w(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector008 = func_orig::func03b(func_orig::func04x(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector009 = func_orig::func03b(func_orig::func04y(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector010 = func_orig::func03b(func_orig::func04z(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::string>> vector011 = func_orig::func03b(func_orig::func04aa(object01a.value001, object01d.value001, object01e.value001),1);
  std::vector<std::vector<std::vector<std::vector<double>>>> vector012(4, std::vector<std::vector<std::vector<double>>>(105, std::vector<std::vector<double>>(2, std::vector<double>(55, 0.0))));
  func_orig::func10a(vector004, vector005, vector006, vector007, vector008, vector009, vector010, vector011, vector012);
  std::vector<std::vector<std::string>> vector013 = func_orig::func03b(func_orig::func04j(object01e.value001), 0);
  std::vector<std::vector<std::string>> vector014 = func_orig::func03b(func_orig::func04k(object01d.value001, object01e.value001), 0);
  std::vector<std::vector<std::string>> vector015 = func_orig::func03b(func_orig::func04m(object01d.value001, object01e.value001), 0);
  std::vector<std::vector<std::string>> vector016 = func_orig::func03b(func_orig::func04n(object01a.value001, object01d.value001, object01e.value001), 250);
  std::vector<std::vector<std::string>> vector017;
  std::vector<std::vector<std::string>> vector018;
  if (object01f.value001==1) {
    vector017 = func_orig::func03b(func_orig::func04p(object01a.value001, object01d.value001, object01e.value001), 0);
    vector018 = func_orig::func03b(func_orig::func04q(object01a.value001, object01d.value001, object01e.value001), 0);
  } else {
    vector017 = func_orig::func03b(func_orig::func04r(object01a.value001, object01d.value001, object01e.value001), 0);
    vector018 = func_orig::func03b(func_orig::func04s(object01a.value001, object01d.value001, object01e.value001), 0);
  }
  for (int loop_var001 : vector002) {
    for (int loop_var002 : vector003) {
      std::vector<int> vector019(4, 0);
      std::vector<int> vector020(7, 0);
      std::vector<double> vector021(8, 0);
      std::vector<std::vector<std::string>> vector022;
      int main_var002;
      std::vector<class02> objects02;
      int main_var003;
      std::vector<int> vector023;
      if ( loop_var002 >= 16 ){
        vector022 = func_orig::func03b(func_orig::func04a(loop_var001, loop_var002), 7);
        main_var002 = vector022.size();
        for (int i = 0; i < main_var002 ; ++i){
          objects02.push_back(class02());
        }
        func_orig::func05a(main_var002, vector022, objects02);
        main_var003 = objects02[0].get_var001();
        for (int i = 0; i < main_var002; ++i){
          if ( objects02[i].get_var001() > main_var003 ) {
            main_var003 = objects02[i].get_var001();
          }
        }
        for (int i = 0; i < main_var002; ++i) {
          vector023.push_back(i);
        }
      }
      std::mt19937 gen_rand(0);
      std::vector<std::vector<std::string>> vector024 = func_orig::func03b(func_orig::func04i(), 0);
      std::vector<std::vector<double>> vector025(vector024.size(), std::vector<double>(vector024[0].size() + 1, 0.0));
      double main_var004 = ( 1.0 + std::stod(vector013[22][3])/100.0 ) * ( 1.0 + std::stod(vector013[22][6])/100.0 );
      for(int i = 0; i < vector025.size(); ++i){
        if ( i<275 ){
          vector025[i][0] = 996000.0 / main_var004;
        } else {
          vector025[i][0] = 924000.0 / main_var004;
        }
        for(int j = 1; j < vector025[i].size(); ++j){
          vector025[i][j] = std::stod(vector024[i][j-1]);
        }
      }
      for (int loop_var003 = loop_var002; loop_var003 < main_var001; ++loop_var003) {
        std::vector<std::vector<std::string>> vector026 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, object01a.value001), 0);
        std::vector<std::vector<std::string>> vector027;
        std::vector<std::vector<std::string>> vector028;
        int main_var005 = 0;
        if ( object01b.value001 == 2 || object01b.value001 == 3 || object01b.value001 == 4 ){
          if ( loop_var003 - loop_var002 == 5 ){
            if ( object01a.value001 % 10 == 1 ){
              vector027 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2111), 0);
              vector028 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2311), 0);
            } else if ( object01a.value001 % 10 == 2 ){
              vector027 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2112), 0);
              vector028 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2312), 0);
            } else if ( object01a.value001 % 10 == 3 ){
              vector027 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2113), 0);
              vector028 = func_orig::func03b(func_orig::func04b(loop_var001, loop_var002, loop_var003 + 2022 - loop_var002, loop_var003 + 1, 2313), 0);
            }
            for ( int i=0; i<vector027.size(); ++i ){
              main_var005 += std::stoi( vector028[i][11] );
              main_var005 -= std::stoi( vector027[i][11] );
            }
            if ( main_var005 < 0 ){
              main_var005 = 0;
            }
          }
        }
        std::vector<std::vector<int>> vector029(vector026.size(), std::vector<int>(vector026[0].size(), 0));
        for ( int i=0; i<vector026.size(); ++i ) {
          for ( int j=0; j<vector026[i].size(); ++j ) {
            vector029[i][j] = std::stoi( vector026[i][j] );
          }
        }
        for ( int j = 0; j < vector026[vector026.size() - 2].size(); ++j) {
          if (std::stoi(vector026[vector026.size() - 2][j]) > 0) {
            for ( int x = main_var002; x < main_var002 + std::stoi(vector026[vector026.size() - 2][j]); ++x) {
              objects02.push_back(class02());
              vector023.push_back(x);
              ++main_var003;
              objects02[x].set_var001(main_var003);
              objects02[x].set_var003(2021 - loop_var002 + loop_var003);
              objects02[x].set_var004(loop_var001);
              objects02[x].set_var005(loop_var003);
              objects02[x].set_var006( (2021 - loop_var002) * 10000 + 1010 );
              objects02[x].set_var008(90);
              objects02[x].set_var035(9);
            }
            main_var002 += std::stoi(vector026[vector026.size() - 2][j]);
          }
        }
        std::shuffle(vector023.begin(), vector023.end(), gen_rand);
        for (int i = 0; i < main_var002; ++i){
          objects02[i].set_var002( vector023[i] );
          int tmp_var003 = objects02[i].get_var003();
          objects02[i].set_var003( ++tmp_var003 );
          int tmp_var005 = objects02[i].get_var005();
          objects02[i].set_var005( ++tmp_var005 );
          int tmp_var007 = objects02[i].get_var008();
          objects02[i].set_var007( tmp_var007 );
          objects02[i].set_var037( 0 );
          double tmp_var039 = objects02[i].get_var041();
          objects02[i].set_var039( tmp_var039 );
          int tmp_var040 = objects02[i].get_var042();
          objects02[i].set_var040( tmp_var040 );
        }
        double main_var006;
        if (loop_var003 == loop_var002){
          main_var006 = 1056000.0;
          func_orig::func10c(main_var002, objects02, loop_var001, loop_var002, loop_var002 - 1, vector012, object01b.value001, main_var006);
          func_orig::func11a(main_var002, objects02, loop_var001, loop_var002, loop_var002 - 1, vector016, vector017, vector018, vector013, object01c.value001);
        }
        stable_sort(objects02.begin(), objects02.end(), class02::compare_var002());
        stable_sort(objects02.begin(), objects02.end(), class02::compare_var007());
        std::vector<std::vector<int>> vector030(vector026.size(), std::vector<int>(vector026[0].size(), 0));
        if ( loop_var003 >= 59 && loop_var003 <= 63 ) {
          func_orig::func06a(main_var002, vector001, objects02, vector026, vector030, vector029, object01c.value001, loop_var002);
        }
        if ( loop_var003 >= 64 && loop_var003 <= 69 ) {
          func_orig::func06b(loop_var003, main_var002, vector001, objects02, vector026, vector030, vector029);
        }
        std::vector<std::vector<std::string>> vector031 = func_orig::func03b(func_orig::func04c(loop_var001, loop_var003), 0);
        std::vector<std::vector<std::string>> vector032 = func_orig::func03b(func_orig::func04d(loop_var001, loop_var003), 0);
        std::vector<std::vector<std::string>> vector033 = func_orig::func03b(func_orig::func04e(loop_var001), 0);
        std::vector<std::vector<std::string>> vector034 = func_orig::func03b(func_orig::func04f(loop_var001, loop_var003), 0);
        func_orig::func07a(loop_var003, main_var002, vector001, objects02, vector026, vector031, vector030, vector029, object01b.value001, object01c.value001, loop_var002);
        func_orig::func07b(loop_var003, main_var002, vector001, objects02, vector026, vector032, vector033, vector030, vector029, object01b.value001, object01c.value001, loop_var002);
        func_orig::func08a(main_var002, vector001, objects02, vector026, vector034, vector030, vector029, object01b.value001);
        std::vector<std::vector<int>> vector035(vector026.size(), std::vector<int>(vector026[0].size(), 0));
        int main_var007 = 0;
        for ( int i=0; i<vector026.size(); ++i ) {
          for ( int j=0; j<vector026[i].size(); ++j ) {
            main_var007 += vector029[i][j];
            vector035[i][j] = main_var007;
          }
        }
        stable_sort(objects02.begin(), objects02.end(), class02::compare_var037());
        func_orig::func09b(main_var007, vector026, vector035, vector001, objects02);
        func_orig::func09c(main_var002, objects02, object01c.value001, loop_var002);
        std::vector<std::vector<std::string>> vector036 = func_orig::func03b(func_orig::func04g(loop_var001, loop_var003), 0);
        std::vector<std::vector<std::string>> vector037 = func_orig::func03b(func_orig::func04h(loop_var001, loop_var003), 0);
        for(int i = 0; i < vector025.size(); ++i){
          for(int j = 0; j < vector025[i].size(); ++j){
            vector025[i][j] = vector025[i][j] * ( 1.0 + std::stod(vector013[loop_var003 - loop_var002 + 21][3])/100.0 ) * ( 1.0 + std::stod(vector013[loop_var003 - loop_var002 + 21][6])/100.0 );
          }
        }
        func_orig::func10b(main_var002, objects02, vector036, vector037, vector025, object01b.value001, loop_var003, loop_var002, main_var005);
        if ( loop_var003 - loop_var002 <= 2 ){
          main_var006 = 1056000.0;
        } else {
          main_var006 = 1056000.0;
          for( int i = 2025; i <= loop_var003 - loop_var002 + 2022; ++i ){
            main_var006 = main_var006 * ( 1.0 + std::stod(vector013[i - 2001][3])/100.0 ) * ( 1.0 + std::stod(vector013[i - 2001][6])/100.0 );
          }
        }
        func_orig::func10c(main_var002, objects02, loop_var001, loop_var002, loop_var003, vector012, object01b.value001, main_var006);
        func_orig::func10d(main_var002, objects02, loop_var002, loop_var003, vector015);
        func_orig::func11a(main_var002, objects02, loop_var001, loop_var002, loop_var003, vector016, vector017, vector018, vector013, object01c.value001);
        if ( loop_var003 == main_var001 - 1){
          func_orig::func12a(main_var002, objects02, vector019);
          func_orig::func12b(main_var002, objects02, vector020);
          func_orig::func12c(main_var002, objects02, vector021);
        }
      }
      func_orig::func13a(loop_var001, loop_var002, object01a.value001, object01f.value001, vector019);
      func_orig::func13b(loop_var001, loop_var002, object01a.value001, object01f.value001, vector020);
      func_orig::func13c(loop_var001, loop_var002, object01a.value001, object01f.value001, vector021);
    }
  }
  time2 = time(NULL);
  printf("time:%ld\n", time2 - time1);
  return 0;
}
