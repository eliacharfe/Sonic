#pragma once
#include "Utilities.h"

class Image // Singleton class
{
public:
	static Image& instance();
	const sf::Sprite& getSprite(const char c);
	const sf::Font& getFont() const;

private:
	Image();
	Image(const Image&) = default;
	Image& operator=(const Image&) = default;

	map < TypeImage, sf::Texture > m_mapTexture;
	map < TypeImage, sf::Sprite > m_mapSprite;

	sf::Font m_font;
};













//const sf::Sprite& getSprite(Type type) ;