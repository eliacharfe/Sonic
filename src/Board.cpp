#include "Board.h"

Board::Board() : m_startLevelOnTextBoard('\n'), m_totalEmerald(0)
{ }
//---------------------------------------------------------
void Board::openFile(const char* nameFile)
{
	m_BoardFile.close();
	m_BoardFile.open(nameFile);
	m_restartGame = true;
	if (!m_BoardFile.is_open())
		throw Exception("Cannot open file...\n");
}
//----------------------------------------
void Board::readLevel()
{
	!Emerald::getEmerald() ? setPlaceTextLevel(Level::WinLevel) : setPlaceTextLevel(Level::LooseLevel);
	if (m_restartGame)
		setPlaceTextLevel(Level::RestartGame);
	m_BoardFile >> m_sizeBoard.y >> m_sizeBoard.x;
	m_BoardFile.get();
	m_charBoard.clear();
	string str;
	for (unsigned int line = 0; line < m_sizeBoard.y; line++) {
		getline(m_BoardFile, str);
		if (str.size() != m_sizeBoard.x)
			throw Exception("Error at file (num of columns don't match), at line: ", line);
		m_charBoard.push_back(move(str)); // save the line in a vector of strings
	}
	if (m_charBoard.size() != m_sizeBoard.y)
		throw Exception("Error at file, num of rows don't match...\n");
	if (m_charBoard.empty())
		throw Exception("Board text is empty\n");
}
//-----------------------------------------------------
void Board::allocateBoard()
{ // allocate according to the board level 
	bool existEmerald = false;
	clear();
	Location location(OBJECT_SIZE / 2, OBJECT_SIZE / 2);
	for (auto& line : m_charBoard) {
		for (auto& c : line) {
			m_sprite = Image::instance().getSprite(c); // get the accurate sprite
			m_sprite.setPosition(locationToVector(location));
			m_movables.size() > 0 ? createObject(c, m_sprite, m_movables[PLAYER_INDEX]) :
				createObject(c, m_sprite, nullptr);  // create object
			if (c == EMERALD)
				existEmerald = true;
			location._x += OBJECT_SIZE;
		}
		location._x = OBJECT_SIZE / 2;
		location._y += OBJECT_SIZE;
	}
	if (m_movables.empty())
		throw std::out_of_range("movables vector is empty--> fix board text\n");
	if (typeid(*m_movables[PLAYER_INDEX]) != typeid(Player))
		throw Exception("First element in movables vector isn't player...\n");
	if (!existEmerald)
		throw Exception("You must have Emerald in your level!!\n");
	for (auto& movable : m_movables) {
		movable->setSizeBoard(m_sizeBoard);
		movable->setLevel(m_totalEmerald + 1);
	}
}
//--------------------------------------------
void Board::draw(sf::RenderWindow& window) const
{
	for (auto& staticObj : m_statics)
		staticObj->draw(window);
	for (auto& movableObj : m_movables)
		movableObj->draw(window);
}
//------------------------------------------------------------------
bool Board::update(const sf::Time& currTime, const sf::Time& runTime)
{
	for (auto& movableObj : m_movables) {
		movableObj->direction(); // set direction 
		movableObj->move(currTime);// move the movable object
		processCollisions(*movableObj); // handle collisions
		movableObj->handleFall();
		handleFalls(*movableObj); // handle fall if is on the air	
	}
	std::experimental::erase_if(m_statics, [](auto& staticObj) { return staticObj->isDisposed(); });
	std::experimental::erase_if(m_movables, [](auto& movable) { return movable->isDisposed(); });

	return checkEmerald() ? true : false;
}
//-----------------------------------------------------
void Board::processCollisions(MovingObject& movable)
{
	for (auto& staticObj : m_statics)
		if (movable.collidesWith(*staticObj)) // if the movable collides a static 
			processCollision(movable, *staticObj);
	for (auto& movableObj : m_movables)
		if (movable.collidesWith(*movableObj))// if the movable collides another movable
			processCollision(movable, *movableObj);
}
//--------------------------------------------
void Board::handleFalls(MovingObject& movable)
{
	if (typeid(movable) == typeid(Boss)) {
		if (Boss::isShooting())
			createBullet(movable);
		return;
	}
	if (typeid(movable) == typeid(Bullet) || typeid(movable) == typeid(VerticalPlattform))
		return;

	auto player = getPlayer();

	for (auto& staticObj : m_statics)
	{
		if (movable.collidesWith(*staticObj)) {
			//processCollision(movable, *staticObj);
			if ((typeid(*staticObj) == typeid(Floor) || typeid(*staticObj) == typeid(Wall) || typeid(*staticObj) == typeid(HorizontalPlattform))) {
				if (typeid(movable) == typeid(Player)) {
					player->setFalse(BoolPlayer::JumpingSpringboard);
					if (player->is(BoolPlayer::Jumping)) {
						processCollision(movable, *staticObj);
						continue;
					}
				}
				if (movable.getLocation()._x < staticObj->getLocation()._x)
					movable.setLocation(Location(staticObj->getLocation()._x - OBJECT_SIZE, staticObj->getLocation()._y));
				if (movable.getLocation()._y < staticObj->getLocation()._y)
					movable.setLocation(Location(movable.getLocation()._x, staticObj->getLocation()._y - OBJECT_SIZE));
				else if (movable.getLocation()._y > staticObj->getLocation()._y)
					movable.setLocation(Location(movable.getLocation()._x, staticObj->getLocation()._y + OBJECT_SIZE));		
			}
			else if (typeid(movable) == typeid(Player) && typeid(*staticObj) == typeid(Pole))
				player->setFalse(BoolPlayer::JumpingSpringboard);
			else if (typeid(*staticObj) == typeid(Spikes)) {
				if (typeid(movable) == typeid(Player))
					movable.setLocation(Location(staticObj->getLocation()._x, staticObj->getLocation()._y - OBJECT_SIZE + 1)); // process collision
				else movable.setLocation(Location(staticObj->getLocation()._x, staticObj->getLocation()._y - OBJECT_SIZE));
			}
			else if (typeid(*staticObj) == typeid(Springboard)) {
				if (typeid(movable) == typeid(Player)) {
					movable.setLocation(Location(staticObj->getLocation()._x, staticObj->getLocation()._y - OBJECT_SIZE + 1));// process collision
					player->setFalse(BoolPlayer::JumpingSpringboard);
				}
				else processCollision(movable, *staticObj);
			}
		}
	}
}
//-------------------------------------
bool Board::checkEmerald()
{
	if (!Emerald::getEmerald()) { // win level 
		++m_totalEmerald;
		return true;
	}
	return false;
}
//---------------------------------------
void Board::createBullet(MovingObject& boss)
{
	auto sprite = Image::instance().getSprite(BULLET);
	sprite.setPosition(boss.getLocation()._x, boss.getLocation()._y);
	createObject(BULLET, sprite, m_movables[PLAYER_INDEX]);
	for (auto& movable : m_movables)
		movable->setLevel(m_totalEmerald + 1);
	Sounds::instance().playSound(TypeSound::BulletType);
}
//--------------------------------------
void Board::restartClocks()
{
	for (auto& movable : m_movables)
		movable->restartClock();
}
//-----------------------------------
void Board::restartGame()
{
	m_restartGame = true;
}
//------------------------------------------
void Board::setPlaceTextLevel(Level status)
{
	switch (status) {
	case Level::WinLevel: m_startLevelOnTextBoard = m_BoardFile.tellg(); break;
	case Level::LooseLevel: m_BoardFile.seekg(m_startLevelOnTextBoard);
		m_startLevelOnTextBoard = m_BoardFile.tellg(); break;
	case Level::RestartGame: { m_BoardFile.clear();
		m_BoardFile.seekg(0, std::ios::beg);
		m_startLevelOnTextBoard = m_BoardFile.tellg();
		m_restartGame = false;
		break;
	}
	default:
		throw Exception("Command not found...\n");
	}
}
//--------------------------------------------------------------------------
void Board::createObject(const char c, const sf::Sprite& sprite, shared_ptr < MovingObject > player)
{
	unique_ptr < StaticObject > staticObj = createUnmovableObject(c, sprite);
	if (staticObj) { m_statics.push_back(move(staticObj)); return; }

	shared_ptr < MovingObject > movableObj = createMovableObject(c, sprite, player);
	if (movableObj) { m_movables.push_back(move(movableObj)); return; }
}
//----------------------------------------------------
shared_ptr < MovingObject > Board::createMovableObject(const char c, const sf::Sprite& sprite, shared_ptr < MovingObject >& player) const
{
	return FactoryMovable::create(c, sprite, player);
}
//-------------------------------------------------
unique_ptr < StaticObject > Board::createUnmovableObject(const char c, const sf::Sprite& sprite) const
{
	return FactoryStatic::create(c, sprite);
}
//------------------------------------------------------------------
//-------------------------------------------------------------------
void Board::createLevel() // at creator mode
{
	m_menuObjects.clear();
	auto charMenu = { '@', '&', 'S', '#', 'F', '-', 'o', 'E',
					  '^', 'u', '=', 'V','O','B'};
	Location location(OBJECT_SIZE / 2, OBJECT_SIZE / 2);
	for (auto& c : charMenu)
	{
		auto sprite = Image::instance().getSprite(c);
		sprite.setPosition(locationToVector(location));
		m_menuObjects.push_back(createObjectAtCreateMode(c, sprite, true));
		location._x += OBJECT_SIZE;
	}
}
//----------------------------------------------------
void Board::createObject(const char c, sf::Sprite& sprite, const sf::Vector2f& mousePos)
{// at creator mode
	sprite.setPosition(mousePos);
	m_objects.push_back(createObjectAtCreateMode(c, sprite, false));
}
//-----------------------------------------
void Board::drawObjectsAtCreateLevelMode(sf::RenderWindow& window)
{// at creator mode
	std::experimental::erase_if(m_objects, [](auto& obj) { return obj->isDisposed(); });

	for (auto& object : m_menuObjects)
		object->draw(window);
	for (auto& object : m_objects)
		object->draw(window);
}
//-------------------------------
unique_ptr<GameObject> Board::createObjectAtCreateMode(const char c, sf::Sprite& sprite, bool menu)
{// at creator mode
	shared_ptr<MovingObject> temp;
	switch (c)
	{
	case PLAYER:      return make_unique<Player>(c, sprite);
	case ENEMY_FAST:  return make_unique<EnemyFast>(c, sprite, temp);
	case ENEMY_SLOW:  return make_unique<EnemySlow>(c, sprite, temp);
	case WALL:        return make_unique<Wall>(c, sprite);
	case FLOOR:       return make_unique<Floor>(c, sprite);
	case POLE:        return make_unique<Pole>(c, sprite);
	case SPIKES:      return make_unique<Spikes>(c, sprite);
	case SPRINGBOARD: return make_unique<Springboard>(c, sprite);
	case RING:        return make_unique<Ring>(c, sprite);
	case EMERALD:     return make_unique<Emerald>(c, sprite);
	case HORIZONTAL_PLAT: {
		if (menu)
			sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE / 2, sprite.getPosition().y);
		else sprite.setPosition(sprite.getPosition().x + 75 - OBJECT_SIZE / 2, sprite.getPosition().y - OBJECT_SIZE / 2 + 36);
		return make_unique<HorizontalPlattform>(c, sprite, temp);
	}
	case VERTICAL_PLAT: {
		if (menu)
			sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE + OBJECT_SIZE / 2 - 10, sprite.getPosition().y + OBJECT_SIZE / 2);
		else sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE / 2, sprite.getPosition().y + 118 - OBJECT_SIZE);
		return make_unique<VerticalPlattform>(c, sprite, temp);
	}
	case CIRCLE: {
		if (menu)
			sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE * 4 + 30, sprite.getPosition().y + OBJECT_SIZE * 2 + OBJECT_SIZE / 2);
		else sprite.setPosition(sprite.getPosition().x + RADIUS - OBJECT_SIZE / 2, sprite.getPosition().y + RADIUS - OBJECT_SIZE / 2);
		return make_unique<Circle>(c, sprite);
	}
	case BOSS: {
		if (menu)
			sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE * 7 + OBJECT_SIZE / 2, sprite.getPosition().y + OBJECT_SIZE / 2);
		else sprite.setPosition(sprite.getPosition().x + OBJECT_SIZE / 2, sprite.getPosition().y + OBJECT_SIZE / 2);
		return make_unique<Boss>(c, sprite, temp);
	}
	default:
		throw Exception("No sush object\n");
	}
	return unique_ptr<GameObject>();//never
}
//--------------------------------------
const char Board::getObjectType(const sf::Vector2f& mousePos)const
{// at creator mode
	for (auto& object : m_menuObjects)
		if (object->getSprite().getGlobalBounds().contains(mousePos))
			return object->getChar();
	return EMPTY;
}
//------------------------------------------------------------
unique_ptr<GameObject> Board::getObject(const char c)
{// at creator mode
	for (auto& object : m_objects)
		if (object->getChar() == c)
			return move(object);

	throw Exception("No sush object type\n");
}
//-------------------------------------------------------
void Board::deleteObject(const sf::Vector2f& mousePos)
{// at creator mode
	for (auto& object : m_objects)
		if (object->getSprite().getGlobalBounds().contains(mousePos)) {
			object->setDisposed();
			Sounds::instance().playSound(TypeSound::SmoothClick);
		}
}
//---------------------------------
void Board::clearObjects()
{// at creator mode
	m_objects.clear();
}
//-------------------------------------
void Board::saveLevelToFile(const vector<vector<char>>& charBoard)
{// at creator mode
	cout << "\nSave to file\n";
	ofstream outputFile("../../../resources/BoardLevels/output.txt");

	outputFile << m_sizeBoard.y << " " << m_sizeBoard.x;

	for (int i = 0; i < m_sizeBoard.y; i++) {
		outputFile << endl;
		for (int j = 0; j < m_sizeBoard.x; j++) {
			outputFile << charBoard[i][j];
		}
	}
	outputFile.close();
}
//-------------------------------------------------------------
void Board::playSavedLevel()
{// at creator mode
	try {
		openFile("../../../resources/BoardLevels/output.txt");
		readLevel();
		allocateBoard();
	}
	catch (Exception& e) { cerr << "Exception throwed\n--> " << e.what(); throw; }// rethrow 
	catch (std::runtime_error& e) { cerr << "run time error throwed\n--> " << e.what(); throw; }
	catch (...) { throw; }
}
//--------------------------------------------------------
void Board::clear()
{
	m_movables.clear();
	m_statics.clear();
	m_menuObjects.clear();
	m_objects.clear();
}






