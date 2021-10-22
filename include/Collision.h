#pragma once
#include "Utilities.h"
#include "Player.h"
#include "Floor.h"
#include "Pole.h"
#include "Wall.h"
#include "Ring.h"
#include "Springboard.h"
#include "Spikes.h"
#include "HorizontalPlattform.h"
#include "Emerald.h"
#include "Circle.h"
#include "EnemySlow.h"
#include "EnemyFast.h"
#include "VerticalPlattform.h"
#include "Boss.h"
#include "Bullet.h"
#include "Exception.h"
#include <typeinfo>
#include <typeindex>

using HitFunctionPtr = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

void processCollision(GameObject& object1, GameObject& object2);
