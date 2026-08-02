#include "_prototype.h"
#include <iostream>
#include <string>
#include <vector>

void func_orig::func11a(int arg11a1, std::vector<class02> & arg11a2, int arg11a3, int arg11a4, int arg11a5, std::vector<std::vector<std::string>> const& arg11a6, std::vector<std::vector<std::string>> const& arg11a7, std::vector<std::vector<std::string>> const& arg11a8, std::vector<std::vector<std::string>> const& arg11a9, int arg11a10) {
  double var11a1 = 0.0;
  if ( arg11a10 == 0 ){
    var11a1 = 480.0;
  } else {
    if ( arg11a4 >= 51 ){
      var11a1 = 480.0;
    } else if ( arg11a4 == 49 || arg11a4 == 50 ){
      var11a1 = 492.0;
    } else if ( arg11a4 == 47 || arg11a4 == 48 ){
      var11a1 = 504.0;
    } else if ( arg11a4 == 45 || arg11a4 == 46 ){
      var11a1 = 516.0;
    } else if ( arg11a4 == 43 || arg11a4 == 44 ){
      var11a1 = 528.0;
    } else {
      var11a1 = 540.0;
    }
  }
  double var11a2 = 1.0;
  if ( arg11a10 == 1 && arg11a4 <= 50 ){
    if ( arg11a4 == 49 || arg11a4 == 50 ){
      if ( arg11a5 - arg11a4 <= 8 ){
        var11a2 = 41.0 / 40.0;
      } else {
        var11a2 = 1.0;
      }
    } else if ( arg11a4 == 47 || arg11a4 == 48 ){
      if ( arg11a5 - arg11a4 <= 8 ){
        var11a2 = 42.0 / 40.0;
      } else if ( arg11a5  - arg11a4 <= 11 ){
        var11a2 = 42.0 / 41.0;
      } else {
        var11a2 = 1.0;
      }
    } else if ( arg11a4 == 45 || arg11a4 == 46 ){
      if ( arg11a5 - arg11a4 <= 8 ){
        var11a2 = 43.0 / 40.0;
      } else if ( arg11a5  - arg11a4 <= 11 ){
        var11a2 = 43.0 / 41.0;
      } else if ( arg11a5  - arg11a4 <= 14 ){
        var11a2 = 43.0 / 42.0;
      } else {
        var11a2 = 1.0;
      }
    } else if ( arg11a4 == 43 || arg11a4 == 44 ){
      if ( arg11a5 - arg11a4 <= 8 ){
        var11a2 = 44.0 / 40.0;
      } else if ( arg11a5  - arg11a4 <= 11 ){
        var11a2 = 44.0 / 41.0;
      } else if ( arg11a5  - arg11a4 <= 14 ){
        var11a2 = 44.0 / 42.0;
      } else if ( arg11a5  - arg11a4 <= 17 ){
        var11a2 = 44.0 / 43.0;
      } else {
        var11a2 = 1.0;
      }
    } else {
      if ( arg11a5 - arg11a4 <= 8 ){
        var11a2 = 45.0 / 40.0;
      } else if ( arg11a5  - arg11a4 <= 11 ){
        var11a2 = 45.0 / 41.0;
      } else if ( arg11a5  - arg11a4 <= 14 ){
        var11a2 = 45.0 / 42.0;
      } else if ( arg11a5  - arg11a4 <= 17 ){
        var11a2 = 45.0 / 43.0;
      } else if ( arg11a5  - arg11a4 <= 20 ){
        var11a2 = 45.0 / 44.0;
      } else {
        var11a2 = 1.0;
      }
    }
  } else {
    var11a2 = 1.0;
  }
  int var11a3 = 0;
  if (arg11a5<=66) {
    var11a3 = 66;
  } else {
    var11a3 = arg11a5;
  }
  double var11a4 = std::stod(arg11a6[arg11a5 - arg11a4 + 2][arg11a5 + 2]) * var11a2;
  std::vector<double> vector11a1 = {74825.0, 68983.0, 62916.0, 56849.0, 51007.0, 44940.0, 38873.0, 33031.0, 26964.0, 20897.0, 15055.0, 15055.0, 15055.0, 15055.0, 15055.0};
  double var11a5 = 0.0;
  if ( arg11a4 >= 56 && arg11a4 <= 70 ) {
    var11a5 = vector11a1[70 - arg11a4] * std::stod(arg11a6[arg11a5 - arg11a4 + 2][arg11a5 + 2]) * var11a2 / std::stod(arg11a6[1][68]);
  }
  double var11a6 = 0.005481;
  double var11a7 = 1628.0 * std::stod(arg11a6[arg11a5 - arg11a4 + 2][arg11a5 + 2]) * var11a2 / std::stod(arg11a6[1][68]) * 480.0 / var11a1;
  double var11a8 = 200.0;
  double var11a9 = 1.0;
  if (arg11a5==arg11a4-1) {
    var11a9 = 1.0 / ( 1.0 + std::stod(arg11a9[21][6])/100.0 ) / ( 1.0 + std::stod(arg11a9[22][6])/100.0 ) / ( 1.0 + std::stod(arg11a9[23][6])/100.0 );
  } else if (arg11a5==arg11a4) {
    var11a9 = 1.0 / ( 1.0 + std::stod(arg11a9[22][6])/100.0 ) / ( 1.0 + std::stod(arg11a9[23][6])/100.0 );
  } else if (arg11a5==arg11a4+1) {
    var11a9 = 1.0 / ( 1.0 + std::stod(arg11a9[23][6])/100.0 );
  } else if (arg11a5==arg11a4+2) {
    var11a9 = 1.0;
  } else {
    for ( int years=arg11a4+3; years < arg11a5 + 1; ++years){
      var11a9 *= ( 1.0 + std::stod(arg11a9[years - arg11a4 + 21][6])/100.0 );
    }
  }
  int var11a10 = 0;
  int var11a11 = 0;
  if ( arg11a4>=56 && arg11a4<65 && arg11a5==64 ) {
    for ( int p=0; p<arg11a1; ++p ) {
      if ( !arg11a2[p].is_func04() && ( arg11a2[p].get_var022() < 240 ) ) {
        ++var11a10;
      }
    }
    if (arg11a3==1) {
      var11a11 = (int)((double)var11a10 * 0.027);
    } else {
      var11a11 = (int)((double)var11a10 * 0.503);
    }
  }
  for ( int p=0; p<arg11a1; ++p ) {
    if (arg11a4<65 && arg11a5==64 && var11a11>0) {
      if( !arg11a2[p].is_func04() && ( arg11a2[p].get_var022() < 240 ) ) {
        arg11a2[p].set_var036(1);
        --var11a11;
      }
    }
    double var11a12 = 0.0;
    double var11a13 = 0.0;
    double var11a14 = 0.0;
    double var11a15 = 0.0;
    double var11a16 = 0.0;
    double var11a17 = 0.0;
    double var11a18 = 0.0;
    double var11a19 = 0.0;
    double var11a20 = 0.0;
    double var11a21 = 0.0;
    double var11a22 = 0.0;
    double var11a23 = 0.0;
    double var11a24 = 0.0;
    double var11a25 = 0.0;
    double var11a26 = 0.0;
    double var11a27 = 0.0;
    double var11a28 = 0.0;
    double var11a29 = 0.0;
    double var11a30 = 0.0;
    double var11a31 = 0.0;
    double var11a32 = 0.0;
    if ( arg11a2[p].get_var038() > var11a1 ) {
      var11a21 = var11a1;
    } else {
      var11a21 = arg11a2[p].get_var038();
    }
    if ( arg11a2[p].get_var022() > var11a1 ) {
      var11a22 = var11a1;
    } else {
      var11a22 = arg11a2[p].get_var022();
    }
    if ( arg11a2[p].get_var023() > var11a1 ) {
      var11a27 = var11a1;
    } else {
      var11a27 = arg11a2[p].get_var023();
    }
    if ( arg11a2[p].get_var028() > var11a1 ) {
      var11a23 = var11a1;
    } else {
      var11a23 = arg11a2[p].get_var028();
    }
    if ( arg11a2[p].get_var024() > var11a1 ) {
      var11a28 = var11a1;
    } else {
      var11a28 = arg11a2[p].get_var024();
    }
    if ( arg11a2[p].get_var030() > var11a1 ) {
      var11a24 = var11a1;
    } else {
      var11a24 = arg11a2[p].get_var030();
    }
    if ( arg11a2[p].get_var025() > var11a1 ) {
      var11a29 = var11a1;
    } else {
      var11a29 = arg11a2[p].get_var025();
    }
    if ( arg11a2[p].get_var031() > var11a1 ) {
      var11a25 = var11a1;
    } else {
      var11a25 = arg11a2[p].get_var031();
    }
    if ( arg11a2[p].get_var026() > var11a1 ) {
      var11a30 = var11a1;
    } else {
      var11a30 = arg11a2[p].get_var026();
    }
    if ( arg11a2[p].get_var032() > var11a1 ) {
      var11a26 = var11a1;
    } else {
      var11a26 = arg11a2[p].get_var032();
    }
    if ( arg11a2[p].get_var027() > var11a1 ) {
      var11a31 = var11a1;
    } else {
      var11a31 = arg11a2[p].get_var027();
    }
    if ( arg11a2[p].get_var012() > var11a1 ) {
      var11a32 = var11a1;
    } else {
      var11a32 = arg11a2[p].get_var012();
    }
    var11a12 = var11a4 * var11a21 / var11a1 * std::stod(arg11a7[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    if ( arg11a2[p].get_var036()==1 ) {
      var11a13 = var11a5 / var11a9;
    }
    var11a14 = arg11a2[p].get_var043() * var11a6 * std::stod(arg11a8[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    var11a16 = ( var11a7 * var11a23 - var11a4 * var11a28 / var11a1 ) * std::stod(arg11a7[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    if ( var11a16 < 0.0 ) {
      var11a16 = 0.0;
    }
    var11a17 = ( var11a7 * var11a24 - var11a4 * var11a29 / var11a1 ) * std::stod(arg11a7[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    if ( var11a17 < 0.0 ) {
      var11a17 = 0.0;
    }
    var11a18 = ( var11a7 * var11a25 - var11a4 * var11a30 / var11a1 ) * std::stod(arg11a7[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    if ( var11a18 < 0.0 ) {
      var11a18 = 0.0;
    }
    var11a19 = ( var11a7 * var11a26 - var11a4 * var11a31 / var11a1 ) * std::stod(arg11a7[arg11a5 - arg11a4 + 17][var11a3 - 65]) / var11a9;
    if ( var11a19 < 0.0 ) {
      var11a19 = 0.0;
    }
    var11a15 = var11a16 + var11a17 + var11a18 + var11a19;
    var11a20 = var11a8 * var11a32 / var11a9;
    arg11a2[p].set_var044( var11a12 + var11a13 + var11a14 + var11a15 + var11a20 );
  }
}
