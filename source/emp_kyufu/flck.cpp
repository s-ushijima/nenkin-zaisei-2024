#include "sepscommon.h"
#include <string>
#include <stdio.h>
#include <map> 
using namespace std;

static void flck_param(FILE *fp);
typedef map<string, string>::iterator iter_t;

void seps::flck(void) {
  if(key == 11 || key == 12 || key == 13) {
    FILE *fp_kiso = fp_map["kiso"];
    string keystr, fullpath;
    for(iter_t itr = readpath_map.begin(); itr != readpath_map.end(); itr++) {
      keystr = itr->first;
      fullpath = itr->second; 
      fprintf(fp_kiso, "%s, %s\n", keystr.c_str(), fullpath.c_str());
    }
    flck_param(fp_kiso);
    fprintf(fp_kiso, "#99-0000-0000\n", ""); 
  }
  
  if(key == 11 || key == 12 || key == 13) {
    FILE *fp_sh = fp_map["sh"];
    string keystr, fullpath;
    for(iter_t itr = readpath_map.begin(); itr != readpath_map.end(); itr++) {
      keystr = itr->first;
      fullpath = itr->second; 
      fprintf(fp_sh, "%s, %s\n", keystr.c_str(), fullpath.c_str());
    }
    flck_param(fp_sh);
    fprintf(fp_sh, "#99-0000-0000\n", "");
  }
}

static void flck_param(FILE *fp) {
  fprintf(fp, "KS, %d\n", KS);
  fprintf(fp, "KE, %d\n", KE);
  fprintf(fp, "KIJUN, %d\n", KIJUN);
  fprintf(fp, "daik14, %d\n", daik14);
  fprintf(fp, "kzn, %d\n", kzn);
  fprintf(fp, "kzny, %d\n", kzny);
  fprintf(fp, "seidver, %d\n", seidver);
  fprintf(fp, "flg_kaisho, %d\n", flg_kaisho);
  fprintf(fp, "psly, %d\n", psly);
  fprintf(fp, "pslsi, %d\n", pslsi);
  fprintf(fp, "pslsi2, %d\n", pslsi2);
  fprintf(fp, "flg_hiho70, %d\n", flg_hiho70);
  fprintf(fp, "hiho70yr, %d\n", hiho70yr);
  fprintf(fp, "flg_part, %d\n", flg_part);
  fprintf(fp, "partyr1, %d\n", partyr1);
  fprintf(fp, "partyr2, %d\n", partyr2);
  fprintf(fp, "flg_hsr, %d\n", flg_hsr);
  fprintf(fp, "flg_sigo, %d\n", flg_sigo);
  fprintf(fp, "flg_kozax, %d\n", flg_kozax);
}
