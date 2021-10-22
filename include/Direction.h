#pragma once
#include "Utilities.h"

enum class Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    STAY,
};

Direction getDir(const Direction& dir);
const sf::Vector2f dirToVector(const Direction& direction) ;
const sf::Vector2f keyToDirection(sf::Keyboard::Key key);

enum class Rotation {
    DownLeft = 45,
    DownRight = 315 ,
    UpLeft = 135,
    UpRight = 225,
    Default = 0
};
