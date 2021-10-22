#pragma once
#include "Utilities.h"
#include "Sounds.h"
#include "Image.h"
#include "Location.h"

class Player;
class Wall;
class Floor;
class Pole;
class Ring;
class Springboard;
class Spikes;
class HorizontalPlattform;
class Emerald;
class Circle;
class Enemy;
class EnemySlow;
class EnemyFast;
class VerticalPlattform;

class GameObject
{
public:
	GameObject(const char c,const sf::Sprite& sprite) ;
	GameObject(const GameObject&) = default;
	GameObject& operator=(const GameObject&) = default;
	GameObject(GameObject&&) = default;
	GameObject& operator=(GameObject&&) = default;
	virtual ~GameObject() = default;

	void draw(sf::RenderWindow& window) const;
	bool collidesWith(const GameObject& gameObject) const;

	void setLocation(const Location& location);
	void setSprite(const sf::Sprite& sprite);
	Location getLocation() const;
	//const sf::Sprite getSprite() const { return m_sprite; }
	sf::Sprite getSprite()  const { return m_sprite; }
	bool isDisposed() const  { return m_isDisposed; }
	void setDisposed() { m_isDisposed = true; }

	char getChar() const { return m_char; }

protected:
	sf::Sprite m_sprite;
	bool m_isDisposed = false;
	const char m_char;
private:
	
};