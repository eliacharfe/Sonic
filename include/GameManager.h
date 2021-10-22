#pragma once
#include "Utilities.h"
#include "Board.h"
#include "Menu.h"
#include "Player.h"

class GameManager
{
public:
	GameManager();
	~GameManager() = default;
	void run();

private:
	void readCurrLevel();
	void startLevel();
	void handleWinLoose(sf::Sprite&);
	void handleWin(sf::Sprite& );
	void handleLoose();
	void restartLevel();
	const sf::Sprite& getCurrLevelSprite();

	void setWindow();
	void setMessages(sf::Text&, sf::Text&, sf::Text&, sf::Text& , sf::Text&,sf::Font&);
	void setMessage(sf::Text& msg, const char* str,const sf::Font& font);
	void setCenterView(sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&,sf::Sprite&, sf::Sprite&, sf::Sprite&, 
		sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Text&,sf::Sprite&, sf::Text&, sf::Sprite&, sf::Text&);

	void handleMouseButtonReleased(sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&,sf::Sprite&, sf::Sprite&,sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&);
	void playButtonHandle(sf::Sprite&, sf::Sprite& );
	void pauseButtonHandle(sf::Sprite&, sf::Sprite&, sf::Sprite&);
	void handleMouseMoved(sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&,sf::Sprite&, sf::Sprite&);

	void handleDrawTextAndButton(sf::Sprite& , sf::Text&, sf::Sprite&, sf::Text&, sf::Sprite&, sf::Text&, sf::Sprite&, sf::Text&,
		sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&, sf::Sprite&,sf::Sprite& emeraldSprite, sf::Text& emerald);
	void updateTextData(sf::Sprite&, sf::Text&, sf::Sprite&, sf::Text&, sf::Text&, sf::Text&, sf::Text&);
	void restartClocks();

	void handleExitMenu();
	void handleWinGame();

	sf::RenderWindow m_window;
	Board m_board;
	sf::Event m_event;
	Location m_centerView;
	sf::Vector2f m_MousePos;
	sf::Clock m_clock;
	sf::Clock m_clockRun;
	sf::Time m_time;
	Player* m_player;
	Menu m_menu;

	bool m_win = false;
	int m_level;

	const char* m_nameFile;
};
