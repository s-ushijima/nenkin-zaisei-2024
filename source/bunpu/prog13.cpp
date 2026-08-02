#include "_prototype.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>

void func_orig::func13a(int arg13a1, int arg13a2, int arg13a3, int arg13a4, std::vector<int> const& arg13a5) {
  std::string path = "../rslt/01_" + std::to_string(arg13a3) + "_" + std::to_string(arg13a4) + "_" + std::to_string(arg13a1) + "_" + std::to_string(arg13a2) + ".csv";
  std::ofstream output_file(path);
  output_file << arg13a1 << std::endl;
  output_file << arg13a2 << std::endl;
  output_file << arg13a3 << std::endl;
  output_file << arg13a4 << std::endl;
  output_file << "01" << std::endl;
  output_file << 65 << "," << 2086 - arg13a2;
  int var13a1 = 0;
  for ( int i = 0; i < 4; ++i ) {
    var13a1 += arg13a5[i];
  }
  for ( int i = 0; i < 4; ++i ) {
    output_file << "," << std::setprecision(15) << (double)arg13a5[i]/(double)var13a1*100.0;
  }
  output_file << std::endl;
}

void func_orig::func13b(int arg13b1, int arg13b2, int arg13b3, int arg13b4, std::vector<int> const& arg13b5) {
  std::string path = "../rslt/02_" + std::to_string(arg13b3) + "_" + std::to_string(arg13b4) + "_" + std::to_string(arg13b1) + "_" + std::to_string(arg13b2) + ".csv";
  std::ofstream output_file(path);
  output_file << arg13b1 << std::endl;
  output_file << arg13b2 << std::endl;
  output_file << arg13b3 << std::endl;
  output_file << arg13b4 << std::endl;
  output_file << "02" << std::endl;
  output_file << 65 << "," << 2086 - arg13b2;
  int var13b1 = 0;
  for ( int i = 0; i < 6; ++i ) {
    var13b1 += arg13b5[i];
  }
  for ( int i = 0; i < 6; ++i ) {
    output_file << "," << std::setprecision(15) << (double)arg13b5[i]/(double)var13b1*100.0;
  }
  output_file << "," << std::setprecision(15) << (double)arg13b5[6]/(double)var13b1/12.0;
  output_file << std::endl;
}

void func_orig::func13c(int arg13c1, int arg13c2, int arg13c3, int arg13c4, std::vector<double> const& arg13c5) {
  std::string path = "../rslt/03_" + std::to_string(arg13c3) + "_" + std::to_string(arg13c4) + "_" + std::to_string(arg13c1) + "_" + std::to_string(arg13c2) + ".csv";
  std::ofstream output_file(path);
  output_file << arg13c1 << std::endl;
  output_file << arg13c2 << std::endl;
  output_file << arg13c3 << std::endl;
  output_file << arg13c4 << std::endl;
  output_file << "03" << std::endl;
  output_file << 65 << "," << 2086 - arg13c2;
  int var13c1 = 0;
  for ( int i = 0; i < 7; ++i ) {
    var13c1 += arg13c5[i];
  }
  for ( int i = 0; i < 7; ++i ) {
    output_file << "," << std::setprecision(15) << (double)arg13c5[i]/(double)var13c1*100.0;
  }
  output_file << "," << std::setprecision(15) << (double)arg13c5[7]/10000.0;
  output_file << std::endl;
}
