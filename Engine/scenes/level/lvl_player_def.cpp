#include "lvl_player_def.h"


LVL_PlayerDef::LVL_PlayerDef()
{
    _characterID  = 1;
    _currentState = 1;
    _playerID = 1;
}

LVL_PlayerDef::~LVL_PlayerDef()
{}

LVL_PlayerDef::LVL_PlayerDef(const LVL_PlayerDef &d)
{
    operator=(d);
}

LVL_PlayerDef &LVL_PlayerDef::operator=(const LVL_PlayerDef &d)
{
    _playerID       = d._playerID;
    _characterID    = d._characterID;
    _currentState   = d._currentState;
    return *this;
}

void LVL_PlayerDef::setCharacterID(unsigned long _id)
{
    if(ConfigManager::playable_characters.contains(_id))
        _characterID = _id;
    else
        _characterID = 1; //First character by default
}

void LVL_PlayerDef::setState(unsigned long _state)
{
    if(ConfigManager::playable_characters[_characterID].states.contains(_state))
        _currentState = _state;
    else
        _currentState = 1; //First state by default
}

void LVL_PlayerDef::setPlayerID(int id)
{
    _playerID = id;
}

int LVL_PlayerDef::playerID()
{
    return _playerID;
}

unsigned long LVL_PlayerDef::characterID()
{
    return _characterID;
}

unsigned long LVL_PlayerDef::currentState()
{
    return _currentState;
}

int LVL_PlayerDef::width()
{
    if(_characterID > 0)
        return ConfigManager::playable_characters[_characterID].states[_currentState].width;
    else
        return 1;
}

int LVL_PlayerDef::height()
{
    if(_characterID > 0)
        return ConfigManager::playable_characters[_characterID].states[_currentState].height;
    else
        return 1;
}

int LVL_PlayerDef::heightDuck()
{
    if(_characterID > 0)
        return ConfigManager::playable_characters[_characterID].states[_currentState].duck_height;
    else
        return 1;
}
