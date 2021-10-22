#pragma once
#include "Utilities.h"
#include "Board.h"
#include "Direction.h"

class Menu 
{
public:
	Menu(Board& board);
	void show();

	void playCurrLevelMusic();
	void pauseCurrLevelMusic();
	void lowVolumCurrLevelMusic();
	void playCurrWindow(Level level);
	void pauseCurrWindow(Level level);
	void lowVolumCurrWindow(Level level);
	void stopMusic();
	void helpWindow();
	void stopHelpWindow();
	void gameOverMenu();

	void setLevel(int level) { m_level = level; }

	void setTrue(Bool boolType);
	void setFalse(Bool boolType);
	bool is(Bool boolType) const ;

private:
	void handleObjectPressed();
	void handleButtonPressed(sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite& ,sf::Sprite&);
	void handleMouseMove(sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&);
	void pressedOnMenuObject();
	void pressedOnGridBoard();
	void createLevel();
	void createSingleObj(bool is, bool& was);
	void createObject();
	void saveLevel();
	void deleteObject();
	void clearBoard();
	void inputFromUser();

	sf::RenderWindow m_window;
	Board& m_board;
	sf::Event m_event;
	sf::Vector2f m_MousePos;

	map < Bool, bool > m_mapBool;

	int m_level;
	char m_char;
	vector < vector < char> > m_charLevelSave;
	int m_height;
	int m_width;
};
