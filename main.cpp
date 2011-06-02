
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include <global/Config.h>
#include <resource/ResourceManager.h>

int main(int argc, char **argv) {
  
  //DrsGraphics gr;
  //gr.load(file);
  
  sf::Sprite spr;
  spr.SetX(200);
  spr.SetY(200);
  
  ResourceManager::Inst();
  std::auto_ptr<Graphic> ptr = ResourceManager::Inst()->getGraphic(50100);
  spr.SetImage( *ptr->getImage() );
  
   // Create the main window
  sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");
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
 
         // Draw the sprite
         App.Draw(spr);
 
         // Draw the string
 
         // Update the window
         App.Display();
     }
     
  Config::Destroy();
  return 0;
}
