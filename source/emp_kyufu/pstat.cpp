#include "sepscommon.h"
#include "sepslib.h"
#include <stdio.h>
#include <string>
namespace sst = sepsstd; 
namespace csv = csvio;
namespace seq = csvio::sequential;

namespace hikaku_ns {

  const char * join2(const v2_t &v, int axis1, int exp) {
    v1_t vals;
    for(int jj = 1; jj <= 2; jj++) {
      vals.push_back(v.AT(axis1, jj) * pow(10.0, exp));
    }
    return csvio::join("%16.8lf", vals).c_str();
  }
  const char * sum1_join2(const v2_t &v, int axis1_from, int axis1_to, int exp) {
    v1_t vals;
    double sum1;
    for(int jj = 1; jj <= 2; jj++) {
      sum1 = 0;
      for(int a1 = axis1_from; a1 <= axis1_to; a1++) {
        sum1 += v.AT(a1, jj);
      }
      vals.push_back(sum1 * pow(10.0, exp));
    }
    return csvio::join("%16.8lf", vals).c_str();
  }
  const char * join1(const v2_t &v, int axis2, int exp) {
    v1_t vals;
    for(int i = 1; i <= 13; i++) {
      vals.push_back(v.AT(i, axis2) * pow(10.0, exp));
    }
    return csvio::join("%16.10lf", vals).c_str();
  }
}

void seps::pstat(void) {

  FILE *fp;
  v1_t vals;
  

  v1_t tmp = VEC(double, 10);
  v2_t tmq = VEC(double, 58, 2);
  v2_t tmr = VEC(double, 13, 2);
  v3_t tms = VEC(double, 115, 13, 58);
  v3_t tmt = VEC(double, 115, 13, 17);
  v3_t tmu = VEC(double, 115, 13, 58);
  v3_t tmv = VEC(double, 115, 13, 17);
  v2_t tmw = VEC(double, 13, 17);
  v2_t tmx = VEC(double, 13, 17);
  v2_t tmka = VEC(double, 13, 2);


  int k_hikaku;
  k_hikaku = KIJUN + 4;
  
  FOR(k, KIJUN, KIJUN + 19) {
    if((key == 11 || key == 13) && nenbeex == 0){

      {
        using namespace hikaku_ns;
        fp = fp_map["hikaku"];

        if(k <= k_hikaku) {
          sst::subc1(tmp, 1,10);
          sst::subc2(tmq, 0,58, 1,2);
          sst::subc2(tmr, 1,13, 1,2);
          FOR(j, 1, 2) FOR(i, 1, 13) {
            tmka.AT(i, j) = 0.0;
          }

          FOR(s, 1, 3) {
            tmp.AT(1) += ap.AT(k, s);
            tmp.AT(2) += ap65.AT(k, s);
            tmp.AT(3) += ap70.AT(k, s);
            tmp.AT(4) += ap75.AT(k, s);
            tmp.AT(5) += ap85.AT(k, s);
            tmp.AT(6) += at.AT(k, s);
            tmp.AT(8) += a.AT(k, s)+aiku.AT(k, s);
            tmp.AT(9) += aiku.AT(k, s);

            FOR(jj, 1, 2) FOR(i, 1, 13) {
              tmr.AT(i, jj) +=   d3.AT(k, s, i, 1, jj) + d3.AT(k, s, i, 2, jj)
                              + d3.AT(k, s, i, 3, jj) + d3.AT(k, s, i, 4, jj)
                              + d3.AT(k, s, i, 5, jj) + d3.AT(k, s, i, 6, jj);
              FOR(j, 0, 58) {
                tmq.AT(j, jj) += d3.AT(k, s, i, j, jj);
                if(j == 10 && jj == 2)
                  tmka.AT(i, 1) += d3.AT(k, s, i, j, jj);
                if(j == 23 && jj == 2)
                  tmka.AT(i, 2) += d3.AT(k, s, i, j, jj);
              }
            }
          }

          fprintf(fp, "pseid,%d,試算番号,%d,経済前提,%d,外枠,%d\n", pseid, iname, iecon, iwname);
          fprintf(fp, "%d%s\n", k, "年度末状態の出力(年報データ比較用)");
          fprintf(fp, "%s\n", "被保険者データの出力");
          
          char f9000[] = "%s,%10.4lf,%s\n";
          fprintf(fp, f9000, "被保険者数", tmp.AT(1) * 1.0e-4, "万人");
          fprintf(fp, f9000, "待期者数", tmp.AT(6) * 1.0e-4, "万人");
          fprintf(fp, f9000, "基金加入者数", 0.0, "万人");
          fprintf(fp, f9000, "基金待期(厚年現存)", 0.0, "万人");
          fprintf(fp, f9000, "基金待期(厚年待期)", 0.0, "万人");
          fprintf(fp, f9000, "標報総計", tmp.AT(8) * 1.0e-12, "兆円");
          fprintf(fp, f9000, "標報総計(育児再掲)", tmp.AT(9) * 1.0e-12, "兆円");
          fprintf(fp, f9000, "基金標報総計", 0.0, "兆円");

          fprintf(fp, "%s,%s,%s,%s\n", "", "受給権者", "受給者", "");
          fprintf(fp, "%s,%12.4lf,%12.4lf,%s\n", "件数", tmq.AT(0, 1) * 1.0e-4, tmq.AT(0, 2) * 1.0e-4, "万人");

          char f9102[] = "%s,%s,%s\n";
          
          fprintf(fp, f9102, "総給付",  sum1_join2(tmq, 1,6, -12), "兆円");
          fprintf(fp, f9102, "総給付;新老退", join2(tmr, 1, -12), "兆円");
          fprintf(fp, f9102, "総給付;新老在", join2(tmr, 2, -12), "兆円");
          fprintf(fp, f9102, "総給付;新通退", join2(tmr, 3, -12), "兆円");
          fprintf(fp, f9102, "総給付;新通在", join2(tmr, 4, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧老退", join2(tmr, 5, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧老在", join2(tmr, 6, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧通退", join2(tmr, 7, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧通在", join2(tmr, 8, -12), "兆円");
          fprintf(fp, f9102, "総給付;新障", join2(tmr, 9, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧障", join2(tmr, 10, -12), "兆円");
          fprintf(fp, f9102, "総給付;新遺", join2(tmr, 11, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧遺１", join2(tmr, 12, -12), "兆円");
          fprintf(fp, f9102, "総給付;旧遺２", join2(tmr, 13, -12), "兆円");
          fprintf(fp, f9102, "独自給付", sum1_join2(tmq, 7, 12, -12), "兆円");
          fprintf(fp, f9102, "独自加給", join2(tmq, 10, -12), "兆円");
          fprintf(fp, f9102, "受給者分のi別内訳", join1(tmka, 1, -12), "兆円");
          fprintf(fp, f9102, "新法基礎", sum1_join2(tmq, 19, 21, -12), "兆円");
          fprintf(fp, f9102, "みなし基礎", sum1_join2(tmq, 22, 24, -12), "兆円");
          double kihon1 = (tmq.AT(22, 1) - tmq.AT(28, 1) - 3.0 * tmq.AT(25, 1)) * 1.0e-12;
          double kihon2 = (tmq.AT(22, 2) - tmq.AT(28, 2) - 3.0 * tmq.AT(25, 2)) * 1.0e-12;
          fprintf(fp, f9102, "みなし基本", sst::format("%16.8lf,%16.8lf", kihon1, kihon2).c_str(), "兆円");
          fprintf(fp, f9102, "みなし基本２", join2(tmq, 28, -12), "兆円");
          double kasa1 = (3.0 * tmq.AT(25, 1)) * 1.0e-12;
          double kasa2 = (3.0 * tmq.AT(25, 2)) * 1.0e-12;
          fprintf(fp, f9102, "みなし嵩上", sst::format("%16.8lf,%16.8lf", kasa1, kasa2).c_str(), "兆円");
          fprintf(fp, f9102, "みなし加給", join2(tmq, 23, -12), "兆円");
          fprintf(fp, f9102, "受給者分のi別内訳", join1(tmka, 2, -12), "兆円");          
          fprintf(fp, f9102, "みなし振替", join2(tmq, 24, -12), "兆円");
          fprintf(fp, f9102, "かさ上げ／４", join2(tmq, 25, -12), "兆円");
          fprintf(fp, f9102, "経過的国庫", sum1_join2(tmq, 26, 27, -12), "兆円");
          fprintf(fp, f9102, "基金代行", sst::format("%16.8lf,%16.8lf", 0.0, 0.0).c_str(), "兆円");
          fprintf(fp, f9102, "政府負担金", sst::format("%16.8lf,%16.8lf", 0.0, 0.0).c_str(), "兆円");
          fprintf(fp, f9102, "代行相当", join2(tmq, 31, -12), "兆円");
        }
      }

      if(key == 11 && nenbeex == 0){
        fp = fp_map["ashimoto"];

        sst::subc3(tms, 0,115, 0,13, 0,58);
        sst::subc3(tmt, 0,115, 0,13, 0,17);

        FOR(s, 1, 3) {
          if (pseid >= 1 && s == 3) continue;
          FOR(x, 0, 115) FOR(i, 1, 13) FOR(j, 0, 58) {
            tms.AT(x, i, j) += d3x.AT(k, x, s, i, j);
            tms.AT(x, 0, j) += d3x.AT(k, x, s, i, j);
          }
        }

        FOR(x, 0, 115) FOR(i, 0, 13) {
            tmt.AT(x, i, 0) =tms.AT(x, i, 0);
            tmt.AT(x, i, 1) =tms.AT(x, i, 1)+tms.AT(x, i, 2)+tms.AT(x, i, 3)
                      +tms.AT(x, i, 4)+tms.AT(x, i, 5)+tms.AT(x, i, 6);
            tmt.AT(x, i, 2) =tms.AT(x, i, 7)+tms.AT(x, i, 8)+tms.AT(x, i, 9)
                      +tms.AT(x, i, 10)+tms.AT(x, i, 11)+tms.AT(x, i, 12);
            tmt.AT(x, i, 3) =tms.AT(x, i, 7);
            tmt.AT(x, i, 4) =tms.AT(x, i, 8);
            tmt.AT(x, i, 5) =tms.AT(x, i, 9);
            tmt.AT(x, i, 6) =tms.AT(x, i, 10);
            tmt.AT(x, i, 7) =tms.AT(x, i, 11);
            tmt.AT(x, i, 8) =tms.AT(x, i, 12);
            tmt.AT(x, i, 9) =tms.AT(x, i, 19)+tms.AT(x, i, 20)+tms.AT(x, i, 21);
            tmt.AT(x, i, 10)=tms.AT(x, i, 22)+tms.AT(x, i, 23)+tms.AT(x, i, 24);
            tmt.AT(x, i, 11)=tms.AT(x, i, 22)-tms.AT(x, i, 28)-tms.AT(x, i, 25)*3.0;
            tmt.AT(x, i, 12)=tms.AT(x, i, 28);
            tmt.AT(x, i, 13)=tms.AT(x, i, 25)*3.0;
            tmt.AT(x, i, 14)=tms.AT(x, i, 23);
            tmt.AT(x, i, 15)=tms.AT(x, i, 24);
            tmt.AT(x, i, 16)=tms.AT(x, i, 25);
            tmt.AT(x, i, 17)=tms.AT(x, i, 26)+tms.AT(x, i, 27);
        }

        fprintf(fp, "pseid,%d,試算番号,%d,経済前提,%d,外枠,%d\n", pseid, iname , iecon, iwname);
        fprintf(fp, "%d,年度末状態の出力(足下のデータ)\n", k);
        fprintf(fp, "%s\n", "被保険者データの出力");
        
        char f9200[] = "%s,%16.0lf,%s\n";
        fprintf(fp, f9200, "被保険者数", tmp.AT(1), "人");
        fprintf(fp, f9200, "待期者数", tmp.AT(6), "人");
        fprintf(fp, f9200, "基金加入者数", 0.0, "人");
        fprintf(fp, f9200, "基金待期(厚年現存)", 0.0, "人");
        fprintf(fp, f9200, "基金待期(厚年待期)", 0.0, "人");
        fprintf(fp, f9200, "標報総計", tmp.AT(8), "円");
        fprintf(fp, f9200, "標報総計(育児再掲)", tmp.AT(9), "円");
        fprintf(fp, f9200, "基金標報総計", 0.0, "円");
        
        seq::line_feed(fp);
        fprintf(fp, "%s\n", "受給者データの出力");
        fprintf(fp, "%s\n", "人数は「人」単位、金額は「円」単位");

        FOR(j, 0, 17) {
          seq::line_feed(fp);
          char fmt[] = "j=,%d,%s\n";
          if(j == 0)       fprintf(fp, fmt, j, "受給者");
          else if(j == 1)  fprintf(fp, fmt, j, "総給付費");
          else if(j == 2)  fprintf(fp, fmt, j, "独自支給");
          else if(j == 3)  fprintf(fp, fmt, j, "独自比例");
          else if(j == 4)  fprintf(fp, fmt, j, "独自定額");
          else if(j == 5)  fprintf(fp, fmt, j, "経過的加算");
          else if(j == 6)  fprintf(fp, fmt, j, "独自加給");
          else if(j == 7)  fprintf(fp, fmt, j, "独自遺族加算");
          else if(j == 8)  fprintf(fp, fmt, j, "独自最低保障");
          else if(j == 9)  fprintf(fp, fmt, j, "新法基礎");
          else if(j == 10) fprintf(fp, fmt, j, "みなし基礎");
          else if(j == 11) fprintf(fp, fmt, j, "みなし基本");
          else if(j == 12) fprintf(fp, fmt, j, "みなし基本２");
          else if(j == 13) fprintf(fp, fmt, j, "みなし嵩上げ");
          else if(j == 14) fprintf(fp, fmt, j, "みなし加給");
          else if(j == 15) fprintf(fp, fmt, j, "みなし振替");
          else if(j == 16) fprintf(fp, fmt, j, "かさ上げ／４");
          else if(j == 17) fprintf(fp, fmt, j, "経過的国庫");
          
          fprintf(fp, "%s\n",
              "年齢, 総計"
              ", 新老退, 新老在, 新通退, 新通在"
              ", 旧老退, 旧老在, 旧通退, 旧通在"
              ", 新障, 旧障, 新遺, 旧遺, 旧通遺");
          FOR(x, 0, 115) {
            seq::print_int(fp, x);
            FOR(i, 0, 13) seq::add_dbl(fp, "%16.0lf", tmt.AT(x, i, j));
            seq::line_feed(fp);
          }
        }
      }


      if(key == 11 && nenbeex == 0){
        fp = fp_map["ashimotos"];
        sst::subc3(tmu, 0,115, 0,13, 0,58);
        sst::subc3(tmv, 0,115, 0,13, 0,17);

        FOR(s, 1, 3) {
          if (pseid >= 1 && s == 3) continue;
          FOR(x, 0, 115) FOR(i, 1, 13) FOR(j, 0, 58) {
            tmu.AT(x, i, j) += d3xs.AT(k, x, s, i, j);
            tmu.AT(x, 0, j) += d3xs.AT(k, x, s, i, j);

          }
        }

        FOR(x, 0, 115) FOR(i, 0, 13) {
          tmv.AT(x, i, 0) = tmu.AT(x, i, 0);
          tmv.AT(x, i, 1) =   tmu.AT(x, i, 1) + tmu.AT(x, i, 2) + tmu.AT(x, i, 3)
                        + tmu.AT(x, i, 4) + tmu.AT(x, i, 5) + tmu.AT(x, i, 6);
          tmv.AT(x, i, 2) =   tmu.AT(x, i, 7)  + tmu.AT(x, i, 8)  + tmu.AT(x, i, 9)
                        + tmu.AT(x, i, 10) + tmu.AT(x, i, 11) + tmu.AT(x, i, 12);
          tmv.AT(x, i, 3) =tmu.AT(x, i, 7);
          tmv.AT(x, i, 4) =tmu.AT(x, i, 8);
          tmv.AT(x, i, 5) =tmu.AT(x, i, 9);
          tmv.AT(x, i, 6) =tmu.AT(x, i, 10);
          tmv.AT(x, i, 7) =tmu.AT(x, i, 11);
          tmv.AT(x, i, 8) =tmu.AT(x, i, 12);
          tmv.AT(x, i, 9) =tmu.AT(x, i, 19) + tmu.AT(x, i, 20) + tmu.AT(x, i, 21);
          tmv.AT(x, i, 10)=tmu.AT(x, i, 22) + tmu.AT(x, i, 23) + tmu.AT(x, i, 24);
          tmv.AT(x, i, 11)=tmu.AT(x, i, 22) - tmu.AT(x, i, 28) - tmu.AT(x, i, 25) * 3.0;
          tmv.AT(x, i, 12)=tmu.AT(x, i, 28);
          tmv.AT(x, i, 13)=tmu.AT(x, i, 25) * 3.0;
          tmv.AT(x, i, 14)=tmu.AT(x, i, 23);
          tmv.AT(x, i, 15)=tmu.AT(x, i, 24);
          tmv.AT(x, i, 16)=tmu.AT(x, i, 25);
          tmv.AT(x, i, 17)=tmu.AT(x, i, 26) + tmu.AT(x, i, 27);
        }

        fprintf(fp, "pseid,%d,試算番号,%d,経済前提,%d,外枠,%d\n", pseid, iname, iecon, iwname);
        fprintf(fp, "%d,%s\n", k, "年度末状態の出力(足下のデータ)");
        fprintf(fp, "%s\n", "被保険者データの出力");
        
        char f9200[] = "%s,%16.0lf,%s\n";
        fprintf(fp, f9200, "被保険者数", tmp.AT(1), "人");
        fprintf(fp, f9200, "待期者数", tmp.AT(6), "人");
        fprintf(fp, f9200, "基金加入者数", 0.0, "人");
        fprintf(fp, f9200, "基金待期(厚年現存)", 0.0, "人");
        fprintf(fp, f9200, "基金待期(厚年待期)", 0.0, "人");
        fprintf(fp, f9200, "標報総計", tmp.AT(8), ", 円");
        fprintf(fp, f9200, "標報総計(育児再掲)", tmp.AT(9),  "円");
        fprintf(fp, f9200, "基金標報総計", 0.0, "円");

        seq::line_feed(fp);
        fprintf(fp, "%s\n", "受給権者データの出力");
        fprintf(fp, "%s\n", "人数は「人」単位、金額は「円」単位");

        FOR(j, 0, 17) {
          seq::line_feed(fp);
          
          char fmt[] = "j=,%d,%s\n";
          if(j == 0)       fprintf(fp, fmt, j, "受給権者");
          else if(j == 1)  fprintf(fp, fmt, j, "総給付費");
          else if(j == 2)  fprintf(fp, fmt, j, "独自支給");
          else if(j == 3)  fprintf(fp, fmt, j, "独自比例");
          else if(j == 4)  fprintf(fp, fmt, j, "独自定額");
          else if(j == 5)  fprintf(fp, fmt, j, "経過的加算");
          else if(j == 6)  fprintf(fp, fmt, j, "独自加給");
          else if(j == 7)  fprintf(fp, fmt, j, "独自遺族加算");
          else if(j == 8)  fprintf(fp, fmt, j, "独自最低保障");
          else if(j == 9)  fprintf(fp, fmt, j, "新法基礎");
          else if(j == 10) fprintf(fp, fmt, j, "みなし基礎");
          else if(j == 11) fprintf(fp, fmt, j, "みなし基本");
          else if(j == 12) fprintf(fp, fmt, j, "みなし基本２");
          else if(j == 13) fprintf(fp, fmt, j, "みなし嵩上げ");
          else if(j == 14) fprintf(fp, fmt, j, "みなし加給");
          else if(j == 15) fprintf(fp, fmt, j, "みなし振替");
          else if(j == 16) fprintf(fp, fmt, j, "かさ上げ／４");
          else if(j == 17) fprintf(fp, fmt, j, "経過的国庫");
          
          fprintf(fp, "%s\n",
              "年齢, 総計"
              ", 新老退, 新老在, 新通退, 新通在"
              ", 旧老退, 旧老在, 旧通退, 旧通在"
              ", 新障, 旧障, 新遺, 旧遺, 旧通遺");
          FOR(x, 0, 115) {
            seq::print_int(fp, x);
            FOR(i, 0, 13) seq::add_dbl(fp, "%16.0lf", tmv.AT(x, i, j));
            seq::line_feed(fp);
          }
        }
      }
      if(key == 11 && nenbeex == 0){
        fp = fp_map["ashimotosum"];
        sst::subc2(tmw, 0,13, 0,17);
        sst::subc2(tmx, 0,13, 0,17);

        FOR(i, 0, 13) FOR(j, 0, 17) FOR(x, 0, 115) {
            tmw.AT(i, j) += tmt.AT(x, i, j);
            tmx.AT(i, j) += tmv.AT(x, i, j);
        }

        fprintf(fp, "pseid,%d,試算番号,%d,経済前提,%d,外枠,%d\n",  pseid, iname, iecon, iwname);
        fprintf(fp, "%d,%s\n", k, "年度末状態の出力(足下のデータ)");
        fprintf(fp, "%s\n", "被保険者データの出力");
        
        char f9200[] = "%s,%16.0lf,%s\n";
        fprintf(fp, f9200, "被保険者数", tmp.AT(1), "人");
        fprintf(fp, f9200, "待期者数", tmp.AT(6), "人");
        fprintf(fp, f9200, "標報総計", tmp.AT(8), "円");
        fprintf(fp, f9200, "標報総計(育児再掲)", tmp.AT(9), "円");
        
        seq::line_feed(fp);
        fprintf(fp, "%s\n", "受給権者データの出力");
        fprintf(fp, "%s\n", "人数は「人」単位、金額は「円」単位");
        
        fprintf(fp, "%s\n",
            ", , , 総計"
            ", 新老退, 新老在, 新通退, 新通在"
            ", 旧老退, 旧老在, 旧通退, 旧通在"
            ", 新障, 旧障, 新遺, 旧遺, 旧通遺");
            
        FOR(j, 0, 17) {
          vals.clear();
          FOR(i, 0, 13) vals.push_back(tmw.AT(i, j));
          const char *ctmw = csv::join("%16.0lf", vals).c_str();
          char f9400[] = "j=,%d,%s,%s\n";
          if(j == 0)       fprintf(fp, f9400, j, "受給権者", ctmw);
          else if(j == 1)  fprintf(fp, f9400, j, "総給付費", ctmw);
          else if(j == 2)  fprintf(fp, f9400, j, "独自支給", ctmw);
          else if(j == 3)  fprintf(fp, f9400, j, "独自比例", ctmw);
          else if(j == 4)  fprintf(fp, f9400, j, "独自定額", ctmw);
          else if(j == 5)  fprintf(fp, f9400, j, "経過的加算", ctmw);
          else if(j == 6)  fprintf(fp, f9400, j, "独自加給", ctmw);
          else if(j == 7)  fprintf(fp, f9400, j, "独自遺族加算",ctmw);
          else if(j == 8)  fprintf(fp, f9400, j, "独自最低保障", ctmw);
          else if(j == 9)  fprintf(fp, f9400, j, "新法基礎",  ctmw);
          else if(j == 10) fprintf(fp, f9400, j, "みなし基礎",  ctmw);
          else if(j == 11) fprintf(fp, f9400, j, "みなし基本",  ctmw);
          else if(j == 12) fprintf(fp, f9400, j, "みなし基本２", ctmw);
          else if(j == 13) fprintf(fp, f9400, j, "みなし嵩上げ", ctmw);
          else if(j == 14) fprintf(fp, f9400, j, "みなし加給",  ctmw);
          else if(j == 15) fprintf(fp, f9400, j, "みなし振替",  ctmw);
          else if(j == 16) fprintf(fp, f9400, j, "かさ上げ／４", ctmw);
          else if(j == 17) fprintf(fp, f9400, j, "経過的国庫",  ctmw);
        }
      }

      if(key == 11 && nenbeex == 0){
        fp = fp_map["ashimotossum"];

        fprintf(fp, "pseid,%d,試算番号,%d,経済前提,%d,外枠,%d\n",  pseid, iname, iecon, iwname);
        fprintf(fp, "%d,%s\n", k, "年度末状態の出力(足下のデータ)");
        fprintf(fp, "%s\n", "被保険者データの出力");
        
        char f9200[] = "%s,%16.0lf,%s\n";
        fprintf(fp, f9200, "被保険者数", tmp.AT(1), "人");
        fprintf(fp, f9200, "待期者数", tmp.AT(6), "人");
        fprintf(fp, f9200, "標報総計", tmp.AT(8), "円");
        fprintf(fp, f9200, "標報総計(育児再掲)", tmp.AT(9), "円");
        
        seq::line_feed(fp);
        fprintf(fp, "%s\n", "受給権者データの出力");
        fprintf(fp, "%s\n", "人数は「人」単位、金額は「円」単位");
        
        fprintf(fp, "%s\n",
            ", , , 総計"
            ", 新老退, 新老在, 新通退, 新通在"
            ", 旧老退, 旧老在, 旧通退, 旧通在"
            ", 新障, 旧障, 新遺, 旧遺, 旧通遺");

        FOR(j, 0, 17) {
          vals.clear();
          FOR(i, 0, 13) vals.push_back(tmx.AT(i, j));
          const char *ctmx = csv::join("%16.0lf", vals).c_str();
          char f9400[] = "j=,%d,%s,%s\n";
          if(j == 0)       fprintf(fp, f9400, j, "受給権者", ctmx);
          else if(j == 1)  fprintf(fp, f9400, j, "総給付費", ctmx);
          else if(j == 2)  fprintf(fp, f9400, j, "独自支給", ctmx);
          else if(j == 3)  fprintf(fp, f9400, j, "独自比例", ctmx);
          else if(j == 4)  fprintf(fp, f9400, j, "独自定額", ctmx);
          else if(j == 5)  fprintf(fp, f9400, j, "経過的加算", ctmx);
          else if(j == 6)  fprintf(fp, f9400, j, "独自加給", ctmx);
          else if(j == 7)  fprintf(fp, f9400, j, "独自遺族加算",ctmx);
          else if(j == 8)  fprintf(fp, f9400, j, "独自最低保障", ctmx);
          else if(j == 9)  fprintf(fp, f9400, j, "新法基礎",  ctmx);
          else if(j == 10) fprintf(fp, f9400, j, "みなし基礎",  ctmx);
          else if(j == 11) fprintf(fp, f9400, j, "みなし基本",  ctmx);
          else if(j == 12) fprintf(fp, f9400, j, "みなし基本２", ctmx);
          else if(j == 13) fprintf(fp, f9400, j, "みなし嵩上げ", ctmx);
          else if(j == 14) fprintf(fp, f9400, j, "みなし加給",  ctmx);
          else if(j == 15) fprintf(fp, f9400, j, "みなし振替",  ctmx);
          else if(j == 16) fprintf(fp, f9400, j, "かさ上げ／４", ctmx);
          else if(j == 17) fprintf(fp, f9400, j, "経過的国庫",  ctmx);
        }
      }
    }
  }
}