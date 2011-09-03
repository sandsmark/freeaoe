
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <global/Config.h>
#include <resource/ResourceManager.h>

#include <Engine.h>
#include <mechanics/Map.h>
#include <mechanics/MapRenderer.h>
#include <data/DataManager.h>
#include <render/RenderGraphic.h>
#include <file/DatFile.h>
#include <mechanics/Unit.h>
#include <render/RenderGame.h>
#include <mechanics/GameManager.h>
#include <mechanics/commands/CommandSpawn.h>


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
