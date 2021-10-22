#pragma once
#include "GameObject.h"
#include "Direction.h"

class MovingObject : public GameObject
{
public:
	MovingObject(const char c, const sf::Sprite& sprite);
	MovingObject(const MovingObject&) = default;
	MovingObject& operator=(const MovingObject&) = default;
	MovingObject(MovingObject&&) = default;
	MovingObject& operator=(MovingObject&&) = default;
	virtual ~MovingObject() = default;

	virtual void direction() = 0;
	virtual void move(const sf::Time& currTime) = 0;
	virtual void handleFall() = 0;

	Direction getDirection() const { return m_direction; }
	void setDirection(Direction dir) { m_direction = dir; }
	Location getLastLocation() const { return m_lastLocation; }
	void restartClock() { m_clock.restart(); }
	void setLastLocation(Location location) { m_lastLocation = location; }

	void setSizeBoard(sf::Vector2f size) { m_sizeBoard = size; }
	void setLevel(int level) { m_level = level; }
protected:
	
	virtual void changeDirectionWhenCollision() = 0;
	Direction getLastDirection() const { return m_lastDirection; }
	
	Location m_lastLocation;
	Direction m_direction = Direction::STAY;
	Direction m_lastDirection = Direction::STAY;
	sf::Clock m_clock;
	sf::Vector2f m_sizeBoard;

	int m_level;

private:

};
