#include "VerticalPlattform.h"
#include "FactoryMovable.h"

bool VerticalPlattform::m_registerit = FactoryMovable::registerit('V', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject>
	{ return make_shared< VerticalPlattform>(c, sprite, player); });

VerticalPlattform::VerticalPlattform(const char c, const sf::Sprite& sprite, shared_ptr< MovingObject>& player)
	: MovingObject::MovingObject(c,sprite), m_player(player), m_rand(1)
{
	m_sprite.setOrigin(OBJECT_SIZE, OBJECT_SIZE);
}
//----------------------------------------
void VerticalPlattform::direction()
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X)
		return;
	if (getLocation()._x < m_player->getLocation()._x - 2 * DEF_SIZE_WINDOW_X)
		m_isDisposed = true;
	srand((int)time(NULL));
	if (m_clock.getElapsedTime().asSeconds() >= 5) {
		m_rand = rand() % 2; // 0 or 1
		m_clock.restart();
	}
	else m_rand = 2;

	switch (m_rand) {
	case 0: m_direction = Direction::UP; break;
	case 1: m_direction = Direction::DOWN;  break;
	default:   break;
	}
}
//-------------------------------------------------
void VerticalPlattform::move(const sf::Time& currTime)
{
	if (getLocation()._x > m_player->getLocation()._x + DEF_SIZE_WINDOW_X
		|| getLocation()._x < m_player->getLocation()._x - DEF_SIZE_WINDOW_X)
		return;
	const auto speedPerSec = currTime.asSeconds() * SPEED_PLATFORM_VERTIVAL;
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec),
		getLocation()._y + (dirToVector(m_direction).y * speedPerSec));
	m_lastLocation = getLocation(); // save in case need to use
	setLocation(location);// if not out of the level board
}
//-------------------------------------------------------
void VerticalPlattform::changeDirectionWhenCollision()
{
	if (m_direction == Direction::UP)
		m_direction = Direction::DOWN;
	else
		m_direction = Direction::UP;
	setLocation(m_lastLocation);
}
void VerticalPlattform::handleFall()
{
}
//----------------------------------------------------------


















//
//
//void VerticalPlattform::handleCollision(GameObject& gameObject)
//{
//	if (&gameObject == this)
//		return;
//	gameObject.handleCollision(*this);
//}
////----------------------------------------------------
//void VerticalPlattform::handleCollision(Wall& wall)
//{
//	changeDirectionWhenCollision();
//}
////------------------------------------------------------------
//void VerticalPlattform::handleCollision(Player& player)
//{
//	if (player.getLocation()._x <= getLocation()._x)
//	   player.setLocation(Location(getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE/2), player.getLocation()._y));
//	else if (player.getLocation()._x > getLocation()._x)
//		player.setLocation(Location(getLocation()._x + (OBJECT_SIZE + OBJECT_SIZE / 2), player.getLocation()._y));
//	player.handleCollision(*this);
//}
////------------------------------------------------------------
//void VerticalPlattform::handleCollision(Floor& floor)
//{
//	changeDirectionWhenCollision();
//}
////--------------------------------------------------------
//void VerticalPlattform::handleCollision(Spikes& gameObject)
//{
//	changeDirectionWhenCollision();
//}
////-------------------------------------------------
//void VerticalPlattform::handleCollision(HorizontalPlattform& horizontal)
//{
//	if (m_direction == Direction::RIGHT)
//		horizontal.setLocation(Location(getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE), horizontal.getLocation()._y));
//	else
//		horizontal.setLocation(Location(getLocation()._x + (OBJECT_SIZE + OBJECT_SIZE), horizontal.getLocation()._y));
//	horizontal.setLastLocation(horizontal.getLocation());
//	horizontal.handleCollision(*this);
//}
////----------------------------------------------------------
//void VerticalPlattform::handleCollision(EnemySlow& enemSlow)
//{
//	enemSlow.setLocation(Location(getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE / 2), enemSlow.getLocation()._y));
//	enemSlow.handleCollision(*this);
//}
////------------------------------------------------------
//void VerticalPlattform::handleCollision(EnemyFast& enemFast)
//{
//	enemFast.setLocation(Location(getLocation()._x - (OBJECT_SIZE + OBJECT_SIZE / 2), enemFast.getLocation()._y));
//	enemFast.handleCollision(*this);
//}
////----------------------------------------------------------------
//void VerticalPlattform::handleCollision(VerticalPlattform& gameObject)
//{
//	changeDirectionWhenCollision();
//}
