#include "_prototype.h"
#include <iostream>
#include <string>
#include <vector>

void func_orig::func10a(std::vector<std::vector<std::string>> const& arg10a1, std::vector<std::vector<std::string>> const& arg10a2, std::vector<std::vector<std::string>> const& arg10a3, std::vector<std::vector<std::string>> const& arg10a4, std::vector<std::vector<std::string>> const& arg10a5, std::vector<std::vector<std::string>> const& arg10a6, std::vector<std::vector<std::string>> const& arg10a7, std::vector<std::vector<std::string>> const& arg10a8, std::vector<std::vector<std::vector<std::vector<double>>>> & arg10a9) {
  for(int i=0; i<arg10a9[0].size(); ++i){
    for(int j=0; j<arg10a9[0][i].size(); ++j){
      for(int k=0; k<arg10a9[0][i][j].size(); ++k){
        double var10a1 = 0.0;
        double var10a2 = 0.0;
        for(int t=0; t<71; ++t){
          var10a1 += std::stod(arg10a1[3*55*i+55*j+k][t+4]) * std::stod(arg10a5[3*55*i+55*j+k][t+4]);
          var10a2 += std::stod(arg10a5[3*55*i+55*j+k][t+4]);
          if (j==0) {
            var10a1 += std::stod(arg10a1[3*55*i+55*2+k][t+4]) * std::stod(arg10a5[3*55*i+55*2+k][t+4]);
            var10a2 += std::stod(arg10a5[3*55*i+55*2+k][t+4]);
          }
        }
        if (var10a2>0){
          arg10a9[0][i][j][k] = var10a1/var10a2;
        }
      }
    }
  }
  for(int i=0; i<arg10a9[1].size(); ++i){
    for(int j=0; j<arg10a9[1][i].size(); ++j){
      for(int k=0; k<arg10a9[1][i][j].size(); ++k){
        double var10a3 = 0.0;
        double var10a4 = 0.0;
        for(int t=0; t<71; ++t){
          var10a3 += std::stod(arg10a2[3*55*i+55*j+k][t+4]) * std::stod(arg10a6[3*55*i+55*j+k][t+4]);
          var10a4 += std::stod(arg10a6[3*55*i+55*j+k][t+4]);
        }
        if (var10a4>0){
          arg10a9[1][i][j][k] = var10a3/var10a4;
        }
      }
    }
  }
  for(int i=0; i<arg10a9[2].size(); ++i){
    for(int j=0; j<arg10a9[2][i].size(); ++j){
      for(int k=0; k<arg10a9[2][i][j].size(); ++k){
        double var10a5 = 0.0;
        double var10a6 = 0.0;
        for(int t=0; t<71; ++t){
          var10a5 += std::stod(arg10a3[3*55*i+55*j+k][t+4]) * std::stod(arg10a7[3*55*i+55*j+k][t+4]);
          var10a6 += std::stod(arg10a7[3*55*i+55*j+k][t+4]);
        }
        if (var10a6>0){
          arg10a9[2][i][j][k] = var10a5/var10a6;
        }
      }
    }
  }
  for(int i=0; i<arg10a9[3].size(); ++i){
    for(int j=0; j<arg10a9[3][i].size(); ++j){
      for(int k=0; k<arg10a9[3][i][j].size(); ++k){
        double var10a7 = 0.0;
        double var10a8 = 0.0;
        for(int t=0; t<71; ++t){
          var10a7 += std::stod(arg10a4[3*55*i+55*j+k][t+4]) * std::stod(arg10a8[3*55*i+55*j+k][t+4]);
          var10a8 += std::stod(arg10a8[3*55*i+55*j+k][t+4]);
        }
        if (var10a8>0){
          arg10a9[3][i][j][k] = var10a7/var10a8;
        }
      }
    }
  }
}

void func_orig::func10b(int arg10b1, std::vector<class02> & arg10b2, std::vector<std::vector<std::string>> const& arg10b3, std::vector<std::vector<std::string>> const& arg10b4, std::vector<std::vector<double>> const& arg10b5, int arg10b6, int arg10b7, int arg10b8, int arg10b9) {
  std::vector<std::vector<std::vector<double>>> vector10b1(7, std::vector<std::vector<double>>(53, std::vector<double>(53, 0.0)));
  std::vector<std::vector<std::vector<int>>> vector10b2(7, std::vector<std::vector<int>>(53, std::vector<int>(53, 0)));
  std::vector<std::vector<double>> vector10b3(7, std::vector<double>(53, 0.0));
  std::vector<std::vector<int>> vector10b4(7, std::vector<int>(53, 0));
  for(int i=0; i<vector10b1.size(); ++i){
    if ( i==3 ){
      vector10b1[i][0][0] = 1.0;
    }
    for(int j=1; j<vector10b1[i].size(); ++j){
      for(int k=1; k<vector10b1[i][j].size(); ++k){
        if ( i==0 || i==2 ){
          vector10b1[i][j][k] = std::stod(arg10b3[0*52+(j-1)][k-1]);
        } else if ( i==1 ){
          vector10b1[i][j][k] = std::stod(arg10b3[1*52+(j-1)][k-1]);
        } else if ( i==3 ){
          vector10b1[i][j][k] = 0.0;
        } else {
          vector10b1[i][j][k] = std::stod(arg10b3[(i-2)*52+(j-1)][k-1]);
        }
      }
    }
  }
  for(int i=0; i<vector10b3.size(); ++i){
    if ( i==3 ){
      vector10b3[i][0] = 1.0;
    }
    for(int j=1; j<vector10b3[i].size(); ++j){
      if ( i==0 || i==2 ){
        vector10b3[i][j] = std::stod(arg10b4[0][j-1]);
      } else if ( i==1 ){
        vector10b3[i][j] = std::stod(arg10b4[1][j-1]);
      } else if ( i==3 ){
        vector10b3[i][j] = 0.0;
      } else {
        vector10b3[i][j] = std::stod(arg10b4[i-2][j-1]);
      }
    }
  }
  std::vector<std::vector<int>> vector10b5(7, std::vector<int>(53, 0));
  std::vector<int> vector10b6(7, 0);
  for ( int p=0; p<arg10b1; ++p ) {
    if ( arg10b2[p].get_var008()==31 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[0][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[0];
      }
    } else if ( arg10b2[p].get_var008()==32 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[1][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[1];
      }
    } else if ( arg10b2[p].get_var008()==33 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[2][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[2];
      }
    } else if ( arg10b2[p].get_var008()==34 ){
      if ( arg10b2[p].is_func01() ) {
        ++vector10b5[3][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[3];
      }
    } else if ( arg10b2[p].get_var008()==40 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[4][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[4];
      }
    } else if ( arg10b2[p].get_var008()==50 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[5][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[5];
      }
    } else if ( arg10b2[p].get_var008()==60 ){
      if ( arg10b2[p].is_func01() && arg10b2[p].get_var007()!=34 ) {
        ++vector10b5[6][arg10b2[p].get_var040()-1];
      } else {
        ++vector10b6[6];
      }
    }
  }
  for(int i=0; i<vector10b2.size(); ++i){
    for(int j=0; j<vector10b2[i].size(); ++j){
      for(int k=0; k<vector10b2[i][j].size(); ++k){
        vector10b2[i][j][k] = round((double)vector10b5[i][j] * vector10b1[i][j][k]);
      }
    }
  }
  for(int i=0; i<vector10b2.size(); ++i){
    for(int j=0; j<vector10b2[i].size(); ++j){
      int var10b1 = 0;
      for(int k=0; k<vector10b2[i][j].size(); ++k){
        var10b1+=vector10b2[i][j][k];
      }
      if ( vector10b5[i][j] > var10b1 ){
        int var10b2 = vector10b5[i][j] - var10b1;
        for(int k=0; k<vector10b2[i][j].size(); ++k){
          if ( vector10b1[i][j][k]>0 && var10b2>0 ) {
            ++vector10b2[i][j][k];
            --var10b2;
          }
        }
        if ( var10b2>0 ) {
          vector10b2[i][j][0]+=var10b2;
        }
      } else if ( vector10b5[i][j] < var10b1 ){
        int var10b3 = var10b1 - vector10b5[i][j];
        for(int k=0; k<vector10b2[i][j].size(); ++k){
          if ( vector10b2[i][j][k]>0 && var10b3>0 ) {
            --vector10b2[i][j][k];
            --var10b3;
          }
        }
      }
    }
  }
  for(int i=0; i<vector10b4.size(); ++i){
    for(int j=0; j<vector10b4[i].size(); ++j){
      if ( !( ( arg10b6 == 2 || arg10b6 == 3 || arg10b6 == 4 ) && ( arg10b7 + 2022 - arg10b8 == 2027 ) && ( i==1 ) ) ){
        vector10b4[i][j] = round((double)vector10b6[i] * vector10b3[i][j]);
      } else {
        int var10b4 = 0;
        var10b4 = vector10b6[i] - arg10b9;
        if ( var10b4 < 0 ){
          var10b4 = 0;
        }
        if ( j==1 ){
          vector10b4[i][j] = round((double)var10b4 * vector10b3[i][j] + (double)arg10b9);
        } else {
          vector10b4[i][j] = round((double)var10b4 * vector10b3[i][j]);
        }
      }
    }
  }
  for(int i=0; i<vector10b4.size(); ++i){
    int var10b5 = 0;
    for(int j=0; j<vector10b4[i].size(); ++j){
      var10b5+=vector10b4[i][j];
    }
    if ( vector10b6[i] > var10b5 ){
      int var10b6 = vector10b6[i] - var10b5;
      for(int j=0; j<vector10b4[i].size(); ++j){
        if ( vector10b3[i][j]>0 && var10b6>0 ) {
          ++vector10b4[i][j];
          --var10b6;
        }
      }
      if ( var10b6>0 ) {
        vector10b4[i][0]+=var10b6;
      }
    } else if ( vector10b6[i] < var10b5 ){
      int var10b7 = var10b5 - vector10b6[i];
      for(int j=0; j<vector10b4[i].size(); ++j){
        if ( vector10b4[i][j]>0 && var10b7>0 ) {
          --vector10b4[i][j];
          --var10b7;
        }
      }
    }
  }
  double var10b8 = 0.9;
  for ( int p=0; p<arg10b1; ++p) {
    if ( arg10b2[p].is_func02() ) {
      if ( arg10b2[p].is_func01() ) {
        if ( arg10b2[p].get_var008()==31 && arg10b2[p].get_var007()!=34 && vector10b5[0][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[0][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[0][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 0][k]);
              --vector10b2[0][arg10b2[p].get_var040()-1][k];
              --vector10b5[0][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==31 && arg10b2[p].get_var007()==34 && vector10b6[0]>0 ){
          for(int j=0; j<vector10b4[0].size(); ++j){
            if ( vector10b4[0][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 0][j]);
              --vector10b4[0][j];
              --vector10b6[0];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==32 && arg10b2[p].get_var007()!=34 && vector10b5[1][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[1][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[1][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 1][k]);
              --vector10b2[1][arg10b2[p].get_var040()-1][k];
              --vector10b5[1][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==32 && arg10b2[p].get_var007()==34 && vector10b6[1]>0 ){
          if ( ( arg10b6 == 2 || arg10b6 == 3 || arg10b6 == 4 ) && ( arg10b7 + 2022 - arg10b8 == 2027 ) && ( arg10b9 > 0 ) && ( vector10b4[1][1]>0 ) ){
            arg10b2[p].set_var042(2);
            arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 1][1]);
            --vector10b4[1][1];
            --vector10b6[1];
            --arg10b9;
            continue;
          }
          for(int j=0; j<vector10b4[1].size(); ++j){
            if ( vector10b4[1][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 1][j]);
              --vector10b4[1][j];
              --vector10b6[1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==33 && arg10b2[p].get_var007()!=34 && vector10b5[2][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[2][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[2][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041( arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 2][k] * var10b8 );
              --vector10b2[2][arg10b2[p].get_var040()-1][k];
              --vector10b5[2][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==33 && arg10b2[p].get_var007()==34 && vector10b6[2]>0 ){
          for(int j=0; j<vector10b4[2].size(); ++j){
            if ( vector10b4[2][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041( arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 2][j] * var10b8 );
              --vector10b4[2][j];
              --vector10b6[2];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==34 && vector10b5[3][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[3][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[3][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 3][k]);
              --vector10b2[3][arg10b2[p].get_var040()-1][k];
              --vector10b5[3][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==40 && arg10b2[p].get_var007()!=34 && vector10b5[4][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[4][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[4][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 4][k]);
              --vector10b2[4][arg10b2[p].get_var040()-1][k];
              --vector10b5[4][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==40 && arg10b2[p].get_var007()==34 && vector10b6[4]>0 ){
          for(int j=0; j<vector10b4[4].size(); ++j){
            if ( vector10b4[4][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 4][j]);
              --vector10b4[4][j];
              --vector10b6[4];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==50 && arg10b2[p].get_var007()!=34 && vector10b5[5][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[5][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[5][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 5][k]);
              --vector10b2[5][arg10b2[p].get_var040()-1][k];
              --vector10b5[5][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==50 && arg10b2[p].get_var007()==34 && vector10b6[5]>0 ){
          for(int j=0; j<vector10b4[5].size(); ++j){
            if ( vector10b4[5][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 5][j]);
              --vector10b4[5][j];
              --vector10b6[5];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==60 && arg10b2[p].get_var007()!=34 && vector10b5[6][arg10b2[p].get_var040()-1]>0 ){
          for(int k=0; k<vector10b2[6][arg10b2[p].get_var040()-1].size(); ++k){
            if ( vector10b2[6][arg10b2[p].get_var040()-1][k]>0 ) {
              arg10b2[p].set_var042(k+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 6][k]);
              --vector10b2[6][arg10b2[p].get_var040()-1][k];
              --vector10b5[6][arg10b2[p].get_var040()-1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==60 && arg10b2[p].get_var007()==34 && vector10b6[6]>0 ){
          for(int j=0; j<vector10b4[6].size(); ++j){
            if ( vector10b4[6][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 6][j]);
              --vector10b4[6][j];
              --vector10b6[6];
              break;
            }
          }
        }
      } else {
        if ( arg10b2[p].get_var008()==31 && vector10b6[0]>0 ){
          for(int j=0; j<vector10b4[0].size(); ++j){
            if ( vector10b4[0][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 0][j]);
              --vector10b4[0][j];
              --vector10b6[0];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==32 && vector10b6[1]>0 ){
          if ( ( arg10b6 == 2 || arg10b6 == 3 || arg10b6 == 4 ) && ( arg10b7 + 2022 - arg10b8 == 2027 ) && ( arg10b9 > 0 ) && ( vector10b4[1][1]>0 ) ){
            arg10b2[p].set_var042(2);
            arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 1][1]);
            --vector10b4[1][1];
            --vector10b6[1];
            --arg10b9;
            continue;
          }
          for(int j=0; j<vector10b4[1].size(); ++j){
            if ( vector10b4[1][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 1][j]);
              --vector10b4[1][j];
              --vector10b6[1];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==33 && vector10b6[2]>0 ){
          for(int j=0; j<vector10b4[2].size(); ++j){
            if ( vector10b4[2][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041( arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 2][j] * var10b8 );
              --vector10b4[2][j];
              --vector10b6[2];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==34 && vector10b6[3]>0 ){
          for(int j=0; j<vector10b4[3].size(); ++j){
            if ( vector10b4[3][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 3][j]);
              --vector10b4[3][j];
              --vector10b6[3];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==40 && vector10b6[4]>0 ){
          for(int j=0; j<vector10b4[4].size(); ++j){
            if ( vector10b4[4][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 4][j]);
              --vector10b4[4][j];
              --vector10b6[4];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==50 && vector10b6[5]>0 ){
          for(int j=0; j<vector10b4[5].size(); ++j){
            if ( vector10b4[5][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 5][j]);
              --vector10b4[5][j];
              --vector10b6[5];
              break;
            }
          }
        } else if ( arg10b2[p].get_var008()==60 && vector10b6[6]>0 ){
          for(int j=0; j<vector10b4[6].size(); ++j){
            if ( vector10b4[6][j]>0 ) {
              arg10b2[p].set_var042(j+1);
              arg10b2[p].set_var041(arg10b5[(arg10b2[p].get_var004()-1)*275 + (arg10b2[p].get_var005()-16)*5 + 6][j]);
              --vector10b4[6][j];
              --vector10b6[6];
              break;
            }
          }
        }
      }
    } else {
      arg10b2[p].set_var042(0);
      arg10b2[p].set_var041(0.0);
    }
  }
}

void func_orig::func10c(int arg10c1, std::vector<class02> & arg10c2, int arg10c3, int arg10c4, int arg10c5, std::vector<std::vector<std::vector<std::vector<double>>>> const& arg10c6, int arg10c7, double arg10c8) {
  std::vector<std::vector<long long>> vector10c1(2, std::vector<long long>(4, 0));
  std::vector<double> vector10c2(4, 0.0);
  std::vector<double> vector10c3(4, 1.0);
  for ( int p=0; p<arg10c1; ++p ) {
    if ( ( arg10c2[p].get_var008()==31 || arg10c2[p].get_var008()==32 || arg10c2[p].get_var008()==33 || arg10c2[p].get_var008()==34 ) && !arg10c2[p].is_func04() ) {
      vector10c1[0][0] += (long long)arg10c2[p].get_var041();
      ++vector10c1[1][0];
    } else if ( arg10c2[p].get_var008()==40 && !arg10c2[p].is_func04() ) {
      vector10c1[0][1] += (long long)arg10c2[p].get_var041();
      ++vector10c1[1][1];
    } else if ( arg10c2[p].get_var008()==50 && !arg10c2[p].is_func04() ) {
      vector10c1[0][2] += (long long)arg10c2[p].get_var041();
      ++vector10c1[1][2];
    } else if ( arg10c2[p].get_var008()==60 && !arg10c2[p].is_func04() ) {
      vector10c1[0][3] += (long long)arg10c2[p].get_var041();
      ++vector10c1[1][3];
    }
  }
  for ( int i=0; i<vector10c2.size(); ++i ) {
    if (vector10c1[1][i]!=0) {
      vector10c2[i] = (double)(vector10c1[0][i]/vector10c1[1][i]);
    }
  }
  for ( int i=0; i<vector10c3.size(); ++i ) {
    if (vector10c2[i]>0.0 && arg10c5<69){
      vector10c3[i] = (double)(arg10c6[i][2021 - arg10c4 + arg10c5 + 1 - 2021][arg10c3 - 1][arg10c5 + 1 - 15]/vector10c2[i]);
    }
  }
  for ( int p=0; p<arg10c1; ++p ) {
    if ( arg10c2[p].get_var008()==31 || arg10c2[p].get_var008()==32 || arg10c2[p].get_var008()==33 || arg10c2[p].get_var008()==34 ) {
      double var10c1 = arg10c2[p].get_var041() * vector10c3[0];
      if ( !( arg10c7==4 && ( arg10c5 + 2022 - arg10c4 >= 2027 ) ) && var10c1 > 0 && var10c1 < arg10c8 ){
        var10c1 = arg10c8;
      }
      arg10c2[p].set_var041(var10c1);
    } else if ( arg10c2[p].get_var008()==40 ) {
      double var10c2 = arg10c2[p].get_var041() * vector10c3[1];
      if ( !( arg10c7==4 && ( arg10c5 + 2022 - arg10c4 >= 2027 ) ) && var10c2 > 0 && var10c2 < arg10c8 ){
        var10c2 = arg10c8;
      }
      arg10c2[p].set_var041(var10c2);
    } else if ( arg10c2[p].get_var008()==50 ) {
      double var10c3 = arg10c2[p].get_var041() * vector10c3[2];
      if ( !( arg10c7==4 && ( arg10c5 + 2022 - arg10c4 >= 2027 ) ) && var10c3 > 0 && var10c3 < arg10c8 ){
        var10c3 = arg10c8;
      }
      arg10c2[p].set_var041(var10c3);
    } else if ( arg10c2[p].get_var008()==60 ) {
      double var10c4 = arg10c2[p].get_var041() * vector10c3[3];
      if ( !( arg10c7==4 && ( arg10c5 + 2022 - arg10c4 >= 2027 ) ) && var10c4 > 0 && var10c4 < arg10c8 ){
        var10c4 = arg10c8;
      }
      arg10c2[p].set_var041(var10c4);
    }
  }
}

void func_orig::func10d(int arg10d1, std::vector<class02> & arg10d2, int arg10d3, int arg10d4, std::vector<std::vector<std::string>> const& arg10d5) {
  double var10d1 = 0.936;
  double var10d2 = 1.0;
  if (arg10d4==64) {
    var10d1 = var10d1 / ( std::stod(arg10d5[(arg10d4 - arg10d3)+18][1]) / std::stod(arg10d5[(arg10d4 - arg10d3)+18][2]) ) / ( std::stod(arg10d5[(arg10d4 - arg10d3)+19][1]) / std::stod(arg10d5[(arg10d4 - arg10d3)+19][2]) ) / std::stod(arg10d5[(arg10d4 - arg10d3)+20][2]);
  } else if (arg10d4==65) {
    var10d1 = var10d1 / ( std::stod(arg10d5[(arg10d4 - arg10d3)+18][1]) / std::stod(arg10d5[(arg10d4 - arg10d3)+18][2]) ) / std::stod(arg10d5[(arg10d4 - arg10d3)+20][2]);
  } else if (arg10d4>=66) {
    var10d1 = var10d1 / std::stod(arg10d5[(arg10d4 - arg10d3)+20][2]);
  } else {
    var10d1 = var10d1 / ( std::stod(arg10d5[(arg10d4 - arg10d3)+18][1]) / std::stod(arg10d5[(arg10d4 - arg10d3)+18][2]) ) / ( std::stod(arg10d5[(arg10d4 - arg10d3)+19][1]) / std::stod(arg10d5[(arg10d4 - arg10d3)+19][2]) ) / std::stod(arg10d5[(arg10d4 - arg10d3)+20][1]);
  }
  if (arg10d4 < 67) {
    var10d2 = std::stod(arg10d5[(arg10d4 - arg10d3)+17][1]);
  } else {
    var10d2 = std::stod(arg10d5[(arg10d4 - arg10d3)+17][arg10d4 - 65]);
  }
  for ( int p=0; p<arg10d1; ++p ) {
    if ( arg10d2[p].is_func02() ) {
      if ( arg10d2[p].is_func01() ) {
        arg10d2[p].add_var043( arg10d2[p].get_var039() * var10d1, arg10d2[p].get_var033(), arg10d2[p].get_var041() * var10d1, arg10d2[p].get_var034(), var10d2 );
      } else {
        arg10d2[p].add_var043( 0.0, 0, arg10d2[p].get_var041() * var10d1, arg10d2[p].get_var034(), var10d2 );
      }
    } else {
      if ( arg10d2[p].is_func01() ) {
        arg10d2[p].add_var043( arg10d2[p].get_var039() * var10d1, arg10d2[p].get_var033(), 0.0, 0, var10d2 );
      } else {
        arg10d2[p].add_var043( 0.0, 0, 0.0, 0, var10d2 );
      }
    }
  }
}
