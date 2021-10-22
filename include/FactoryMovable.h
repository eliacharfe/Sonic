#pragma once
#include "Utilities.h"
#include "MovingObject.h"

class FactoryMovable : public MovingObject
{
public:
	using pFnc = shared_ptr<MovingObject>(*)(const char , const sf::Sprite& , shared_ptr<MovingObject>& );
	static shared_ptr<MovingObject> create(const char c, const sf::Sprite& sprite, shared_ptr<MovingObject>& player);
	static bool registerit(const char , pFnc);
private:
	static auto& getMap() {
		static std::map<const char, pFnc> map;
		return map;
	}
};
