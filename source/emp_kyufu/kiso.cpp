#include "sepscommon.h"
#include "sepslib.h"
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
namespace sst = sepsstd;
namespace csv = csvio;


void seps::kiso() {
  v2_t beta   = VEC(double, ENDY, 115);
  v2_t qp0    = VEC(double, 115, 3);

  double tmp, kdc, kdctmp;

  v1_t qpr    = VEC(double, 2);
  v1_t rds    = VEC(double, 2);
  v1_t rdsp1  = VEC(double, 2);
  v1_t rdsp2  = VEC(double, 2);
  v1_t rdsp3  = VEC(double, 2);

  string nensyu;

  int ss, sss, s3;

  v1_t vals;
  vector<string> items;

  FILE *fp = fp_map["kisor"];

  csv::read(fp);
  int stmp = (int)csv::read(fp).at(1);
  assert(stmp == s);

  if(s2 != 2) ss = 1;
  if(s2 == 2) ss = 2;

  nensyu = csv::read_str(fp).at(1).substr(0, 1);
  assert(nensyu == "Q");

  csv::read(fp);
  FOR(x, 0, 115) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0);
    assert(xx == x);
    FOR(i, 1, 3) q.AT(KS, x, i) = vals.at(1 + (i - 1));
  }
  
  
  if(pseid != 0 && ss == 2){
      FOR(x, 20, 54){
	      q.AT(KS, x, 3) = (qp.AT(19, x, 1) + qp.AT(20, x, 1) + qp.AT(21, x, 1)) / 3.0;
	  }
  }


  FOR(k, KS + 1, KE) FOR(x, 0, 115) FOR(i, 1, 3) {
    if(i == 3) {
      if(ss == 1) sss = 2;
      if(ss == 2) sss = 1;
    } else {
      sss = ss;
    }
    qpr.AT(1) = 1.0;
    qpr.AT(2) = 1.0;
    
    if(q.AT(KS, x, i) > 0.0) {
      if(i == 3 && x < 60) {
        q.AT(k, x, i) = q.AT(KS, x, i);
      }
      else if(i != 2) {
        if(x <= 104) {
            if(kzn == 1){
                qp0.AT(x, sss) = (qp.AT(19, x, sss) + qp.AT(20, x, sss) + qp.AT(21, x, sss)) / 3.0;
	        	q.AT(k, x, i) = q.AT(KS, x, i) * qp.AT(min(k, seiy), x, sss) / qp0.AT(x, sss);
	        } 
	    }
        else {
          if(q.AT(KS, 104, i) > 1.0e-6) {
            q.AT(k, x, i) = min(1.0,
              q.AT(k, 104, i) * q.AT(KS, x, i) / q.AT(KS, 104, i));
          } else {
            q.AT(k, x, i) = 0.0;
          }
        }
      } 
      else if(i == 2) {
        if(q.AT(KS, x, 1) > 1.0e-6) {
          q.AT(k, x, i) = min(1.0,
            q.AT(KS, x, i) * q.AT(k, x, 1) / q.AT(KS, x, 1));
        } else {
          q.AT(k, x, i) = 0.0;
        }
      }
    } else {
      q.AT(k, x, i) = 0.0;
    }

    q.AT(k,x,i) = min(1.0, max(0.0, q.AT(k, x, i)));

    if(x == 115 || (i == 3 && x == 19)) q.AT(k, x, i) = 1.0;
  }

  FOR(k, KS + 1, KE) {
    q.AT(k, 65, 2) = q.AT(k, 65, 2) * max(0.0, (KS + 40 - k) / 40.0)
                     + (q.AT(k, 64, 2) + q.AT(k, 66, 2)) / 2.0 * min(1.0, (k - KS) / 40.0);
  }

  nensyu = csv::read_str(fp).at(1).substr(0, 1);
  assert(nensyu == "U");

  csv::read(fp);
  if(pseid == 0) {
    FOR(x, 15, 84) {
      vals = csv::read(fp);
      int xx = (int)vals.at(0);
      assert(xx == x);
      FOR(i, 1, 3) u.AT(KS + 1, x, i) = vals.at(1 + (i - 1));
    }
  } else {
    FOR(x, 15, 74) {
      vals = csv::read(fp);
      int xx = (int)vals.at(0);
      assert(xx == x);
      FOR(i, 1, 3) u.AT(KS + 1, x, i) = vals.at(1 + (i - 1));
    }
  }
  
  
  if(pseid == 0) {
  	 FOR(k, KS + 1, KE) FOR(x, 15, 84) {
		
	    if(s2 <= 3) {
	      if(s2 != 2) {
	        s3 = 1;
	      } else {
	        s3 = 2;
	      }
	      
	      if(flg_inout <= 1 && pseid == 0){
		      
		      if(flg_inout == 0){
		      	if(s3 == 1){
		      		if(x <= 39)             rds.AT(s3) = 0.00;
		      		if(x >= 40 && x <= 59)  rds.AT(s3) = 0.20;
		      		if(x >= 60 && x <= 64)  rds.AT(s3) = 0.40;
		      		if(x >= 65)             rds.AT(s3) = 0.00;
		      	}
		      	if(s3 == 2){
		      		if(x <= 24)             rds.AT(s3) = 0.00;
		      		if(x >= 25 && x <= 59)  rds.AT(s3) = 0.35;
		      		if(x >= 60 && x <= 64)  rds.AT(s3) = 0.55;
		      		if(x >= 65)             rds.AT(s3) = 0.00;
		      	}
		      }
		      else if(flg_inout == 1){
		      	if(s3 == 1){
		      		if(x <= 39)             rds.AT(s3) = 0.00;
		      		if(x >= 40 && x <= 59)  rds.AT(s3) = 0.00;
		      		if(x >= 60 && x <= 64)  rds.AT(s3) = 0.30;
		      		if(x >= 65)             rds.AT(s3) = 0.00;
		      	}
		      	if(s3 == 2){
		      		if(x <= 24)             rds.AT(s3) = 0.00;
		      		if(x >= 25 && x <= 59)  rds.AT(s3) = 0.20;
		      		if(x >= 60 && x <= 64)  rds.AT(s3) = 0.55;
		      		if(x >= 65)             rds.AT(s3) = 0.00;
		      	}
		      }
		      
		      if(k > KS + 1 && k <= 40) {
		        u.AT(k, x, 1) = u.AT(KS + 1, x, 1)
		                        * (1.0 - rds.AT(s3) * (k - (KS + 1.0)) / (40.0 - (KS + 1.0)));
		      } else if(k > 40) {
		        u.AT(k, x, 1) = u.AT(40, x, 1);
		      }
		   }
		   else{
		      u.AT(k, x, 1) = u.AT(KS + 1, x, 1);
		   }
		}
	    
	    u.AT(k, x, 3) = u.AT(KS + 1, x, 3) * qp.AT(min(k, seiy), x, s3) / qp.AT(21, x, s3);
	    if(x >= 70) {
     		if(q.AT(k, x, 1) < 1.0 - 1.0e-6) {
        		u.AT(k, x, 3) = -log(1.0 - q.AT(k, x, 1));
      		} else {
        		u.AT(k, x, 3) = 1000.0;
      		}
        }
        
     }
  }
  
  
  if(pseid == 1 || pseid == 4) {
    FOR(x, 15, 84) {
      u.AT(KS + 1, x, 0) = u.AT(KS + 1, x, 1) + u.AT(KS + 1, x, 2) + u.AT(KS + 1, x, 3);
    }
    
    if(s == 2) {
       if(pseid == 1) tmp = 0.16302;
       if(pseid == 4) tmp = 0.23008;
    } else {
       if(pseid == 1) tmp = 0.08676;
       if(pseid == 4) tmp = 0.25681;
    }
    FOR(k, KS + 1, KE) FOR(x, 15, 84) {
        if (k >= 23 && x == 64) {
        	u.AT(k, x, 0) = u.AT(KS + 1, x, 0) - tmp;
        } else if(((k == 24 || k == 25) && x == 65)  || 
                  ((k >= 27           ) && x == 66)) {
        	u.AT(k, x, 0) = u.AT(KS + 1, x, 0) + tmp;
        } else {
        	u.AT(k, x, 0) = u.AT(KS + 1, x, 0);
        }
        
  		qp0.AT(x, ss) = (qp.AT(19, x, ss) + qp.AT(20, x, ss) + qp.AT(21, x, ss)) / 3.0;
	    u.AT(k, x, 3) = u.AT(KS + 1, x, 3) * qp.AT(min(k, seiy), x, ss) / qp0.AT(x, ss);
	    if(x >= 70) {
     		if(q.AT(k, x, 1) < 1.0 - 1.0e-6) {
        		u.AT(k, x, 3) = -log(1.0 - q.AT(k, x, 1));
      		} else {
        		u.AT(k, x, 3) = 1000.0;
      		}
        }
  	    
  	    u.AT(k, x, 0) += u.AT(k, x, 3) -  u.AT(KS + 1, x, 3);
    }
  }
  
  
  if(pseid == 5) {
	  FOR(x, 15, 84) {
      	u.AT(KS + 1, x, 0) = u.AT(KS + 1, x, 1) + u.AT(KS + 1, x, 2) + u.AT(KS + 1, x, 3);
      }
	  FOR(k, KS + 1, KE) FOR(x, 15, 85) {
  		qp0.AT(x, ss) = (qp.AT(19, x, ss) + qp.AT(20, x, ss) + qp.AT(21, x, ss)) / 3.0;
	    u.AT(k, x, 3) = u.AT(KS + 1, x, 3) * qp.AT(min(k, seiy), x, ss) / qp0.AT(x, ss);
	    if(x >= 70) {
     		if(q.AT(k, x, 1) < 1.0 - 1.0e-6) {
        		u.AT(k, x, 3) = -log(1.0 - q.AT(k, x, 1));
      		} else {
        		u.AT(k, x, 3) = 1000.0;
      		}
        }
  	    
  		u.AT(k, x, 1) = u.AT(KS + 1, x, 0) - u.AT(KS + 1, x, 2) - u.AT(KS + 1, x, 3);
        
  	 }
  }
  
  
  FOR(k, KS + 1, KE) FOR(x, 15, 84) {
	  if(x <= 64) {
	       u.AT(k, x, 2) = u.AT(KS + 1, x, 2);
	  } else {
	       u.AT(k, x, 2) = 0.0;
	  }
	  seps::sknr(k, x, xxr, xrb);
	  xrb = max(60, xrb);
	  if(x > xrb) {
	  	if(pseid == 0 || pseid == 5){
	  		u.AT(k, x, 1) = 0.0;
	  	}
	  	if(pseid == 1 || pseid == 4){
	  		u.AT(k, x, 0) = u.AT(k, x, 2) + u.AT(k, x, 3);
	  	}
	  }
  }


  int tmxend;
  FOR(k, KS + 1, KE) {
    if(pseid == 0) {
      tmxend = 85;
    } else {
      tmxend = 70;
    }
    FOR(x, 15, 85) {
      if(pseid == 0 && x >= tmxend)                   u.AT(k, x, 1) = 1.0;
      if((pseid == 1 || pseid == 4) && x >= tmxend)   u.AT(k, x, 0) = 1000.0;
      if(pseid == 5 && x >= tmxend) 				  u.AT(k, x, 1) = 1000.0;
      
      
      if(pseid == 0 || pseid == 5) { 
        u.AT(k, x, 0) = u.AT(k, x, 1) + u.AT(k, x, 2) + u.AT(k, x, 3);
      }
      u.AT(k, x, 0) = max(0.0, u.AT(k, x, 0));
      u.AT(k, x, 2) = min(1.0, max(0.0, u.AT(k, x, 2)));
      u.AT(k, x, 3) = min(max(0.0, u.AT(k, x, 3)), 1.0 - u.AT(k, x, 2));
      u.AT(k, x, 1) = u.AT(k, x, 0) - u.AT(k, x, 2) - u.AT(k, x, 3);
    }
  }

  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "RT");

  csv::read(fp);
  FOR(x, 15, 74) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);
    rt.AT(KS+1, x) = vals.at(1);
  }

  FOR(x, 15, 74) FOR(k, KS + 2, KE) {
    rt.AT(k, x) = rt.AT(KS+1, x);
    seps::sknr(k, x, xxr, xrb);
    xrb = max(60, xrb);
    if(x > xrb) rt.AT(k, x) = 0.0;
  }


  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "YX");
  
  csv::read(fp);
  FOR(x, 15, 115) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);

    if(s != 2) {
      yx.AT(KS, x, 0) = vals.at(1);
      yx.AT(KS, x, 1) = 0.0;
      ns.AT(KS, x) = vals.at(2);
      
    } else {
      yx.AT(KS, x, 0) = vals.at(1);
      yx.AT(KS, x, 1) = vals.at(2);
      ns.AT(KS, x) = vals.at(3);
    }
  }

  FOR(k, KS + 1, KE) FOR(x, 15, 115) {
    yx.AT(k, x, 0) = yx.AT(KS, x, 0);
    yx.AT(k, x, 1) = yx.AT(KS, x, 1);
    ns.AT(k, x)    = ns.AT(KS, x);
  }

  nensyu = csv::read_str(fp).at(1).substr(0,2);
  assert(nensyu == "RC");

  csv::read(fp);
  FOR(x, 15, 115) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);
    rc.AT(s, KS, x) = vals.at(1);
  }

  FOR(k, KS + 1, KE) FOR(x, 15, 115) {
    rc.AT(s, k, x) = rc.AT(s, KS, x);
  }

  if(s == 2) {
    FOR(k, KS + 1, KE) FOR(x, 58,115) {
      if(k - 14 == x - 55) {
        rc.AT(s, k, x) = rc.AT(s , k - 1, x) * (k - 13 - 0.5) / (double)((k - 1) - 13);
      } else if(k - 14 < x - 55) {
        rc.AT(s, k, x) = rc.AT(s, k - 1, x) * (k - 13) / (double)((k - 1) - 13);
      } else {
        rc.AT(s, k, x) = rc.AT(s, k - 1, x);
      }
    }
  }

  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "CL");

  csv::read(fp);
  vals = csv::read(fp);
  FOR(i, 1, 3) cl.AT(KS, i) = vals.at(1 + (i - 1));
  FOR(i, 1, 3) cl2.AT(KS, i) = vals.at(4 + (i - 1));

  FOR(k, KS + 1, KE) FOR(i, 1, 3) {
    cl.AT(k,i)  = cl.AT(KS, i);
    cl2.AT(k,i) = cl2.AT(KS, i);
  }

  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "KD");
  
  csv::read(fp);
  csv::read(fp);

  FOR(x, 0, 115) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);
    FOR(i, 1, 2) kd.AT(KS ,i, 1, x)     = vals.at(1 + (i - 1));
    FOR(j, 2, 3) kd.AT(KS ,1, j, x)     = vals.at(3 + (j - 2));
    FOR(i, 3, 4) kd.AT(KS ,i, 1, x)     = vals.at(5 + (i - 3));
    FOR(j, 2, 3) kd.AT(KS ,3, j, x)     = vals.at(7 + (j - 2));
    FOR(j, 2, 3) kd.AT(KS ,5, j, x)     = vals.at(9 + (j - 2));
    kd.AT(KS, 1, 4, x) = vals.at(11);

    FOR(j, 2, 3) {
      kd.AT(KS, 2, j, x) = kd.AT(KS, 1, j, x);
      kd.AT(KS, 4, j, x) = kd.AT(KS, 3, j, x);
    }
    kd.AT(KS, 3, 4, x) = kd.AT(KS, 1, 4, x);
  }
  if(flg_hantei == 0){
	  if(s != 2) {
	    kdc = 0.0340341;
	  } else {
	    kdc = 0.0237070;
	  }
  }

  FOR(j, 1, 4) FOR(i, 1, 6) {
    if(((i == 2 || i == 4 || i == 5) && j == 4)
       || (i == 5 && j == 1)) continue;
    FOR(k, KS, KE) FOR(x, 0, 115) {
      if(i != 5 && i != 6) {
        kd.AT(k, i, j, x) = kd.AT(KS, i, j, x);
      } else if(i == 5) {
        kd.AT(k, i, j, x) = kd.AT(KS, i, j, x);
      }
      else if(i == 6) { 
        if        (k - 20 <= x - 69) {
          kdctmp = kdc * 0;
        } else if (k - 20 == x - 68) {
          kdctmp = kdc * 1;
        } else if (k - 20 == x - 67) {
          kdctmp = kdc * 2;
        } else if (k - 20 == x - 66) {
          kdctmp = kdc * 3;
        } else if (k - 20 == x - 65) {
          kdctmp = kdc * 4;
        } else if (k - 20 >= x - 64) {
          kdctmp = kdc * 5;
        }
        kd.AT(k, i, j, x) = kd.AT(KS, 1, j, x) * kdctmp;
      }
    }
  }
  if(s == 2) {
    FOR(k, KS + 1, KE) FOR(x, 58, 115) FOR(j, 2, 3) {
      if(k - 14 == x - 55) {
        kd.AT(k, 5, j, x) = kd.AT(k - 1, 5, j, x) * (k - 13 - 0.5)
                            / (double)((k - 1) - 13);
      } else if(k - 14 < x - 55) {
        kd.AT(k, 5, j, x) = kd.AT(k - 1, 5, j, x) * (k - 13)
                            / (double)((k - 1) - 13);
      } else {
        kd.AT(k, 5, j, x) = kd.AT(k - 1, 5, j, x);
      }
    }
  }


  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "IK");  
  csv::read(fp);
  FOR(x, 20, 49) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);
    ikucoe.AT(KS+1, x) = vals.at(1);
  }

  FOR(k, KS + 2, KE) FOR(x, 20, 49) {
    ikucoe.AT(k, x) = ikucoe.AT(KS+1, x);
  }
  

  nensyu = csv::read_str(fp).at(1).substr(0, 2);
  assert(nensyu == "JI");  
  csv::read(fp);
  FOR(x, 20, 49) {
    vals = csv::read(fp);
    int xx = (int)vals.at(0); assert(xx == x);
    jiiku.AT(KS+1, x) = vals.at(1);
  }

  FOR(k, KS + 2, KE) FOR(x, 20, 49) {
    jiiku.AT(k, x) = jiiku.AT(KS+1, x);
  }

  FILE *fpo = fp_map["kisor_out"];
  if(key == 11 && nenbeex == 0) {
    fprintf(fpo, "受給者の失権率 Q\n");
    fprintf(fpo, "記号,種別,年度,年齢,老齢,障害,遺族\n");
    FOR(k, KS, KE) FOR(x, 0, 115) {
      fprintf(fpo,
        "Q,%d,%d,%d,%22.15e,%22.15e,%22.15e\n",
        s, k, x, q.AT(k, x, 1), q.AT(k, x, 2), q.AT(k, x, 3));
    }

    fprintf(fpo, "被保険者の脱退力 U\n");
    fprintf(fpo, "記号,種別,年度,年齢,計,生存,障害,死亡\n");
    FOR(k, KS, KE) FOR(x, 15, 85) {
      fprintf(fpo,
        "U,%d,%d,%d,%22.15e,%22.15e,%22.15e,%22.15e\n",
        s, k, x, u.AT(k, x, 0), u.AT(k, x, 1), u.AT(k, x, 2), u.AT(k, x, 3));
    }

    fprintf(fpo, "再加入者/(新規加入者+再加入者) RT\n");
    fprintf(fpo, "記号,種別,年度,年齢,再加入者/(新規加入者+再加入者)\n");
    FOR(k, KS, KE) FOR(x, 15, 74) {
      fprintf(fpo,
        "RT,%d,%d,%d,%22.15e\n",
        s, k, x, rt.AT(k, x));
    }

    fprintf(fpo, "年齢相関 YX\n");
    fprintf(fpo, "記号,種別,年度,年齢,被保から妻/夫,被保から子\n");
    FOR(k, KS, KE) FOR(x, 15, 115) {
      fprintf(fpo,
        "YX,%d,%d,%d,%22.15e,%22.15e\n",
        s, k, x, yx.AT(k, x, 0), yx.AT(k, x, 1));
    }

    fprintf(fpo, "加給・加算用（受給者から配偶者） NS\n");
    fprintf(fpo, "記号,種別,年度,年齢,加給・加算用（受給者から配偶者）\n");
    FOR(k, KS, KE) FOR(x, 15, 115) {
      fprintf(fpo,
        "NS,%d,%d,%d,%22.15e\n",
        s, k, x, ns.AT(k, x));
    }

    fprintf(fpo, "有子割合 RC\n");
    fprintf(fpo, "記号,種別,年度,年齢,有子割合\n");
    FOR(k, KS, KE) FOR(x, 0, 115) {
      fprintf(fpo,
        "RC,%d,%d,%d,%22.15e\n",
        s, k, x, rc.AT(s, k, x));
    }

    fprintf(fpo, "障害年金割合 CL\n");
    fprintf(fpo, "記号,種別,年度,年齢,1級,2級,3級\n");
    FOR(k, KS, KE) FOR(x, 0, 115) {
      fprintf(fpo,
        "CL,%d,%d,%d,%22.15e,%22.15e,%22.15e\n",
        s, k, x, cl.AT(k, 1), cl.AT(k, 2), cl.AT(k, 3));
    }

    fprintf(fpo, "加給対象者割合、振替加算割合 kd\n");
    fprintf(fpo,
      "記号,種別,年度,年齢,"
      "新老（配）,新老（子12）,新老（子3）,新老（配振）,"
      "旧老（配）,旧老（子12）,旧老（子3）,"
      "新障（配）,新障（子12）,新障（子3）,新障（配振）,"
      "旧障（配）,旧障（子12）,旧障（子3）,"
      "遺族（子12）,遺族（子3）,"
      "新通（配）,新通（子12）,新通（子3）,新通（配振）\n");
    FOR(k, KS, KE) FOR(x, 0, 115) {
      vals.clear();
      FOR(j, 1, 4) vals.push_back(kd.AT(k, 1, j, x));
      FOR(j, 1, 3) vals.push_back(kd.AT(k, 2, j, x));
      FOR(j, 1, 4) vals.push_back(kd.AT(k, 3, j, x));
      FOR(j, 1, 3) vals.push_back(kd.AT(k, 4, j, x));
      FOR(j, 2, 3) vals.push_back(kd.AT(k, 5, j, x));
      FOR(j, 1, 4) vals.push_back(kd.AT(k, 6, j, x));
      assert(vals.size() == 20);
      fprintf(fpo,
        "KD,%d,%d,%d,%s\n",
        s, k, x, csv::join("%22.15e", vals).c_str());
    }

    fprintf(fpo, "育休産休取得率 IKUCOE\n");
    fprintf(fpo, "記号,種別,年度,育休産休取得率\n");
    FOR(k, KS, KE) FOR(x, 15, 64){ 
      fprintf(fpo,
        "IKUCOE,%d,%d,%d,%22.15e\n",
        s, k, x,ikucoe.AT(k, x));
    }

    fprintf(fpo, "標準報酬比率（２種のみセット） JIIKU\n");
    fprintf(fpo, "記号,種別,年度,標準報酬比率\n");
    FOR(k, KS, KE) FOR(x, 15, 64) {
      fprintf(fpo,
        "JIIKU,%d,%d,%d,%22.15e\n",
        s, k, x, jiiku.AT(k, x));
    }
  }
}