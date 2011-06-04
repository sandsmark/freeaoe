
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include <global/Config.h>
#include <resource/ResourceManager.h>

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
  sf::View view(sf::FloatRect(0,0,300,300));
  
  MapRenderer render(&App);
  render.setMap(&map);
  
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
 
         App.SetView(view);
         // Draw the sprite
         render.Draw();
         
         App.SetView(App.GetDefaultView());
         
         App.Draw(spr);
 
         // Draw the string
 
         // Update the window
         App.Display();
     }
     
  Config::Destroy();
  return 0;
}
