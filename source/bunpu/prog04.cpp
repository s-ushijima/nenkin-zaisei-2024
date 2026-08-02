#include "_prototype.h"
#include <string>
#include <fstream>

std::string func_orig::func04a(int arg04a1, int arg04a2) {
  std::string path_file = "../kisosuu/" + std::to_string(arg04a1) + "/" + std::to_string(arg04a2) + "/kisosuu_set.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04b(int arg04b1, int arg04b2, int arg04b3, int arg04b4, int arg04b5) {
  std::string path_file = "../kisoritsu/kisoritsu01/" + std::to_string(arg04b1) + "/" + std::to_string(arg04b2) + "/seni_" + std::to_string(arg04b1) + "_" + std::to_string(arg04b3) + "_" + std::to_string(arg04b4) + "_" + std::to_string(arg04b5) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04c(int arg04c1, int arg04c2) {
  std::string path_file = "../kisoritsu/kisoritsu02/prob_shougai_shikken_" + std::to_string(arg04c1) + "_" + std::to_string(arg04c2) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04d(int arg04d1, int arg04d2) {
  std::string path_file = "../kisoritsu/kisoritsu03/prob_shougai_hassei_" + std::to_string(arg04d1) + "_" + std::to_string(arg04d2) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04e(int arg04e1) {
  std::string path_file = "../kisoritsu/kisoritsu04/prob_shougai_hassei_20mae_" + std::to_string(arg04e1) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04f(int arg04f1, int arg04f2) {
  std::string path_file = "../kisoritsu/kisoritsu05/prob_seni_kikan_" + std::to_string(arg04f1) + "_" + std::to_string(arg04f2) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04g(int arg04g1, int arg04g2) {
  std::string path_file = "../kisoritsu/kisoritsu06/prob_houshuu_seni_" + std::to_string(arg04g1) + "_" + std::to_string(arg04g2) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04h(int arg04h1, int arg04h2) {
  std::string path_file = "../kisoritsu/kisoritsu07/prob_houshuu_shinki_" + std::to_string(arg04h1) + "_" + std::to_string(arg04h2) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04i(void) {
  std::string path_file = "../kisoritsu/kisoritsu08/table_souhoushuu.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04j(int arg04j1) {
  std::string path_file = "../../emp/data/u-rev/econ/econ-" + std::to_string(arg04j1) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04k(int arg04k1, int arg04k2) {
  std::string path_file = "../../emp/rslt/u-rev/kaite/kaitea-" + std::to_string(arg04k1) + "-" + std::to_string(arg04k2) + "e";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04m(int arg04m1, int arg04m2) {
  std::string path_file = "../../emp/rslt/u-rev/kaite/kaiteb-" + std::to_string(arg04m1) + "-" + std::to_string(arg04m2) + "e";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04n(int arg04n1, int arg04n2, int arg04n3) {
  std::string path_file = "../../nat/data/PENSION_" + std::to_string(arg04n2) + "-" + std::to_string(arg04n3) + "-" + std::to_string(arg04n1) + ".csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04p(int arg04p1, int arg04p2, int arg04p3) {
  std::string path_file = "../../emp/rslt/ez_arev/cutr/cuta-" + std::to_string(arg04p2) + "-" + std::to_string(arg04p2) + "-" + std::to_string(arg04p3) + "-" + std::to_string(arg04p1) + "-1120-125.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04q(int arg04q1, int arg04q2, int arg04q3) {
  std::string path_file = "../../emp/rslt/ez_arev/cutr/cutb-" + std::to_string(arg04q2) + "-" + std::to_string(arg04q2) + "-" + std::to_string(arg04q3) + "-" + std::to_string(arg04q1) + "-1120-125.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04r(int arg04r1, int arg04r2, int arg04r3) {
  std::string path_file = "../../emp/rslt/ez_arev/cutr/cuta-" + std::to_string(arg04r2) + "-" + std::to_string(arg04r2) + "-" + std::to_string(arg04r3) + "-" + std::to_string(arg04r1) + "-1120-925.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04s(int arg04s1, int arg04s2, int arg04s3) {
  std::string path_file = "../../emp/rslt/ez_arev/cutr/cutb-" + std::to_string(arg04s2) + "-" + std::to_string(arg04s2) + "-" + std::to_string(arg04s3) + "-" + std::to_string(arg04s1) + "-1120-925.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04t(int arg04t1, int arg04t2, int arg04t3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_bb." + std::to_string(arg04t2) + "-" + std::to_string(arg04t3) + "-" + std::to_string(arg04t1) + "_kou.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04u(int arg04u1, int arg04u2, int arg04u3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_bb." + std::to_string(arg04u2) + "-" + std::to_string(arg04u3) + "-" + std::to_string(arg04u1) + "_kok.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04v(int arg04v1, int arg04v2, int arg04v3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_bb." + std::to_string(arg04v2) + "-" + std::to_string(arg04v3) + "-" + std::to_string(arg04v1) + "_ren.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04w(int arg04w1, int arg04w2, int arg04w3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_bb." + std::to_string(arg04w2) + "-" + std::to_string(arg04w3) + "-" + std::to_string(arg04w1) + "_sig.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04x(int arg04x1, int arg04x2, int arg04x3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_g." + std::to_string(arg04x2) + "-" + std::to_string(arg04x3) + "-" + std::to_string(arg04x1) + "_kou.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04y(int arg04y1, int arg04y2, int arg04y3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_g." + std::to_string(arg04y2) + "-" + std::to_string(arg04y3) + "-" + std::to_string(arg04y1) + "_kok.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04z(int arg04z1, int arg04z2, int arg04z3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_g." + std::to_string(arg04z2) + "-" + std::to_string(arg04z3) + "-" + std::to_string(arg04z1) + "_ren.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}

std::string func_orig::func04aa(int arg04aa1, int arg04aa2, int arg04aa3) {
  std::string path_file = "../../emp/rslt/u-rev/bunpu/bunpu_g." + std::to_string(arg04aa2) + "-" + std::to_string(arg04aa3) + "-" + std::to_string(arg04aa1) + "_sig.csv";
  FILE *ifp_file;
  if((ifp_file=fopen(path_file.c_str(),"r"))==NULL) {
    std::exit(1);
  }
  return path_file;
}
