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

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>

#include <genie/Types.h>
#include <genie/resource/Slope.h>

class TerrainSprite;
class Sprite;

namespace genie {
class DrsFile;
class PalFile;
class UIFile;
class SlpFile;
class PatternMasksFile;
class FiltermapFile ;
struct BlendMode;
class BlendomaticFile;
class ScnFile;
class SlpTemplateFile;
template<int EdgeCount> class EdgeFile;
struct VisibilityMask;
}

// genie
using DrsFilePtr = std::shared_ptr<genie::DrsFile>;
using DrsFileVector = std::vector<DrsFilePtr>;
using SlpFilePtr = std::shared_ptr<genie::SlpFile>;
using PatternMasksFilePtr = std::shared_ptr<genie::PatternMasksFile>;
using FiltermapFilePtr = std::shared_ptr<genie::FiltermapFile>;
using ScnFilePtr = std::shared_ptr<genie::ScnFile>;
using SlpTemplateFilePtr = std::shared_ptr<genie::SlpTemplateFile>;
using BlendomaticFilePtr = std::shared_ptr<genie::BlendomaticFile>;
using TileEdgeFile = genie::EdgeFile<94>;
using TileEdgeFilePtr = std::shared_ptr<TileEdgeFile>;
using BlkEdgeFile = genie::EdgeFile<47>;
using BlkEdgeFilePtr = std::shared_ptr<BlkEdgeFile>;

// ours
using SpritePtr = std::shared_ptr<Sprite>;
using GraphicMap = std::unordered_map<uint32_t, SpritePtr>;
using TerrainPtr = std::shared_ptr<TerrainSprite>;
using TerrainMap = std::unordered_map<uint32_t, TerrainPtr>;

//------------------------------------------------------------------------------
/// The resource manager is the primary interface for getting recourses. At
//
class AssetManager
{
public:
    enum UiResolution {
        Ui800x600 = 51100,
        Ui1024x768 = 51120,
        Ui1280x1024 = 51140,
        Ui1600x1200 = 51150
    };

    enum class ResourceType {
        Undefined,
        GameData,
        Interface,
        Graphics,
        Terrain,
    };
    enum class StandardSlpType {
        Buildings,
        Units,
        Technology,
        Commands
    };

    enum UiCiv : int {
        Invalid = 0,
        Briton = 1,
        Frank = 2,
        Goth = 3,
        Teuton = 4,
        Japanese = 5,
        Chinese = 6,
        Byzantine = 7,
        Persian = 8,
        Saracen = 9,
        Turkish = 10,
        Viking = 11,
        Mongol = 12,
        Celtic = 13,
        Spanish = 14,
        Aztec = 15,
        Mayan = 16,
        Hunnic = 17,
        Korean = 18,
    };

    enum UiCiv_SWGB : int {
        GalacticEmpire = 1,
        Gungans = 2,
        RebelAlliance = 3,
        RoyalNaboo = 4,
        TradeFederation = 5,
        Wookies = 6,
    };

    static std::string uiFilename(const UiResolution resolution, const UiCiv civ);

    AssetManager(const AssetManager &) = default;
    AssetManager &operator=(const AssetManager &) = delete;

    //----------------------------------------------------------------------------
    /// Initializes the resource manager once and returns its reference. On
    /// calling inst the first time the manager will load header information from
    /// drs and other files.
    //
    static void create(const bool isHd);
    static const std::unique_ptr<AssetManager> &Inst();

    //----------------------------------------------------------------------------
    /// Returns the slp file with given id or 0 if not found. The slp file
    /// should not be deleted!
    ///
    /// @param id id of the slp file
    /// @return slp file
    //
    virtual SlpFilePtr getSlp(uint32_t id, const ResourceType type = ResourceType::Undefined);
    virtual SlpFilePtr getSlp(const std::string &name, const ResourceType type = ResourceType::Undefined);
    virtual SlpFilePtr getInterfaceSlp(const StandardSlpType type, const int playerCiv);

    virtual SlpFilePtr getUiOverlay(const UiResolution res, const UiCiv civ);

    ScnFilePtr getScn(uint32_t id);

    virtual std::shared_ptr<genie::UIFile> getUIFile(const std::string &name);

    std::shared_ptr<uint8_t[]> getWavPtr(uint32_t id);

    const SlpTemplateFilePtr &getSlpTemplateFile() { return m_stemplatesFile; }
    const FiltermapFilePtr &filtermapFile() { return m_filtermapFile; }
    const PatternMasksFilePtr &patternmasksFile() { return m_patternmasksFile; }

    //----------------------------------------------------------------------------
    /// Get a Graphic resource object.
    ///
    /// @param id id of the resource
    /// @return ImagePtr pointing to the object
    //
    SpritePtr getGraphic(uint32_t id);

    //----------------------------------------------------------------------------
    /// Get a Terrain resource object.
    ///
    /// @param id id of the resource
    /// @return resource pointer to the object
    //
    const TerrainPtr &getTerrain(uint32_t id);

    const genie::PalFile &getPalette(const std::string &name);
    virtual const genie::PalFile &getPalette(uint32_t id = 50500);

    const genie::BlendMode &getBlendmode(uint32_t id = 0);

    const genie::VisibilityMask &unexploredVisibilityMask(const genie::Slope slope, int edges) const;
    const genie::VisibilityMask &exploredVisibilityMask(const genie::Slope slope, int edges) const;

    virtual bool initialize(const genie::GameVersion gameVersion);

    static int filenameID(const std::string &filename);

    size_t terrainCacheSize() const;

    static std::string findFile(const std::string &filename, const std::string &folder);

    virtual const std::string &assetsPath() const;
    virtual std::string soundsPath() const;
    virtual std::string streamsPath() const;

    virtual bool missingData() const;

protected:
    friend struct std::default_delete<AssetManager>;
    friend std::unique_ptr<AssetManager> std::make_unique<AssetManager>();
    AssetManager() = default;
    virtual ~AssetManager() = default;

    virtual std::string blendomaticFilename() const { return "blendomatic.dat"; }

    bool initializeInternal(const std::string &dataPath, const genie::GameVersion gameVersion);

private:
    DrsFileVector loadDrs(const std::vector<std::string> &filenames);
    DrsFilePtr loadDrs(const std::string &filename);

    DrsFileVector m_gamedataFiles;
    DrsFileVector m_soundFiles;

    DrsFileVector m_interfaceFiles;
    DrsFilePtr m_graphicsFile;
    DrsFilePtr m_terrainFile;

    DrsFileVector m_allFiles;

    BlendomaticFilePtr blendomatic_file_;

    SlpTemplateFilePtr m_stemplatesFile;
    FiltermapFilePtr m_filtermapFile;
    PatternMasksFilePtr m_patternmasksFile;

    TileEdgeFilePtr m_tileEdgeFile;

    BlkEdgeFilePtr m_blkEdgeFile;

    //TODO: All resources into one map?
    GraphicMap graphics_;

    TerrainMap terrains_;

    std::unordered_map<uint32_t, std::weak_ptr<uint8_t[]>> m_wavCache;

    genie::GameVersion m_gameVersion;
    std::string m_dataPath;
    std::string m_gamePath;
    std::unordered_set<uint32_t> m_nonExistentSlps;

    static std::unique_ptr<AssetManager> m_instance;
};

