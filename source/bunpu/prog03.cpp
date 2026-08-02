#include "_prototype.h"
#include <string>
#include <fstream>
#include <vector>

std::vector<std::string> func_orig::func03a(std::string arg03a1, char arg03a2) {
  int var03a1 = 0;
  int var03a2 = arg03a1.find_first_of(arg03a2);
  std::vector<std::string> vector03a1;
  while (var03a1 < arg03a1.size()) {
    std::string subStr(arg03a1, var03a1, var03a2 - var03a1);
    vector03a1.push_back(subStr);
    var03a1 = var03a2 + 1;
    var03a2 = arg03a1.find_first_of(arg03a2, var03a1);
    if (var03a2 == std::string::npos) {
      var03a2 = arg03a1.size();
    }
  }
  return vector03a1;
}

std::vector<std::vector<std::string>> func_orig::func03b(std::string arg03b1, int arg03b2){
  std::ifstream var03b1;
  var03b1.open(arg03b1, std::ios::in);
  if(!var03b1){
    std::vector<std::vector<std::string>> vector03b1;
    return vector03b1;
  }
  std::string var03b2;
  for(int i = 0; i < arg03b2; ++i){
    std::getline(var03b1, var03b2);
    if(var03b1.eof()) break;
  }
  std::vector<std::vector<std::string>> vector03b2;
  while(std::getline(var03b1, var03b2)){
    if(var03b2.size() == 0) break;
    std::vector<std::string> vector03b3;
    vector03b3 = func_orig::func03a(var03b2, ',');
    vector03b2.push_back(vector03b3);
  }
  return vector03b2;
}