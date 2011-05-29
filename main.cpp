
#include <iostream>
#include <fstream>

#include "src/file/DrsGraphics.h"

int main(int argc, char **argv) {
  std::cout << "Hello, world!" << std::endl;
    
  std::fstream file;
  
  file.open("../aoe2/Data/graphics.drs");
  
  DrsGraphics gr;
  
  gr.load(file);
  
  return 0;
}
