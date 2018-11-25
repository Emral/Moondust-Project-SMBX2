/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2017 Vitaly Novichkov <admin@wohlnet.ru>
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

#include "controller.h"
#include "controllable_object.h"

Controller::Controller()
{
    keys = noKeys();
}

controller_keys Controller::noKeys()
{
    return ResetControlKeys();
}

void Controller::setKeyMap(KeyMap map)
{
    kmap = map;
}

void Controller::resetControls()
{
    keys = ResetControlKeys();
}

void Controller::sendControls()
{
    for(ControllableObject *x : m_objects)
        x->applyControls(keys);
}

void Controller::update() {}

void Controller::registerInControl(ControllableObject *obj)
{
    if(m_objects.find(obj) == m_objects.end())
        m_objects.insert(obj);
}

void Controller::removeFromControl(ControllableObject *obj)
{
    auto i = m_objects.find(obj);
    if(i != m_objects.end())
        m_objects.erase(i);
}
