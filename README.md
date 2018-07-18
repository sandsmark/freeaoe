freeaoe
=======

![screenshot](/doc/screenshot.png)

Freeaoe is a project aimed to write a free engine capable of running Age of Empires 2.

The project is still in early development, but you can load scenarios and move around and stuff.

Windows
-------
Automated windows builds can be [downloaded from AppVeyor](https://ci.appveyor.com/project/sandsmark/freeaoe/build/artifacts).

In theory it should be able to automatically find the data files if AoE2 is installed, but I don't have windows so I haven't tested this.

Dependencies
------------
 - SFML
 - Modern C++ compiler

To build
--------
 - Clone with --recurse-submodules (e. g. `git clone --recurse-submodules https://github.com/sandsmark/freeaoe.git`)
 - `mkdir build && cd build`
 - `cmake .. && make`
 - `./freeaoe --game-path=~/.wine/drive_c/Program\ Files/Microsoft\ Games/Age\ of\ Empires\ II\ The\ Conquerors\ Expansion\ Trial/`
 - Adjust the path above (it should work with both the full games and trial edition)

