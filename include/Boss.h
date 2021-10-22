#pragma once
#include "Enemy.h"
#include "Bullet.h"

class Boss : public Enemy
{
	//friend class Bullet;
public:
	Boss(const char c,const sf::Sprite& sprite, shared_ptr<MovingObject>& player);
	Boss(const Boss&) = default;
	Boss& operator=(const Boss&) = default;
	Boss(Boss&&) = default;
	Boss& operator=(Boss&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void changeDirectionWhenCollision() override;
	void handleFall() override;

	void setLife(int life) { m_life += life; }
	int getLife() const { return m_life; }
	void setDamage(int damage) { m_life -= damage; }

	static bool isShooting() { return m_shooting; }

private:
	static int m_life;
	static bool m_registerit;
	static bool m_shooting;
};