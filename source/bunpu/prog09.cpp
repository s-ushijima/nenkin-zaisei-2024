#include "_prototype.h"
#include <iostream>
#include <string>

int func_orig::func09a(int arg09a1) {
  if (arg09a1 == 11) {
    return 0;
  } else if (arg09a1 == 12) {
    return 1;
  } else if (arg09a1 == 13) {
    return 2;
  } else if (arg09a1 == 14) {
    return 3;
  } else if (arg09a1 == 15) {
    return 4;
  } else if (arg09a1 == 16) {
    return 5;
  } else if (arg09a1 == 17) {
    return 6;
  } else if (arg09a1 == 18) {
    return 7;
  } else if (arg09a1 == 19) {
    return 8;
  } else if (arg09a1 == 20) {
    return 9;
  } else if (arg09a1 == 31) {
    return 10;
  } else if (arg09a1 == 32) {
    return 11;
  } else if (arg09a1 == 33) {
    return 12;
  } else if (arg09a1 == 34) {
    return 13;
  } else if (arg09a1 == 40) {
    return 14;
  } else if (arg09a1 == 50) {
    return 15;
  } else if (arg09a1 == 60) {
    return 16;
  } else if (arg09a1 == 70) {
    return 17;
  } else if (arg09a1 == 80) {
    return 18;
  } else if (arg09a1 == 99) {
    return 19;
  } else {
    return 99;
  }
}

void func_orig::func09b(int arg09b1, std::vector<std::vector<std::string>> const& arg09b2, std::vector<std::vector<int>> const& arg09b3, std::vector<int> const& arg09b4, std::vector<class02> & ag09b5) {
  for ( int p=0; p<arg09b1; ++p) {
    int var09b1 = 0;
    for ( int i=0; ((i<arg09b2.size()) && (var09b1 == 0)); ++i ) {
      for ( int j=0; ((j<arg09b2[i].size()) && (var09b1 == 0)); ++j ) {
        if ( p < arg09b3[i][j] ) {
          ag09b5[p].set_var008(arg09b4[j]);
          var09b1 = 1;
        }
      }
    }
  }
}

void func_orig::func09c(int arg09c1, std::vector<class02> & arg09c2, int arg09c3, int arg09c4) {
  int var09c1 = 60;
  if ( arg09c3 == 0 ){
    var09c1 = 60;
  } else {
    if ( arg09c4 >= 51 ){
      var09c1 = 60;
    } else if ( arg09c4 == 49 || arg09c4 == 50 ){
      var09c1 = 61;
    } else if ( arg09c4 == 47 || arg09c4 == 48 ){
      var09c1 = 62;
    } else if ( arg09c4 == 45 || arg09c4 == 46 ){
      var09c1 = 63;
    } else if ( arg09c4 == 43 || arg09c4 == 44 ){
      var09c1 = 64;
    } else {
      var09c1 = 65;
    }
  }
  for ( int p=0; p<arg09c1; ++p) {
    int var09c2 = 6;
    int var09c3 = 6;
    int var09c4 = 6;
    int var09c5 = 6;
    int var09c6;
    if ( arg09c2[p].get_var006() % 10000 == 101 ) {
      var09c6 = 8;
    } else if ( arg09c2[p].get_var006() % 10000 <= 201 ) {
      var09c6 = 9;
    } else if ( arg09c2[p].get_var006() % 10000 <= 301 ) {
      var09c6 = 10;
    } else if ( arg09c2[p].get_var006() % 10000 <= 401 ) {
      var09c6 = 11;
    } else if ( arg09c2[p].get_var006() % 10000 <= 501 ) {
      var09c6 = 0;
    } else if ( arg09c2[p].get_var006() % 10000 <= 601 ) {
      var09c6 = 1;
    } else if ( arg09c2[p].get_var006() % 10000 <= 701 ) {
      var09c6 = 2;
    } else if ( arg09c2[p].get_var006() % 10000 <= 801 ) {
      var09c6 = 3;
    } else if ( arg09c2[p].get_var006() % 10000 <= 901 ) {
      var09c6 = 4;
    } else if ( arg09c2[p].get_var006() % 10000 <= 1001 ) {
      var09c6 = 5;
    } else if ( arg09c2[p].get_var006() % 10000 <= 1101 ) {
      var09c6 = 6;
    } else if ( arg09c2[p].get_var006() % 10000 <= 1201 ) {
      var09c6 = 7;
    } else if ( arg09c2[p].get_var006() % 10000 <= 1231 ) {
      var09c6 = 8;
    }
    if ( arg09c2[p].get_var005() <= 19 ) {
      if ( arg09c2[p].is_func02() ) {
        var09c2 = 0;
        var09c3 = 12;
        var09c4 = 0;
        var09c5 = 0;
      } else {
        var09c4 = 0;
        var09c5 = 0;
      }
    } else if ( arg09c2[p].get_var005() == 20 ) {
      if ( arg09c2[p].is_func02() ) {
        var09c2 = 0;
        var09c3 = 12;
        var09c4 = 0;
        var09c5 = 12 - var09c6;
      } else {
        var09c2 = var09c6;
        var09c3 = 12 - var09c6;
        var09c4 = 0;
        var09c5 = 12 - var09c6; 
      }
    } else if ( ( arg09c2[p].get_var005() >= 21 && arg09c2[p].get_var005() <= 25 ) && arg09c2[p].is_func02() ) {
      var09c2 = 0;
      var09c3 = 12;
      var09c4 = 0;
      var09c5 = 12;
    } else if ( arg09c2[p].get_var005() == var09c1 ) {
      if ( arg09c2[p].get_var007() == 40 || arg09c2[p].get_var007() == 50 || arg09c2[p].get_var007() == 60 ) {
        var09c2 = 12;
        var09c3 = 0;
        var09c4 = var09c6;
        var09c5 = 0;
      } else {
        if ( arg09c2[p].get_var008() == 11 || arg09c2[p].get_var008() == 12 || arg09c2[p].get_var008() == 20 ){
          var09c2 = var09c6;
          var09c3 = 12 - var09c6;
          var09c4 = var09c6;
          var09c5 = 12 - var09c6;
        } else {
          var09c2 = var09c6;
          var09c3 = 12 - var09c6;
          var09c4 = var09c6;
          var09c5 = 0;
        }
      }
    } else if ( arg09c2[p].get_var005() >= var09c1 + 1 ) {
      if ( arg09c2[p].get_var007() == 40 || arg09c2[p].get_var007() == 50 || arg09c2[p].get_var007() == 60 ) {
        var09c2 = 12;
        var09c3 = 0;
        var09c4 = 0;
        var09c5 = 0;
      } else if ( arg09c2[p].get_var007() == 11 || arg09c2[p].get_var007() == 12 || arg09c2[p].get_var007() == 20 ){
        var09c2 = var09c6;
        var09c3 = 12 - var09c6;
        var09c4 = var09c6;
        var09c5 = 0;
      } else {
        var09c2 = var09c6;
        var09c3 = 12 - var09c6;
        var09c4 = 0;
        var09c5 = 0;
      }
    }
    arg09c2[p].set_var033( var09c2 );
    arg09c2[p].set_var034( var09c3 );
    if (arg09c2[p].get_var007() == 11) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var011( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 12) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var012( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 13) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var013( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 * 1.0/2.0 );
    } else if (arg09c2[p].get_var007() == 14) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var014( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 * 1.0/2.0 );
    } else if (arg09c2[p].get_var007() == 15) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var015( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 * 5.0/8.0 );
    } else if (arg09c2[p].get_var007() == 16) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var016( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 * 6.0/8.0 );
    } else if (arg09c2[p].get_var007() == 17) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var017( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 * 7.0/8.0 );
    } else if (arg09c2[p].get_var007() == 18) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var018( var09c2 );
    } else if (arg09c2[p].get_var007() == 19) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var019( var09c2 );
    } else if (arg09c2[p].get_var007() == 20) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var010( var09c2 );
      arg09c2[p].add_var020( var09c2 );
    } else if ( arg09c2[p].get_var007() == 31 || arg09c2[p].get_var007() == 33 ) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var022( var09c2 );
      arg09c2[p].add_var023( var09c4 );
      arg09c2[p].add_var024( var09c4 );
      arg09c2[p].add_var028( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if ( arg09c2[p].get_var007() == 32 || arg09c2[p].get_var007() == 34 ) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var022( var09c2 );
      arg09c2[p].add_var023( var09c4 );
      arg09c2[p].add_var024( var09c4 );
      arg09c2[p].add_var028( var09c2 );
      arg09c2[p].add_var029( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 40) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var022( var09c2 );
      arg09c2[p].add_var023( var09c4 );
      arg09c2[p].add_var025( var09c4 );
      arg09c2[p].add_var030( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 50) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var022( var09c2 );
      arg09c2[p].add_var023( var09c4 );
      arg09c2[p].add_var026( var09c4 );
      arg09c2[p].add_var031( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 60) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var022( var09c2 );
      arg09c2[p].add_var023( var09c4 );
      arg09c2[p].add_var027( var09c4 );
      arg09c2[p].add_var032( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    } else if (arg09c2[p].get_var007() == 70) {
      arg09c2[p].add_var009( var09c4 );
      arg09c2[p].add_var021( var09c2 );
      arg09c2[p].add_var038( (double)var09c4 );
    }
    if (arg09c2[p].get_var008() == 11) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var011( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if (arg09c2[p].get_var008() == 12) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var012( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if (arg09c2[p].get_var008() == 13) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var013( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 * 1.0/2.0 );
    } else if (arg09c2[p].get_var008() == 14) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var014( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 * 1.0/2.0 );
    } else if (arg09c2[p].get_var008() == 15) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var015( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 * 5.0/8.0 );
    } else if (arg09c2[p].get_var008() == 16) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var016( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 * 6.0/8.0 );
    } else if (arg09c2[p].get_var008() == 17) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var017( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 * 7.0/8.0 );
    } else if (arg09c2[p].get_var008() == 18) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var018( var09c3 );
    } else if (arg09c2[p].get_var008() == 19) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var019( var09c3 );
    } else if (arg09c2[p].get_var008() == 20) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var010( var09c3 );
      arg09c2[p].add_var020( var09c3 );
    } else if ( arg09c2[p].get_var008() == 31 || arg09c2[p].get_var008() == 33 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var022( var09c3 );
      arg09c2[p].add_var023( var09c5 );
      arg09c2[p].add_var024( var09c5 );
      arg09c2[p].add_var028( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if ( arg09c2[p].get_var008() == 32 || arg09c2[p].get_var008() == 34 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var022( var09c3 );
      arg09c2[p].add_var023( var09c5 );
      arg09c2[p].add_var024( var09c5 );
      arg09c2[p].add_var028( var09c3 );
      arg09c2[p].add_var029( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if ( arg09c2[p].get_var008() == 40 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var022( var09c3 );
      arg09c2[p].add_var023( var09c5 );
      arg09c2[p].add_var025( var09c5 );
      arg09c2[p].add_var030( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if ( arg09c2[p].get_var008() == 50 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var022( var09c3 );
      arg09c2[p].add_var023( var09c5 );
      arg09c2[p].add_var026( var09c5 );
      arg09c2[p].add_var031( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if ( arg09c2[p].get_var008() == 60 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var022( var09c3 );
      arg09c2[p].add_var023( var09c5 );
      arg09c2[p].add_var027( var09c5 );
      arg09c2[p].add_var032( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    } else if ( arg09c2[p].get_var008() == 70 ) {
      arg09c2[p].add_var009( var09c5 );
      arg09c2[p].add_var021( var09c3 );
      arg09c2[p].add_var038( (double)var09c5 );
    }
  }
}
