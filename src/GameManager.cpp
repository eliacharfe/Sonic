#include "GameManager.h"

GameManager::GameManager() : m_MousePos(0, 0), m_event(sf::Event()), m_level(Level::First),
                             m_menu(m_board), m_centerView(0, 0), m_player(nullptr),
                             m_nameFile("Board.txt")
{}
//----------------------------------------------
void GameManager::run() // main loop --> been call recursively when at create level we save the level
{ // and play or when we want to clear the saved level and play normally
	try {
		m_board.openFile(m_nameFile);
		if (!m_menu.is(Bool::Save)) { 
			readCurrLevel();
			m_menu.show();
			if (m_menu.is(Bool::Clear))
				handleExitMenu(); // if clear
		}
		else handleExitMenu(); // if save level
		setWindow();
		m_menu.setLevel(m_level);
		m_menu.playCurrLevelMusic();
	}
	catch (Exception& e) { cerr << "Exception throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::out_of_range& e) { cerr << "Out of range throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::runtime_error& e) { cerr << "Run time error throwed\n--> " << e.what(); throw; }
	catch (...) { throw; }

	auto font = Image::instance().getFont();
	auto background = getCurrLevelSprite();
	auto playButton = Image::instance().getSprite(PLAY_BUTTON);
	auto pauseButton = Image::instance().getSprite(PAUSE_BUTTON);
	auto stopButton = Image::instance().getSprite(STOP_BUTTON);
	auto soundOnButton = Image::instance().getSprite(SOUND_ON);
	soundOnButton.setColor(sf::Color::Yellow);
	auto soundOffButton = Image::instance().getSprite(SOUND_OFF);
	auto soundLowButton = Image::instance().getSprite(SOUND_LOW);
	auto restart = Image::instance().getSprite(RESTART);
	auto backButton = Image::instance().getSprite(BACK);
	auto pause = Image::instance().getSprite(PAUSE);
	auto help = Image::instance().getSprite(HELP);
	auto emeraldSprite = Image::instance().getSprite(EMERALD);
	auto timeSprite = Image::instance().getSprite(TIME);
	auto ringsSprite = Image::instance().getSprite(RING);
	auto heartSprite = Image::instance().getSprite(HEART);
	auto lifeSprite = Image::instance().getSprite(LIFE_BAR);

	m_player = m_board.getPlayer();
	m_centerView = move(Location(m_player->getLocation()._x + 300, m_player->getLocation()._y - 180));

	sf::Text life, heart, rings, time, emerald;
	setMessages(life, heart, rings, time, emerald, font);
	m_menu.setFalse(Bool::Save);
	restartClocks();
	m_clockRun.restart();
	m_menu.setTrue(Bool::Running);

	while (m_window.isOpen() &&  m_menu.is(Bool::Running))
	{
		while (m_window.pollEvent(m_event))
		{
			switch (m_event.type) {
			case sf::Event::Closed:
				m_window.close(); break;
			case sf::Event::KeyReleased:
				if (m_event.key.code == sf::Keyboard::Escape) {
					pauseButtonHandle(playButton, pauseButton, pause);
					m_menu.show();
					handleExitMenu(); 
					restartClocks();
				}
				break;
			case sf::Event::MouseButtonReleased:
				m_MousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				handleMouseButtonReleased(playButton, pauseButton, stopButton, soundOnButton, soundOffButton, soundLowButton, restart, backButton, pause, help);
				break;
			case sf::Event::MouseMoved:
				m_MousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				handleMouseMoved(playButton, pauseButton, stopButton, soundOnButton, soundOffButton, soundLowButton, restart, backButton, help);
				break;
			}
		}
		setCenterView(background, playButton, pauseButton, stopButton, soundOnButton, soundOffButton, soundLowButton,
			restart, backButton, help, timeSprite, time, emeraldSprite, emerald, ringsSprite, rings);

		m_window.clear();
		m_window.draw(background);
		m_board.draw(m_window);
		handleDrawTextAndButton(lifeSprite, life, heartSprite, heart, ringsSprite, rings, timeSprite, time,
			playButton, pauseButton, stopButton, soundOnButton, soundOffButton, soundLowButton, restart, backButton, help, emeraldSprite, emerald);
		m_time = m_clockRun.getElapsedTime(); // for time running of the level
		const auto currTime = m_clock.restart();// for speed move

		if (!m_menu.is(Bool::Pause)) // if playing
		{
			if (m_board.update(currTime, m_time)) { // move and update
				m_win = true; // if win
				handleWinLoose(background);
			}
			else if (m_board.isDead()) // if loose (player is dead)
				handleWinLoose(background);
			updateTextData(lifeSprite, life, heartSprite, heart, rings, time, emerald);
		}
		else m_window.draw(pause); // if pressed pause
		m_window.display();
	}
}
//------------------------------
void GameManager::readCurrLevel()
{
	try {
		m_board.readLevel();
		m_board.allocateBoard();
	}
	catch (Exception& e) { cerr << "Exception throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::out_of_range& e) { cerr << "Out of range throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::runtime_error& e) { cerr << "run time error throwed\n--> " << e.what(); throw; }
	catch (...) { throw; }
}
//-------------------------------------------
void GameManager::startLevel()
{
	m_player = m_board.getPlayer();
	m_centerView = move(Location(m_player->getLocation()._x + 300.0f, m_player->getLocation()._y - 180));
	m_clockRun.restart();
	restartClocks();
	m_win = false;
	m_menu.setTrue(Bool::SoundOn); m_menu.setFalse(Bool::SoundOff); m_menu.setFalse(Bool::SoundLow);
}
//----------------------------------------------------
void GameManager::handleWinLoose(sf::Sprite& background)
{
	m_win ? handleWin(background) : handleLoose();

	if (!m_menu.is(Bool::RestartGameBool)) {
		readCurrLevel();
		startLevel();
	}
	else {
		m_level = Level::First;
		background = getCurrLevelSprite();
		m_menu.setFalse(Bool::RestartGameBool);
	}
}
//------------------------------------------------
void GameManager::handleWin(sf::Sprite& background)
{ // win level
	++m_level;
	Sounds::instance().playSound(TypeSound::LevelComplete);
	if (m_level == Fourth) 
		handleWinGame();
	m_menu.setLevel(m_level);
	m_menu.stopMusic();
	m_window.clear();
	m_window.draw(background);
	m_board.draw(m_window);
	m_window.display();
	Sleep(FOUR_SEC);
	background = getCurrLevelSprite();
	m_menu.playCurrLevelMusic();
}
//-------------------------------
void GameManager::handleLoose()
{ // game over
	m_menu.stopMusic();
	Sounds::instance().playSound(TypeSound::GameOverSound);
	auto gameOver = Image::instance().getSprite(GAME_OVER);
	gameOver.setOrigin(700, 200);
	gameOver.setPosition(m_centerView._x, m_centerView._y);
	m_window.draw(gameOver);
	m_window.display();
	Sleep(SEVEN_SEC);
	m_menu.gameOverMenu();
	restartLevel();
}
//------------------------------------
void GameManager::restartLevel()
{ // if want to resart from begging of the level
	Sounds::instance().playSound(TypeSound::Click);
	m_menu.stopMusic();
	Player::resetData();
	readCurrLevel();
	startLevel();
	m_menu.playCurrLevelMusic();
	restartClocks();
}
//---------------------------------------------------------
const sf::Sprite& GameManager::getCurrLevelSprite()
{
	switch (m_level)
	{
	case Level::First: return Image::instance().getSprite(BACKGROUND1);  break;
	case Level::Second: return Image::instance().getSprite(BACKGROUND2); break;
	case Level::Third: return Image::instance().getSprite(BACKGROUND3); break;
	}
	return Image::instance().getSprite(BACKGROUND1);
}
//-------------------------------------------------------------
void GameManager::setWindow()
{
	sf::Vector2i sizeWindow(DEF_SIZE_WINDOW_X, DEF_SIZE_WINDOW_Y);
	m_window.create(sf::VideoMode(sizeWindow.x, sizeWindow.y),
		"SONIC", sf::Style::Close | sf::Style::Titlebar);
	m_window.setFramerateLimit(80);
}
//--------------------------------------------------------------------
void GameManager::setMessages(sf::Text& life, sf::Text& heart, sf::Text& rings, sf::Text& time, sf::Text& emerald, sf::Font& font)
{
	setMessage(life, "100", font);
	setMessage(heart, "3", font);
	setMessage(rings, "-1", font);
	setMessage(time, "-1", font);
	setMessage(emerald, "-1", font);
}
//------------------------------------------------
void GameManager::setMessage(sf::Text& msg, const char* str, const sf::Font& font)
{
	msg.setFont(font);
	msg.setCharacterSize(SIZE_TEXT);
	msg.setFillColor(sf::Color::Magenta);
	msg.setOutlineThickness(OUTLINE_THIKNESS);
	msg.setOutlineColor(sf::Color::Green);
	if (strcmp(str, "-1") == 0) {
		msg.setOutlineColor(sf::Color::Yellow);
		msg.setFillColor(sf::Color::Black);
	}
	msg.setString(str);
}
//----------------------------------------
void GameManager::setCenterView(sf::Sprite& background, sf::Sprite& playButton, sf::Sprite& pauseButton, sf::Sprite& stopButton,
	sf::Sprite& soundOn, sf::Sprite& soundOff, sf::Sprite& soundLow, sf::Sprite& restart, sf::Sprite& backButton, sf::Sprite& help, sf::Sprite& timeSprite, sf::Text& time,
	sf::Sprite& emeraldSprite, sf::Text& emerald, sf::Sprite& ringsSprite, sf::Text& rings)
{
	auto view = m_window.getView();
	if (m_player->getDirection() == Direction::RIGHT) // direction right
		m_centerView = Location(m_player->getLocation()._x + 300.0f, m_player->getLocation()._y - 130);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // direction left
		m_centerView = Location(m_player->getLocation()._x - 300.0f, m_player->getLocation()._y - 130);
	else if (m_player->getDirection() == Direction::UP) // direction up
		m_centerView = Location(m_player->getLocation()._x, m_player->getLocation()._y - 150);
	else if (m_player->getDirection() == Direction::DOWN) /// direction down
		m_centerView = Location(m_player->getLocation()._x, m_player->getLocation()._y + 150);
	else  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // dirction in place (0, 0)
		if (m_player->getLocation()._y > m_centerView._y + 150)
			m_centerView = move(Location(m_player->getLocation()._x, m_player->getLocation()._y + 150));
		else if (m_player->getLocation()._y < m_centerView._y - 200)
			m_centerView = Location(m_player->getLocation()._x, m_player->getLocation()._y - 150);
		if (m_player->getLocation()._x > m_centerView._y + 300)
			m_centerView = Location(m_player->getLocation()._x + 300.0f, m_player->getLocation()._y - 150);
	}
	view.setCenter(locationToVector(m_centerView));
	m_window.setView(view);
	background.setTextureRect(sf::IntRect((int)(m_centerView._x - 800), (int)(m_centerView._y - 500), (int)(DEF_SIZE_WINDOW_X), (int)(DEF_SIZE_WINDOW_Y + 200)));
	background.setPosition(m_centerView._x, m_centerView._y);
	playButton.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 - 350, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	pauseButton.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 - 250, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	stopButton.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 - 150, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	soundOn.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 50, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	soundLow.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 135, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	soundOff.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 220, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	backButton.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 350, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	restart.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 450, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	help.setPosition(m_window.getView().getCenter().x - DEF_SIZE_WINDOW_X / 4 + 550, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 120);
	ringsSprite.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 620, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 170);
	rings.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 530, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 160);
	emeraldSprite.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 450, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 170);
	emerald.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 350, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 160);
	timeSprite.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 240, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 130);
	time.setPosition(m_window.getView().getCenter().x + DEF_SIZE_WINDOW_X / 2 - 180, m_window.getView().getCenter().y - DEF_SIZE_WINDOW_Y / 4 - 160);
}
//------------------------------------------------------------------
void GameManager::handleMouseButtonReleased(sf::Sprite& playButton, sf::Sprite& pauseButton, sf::Sprite& stopButton,
	sf::Sprite& soundOnButton, sf::Sprite& soundOffButton, sf::Sprite& soundLowButton, sf::Sprite& restart, sf::Sprite& backButton, sf::Sprite& pause, sf::Sprite& help)
{
	if (playButton.getGlobalBounds().contains(m_MousePos))
		playButtonHandle(playButton, pauseButton);
	else if (pauseButton.getGlobalBounds().contains(m_MousePos))
		pauseButtonHandle(playButton, pauseButton, pause);
	else if (stopButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		m_menu.setFalse(Bool::Running);
	}
	else if (soundOnButton.getGlobalBounds().contains(m_MousePos)) {
		if (m_menu.is(Bool::Pause)) return;
		Sounds::instance().playSound(TypeSound::Click);
		soundOnButton.setColor(sf::Color::Yellow);
		soundOffButton.setColor(sf::Color::White);
		soundLowButton.setColor(sf::Color::White);
		m_menu.playCurrLevelMusic();
		m_menu.setTrue(Bool::SoundOn); m_menu.setFalse(Bool::SoundOff); m_menu.setFalse(Bool::SoundLow);
	}
	else if (soundOffButton.getGlobalBounds().contains(m_MousePos)) {
		if (m_menu.is(Bool::Pause)) return;
		Sounds::instance().playSound(TypeSound::Click);
		soundOnButton.setColor(sf::Color::White);
		soundOffButton.setColor(sf::Color::Yellow);
		soundLowButton.setColor(sf::Color::White);
		m_menu.pauseCurrLevelMusic();
		m_menu.setTrue(Bool::SoundOff); m_menu.setFalse(Bool::SoundOn); m_menu.setFalse(Bool::SoundLow);
	}
	else if (soundLowButton.getGlobalBounds().contains(m_MousePos)) {
		if (m_menu.is(Bool::Pause)) return;
		Sounds::instance().playSound(TypeSound::Click);
		soundOnButton.setColor(sf::Color::White);
		soundOffButton.setColor(sf::Color::White);
		soundLowButton.setColor(sf::Color::Yellow);
		m_menu.lowVolumCurrLevelMusic();
		m_menu.setTrue(Bool::SoundLow); m_menu.setFalse(Bool::SoundOn); m_menu.setFalse(Bool::SoundOff);
	}
	else if (restart.getGlobalBounds().contains(m_MousePos)) {
		if (!m_menu.is(Bool::Pause))
			restartLevel();
	}
	else if (backButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		pauseButtonHandle(playButton, pauseButton, pause);
		m_menu.show();
		handleExitMenu();
		m_menu.playCurrLevelMusic();
		restartClocks();
	}
	else if (help.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::Click);
		m_menu.pauseCurrLevelMusic();
		m_menu.setTrue(Bool::Pause);
		m_menu.setTrue(Bool::Help);
		m_menu.helpWindow();
		restartClocks();
	}
}
//-------------------------------------------------------------------------
void GameManager::playButtonHandle(sf::Sprite& play, sf::Sprite& pause)
{
	Sounds::instance().playSound(TypeSound::Click);
	play.setColor(sf::Color::Yellow);
	pause.setColor(sf::Color::White);
	if (m_menu.is(Bool::Pause) && !m_menu.is(Bool::SoundOff))
		m_menu.playCurrLevelMusic();
	m_menu.setFalse(Bool::Pause);
}
//----------------------------------------------------------------
void GameManager::pauseButtonHandle(sf::Sprite& playButton, sf::Sprite& pauseButton, sf::Sprite& pause)
{
	m_menu.pauseCurrLevelMusic();
	Sounds::instance().playSound(TypeSound::Click);
	pauseButton.setColor(sf::Color::Yellow);
	playButton.setColor(sf::Color::White);
	m_window.draw(pauseButton);
	m_window.draw(playButton);
	pause.setPosition(m_window.getView().getCenter().x, m_window.getView().getCenter().y);
	m_window.draw(pause);
	m_menu.setTrue(Bool::Pause);
}
//-------------------------------------------------------------------------
void GameManager::handleMouseMoved(sf::Sprite& playButton, sf::Sprite& pauseButton, sf::Sprite& stopButton, sf::Sprite& soundOnButton,
	sf::Sprite& soundOffButton, sf::Sprite& soundLowButton, sf::Sprite& restart, sf::Sprite& backButton, sf::Sprite& help)
{
	if (playButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		playButton.setColor(sf::Color::Cyan);
	}
	else if (m_menu.is(Bool::Pause))
		playButton.setColor(sf::Color::White);
	else playButton.setColor(sf::Color::Yellow);
	if (pauseButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		pauseButton.setColor(sf::Color::Green);
	}
	else if (!m_menu.is(Bool::Pause))
		pauseButton.setColor(sf::Color::White);
	if (stopButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		stopButton.setColor(sf::Color::Red);
	}
	else stopButton.setColor(sf::Color::White);
	if (soundOnButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		soundOnButton.setColor(sf::Color::Yellow);
	}
	else if (!m_menu.is(Bool::SoundOn)) soundOnButton.setColor(sf::Color::White);
	if (soundOffButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		soundOffButton.setColor(sf::Color::Yellow);
	}
	else if (!m_menu.is(Bool::SoundOff)) soundOffButton.setColor(sf::Color::White);
	if (soundLowButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		soundLowButton.setColor(sf::Color::Yellow);
	}
	else if (!m_menu.is(Bool::SoundLow)) soundLowButton.setColor(sf::Color::White);
	if (restart.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		restart.setColor(sf::Color::Yellow);
	}
	else restart.setColor(sf::Color::White);
	if (backButton.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		backButton.setColor(sf::Color::Yellow);
	}
	else backButton.setColor(sf::Color::White);
	if (help.getGlobalBounds().contains(m_MousePos)) {
		Sounds::instance().playSound(TypeSound::MouseWheel);
		help.setColor(sf::Color::Magenta);
	}
	else help.setColor(sf::Color::White);
	m_window.draw(playButton); m_window.draw(pauseButton); m_window.draw(stopButton);
	m_window.draw(soundOnButton); m_window.draw(soundOffButton); m_window.draw(backButton);
	m_window.display();
}
//--------------------------------------------------------------------
void GameManager::handleDrawTextAndButton(sf::Sprite& lifeSprite, sf::Text& life, sf::Sprite& heartSprite, sf::Text& heart, sf::Sprite& ringsSprite, sf::Text& rings, sf::Sprite& timeSprite, sf::Text& time,
	sf::Sprite& play, sf::Sprite& pauseButton, sf::Sprite& stop, sf::Sprite& soundOn, sf::Sprite& soundOff, sf::Sprite& soundLow, sf::Sprite& restart, sf::Sprite& backButton, sf::Sprite& help,
	sf::Sprite& emeraldSprite, sf::Text& emerald)
{
	m_window.draw(lifeSprite); m_window.draw(life); m_window.draw(heartSprite); m_window.draw(heart);
	m_window.draw(ringsSprite); m_window.draw(rings); m_window.draw(timeSprite); m_window.draw(time);
	m_window.draw(play); m_window.draw(pauseButton); m_window.draw(stop);
	m_window.draw(soundOn); m_window.draw(soundOff); m_window.draw(soundLow);
	m_window.draw(restart); m_window.draw(backButton);
	m_window.draw(help); m_window.draw(emeraldSprite);  m_window.draw(emerald);
}
//--------------------------------------------------------------------
void GameManager::updateTextData(sf::Sprite& lifeSprite, sf::Text& life, sf::Sprite& heartSprite, sf::Text& heart, sf::Text& rings, sf::Text& time, sf::Text& emerald)
{
	life.setString(to_string(m_board.getLife()));
	heart.setString(to_string(m_board.getHeart()));
	rings.setString(to_string(m_board.getRings()));
	time.setString(to_string((int)m_time.asSeconds()));
	emerald.setString(to_string(m_board.getEmerald()));
	lifeSprite.setPosition(m_player->getLocation()._x - 130, m_player->getLocation()._y - 140);
	life.setPosition(m_player->getLocation()._x - 100, m_player->getLocation()._y - 200);
	heartSprite.setPosition(m_player->getLocation()._x + 50, m_player->getLocation()._y - 195);
	heart.setPosition(m_player->getLocation()._x + 120, m_player->getLocation()._y - 200);
}
//-----------------------------------
void GameManager::restartClocks()
{
	m_board.restartClocks();
	m_clock.restart();
}
//--------------------------------
void GameManager::handleExitMenu()
{
	if (m_menu.is(Bool::Save)) {
		m_nameFile = "../../../resources/BoardLevels/output.txt";
		m_window.close();
		m_menu.stopMusic();
		m_menu.setFalse(Bool::Save);
		run();
	}
	if (m_menu.is(Bool::Clear)) {
		m_nameFile = "Board.txt";
		m_window.close();
		m_menu.stopMusic();
		m_menu.setFalse(Bool::Clear);
		run();
	}
}
//-------------------------------
void GameManager::handleWinGame()
{
	m_menu.stopMusic();
	auto win = Image::instance().getSprite(WIN);
	win.setOrigin(560, 125);
	win.setPosition(m_centerView._x, m_centerView._y);
	m_window.draw(win);
	m_window.display();
	Sleep(SEVEN_SEC);
	m_window.close();
	m_level = Level::First;
	m_menu.setFalse(Bool::RestartGameBool);
	m_menu.show();
}
//----------------------------------------------
