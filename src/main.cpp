/*
    Main entry point.
    Copyright (C) 2017-2020 Martin Sandsmark <martin.sandsmark@kde.org>

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
#include <genie/util/Utility.h>
#include <genie/util/Logger.h>

#include "ui/HomeScreen.h"

#ifdef _WIN32
#include <windows.h>
static HANDLE s_stdoutHandle;
static DWORD s_outModeInit;
static void fixWindowsConsole()
{
    DWORD outMode = 0;
    s_stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(s_stdoutHandle == INVALID_HANDLE_VALUE) {
        puts("failed to get stdout handle");
    }

    if(!GetConsoleMode(s_stdoutHandle, &outMode)) {
        puts("failed to get windows console mode");
    }

    s_outModeInit = outMode;

    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(s_stdoutHandle, outMode)) {
        puts("Failed to set console mode");
    }
}
static void restoreWindowsConsole()
{
    if(!SetConsoleMode(s_stdoutHandle, s_outModeInit)) {
        puts("Failed to restore windows console mode");
    }
}
#endif

static void initData()
{
    if (!Config::Inst().isOptionSet(Config::GamePath)) {
        throw std::runtime_error("No data path set");
    }

    const std::string dataPath = Config::Inst().getValue(Config::GamePath);
    if (!std::filesystem::exists(dataPath)) {
        throw std::runtime_error("Data path does not exist");
    }

    if (!LanguageManager::Inst()->initialize()) {
        throw std::runtime_error("Failed to load language.dll");
    }

    if (!DataManager::Inst().initialize()) {
        throw std::runtime_error("Failed to load game data");
    }
    DBG << "Loaded game data";

    // reinits if already inited
    AssetManager::create(DataManager::Inst().isHd());

    if (!AssetManager::Inst()->initialize(DataManager::Inst().gameVersion())) {
        throw std::runtime_error("Failed to load game assets");
    }
}

static bool showHomeScreen(genie::ScnFilePtr *scenarioFile)
{
    Config &config = Config::Inst();

    // TODO: clean up this mess...
    while (true) {
        HomeScreen home;
        if (!home.init()) {
            return false;
        }

        const HomeScreen::Button::Type button = home.getSelection();
        if (button == HomeScreen::Button::Exit) {
            return false;
        }

        if (button == HomeScreen::Button::History) {
            HistoryScreen history;
            if (!history.init(AssetManager::Inst()->historyFilesPath())) {
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
            genie::CpxFile cpxFile;
            cpxFile.setFileName(genie::util::resolvePathCaseInsensitive("cam8.cpn", AssetManager::Inst()->campaignsPath()));

            try {
                cpxFile.load();

                *scenarioFile = cpxFile.getScnFile(0);
            } catch (const std::exception &error) {
                WARN << "Failed to load " << cpxFile.getFileName() << ":" << error.what();
                continue;
            }

            break;
        }

        if (button == HomeScreen::Button::Singleplayer) {
            if (home.getGameType() != HomeScreen::GameTypeChoice::Campaign) {
                break;
            }


            std::string campaignFile;
            if (DataManager::Inst().isHd()){
                campaignFile = config.getValue(Config::GamePath) + "/resources/_common/drs/retail-campaigns/dlc0/conquerors/xcam3.cpn";
            } else {
                campaignFile = config.getValue(Config::GamePath) + "/Campaign/xcam3.cpx";
            }

            genie::CpxFile cpxFile;
            cpxFile.setFileName(genie::util::resolvePathCaseInsensitive(campaignFile));

            try {
                cpxFile.load();

                *scenarioFile = cpxFile.getScnFile(0);
                break;
            } catch (const std::exception &error) {
                WARN << "Failed to load " << cpxFile.getFileName() << ":" << error.what();
            }

            break;
        }

        if (!config.isOptionSet(Config::ScenarioFile)) {
            break;
        }

        try {
            *scenarioFile = std::make_shared<genie::ScnFile>();
            (*scenarioFile)->load(config.getValue(Config::ScenarioFile));
        } catch (const std::exception &error) {
            WARN << "Failed to load" << config.getValue(Config::ScenarioFile) << ":" << error.what();
            continue;
        }
        break;
    }

    return true;
}

static bool requestFilePath(const std::string &errorMessage)
{
    Config &config = Config::Inst();

    FileDialog filediag;
    if (!filediag.setup(1024, 768)) {
        WARN << "failed to open file dialog!";
        return false;
    }
    filediag.setErrorString(errorMessage);

    const std::string selectedPath = filediag.getPath();
    if (selectedPath.empty()) {
        WARN << "user aborted";
        return false;
    }

    config.setValue(Config::GamePath, selectedPath);

    return true;
}

int main(int argc, char **argv)
#ifdef NDEBUG
try
#endif
{
#ifdef _WIN32
    fixWindowsConsole();
#endif
    for (int i=1; i<argc; i++) {
        if (std::string(argv[i]) == "--debug") {
            LogPrinter::enableAllDebug = true;
            genie::Logger::setLogLevel(genie::Logger::L_INFO);
            break;
        }
    }
    if (!LogPrinter::enableAllDebug) {
        genie::Logger::setLogLevel(genie::Logger::L_WARNING);
    }
    DBG << "executable path" << util::executablePath() << "folder:" << util::executableDirectory();

    Config &config = Config::Inst();

    if (!config.parseOptions(argc, argv)) {
        return 1;
    }

    while (true) {
        try {
            initData();
            break;
        } catch(const std::exception &e) {
            WARN << "failed to load:" << e.what() << strerror(errno);

            std::string errorMessage = e.what();
            if (errorMessage.empty() && errno != 0) {
                errorMessage = strerror(errno);
            }

            if (!requestFilePath(errorMessage)) {
                return 1;
            }
        }
    }

    AudioPlayer::instance();

    genie::ScnFilePtr scenarioFile;

    if (!config.isOptionSet(Config::GameSample) && !config.isOptionSet(Config::SinglePlayer)) {
        if (!showHomeScreen(&scenarioFile)) {
            return 0;
        }

    }

    Engine engine;
    if (!engine.setup(scenarioFile)) {
        return 1;
    }

    engine.start();
#ifdef _WIN32
    restoreWindowsConsole();
#endif

    return 0;
}
#ifdef NDEBUG
 catch (const std::exception &e) {
    std::cerr << "uncatched exception '" << e.what() << "', terminating uncleanly" << std::endl;
    return 1;
}
#endif
