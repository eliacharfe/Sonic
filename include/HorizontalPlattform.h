#pragma once
#include "MovingObject.h"

class HorizontalPlattform : public MovingObject
{

public:
	HorizontalPlattform(const char c, const sf::Sprite& sprite, shared_ptr< MovingObject>& player);
	HorizontalPlattform(const HorizontalPlattform&) = default;
	HorizontalPlattform& operator=(const HorizontalPlattform&) = default;
	HorizontalPlattform(HorizontalPlattform&&) = default;
	HorizontalPlattform& operator=(HorizontalPlattform&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override;
	void handleFall() override;

private:
	shared_ptr<MovingObject> m_player;
	int m_rand;
	static bool m_registerit;
};

