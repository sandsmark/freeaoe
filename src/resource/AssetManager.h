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

#include <genie/Types.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>

#include <genie/resource/Slope.h>

class ColorPalette;
class BinaFile;

class TerrainSprite;
typedef std::shared_ptr<TerrainSprite> TerrainPtr;

class Graphic;
using GraphicPtr = std::shared_ptr<Graphic>;


namespace genie {
class DrsFile;
class PalFile;
class UIFile;
class SlpFile;

class FiltermapFile ;
using FiltermapFilePtr = std::shared_ptr<FiltermapFile>;

class PatternMasksFile;
using PatternMasksFilePtr = std::shared_ptr<PatternMasksFile>;

class LightmapFile;
typedef std::shared_ptr<SlpFile> SlpFilePtr;

class IcmFile;
typedef std::shared_ptr<IcmFile> IcmFilePtr;

struct BlendMode;
class BlendomaticFile;
typedef std::shared_ptr<BlendomaticFile> BlendomaticFilePtr;

class ScnFile;
typedef std::shared_ptr<ScnFile> ScnFilePtr;

class SlpTemplateFile;
using SlpTemplateFilePtr = std::shared_ptr<SlpTemplateFile>;


template<int EdgeCount> class EdgeFile;

using TileEdgeFile =  EdgeFile<94>;
using TileEdgeFilePtr = std::shared_ptr<TileEdgeFile>;
using BlkEdgeFile = EdgeFile<47>;
using BlkEdgeFilePtr = std::shared_ptr<BlkEdgeFile>;

struct VisibilityMask;
}

//------------------------------------------------------------------------------
/// The resource manager is the primary interface for getting recourses. At
//
class AssetManager
{
private:
    AssetManager() = default;
    virtual ~AssetManager() = default;

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

    enum UiCiv : int {
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

    static std::string uiFilename(const UiResolution resolution, const UiCiv civ);

    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;

    //----------------------------------------------------------------------------
    /// Initializes the resource manager once and returns its reference. On
    /// calling inst the first time the manager will load header information from
    /// drs and other files.
    //
    static AssetManager *Inst();

    //----------------------------------------------------------------------------
    /// Returns the slp file with given id or 0 if not found. The slp file
    /// should not be deleted!
    ///
    /// @param id id of the slp file
    /// @return slp file
    //
    genie::SlpFilePtr getSlp(uint32_t id, const ResourceType type = ResourceType::Undefined);
    genie::SlpFilePtr getSlp(const std::string &name, const ResourceType type = ResourceType::Undefined);

    genie::SlpFilePtr getUiOverlay(const UiResolution res, const UiCiv civ);

    genie::ScnFilePtr getScn(uint32_t id);

    std::shared_ptr<genie::UIFile> getUIFile(const std::string &name);

    std::shared_ptr<uint8_t[]> getWavPtr(uint32_t id);

    const genie::SlpTemplateFilePtr &getSlpTemplateFile() { return m_stemplatesFile; }
    const genie::FiltermapFilePtr &filtermapFile() { return m_filtermapFile; }
    const genie::PatternMasksFilePtr &patternmasksFile() { return m_patternmasksFile; }

    //----------------------------------------------------------------------------
    /// Get a Graphic resource object.
    ///
    /// @param id id of the resource
    /// @return ImagePtr pointing to the object
    //
    GraphicPtr getGraphic(uint32_t id);

    //----------------------------------------------------------------------------
    /// Get a Terrain resource object.
    ///
    /// @param id id of the resource
    /// @return resource pointer to the object
    //
    const TerrainPtr &getTerrain(uint32_t id);

    const genie::PalFile &getPalette(const std::string &name);
    const genie::PalFile &getPalette(uint32_t id = 50500);

    const genie::BlendMode &getBlendmode(uint32_t id = 0);

    const genie::VisibilityMask &unexploredVisibilityMask(const genie::Slope slope, int edges) const;
    const genie::VisibilityMask &exploredVisibilityMask(const genie::Slope slope, int edges) const;

    bool initialize(const std::string &gamePath, const genie::GameVersion gameVersion);

    static int filenameID(const std::string &filename);

    size_t terrainCacheSize() const;

    static std::string findFile(const std::string &filename, const std::string &folder);

    const std::string &assetsPath() const;

     bool missingData() const;

private:
    std::string findHdFile(const std::string &filename) const;

    typedef std::vector<std::shared_ptr<genie::DrsFile>> DrsFileVector;
    DrsFileVector loadDrs(const std::vector<std::string> &filenames);
    std::shared_ptr<genie::DrsFile> loadDrs(const std::string &filename);

    DrsFileVector m_gamedataFiles;
    DrsFileVector m_soundFiles;

    std::shared_ptr<genie::DrsFile> m_interfaceFile;
    std::shared_ptr<genie::DrsFile> m_graphicsFile;
    std::shared_ptr<genie::DrsFile> m_terrainFile;

    std::unordered_map<int, std::unique_ptr<genie::PalFile>> m_hdPalFiles;

    DrsFileVector m_allFiles;

    genie::BlendomaticFilePtr blendomatic_file_;
    genie::SlpTemplateFilePtr m_stemplatesFile;
    genie::FiltermapFilePtr m_filtermapFile;
    genie::PatternMasksFilePtr m_patternmasksFile;
    genie::TileEdgeFilePtr m_tileEdgeFile;
    genie::BlkEdgeFilePtr m_blkEdgeFile;

    //TODO: All resources into one map?
    typedef std::unordered_map<uint32_t, GraphicPtr> GraphicMap;
    GraphicMap graphics_;

    typedef std::unordered_map<uint32_t, TerrainPtr> TerrainMap;
    TerrainMap terrains_;

    std::unordered_map<uint32_t, std::weak_ptr<uint8_t[]>> m_wavCache;

    genie::GameVersion m_gameVersion;
    std::string m_dataPath;
    std::unordered_set<uint32_t> m_nonExistentSlps;

    std::unordered_map<std::string, std::string> m_hdFilePaths;

    // TODO don't duplicate with datamanager, but I'm lazy
    bool m_isHd = false;
    std::string m_hdAssetPath;
};

