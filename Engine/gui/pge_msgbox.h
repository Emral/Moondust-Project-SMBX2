/*
 * Moondust, a free game engine for platform game making
 * Copyright (c) 2014-2018 Vitaly Novichkov <admin@wohlnet.ru>
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

#ifndef PGE_MSGBOX_H
#define PGE_MSGBOX_H

#include "pge_boxbase.h"
#include "../scenes/scene.h"

#include <graphics/gl_renderer.h>
#include <graphics/gl_color.h>
#include <common_features/rect.h>
#include <common_features/point.h>
#include <common_features/pointf.h>
#include <common_features/size.h>
#include <common_features/sizef.h>

#include <controls/control_keys.h>
#include <string>

class PGE_MsgBox : public PGE_BoxBase
{
public:
    PGE_MsgBox();
    PGE_MsgBox(Scene *_parentScene = nullptr,
               std::string msg = "Message box is works!",
               msgType _type = msg_info,
               PGE_Point boxCenterPos = PGE_Point(-1, -1),
               double _padding = -1,
               std::string texture = std::string());
    PGE_MsgBox(const PGE_MsgBox &mb);
    ~PGE_MsgBox();

    void setBoxSize(double _Width, double _Height, double _padding);
    void update(double ticks);
    void render();
    void restart();
    bool isRunning();
    void exec();

    void processLoader(double ticks);
    void processBox(double);
    void processUnLoader(double ticks);

    static void info(std::string msg);
    //static void info(std::string msg);
    static void warn(std::string msg);
    //static void warn(std::string msg);
    static void error(std::string msg);
    //static void error(std::string msg);
    static void fatal(std::string msg);
    //static void fatal(std::string msg);

private:
    void construct(std::string msg = "Message box is works!",
                   msgType _type = msg_info, PGE_Point pos = PGE_Point(-1, -1),
                   double _padding = -1, std::string texture = "");
    int     m_page;
    bool    m_running;
    int     fontID;
    GlColor fontRgba;
    int     m_borderWidth = 32;

    controller_keys keys;
    bool   m_exitKeyLock; //Don't close message box if exiting key already holden (for example, 'Run' key)

    msgType m_type;
    PGE_Rect m_sizeRect;
    std::string m_message;
    double  width;
    double  height;
    double  padding;
    GlColor bg_color;
    void updateControllers();
};

#endif // PGE_MSGBOX_H
