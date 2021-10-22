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
#include "Boss.h"
#include "Bullet.h"
#include "VerticalPlattform.h"
#include "Exception.h"
#include "Image.h"
#include "Sounds.h"
#include "Location.h"
#include "Collision.h"
#include "FactoryMovable.h"
#include "FactoryStatic.h"

class Board
{
public:
	Board(); // c-tor
	Board(const Board&) = default;
	Board& operator=(const Board&) = default;
	Board(Board&&) = default;
	Board& operator=(Board&&) = default;

	void openFile(const char* nameFile);
	void readLevel();
	void allocateBoard();

	void draw(sf::RenderWindow& window) const;
	bool update(const sf::Time& currTime, const sf::Time& runTime);
	
	sf::Vector2f getSize() const { return m_sizeBoard; };
	Player* getPlayer() const { return dynamic_cast <Player*>(m_movables[PLAYER_INDEX].get()); }
	int getLife() const { return getPlayer()->getLife(); }
	int getHeart() const { return getPlayer()->getHeart(); }
	int getRings() const { return getPlayer()->getCollectedRing(); }
	bool isDead() const { return getPlayer()->is(BoolPlayer:: Dead); }
	int getEmerald() const { return m_totalEmerald; }

	void restartClocks();
	void restartGame();

	void createLevel(); // creator level mode
	void createObject(const char c, sf::Sprite& sprite, const sf::Vector2f& mousePos);// creator level mode
	void drawObjectsAtCreateLevelMode(sf::RenderWindow& window);// creator level mode
	unique_ptr < GameObject > getObject(const char c);// creator level mode
	const char getObjectType(const sf::Vector2f& mousePos)const;// creator level mode
	void deleteObject(const sf::Vector2f& mousePos);// creator level mode
	void clearObjects();// creator level mode
	void setSizeBoard(const sf::Vector2f& size) { m_sizeBoard = size; }// creator level mode
	void saveLevelToFile(const vector<vector<char>>& charBoard);// creator level mode
	void playSavedLevel();// creator level mode

private:
	void setPlaceTextLevel(Level status);
	void createObject(const char c, const sf::Sprite& sprite, shared_ptr < MovingObject> player);
	shared_ptr< MovingObject > createMovableObject(const char c, const sf::Sprite& sprite, shared_ptr < MovingObject >& player)const;
	unique_ptr< StaticObject > createUnmovableObject(const char c, const sf::Sprite& sprite)const;

	void processCollisions(MovingObject& movableObject);
	void handleFalls(MovingObject& obj);
	bool checkEmerald();
	void createBullet(MovingObject& boss);
	unique_ptr < GameObject > createObjectAtCreateMode(const char c, sf::Sprite& sprite, bool);// creator level mode
	void clear();

	vector < string > m_charBoard;
	vector < shared_ptr < MovingObject >> m_movables;
	vector < unique_ptr < StaticObject >> m_statics;

	vector < unique_ptr < GameObject >> m_menuObjects; // for creator level mode
	vector < unique_ptr < GameObject >> m_objects; // for creator level mode

	ifstream m_BoardFile;
	streamoff m_startLevelOnTextBoard;
	sf::Sprite m_sprite;
	sf::Vector2f m_sizeBoard;

	int m_totalEmerald;
	bool m_restartGame = false ;
};
//-------------------------------------------------






//template <typename FwdIt, typename Fn>
//void for_each_pair(FwdIt begin, FwdIt end, Fn fn)
//{
//	for (; begin != end; ++begin)
//		for (auto second = begin + 1; second != end; ++second)
//			fn(*begin, *second);
//}