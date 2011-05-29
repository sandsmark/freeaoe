
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "src/file/DrsGraphics.h"

int main(int argc, char **argv) {
  std::cout << "Hello, world!" << std::endl;
    
  std::fstream file;
  
  file.open("../aoe2/Data/graphics.drs");
  
  DrsGraphics gr;
  
  gr.load(file);
  
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
 
         // Draw the string
 
         // Update the window
         App.Display();
     }
  return 0;
}
