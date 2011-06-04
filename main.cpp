
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include <global/Config.h>
#include <resource/ResourceManager.h>

#include <genied.h>
#include <Engine.h>
#include <mechanics/Map.h>
#include <mechanics/MapRenderer.h>

int main(int argc, char **argv) 
{
  Logger::setLogLevel(Logger::L_INFO);
  
  Engine en;
  en.run();
  
  ResourceManager::Inst();
  
  Map map;
  map.setUpSample();
  
  sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");
  
  MapRenderer render(&App);
  render.setMap(&map);
  
  GenieFile gf;
  
  gf.LoadGenie("../aoe2/Data/empires2_x1.dat");
  gf.ReadUnitsData();
  
  std::cout << gf.Civs.front()->Title << std::endl;
  
  sf::Sprite spr;
  spr.SetX(200);
  spr.SetY(200);
  
  std::auto_ptr<Graphic> ptr = ResourceManager::Inst()->getGraphic(5);
  std::auto_ptr<Graphic> ptr2 = ResourceManager::Inst()->getGraphic(5);
  spr.SetImage( *ptr->getImage() );

  

   // Start the game loop
     while (App.IsOpened())
     {
         // Process events
         sf::Event Event;
         while (App.GetEvent(Event))
         {
             // Close window : exit
             if (Event.Type == sf::Event::Closed)
                 App.Close();
         }
 
         // Clear screen
         App.Clear();
 
         App.SetView(render.GetView());
         // Draw the sprite
         App.Draw(spr);
         render.Draw();
 
         // Draw the string
 
         // Update the window
         App.Display();
     }
     
  Config::Destroy();
  return 0;
}
