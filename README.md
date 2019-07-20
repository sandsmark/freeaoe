freeaoe
=======

![screenshot](/doc/screenshot.png)

Freeaoe is a project to write a free engine capable of running Age of Empires 2
(and other Genie games).

The project is still in early development, but we can load basically all the
original data, and you can build, move around, load scenarios, show the
civilization history and stuff.

It (obviously) needs the original data files, but it should work with the data
files from the trial version (it's available e. g. from Archive.org).

It uses the same [library](https://github.com/sandsmark/genieutils) as [AGE
(Advanced Genie Editor)](https://github.com/Tapsa/AGE), so it should be able to
handle anything that can be edited by that (and therefore basically all
community content created for AoE2). Because of this it doesn't need to unpack
or convert anything, all data files are used as is.

Windows
-------
Automated windows builds can be [downloaded from AppVeyor](https://ci.appveyor.com/project/sandsmark/freeaoe/build/artifacts).

There is no installation, it's just a zip file with a standalone .exe that you
run.

NB: If Appveyor says there's no artifact available it's probably because it's
building the latest version, just give it a few moments (or click around in
AppVeyor to find the older versions).


Caveat emptor; I don't have any Windows installation to test with, but it
works fine in Wine.

Running
-------

If you have AoE2 installed it should automatically detect where it is installed
and load the data files automatically (looking up in the Windows registry). If
that doesn't work for some reason it will pop up a dialog where you can point
it to the files manually.

If you don't have it installed there's a nice button in that dialog which opens
[an URL](https://archive.org/details/AgeOfEmpiresIiTheConquerorsDemo) where you
can download the trial version of AoC. It doesn't have the higher resolution
graphics e. g. for the UI, though, so I highly recommend getting an original CD
with the full version.



On Linux it parses the Wine registry file to try to find the installation,
otherwise you get the same dialog (but with a handy button to go directly to
the .wine folder). Be aware that it respects WINEPREFIX, so make sure that is
set correctly if you use it.


Dependencies
------------
 - SFML
 - Modern C++ compiler

To build
--------
 - Clone with --recurse-submodules (e. g. `git clone --recurse-submodules https://github.com/sandsmark/freeaoe.git`)
 - `mkdir build && cd build`
 - `cmake .. && make`
 - `./freeaoe`

TODO (this is probably going to get outdated)
----
 - Proper victory screen.
 - Unit grouping/formations.
 - Patrolling.
 - Garrisoning.
 - AI Script execution (lot of overlap with scenario triggers).
 - (Proper) wall building.
 - Campaign cinematics (mainly just parse the .mm files).
 - Streaming sound (music, scenario voices, etc.).
 - Map analysis stuff (for RMS and AI).
 - Random map RMS script parsing and generating.
 - Performance (especially the path finding).
 - Various refactoring (move VisibilityMap out into separate file, rendering of units out from UnitManager, etc.)

Done
----
Not exhaustive list, mostly in addition to "normal" RTS things, or things not available in other re-implementations.

Compared to other reimplementations as much as possible is fetched from the data files as well, and I try to avoid hardcoding anything, though some is hardcoded in the original game.

 * Scenarios:
    * Loading and parsing old and new scenario files (.scn and .scx)
    * Loading and parsing old and new campaign files (.cpn and .cpx)
    * All scenario trigger conditions and effects necessary to play the William Wallace tutorial scenario.
 * Villagers:
    * Automatic switching between builders, lumberjacks, etc.
    * Carrying resource tracking.
 * Units:
    * Dying animations.
    * Creating corpses on death.
    * Decaying corpses.
    * Visibility tracking.
    * Default actions on right click.
 * Buildings:
    * Construction of buildings.
    * Training units.
 * Actions types:
    * Melee attacks.
    * Ranged attacks.
    * Building (buildings).
    * Moving (on land and arrows/missiles).
    * Gathering, with automatic dropoff.
    * Construction.
    * Flying (birds).
 * Technology:
    * Research.
    * Automatic research of implicit technologies.
    * Unique technologies.
    * Ages with list of techs.
 * Actions:
    * Automatic actions (attacking nearby etc.)
    * Fetching actions for the action panel at the bottom from data files.
    * Queueing.
 * Terrain rendering:
    * Slopes/hills.
    * Blending terrain between tiles.
    * Fog of war.
 * Unit rendering:
    * Animations.
    * Angles.
    * Unit outline when behind buildings (needs improvement).
    * Health bar.
    * Selection outline.
    * Player colors.
    * Construction available/unavailable graphics.
    * Shadows.
    * Fog of war shading.
 * Sound:
    * Sound on selection.
    * Sound when attacking.
    * Sound when dying.
    * Sound when training units.
    * Positional.
 * Civilizations:
    * Starting resources.
    * Different UI interface graphics.
    * Names.
 * Players:
    * Civs.
    * Colors.
    * Ages.
    * Techs.
    * Alliances.
    * Per player visibility.
 * Game assets:
    * Graphics.
    * Palettes.
    * Sounds.
    * Campaign files.
    * Scenario files.
    * Terrain blending files.
    * Terrain hill shape/lightning files.
    * UI interface files.
    * Fog of war graphics.
    * AI script parsing.
    * Support for loading basically everything.
    * Use only original files, don't convert.
 * Game data files:
    * Graphic info.
    * Sound info (randomness of sounds etc.)
    * Unit tasks.
    * Player colors.
    * Techs.
    * Terrain info.
    * Maps.
    * Civilizations.
    * UI info files (button colors etc.)
    * Random map files (not .rms).
    * Automatic location of game files if installed (Windows and Linux).
 * UI interface:
    * Unit info panel.
    * Unit actions panel.
    * Resource info labels.
    * In game buttons/menu.
    * Home screen.
    * History screen.
    * Dialog when starting to find game data.
 * Minimap:
    * Terrain colors.
    * Unit colors.
    * Unit outline types (rectangles vs. diamonds etc.)
    * Unit outline sizes.
    * Fog of war.
    * Camera moving.

