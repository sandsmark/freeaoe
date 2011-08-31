
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include <global/Config.h>
#include <resource/ResourceManager.h>

#include <Engine.h>
#include <mechanics/Map.h>
#include <mechanics/MapRenderer.h>
#include <data/DataManager.h>
#include <render/RenderGraphic.h>
#include <file/DatFile.h>


// TODO: Bad_alloc

// The main function behaves now as a testbed, real code should not be written
// here.

int main(int argc, char **argv) 
{
  Logger::setLogLevel(Logger::L_INFO);
  
 // DatFile df;
 // df.open("aoe2/Data/empires2.dat");
  
  //Engine en;
  //en.start();
  
  ResourceManager::Inst();
  DataManager::Inst();
  sf::Clock clk;
 
  GenieGraphic gg = DataManager::Inst()->getGraphic(1972);//1128);
  RenderGraphic rg(&gg);
  rg.setX(100);
  rg.setY(150);
  
  Map map;
  map.setUpSample();
  
  sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");
  sf::View view(sf::FloatRect(0,0,300,300));
  
  MapRenderer render(&App);
  render.setMap(&map);
  
  bool pause = false;
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
             
             if (Event.Type == sf::Event::KeyReleased)
             {
                if (Event.Key.Code  == sf::Key::Space)
                  pause = !pause;
             }
         }

        if (!pause)
        {
         // Clear screen
         App.Clear();
 
         //App.SetView(view);
         // Draw the sprite
         render.Draw();
         
         rg.drawOn(&App);
         
         App.SetView(App.GetDefaultView());
 
         // Draw the string
 
         // Update the window
         App.Display();
        }
         
     }
     
  return 0;
}
