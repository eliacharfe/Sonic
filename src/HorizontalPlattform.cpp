#include "HorizontalPlattform.h"
#include "FactoryMovable.h"

bool HorizontalPlattform::m_registerit = FactoryMovable::registerit('=', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject> 
	{ return make_shared<HorizontalPlattform>(c, sprite, player); });

HorizontalPlattform::HorizontalPlattform(const char c, const sf::Sprite& sprite, shared_ptr< MovingObject>& player)
	: MovingObject::MovingObject(c,sprite), m_player(player), m_rand(1)
{
	m_sprite.setOrigin(OBJECT_SIZE, OBJECT_SIZE / 2);
}
//----------------------------------------
void HorizontalPlattform::direction()
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;
	if (getLocation()._x < m_player->getLocation()._x - 2 * DEF_SIZE_WINDOW_X)
		m_isDisposed = true;
	srand((int)time(NULL));
	if (m_clock.getElapsedTime().asSeconds() >= 3) {
		m_rand = rand() % 2; // 0 or 1
		m_clock.restart();
	}
	else m_rand = 2;

	switch (m_rand) {
	case 0: m_direction = Direction::LEFT; break;
	case 1: m_direction = Direction::RIGHT;  break;
	default:   break;
	}
}
//-------------------------------------------------
void HorizontalPlattform::move(const sf::Time& currTime)
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X
		|| getLocation()._x < m_player->getLocation()._x - DEF_SIZE_WINDOW_X)
		return;
	const auto speedPerSec = currTime.asSeconds() * SPEED_PLATFORM_HORIZONTAL;
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
		              getLocation()._y + (dirToVector(m_direction).y * speedPerSec));
	m_lastLocation = getLocation(); // save in case need to use
	setLocation(location);// if not out of the level board
}
//----------------------------------------------------------
void HorizontalPlattform::changeDirectionWhenCollision()
{
	if (m_direction == Direction::LEFT)
		m_direction = Direction::RIGHT;
	else
		m_direction = Direction::LEFT;
	setLocation(m_lastLocation);
}
void HorizontalPlattform::handleFall()
{
}
//-------------------------------------------




















//void HorizontalPlattform::handleCollision(GameObject& gameObject)
//{
//	if (&gameObject == this) return;
//	gameObject.handleCollision(*this);
//}
////----------------------------------------------------
//void HorizontalPlattform::handleCollision(Wall& wall)
//{
//	changeDirectionWhenCollision();
//}
////------------------------------------------------------------
//void HorizontalPlattform::handleCollision(Player& player)
//{
//	if (getLocation()._y <= player.getLocation()._y)
//		player.stopJump();
//	player.setLocation(Location(getLocation()._x, getLocation()._y - OBJECT_SIZE));
//	player.handleCollision(*this);
//}
////------------------------------------------------------------
//void HorizontalPlattform::handleCollision(Floor& floor)
//{
//	changeDirectionWhenCollision();
//}
////---------------------------------------------------------
//void HorizontalPlattform::handleCollision(HorizontalPlattform& gameObject)
//{
//	changeDirectionWhenCollision();
//}
////--------------------------------------------------------------
//void HorizontalPlattform::handleCollision(VerticalPlattform& vertical)
//{
//	changeDirectionWhenCollision();
//	//if (m_direction == Direction::RIGHT)
//	//	setLocation(Location(getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE), getLocation()._y));
//	//else 
//	//	setLocation(Location(getLocation()._x + (OBJECT_SIZE + OBJECT_SIZE), getLocation()._y ));
//}
////---------------------------------------------------------
//
