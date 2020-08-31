/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/* Intel Indeo 4 decompressor, derived from ffmpeg.
 *
 * Original copyright note:
 * Intel Indeo 4 (IV31, IV32, etc.) video decoder for ffmpeg
 * written, produced, and directed by Alan Smithee
 */

#ifndef IMAGE_CODECS_INDEO5_H
#define IMAGE_CODECS_INDEO5_H


///////////// TEMP
// TODO: move below after adding everywere necessaray
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>

#define error printf
#define warning printf
#define int32 int32_t
#define uint32 uint32_t
#define int16 int16_t
#define uint16 uint16_t
#define int8 int8_t
#define uint8 uint8_t
#define byte uint8_t

#define SWAP std::swap

struct Codec {};

inline uint16_t SWAP_BYTES_16(const uint16_t a) {
                return (a >> 8) | (a << 8);
                }
uint32_t SWAP_BYTES_32(uint32_t a) {
                return __builtin_bswap32(a);
        }

inline uint16_t READ_UINT16(const void *ptr) {
                        const uint8_t *b = (const uint8_t *)ptr;
                        return (b[1] << 8) | b[0];
                }
inline uint16_t READ_BE_UINT16(const void *ptr) {
                        return SWAP_BYTES_16(READ_UINT16(ptr));
                }
uint32_t READ_UINT32(const void *ptr) {
                return *(const uint32_t *)(ptr);
        }
inline uint32_t READ_BE_UINT32(const void *ptr) {
                        return SWAP_BYTES_32(READ_UINT32(ptr));
                }

#define READ_LE_UINT16(a) READ_UINT16(a)
#define READ_LE_UINT32(a) READ_UINT32(a)
////////////////////////

#include "indeo/get_bits.h"
#include "indeo/indeo.h"

namespace Image {

using namespace Indeo;

/**
 * Intel Indeo 5 decoder.
 *
 * Used by AVI.
 *
 * Used in video:
 *  - AVIDecoder
 */
class Indeo5Decoder : public IndeoDecoderBase {
	struct Transform {
		InvTransformPtr *inv_trans;
		DCTransformPtr  *dc_trans;
		int             is_2d_trans;
	};
public:
	Indeo5Decoder(uint16_t width, uint16_t height, uint bitsPerPixel = 16);
	virtual ~Indeo5Decoder() {}

#if 0
	virtual const Graphics::Surface *decodeFrame(Common::SeekableReadStream &stream);

	static bool isIndeo5(Common::SeekableReadStream &stream);
#endif
protected:
	/**
	 * Decode the Indeo 5 picture header.
	 * @returns		0 = Ok, negative number = error
	 */
	virtual int decodePictureHeader();

	/**
	 *  Rearrange decoding and reference buffers.
	 */
	virtual void switchBuffers();

	virtual bool isNonNullFrame() const;

	/**
	 *  Decode Indeo 4 band header.
	 *
	 *  @param[in,out] band      pointer to the band descriptor
	 *  @return        result code: 0 = OK, negative number = error
	 */
	virtual int decodeBandHeader(IVIBandDesc *band);

	/**
	 *  Decode information (block type, cbp, quant delta, motion vector)
	 *  for all macroblocks in the current tile.
	 *
	 *  @param[in,out] band      pointer to the band descriptor
	 *  @param[in,out] tile      pointer to the tile descriptor
	 *  @return        result code: 0 = OK, negative number = error
	 */
	virtual int decodeMbInfo(IVIBandDesc *band, IVITile *tile);
private:
	/**
	 *  Decode Indeo5 GOP (Group of pictures) header.
	 *  This header is present in key frames only.
	 *  It defines parameters for all frames in a GOP.
	 *  @returns	result code: 0 = OK, -1 = error
	 */
	int decode_gop_header();

	/**
	 *  Skip a header extension.
	 */
	int skip_hdr_extension();

private:
	/**
	 *  standard picture dimensions (width, height divided by 4)
	 */
	static const uint8_t _commonPicSizes[30];

	/**
	 *  Indeo5 dequantization matrixes consist of two tables: base table
	 *  and scale table. The base table defines the dequantization matrix
	 *  itself and the scale table tells how this matrix should be scaled
	 *  for a particular quant level (0...24).
	 *
	 *  ivi5_base_quant_bbb_ttt  - base  tables for block size 'bbb' of type 'ttt'
	 *  ivi5_scale_quant_bbb_ttt - scale tables for block size 'bbb' of type 'ttt'
	 */
	static const uint16_t _baseQuant8x8Inter[5][64];
	static const uint16_t _baseQuant8x8Intra[5][64];

	static const uint16_t _baseQuant4x4Inter[16];
	static const uint16_t _baseQuant4x4Intra[16];

	static const uint8_t _scaleQuant8x8Inter[5][24];
	static const uint8_t _scaleQuant8x8Intra[5][24];

	static const uint8_t _scaleQuant4x4Inter[24];
	static const uint8_t _scaleQuant4x4Intra[24];
};

} // End of namespace Image

#endif
