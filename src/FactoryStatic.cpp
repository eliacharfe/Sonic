#include "FactoryStatic.h"

unique_ptr<StaticObject> FactoryStatic::create(const char c, const sf::Sprite& sprite)
{
	auto it = FactoryStatic::getMap().find(c);
	if (it == FactoryStatic::getMap().end())
		return nullptr;
	return it->second(c, sprite);
}
//------------------------------------------------------------
bool FactoryStatic::registerit(const char c, pFnc2 func)
{
	FactoryStatic::getMap().emplace(c, func);
	return true;
}
