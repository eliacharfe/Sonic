#include "FactoryMovable.h"

shared_ptr<MovingObject> FactoryMovable::create(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player)
{
	auto it = FactoryMovable::getMap().find(c);
	if (it == FactoryMovable::getMap().end())
		return nullptr;
	return it->second(c, sprite, player);
}
//---------------------------------------------------------
bool FactoryMovable::registerit(const char c, pFnc func)
{
	FactoryMovable::getMap().emplace(c, func);
	return true;
}
