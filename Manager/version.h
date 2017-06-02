/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014-2016 Vitaly Novichkov <admin@wohlnet.ru>
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

#include "../pge_version.h" //Global Project version file

#pragma once
#ifndef MANAGER_VERSION_H
#define MANAGER_VERSION_H

#define _VF1 0
#define _VF2 0
#define _VF3 1
#define _VF4 0
#define _FILE_RELEASE "-pre-alpha"

#define _VF1_s STR_VALUE(_VF1)
#define _VF2_s STR_VALUE(_VF2)
#define _VF3_s STR_VALUE(_VF3)
#define _VF4_s STR_VALUE(_VF4)
#if _VF4 == 0
    #if _VF3 == 0
        #define _FILE_VERSION_NUM GEN_VERSION_NUMBER_2(_VF1_s, _VF2_s)
    #else
        #define _FILE_VERSION_NUM GEN_VERSION_NUMBER_3(_VF1_s, _VF2_s, _VF3_s)
    #endif
#else
    #define _FILE_VERSION_NUM GEN_VERSION_NUMBER_4(_VF1_s, _VF2_s, _VF3_s, _VF4_s)
#endif

//Version of this program
#define _FILE_VERSION _FILE_VERSION_NUM

//Version of this program
#define _LATEST_STABLE _FILE_VERSION_NUM _FILE_RELEASE

#define _FILE_DESC "PGE Content Manager"

#define _INTERNAL_NAME "pge_manager"

#ifdef _WIN32
	#define _ORIGINAL_NAME "pge_manager.exe" // for Windows platforms
#else
	#define _ORIGINAL_NAME "pge_manager" // for any other platforms
#endif

//Uncomment this for enable detal logging
//#define _DEBUG_

#endif
