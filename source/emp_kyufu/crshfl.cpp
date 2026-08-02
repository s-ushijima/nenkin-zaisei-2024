#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
namespace sst = sepsstd;
namespace csv = csvio;
namespace seq = csvio::sequential;


void seps::crshfl(void) {

  FILE *fp = fp_map["sh"];
  v1_t vals;

  fprintf(fp, "%d,%d\n", KS, KE);
  fprintf(fp, "%s\n", "·ÐºÑÅªÍ×ÁÇ");
  fprintf(fp, "%s\n", "Ç¯ÅÙ,Íø²ó¤ê,ÄÂ¶â,Êª²Á,Ç¯¶â²þÄêÎ¨(ÈæÎã),Ç¯¶â²þÄêÎ¨(²Ãµë),Ç¯¶â²þÄêÎ¨(´ðÁÃ),Ç¯¶â²þÄêÎ¨(Êª²Á)");
  FOR(k, 1, KE) {
    fprintf(fp, "%d"
    ",%8.5lf,%8.5lf,%8.5lf,%8.5lf"
    ",%8.5lf,%8.5lf,%8.5lf\n",
    k,
    ri.AT(k),h.AT(k),ci.AT(k),hh.AT(k),
    hp2.AT(k,67),hp2.AT(k,67),ci2.AT(k,67));
  }

  fprintf(fp, "%s\n", ",AP,,,,APDUM");
  fprintf(fp, "%s\n", "K,S=0,S=1,S=2,S=3,S=1,S=2,S=3");
  FOR(k, FLKS, FLKE) {
     seq::print_int(fp, k);
    FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", ap.AT(k, s));
    FOR(s, 1, 3) seq::add_dbl(fp, "%21.14e", apdum.AT(k, s));
    seq::line_feed(fp);
  }

  if(flg_hiho70 == 0) {
    fprintf(fp, "%s\n", ",AP65,,,,AP70,,,,AP75");
    fprintf(fp, "%s\n", "K,S=0,S=1,S=2,S=3,S=0,S=1,S=2,S=3,S=0,S=1,S=2,S=3");
    FOR(k, FLKS, FLKE) {
      seq::print_int(fp, k);
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", ap65.AT(k, s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", ap70.AT(k, s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", ap75.AT(k, s));
      seq::line_feed(fp);
    }
  }

  if(flg_hiho70 == 0){
    fprintf(fp, "%s\n", ",A,,,,ADUM,,,A60,,,,A65,,,,A70,,,,A75");
    fprintf(fp, "%s\n",
        "k,s=0,s=1,s=2,s=3,s=1,s=2,s=3,s=0,s=1,s=2,s=3,"
        "s=0,s=1,s=2,s=3,s=0,s=1,s=2,s=3,s=0,s=1,s=2,s=3");
    FOR(k, FLKS, FLKE) {
      seq::print_int(fp, k);
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a.AT(k,s));
      FOR(s, 1, 3) seq::add_dbl(fp, "%21.14e", adum.AT(k,s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a60.AT(k,s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a65.AT(k,s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a70.AT(k,s));
      FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a75.AT(k,s));
      seq::line_feed(fp);
    }
  }

  fprintf(fp, "%s\n", "AIKU");
  fprintf(fp, "%s\n", "K,S=0,S=1,S=2,S=3");
  FOR(k, FLKS, FLKE) {
    seq::print_int(fp, k);
    FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", aiku.AT(k,s));
    FOR(s, 1, 3) seq::add_dbl(fp, "%21.14e", aikudum.AT(k,s));
    seq::line_feed(fp);
  }


  fprintf(fp, "%s\n", "AAL");
  fprintf(fp, "%s\n", "K,S=0,S=1,S=2,S=3");
  FOR(k, FLKS, FLKE) {
    seq::print_int(fp, k);
    FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", aal.AT(k,s));
    seq::line_feed(fp);
  }


  FOR(k, KS, KE) {
    if(pseid == 0 && k == partyr3) {
      fprintf(fp, "%s\n", "PARTHOU");
      fprintf(fp, "%s\n", "K,S=0,S=1,S=2,S=3");
      if(flg_hiho70 == 0) {
        seq::print_int(fp, k);
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", apart.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", aikupart.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a60part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a65part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a70part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a75part.AT(k,s));
        seq::line_feed(fp);
      } 
    } 
    if(flg_part >= 1 && pseid == 0 && k == partyr4) {
      if(flg_hiho70 == 0) {
        seq::print_int(fp, k);
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", apart.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", aikupart.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a60part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a65part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a70part.AT(k,s));
        FOR(s, 0, 3) seq::add_dbl(fp, "%21.14e", a75part.AT(k,s));
        seq::line_feed(fp);
      } 
    }
  }
    
  int xstrt;
  if(nenbeex == 0) {
    xstrt = xa - 1;
  } else {
    xstrt = xa;
  }


  FOR(x, xstrt, xb) FOR(s, 1, 3) {
    fprintf(fp, "%s,%d,%d\n", "D3X(k;s;i;0)", x, s);
    fprintf(fp, "%s\n", "k,¹ç·×,Ï·Âà,Ï·ºß,ÄÌÂà,ÄÌºß,¾ã³²,°äÂ²");
    FOR(k, FLKS, FLKE) {
      vals.clear();
      vals.push_back(d3x.AT(k,x,s,0,0));
      vals.push_back(d3x.AT(k,x,s,1,0)  + d3x.AT(k,x,s,5,0));
      vals.push_back(d3x.AT(k,x,s,2,0)  + d3x.AT(k,x,s,6,0));
      vals.push_back(d3x.AT(k,x,s,3,0)  + d3x.AT(k,x,s,7,0));
      vals.push_back(d3x.AT(k,x,s,4,0)  + d3x.AT(k,x,s,8,0));
      vals.push_back(d3x.AT(k,x,s,9,0)  + d3x.AT(k,x,s,10,0));
      vals.push_back(d3x.AT(k,x,s,11,0) + d3x.AT(k,x,s,12,0) + d3x.AT(k,x,s,13,0));
      fprintf(fp,"%d,%s\n", k, csv::join("%21.14e", vals).c_str());
    }
  }

  FOR(x, xstrt, xb) FOR(s, 0, 3) FOR(i, 0, 13) {
    fprintf(fp, "%s,%d,%d,%d\n", "D3X", x, s, i);
    fprintf(fp, "%s\n", "K,J=25,J=7,J=8,J=9,J=10,J=11,J=12,KOFU");
    FOR(k, FLKS, FLKE) {
      vals.clear();
      vals.push_back(d3x.AT(k,x,s,i,25));
      FOR(j, 7, 12) vals.push_back(d3x.AT(k,x,s,i,j));
      vals.push_back(d3x.AT(k,x,s,i,22)+d3x.AT(k,x,s,i,23)+d3x.AT(k,x,s,i,24));
      vals.push_back(d3x.AT(k,x,s,i,22)+d3x.AT(k,x,s,i,24));
      vals.push_back(d3x.AT(k,x,s,i,23));
      fprintf(fp, "%d,%s\n", k, csv::join("%21.14e", vals).c_str());
    }
  }


  FOR(x, xstrt, xb) FOR(i, 0, 13) {
    fprintf(fp, "%s,%d,%d\n", "KFPRX", x, i);
    fprintf(fp, "%s\n", "K,(S-J)=0-1,0-2,1-1,1-2,2-1,2-2,3-1,3-2");
    FOR(k, FLKS, FLKE) {
      vals.clear();
      FOR(s, 0, 3) FOR(j, 1, 2) vals.push_back(kfprx.AT(k,x,s,i,j));
      fprintf(fp, "%d,%s\n", k, csv::join("%21.14e", vals).c_str());
    }
  }


  if(key == 11){
    FILE *fpg = fp_map["shg"];

    FOR(k, FLKS, FLKE) FOR(s, 0, 3) {
      fprintf(fpg, "%s,%s,%d,%s,%d\n", "GEE(K,S,X,T)", "K=", k, "S=", s);
      FOR(x, 15, 85) {
        vals.clear();
        FOR(t, 0 ,70) vals.push_back(gee.AT(k,s,x,t));
        fprintf(fpg, "%d,%s\n", x, csv::join("%21.14e", vals).c_str());
      }
    }

    FOR(k, FLKS, FLKE) FOR(s, 0, 3) {
      fprintf(fpg, "%s,%s,%d,%s,%d\n", "GEEPT(K,S,X,T)", "K=", k, "S=", s);
      FOR(x, 15, 85) {
        vals.clear();
        FOR(t, 0, 70) vals.push_back(geept.AT(k,s,x,t));
        fprintf(fpg, "%d,%s\n", x, csv::join("%21.16e", vals).c_str());
      }
    }
  }
  

   if(key == 11){
	   	FILE *fp_bb = fp_map["bunpu_bb"];
		fprintf(fp_bb, "%s,%s,%s,%s\n","bb","k","s","x");
	    FOR(k, KIJUN, KE) FOR(s, 1, 3) FOR(x, 15, 69) {
	    	vals.clear();
	    	FOR(t, 0, 70) vals.push_back(bb3.AT(k, s, x, t));
	    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "bb",k, s, x, csv::join("%21.14e", vals).c_str());
	    }
	  	if(pseid == 0){
		    FOR(k, KIJUN, KE) FOR(s, 1, 2) FOR(x, 15, 69) {
		    	vals.clear();
		    	FOR(t, 0, 70) vals.push_back(bbnp3.AT(k, s, x, t));
		    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "bbnp",k, s, x, csv::join("%21.14e", vals).c_str());
		    }
		    FOR(k, KIJUN, 70) FOR(s, 1, 2) FOR(x, 15, 69) {
		    	vals.clear();
		    	FOR(t, 0, 70) vals.push_back(bbpt3.AT(k, s, x, t));
		    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "bbpt",k, s, x, csv::join("%21.14e", vals).c_str());
		    }
		}
   }
   if(key == 11){
	   	FILE *fp_bb = fp_map["bunpu_g"];
		fprintf(fp_bb, "%s,%s,%s,%s\n","g","k","s","x");
	    FOR(k, KIJUN, KE) FOR(s, 1, 3) FOR(x, 15, 69) {
	    	vals.clear();
	    	FOR(t, 0, 70) vals.push_back(g3.AT(k, s, x, t));
	    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "g",k, s, x, csv::join("%21.14e", vals).c_str());
	    }
	  	if(pseid == 0){
		    FOR(k, KIJUN, KE) FOR(s, 1, 2) FOR(x, 15, 69) {
		    	vals.clear();
		    	FOR(t, 0, 70) vals.push_back(gnp3.AT(k, s, x, t));
		    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "gnp",k, s, x, csv::join("%21.14e", vals).c_str());
		    }
		    FOR(k, KIJUN, KE) FOR(s, 1, 2) FOR(x, 15, 69) {
		    	vals.clear();
		    	FOR(t, 0, 70) vals.push_back(gpt3.AT(k, s, x, t));
		    	fprintf(fp_bb, "%s,%d,%d,%d,%s\n", "gpt",k, s, x, csv::join("%21.14e", vals).c_str());
		    }
		}
   }
     
}


