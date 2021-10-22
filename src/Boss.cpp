#include "Boss.h"
#include "FactoryMovable.h"

bool Boss::m_registerit = FactoryMovable::registerit('B', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject> 
	{ return make_shared<Boss>(c, sprite, player); });
int Boss::m_life = FULL_LIFE;
bool Boss::m_shooting = false;

Boss::Boss(const char c,const sf::Sprite& sprite, shared_ptr<MovingObject>& player)
	: Enemy::Enemy(c, sprite, player)
{
	m_sprite.setOrigin(OBJECT_SIZE, OBJECT_SIZE);
}
//----------------------------------------------------
void Boss::direction()
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;
	//if player is near
	if (m_player->getLocation()._x > getLocation()._x - DEF_SIZE_WINDOW_X / 4 &&
		m_player->getLocation()._x < getLocation()._x + DEF_SIZE_WINDOW_X / 4)
	{
		if ((m_clock.getElapsedTime().asSeconds() > 0 
			&& m_clock.getElapsedTime().asSeconds() < (0.1 * m_level) )
			|| (m_clock.getElapsedTime().asSeconds() > 1.5 
				&& m_clock.getElapsedTime().asSeconds() < 1.5 + (0.1 * m_level)))
			m_shooting = true;
		else
			m_shooting = false;
	}

	const auto YPlayer = m_player->getLocation()._y;
	const auto XPlayer = m_player->getLocation()._x;
	const auto YBoss = getLocation()._y;
	const auto XBoss = getLocation()._x;

	if (XPlayer <= XBoss)
		m_direction = Direction::LEFT;
	else 
		m_direction = Direction::RIGHT;

}
//-----------------------------------------------
void Boss::move(const sf::Time& currTime)
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;

	switch (m_direction)
	{
	case Direction::LEFT: {
		if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() <= 0.5)
			setSprite(Image::instance().getSprite(BOSS));
		else if (m_clock.getElapsedTime().asSeconds() > 0.5 && m_clock.getElapsedTime().asSeconds() < 1) 
			setSprite(Image::instance().getSprite(BOSS_SHOOT1_LEFT));
		else if (m_clock.getElapsedTime().asSeconds() >= 1 && m_clock.getElapsedTime().asSeconds() < 1.5) 
			setSprite(Image::instance().getSprite(BOSS_SHOOT2_LEFT));
		else if (m_clock.getElapsedTime().asSeconds() >= 1.5 && m_clock.getElapsedTime().asSeconds() < 2) 
			setSprite(Image::instance().getSprite(BOSS_EGG_LEFT));
		else if (m_clock.getElapsedTime().asSeconds() >= 2 && m_clock.getElapsedTime().asSeconds() < 2.5) 
			setSprite(Image::instance().getSprite(BOSS_HAMMER_LEFT));
		else if (m_clock.getElapsedTime().asSeconds() >= 2.5)
			m_clock.restart();
		break;
	}
	case Direction::RIGHT: {
		if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() <= 0.5)
			setSprite(Image::instance().getSprite(BOSS_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() > 0.5 && m_clock.getElapsedTime().asSeconds() < 1) 
			setSprite(Image::instance().getSprite(BOSS_SHOOT1_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 1 && m_clock.getElapsedTime().asSeconds() < 1.5) 
			setSprite(Image::instance().getSprite(BOSS_SHOOT2_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 1.5 && m_clock.getElapsedTime().asSeconds() < 2) 
			setSprite(Image::instance().getSprite(BOSS_EGG_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 2 && m_clock.getElapsedTime().asSeconds() < 2.5) 
			setSprite(Image::instance().getSprite(BOSS_HAMMER_RIGHT));
		else if (m_clock.getElapsedTime().asSeconds() >= 2.5)
			m_clock.restart();
		break;
	}
	}

	const auto speedPerSec = currTime.asSeconds() * (SPEED_BOSS + m_level * 25);
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
		getLocation()._y + (dirToVector(m_direction).y * speedPerSec));
	m_lastLocation = getLocation(); // save in case need to use
	m_lastDirection = m_direction;
	setLocation(location);// if not out of the level board
}
//-------------------------------------------------------------
void Boss::changeDirectionWhenCollision()
{
	if (m_direction == Direction::LEFT)
		m_direction = Direction::RIGHT;
	else if (m_direction == Direction::RIGHT)
		m_direction = Direction::LEFT;
	m_clock.restart();
}
void Boss::handleFall()
{
}
//----------------------------------------------------


