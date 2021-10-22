#pragma once
#include "Player.h"

class VerticalPlattform : public MovingObject
{
public:
	VerticalPlattform(const char c, const sf::Sprite& sprite, shared_ptr< MovingObject>& player);
	VerticalPlattform(const VerticalPlattform&) = default;
	VerticalPlattform& operator=(const VerticalPlattform&) = default;
	VerticalPlattform(VerticalPlattform&&) = default;
	VerticalPlattform& operator=(VerticalPlattform&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override;
	void handleFall() override;

private:
	shared_ptr<MovingObject> m_player;
	int m_rand;
	static bool m_registerit;
};


