#pragma once
#include "Utilities.h"
#include "StaticObject.h"

class FactoryStatic : public StaticObject
{
public:
	using pFnc2 = unique_ptr<StaticObject>(*)(const char , const sf::Sprite&);
	static unique_ptr<StaticObject> create(const char c, const sf::Sprite& sprite);
	static bool registerit(const char, pFnc2);
private:
	static auto& getMap() {
		static std::map<const char, pFnc2> map;
		return map;
	}
};
