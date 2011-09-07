
#include <iostream>

#include <Engine.h>

// TODO: Bad_alloc

// The main function behaves now as a testbed, real code should not be written
// here.

int main(int argc, char **argv)
{
  Logger::setLogLevel(Logger::L_INFO);
  
 // DatFile df;
 // df.open("aoe2/Data/empires2.dat");
  
  Engine en;
  en.start();

  return 0;
}
