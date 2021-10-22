#pragma once
#include "Enemy.h"

class EnemyFast : public Enemy
{
public:
	EnemyFast(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player);
	EnemyFast(const EnemyFast&) = default;
	EnemyFast& operator=(const EnemyFast&) = default;
	EnemyFast(EnemyFast&&) = default;
	EnemyFast& operator=(EnemyFast&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override;
	void handleFall() override;

private:
	static bool m_registerit;

};