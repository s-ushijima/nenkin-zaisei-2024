#include "_prototype.h"
#include <vector>

void func_orig::func12a(int arg12a1, std::vector<class02> const& arg12a2, std::vector<int> & arg12a3) {
  for (int j=0; j<arg12a3.size(); ++j) {
    arg12a3[j] = 0;
  }
  for (int i=0; i<arg12a1; ++i) {
    if ( !arg12a2[i].is_func03() ) {
      if ( ( arg12a2[i].get_var022() >= 240 && arg12a2[i].get_var010() < 240 && arg12a2[i].get_var021() < 240 ) || ( arg12a2[i].get_var022() >= 240 && arg12a2[i].get_var010() >= 240 && arg12a2[i].get_var021() < 240 && arg12a2[i].get_var022() >= arg12a2[i].get_var010() ) || ( arg12a2[i].get_var022() >= 240 && arg12a2[i].get_var010() < 240 && arg12a2[i].get_var021() >= 240 && arg12a2[i].get_var022() >= arg12a2[i].get_var021() ) ) {
        ++arg12a3[0];
      } else if ( ( arg12a2[i].get_var010() >= 240 && arg12a2[i].get_var022() < 240 && arg12a2[i].get_var021() < 240 ) || ( arg12a2[i].get_var010() >= 240 && arg12a2[i].get_var022() >= 240 && arg12a2[i].get_var021() < 240 && arg12a2[i].get_var010() > arg12a2[i].get_var022() ) || ( arg12a2[i].get_var010() >= 240 && arg12a2[i].get_var022() < 240 && arg12a2[i].get_var021() >= 240 && arg12a2[i].get_var010() >= arg12a2[i].get_var021() ) ) {
        ++arg12a3[1];
      } else if ( ( arg12a2[i].get_var021() >= 240 && arg12a2[i].get_var022() < 240 && arg12a2[i].get_var010() < 240 ) || ( arg12a2[i].get_var021() >= 240 && arg12a2[i].get_var022() >= 240 && arg12a2[i].get_var010() < 240 && arg12a2[i].get_var021() > arg12a2[i].get_var022() ) || ( arg12a2[i].get_var021() >= 240 && arg12a2[i].get_var022() < 240 && arg12a2[i].get_var010() >= 240 && arg12a2[i].get_var021() > arg12a2[i].get_var010() ) ) {
        ++arg12a3[2];
      } else if ( arg12a2[i].get_var022() < 240 && arg12a2[i].get_var010() < 240 && arg12a2[i].get_var021() < 240 ) {
        ++arg12a3[3];
      }
    }
  }
}

void func_orig::func12b(int arg12b1, std::vector<class02> const& arg12b2, std::vector<int> & arg12b3) {
  for (int j=0; j<arg12b3.size(); ++j) {
    arg12b3[j] = 0;
  }
  for (int i=0; i<arg12b1; ++i) {
    if ( !arg12b2[i].is_func03() ) {
      if ( arg12b2[i].get_var022() >= 480 ) {
        ++arg12b3[5];
        arg12b3[6]+=arg12b2[i].get_var022();
      } else if ( arg12b2[i].get_var022() >= 360 ) {
        ++arg12b3[4];
        arg12b3[6]+=arg12b2[i].get_var022();
      } else if ( arg12b2[i].get_var022() >= 240 ) {
        ++arg12b3[3];
        arg12b3[6]+=arg12b2[i].get_var022();
      } else if ( arg12b2[i].get_var022() >= 120 ) {
        ++arg12b3[2];
        arg12b3[6]+=arg12b2[i].get_var022();
      } else if ( arg12b2[i].get_var022() >= 12 ) {
        ++arg12b3[1];
        arg12b3[6]+=arg12b2[i].get_var022();
      } else if ( arg12b2[i].get_var022() >= 0 ) {
        ++arg12b3[0];
        arg12b3[6]+=arg12b2[i].get_var022();
      }
    }
  }
}

void func_orig::func12c(int arg12c1, std::vector<class02> const& arg12c2, std::vector<double> & arg12c3) {

  for (int j=0; j<arg12c3.size(); ++j) {
    arg12c3[j] = 0.0;
  }
  long long var12c1 = 0;
  long long var12c2 = 0;
  for (int i=0; i<arg12c1; ++i) {
    if ( !arg12c2[i].is_func03() ) {
      if ( arg12c2[i].get_var044() >= 3000000.0 ) {
        ++arg12c3[6];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() >= 2400000.0 ) {
        ++arg12c3[5];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() >= 1800000.0 ) {
        ++arg12c3[4];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() >= 1200000.0 ) {
        ++arg12c3[3];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() >= 840000.0 ) {
        ++arg12c3[2];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() >= 600000.0 ) {
        ++arg12c3[1];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      } else if ( arg12c2[i].get_var044() > 0.0 ) {
        ++arg12c3[0];
        var12c1+=(long long)(arg12c2[i].get_var044()/12.0);
        ++var12c2;
      }
    }
    if (var12c2!=0){
      arg12c3[7] = (double)(var12c1/var12c2);
    }
  }
}
