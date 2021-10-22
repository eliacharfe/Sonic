#include "EnemySlow.h"
#include "FactoryMovable.h"

bool EnemySlow::m_registerit = FactoryMovable::registerit('S', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject> 
	{ return make_shared<EnemySlow>(c, sprite, player); });

EnemySlow::EnemySlow(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player)
	: Enemy::Enemy(c,sprite, player)
{}
//-----------------------------------------
void EnemySlow::direction()
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;
	if (getLocation()._x < m_player->getLocation()._x - 2 * DEF_SIZE_WINDOW_X)
		m_isDisposed = true;
	srand((int)time(NULL));
	int random;
	if (m_clock.getElapsedTime().asSeconds() >= 2) {
		random = rand() % 2; // 0 or 1
		m_clock.restart();
	}
	else random = 2;

	switch (random) {
	case 0: { m_direction = Direction::RIGHT;
		setSprite(Image::instance().getSprite(ENEMY_SLOW_RIGHT)); break;
	}
	case 1: { m_direction = Direction::LEFT;
		setSprite(Image::instance().getSprite(ENEMY_SLOW)); break;
	}
	default:   break;
	}
}
//----------------------------------------------
void EnemySlow::move(const sf::Time& currTime)
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X / 2
		|| getLocation()._x < m_player->getLocation()._x - DEF_SIZE_WINDOW_X / 2)
		return;
	const auto speedPerSec = currTime.asSeconds() * (SPEED_ENEMY_SLOW + m_level * 20);
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
	                  getLocation()._y + (dirToVector(m_direction).y * speedPerSec));

	m_lastLocation = getLocation(); // save in case need to use
	setLocation(location);
}
//----------------------------------------------
void EnemySlow::changeDirectionWhenCollision()
{
	if (m_direction == Direction::LEFT) {
		m_direction = Direction::RIGHT;
		setSprite(Image::instance().getSprite(ENEMY_SLOW_RIGHT));
	}
	else {
		m_direction = Direction::LEFT;
		setSprite(Image::instance().getSprite(ENEMY_SLOW));
	}
}
//-------------------------------
void EnemySlow::handleFall()
{
	Location NewLocation(getLocation()._x, getLocation()._y + 30);
	setLocation(NewLocation);// fall down
}
//----------------------------------------------------
