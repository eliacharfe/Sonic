#include "GameObject.h"

GameObject::GameObject(const char c, const sf::Sprite& sprite)
	: m_sprite(sprite), m_char(c)
{
	m_sprite.setOrigin(OBJECT_SIZE / 2, OBJECT_SIZE / 2);
}
//-------------------------------------------------
void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
//------------------------------------
bool GameObject::collidesWith(const GameObject& gameObject) const
{
	return m_sprite.getGlobalBounds().intersects(gameObject.m_sprite.getGlobalBounds());
}
//-------------------------------------------------
void GameObject::setSprite(const sf::Sprite& sprite)
{
	Location location = vecTotLocation(m_sprite.getPosition());
	m_sprite = sprite;
	m_sprite.setOrigin(OBJECT_SIZE / 2, OBJECT_SIZE / 2);
	m_sprite.setPosition(move(location._x), move(location._y));
}
//--------------------------------------
void GameObject::setLocation(const Location& location)
{
	m_sprite.setPosition(location._x, location._y);
}
//---------------------------------------
Location GameObject::getLocation() const
{
	return vecTotLocation(m_sprite.getPosition());
}
//--------------------------------------------------