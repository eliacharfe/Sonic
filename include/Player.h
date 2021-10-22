#pragma once
#include "MovingObject.h"

class Player : public MovingObject
{
public:
	Player(const char c, const sf::Sprite& sprite);

	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;

	void direction() override;
	void move(const sf::Time& currTime) override;
	void handleFall() override;

	void jump();
	void stopJump();
	bool moveOnCircle();

	void setTrue(BoolPlayer boolType);
	void setFalse(BoolPlayer boolType);
	bool is(BoolPlayer boolType) const;

	void nextFallAngle();
	void nextJumpAngle();
	Location nextJumpLocation();

	void setLife(int life) { m_life += life; }
	void setDamage(int damage);
	void increaseHeart() { ++m_heart; }
	void decreaseHeart() { --m_heart; }
	bool decreaseLife();
	void collectRing() { ++m_collectedRings; }
	void setLastCircleLocation(Location location) { m_lastCircleLocation = location; }

	double getAngleJump() const { return m_angleJump; }
	int getLife() const { return m_life; }
	int getHeart() const { return m_heart; }
	int getCollectedRing() const  { return m_collectedRings; }
	Location getLastCircleLocation() { return m_lastCircleLocation; }

	void resetAngleJump();
	void resetAngleCircle();
	void resetLife() { m_life = FULL_LIFE; }
	static void resetData();

private:
	void setMapBool();
	void changeDirectionWhenCollision() override {}

	map < BoolPlayer, bool > m_mapBool;

	Location m_lastCircleLocation;
	double m_angleCircle;
	double m_angleJump;

	//bool m_isStay = false;

	static int m_life;
	static int m_heart;
	static int m_collectedRings;

	static bool m_registerit;
};








/*bool m_jumpModeSpringboard = false;
bool m_jump = false;
bool m_onCircle = false;
bool m_finishLoop = false;
bool m_ballSpeedMode = false;
bool m_isDead = false;
bool m_killBoss = false;
bool m_touchEmerald = false;*/

//void stopJumpingSpringboard() { m_jumpModeSpringboard = false; }
//void startJumpingSpringboard() { m_jumpModeSpringboard = true; }
//bool isDead() const { return m_isDead; }
//bool isTouchedEmerald()const { return m_touchEmerald; }
//void touchEmerald() { m_touchEmerald = true; }

//bool isJumping() const { return m_jump; }
//void setJump() { m_jump = true; }
//bool isJumpingSpringboard() const { return m_jumpModeSpringboard; }
//void unFinishLoop() { m_finishLoop = false; }
//void finishLoop() { m_finishLoop = true; }
//bool isFinishLoop() { return m_finishLoop; }
//bool isBallSpeedMode() const { return m_ballSpeedMode; }
//void setBallSpeedMode() { m_ballSpeedMode = true; }
//bool isOnCircle() { return m_onCircle; }
//void setOnCircle() { m_onCircle = true; }
//void setOffCircle() { m_onCircle = false; }
//bool isKillBoss() const { return m_killBoss; }
//void killBoss() { m_killBoss = true; }
