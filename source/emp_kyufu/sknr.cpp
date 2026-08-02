#include "sepscommon.h"
#include "sepslib.h"
#include "iostream"
namespace sst = sepsstd;

void seps::sknr(const int k, const int x, int &xxr, int &xrb) {

  xxr = 60;

  if(s2 == 1 || konen != 1) {
    if(k - x >= -59) xxr = 61;
    if(k - x >= -57) xxr = 62;
    if(k - x >= -55) xxr = 63;
    if(k - x >= -53) xxr = 64;
    if(k - x >= -51) xxr = 65;
  } else if(s2 == 2) {
    if(k - x <= -61) xxr = 59;
    if(k - x >= -54) xxr = 61;
    if(k - x >= -52) xxr = 62;
    if(k - x >= -50) xxr = 63;
    if(k - x >= -48) xxr = 64;
    if(k - x >= -46) xxr = 65;
  } else {
    if(k - x <= -47) xxr = 59;
    if(k - x <= -49) xxr = 58;
    if(k - x <= -51) xxr = 57;
    if(k - x <= -53) xxr = 56;
    if(k - x <= -55) xxr = 55;
    if(k - x >= -42) xxr = 61;
    if(k - x >= -40) xxr = 62;
    if(k - x >= -38) xxr = 63;
    if(k - x >= -36) xxr = 64;
    if(k - x >= -34) xxr = 65;
  }


  xrb = 60;

  if(s2 == 1 || konen != 1) {
    if(k - x >= -47) xrb = 61;
    if(k - x >= -45) xrb = 62;
    if(k - x >= -43) xrb = 63;
    if(k - x >= -41) xrb = 64;
    if(k - x >= -39) xrb = 65;
  } else if(s2 == 2) {
    if(k - x <= -61) xrb = 59;
    if(k - x >= -42) xrb = 61;
    if(k - x >= -40) xrb = 62;
    if(k - x >= -38) xrb = 63;
    if(k - x >= -36) xrb = 64;
    if(k - x >= -34) xrb = 65;
  } else {
    xrb = xxr;
  }

  if(xrb > xxr || xxr > 65 || xrb > 65 || xrb < 55) {
    std::clog << sst::format(
      "»Ùµë³«»ÏÇ¯Îð¥¨¥é¡¼: "
      "s = %d, k = %d, x = %d, xrb = %d, xxr = %d\n",
      s, k, x, xrb, xxr);
    throw std::logic_error("xrb, xxr");
  }
}