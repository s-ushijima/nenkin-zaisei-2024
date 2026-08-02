#include "_prototype.h"
#include <iostream>
#include <vector>

void func_orig::func08a(int arg08a1, std::vector<int> const& arg08a2, std::vector<class02> & arg08a3, std::vector<std::vector<std::string>> const& arg08a4, std::vector<std::vector<std::string>> const& arg08a5, std::vector<std::vector<int>> & arg08a6, std::vector<std::vector<int>> & arg08a7, int arg08a8) {
  std::vector<std::vector<std::vector<double>>> vector08a1(arg08a2.size()-2, std::vector<std::vector<double>>(100, std::vector<double>(arg08a2.size(), 0.0)));
  std::vector<std::vector<std::vector<int>>> vector08a2(arg08a2.size()-2, std::vector<std::vector<int>>(100, std::vector<int>(arg08a2.size(), 0)));
  if ( arg08a8>=1 ){
    for ( int j = 0; j < arg08a2.size()-2; ++j ) {
      for ( int m = 0 ; m < 50; ++m ) {
        for ( int k = 0 ; k < arg08a2.size(); ++k ) {
          if ( j < 12 ) {
            if ( k < 12 ){
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+j][k]);
            } else if ( k==12 || k==13 ){
              vector08a1[j][m][k] = 0.0;
            } else {
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+j][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector08a1[j][m][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+(j-2)][k]);
            } else if ( k==12 || k==13 ){
              vector08a1[j][m][k] = 0.0;
            } else {
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+(j-2)][k-2]);
            }
          }
        }
      }
    }
  } else {
    for ( int j = 0; j < arg08a2.size()-2; ++j ) {
      for ( int m = 0 ; m < 50; ++m ) {
        for ( int k = 0 ; k < arg08a2.size(); ++k ) {
          if ( j < 12 ) {
            if ( k < 12 ){
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+j][k]);
            } else if ( k==12 || k==13 ){
              vector08a1[j][m][k] = 0.0;
            } else {
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+j][k-2]);
            }
          } else if ( j==12 || j==13 ){
            vector08a1[j][m][k] = 0.0;
          } else {
            if ( k < 12 ){
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+(j-2)][k]);
            } else if ( k==12 || k==13 ){
              vector08a1[j][m][k] = 0.0;
            } else {
              vector08a1[j][m][k] = std::stod(arg08a5[m*16+(j-2)][k-2]);
            }
          }
        }
      }
    }
  }
  std::vector<std::vector<int>> vector08a3(arg08a2.size()-2, std::vector<int>(100, 0));
  for (int i = 0; i<arg08a1; ++i) {
    if ( arg08a3[i].get_var007() == arg08a2[0] && arg08a3[i].get_var011() < 600 ) {
      ++vector08a3[0][int(arg08a3[i].get_var011()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[1] && arg08a3[i].get_var012() < 600 ) {
      ++vector08a3[1][int(arg08a3[i].get_var012()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[2] && arg08a3[i].get_var013() < 600 ) {
      ++vector08a3[2][int(arg08a3[i].get_var013()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[3] && arg08a3[i].get_var014() < 600 ) {
      ++vector08a3[3][int(arg08a3[i].get_var014()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[4] && arg08a3[i].get_var015() < 600 ) {
      ++vector08a3[4][int(arg08a3[i].get_var015()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[5] && arg08a3[i].get_var016() < 600 ) {
      ++vector08a3[5][int(arg08a3[i].get_var016()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[6] && arg08a3[i].get_var017() < 600 ) {
      ++vector08a3[6][int(arg08a3[i].get_var017()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[7] && arg08a3[i].get_var018() < 600 ) {
      ++vector08a3[7][int(arg08a3[i].get_var018()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[8] && arg08a3[i].get_var019() < 600 ) {
      ++vector08a3[8][int(arg08a3[i].get_var019()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[9] && arg08a3[i].get_var020() < 600 ) {
      ++vector08a3[9][int(arg08a3[i].get_var020()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[10] && ( arg08a3[i].get_var028() - arg08a3[i].get_var029() < 600 ) ) {
      ++vector08a3[10][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[11] && arg08a3[i].get_var029() < 600 ) {
      ++vector08a3[11][int(arg08a3[i].get_var029()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[12] && ( arg08a3[i].get_var028() - arg08a3[i].get_var029() < 600 ) ) {
      ++vector08a3[12][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[13] && arg08a3[i].get_var029() < 600 ) {
      ++vector08a3[13][int(arg08a3[i].get_var029()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[14] && arg08a3[i].get_var030() < 600 ) {
      ++vector08a3[14][int(arg08a3[i].get_var030()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[15] && arg08a3[i].get_var031() < 600 ) {
      ++vector08a3[15][int(arg08a3[i].get_var031()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[16] && arg08a3[i].get_var032() < 600 ) {
      ++vector08a3[16][int(arg08a3[i].get_var032()/12)];
    } else if ( arg08a3[i].get_var007() == arg08a2[17] && arg08a3[i].get_var021() < 600 ) {
      ++vector08a3[17][int(arg08a3[i].get_var021()/12)];
    }
  }
  for( int j = 0; j < arg08a2.size()-2; ++j ) {
    for ( int m = 0; m < 50; ++m ){
      for ( int k = 0 ; k < arg08a2.size(); ++k ) {
        vector08a2[j][m][k] = round( (double)vector08a3[j][m] * (double)vector08a1[j][m][k] );
      }
    }
  }
  for (int i = 0; i<arg08a1; ++i) {
    if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 11 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var011()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var011()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 12 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var012()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var012()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 13 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var013()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var013()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 14 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var014()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var014()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 15 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var015()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var015()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 16 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var016()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var016()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 17 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var017()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var017()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 18 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var018()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var018()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 19 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var019()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var019()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 20 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var020()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var020()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 31 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 32 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var029()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var029()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 33 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int((arg08a3[i].get_var028() - arg08a3[i].get_var029())/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 34 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var029()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var029()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 40 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var030()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var030()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 50 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var031()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var031()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 60 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var032()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var032()/12)][k];
            break;
          }
        }
      }
    } else if ( arg08a3[i].get_var037() != 1 && arg08a3[i].get_var007() == 70 ) {
      for ( int k = 0; k<arg08a2.size()-1; ++k ) {
        if ( vector08a2[ func_orig::func09a(arg08a3[i].get_var007()) ][int(arg08a3[i].get_var021()/12)][k] > 0 ) {
          if ( arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k] < std::stoi(arg08a4[func_orig::func09a(arg08a3[i].get_var007())][k]) ) {
            arg08a3[i].set_var008(arg08a2[k]);
            ++arg08a6[func_orig::func09a(arg08a3[i].get_var007())][k];
            --arg08a7[func_orig::func09a(arg08a3[i].get_var007())][k];
            arg08a3[i].set_var037(1);
            --vector08a2[func_orig::func09a(arg08a3[i].get_var007())][int(arg08a3[i].get_var021()/12)][k];
            break;
          }
        }
      }
    }
  }
}
