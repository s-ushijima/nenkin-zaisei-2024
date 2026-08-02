#include "sepscommon.h"
#include "sepslib.h"
namespace sst = sepsstd;

static void shke_sigonen(void);
static void shke_e3x(void);

void seps::shke() {

  sst::subc3(t4  ,0,115, 0,15, 0,13);
  sst::subc3(t4k ,0,115, 0,15, 0,13);
  sst::subc4(hn2 ,0,115, 0,15, 0,13, 1,2);
  sst::subc4(hn2k,0,115, 0,15, 0,13, 1,2);
  sst::subc4(t6  ,0,115, 0,15, 0,13, 0,23);
  sst::subc4(t6k ,0,115, 0,15, 0,13, 0,23);


  seps::shkehiho();
 
  
  FOR(i, 1, 13) FOR(xx, 0, 15) {
    if(i >= 5 && xx != 0) continue;
    FOR(x, 0, 114) {
      seps::shkejken(i, x, xx);
    }
  }

  if(flg_sigo == 1) {
    shke_sigonen();
  }

 
  FOR(i, 1, 13) FOR(xx, 0, 15) {
    if(i >= 5 && xx != 0) continue;
    FOR(x, 0, 114) {
      seps::shkejsha(i, x, xx);
    }
  }
 
  FOR(i, 1, 13) FOR(xx, 0, 15) {
    if(i >= 5 && xx != 0) continue;
    FOR(x, 0, 114) {
      seps::shkejuk(i, x, xx);
    }
  }


  if(11 <= key && key <= 13) {
    
    
    seps::shkekiso();
  }
}


static void shke_sigonen(void) {
  FOR(i, 9, 13) {
    if(i != 9 && i != 11) continue;
    
    FOR(j, 2, 23) {
      if(j == 2 || j == 7 || j == 11 || j == 12 || j == 14) {
        FOR(x, 0, 114) {
        	if(j != 12){
	            t6k.AT(x, 0, i, j) *= kflcan.AT(k, C19(max(k-x,-74)))/40.0;
	        }else if(j == 12){
	        	t6k.AT(x, 0, i, j) *= pow(kflcan.AT(k, C19(max(k-x,-74)))/40.0, 2.0);
	        
	        }
        }
      }
    }
  }
}

