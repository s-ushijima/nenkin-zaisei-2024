#include "_prototype.h"
#include <iostream>
#include <iomanip>
#include <vector>

void func_orig::func07a(int arg07a1, int arg07a2, std::vector<int> const& arg07a3, std::vector<class02> & arg07a4, std::vector<std::vector<std::string>> const& arg07a5, std::vector<std::vector<std::string>> const& arg07a6, std::vector<std::vector<int>> & arg07a7, std::vector<std::vector<int>> & arg07a8, int arg07a9, int arg07a10, int arg07a11) {

  std::vector<std::vector<std::vector<double>>> vector07a1(2, std::vector<std::vector<double>>(arg07a3.size()-1, std::vector<double>(arg07a3.size(), 0.0)));
  std::vector<std::vector<std::vector<int>>> vector07a2(2, std::vector<std::vector<int>>(arg07a3.size()-1, std::vector<int>(arg07a3.size(), 0)));
  if ( arg07a9 >= 1 ){
    for(int j = 0; j < arg07a3.size()-1; ++j) {
      for(int k = 0 ; k < arg07a3.size(); ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 12 ) {
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k-2]);
            }
          } else if ( j==12 ){
            if ( k<10 ){
              vector07a1[m][j][k] = std::stod(arg07a6[10+(arg07a3.size()-3)*m][k]);
            } else if ( k==10 ){
              vector07a1[m][j][k] = 0.0;
            } else if ( k==11 ){
              vector07a1[m][j][k] = std::stod(arg07a6[10+(arg07a3.size()-3)*m][11]);
            } else if ( k==12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[10+(arg07a3.size()-3)*m][10]);
            } else if ( k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[10+(arg07a3.size()-3)*m][k-2]);
            }
          } else if ( j==13 ){
            if ( k<10 ){
              vector07a1[m][j][k] = std::stod(arg07a6[11+(arg07a3.size()-3)*m][k]);
            } else if ( k==10 ){
              vector07a1[m][j][k] = std::stod(arg07a6[11+(arg07a3.size()-3)*m][10]);
            } else if ( k==11 ){
              vector07a1[m][j][k] = 0.0;
            } else if ( k==12 ){
              vector07a1[m][j][k] = 0.0;
            } else if ( k==13 ){
              vector07a1[m][j][k] = std::stod(arg07a6[11+(arg07a3.size()-3)*m][11]);
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[11+(arg07a3.size()-3)*m][k-2]);
            }
          } else {
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  } else if ( arg07a10 == 1 && ( ( ( arg07a11==49 || arg07a11==50 ) && arg07a1==60 ) || ( ( arg07a11==47 || arg07a11==48 ) && arg07a1>=60 && arg07a1<=61 ) || ( ( arg07a11==45 || arg07a11==46 ) && arg07a1>=60 && arg07a1<=62 ) || ( ( arg07a11==43 || arg07a11==44 ) && arg07a1>=60 && arg07a1<=63 ) || ( arg07a11<=42 && arg07a1>=60 && arg07a1<=64 ) ) ){
    for(int j = 0; j < arg07a3.size()-1; ++j) {
      for(int k = 0 ; k < arg07a3.size(); ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 10 || j == 17 ) {
            if ( k == 19 ){
              vector07a1[m][j][k] = std::stod(arg07a6[16+(arg07a3.size()-3)*m][17]);
            } else if ( k == j ){
              vector07a1[m][j][k] = 1.0 - std::stod(arg07a6[16+(arg07a3.size()-3)*m][17]);
            } else {
              vector07a1[m][j][k] = 0.0;
            }
          } else if ( j==10 || j==11 ){
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector07a1[m][j][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  } else {
    for(int j = 0; j < arg07a3.size()-1; ++j) {
      for(int k = 0 ; k < arg07a3.size(); ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 12 ) {
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[j+(arg07a3.size()-3)*m][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector07a1[m][j][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07a1[m][j][k] = 0.0;
            } else {
              vector07a1[m][j][k] = std::stod(arg07a6[(j-2)+(arg07a3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  }
  std::vector<std::vector<int>> vector07a3(2, std::vector<int>(arg07a3.size()-1, 0));
  for (int i = 0; i < arg07a2; ++i) {
    for (int j = 0; j < arg07a3.size()-1; ++j) {
      if ( !(arg07a1 < 59 && arg07a4[i].get_var007() == 80) && arg07a4[i].get_var007() != 90 && arg07a4[i].get_var007() != 99 && arg07a4[i].get_var007() == arg07a3[j] && (arg07a4[i].get_var035() == 1 || arg07a4[i].get_var035() == 2) ) {
        ++vector07a3[0][j];
        break;
      } else if ( !(arg07a1 < 59 && arg07a4[i].get_var007() == 80) && arg07a4[i].get_var007() != 90 && arg07a4[i].get_var007() != 99 && arg07a4[i].get_var007() == arg07a3[j] && arg07a4[i].get_var035() == 3 ) {
        ++vector07a3[1][j];
        break;
      }
    }
  }
  for(int m = 0; m < 2; ++m) {
    for(int j = 0; j < arg07a3.size()-1; ++j) {
      for (int k = 0 ; k < arg07a3.size(); ++k){
        vector07a2[m][j][k] = round( (double)vector07a3[m][j] * (double)vector07a1[m][j][k] );
      }
    }
  }
  for (int i = 0; i<arg07a2; ++i) {
    if ( !(arg07a1 < 59 && arg07a4[i].get_var007() == 80) && arg07a4[i].get_var007() != 90 && arg07a4[i].get_var007() != 99 && arg07a4[i].get_var037() != 1 ) {
      if ( ( arg07a4[i].get_var035() == 1 || arg07a4[i].get_var035() == 2 ) ) {
        for (int k =0; k < arg07a3.size(); ++k){
          if ( vector07a2[0][ func_orig::func09a(arg07a4[i].get_var007()) ][k] > 0 ) {
            if ( arg07a7[func_orig::func09a(arg07a4[i].get_var007())][k] < std::stoi(arg07a5[func_orig::func09a(arg07a4[i].get_var007())][k]) ) {
              arg07a4[i].set_var008(arg07a3[k]);
              ++arg07a7[func_orig::func09a(arg07a4[i].get_var007())][k];
              --arg07a8[func_orig::func09a(arg07a4[i].get_var007())][k];
              arg07a4[i].set_var037(1);
              --vector07a2[0][ func_orig::func09a(arg07a4[i].get_var007()) ][k];
              break;
            }
          }
        }
      } else if ( arg07a4[i].get_var035() == 3 ) {
        for (int k =0; k < arg07a3.size(); ++k){
          if ( vector07a2[1][ func_orig::func09a(arg07a4[i].get_var007()) ][k] > 0 ) {
            if ( arg07a7[func_orig::func09a(arg07a4[i].get_var007())][k] < std::stoi(arg07a5[func_orig::func09a(arg07a4[i].get_var007())][k]) ) {
              arg07a4[i].set_var008(arg07a3[k]);
              ++arg07a7[func_orig::func09a(arg07a4[i].get_var007())][k];
              --arg07a8[func_orig::func09a(arg07a4[i].get_var007())][k];
              arg07a4[i].set_var037(1);
              --vector07a2[1][ func_orig::func09a(arg07a4[i].get_var007()) ][k];
              break;
            }
          }
        }
      }
    }
  }
}

void func_orig::func07b(int arg07b1, int arg07b2, std::vector<int> const& arg07b3, std::vector<class02> & arg07b4, std::vector<std::vector<std::string>> const& arg07b5, std::vector<std::vector<std::string>> const& arg07b6, std::vector<std::vector<std::string>> const& arg07b7, std::vector<std::vector<int>> & arg07b8, std::vector<std::vector<int>> & arg07b9, int arg07b10, int arg07b11, int arg07b12) {
  std::vector<std::vector<std::vector<double>>> vector07b1(2, std::vector<std::vector<double>>(arg07b3.size()-1, std::vector<double>(arg07b3.size()-1, 0.0)));
  std::vector<std::vector<std::vector<int>>> vector07b2(2, std::vector<std::vector<int>>(arg07b3.size()-1, std::vector<int>(arg07b3.size()-1, 0)));
  std::vector<double> vector07b3(arg07b3.size()-1, 0.0);
  std::vector<int> vector07b4(arg07b3.size()-1, 0);
  if ( arg07b10 >= 1 ){
    for(int j = 0; j < arg07b3.size()-1; ++j) {
      for(int k = 0 ; k < arg07b3.size()-1; ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 12 ) {
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k-2]);
            }
          } else if ( j==12 ){
            if ( k<10 ){
              vector07b1[m][j][k] = std::stod(arg07b6[10+(arg07b3.size()-3)*m][k]);
            } else if ( k==10 ){
              vector07b1[m][j][k] = 0.0;
            } else if ( k==11 ){
              vector07b1[m][j][k] = std::stod(arg07b6[10+(arg07b3.size()-3)*m][11]);
            } else if ( k==12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[10+(arg07b3.size()-3)*m][10]);
            } else if ( k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[10+(arg07b3.size()-3)*m][k-2]);
            }
          } else if ( j==13 ){
            if ( k<10 ){
              vector07b1[m][j][k] = std::stod(arg07b6[11+(arg07b3.size()-3)*m][k]);
            } else if ( k==10 ){
              vector07b1[m][j][k] = std::stod(arg07b6[11+(arg07b3.size()-3)*m][10]);
            } else if ( k==11 ){
              vector07b1[m][j][k] = 0.0;
            } else if ( k==12 ){
              vector07b1[m][j][k] = 0.0;
            } else if ( k==13 ){
              vector07b1[m][j][k] = std::stod(arg07b6[11+(arg07b3.size()-3)*m][11]);
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[11+(arg07b3.size()-3)*m][k-2]);
            }
          } else {
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  } else if ( arg07b11 == 1 && ( ( ( arg07b12==49 || arg07b12==50 ) && arg07b1==60 ) || ( ( arg07b12==47 || arg07b12==48 ) && arg07b1>=60 && arg07b1<=61 ) || ( ( arg07b12==45 || arg07b12==46 ) && arg07b1>=60 && arg07b1<=62 ) || ( ( arg07b12==43 || arg07b12==44 ) && arg07b1>=60 && arg07b1<=63 ) || ( arg07b12<=42 && arg07b1>=60 && arg07b1<=64 ) ) ){
    for(int j = 0; j < arg07b3.size()-1; ++j) {
      for(int k = 0 ; k < arg07b3.size()-1; ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 10 || j == 17 ) {
            if ( k == j ){
              vector07b1[m][j][k] = std::stod(arg07b6[16+(arg07b3.size()-3)*m][16]);
            } else {
              vector07b1[m][j][k] = 0.0;
            }
          } else if ( j==10 || j==11 ){
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector07b1[m][j][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  } else {
    for(int j = 0; j < arg07b3.size()-1; ++j) {
      for(int k = 0 ; k < arg07b3.size()-1; ++k) {
        for (int m = 0; m < 2; ++m){
          if ( j < 12 ) {
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[j+(arg07b3.size()-3)*m][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector07b1[m][j][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k]);
            } else if ( k==12 || k==13 ){
              vector07b1[m][j][k] = 0.0;
            } else {
              vector07b1[m][j][k] = std::stod(arg07b6[(j-2)+(arg07b3.size()-3)*m][k-2]);
            }
          }
        }
      }
    }
  }
  for(int k = 0 ; k < arg07b3.size()-1; ++k) {
    if ( k < 12 ){
      vector07b3[k] = std::stod(arg07b7[0][k]);
    } else if ( k==12 || k==13 ){
      vector07b3[k] = 0.0;
    } else {
      vector07b3[k] = std::stod(arg07b7[0][k-2]);
    }
  }
  std::vector<int> vector07b5(arg07b3.size()-1, 0);
  int var07b1 = 0;
  for (int i = 0; i<arg07b2; ++i) {
    for (int j = 0; j < arg07b3.size()-1; ++j) {
      if ( !(arg07b1 < 59 && arg07b4[i].get_var007() == 80) && arg07b4[i].get_var007() != 90 && arg07b4[i].get_var007() != 99 && arg07b4[i].get_var007() == arg07b3[j] && arg07b4[i].get_var035() == 9 ) {
        ++vector07b5[j];
        break;
      }
    }
    if ( (arg07b1 == 19 && arg07b4[i].get_var007() == 90) && arg07b4[i].get_var035() == 9 ) {
      ++var07b1;
    }
  }
  for(int m = 0; m < 2; ++m) {
    for(int j = 0; j < arg07b3.size()-1; ++j) {
      for (int k = 0 ; k < arg07b3.size()-1; ++k){
        vector07b2[m][j][k] = round( (double)vector07b5[j] * (double)vector07b1[m][j][k] );
      }
    }
  }
  for (int k = 0 ; k < arg07b3.size()-1; ++k){
    vector07b4[k] = round( (double)var07b1 * (double)vector07b3[k] );
  }
  for (int i = 0; i<arg07b2; ++i) {
    if ( !(arg07b1 < 59 && arg07b4[i].get_var007() == 80) && arg07b4[i].get_var007() != 90 && arg07b4[i].get_var007() != 99 && arg07b4[i].get_var035() == 9 && arg07b4[i].get_var037() != 1 ) {
      int flag_kiso_hassei = 0;
      for (int k = 0; k < arg07b3.size()-1; ++k) {
        if ( vector07b2[0][ func_orig::func09a(arg07b4[i].get_var007()) ][k] > 0 ) {
          if ( arg07b8[func_orig::func09a(arg07b4[i].get_var007())][k] < std::stoi(arg07b5[func_orig::func09a(arg07b4[i].get_var007())][k]) ) {
            arg07b4[i].set_var035(1);
            arg07b4[i].set_var008(arg07b3[k]);
            ++arg07b8[func_orig::func09a(arg07b4[i].get_var007())][k];
            --arg07b9[func_orig::func09a(arg07b4[i].get_var007())][k];
            arg07b4[i].set_var037(1);
            --vector07b2[0][ func_orig::func09a(arg07b4[i].get_var007()) ][k];
            flag_kiso_hassei = 1;
            break;
          }
        }
      }
      if ( flag_kiso_hassei != 1 ) {
        for (int k = 0; k < arg07b3.size()-1; ++k) {
          if ( vector07b2[1][ func_orig::func09a(arg07b4[i].get_var007()) ][k] > 0 ) {
            if ( arg07b8[func_orig::func09a(arg07b4[i].get_var007())][k] < std::stoi(arg07b5[func_orig::func09a(arg07b4[i].get_var007())][k]) ) {
              arg07b4[i].set_var035(3);
              arg07b4[i].set_var008(arg07b3[k]);
              ++arg07b8[func_orig::func09a(arg07b4[i].get_var007())][k];
              --arg07b9[func_orig::func09a(arg07b4[i].get_var007())][k];
              arg07b4[i].set_var037(1);
              --vector07b2[1][ func_orig::func09a(arg07b4[i].get_var007()) ][k];
              break;
            }
          }
        }
      }
    } else if ( (arg07b1 == 19 && arg07b4[i].get_var007() == 90) && arg07b4[i].get_var035() == 9 && arg07b4[i].get_var037() != 1 ) {
      for (int k = 0; k < arg07b3.size()-1; ++k) {
        if ( vector07b4[k] > 0 ) {
          if ( arg07b8[arg07b8.size()-2][k] < std::stoi(arg07b5[arg07b5.size()-2][k]) ) {
            arg07b4[i].set_var035(1);
            arg07b4[i].set_var008(arg07b3[k]);
            ++arg07b8[arg07b8.size()-2][k];
            --arg07b9[arg07b9.size()-2][k];
            arg07b4[i].set_var037(1);
            --vector07b4[k];
            break;
          }
        }
      }
    }
  }
}
