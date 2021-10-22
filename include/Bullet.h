#pragma once
#include "Utilities.h"
#include "MovingObject.h"

class Bullet : public MovingObject
{
public:
	Bullet(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player);
	Bullet(const Bullet&) = default;
	Bullet& operator=(const Bullet&) = default;
	Bullet(Bullet&&) = default;
	Bullet& operator=(Bullet&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override {}
	void handleFall() override {};

private:
	void setRotation();

	Rotation m_rotation = Rotation::Default;
	shared_ptr<MovingObject> m_player;
	static bool m_registerit;
};