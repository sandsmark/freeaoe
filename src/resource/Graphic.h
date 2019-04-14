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

#include "Resource.h"

#include "core/Types.h"
#include "core/Logger.h"

#include <genie/dat/Graphic.h>
#include <genie/resource/SlpFile.h>
#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>

class SlpFile;
enum class ImageType {
    Base,
    Outline,
    Shadow,
    Construction,
    ConstructionUnavailable,
    InTheShadows, // TODO find a proper name for units not visible
};

inline LogPrinter &operator <<(LogPrinter &os, const ImageType &type) {
    os << "ImageType(";
    switch (type) {
    case ImageType::Base:
        os << "Base";
        break;
    case ImageType::Outline:
        os << "Outline";
        break;
    default:
        os << "Invalid";
        break;
    }
    os << ")";
    return os;
}

struct GraphicState {
    uint32_t frame = 0;
    int angle = 0;
    uint8_t playerId = 0;
    ImageType type = ImageType::Base;
    bool flipped = false;

    bool operator==(const GraphicState &other) const {
        return frame == other.frame &&
               angle == other.angle &&
               playerId == other.playerId &&
               type == other.type &&
               flipped == other.flipped;
    }
};

namespace std {
template<> struct hash<GraphicState>
{
    size_t operator()(const GraphicState b) const {
        return hash<uint32_t>()(b.frame) ^
               hash<int>()(b.angle) ^
               hash<uint8_t>()(b.playerId) ^
               hash<int>()(int(b.type)) ^
               hash<bool>()(b.flipped);

    }
};
}


//------------------------------------------------------------------------------
/// A graphic resource contains one or more frames and data stored to
/// the graphic.
// TODO: Player mask, outline
//
class Graphic
{
    static const sf::Texture nullImage;

public:
    const int graphicId = -1;

    //----------------------------------------------------------------------------
    /// Constructor
    ///
    /// @param id Id of the graphic struct in .dat file.
    //
    Graphic(const genie::Graphic &m_data, const int id);
    virtual ~Graphic();

    static sf::Image slpFrameToImage(const genie::SlpFramePtr &frame, uint8_t playerId, const ImageType imageType);

    //----------------------------------------------------------------------------
    /// Returns the image of the graphic.
    ///
    /// @param frame_num Number of the frame
    /// @param mirrored If set, the image will be returned mirrored
    /// @return Image
    //
//    const sf::Texture &getImage(uint32_t frame_num = 0, float angle = 0, uint8_t playerId = 0, const ImageType type = ImageType::Base);
//    const sf::Texture &overlayImage(uint32_t frame_num, float angle, uint8_t playerId);

    const sf::Texture &texture(uint32_t frameNum = 0, float angleRadians = 0, uint8_t playerId = 0, const ImageType imageType = ImageType::Base);

    const Size size(uint32_t frame_num, float angle) const;
    const ScreenRect rect(uint32_t frame_num, float angle) const;
    ScreenPos getHotspot(uint32_t frame_num, float angle) const;

    bool checkClick(const ScreenPos &pos, uint32_t frame_num, float angle) const;

    const std::vector<genie::GraphicDelta> deltas() const;

    bool hasSounds() const { return m_data.AngleSoundsUsed; }

    const genie::GraphicAngleSound &soundForAngle(float angle);

    int sound() const { return m_data.SoundID; }

    //----------------------------------------------------------------------------
    /// Get the frame rate of the graphic
    ///
    /// @return frame rate
    //
    float framerate() const;

    //----------------------------------------------------------------------------
    ///
    /// @return replay delay
    //
    inline float replayDelay() const { return m_data.ReplayDelay; }

    //----------------------------------------------------------------------------
    /// Get the graphics frame count.
    ///
    /// @return frame count
    //
    inline uint16_t frameCount() const { return m_data.FrameCount; }

    bool load();
    void unload();

    ScreenPos offset_;

    bool isValid();

    bool runOnce() const;
    void setRunOnce(const bool once);

    int angleToOrientation(float angle) const;
    float orientationToAngle(float orientation) const;
private:
    const genie::SlpFramePtr &getFrame(uint32_t frame_num, float angle) const;

    struct FrameInfo {
        uint32_t frameNum = 0;
        bool mirrored = false;
    };
    FrameInfo calcFrameInfo(uint32_t num, float angle) const;

    genie::SlpFilePtr slp_;

    std::unordered_map<GraphicState, sf::Texture> m_cache;

    const genie::Graphic &m_data;
    bool m_runOnce = false;
};

typedef std::shared_ptr<Graphic> GraphicPtr;

