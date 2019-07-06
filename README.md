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

It uses the same library as [AGE (Advanced Genie Editor)](https://github.com/Tapsa/AGE), so it should be able
to handle anything that can be edited by that (and therefore basically all
community content created for AoE2).

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
 - `./freeaoe`

TODO (this is probably going to get outdated)
----
 - Scenario triggers.
 - Unit grouping/formations.
 - Patrolling.
 - Garrisoning.
 - AI Script execution (lot of overlap with scenarios).
 - Wall building.
 - Map analysis stuff (for RMS and AI).
 - Random map RMS script parsing and generating.
 - Performance (especially the path finding).
 - Various refactoring (move VisibilityMap out into separate file, rendering of units out from UnitManager, etc.)

Done
----
Not exhaustive list, mostly in addition to "normal" RTS things, or things not available in other re-implementations.

Compared to other reimplementations as much as possible is fetched from the data files as well, and I try to avoid hardcoding anything, though some is hardcoded in the original game.

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

