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

#include <genie/script/ScnFile.h>
#include <filesystem>
#include <memory>
#include <string>

#include "Engine.h"
#include "audio/AudioPlayer.h"
#include "core/Logger.h"
#include "core/Utility.h"
#include "debug/SampleGameFactory.h"
#include "global/Config.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "ui/FileDialog.h"
#include "ui/HistoryScreen.h"
#include "editor/Editor.h"
#include "debug/SampleGameFactory.h"

#include "ui/HomeScreen.h"

// TODO: Bad_alloc
int main(int argc, char **argv) try
{
    DBG << "executable path" << util::executablePath();

    Config config("freeaoe");
    config.setAllowedOptions({
            {"game-path", "Path to AoE installation with data files", Config::Stored },
            {"scenario-file", "Path to scenario file to load", Config::NotStored },
            {"single-player", "Launch a simple test map", Config::NotStored },
            {"game-sample", "Game samples to load", Config::NotStored }
            });
    if (!config.parseOptions(argc, argv)) {
        return 1;
    }
    std::string dataPath;

    do {
        try {
            if (config.getValue("game-path").empty()) {
                throw std::runtime_error("No data path set");
            }

            dataPath = config.getValue("game-path");
            if (!std::filesystem::exists(dataPath)) {
                throw std::runtime_error("Data path does not exist");
            }

            if (!LanguageManager::Inst()->initialize(config.getValue("game-path") + "/")) {
                throw std::runtime_error("Failed to load language.dll");
            }

            if (!DataManager::Inst().initialize(config.getValue("game-path"))) {
                throw std::runtime_error("Failed to load game data");
            }
            DBG << "Loaded game data";

            AssetManager::create(DataManager::Inst().isHd());
            if (!AssetManager::Inst()->initialize(dataPath, DataManager::Inst().gameVersion())) {
                throw std::runtime_error("Failed to load game assets");
            }

        } catch(const std::exception &e) {
            dataPath = "";

            std::string errorMessage;
            if (errno != 0) {
                errorMessage = strerror(errno);
            } else {
                errorMessage = e.what();
            }

            WARN << "failed to load:" << e.what() << strerror(errno);

            FileDialog filediag;
            if (!filediag.setup(1024, 768)) {
                WARN << "failed to open file dialog!";
                return 1;
            }
            filediag.setErrorString(e.what());

            const std::string selectedPath = filediag.getPath();
            if (selectedPath.empty()) {
                WARN << "user aborted";
                return 1;
            }

            config.setValue("game-path", selectedPath);
        }
    } while (!std::filesystem::exists(dataPath));

    AudioPlayer::instance();

    genie::ScnFilePtr scenarioFile;

    bool skipMenu = config.getValue("single-player") == "true" || !config.getValue("game-sample").empty();

    if (!skipMenu) {
        // TODO: clean up this mess...
        while (true) {
            HomeScreen home;
            if (!home.init()) {
                return 1;
            }

            const HomeScreen::Button::Type button = home.getSelection();
            if (button == HomeScreen::Button::Exit) {
                return 0;
            }

            if (button == HomeScreen::Button::History) {
                HistoryScreen history;
                if (!history.init(config.getValue("game-path") + "/History/")) {
                    continue;
                }

                history.display();

                continue;
            }

            if (button == HomeScreen::Button::MapEditor) {
                Editor editor;
                if (editor.init()) {
                    editor.run();
                } else {
                    WARN << "Failed to load editor";
                }

                continue;
            }

            if (button == HomeScreen::Button::Tutorial) {
                try {
                    genie::CpxFile cpxFile;
                    if (DataManager::Inst().isHd()){
                        cpxFile.setFileName(config.getValue("game-path") + "/resources/_common/drs/retail-campaigns/dlc0/kings/cam8.cpn");
                    } else {
                        cpxFile.setFileName(config.getValue("game-path") + "/Campaign/cam8.cpn");
                    }
                    cpxFile.load();

                    scenarioFile = cpxFile.getScnFile(0);
                } catch (const std::exception &error) {
                    WARN << "Failed to load" << ":" << error.what();
                    continue;
                }

                break;
            }

            if (button == HomeScreen::Button::Singleplayer) {
                if (home.getGameType() != HomeScreen::GameTypeChoice::Campaign) {
                    continue;
                }

                try {
                    genie::CpxFile cpxFile;
                    if (DataManager::Inst().isHd()){
                        cpxFile.setFileName(config.getValue("game-path") + "/resources/_common/drs/retail-campaigns/dlc0/conquerors/xcam3.cpn");
                    } else {
                        cpxFile.setFileName(config.getValue("game-path") + "/Campaign/xcam3.cpx");
                    }
                    cpxFile.load();

                    scenarioFile = cpxFile.getScnFile(0);
                } catch (const std::exception &error) {
                    WARN << "Failed to load" << ":" << error.what();
                }

                continue;
            }

            if (config.getValue("scenario-file").empty()) {
                break;
            }

            try {
                scenarioFile = std::make_shared<genie::ScnFile>();
                scenarioFile->load(config.getValue("scenario-file"));
            } catch (const std::exception &error) {
                WARN << "Failed to load" << config.getValue("scenario-file") << ":" << error.what();
            }
            break;
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
} catch (const std::exception &e) {
    std::cerr << "uncatched exception '" << e.what() << "', terminating uncleanly" << std::endl;
    return 1;
}
