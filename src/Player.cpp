#include "Player.h"
#include "FactoryMovable.h"

bool Player::m_registerit = FactoryMovable::registerit('@', [](const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player) -> shared_ptr<MovingObject>
	{ return make_shared<Player>(c, sprite); });

int Player::m_life = FULL_LIFE;
int Player::m_heart = START_HEART;
int Player::m_collectedRings = 0;

Player::Player(const char c, const sf::Sprite& sprite) 
	: MovingObject::MovingObject(c,sprite), m_lastCircleLocation(0, 0)
	, m_angleCircle(START_CIRCLE), m_angleJump(START_JUMP)
{ 
	setMapBool();
}
//-------------------------------
void Player::direction()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (m_mapBool.find(BoolPlayer::Jumping)->second 
			&& !m_mapBool.find(BoolPlayer::TouchEmerald)->second )
			return;
		Sounds::instance().playSound(TypeSound::JumpSound);
		m_mapBool.find(BoolPlayer::Jumping)->second = true;
		if (!m_mapBool.find(BoolPlayer::OnCircle)->second) {
			resetAngleJump();
			m_lastLocation = getLocation();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_mapBool.find(BoolPlayer::BallSpeed)->second = false;
		if (!m_mapBool.find(BoolPlayer::JumpingSpringboard)->second)
			setSprite(Image::instance().getSprite(GET_DOWN));
		m_direction = Direction::DOWN;
		if (m_lastDirection != Direction::DOWN)
			m_clock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!m_mapBool.find(BoolPlayer::JumpingSpringboard)->second)
			setSprite(Image::instance().getSprite(PLAYER));
		m_direction = Direction::RIGHT;
		if (m_lastDirection != Direction::RIGHT)
			m_clock.restart();
		if (m_mapBool[BoolPlayer::Stay]) {
			m_clock.restart();
			m_mapBool[BoolPlayer::Stay] = false;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!m_mapBool.find(BoolPlayer::JumpingSpringboard)->second)
			setSprite(Image::instance().getSprite(PLAYER_LEFT_START));
		if (m_mapBool.find(BoolPlayer::TouchEmerald)->second)
			m_direction = Direction::LEFT;
		if (m_mapBool.find(BoolPlayer::Stay)->second) {
			m_clock.restart();
			m_mapBool.find(BoolPlayer::Stay)->second = false;
		}
	}
	else if (!m_mapBool[BoolPlayer::Jumping]) {
		if (!m_mapBool.find(BoolPlayer::OnCircle)->second && !m_mapBool.find(BoolPlayer::Stay)->second) {
			m_clock.restart();
			m_mapBool.find(BoolPlayer::Stay)->second = true;
		}
		if (!m_mapBool.find(BoolPlayer::JumpingSpringboard)->second) {
			if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() <= 0.3)
				setSprite(Image::instance().getSprite(PLAYER));
			else if (m_clock.getElapsedTime().asSeconds() > 0.3 && m_clock.getElapsedTime().asSeconds() <= 0.6)
				setSprite(Image::instance().getSprite(PLAYER_STAY1));
			else if (m_clock.getElapsedTime().asSeconds() > 0.6 && m_clock.getElapsedTime().asSeconds() <= 0.9)
				setSprite(Image::instance().getSprite(PLAYER_STAY2));
			else if (m_clock.getElapsedTime().asSeconds() > 0.9 && m_clock.getElapsedTime().asSeconds() <= 1.2)
				setSprite(Image::instance().getSprite(PLAYER_STAY3));
			else if (m_clock.getElapsedTime().asSeconds() > 1.2 && m_clock.getElapsedTime().asSeconds() <= 1.7)
				setSprite(Image::instance().getSprite(PLAYER_STAY4));
			else m_mapBool.find(BoolPlayer::Stay)->second = false;
		}

		m_direction = Direction::STAY;
		m_mapBool.find(BoolPlayer::BallSpeed)->second = false;
	}

	if (m_mapBool.find(BoolPlayer::KillBoss)->second || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_direction = Direction::LEFT;
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (!m_mapBool.find(BoolPlayer::JumpingSpringboard)->second)
					setSprite(Image::instance().getSprite(PLAYER_LEFT_START));
			}
			if (m_lastDirection != Direction::LEFT)
				m_clock.restart();
		}
	}
}
//------------------------------------------------------
void Player::move(const sf::Time& currTime)
{
	if (m_mapBool.find(BoolPlayer::OnCircle)->second)
		if (!moveOnCircle())
			m_mapBool.find(BoolPlayer::OnCircle)->second = false;
	if (m_mapBool.find(BoolPlayer::Jumping)->second) {
		jump();
		return;
	}
	if (m_direction == Direction::RIGHT || m_direction == Direction::LEFT)
		m_lastDirection = m_direction;
	auto delta = 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_mapBool.find(BoolPlayer::JumpingSpringboard)->second
		&& m_direction != Direction::DOWN) {
		delta = 4;
		setSprite(Image::instance().getSprite(BALL_SPEED));
		m_mapBool[BoolPlayer::BallSpeed] = true;
	}
	else {
		if (m_direction != Direction::RIGHT)
			m_mapBool[BoolPlayer::BallSpeed]= false;
		if (m_direction == Direction::RIGHT && !m_mapBool.find(BoolPlayer::JumpingSpringboard)->second)
		{
			if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() <= 0.2)
				setSprite(Image::instance().getSprite(READY_RIGHT));
			else if (m_clock.getElapsedTime().asSeconds() > 0.2 && m_clock.getElapsedTime().asSeconds() < 0.4) {
				delta = 1.2f;
				setSprite(Image::instance().getSprite(WALK_RIGHT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 0.4 && m_clock.getElapsedTime().asSeconds() < 0.7) {
				delta = 1.5f;
				setSprite(Image::instance().getSprite(RUN0_RIGHT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 0.7 && m_clock.getElapsedTime().asSeconds() < 1) {
				delta = 1.8f;
				setSprite(Image::instance().getSprite(RUN1_RIGHT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 1 && m_clock.getElapsedTime().asSeconds() < 1.5) {
				delta = 2.4f;
				setSprite(Image::instance().getSprite(RUN_RIGHT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 1.5 && m_clock.getElapsedTime().asSeconds() < 2.5) {
				delta = 3;
				setSprite(Image::instance().getSprite(RUN2_RIGHT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 2.5) {
				delta = 4;
				setSprite(Image::instance().getSprite(BALL_SPEED));
				m_mapBool[BoolPlayer::BallSpeed] = true;
			}
		}
	}
	if (m_direction == Direction::LEFT) // in case kill boss or in ball speed mode
	{
		if (!m_mapBool.find(BoolPlayer::BallSpeed)->second && !m_mapBool.find(BoolPlayer::JumpingSpringboard)->second) {
			if (m_clock.getElapsedTime().asSeconds() > 0 && m_clock.getElapsedTime().asSeconds() <= 0.2)
				setSprite(Image::instance().getSprite(READY_LEFT));
			else if (m_clock.getElapsedTime().asSeconds() > 0.2 && m_clock.getElapsedTime().asSeconds() < 0.4) {
				delta = 1.5f;
				setSprite(Image::instance().getSprite(WALK_LEFT));
			}
			else if (m_clock.getElapsedTime().asSeconds() >= 0.4 && m_clock.getElapsedTime().asSeconds() < 0.7) {
				delta = 2;
				setSprite(Image::instance().getSprite(RUN0_LEFT));
			}
			else {
				delta = 4;
				setSprite(Image::instance().getSprite(BALL_SPEED));
				m_mapBool.find(BoolPlayer::BallSpeed)->second = true;
			}
		}
	}
	const auto speedPerSec = currTime.asSeconds() * SPEED_PLAYER;
	Location location(getLocation()._x + (dirToVector(m_direction).x * speedPerSec * delta),
		getLocation()._y + (dirToVector(m_direction).y * speedPerSec * delta));
	m_lastLocation = getLocation(); // in case collides wall/floor etc
	setLocation(location);

	if (getLocation()._x > m_sizeBoard.x * OBJECT_SIZE || getLocation()._y > m_sizeBoard.y * OBJECT_SIZE
		|| getLocation()._x < 0 || getLocation()._y < 0) {
		m_mapBool.find(BoolPlayer::Dead)->second = true;
	}
}
//----------------------------------
void Player::handleFall()
{
	Location NewLocation(getLocation()._x, getLocation()._y + 30);

	if (is(BoolPlayer::JumpingSpringboard) /*isJumpingSpringboard()*/)
		setLocation(Location(getLocation()._x + 5, getLocation()._y - OBJECT_SIZE / 2));
	if (is(BoolPlayer::Jumping) && getAngleJump() >= HALF_JUMP) {
		if (getAngleJump() >= COMPLETE_JUMP) {
			setTrue(BoolPlayer::BallSpeed);
			stopJump();
		}
		else {
			nextFallAngle();
			setLocation(nextJumpLocation());
		}
	}
	else if (!is(BoolPlayer::JumpingSpringboard) && !is(BoolPlayer::Jumping))
		setLocation(NewLocation);// fall down
}
//------------------------------------------
bool Player::moveOnCircle()
{
	m_mapBool.find(BoolPlayer::Jumping)->second = false;
	m_lastLocation = getLocation();
	setLocation(Location((float)(RADIUS * std::cos(m_angleCircle) + m_lastCircleLocation._x),
		                 (float)(RADIUS * std::sin(m_angleCircle) + m_lastCircleLocation._y)));
	               
	m_angleCircle -= 0.2;
	m_sprite.setOrigin(OBJECT_SIZE, OBJECT_SIZE);
	m_sprite.setRotation((float)(m_angleCircle * TO_DEGREES - ROTATE));

	if (m_angleCircle < FULL_CIRCLE) {
		m_mapBool.find(BoolPlayer::FinishLoop)->second = true;
		m_sprite.setOrigin(OBJECT_SIZE / 2, OBJECT_SIZE / 2);
		setSprite(Image::instance().getSprite(PLAYER));
		return false;
	}
	return true;
}
//-------------------------------------------------------
void Player::jump()
{
	if (m_mapBool.find(BoolPlayer::JumpingSpringboard)->second) {
		m_mapBool.find(BoolPlayer::Jumping)->second = false;
		return;
	}
	m_mapBool.find(BoolPlayer::Jumping)->second = true;
	setSprite(Image::instance().getSprite(JUMP));
	if (m_angleJump >= START_JUMP && m_angleJump < HALF_JUMP) { // from pi to 2 * pi
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			m_mapBool.find(BoolPlayer::BallSpeed)->second = true;
			setSprite(Image::instance().getSprite(BALL_SPEED));
		}
		else {
			m_mapBool.find(BoolPlayer::BallSpeed)->second = false;
			setSprite(Image::instance().getSprite(JUMP));
		}
		setLocation(nextJumpLocation());
		nextJumpAngle();
	}
	else
		setSprite(Image::instance().getSprite(SPRING_J_R));
}
//-----------------------------------------------
Location Player::nextJumpLocation()
{
	return Location((float)(RADIUS_JUMP * std::cos(m_angleJump) + m_lastLocation._x + RADIUS_JUMP),
		            (float)(RADIUS_JUMP * std::sin(m_angleJump) + m_lastLocation._y));
}
//-----------------------------------------------------
void Player::stopJump()
{
	m_mapBool.find(BoolPlayer::Jumping)->second = false;
	if (!m_mapBool.find(BoolPlayer::OnCircle)->second) {
		m_lastLocation = getLocation();
		resetAngleJump();
	}
}
//-------------------------------------------------------------
void Player::resetData()
{
	m_life = FULL_LIFE;
	m_heart = START_HEART;
	m_collectedRings = 0;
}
//-----------------------------------
void Player::setDamage(int damage)
{
	m_life -= damage;
	if (m_life <= 0)
		!decreaseLife() ? m_mapBool.find(BoolPlayer::Dead)->second = true : m_life = FULL_LIFE;
}
//---------------------------------
bool Player::decreaseLife()
{
	--m_heart;
	return m_heart <= 0 ? false : true;
}
//-----------------------------------------
void Player::setTrue(BoolPlayer boolType)
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	m_mapBool.find(boolType)->second = true;
}
//---------------------------------------
void Player::setFalse(BoolPlayer boolType)
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	m_mapBool.find(boolType)->second = false;
}
//-------------------------------------------------
bool Player::is(BoolPlayer boolType) const
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	return m_mapBool.find(boolType)->second;
}
//-------------------------------
void Player::resetAngleJump()
{
	m_angleJump = START_JUMP;
}
//-----------------------------
void Player::resetAngleCircle()
{
	m_angleCircle = START_CIRCLE;
}
//-------------------------------------
void Player::nextFallAngle()
{
	m_angleJump += FALL_ANGLE;
}
//-----------------------------------
void Player::nextJumpAngle()
{
	m_angleJump += JUMP_ANGLE;
}
//----------------------------------------------
void Player::setMapBool()
{
	m_mapBool[BoolPlayer::Jumping] = m_mapBool[BoolPlayer::JumpingSpringboard] = 
	m_mapBool[BoolPlayer::FinishLoop] = m_mapBool[BoolPlayer::OnCircle] = 
	m_mapBool[BoolPlayer::Dead] = m_mapBool[BoolPlayer::KillBoss] =
	m_mapBool[BoolPlayer::BallSpeed] = m_mapBool[BoolPlayer::TouchEmerald] = 
	m_mapBool[BoolPlayer::Stay] = false;
}
