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

#ifndef FREEAOE_GRAPHIC_H
#define FREEAOE_GRAPHIC_H

#include "Resource.h"

#include <SFML/Graphics/Image.hpp>
#include <global/Types.h>
#include <global/Logger.h>
#include <genie/dat/Graphic.h>

#include <genie/resource/SlpFile.h>

#include <unordered_map>

class SlpFile;

namespace res {

//------------------------------------------------------------------------------
/// A graphic resource contains one or more frames and data stored to
/// the graphic.
// TODO: Player mask, outline
//
class Graphic : public Resource
{

public:
    //----------------------------------------------------------------------------
    /// Constructor
    ///
    /// @param id Id of the graphic struct in .dat file.
    //
    Graphic(uint32_t id);
    virtual ~Graphic();

    //----------------------------------------------------------------------------
    /// Returns the image of the graphic.
    ///
    /// @param frame_num Number of the frame
    /// @param mirrored If set, the image will be returned mirrored
    /// @return Image
    //
    sf::Image getImage(uint32_t frame_num = 0, bool mirrored = false, float angle = 0.);

    std::vector<std::shared_ptr<Graphic>> getDeltas();

    //----------------------------------------------------------------------------
    /// Get the hotspot of a frame.
    // TODO: Maybe inherit from sf::Image and include this property
    //
    ScreenPos getHotspot(uint32_t frame_num = 0, bool mirrored = false) const;

    //----------------------------------------------------------------------------
    /// Get the frame rate of the graphic
    ///
    /// @return frame rate
    //
    float getFrameRate(void) const;

    //----------------------------------------------------------------------------
    ///
    /// @return replay delay
    //
    float getReplayDelay(void) const;

    //----------------------------------------------------------------------------
    /// Get the graphics frame count.
    ///
    /// @return frame count
    //
    uint32_t getFrameCount(void) const;

    //----------------------------------------------------------------------------
    /// Get the graphics angle count
    ///
    /// @return angle count
    //
    uint32_t getAngleCount(void) const;

    bool load(void) override;
    void unload(void) override;

    ScreenPos offset_;

private:
    static Logger &log;

    uint32_t id_;

    std::unique_ptr<genie::Graphic> data_;
    genie::SlpFilePtr slp_;
    std::unordered_map<int, sf::Image> m_images;
    std::unordered_map<int, sf::Image> m_flippedImages;

    std::vector<std::shared_ptr<Graphic>> m_deltas;

    //TODO: collection with all frames, playercolors and outlines loaded
    //      And rewrite SlpFile/Frame so that it will not store any data.
};

typedef std::shared_ptr<Graphic> GraphicPtr;
}

#endif // FREEAOE_GRAPHIC_H
