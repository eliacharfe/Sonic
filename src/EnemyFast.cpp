#include "EnemyFast.h"
#include "FactoryMovable.h"

bool EnemyFast::m_registerit = FactoryMovable::registerit('&', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject> 
	{ return make_shared<EnemyFast>(c, sprite, player); });

EnemyFast::EnemyFast(const char c, const sf::Sprite& sprite, shared_ptr < MovingObject >& player)
	: Enemy::Enemy(c,sprite, player)
{}
//----------------------------------------------------
void EnemyFast::direction()
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X )
		return;
	if (getLocation()._x < m_player->getLocation()._x - 3 * DEF_SIZE_WINDOW_X)
		m_isDisposed = true;

	if (m_player->getLocation()._x < getLocation()._x)
		m_direction = Direction::LEFT;
	else if (m_player->getLocation()._x > getLocation()._x)
		m_direction = Direction::RIGHT;
	else
		m_direction = Direction::STAY;

	switch (m_direction)
	{
	case Direction::RIGHT: {
		if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() < 0.2)
			setSprite(Image::instance().getSprite(ENEMY_FAST_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 0.2 && m_clock.getElapsedTime().asSeconds() < 0.4)
			setSprite(Image::instance().getSprite(ENEMY_FAST_RUN_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 0.4 && m_clock.getElapsedTime().asSeconds() < 0.6)
			setSprite(Image::instance().getSprite(ENEMY_FAST_RIGHT_HIT));
		else m_clock.restart();
		break;
	}
	case Direction::LEFT: {
		if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() < 0.2)
			setSprite(Image::instance().getSprite(ENEMY_FAST));
		else if (m_clock.getElapsedTime().asSeconds() >= 0.2 && m_clock.getElapsedTime().asSeconds() < 0.4)
			setSprite(Image::instance().getSprite(ENEMY_FAST_RUN_LEFT));
		else if (m_clock.getElapsedTime().asSeconds() >= 0.4 && m_clock.getElapsedTime().asSeconds() < 0.6)
			setSprite(Image::instance().getSprite(ENEMY_FAST_LEFT_HIT));
		else m_clock.restart();
		break;

	}
	case Direction::STAY: {
		m_clock.restart();
			setSprite(Image::instance().getSprite(ENEMY_FAST));
		break;
	}
	}
}
//-----------------------------------------------
void EnemyFast::move(const sf::Time& currTime)
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;

	const auto speedPerSec = currTime.asSeconds() * (SPEED_ENEMY_FAST + m_level * 25) ;
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
		              getLocation()._y + (dirToVector(m_direction).y * speedPerSec));
	m_lastLocation = getLocation(); // save in case need to use
	m_lastDirection = m_direction;
	setLocation(location);
}
//-------------------------------------------------------------
void EnemyFast::changeDirectionWhenCollision()
{
	if (m_direction == Direction::LEFT)
		m_direction = Direction::RIGHT;
	else
		m_direction = Direction::LEFT;
	m_clock.restart();
}
//-----------------------------------
void EnemyFast::handleFall()
{
	Location NewLocation(getLocation()._x, getLocation()._y + 30);
	setLocation(NewLocation);// fall down
}
//----------------------------------------------------
