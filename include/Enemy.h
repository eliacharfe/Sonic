#pragma once
#include "Player.h"

class Enemy : public MovingObject
{
public:
	Enemy(const char c, const sf::Sprite& sprite, shared_ptr< MovingObject>& player);
	Enemy(const Enemy&) = default;
	Enemy& operator=(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(Enemy&&) = default;

protected:
	void changeDirectionWhenCollision() override = 0;
	shared_ptr<MovingObject> m_player;

private:


};