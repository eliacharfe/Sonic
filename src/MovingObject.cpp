#include "MovingObject.h"

MovingObject::MovingObject(const char c, const sf::Sprite& sprite)
	: GameObject::GameObject(c, sprite)
	,m_lastLocation(Location(OBJECT_SIZE / 2, OBJECT_SIZE / 2)),  m_clock(sf::Clock())
{
}
