#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <functional>
#include <string>
#include <vector>
#include <random>

class class01
{
public:
  int value001;
  void input_value001(std::string some_string);
};

class class02
{
private:
  int var001;
  int var002;
  int var003;
  int var004;
  int var005;
  int var006;
  int var007;
  int var008;
  int var009;
  int var010;
  int var011;
  int var012;
  int var013;
  int var014;
  int var015;
  int var016;
  int var017;
  int var018;
  int var019;
  int var020;
  int var021;
  int var022;
  int var023;
  int var024;
  int var025;
  int var026;
  int var027;
  int var028;
  int var029;
  int var030;
  int var031;
  int var032;
  int var033;
  int var034;
  int var035;
  int var036;
  int var037;
  double var038;
  double var039;
  int var040;
  double var041;
  int var042;
  double var043;
  double var044;

public:
  class02() : var001(-1), var002(0), var003(-1), var004(-1), var005(-1), var006(-1), var007(0), var008(-1), var009(0), var010(0), var011(0), var012(0), var013(0), var014(0), var015(0), var016(0), var017(0), var018(0), var019(0), var020(0), var021(0), var022(0), var023(0), var024(0), var025(0), var026(0), var027(0), var028(0), var029(0), var030(0), var031(0), var032(0), var033(0), var034(0), var035(0), var036(0), var037(0), var038(0.0), var039(0.0), var040(0), var041(0.0), var042(0), var043(0.0), var044(0.0) {}
  class02(const class02& some_object02);

  struct compare_var002 : public std::binary_function<class02, class02, bool>
  {
    bool operator()(class02 object02_1, class02 object02_2)
    {
      return (object02_1.var002 < object02_2.var002);
    }
  };

  struct compare_var007 : public std::binary_function<class02, class02, bool>
  {
    bool operator()(class02 object02_1, class02 object02_2)
    {
      return (object02_1.var007 < object02_2.var007);
    }
  };

  struct compare_var037 : public std::binary_function<class02, class02, bool>
  {
    bool operator()(class02 object02_1, class02 object02_2)
    {
      return (object02_1.var037 < object02_2.var037);
    }
  };

  void set_var001(int new_var001) {var001 = new_var001;};
  void set_var002(int new_var002) {var002 = new_var002;};
  void set_var003(int new_var003) {var003 = new_var003;};
  void set_var004(int new_var004) {var004 = new_var004;};
  void set_var005(int new_var005) {var005 = new_var005;};
  void set_var006(int new_var006) {var006 = new_var006;};
  void set_var007(int new_var007) {var007 = new_var007;};
  void set_var008(int new_var008) {var008 = new_var008;};
  void set_var009(int new_var009) {var009 = new_var009;};
  void set_var010(int new_var010) {var010 = new_var010;};
  void set_var011(int new_var011) {var011 = new_var011;};
  void set_var012(int new_var012) {var012 = new_var012;};
  void set_var013(int new_var013) {var013 = new_var013;};
  void set_var014(int new_var014) {var014 = new_var014;};
  void set_var015(int new_var015) {var015 = new_var015;};
  void set_var016(int new_var016) {var016 = new_var016;};
  void set_var017(int new_var017) {var017 = new_var017;};
  void set_var018(int new_var018) {var018 = new_var018;};
  void set_var019(int new_var019) {var019 = new_var019;};
  void set_var020(int new_var020) {var020 = new_var020;};
  void set_var021(int new_var021) {var021 = new_var021;};
  void set_var022(int new_var022) {var022 = new_var022;};
  void set_var023(int new_var023) {var023 = new_var023;};
  void set_var024(int new_var024) {var024 = new_var024;};
  void set_var025(int new_var025) {var025 = new_var025;};
  void set_var026(int new_var026) {var026 = new_var026;};
  void set_var027(int new_var027) {var027 = new_var027;};
  void set_var028(int new_var028) {var028 = new_var028;};
  void set_var029(int new_var029) {var029 = new_var029;};
  void set_var030(int new_var030) {var030 = new_var030;};
  void set_var031(int new_var031) {var031 = new_var031;};
  void set_var032(int new_var032) {var032 = new_var032;};
  void set_var033(int new_var033) {var033 = new_var033;};
  void set_var034(int new_var034) {var034 = new_var034;};
  void set_var035(int new_var035) {var035 = new_var035;};
  void set_var036(int new_var036) {var036 = new_var036;};
  void set_var037(int new_var037) {var037 = new_var037;};
  void set_var038(double new_var038) {var038 = new_var038;}
  void set_var039(double new_var039) {var039 = new_var039;};
  void set_var040(int new_var040) {var040 = new_var040;};
  void set_var041(double new_var041) {var041 = new_var041;};
  void set_var042(int new_var042) {var042 = new_var042;};
  void set_var043(double new_var043) {var043 = new_var043;};
  void set_var044(double new_var044) {var044 = new_var044;};

  int get_var001() const {return var001;};
  int get_var002() const {return var002;};
  int get_var003() const {return var003;};
  int get_var004() const {return var004;};
  int get_var005() const {return var005;};
  int get_var006() const {return var006;};
  int get_var007() const {return var007;};
  int get_var008() const {return var008;};
  int get_var009() const {return var009;};
  int get_var010() const {return var010;};
  int get_var011() const {return var011;};
  int get_var012() const {return var012;};
  int get_var013() const {return var013;};
  int get_var014() const {return var014;};
  int get_var015() const {return var015;};
  int get_var016() const {return var016;};
  int get_var017() const {return var017;};
  int get_var018() const {return var018;};
  int get_var019() const {return var019;};
  int get_var020() const {return var020;};
  int get_var021() const {return var021;};
  int get_var022() const {return var022;};
  int get_var023() const {return var023;};
  int get_var024() const {return var024;};
  int get_var025() const {return var025;};
  int get_var026() const {return var026;};
  int get_var027() const {return var027;};
  int get_var028() const {return var028;};
  int get_var029() const {return var029;};
  int get_var030() const {return var030;};
  int get_var031() const {return var031;};
  int get_var032() const {return var032;};
  int get_var033() const {return var033;};
  int get_var034() const {return var034;};
  int get_var035() const {return var035;};
  int get_var036() const {return var036;};
  int get_var037() const {return var037;};
  double get_var038() const {return var038;};
  double get_var039() const {return var039;};
  int get_var040() const {return var040;};
  double get_var041() const {return var041;};
  int get_var042() const {return var042;};
  double get_var043() const {return var043;};
  double get_var044() const {return var044;};

  void add_var009(int x) {var009 += x;};
  void add_var010(int x) {var010 += x;};
  void add_var011(int x) {var011 += x;};
  void add_var012(int x) {var012 += x;};
  void add_var013(int x) {var013 += x;};
  void add_var014(int x) {var014 += x;};
  void add_var015(int x) {var015 += x;};
  void add_var016(int x) {var016 += x;};
  void add_var017(int x) {var017 += x;};
  void add_var018(int x) {var018 += x;};
  void add_var019(int x) {var019 += x;};
  void add_var020(int x) {var020 += x;};
  void add_var021(int x) {var021 += x;};
  void add_var022(int x) {var022 += x;};
  void add_var023(int x) {var023 += x;};
  void add_var024(int x) {var024 += x;};
  void add_var025(int x) {var025 += x;};
  void add_var026(int x) {var026 += x;};
  void add_var027(int x) {var027 += x;};
  void add_var028(int x) {var028 += x;};
  void add_var029(int x) {var029 += x;};
  void add_var030(int x) {var030 += x;};
  void add_var031(int x) {var031 += x;};
  void add_var032(int x) {var032 += x;};
  void add_var038(double y) {var038 += y;};
  void add_var043(double a, int x, double b, int y, double r)
         {var043 = var043 * r + ( a * ((double)x/12.0) + b * ((double)y/12.0) );};

  bool is_func01() const {return ( var007==31 || var007==32 || var007==33 || var007==34 || var007==40 || var007==50 || var007==60 );};
  bool is_func02() const {return ( var008==31 || var008==32 || var008==33 || var008==34 || var008==40 || var008==50 || var008==60 );};
  bool is_func03() const {return ( var008==99 || var035==1 || var035==2 || var009<240 );};
  bool is_func04() const {return ( var008==99 );};
};

namespace func_orig{
  std::vector<std::string> func03a(std::string, char);
  std::vector<std::vector<std::string>> func03b(std::string, int);
  std::string func04a(int, int);
  std::string func04b(int, int, int, int, int);
  std::string func04c(int, int);
  std::string func04d(int, int);
  std::string func04e(int);
  std::string func04f(int, int);
  std::string func04g(int, int);
  std::string func04h(int, int);
  std::string func04i(void);
  std::string func04j(int);
  std::string func04k(int, int);
  std::string func04m(int, int);
  std::string func04n(int, int, int);
  std::string func04p(int, int, int);
  std::string func04q(int, int, int);
  std::string func04r(int, int, int);
  std::string func04s(int, int, int);
  std::string func04t(int, int, int);
  std::string func04u(int, int, int);
  std::string func04v(int, int, int);
  std::string func04w(int, int, int);
  std::string func04x(int, int, int);
  std::string func04y(int, int, int);
  std::string func04z(int, int, int);
  std::string func04aa(int, int, int);
  void func05a(int, std::vector<std::vector<std::string>> const&, std::vector<class02> &);
  void func06a(int, std::vector<int> const&, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> &, std::vector< std::vector<int>> &, int, int);
  void func06b(int, int, std::vector<int> const&, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
  void func07a(int, int, std::vector<int> const&, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, int, int, int);
  void func07b(int, int, std::vector<int> const&, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, int, int, int);
  void func08a(int, std::vector<int> const&, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, int);
  int func09a(int);
  void func09b(int, std::vector<std::vector<std::string>> const&, std::vector<std::vector<int>> const&, std::vector<int> const&, std::vector<class02> &);
  void func09c(int, std::vector<class02> &, int, int);
  void func10a(std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::vector<std::vector<double>>>> &);
  void func10b(int, std::vector<class02> &, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<double>> const&, int, int, int, int);
  void func10c(int, std::vector<class02> &, int, int, int, std::vector<std::vector<std::vector<std::vector<double>>>> const&, int, double);
  void func10d(int, std::vector<class02> &, int, int, std::vector<std::vector<std::string>> const&);
  void func11a(int, std::vector<class02> &, int, int, int, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, std::vector<std::vector<std::string>> const&, int);
  void func12a(int, std::vector<class02> const&, std::vector<int> &);
  void func12b(int, std::vector<class02> const&, std::vector<int> &);
  void func12c(int, std::vector<class02> const&, std::vector<double> &);
  void func13a(int, int, int, int, std::vector<int> const&);
  void func13b(int, int, int, int, std::vector<int> const&);
  void func13c(int, int, int, int, std::vector<double> const&);
}

#endif
