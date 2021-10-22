#include "Direction.h"
#include <stdexcept>

Direction getDir(const Direction& dir) 
{
	switch (dir)
	{
	case Direction::UP: return Direction::UP;
	case Direction::DOWN: return Direction::DOWN;
	case Direction::RIGHT:return Direction::RIGHT;
	case Direction::LEFT: return Direction::LEFT;
	case Direction::STAY: return Direction::STAY;

	default:
		throw std::runtime_error("Unknown direction");
	}
}
//--------------------------------------------------
const sf::Vector2f dirToVector(const Direction& direction)
{
	switch (direction)
	{
	case Direction::UP:    return { 0, -1 };
	case Direction::DOWN:  return { 0, 1 };
	case Direction::RIGHT: return { 1, 0 };
	case Direction::LEFT:  return { -1, 0 };
	case Direction::STAY:  return { 0, 0 };
	default:
		return { 0, 0 };
	}
}
//-------------------------------------------
const sf::Vector2f keyToDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Left:
		return { -1, 0 };
	case sf::Keyboard::Right:
		return { 1, 0 };
	case sf::Keyboard::Up:
		return { 0, -1 };
	case sf::Keyboard::Down:
		return { 0, 1 };
	default:
		return { 0, 0 };
	}
}
//----------------------------------























//Direction opposite(Direction dir)
//{
//    switch (dir)
//    {
//    case Direction::Up:
//        return Direction::Down;
//    case Direction::Down:
//        return Direction::Up;
//    case Direction::Right:
//        return Direction::Left;
//    case Direction::Left:
//        return Direction::Right;
//    case Direction::Stay:
//        return Direction::Stay;
//    default:
//        throw std::runtime_error("Unknown direction");
//    }
//}

 /*   switch (dir)
	{
	case Direction::Up:
		return { 0, -1 };
	case Direction::Down:
		return { 0, 1 };
	case Direction::Right:
		return { 1, 0 };
	case Direction::Left:
		return { -1, 0 };
	case Direction::Stay:
		return { 0, 0 };
	default:
		return { 0, 0 };
	}*/

