
#include <iostream>
#include <fstream>

#include "src/file/DrsReader.h"

int main(int argc, char **argv) {
  std::cout << "Hello, world!" << std::endl;
    
  std::fstream file;
  
  file.open("../aoe2/Data/graphics.drs");
  
  DrsReader drs;
  
  drs.read(file);
  
  return 0;
}
