/*
 * Moondust, a free game engine for platform game making
 * Copyright (c) 2014-2023 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This software is licensed under a dual license system (MIT or GPL version 3 or later).
 * This means you are free to choose with which of both licenses (MIT or GPL version 3 or later)
 * you want to use this software.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You can see text of MIT license in the LICENSE.mit file you can see in Engine folder,
 * or see https://mit-license.org/.
 *
 * You can see text of GPLv3 license in the LICENSE.gpl3 file you can see in Engine folder,
 * or see <http://www.gnu.org/licenses/>.
 */

#include "config_bgo.h"

#include <IniProcessor/ini_processing.h>
#include <Utils/maths.h>
#include "../../number_limiter.h"

#include <assert.h>

bool BgoSetup::parse(IniProcessing *setup,
                     PGEString bgoImgPath,
                     uint32_t defaultGrid,
                     const BgoSetup *merge_with,
                     PGEString *error)
{
    bool canParse = baseParse(setup, bgoImgPath, 0, merge_with, error);
    if (!canParse) {
        return false;
    }
#define pMerge(param, def) (merge_with ? pgeConstReference(merge_with->param) : pgeConstReference(def))
#define pMergeMe(param) (merge_with ? pgeConstReference(merge_with->param) : pgeConstReference(param))
#define pAlias(paramName, destValue) setup->read(paramName, destValue, destValue)

    pAlias("hide-on-exported-images", is_meta_object);//Alias
    setup->read("grid",     grid, pMerge(grid, defaultGrid));
    setup->read("grid-offset-x", grid_offset_x, pMerge(grid_offset_x, 0));
    setup->read("grid-offset-y", grid_offset_y, pMerge(grid_offset_y, 0));
    setup->read("offset-x", grid_offset_x, pMergeMe(grid_offset_x));//DEPRECATED
    setup->read("offset-y", grid_offset_y, pMergeMe(grid_offset_y));//DEPRECATED

    {
        IniProcessing::StrEnumMap zLayers = {
            {"foreground2", z_foreground_2},
            {"foreground1", z_foreground_1},
            {"foreground",  z_foreground_1},
            {"background",  z_background_1},
            {"background1", z_background_1},
            {"background2", z_background_2},
        };
        setup->readEnum("z-layer", zLayer, pMerge(zLayer, z_background_1), zLayers);
        setup->readEnum("view", zLayer, zLayer, zLayers);//Alias
    }

    zValueOverride = setup->hasKey("z-value") || setup->hasKey("priority");
    setup->read("z-value",  zValue,    pMerge(zValue, 0.0l));
    pAlias("priority", zValue);//Alias

    if(merge_with && zValueOverride)
        setup->read("z-offset", zOffset,    0.0l);
    else
        setup->read("z-offset", zOffset,    pMerge(zOffset, 0.0l));

    setup->read("climbing", climbing ,  pMerge(climbing, false));
    setup->read("frames", frames,       pMerge(frames, 1u));//Real
    pAlias("framecount",           frames);
    pAlias("frame-count",          frames);
#ifdef PGE_EDITOR // alternative animation for Editor
    pAlias("editor-frames",   frames);
#endif
    NumberLimiter::apply(frames, 1u);
    animated = (frames > 1);
    setup->read("frame-delay", framespeed, pMerge(framespeed, 125));//Real
    pAlias("frame-speed", framespeed);//Alias
    if(setup->hasKey("framespeed"))
    {
        setup->read("framespeed",  framespeed, framespeed);//Alias
        framespeed = (framespeed * 1000u) / 65u;//Convert 1/65'th into milliseconds
    }

    frame_sequence.clear();
    setup->read("frame-sequence", frame_sequence, pMergeMe(frame_sequence));
#ifdef PGE_EDITOR // alternative animation for Editor
    pAlias("editor-frame-sequence",   frame_sequence);
#endif

    frame_h =   animated ? Maths::uRound(double(h) / double(frames)) : h;
    NumberLimiter::apply(frame_h, 0u);
    setup->read("display-frame", display_frame, pMerge(display_frame, 0));
    NumberLimiter::apply(display_frame, 0u);

#undef pMerge
#undef pMergeMe
#undef pAlias
    return true;
}
