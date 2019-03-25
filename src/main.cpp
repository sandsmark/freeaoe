/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include <filesystem>

#include "Engine.h"
#include "resource/DataManager.h"
#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"

#include "mechanics/UnitFactory.h"
#include "global/Config.h"
#include "render/GraphicRender.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "ui/FileDialog.h"
#include "audio/AudioPlayer.h"
#include "ui/HomeScreen.h"
#include "ui/HistoryScreen.h"
#include "debug/SampleGameFactory.h"

// TODO: Bad_alloc
int main(int argc, char **argv)
{
//    genie::Logger::setLogLevel(genie::Logger::L_DEBUG);

    Config config("freeaoe");
    config.setAllowedOptions({
            {"game-path", "Path to AoE installation with data files", Config::Stored },
            {"scenario-file", "Path to scenario file to load", Config::NotStored },
            {"single-player", "Path to scenario file to load", Config::NotStored },
            {"game-sample", "Game samples to load", Config::NotStored }
            });
    if (!config.parseOptions(argc, argv)) {
        return 1;
    }
    std::string dataPath = config.getValue("game-path") + "/Data/";

    if (!std::filesystem::exists(dataPath)) {
        FileDialog filediag;
        if (!filediag.setup(1024, 768)) {
            WARN << "failed to open file dialog!";
            return 1;
        }

        config.setValue("game-path", filediag.getPath());
    }

    dataPath = config.getValue("game-path") + "/Data/";

    if (!std::filesystem::exists(dataPath)) {
        WARN << "Game path " << dataPath << " does not exist";
        config.printUsage(argv[0]);
        return 1;
    }

    if (!LanguageManager::Inst()->initialize(config.getValue("game-path") + "/")) {
        return 1;
    }

    if (!DataManager::Inst().initialize(dataPath)) {
        return 1;
    }

    if (!AssetManager::Inst()->initialize(dataPath, DataManager::Inst().gameVersion())) {
        return 1;
    }

    AudioPlayer::instance();

    genie::ScnFilePtr scenarioFile;

    bool skipMenu = config.getValue("single-player") == "true" || !config.getValue("game-sample").empty();

    if (!skipMenu) {
        bool startGame = false;

        // TODO: clean up this mess...
        while (!startGame) {
            HomeScreen home;
            if (!home.init()) {
                return 1;
            }

            const HomeScreen::Button::Type button = home.getSelection();
            if (button == HomeScreen::Button::Exit) {
                return 0;
            } else if (button == HomeScreen::Button::History) {
                HistoryScreen history;
                if (!history.init(config.getValue("game-path") + "/History/")) {
                    return 1;
                }
                history.display();
            } else if (button == HomeScreen::Button::Tutorial) {
                startGame = true;
                try {
                    genie::CpxFile cpxFile;
                    cpxFile.setFileName(config.getValue("game-path") + "/Campaign/xcam3.cpx");
                    cpxFile.load();

                    scenarioFile = cpxFile.getScnFile(0);
                } catch (const std::exception &error) {
                    WARN << "Failed to load" << ":" << error.what();
                }
            } else if (button == HomeScreen::Button::Singleplayer) {
                startGame = true;
                if (home.getGameType() == HomeScreen::TextButton::Campaign) {
                    try {
                        genie::CpxFile cpxFile;
                        cpxFile.setFileName(config.getValue("game-path") + "/Campaign/xcam3.cpx");
                        cpxFile.load();

                        scenarioFile = cpxFile.getScnFile(0);
                    } catch (const std::exception &error) {
                        WARN << "Failed to load" << ":" << error.what();
                    }
                }
            } else {
                startGame = true;
                if (!config.getValue("scenario-file").empty()) {
                    try {
                        scenarioFile = std::make_shared<genie::ScnFile>();
                        scenarioFile->load(config.getValue("scenario-file"));
                    } catch (const std::exception &error) {
                        WARN << "Failed to load" << config.getValue("scenario-file") << ":" << error.what();
                    }
                }
                break;
            }
        }
    } else if (!config.getValue("game-sample").empty()) {
        const std::string alias = config.getValue("game-sample");
        SampleGameFactory::Inst().setSampleFromAlias(alias);
    }

    Engine en;
    if (!en.setup(scenarioFile)) {
        return 1;
    }

    en.start();

    return 0;
}
