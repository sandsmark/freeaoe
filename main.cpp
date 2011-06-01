
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "src/file/DrsGraphics.h"
#include "src/global/Config.h"

int main(int argc, char **argv) {
  std::cout << "Hello, world!" << std::endl;
    
  std::fstream file;
  
  file.open(std::string(Config::Inst()->getDataPath() + "terrain.drs").c_str());
  
  DrsGraphics gr;
  gr.load(file);
  
  sf::Sprite spr;
  spr.SetX(200);
  spr.SetY(200);
  spr.SetImage(*gr.image_);
  
  //gr.load(file);
  /*
  sf::Image img(2,2);
  
  img.SetPixel(0,0, sf::Color(255,100,50));
  img.SetPixel(1,0, sf::Color(0,0,50));
  img.SetPixel(0,1, sf::Color(55,10,50));
  img.SetPixel(1,1, sf::Color(55,0,50));
  
  const sf::Uint8 *pptr = img.GetPixelsPtr();
  std::cout << "a: " << (int)pptr[0] << " " << (int)pptr[3] << std::endl;
  */
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
