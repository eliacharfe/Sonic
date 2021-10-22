#include "Menu.h"

Menu::Menu(Board& board) : m_event(sf::Event()), m_level(Level::First), m_board(board), 
                           m_char(EMPTY), m_height(0), m_width(0)
{
	m_mapBool[Bool::Running] = m_mapBool[Bool::Play] = m_mapBool[Bool::Pause] = 
	m_mapBool[Bool::SoundOn] = m_mapBool[Bool::SoundLow] = m_mapBool[Bool::SoundOff] = 
	m_mapBool[Bool::Help] = m_mapBool[Bool::GameOverBool] = m_mapBool[Bool::RestartGameBool] = 
	m_mapBool[Bool::CreateWindowBool] = 
	m_mapBool[Bool::Delete] = m_mapBool[Bool::Save] = m_mapBool[Bool::Clear] = 
	m_mapBool[Bool::isPlayer] = m_mapBool[Bool::wasPlayer] = 
	m_mapBool[Bool::isEmerald] = m_mapBool[Bool::wasEmerald] = 
	m_mapBool[Bool::isBoss] = m_mapBool[Bool::wasBoss] = false;
}
//------------------------------------------------------------------
void Menu::show()
{
	sf::RenderWindow mainMenu(sf::VideoMode(DEF_SIZE_MAIN_MENU_X, DEF_SIZE_MAIN_MENU_Y),
		"WELCOME TO SONIC", sf::Style::Default);
	Sounds::instance().playMusic(TypeMusic::MainMenuMusic);

	const auto background = Image::instance().getSprite(WELCOME);
	auto startButton = Image::instance().getSprite(START_BUTTON);
	auto createButton = Image::instance().getSprite(CREATE_BUTTON);
	auto clearButton = Image::instance().getSprite(CLEAR);
	auto exitButton = Image::instance().getSprite(EXIT_BUTTON);
	auto help = Image::instance().getSprite(HELP);
	auto soundOnButton = Image::instance().getSprite(SOUND_ON);
	auto soundOffButton = Image::instance().getSprite(SOUND_OFF);
	auto soundLowButton = Image::instance().getSprite(SOUND_LOW);

	startButton.setPosition(200, 400);
	createButton.setPosition(200, 500);
	clearButton.setPosition(200, 600);
	exitButton.setPosition(200, 700);
	help.setPosition(1200, 100);
	soundOnButton.setPosition(1100, 600);
	soundOffButton.setPosition(1300, 600);
	soundLowButton.setPosition(1200, 600);

	while (mainMenu.isOpen())
	{
		mainMenu.clear();
		mainMenu.draw(background);
		mainMenu.draw(startButton);
		mainMenu.draw(createButton);
		mainMenu.draw(clearButton);
		mainMenu.draw(exitButton);
		mainMenu.draw(help);
		mainMenu.draw(soundOnButton);
		mainMenu.draw(soundOffButton);
		mainMenu.draw(soundLowButton);
		mainMenu.display();

		while (mainMenu.pollEvent(m_event))
		{
			switch (m_event.type) {
			case sf::Event::Closed:
				exit(EXIT_SUCCESS);	break;
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::Escape)
					exit(EXIT_SUCCESS);
				if (m_event.key.code == sf::Keyboard::Space ||m_event.key.code == sf::Keyboard::Enter) {
					pauseCurrWindow(MainMenu);
					mainMenu.close();
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = mainMenu.mapPixelToCoords(sf::Mouse::getPosition(mainMenu));
				if (startButton.getGlobalBounds().contains(m_MousePos)) {
					pauseCurrWindow(MainMenu);
					Sounds::instance().playSound(TypeSound::Click);
					m_mapBool[Bool::Play] = true;
					m_mapBool[Bool::GameOverBool] = true;
					mainMenu.close();
				}
				else if (createButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrWindow(MainMenu);
					createLevel();
					if (m_mapBool[Bool::Save])
						mainMenu.close();
					else playCurrWindow(MainMenu);
				}
				else if (clearButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrWindow(MainMenu);
					m_mapBool[Bool::Clear] = true;
					clearBoard();
					m_board.restartGame();
					mainMenu.close();
				}
				else if (help.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrLevelMusic();
					pauseCurrWindow(MainMenu);
					m_mapBool[Bool::Help] = true;
					helpWindow();
				}
				else if (soundOnButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					soundOnButton.setColor(sf::Color::Yellow);
					soundOffButton.setColor(sf::Color::White);
					soundLowButton.setColor(sf::Color::White);
					playCurrWindow(MainMenu);
					m_mapBool[Bool::SoundOn] = true; m_mapBool[Bool::SoundOff] = false; m_mapBool[Bool::SoundLow] = false;
				}
				else if (soundOffButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					soundOnButton.setColor(sf::Color::White);
					soundOffButton.setColor(sf::Color::Yellow);
					soundLowButton.setColor(sf::Color::White);
					pauseCurrWindow(MainMenu);
					m_mapBool[Bool::SoundOn] = false; m_mapBool[Bool::SoundOff] = true; m_mapBool[Bool::SoundLow] = false;
				}
				else if (soundLowButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					soundOnButton.setColor(sf::Color::White);
					soundOffButton.setColor(sf::Color::White);
					soundLowButton.setColor(sf::Color::Yellow);
					lowVolumCurrWindow(MainMenu);
					m_mapBool[Bool::SoundOn] = false; m_mapBool[Bool::SoundOff] = false; m_mapBool[Bool::SoundLow] = true;
				}
				else if (exitButton.getGlobalBounds().contains(m_MousePos))
					exit(EXIT_SUCCESS);
				break;
			}
			case sf::Event::MouseMoved: {
				m_MousePos = mainMenu.mapPixelToCoords(sf::Mouse::getPosition(mainMenu));
				if (startButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					startButton.setColor(sf::Color::Green);
				}
				else startButton.setColor(sf::Color::White);
				if (exitButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					exitButton.setColor(sf::Color::Red);
				}
				else exitButton.setColor(sf::Color::White);
				if (createButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					createButton.setColor(sf::Color::Yellow);
				}
				else createButton.setColor(sf::Color::White);
				if (clearButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					clearButton.setColor(sf::Color::Magenta);
				}
				else clearButton.setColor(sf::Color::White);
				if (help.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					help.setColor(sf::Color::Magenta);
				}
				else help.setColor(sf::Color::White);

				if (soundOnButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					soundOnButton.setColor(sf::Color::Yellow);
				}
				else if (!m_mapBool[Bool::SoundOn]) soundOnButton.setColor(sf::Color::White);
				if (soundOffButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					soundOffButton.setColor(sf::Color::Yellow);
				}
				else if (!m_mapBool[Bool::SoundOff]) soundOffButton.setColor(sf::Color::White);
				if (soundLowButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					soundLowButton.setColor(sf::Color::Yellow);
				}
				else if (!m_mapBool[Bool::SoundLow]) soundLowButton.setColor(sf::Color::White);
				break;
			}
			}
		}
	}
	m_mapBool[Bool::SoundOn] = true; m_mapBool[Bool::SoundOff] = false; m_mapBool[Bool::SoundLow] = false;
	m_mapBool[Bool::Pause] = false;
	if (!m_mapBool[Bool::Help]  && !m_mapBool[Bool::GameOverBool])
		playCurrLevelMusic();
	m_board.restartClocks();
}
//--------------------------------------
void Menu::setTrue(Bool boolType)
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	m_mapBool.find(boolType)->second = true;
}
//--------------------------------------
void Menu::setFalse(Bool boolType)
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	m_mapBool.find(boolType)->second = false;
}
//---------------------------------
bool Menu::is(Bool boolType) const
{
	if ((int)boolType < 0 || (int)boolType >= m_mapBool.size())
		throw std::out_of_range("type bool doesnt exist\n");

	return m_mapBool.find(boolType)->second;
}
//------------------------------------
void Menu::playCurrLevelMusic()
{
	switch (m_level)
	{
	case Level::First:  Sounds::instance().playMusic(TypeMusic::Music1); break;
	case Level::Second: Sounds::instance().playMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().playMusic(TypeMusic::Music3); break;
	default:
		throw Exception("No sush level exist: #", m_level);
	}
}
//-------------------------------------------
void Menu::pauseCurrLevelMusic()
{
	switch (m_level)
	{
	case Level::First:  Sounds::instance().pauseMusic(TypeMusic::Music1);  break;
	case Level::Second: Sounds::instance().pauseMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().pauseMusic(TypeMusic::Music3); break;
	default:
		throw Exception("No sush level exist: #", m_level);
	}
}
//------------------------------------------------------------
void Menu::lowVolumCurrLevelMusic()
{
	switch (m_level)
	{
	case Level::First:  Sounds::instance().lowMusic(TypeMusic::Music1); break;
	case Level::Second: Sounds::instance().lowMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().lowMusic(TypeMusic::Music3); break;
	default:
		throw Exception("No sush level exist: #", m_level);
	}
}
//------------------------------------------
void Menu::playCurrWindow(Level window)
{
	switch (window)
	{
	case Level::First:  Sounds::instance().playMusic(TypeMusic::Music1); break;
	case Level::Second: Sounds::instance().playMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().playMusic(TypeMusic::Music3); break;
	case Level::MainMenu: Sounds::instance().playMusic(TypeMusic::MainMenuMusic); break;
	case Level::HelpWindow: Sounds::instance().playMusic(TypeMusic::HelpWindowMusic); break;
	case Level::GameOver: Sounds::instance().playMusic(TypeMusic::GameOverWindowMusic); break;
	case Level::CreatorMode: Sounds::instance().playMusic(TypeMusic::CreatorModeMusic); break;
	default:
		throw Exception("No sush window...");
	}
}
//---------------------------------------------------
void Menu::pauseCurrWindow(Level window)
{
	switch (window)
	{
	case Level::First:  Sounds::instance().pauseMusic(TypeMusic::Music1); break;
	case Level::Second: Sounds::instance().pauseMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().pauseMusic(TypeMusic::Music3); break;
	case Level::MainMenu: Sounds::instance().pauseMusic(TypeMusic::MainMenuMusic); break;
	case Level::HelpWindow: Sounds::instance().pauseMusic(TypeMusic::HelpWindowMusic); break;
	case Level::GameOver: Sounds::instance().pauseMusic(TypeMusic::GameOverWindowMusic); break;
	case Level::CreatorMode: Sounds::instance().pauseMusic(TypeMusic::CreatorModeMusic); break;
	default:
		throw Exception("No sush window...");
	}
}
//------------------------------------------------------
void Menu::lowVolumCurrWindow(Level window)
{
	switch (window)
	{
	case Level::First:  Sounds::instance().lowMusic(TypeMusic::Music1); break;
	case Level::Second: Sounds::instance().lowMusic(TypeMusic::Music2); break;
	case Level::Third: Sounds::instance().lowMusic(TypeMusic::Music3); break;
	case Level::MainMenu: Sounds::instance().lowMusic(TypeMusic::MainMenuMusic); break;
	case Level::HelpWindow: Sounds::instance().lowMusic(TypeMusic::HelpWindowMusic); break;
	case Level::GameOver: Sounds::instance().lowMusic(TypeMusic::GameOverWindowMusic); break;
	case Level::CreatorMode: Sounds::instance().lowMusic(TypeMusic::CreatorModeMusic); break;
	default:
		throw Exception("No sush window...");
	}
}
//-------------------------------------
void Menu::stopMusic()
{
	Sounds::instance().stopMusic(TypeMusic::Music1);
	Sounds::instance().stopMusic(TypeMusic::Music2);
	Sounds::instance().stopMusic(TypeMusic::Music3);
	Sounds::instance().stopMusic(TypeMusic::MainMenuMusic);
	Sounds::instance().stopMusic(TypeMusic::HelpWindowMusic);
	Sounds::instance().stopMusic(TypeMusic::GameOverWindowMusic);
	Sounds::instance().stopMusic(TypeMusic::CreatorModeMusic);
}
//----------------------------------------
void Menu::helpWindow()
{
	sf::RenderWindow helpWindow(sf::VideoMode(DEF_SIZE_HELP_WINDOW_X, DEF_SIZE_HELP_WINDOW_Y), "HELP", sf::Style::Default);
	Sounds::instance().playMusic(TypeMusic::HelpWindowMusic);

	auto background = Image::instance().getSprite(HELP_WINDOW);
	auto next = Image::instance().getSprite(NEXT);
	auto back = Image::instance().getSprite(BACK);
	auto stop = Image::instance().getSprite(STOP_BUTTON);

	next.setPosition(1200, 650);
	back.setPosition(2620, 650);
	stop.setPosition(2733, 650);

	auto font = Image::instance().getFont();
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(SIZE_TEXT);
	text.setFillColor(sf::Color::Magenta);
	text.setOutlineThickness(OUTLINE_THIKNESS);
	text.setOutlineColor(sf::Color::Black);
	text.setString("\n\t\t\t\t\t\t\t                                           HELP                                                                                                                                 \n\n "
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Move with the Arrow Keys,\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                          else such a collision decrease your life!\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tUp is for jumping\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                              Try to collect as many rings that you can,\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tNotice: you can move left only\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                    they increase your life.\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tat speed ball mode!\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                         At the end of the level you can get\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPress Space to enter speed ball mode, \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   the Chaus Emerald only after\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhich allows you\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                             you defeat the Boss of the level.\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tto get full speed and give you some\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t        You will pass a series of obstacles,\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tprotection and you can\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                  be carefull and speed up!\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tat times overcome physics rules.\n"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWhen jumping on an enemy you kill him,\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                                  GOOD LUCK!!\n");

	while (helpWindow.isOpen() && m_mapBool[Bool::Help])
	{
		helpWindow.clear();
		helpWindow.draw(background);
		helpWindow.draw(text);
		helpWindow.draw(next);
		helpWindow.draw(back);
		helpWindow.draw(stop);
		helpWindow.display();

		while (helpWindow.pollEvent(m_event))
		{
			auto view = helpWindow.getView();
			switch (m_event.type)
			{
			case sf::Event::Closed: {
				stopHelpWindow();
				helpWindow.close(); break;
			}
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::Escape) {
					stopHelpWindow();
					helpWindow.close();
				}
				else if ((m_event.key.code == sf::Keyboard::Right || m_event.key.code == sf::Keyboard::Space)
					&& background.getPosition().x < DEF_SIZE_HELP_WINDOW_X) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					background.setPosition(background.getPosition().x + DEF_SIZE_HELP_WINDOW_X, background.getPosition().y);
					view.setCenter(helpWindow.getView().getCenter().x + DEF_SIZE_HELP_WINDOW_X, helpWindow.getView().getCenter().y);
					helpWindow.setView(view);
				}
				else if (m_event.key.code == sf::Keyboard::Left && background.getPosition().x > 0) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					background.setPosition(background.getPosition().x - DEF_SIZE_HELP_WINDOW_X, background.getPosition().y);
					view.setCenter(helpWindow.getView().getCenter().x - DEF_SIZE_HELP_WINDOW_X, helpWindow.getView().getCenter().y);
					helpWindow.setView(view);
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = helpWindow.mapPixelToCoords(sf::Mouse::getPosition(helpWindow));
				if (next.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					background.setPosition(background.getPosition().x + 1420, background.getPosition().y);
					view.setCenter(helpWindow.getView().getCenter().x + 1420, helpWindow.getView().getCenter().y);
					helpWindow.setView(view);
				}
				else if (back.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					background.setPosition(background.getPosition().x - 1420, background.getPosition().y);
					view.setCenter(helpWindow.getView().getCenter().x - 1420, helpWindow.getView().getCenter().y);
					helpWindow.setView(view);
				}
				else if (stop.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					stopHelpWindow();
					helpWindow.close();
				}
				break;
			}
			case sf::Event::MouseMoved: {
				m_MousePos = helpWindow.mapPixelToCoords(sf::Mouse::getPosition(helpWindow));
				if (next.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					next.setColor(sf::Color::Green);
				}
				else next.setColor(sf::Color::White);
				if (back.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					back.setColor(sf::Color::Yellow);
				}
				else back.setColor(sf::Color::White);
				if (stop.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					stop.setColor(sf::Color::Yellow);
				}
				else stop.setColor(sf::Color::White);
				break;
			}
			}
		}
	}
}
//-----------------------------
void Menu::stopHelpWindow()
{
	m_mapBool.find(Bool::Pause)->second = false;
	m_mapBool.find(Bool::Help)->second = false;
	pauseCurrWindow(HelpWindow);

	if (m_mapBool.find(Bool::Running)->second) {
		if (m_mapBool.find(Bool::SoundOn)->second)
			playCurrLevelMusic();
		else if (m_mapBool.find(Bool::SoundLow)->second)
			lowVolumCurrLevelMusic();
	}
	else if (!m_mapBool.find(Bool::GameOverBool)->second) {
		if (m_mapBool.find(Bool::SoundOn)->second)
			playCurrWindow(MainMenu);
		else if (m_mapBool.find(Bool::SoundLow)->second)
			lowVolumCurrWindow(MainMenu);
	}
	else
		playCurrWindow(GameOver);
}
//-------------------------------------
void Menu::gameOverMenu()
{
	sf::RenderWindow gameOverWindow(sf::VideoMode(DEF_SIZE_HELP_WINDOW_X / 2, RADIUS*2), "GAME OVER", sf::Style::Default);
	Sounds::instance().playMusic(TypeMusic::GameOverWindowMusic);

	auto background = Image::instance().getSprite(BACKGROUND_OPTIONS);
	auto begin = Image::instance().getSprite(BEGIN);
	auto restart = Image::instance().getSprite(RESTART);
	auto backButton = Image::instance().getSprite(BACK);
	auto help = Image::instance().getSprite(HELP);
	begin.setPosition(250, 200);
	restart.setPosition(400, 200);
	backButton.setPosition(100, 100);
	help.setPosition(550, 100);
	m_mapBool[Bool::Running] = false;
	m_mapBool[Bool::GameOverBool] = true;

	while (gameOverWindow.isOpen() && m_mapBool.find(Bool::GameOverBool)->second)
	{
		gameOverWindow.clear();
		gameOverWindow.draw(background);
		gameOverWindow.draw(restart);
		gameOverWindow.draw(begin);
		gameOverWindow.draw(backButton);
		gameOverWindow.draw(help);
		gameOverWindow.display();

		while (gameOverWindow.pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed: {
				exit(EXIT_SUCCESS); break;
			}
			case sf::Event::KeyReleased: {
				if (m_event.key.code == sf::Keyboard::Enter) {
					pauseCurrWindow(GameOver);
					gameOverWindow.close();
				}
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = gameOverWindow.mapPixelToCoords(sf::Mouse::getPosition(gameOverWindow));
				if (restart.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrWindow(GameOver);
					gameOverWindow.close();
				}
				if (begin.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					m_mapBool.find(Bool::RestartGameBool)->second = true;
					m_board.restartGame();
					pauseCurrWindow(GameOver);
					gameOverWindow.close();
				}
				if (backButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrWindow(GameOver);
					show();
				}
				if (help.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::Click);
					pauseCurrLevelMusic();
					pauseCurrWindow(GameOver);
					m_mapBool.find(Bool::Help)->second = true;
					helpWindow();
				}
				break;
			}
			case sf::Event::MouseMoved: {
				m_MousePos = gameOverWindow.mapPixelToCoords(sf::Mouse::getPosition(gameOverWindow));
				if (restart.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					restart.setColor(sf::Color::Green);
				}
				else restart.setColor(sf::Color::White);
				if (begin.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					begin.setColor(sf::Color::Red);
				}
				else begin.setColor(sf::Color::White);
				if (backButton.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					backButton.setColor(sf::Color::Green);
				}
				else backButton.setColor(sf::Color::White);
				if (help.getGlobalBounds().contains(m_MousePos)) {
					Sounds::instance().playSound(TypeSound::MouseWheel);
					help.setColor(sf::Color::Green);
				}
				else help.setColor(sf::Color::White);
				break;
			}
			}
		}
	}
	m_mapBool.find(Bool::Running)->second = true;
	m_mapBool.find(Bool::GameOverBool)->second = false;
}
//------------------------------------
void Menu::createLevel()
{ // handle create new level
	sf::RenderWindow createWindow(sf::VideoMode(DEF_SIZE_GM_X, DEF_SIZE_GM_Y), "CREATE", sf::Style::Default);
	Sounds::instance().playMusic(TypeMusic::CreatorModeMusic);

	auto deleteButton = Image::instance().getSprite(DELETE_BUTTON);
	deleteButton.setPosition(OBJECT_SIZE / 2+10, 3 * OBJECT_SIZE + BUTTON_HEIGHT * 3 -10);
	auto clearButton = Image::instance().getSprite(CLEAR);
	clearButton.setPosition(OBJECT_SIZE / 2 + 10, 3 * OBJECT_SIZE + BUTTON_HEIGHT * 4 - 10);
	auto saveButton = Image::instance().getSprite(SAVE);
	saveButton.setPosition(OBJECT_SIZE / 2 + 10, 3 * OBJECT_SIZE + BUTTON_HEIGHT * 5 - 10);
	auto playButton = Image::instance().getSprite(PLAY_BUTTON);
	playButton.setPosition(OBJECT_SIZE + 10, 3 * OBJECT_SIZE + BUTTON_HEIGHT * 6 - 10);
	auto closeButton = Image::instance().getSprite(CLOSE);
	closeButton.setPosition(OBJECT_SIZE / 2 +20, 3 * OBJECT_SIZE + BUTTON_HEIGHT * 7 - 10);

	try { m_board.createLevel();
	}
	catch (Exception& e) { cerr << "Exception throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::out_of_range& e) { cerr << "Out of range throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::runtime_error& e) { cerr << "run time error throwed\n--> " << e.what(); throw; }
	catch (...) { throw; }

	inputFromUser();
	clearBoard();

	vector < vector < sf::RectangleShape  >> grid;
	grid.resize(m_width);
	for (auto& row : grid)
		row.resize(m_height);

	sf::Vector2f cellSize(OBJECT_SIZE , OBJECT_SIZE );

	auto shape = sf::RectangleShape(sf::Vector2f((float)(m_width * OBJECT_SIZE), (float)(RADIUS * 2)));
	shape.setFillColor(sf::Color(195, 195, 195));
	auto shape2 = sf::RectangleShape(sf::Vector2f((float)(RADIUS), (float)(m_height * OBJECT_SIZE)));
	shape2.setFillColor(sf::Color(195, 195, 195));

	m_mapBool.find(Bool::CreateWindowBool)->second = true;
	while (createWindow.isOpen() && m_mapBool.find(Bool::CreateWindowBool)->second)
	{
		createWindow.clear();
		createWindow.draw(shape);
		createWindow.draw(shape2);
		createWindow.draw(deleteButton);
		createWindow.draw(clearButton);
		createWindow.draw(saveButton);
		createWindow.draw(playButton);
		createWindow.draw(closeButton);

		for (int i = 3; i < m_width; i++) {
			for (int j = 6; j < m_height; j++) {
				grid[i][j].setSize(cellSize);
				grid[i][j].setOutlineColor(sf::Color::Black);
				grid[i][j].setOutlineThickness(1);
				grid[i][j].setPosition(i * cellSize.x, j * cellSize.y);
				createWindow.draw(grid[i][j]);
			}
		}
		m_board.drawObjectsAtCreateLevelMode(createWindow);
		createWindow.display();

		if (auto event = sf::Event{}; createWindow.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				createWindow.close(); break;
			case sf::Event::KeyPressed: {
				auto view = createWindow.getView();
				auto lastView = createWindow.getView();
				
				view.move(keyToDirection(event.key.code) * (float)OBJECT_SIZE);
				createWindow.setView(view);

				if (createWindow.getView().getCenter().x < DEF_SIZE_GM_X / 2 
					|| createWindow.getView().getCenter().y < DEF_SIZE_GM_Y / 2)
					createWindow.setView(lastView);
				
				if (event.key.code == sf::Keyboard::Escape)
					m_mapBool.find(Bool::CreateWindowBool)->second = false;
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_MousePos = createWindow.mapPixelToCoords(sf::Mouse::getPosition(createWindow));
				handleObjectPressed();
				handleButtonPressed(deleteButton, clearButton, saveButton,playButton, closeButton);
				break;
			}
			case sf::Event::MouseMoved: {
				m_MousePos = createWindow.mapPixelToCoords(sf::Mouse::getPosition(createWindow));
				handleMouseMove(deleteButton, clearButton, saveButton, playButton, closeButton);
				break;
			}
			}
		}
	}
	Sounds::instance().stopMusic(TypeMusic::CreatorModeMusic);
}
//-------------------------------------
void Menu::createSingleObj(bool is, bool& was)
{
	if (is && !was)
		createObject();
	if (is)
		was = true;
}
//----------------------------------------
void Menu::createObject()
{
	if (m_MousePos.x >= RADIUS) {
		int row = (int)(floor((m_MousePos.y) / OBJECT_SIZE));
		int col = (int)(floor((m_MousePos.x) / OBJECT_SIZE));

		if (row < m_height  && col < m_width) {
			sf::Vector2f mousePosGrid(col * OBJECT_SIZE + OBJECT_SIZE / 2, row * OBJECT_SIZE + OBJECT_SIZE / 2);
			auto sprite = Image::instance().getSprite(m_char);
			m_board.createObject(m_char, sprite, mousePosGrid);
			Sounds::instance().playSound(TypeSound::SmoothClick);

			row = (int)(floor((m_MousePos.y - 2 * RADIUS) / OBJECT_SIZE));
			col = (int)(floor((m_MousePos.x - RADIUS) / OBJECT_SIZE));
			m_charLevelSave[row][col] = m_char;
		}
	}
}
//--------------------------------------
void Menu::handleObjectPressed()
{
	if (m_MousePos.y < RADIUS * 2 || m_MousePos.x < RADIUS)
		pressedOnMenuObject();
	else
		pressedOnGridBoard();
}
//---------------------------------------
void Menu::pressedOnMenuObject()
{
	m_mapBool[Bool::Delete] = false;
	char c = m_board.getObjectType(m_MousePos);
	if (c != EMPTY) {
		m_char = c;
		Sounds::instance().playSound(TypeSound::SmoothClick);
	}
	if (m_char == PLAYER) m_mapBool.find(Bool::isPlayer)->second = true;
	else if (m_char == EMERALD) m_mapBool.find(Bool::isEmerald)->second = true;
	else if (m_char == BOSS) m_mapBool.find(Bool::isBoss)->second = true;
}
//----------------------------------------
void Menu::pressedOnGridBoard()
{
	if (!m_mapBool[Bool::Delete]) {
		if (m_char == PLAYER)
			createSingleObj(m_mapBool.find(Bool::isPlayer)->second, m_mapBool.find(Bool::wasPlayer)->second);
		else if (m_char == EMERALD)
			createSingleObj(m_mapBool.find(Bool::isEmerald)->second, m_mapBool.find(Bool::wasEmerald)->second);
		else if (m_char == BOSS)
			createSingleObj(m_mapBool.find(Bool::isBoss)->second, m_mapBool.find(Bool::wasBoss)->second);
		else if (m_char != EMPTY)
			createObject();
	}
	else 
		deleteObject();
}
//------------------------------------
void Menu::handleButtonPressed(sf::Sprite& deleteButton, sf::Sprite& clearButton, sf::Sprite& saveButton, sf::Sprite& playButton,  sf::Sprite& closeButton)
{
	if (deleteButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		m_mapBool.find(Bool::Delete)->second = true;
	}
	if (clearButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		clearBoard();
	}
	if (saveButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		m_mapBool.find(Bool::Save)->second = true;
		saveLevel();
	}
	if (playButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		if (m_mapBool.find(Bool::Save)->second) {
			m_board.playSavedLevel();
			m_mapBool.find(Bool::CreateWindowBool)->second = false;
		}
	}
	if (closeButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		m_mapBool.find(Bool::CreateWindowBool)->second = false;
	}
}
//-----------------------------------------------------------------------------
void Menu::handleMouseMove(sf::Sprite& deleteButton, sf::Sprite& clearButton, sf::Sprite& saveButton, sf::Sprite& playButton, sf::Sprite& closeButton)
{
	if (deleteButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		deleteButton.setColor(sf::Color::Yellow);
	}
	else deleteButton.setColor(sf::Color::White);

	if (clearButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		clearButton.setColor(sf::Color::Magenta);
	}
	else clearButton.setColor(sf::Color::White);

	if (saveButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		saveButton.setColor(sf::Color::Green);
	}
	else saveButton.setColor(sf::Color::White);

	if (playButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		playButton.setColor(sf::Color::Yellow);
	}
	else playButton.setColor(sf::Color::White);

	if (closeButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		closeButton.setColor(sf::Color::Red);
	}
	else closeButton.setColor(sf::Color::White);
}
//-----------------------------------------
void Menu::saveLevel()
{
	m_board.setSizeBoard(sf::Vector2f((float)m_width, (float)m_height));
	m_board.saveLevelToFile(m_charLevelSave);
}
//-------------------------------
void Menu::deleteObject()
{
	m_board.deleteObject(m_MousePos);
	int row = (int)(floor((m_MousePos.y - 2 * RADIUS) / OBJECT_SIZE));
	int col = (int)(floor((m_MousePos.x - RADIUS) / OBJECT_SIZE));

	if (row < m_height && col < m_width)
		m_charLevelSave[row][col] = EMPTY;

	if (typeid(m_board.getObject(m_char)) == typeid(Player))
		m_mapBool.find(Bool::isPlayer)->second = false;
	if (typeid(m_board.getObject(m_char)) == typeid(Emerald))
		m_mapBool.find(Bool::isEmerald)->second = false;
	if (typeid(m_board.getObject(m_char)) == typeid(Boss))
		m_mapBool.find(Bool::isBoss)->second = false;
	m_mapBool.find(Bool::wasPlayer)->second = m_mapBool.find(Bool::wasEmerald)->second =
		m_mapBool.find(Bool::wasBoss)->second = false;
}
//------------------------------------------------
void Menu::clearBoard()
{
	m_board.clearObjects();
	for (auto& line : m_charLevelSave) 
		for (auto& c : line) 
			c = EMPTY;

	m_mapBool.find(Bool::isPlayer)->second = m_mapBool.find(Bool::isEmerald)->second = 
	m_mapBool.find(Bool::isBoss)->second = m_mapBool.find(Bool::wasPlayer)->second = 
	m_mapBool.find(Bool::wasEmerald)->second = m_mapBool.find(Bool::wasBoss)->second = false;
}
//-----------------------------------
void Menu::inputFromUser()
{
	cout << "Enter Height: ";
	cin >> m_height;
	cout << "Enter Width: ";
	cin >> m_width;

	m_charLevelSave.resize(m_height);
	for (auto& line : m_charLevelSave)
		line.resize(m_width);
}
//---------------------------------------------------