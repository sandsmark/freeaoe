freeaoe
=======

![screenshot](/doc/screenshot.png)

freeaoe is a project to write a free engine capable of running Age of Empires 2
(and other Genie games like SW:GB eventually).

The project is still in early development. But you can load and play scenarios,
show the history screen, move around, attack, build and stuff.  There are some
screenshots in the [doc/](doc/) folder.

It (obviously) needs the original data files, but it works with the data
files from the trial version (e. g. from Archive.org).


Windows
-------
Automated Windows builds can be [downloaded from AppVeyor](https://ci.appveyor.com/project/sandsmark/freeaoe/build/artifacts).

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

I can't get it to build on macOS (and I don't have any Apple machines), so if
you manage to get it to build please open a PR. It seems like Apple ships a
really outdated version of Clang that doesn't support modern C++.


Legal
-----
Preface: I am not a lawyer (nor a native english speaker), this is just based
on my interpretation of local laws to show that everything is done in good
faith. If you believe I am infringing on any of your rights please open an
issue and I will seek to rectify it as soon as possible.


I am in no way affiliated with Microsoft, Linus Torvalds nor anyone else who own
any trademarks that may appear here. Any display of trademarks here is purely
to indicate the purpose of this project and in accordance with good business
practice, as permitted by relevant laws.

There are no copyrighted works distributed here, nor works derived from
copyrighted works, except works with a free and open source license permitting
distribution.

*In no part of the creation of this is reverse engineering involved*. All
insight used is based on publicly available knowledge and playing of the game.

My right to gather insight into the functioning and principles of individiual
parts of a copyrighted computer program by means of execution, observation,
investigation and testing is [protected by norwegian law](https://lovdata.no/lov/2018-06-15-40/§41).

Although I also have some rights to reverse engineer works I have the right to
use it's more fun to figure out how to do something myself. In addition I'm
not familiar enough with the laws governing reverse engineering that Github is
subject to, and I don't want to be nuked from Github.


In general I work on this this because it's fun to create a strategy game, I
already paid for and own a license to the games. I do not receive nor do I
intend to receive any form of compensation for this. I have no incentive or
intention to do anything that would infringe on anyones copyright, trademarks
or other rights.


Misc
----

This is mostly a single-person pet project, so if you want a more serious project,
try [openage](https://openage.sft.mx/).

It uses the same [library](https://github.com/sandsmark/genieutils) as [AGE
(Advanced Genie Editor)](https://github.com/sandsmark/AGE), so it should be able to
handle anything that can be edited by that (and therefore basically all
community content created for AoE2). Because of this it doesn't need to unpack
or convert anything, all data files are used as is.

This repo is originally a fork of https://github.com/apreiml/freeaoe, but
because a lot of stuff doesn't like working on forked repos it is now created
as a separate repo.


TODO (this is probably going to get outdated)
----
 - Proper victory screen.
 - Unit grouping/formations.
 - Patrolling.
 - Campaign cinematics (mainly just parse the .mm files).
 - Random map RMS script parsing and generating.
 - Performance (especially the path finding).
 - Various refactoring (move VisibilityMap out into separate file, rendering of units out from UnitManager, etc.)
 - Fix edges of walls when dragging.
 - Rest of AI script actions and conditions:
    - town-under-attack
    - cc-players-unit-type-count (AI cheat)
    - game-time
    - timer-triggered
    - difficulty
    - dropsite-min-distance
    - resource-found
    - players-stance
 - Angle of arrows
 - Arrows stuck in the ground
 - Upscale shaders (WIP in the `martin/lolshaders` branch)
 - MIDI support, for music in the trial versions (WIP in the `martin/midi` branch)
 - Video support, intro videos etc. (WIP in the `martin/video` branch)

Wishlist/low priority:
 - Proper support for new terrain graphics (Rise of the Rajas stopped shipping the old ones).
 - Map analysis stuff (for RMS and AI).

Done
----
Not exhaustive list, mostly in addition to "normal" RTS things, or things not available in other re-implementations.

Compared to other reimplementations as much as possible is fetched from the data files as well, and I try to avoid hardcoding anything, though some is hardcoded in the original game.

 * HD Support.
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
    * Garrisoning.
    * Ungarrisoning.
 * Buildings:
    * Construction of buildings.
    * Training units.
    * Dragging wall construction.
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
    * Dopplegangers (i. e. persist last seen buildings. etc in fog of war).
 * Sound:
    * Sound on selection.
    * Sound when attacking.
    * Sound when dying.
    * Sound when training units.
    * Positional.
    * Streaming sound (scenario voices, music, etc.).
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
 * AI scripts (partial)
   * Can fully parse scripts, with all tokens recognised.
   * Most conditions implemented.
   * Most actions implemented.

