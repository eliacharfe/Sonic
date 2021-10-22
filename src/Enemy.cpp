#include "Enemy.h"

Enemy::Enemy(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player)
	: MovingObject::MovingObject(c, sprite), m_player(player)
{
}
