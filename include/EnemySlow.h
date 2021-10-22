#pragma once
#include "Enemy.h"
#include "EnemyFast.h"

class EnemySlow : public Enemy
{
public:
	EnemySlow(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player);
	EnemySlow(const EnemySlow&) = default;
	EnemySlow& operator=(const EnemySlow&) = default;
	EnemySlow(EnemySlow&&) = default;
	EnemySlow& operator=(EnemySlow&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override;
	void handleFall() override;

private:
	static bool m_registerit;
};