/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2016 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLAYER_CALIBRATION_H
#define PLAYER_CALIBRATION_H

class QSettings;
#include <QString>
#include <QList>
#include <vector>

struct AniFrame
{
    size_t x;
    size_t y;
};

struct AniFrameSet
{
    QList<AniFrame > L;
    QList<AniFrame > R;
    QString name;
};

struct FrameSets
{
    QList<AniFrameSet > set;
};

struct frameOpts
{
    frameOpts():
        H(0),
        W(0),
        offsetX(0),
        offsetY(0),
        used(false),
        isDuck(false),
        isRightDir(false),
        showGrabItem(false)
    {}
    unsigned int H;
    unsigned int W;
    int offsetX;
    int offsetY;
    bool used;
    bool isDuck;
    bool isRightDir;
    bool showGrabItem;
};

struct obj_player_calibration
{
        size_t matrixWidth;
        size_t matrixHeight;
        int frameWidth;
        int frameHeight;
        int frameHeightDuck;
        int frameGrabOffsetX;
        int frameGrabOffsetY;
        int frameOverTopGrab;
        //! Collision boxes settings
        std::vector<frameOpts> frames;
        FrameSets AniFrames;               //!< Animation settings
        //! Grabber which allows take frame by X and Y
        frameOpts &frame(size_t x, size_t y);
        void init(size_t x, size_t y);
        bool load(QString fileName);
    private:
        void getSpriteAniData(QSettings &set, QString name);
};

#endif // PLAYER_CALIBRATION_H
