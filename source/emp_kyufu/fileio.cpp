#include "sepscommon.h"
#include <iostream>
#include <string>     
#include <sstream>    
#include <iomanip>    
#include <fstream>    
#include <map>        
using namespace std;

static void open_and_add_map(const string &fullpath, const string &mode, const string &keyname);

void seps::fopn(void) {
  int syutsuerr;

  string
    cver, cname, cwname, cecon, cyr,
    saimushu, ctem, vernum;
  string
    cseid[8];

  stringstream ss;

  ss << setw(4) << setfill('0') << iname << "\n";
  ss >> cname;

  ss << setw(4) << setfill('0') << iwname << "\n";
  ss >> cwname;

  ss << setw(4) << setfill('0') << iecon << "\n";
  ss >> cecon;


  cseid[0] = "kou";
  cseid[1] = "kok";
  cseid[4] = "ren";
  cseid[5] = "sig";

  string base_dir, fullpath, keystr;
  base_dir = "/suuri/rev2024";


  fullpath = base_dir + "/emp/rslt/u-rev/PROG.log";
  keystr = "prog";
  open_and_add_map(fullpath, "w", keystr); 
  
	
  fullpath = base_dir + "/emp/data/u-rev/kisor/kisor_" + cseid[pseid] + "2024.csv";
  keystr = "kisor";
  open_and_add_map(fullpath, "r", keystr);
	

  fullpath = base_dir + "/emp/data/u-rev/kisor/hou_" + cseid[pseid] + "2024.csv";
  keystr = "hou";
  open_and_add_map(fullpath, "r", keystr);
    

  fullpath = base_dir + "/emp/data/u-rev/kisor/sikur_" + cseid[pseid] + "2024.csv";
  keystr = "sikur";
  open_and_add_map(fullpath, "r", keystr);
    

    fullpath = base_dir + "/emp/data/u-rev/kisor/yuizor_" + cseid[pseid] + "2024.csv";
    keystr = "yuizor";
    open_and_add_map(fullpath, "r", keystr);

    if(seimei == 4) fullpath = base_dir + "/emp/data/u-sinj/QX-M2023.csv";
    if(seimei == 5) fullpath = base_dir + "/emp/data/u-sinj/QX-H2023.csv";
    if(seimei == 6) fullpath = base_dir + "/emp/data/u-sinj/QX-L2023.csv";
    
    keystr = "qx";
    open_and_add_map(fullpath, "r", keystr);
    

    fullpath = base_dir + "/emp/data/u-rev/kisor/kragsg_2024.csv";
    keystr = "kragsg";
    open_and_add_map(fullpath, "r", keystr); 
    
    

   	fullpath = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/hk2021-1.csv";
    keystr = "hk-1";
    open_and_add_map(fullpath, "r", keystr);

    fullpath = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/hk2021-2.csv";
    keystr = "hk-2";
    open_and_add_map(fullpath, "r", keystr);

    if(pseid == 0){
	   	fullpath = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/hk2021-3.csv";
        keystr = "hk-3";
        open_and_add_map(fullpath, "r", keystr);
    }

    string fullpath1, fullpath2, fullpath3;
    
	if(pseid == 0){
		fullpath1 = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/jk2021-1.csv";
		fullpath2 = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/jk2021-2.csv";
		fullpath3 = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/jk2021-3.csv";
	}
	else{
		fullpath1 = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/jk2021-1.csv";
		fullpath2 = base_dir + "/emp/data/u-rev/kisos/" + cseid[pseid] + "/jk2021-2.csv";
	}
    
    open_and_add_map(fullpath1, "r", "jk-1");
    open_and_add_map(fullpath2, "r", "jk-2");
    if(pseid == 0) open_and_add_map(fullpath3, "r", "jk-3");
    
	fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-20.csv";
	keystr = "waku-population";
	open_and_add_map(fullpath, "r", keystr);

	if(pseid == 0) fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-05.csv";
	if(pseid == 1) fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-08.csv";
	if(pseid == 4) fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-09.csv";
	if(pseid == 5) fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-10.csv";
	keystr = "waku";
	open_and_add_map(fullpath, "r", keystr);

	if(pseid == 0) {
	  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-06.csv";
	  keystr = "waku-s3";
	  open_and_add_map(fullpath, "r", keystr);
	     
	  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-07.csv";
	  keystr = "waku-part-all";
	  open_and_add_map(fullpath, "r", keystr);
		   
	  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-22.csv";
	  keystr = "waku-part202410";
	  open_and_add_map(fullpath, "r", keystr);
	  
	  if(flg_part >= 1){
		  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-30.csv";
		  keystr = "waku-part30-op";
		  open_and_add_map(fullpath, "r", keystr);
	  	  
		  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-31.csv";
		  keystr = "waku-part20-30-op";
		  open_and_add_map(fullpath, "r", keystr);
		  
		  if(flg_part == 4){
			  fullpath = base_dir + "/wakuc/rslt/ver_4_1" + "/rslt" + cwname + "/waku" + cwname + "-32.csv";
			  keystr = "waku-part10-20-op";
			  open_and_add_map(fullpath, "r", keystr);
	  	  }
	  }
	  
   	}

  fullpath = base_dir + "/emp/data/u-rev/econ/econ-" + cecon + ".csv";
  keystr = "econ";
  open_and_add_map(fullpath, "r", keystr);


  syutsuerr = 0;

  if(key == 12) {
    if(pslsi == 2 && pslsi2 == 1) {
      if(psly == 25) {
        saimushu = "AK";
      } else {
        syutsuerr = 1;
      }
    } else {
      syutsuerr = 1;
    }
  }

  if(key == 13) {
    if(pslsi == 0 && pslsi2 == 1) {
      if(psly == 22) {
        saimushu = "CJ";
      } else {
        syutsuerr = 1;
      }
    } else if(pslsi == 2 && pslsi2 == 1) {
      if(psly == 25) {
        saimushu = "AJ";
      }else {
        syutsuerr = 1;
      }
    } else {
      syutsuerr = 1;
    }
  }

  if(syutsuerr == 1) {
    clog << "現在設定外の組み合わせです。 "
         << "psly = " << psly << ", "
         << "kzn = " << kzn << ", ";
    throw invalid_argument("syutsuerr");
  }


  string u_dir, shisan_id, shisan_id_seid;
  u_dir = base_dir + "/emp/rslt/u-rev";
  shisan_id = cname + "-" + cecon + "-" + cwname;
  shisan_id_seid = shisan_id + "_" + cseid[pseid];

  fullpath = "";
  if(key == 11) {
    fullpath = u_dir + "/shus/shus." + shisan_id_seid;
  } else if(key == 12 || key == 13) {
    fullpath = u_dir + "/shus/shus." + saimushu + shisan_id_seid;
  } 
  if(!fullpath.empty()){
    open_and_add_map(fullpath, "w", "sh");
  }

  if(key == 11){
    fullpath = "";
    fullpath = u_dir + "/shus/shusg." + shisan_id_seid;
    open_and_add_map(fullpath, "w", "shg");
  }


  if(pseid == 0 || konen != 1) {
    if(key == 11) {
      fullpath = u_dir + "/kiso/kiso." + shisan_id_seid;
    } else if(key == 12 || key == 13) {
      fullpath = u_dir + "/kiso/kiso." + saimushu + shisan_id_seid;
    }
    open_and_add_map(fullpath, "w", "kiso");
  }
  
  
  
  if(key == 11){
    fullpath = "";
    fullpath = u_dir + "/bunpu/bunpu_bb." + shisan_id_seid + ".csv";
    open_and_add_map(fullpath, "w", "bunpu_bb");
  }
  
  if(key == 11){
    fullpath = "";
    fullpath = u_dir + "/bunpu/bunpu_g." + shisan_id_seid + ".csv";
    open_and_add_map(fullpath, "w", "bunpu_g");
  }

  if(kaite == 1) {
    if(pseid == 0) {
      string kapath, kbpath;
      kapath = u_dir + "/kaite/kaitea-" + cname + "-" + cecon + "e";
      kbpath = u_dir + "/kaite/kaiteb-" + cname + "-" + cecon + "e";
      open_and_add_map(kapath, "w", "kaitea");
      open_and_add_map(kbpath, "w", "kaiteb");
    }
  }
  
  fullpath = base_dir + "/emp/rslt/u-rev/PRTFIL_1_0";
  keystr = "prtfil";
  open_and_add_map(fullpath, "w", keystr);

  string pstat_write_mode = "w";
  if(pstat_written) pstat_write_mode = "a";
  
  if((key == 11) && nenbeex == 0) {
    fullpath = u_dir + "/hikaku/hikaku." + shisan_id;
    keystr = "hikaku";
    open_and_add_map(fullpath, pstat_write_mode, keystr);

    fullpath = u_dir + "/ashimoto/ashimoto." + shisan_id;
    keystr = "ashimoto";
    open_and_add_map(fullpath, pstat_write_mode, keystr);

    fullpath = u_dir + "/ashimoto/ashimotos." + shisan_id;
    keystr = "ashimotos";
    open_and_add_map(fullpath, pstat_write_mode, keystr);

    fullpath = u_dir + "/ashimoto/ashimotosum." + shisan_id;
    keystr = "ashimotosum";
    open_and_add_map(fullpath, pstat_write_mode, keystr);

    fullpath = u_dir + "/ashimoto/ashimotossum." + shisan_id;
    keystr = "ashimotossum";
    open_and_add_map(fullpath, pstat_write_mode, keystr);

  } else if(key == 13 && nenbeex == 0) {
    fullpath = u_dir + "/hikaku/hikaku." + saimushu + shisan_id;
    keystr = "hikaku";
    open_and_add_map(fullpath, pstat_write_mode, keystr);
  }
  pstat_written = true; 
  
  if(key == 11) {
    
      if(nenbeex == 0) {
        fullpath = u_dir + "/hou/hou." + shisan_id_seid + ".csv";
        keystr = "hou_out";
        open_and_add_map(fullpath, "w", keystr);

        fullpath = u_dir + "/hou/hou2." + shisan_id_seid + ".csv";
        keystr = "hou2_out";
        open_and_add_map(fullpath, "w", keystr);

        fullpath = u_dir + "/kisor/kisor." + shisan_id_seid + ".csv";
        keystr = "kisor_out";
        open_and_add_map(fullpath, "w", keystr);
        
        fullpath = u_dir + "/kisor/sikr." + shisan_id_seid + ".csv";
        keystr = "sikr_out";
        open_and_add_map(fullpath, "w", keystr);
      }
    
  }
}

static void open_and_add_map(const string &fullpath, const string &mode, const string &keystr) {
  FILE *fp;
  if ((fp = fopen(fullpath.c_str(), mode.c_str())) == NULL) {
    clog << fullpath << " を開くのに失敗しました。" << "\n";
    throw invalid_argument("fopen did not succeed.");
  } else {
    bool key_exist = (fp_map.count(keystr) != 0);
    if(key_exist) {
      clog << "fp_map[\"" << keystr << "\"] は既に存在します。" << "\n";
      throw invalid_argument("std::map key already exists. keystr = " + keystr);
    } else {
      fp_map.insert(make_pair(keystr, fp));
      if (mode == "r") {
        readpath_map.insert(make_pair(keystr, fullpath));
      }
    }
  }
}

void seps::fcls() {
  for(map<string, FILE*>::iterator itr = fp_map.begin(); itr != fp_map.end(); itr++) {
    fclose(itr->second);
  }
  fp_map.clear();
  readpath_map.clear();
}