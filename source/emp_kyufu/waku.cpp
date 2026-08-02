#include "sepscommon.h"
#include "sepslib.h"
#include <iostream>
#include <stdio.h>
#include <cmath> 
#include <cassert>

void seps::waku(void) {
  
  cout << "外枠ファイル読み込み開始" << "\n";

  char buf[BUF_SIZE];
  FILE *fp;
  double err;

  fp = fp_map["waku-population"];

  fgets(buf, BUF_SIZE, fp);
  fgets(buf, BUF_SIZE, fp);

  for(s = 0; s <= 2; s++) {
    for(k = WKKS; k <= WKKE; k++) {
      fgets(buf, BUF_SIZE, fp);
      
      if(k < STTY || ENDY < k) continue;

      vector<double> vals = csvio::getnums(buf);

      int ss = (int)vals.at(1);
      int kk = (int)vals.at(2) - 2000;
      assert(s == ss);
      assert(k == kk);

      for(int xx = 15; xx <= 100; xx++){
        pop.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
      }
    }
  }

  fp = fp_map["waku"];

  fgets(buf, BUF_SIZE, fp);
  fgets(buf, BUF_SIZE, fp);

  for(s = 0; s <= 2; s++) {
    for(k = WKKS; k <= WKKE; k++) {
      fgets(buf, BUF_SIZE, fp);
      if(k < STTY || ENDY < k) continue;

      vector<double> vals = csvio::getnums(buf);

      int ss = (int)vals.at(1);
      int kk = (int)vals.at(2) - 2000;
      assert(s == ss);
      assert(k == kk);

      for(int xx = 15; xx <= 100; xx++){
        l.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
      }
    }
  }

  if(pseid == 0) {
    fp = fp_map["waku-s3"];

    fgets(buf, BUF_SIZE, fp);
    fgets(buf, BUF_SIZE, fp);
    
    for(s = 0; s <= 2; s++) {
      for(k = WKKS; k <= WKKE; k++) {
        fgets(buf, BUF_SIZE, fp);
        if(k < STTY || ENDY < k) continue;

        if (s == 0) continue;
        if (s == 2) break;

        vector<double> vals = csvio::getnums(buf);

        int ss = (int)vals.at(1);
        int kk = (int)vals.at(2) - 2000;
        assert(s == ss);
        assert(k == kk);

        for(int xx = 15; xx <= 100; xx++){
          l.AT(kk, ss+2, xx) = vals.at(4 + (xx - 15));
        }
      }
    }
  }

  if(pseid == 0) {
    fp = fp_map["waku-part-all"];

    fgets(buf, BUF_SIZE, fp);
    fgets(buf, BUF_SIZE, fp);

    for(s = 0; s <= 2; s++) {
      for(k = WKKS; k <= WKKE; k++) {
        fgets(buf, BUF_SIZE, fp);
        if(k < STTY || ENDY < k) continue;

        vector<double> vals = csvio::getnums(buf);

        int ss = (int)vals.at(1);
        int kk = (int)vals.at(2) - 2000;
        assert(s == ss);
        assert(k == kk);

        for(int xx = 15; xx <= 100; xx++){
          lpt.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
        }
      }
    }


    fp = fp_map["waku-part202410"];

    fgets(buf, BUF_SIZE, fp);
    fgets(buf, BUF_SIZE, fp);

    for(s = 0; s <= 2; s++) {
      for(k = WKKS; k <= WKKE; k++) {
        fgets(buf, BUF_SIZE, fp);
        if(k < STTY || ENDY < k) continue;

        vector<double> vals = csvio::getnums(buf);

        int ss = (int)vals.at(1);
        int kk = (int)vals.at(2) - 2000;
        assert(s == ss);
        assert(k == kk);

        for(int xx = 15; xx <= 100; xx++){
            lpt1.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
        }
      }
    }
    
    if(flg_part >= 1){
	    fp = fp_map["waku-part30-op"];

	    fgets(buf, BUF_SIZE, fp);
	    fgets(buf, BUF_SIZE, fp);

	    for(s = 0; s <= 2; s++) {
	      for(k = WKKS; k <= WKKE; k++) {
	        fgets(buf, BUF_SIZE, fp);
	        if(k < STTY || ENDY < k) continue;

	        vector<double> vals = csvio::getnums(buf);

	        int ss = (int)vals.at(1);
	        int kk = (int)vals.at(2) - 2000;
	        assert(s == ss);
	        assert(k == kk);

	        for(int xx = 15; xx <= 100; xx++){
	            lpt2.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
	        }
	      }
	    }
	    
	    fp = fp_map["waku-part20-30-op"];

	    fgets(buf, BUF_SIZE, fp);
	    fgets(buf, BUF_SIZE, fp);

	    for(s = 0; s <= 2; s++) {
	      for(k = WKKS; k <= WKKE; k++) {
	        fgets(buf, BUF_SIZE, fp);
	        if(k < STTY || ENDY < k) continue;

	        vector<double> vals = csvio::getnums(buf);

	        int ss = (int)vals.at(1);
	        int kk = (int)vals.at(2) - 2000;
	        assert(s == ss);
	        assert(k == kk);

	        for(int xx = 15; xx <= 100; xx++){
	            lpt3.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
	        }
	      }
	    }
	    
	    if(flg_part == 4){
		    fp = fp_map["waku-part10-20-op"];

		    fgets(buf, BUF_SIZE, fp);
		    fgets(buf, BUF_SIZE, fp);

		    for(s = 0; s <= 2; s++) {
		      for(k = WKKS; k <= WKKE; k++) {
		        fgets(buf, BUF_SIZE, fp);
		        if(k < STTY || ENDY < k) continue;

		        vector<double> vals = csvio::getnums(buf);

		        int ss = (int)vals.at(1);
		        int kk = (int)vals.at(2) - 2000;
		        assert(s == ss);
		        assert(k == kk);

		        for(int xx = 15; xx <= 100; xx++){
		            lpt4.AT(kk, ss, xx) = vals.at(4 + (xx - 15));
		        }
		      }
		    }
	    }
    
    }
    
  }

}
