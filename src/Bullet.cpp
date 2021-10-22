#include "Bullet.h"
#include "FactoryMovable.h"

bool Bullet::m_registerit = FactoryMovable::registerit('*', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject> 
	{ return make_shared< Bullet>(c, sprite, player); });

Bullet::Bullet(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player)
	: MovingObject::MovingObject(c,sprite), m_player(player)
{
}
//-------------------------------------------
void Bullet::direction()
{
	const auto YPlayer = m_player->getLocation()._y;
	const auto XPlayer = m_player->getLocation()._x;
	const auto YBullet = getLocation()._y;
	const auto XBullet = getLocation()._x;

	srand((int)time(NULL));
	int random_direction = rand() % 2;
	if (XPlayer <= XBullet  && YPlayer <= YBullet ) {
		if (random_direction % 2 == 0)
			m_direction = Direction::UP;
		else m_direction = Direction::LEFT;

		m_rotation = Rotation::UpLeft;
	}
	else if (XPlayer <= XBullet && YPlayer >= YBullet ) {
		if (random_direction % 2 == 0)
			m_direction = Direction::DOWN;
		else
		    m_direction = Direction::LEFT;

		m_rotation = Rotation::DownLeft;
	}
	else if (XPlayer >= XBullet && YPlayer <= YBullet ) {
		if (random_direction % 2 == 0)
			m_direction = Direction::UP;
		else m_direction = Direction::RIGHT;

		m_rotation = Rotation::UpRight;
	}
	else if (XPlayer > XBullet  && YPlayer >= YBullet) {
		if (random_direction % 2 == 0)
			m_direction = Direction::DOWN;
		else m_direction = Direction::RIGHT;

		m_rotation = Rotation::DownRight;
	}

	setRotation();
}
//-------------------------------------------
void Bullet::move(const sf::Time& currTime)
{
	const auto speedPerSec = currTime.asSeconds() * (SPEED_BULLET + m_level * 20);
	setLocation(Location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
		                 getLocation()._y + (dirToVector(m_direction).y * speedPerSec)));
}
//-----------------------------------------
void Bullet::setRotation()
{
	switch (m_rotation)
	{
	case Rotation::UpLeft:
		m_sprite.setRotation((int)Rotation::UpLeft);
		break;
	case Rotation::DownLeft:
		m_sprite.setRotation((int)Rotation::DownLeft);
		break;
	case Rotation::UpRight:
		m_sprite.setRotation((int)Rotation::UpRight);
		break;
	case Rotation::DownRight:
		m_sprite.setRotation((int)Rotation::DownRight);
		break;
	}	
}
//-------------------------------------------
