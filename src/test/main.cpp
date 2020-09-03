#include <genie/script/ScnFile.h>
#include <genie/util/Utility.h>
#include <genie/util/Logger.h>
#include <filesystem>
#include <memory>
#include <string>

#include "core/Logger.h"
#include "global/Config.h"
#include "mechanics/Map.h"
#include "mechanics/MapTile.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "resource/TerrainSprite.h"

void testLoadTiles()
{
    DBG << "Testing map rendering speed";

    genie::CpxFile cpxFile;
    cpxFile.setFileName(genie::util::resolvePathCaseInsensitive(Config::Inst().getValue(Config::GamePath) + "/Campaign/cam8.cpn"));
    //cpxFile.setFileName(std::string(gamePath) + "/Campaign/xcam3.cpx");
    cpxFile.load();

    genie::ScnFilePtr scenarioFile = cpxFile.getScnFile(0);

    Map map;
    map.create(scenarioFile->map);
    map.updateMapData();

    DBG << "Timing how long it takes to generate textures for all tiles";

    {
        TIME_THIS;
        for (int col = 0; col < map.columnCount(); col++) {
            for (int row = 0; row < map.rowCount(); row++) {
                MapTile &tile = map.getTileAt(col, row);
                TerrainPtr terrain = AssetManager::Inst()->getTerrain(tile.terrainId);
                terrain->texture(tile, nullptr);
            }
        }
    }
    DBG << "Cache size/rendered tiles" << AssetManager::Inst()->terrainCacheSize();

    DBG << "Timing fetching from cache (less than 10ms isn't printed)";

    {
        TIME_THIS;
        for (int col = 0; col < map.columnCount(); col++) {
            for (int row = 0; row < map.rowCount(); row++) {
                MapTile &tile = map.getTileAt(col, row);
                TerrainPtr terrain = AssetManager::Inst()->getTerrain(tile.terrainId);
                terrain->texture(tile, nullptr);
            }
        }
    }

}

int main(int argc, char *argv[]) try
{
    if (argc < 2)  {
        WARN << "Please pass path to game installation directory";
        return 1;
    }
    genie::Logger::setLogLevel(genie::Logger::L_INFO);

    const char *gamePath = argv[1];
    Config::Inst().testMode = true;
//    std::string gamePath(argv[1]);
    //std::string dataPath = std::string(gamePath) + "/Data/";
    try {
        if (!std::filesystem::exists(gamePath)) {
            throw std::runtime_error("Data path does not exist");
        }
        Config::Inst().setValue(Config::GamePath, gamePath);

        if (!LanguageManager::Inst()->initialize()) {
            throw std::runtime_error("Failed to load language.dll");
        }

        if (!DataManager::Inst().initialize()) {
            throw std::runtime_error("Failed to load game data");
        }

        DBG << "create";
        AssetManager::create(DataManager::Inst().isHd());
        DBG << "created";

        if (!AssetManager::Inst()->initialize(DataManager::Inst().gameVersion())) {
            throw std::runtime_error("Failed to load game assets");
        }
    } catch(const std::exception &e) {
        gamePath = "";
        WARN << "failed to load data:" << e.what();
        return 1;
    }
    DBG << "Successfully loaded data files";

    testLoadTiles();

    return 0;
} catch(const std::exception &e) {
    puts(e.what());
    return 1;
}

