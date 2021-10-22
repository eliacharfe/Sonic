#include "Image.h"

Image::Image()
{
	if (!m_mapTexture[Object].loadFromFile("objectsSpriteSheet.png")// for sprite sheet game objects
	 || !m_mapTexture[PlayerType].loadFromFile("playerSpriteSheet.png")// for sprite sheet player
	 || !m_mapTexture[EnemyType].loadFromFile("enemySheet.png")// for sprite sheet enemies
	 || !m_mapTexture[BossType].loadFromFile("bossSpriteSheet.png")// for sprite sheet boss
	 || !m_mapTexture[Buttons].loadFromFile("buttonsSpriteSheet.png")// for sprite sheet of buttons
	 || !m_mapTexture[Background1].loadFromFile("background1.png") // background
	 || !m_mapTexture[Background2].loadFromFile("background2.jpg") // background
	 || !m_mapTexture[Background3].loadFromFile("background3.jpg") // background
	 || !m_mapTexture[BackOptions].loadFromFile("backgroundOptions.jpg") // background
	 || !m_mapTexture[Welcome].loadFromFile("sonicBack.jpg")// background
	 || !m_mapTexture[Help].loadFromFile("helpBackground.jpg")// background
	 || !m_mapTexture[GameOverMsg].loadFromFile("gameOverMsg.png")// Game over message
	 || !m_mapTexture[YouWonMsg].loadFromFile("YouWon.png")// win message
	 || !m_mapTexture[Pause].loadFromFile("pause.png") // pause sprite
	 || !m_mapTexture[Empty].loadFromFile("empty.png")) // empty sprite(never)
		throw std::runtime_error("Can't load texture (else)\n");

	m_mapTexture[Background1].setRepeated(true);
	m_mapTexture[Background2].setRepeated(true);
	m_mapTexture[Background3].setRepeated(true);

	for (auto iter = m_mapTexture.begin(); iter != m_mapTexture.end(); iter++)
		m_mapSprite[iter->first].setTexture(m_mapTexture[iter->first]);

	m_font.loadFromFile("resources/sansation.ttf");
}
//------------------------------------
Image& Image::instance()
{
	static Image inst;
	return inst;
}
//-----------------------------------------
const sf::Sprite& Image::getSprite(const char c)
{
	srand((int)time(NULL));
	static int random3 = rand() % 3; ;
	static int random2 = rand() % 2; ;
	switch (c)
	{
	case PLAYER: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(0, 0, OBJECT_SIZE, OBJECT_SIZE));
		             return m_mapSprite.find(PlayerType)->second; break;
	}
	case PLAYER_STAY1: { m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1185, 0, OBJECT_SIZE-2, OBJECT_SIZE));
		return m_mapSprite.find(PlayerType)->second; break;
	}
	case PLAYER_STAY2: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1262, 0, OBJECT_SIZE, OBJECT_SIZE));
		return m_mapSprite.find(PlayerType)->second; break;
	}
	case PLAYER_STAY3: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1341, 0, OBJECT_SIZE, OBJECT_SIZE));
		return m_mapSprite.find(PlayerType)->second; break;
	}
	case PLAYER_STAY4: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1420, 0, OBJECT_SIZE, OBJECT_SIZE));
		return m_mapSprite.find(PlayerType)->second; break;
	}
	case FLOOR: {    m_mapSprite[Object].setTextureRect(sf::IntRect(80, 0, OBJECT_SIZE, OBJECT_SIZE));
		              return m_mapSprite[Object]; break;
	}
	case PLAYER_LEFT_START: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(79, 0, OBJECT_SIZE, OBJECT_SIZE));
							  return m_mapSprite.find(PlayerType)->second; break;
	}
	case RUN1_RIGHT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(632, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second; break;
	}
	case JUMP: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1106, 0, OBJECT_SIZE, OBJECT_SIZE));
		            return m_mapSprite.find(PlayerType)->second; break;
	}
	case RUN0_RIGHT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(474, 0, OBJECT_SIZE, OBJECT_SIZE));
		                return m_mapSprite.find(PlayerType)->second; break;
	}
	case RUN0_LEFT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(553, 0, OBJECT_SIZE, OBJECT_SIZE));
		return m_mapSprite.find(PlayerType)->second; break;
	}
	case HORIZONTAL_PLAT: {  
		random2 += 1;
		if (random2 == 2)
			random2 = 0;
		if (random2 == 0)
			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(400, 0, 150, 36));
		else  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1652, 0, 150, 36));
	  return m_mapSprite.find(Object)->second; break;
	}
	case TIME: {
		m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1802, 0, OBJECT_SIZE+1, OBJECT_SIZE+1));
		m_mapSprite.find(Object)->second.setOrigin(40, 40);
		return m_mapSprite.find(Object)->second; break;
	}
	case HEART: { m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1882, 0, 42, 40));
		return m_mapSprite.find(Object)->second; break;
	}
	case LIFE_BAR: { m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1924, 0, 116, 25));
		return m_mapSprite.find(Object)->second; break;
	}
	case RUN2_RIGHT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(790, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second; break;
	}
	case GET_DOWN: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(1027, 0, OBJECT_SIZE, OBJECT_SIZE));
		           return m_mapSprite.find(PlayerType)->second; break;
	}
	case POLE: {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(316, 0, OBJECT_SIZE+1, OBJECT_SIZE));
		           return m_mapSprite.find(Object)->second; break;
	}
	case WALL: { 
		random3 += 1;
		if (random3 == 3)
			random3 = 0;
		if (random3 == 0) 
			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(0, 0, OBJECT_SIZE, OBJECT_SIZE));
		else if (random3 == 1)
			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1493, 0, OBJECT_SIZE, OBJECT_SIZE));
		else m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1573, 0, OBJECT_SIZE, OBJECT_SIZE));             
		return m_mapSprite.find(Object)->second; break;
	}
	case READY_RIGHT: { m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(158, 0, OBJECT_SIZE, OBJECT_SIZE));
		                return m_mapSprite.find(PlayerType)->second; break;
	}
	case READY_LEFT: { m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(237, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second;
	}
	case WALK_RIGHT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(316, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second; break;
	}
	case WALK_LEFT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(395, 0, OBJECT_SIZE, OBJECT_SIZE));
		                return m_mapSprite.find(PlayerType)->second; break;
	}
	case RUN_RIGHT: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(711, 0, OBJECT_SIZE, OBJECT_SIZE));
	                 	return m_mapSprite.find(PlayerType)->second; break;
	}
	case RING: {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(548, 0, OBJECT_SIZE, OBJECT_SIZE));
		            m_mapSprite.find(Object)->second.setOrigin(0 , 0 );
		             return m_mapSprite.find(Object)->second; break;
	}
	case SPRINGBOARD:   {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(780, 0, OBJECT_SIZE+1, OBJECT_SIZE+1));
		                   return m_mapSprite.find(Object)->second; break;
	}
	case SPRING_J_R: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(948, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second; break;
	}
	case BALL_SPEED: {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(869, 0, OBJECT_SIZE, OBJECT_SIZE));
		                 return m_mapSprite.find(PlayerType)->second; break;
	}
	case SPIKES: {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(710, 0, 70, OBJECT_SIZE+1));
		              return m_mapSprite.find(Object)->second; break;
	}
	case EMERALD: {   m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(626, 0, 81, 70));
		m_mapSprite.find(Object)->second.setOrigin(0, 0);
		                return m_mapSprite.find(Object)->second; break;
	}
	case CIRCLE: {  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(854, 0, 480, 480));
		            return m_mapSprite.find(Object)->second; break;
	}
	case ENEMY_SLOW: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(80, 0, OBJECT_SIZE, OBJECT_SIZE - 5));
		                return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_SLOW_RIGHT: { m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(0, 0, OBJECT_SIZE, OBJECT_SIZE - 5));
		                      return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(159, 0, OBJECT_SIZE, OBJECT_SIZE ));
		                 return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST_RIGHT: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(237, 0, OBJECT_SIZE, OBJECT_SIZE));
		                      return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST_RUN_LEFT: { m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(317, 0, OBJECT_SIZE, OBJECT_SIZE));
		                        return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST_RUN_RIGHT: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(395, 0, OBJECT_SIZE, OBJECT_SIZE));
		                          return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST_LEFT_HIT: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(474, 0, OBJECT_SIZE, OBJECT_SIZE));
		                         return m_mapSprite.find(EnemyType)->second;
	}
	case ENEMY_FAST_RIGHT_HIT: {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(553, 0, OBJECT_SIZE, OBJECT_SIZE));
		                          return m_mapSprite.find(EnemyType)->second;
	}
	case VERTICAL_PLAT: {  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1335, 0, 158, 237));
		                   return m_mapSprite.find(Object)->second; break;
	}
	case BOSS: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(0, 0, 160, 160));
		          return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_RIGHT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(160, 0, 160, 160));
		               return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_SHOOT1_LEFT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(320, 0, 150, 134));
	                         return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_SHOOT1_RIGHT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(470, 0, 150, 134));
		                       return m_mapSprite[BossType]; break;
	}
	case BOSS_SHOOT2_LEFT: {  m_mapSprite[BossType].setTextureRect(sf::IntRect(620, 0, 160, 160));
	                     	return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_SHOOT2_RIGHT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(780, 0, 160, 160));
		                       return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_EGG_LEFT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(940, 0, 160, 160));
		                   return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_EGG_RIGHT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(1102, 0, 160, 160));
		                   return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_HAMMER_LEFT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(1264, 0, 183, 160));
		                       return m_mapSprite.find(BossType)->second; break;
	}
	case BOSS_HAMMER_RIGHT: {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(1447, 0, 183, 160));
		                      return m_mapSprite.find(BossType)->second; break;
	}
	case BULLET: {   m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(1630, 0, 41, 50));
		             return m_mapSprite.find(BossType)->second; break;
	}
	case PLAY_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(0, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		                 m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);
		                 return m_mapSprite.find(Buttons)->second; break;
	}
	case PAUSE_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(BUTTON_HEIGHT, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		                  m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);
		                  return m_mapSprite.find(Buttons)->second; break;
	}
	case STOP_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2* BUTTON_HEIGHT, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		                 m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);
		                 return m_mapSprite.find(Buttons)->second; break;
	}
	case START_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(3* BUTTON_HEIGHT, 0, 215, BUTTON_HEIGHT));
		                  return m_mapSprite.find(Buttons)->second; break;
	}
	case EXIT_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(515, 0, 213, BUTTON_HEIGHT));
		                 return m_mapSprite.find(Buttons)->second; break;
	}
	case CREATE_BUTTON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(1608, 0, 216, BUTTON_HEIGHT));
		                   return m_mapSprite.find(Buttons)->second; break;
	}
	case SOUND_ON: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2443, 0, 85, BUTTON_HEIGHT));
		              m_mapSprite.find(Buttons)->second.setOrigin(42, BUTTON_HEIGHT / 2);
		              return m_mapSprite.find(Buttons)->second; break;
	}
	case SOUND_OFF: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2527, 0, 71, BUTTON_HEIGHT));
		               m_mapSprite.find(Buttons)->second.setOrigin(36, BUTTON_HEIGHT / 2);
		               return m_mapSprite.find(Buttons)->second; break;
	}
	case SOUND_LOW: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2700, 0, 71, BUTTON_HEIGHT));
		               m_mapSprite.find(Buttons)->second.setOrigin(36, BUTTON_HEIGHT / 2);
		               return m_mapSprite.find(Buttons)->second; break;
	}
	case SETTINGS: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2599, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		              m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);
		              return m_mapSprite.find(Buttons)->second; break;
	}
	case HELP: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2770, 0, 93, BUTTON_HEIGHT));
		          m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2 - 3, BUTTON_HEIGHT / 2);
		          return m_mapSprite.find(Buttons)->second; break;
	}
	case NEXT: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2863, 0, 113, BUTTON_HEIGHT));
		          m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2 + 6, BUTTON_HEIGHT / 2);
		          return m_mapSprite.find(Buttons)->second; break;
	}
	case BACK: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2976, 0, 113, BUTTON_HEIGHT));
		          m_mapSprite.find(Buttons)->second.setOrigin(BUTTON_HEIGHT / 2 + 6, BUTTON_HEIGHT / 2);
		          return m_mapSprite.find(Buttons)->second; break;
	}
	case RESTART: { m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(3089, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		            return m_mapSprite.find(Buttons)->second; break;
	}
	case BEGIN: { m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(3189, 0, BUTTON_HEIGHT, BUTTON_HEIGHT));
		          return m_mapSprite.find(Buttons)->second; break;
	}
	case DELETE_BUTTON: { m_mapSprite[Buttons].setTextureRect(sf::IntRect(1393, 0, 215, BUTTON_HEIGHT));
		                  return m_mapSprite.find(Buttons)->second; break;
	}
	case CLEAR: {  m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(728, 0, 214, BUTTON_HEIGHT));
		           return m_mapSprite.find(Buttons)->second; break;
	}
	case SAVE: { m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(2040, 0, 216, BUTTON_HEIGHT));
		         return m_mapSprite.find(Buttons)->second; break;
	}
	case CLOSE: { m_mapSprite.find(Buttons)->second.setTextureRect(sf::IntRect(942, 0, 214, BUTTON_HEIGHT));
		          return m_mapSprite.find(Buttons)->second; break;
	}
	case BACKGROUND1: { m_mapSprite.find(Background1)->second.setOrigin(DEF_SIZE_WINDOW_X/2, DEF_SIZE_WINDOW_Y / 2 + BUTTON_HEIGHT);
		return m_mapSprite.find(Background1)->second;
	}
	case BACKGROUND2: { m_mapSprite.find(Background2)->second.setOrigin(DEF_SIZE_WINDOW_X / 2, DEF_SIZE_WINDOW_Y / 2 + BUTTON_HEIGHT);
		return m_mapSprite.find(Background2)->second;
	}
	case BACKGROUND3: { m_mapSprite.find(Background3)->second.setOrigin(DEF_SIZE_WINDOW_X / 2, DEF_SIZE_WINDOW_Y / 2 + BUTTON_HEIGHT);
		return m_mapSprite.find(Background3)->second;
	}
	case BACKGROUND_OPTIONS: return m_mapSprite.find(BackOptions)->second;
	case WELCOME: return m_mapSprite.find(Welcome)->second;
	case HELP_WINDOW: return m_mapSprite.find(Help)->second;
	case GAME_OVER: return m_mapSprite.find(GameOverMsg)->second; break;
	case WIN: return m_mapSprite.find(YouWonMsg)->second; break;
	case PAUSE: { m_mapSprite.find(Pause)->second.setOrigin(5 * BUTTON_HEIGHT / 2, 5 * BUTTON_HEIGHT / 2);
		          return m_mapSprite.find(Pause)->second;
	}
	}
	return m_mapSprite.find(Empty)->second; // never
}
//------------------------------------------------
const sf::Font& Image::getFont() const
{
	return m_font;
}
//--------------------------------------------------------------












































//const sf::Sprite& Image::getSprite(const char c)
//{
//	static int random2 = rand() % 2; ;
//	static int random3 = rand() % 3; ;
//	switch (c)
//	{
//	case '@': {   m_mapSprite.find(PlayerType)->second.setTextureRect(sf::IntRect(0, 0, OBJECT_SIZE, OBJECT_SIZE));
//		return m_mapSprite.find(PlayerType)->second; break;
//	}
//	case 'F': {    m_mapSprite[Object].setTextureRect(sf::IntRect(80, 0, OBJECT_SIZE, OBJECT_SIZE));
//		return m_mapSprite[Object]; break;
//	}
//	case '-': {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(316, 0, OBJECT_SIZE + 1, OBJECT_SIZE));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case '#': {
//		random3 += 1;
//		if (random3 == 3)
//			random3 = 0;
//		if (random3 == 0)
//			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(0, 0, OBJECT_SIZE, OBJECT_SIZE));
//		else if (random3 == 1)
//			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1493, 0, OBJECT_SIZE, OBJECT_SIZE));
//		else m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1573, 0, OBJECT_SIZE, OBJECT_SIZE));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'u': {  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(780, 0, OBJECT_SIZE + 1, OBJECT_SIZE + 1));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case '=': {
//		random2 += 1;
//		if (random2 == 2)
//			random2 = 0;
//		if (random2 == 0)
//			m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(400, 0, 150, 36));
//		else  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1652, 0, 150, 36));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'o': {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(548, 0, OBJECT_SIZE, OBJECT_SIZE));
//		m_mapSprite.find(Object)->second.setOrigin(0, 0);
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case '^': {    m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(710, 0, 70, OBJECT_SIZE + 1));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'E': {   m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(626, 0, 81, 70));
//		m_mapSprite.find(Object)->second.setOrigin(0, 0);
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'O': {  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(854, 0, 480, 480));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'S': {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(80, 0, OBJECT_SIZE, OBJECT_SIZE - 5));
//		return m_mapSprite.find(EnemyType)->second;
//	}
//	case '&': {  m_mapSprite.find(EnemyType)->second.setTextureRect(sf::IntRect(159, 0, OBJECT_SIZE, OBJECT_SIZE));
//		return m_mapSprite.find(EnemyType)->second;
//	}
//	case '*': {   m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(1630, 0, 41, 50));
//		return m_mapSprite.find(BossType)->second; break;
//	}
//	case 'V': {  m_mapSprite.find(Object)->second.setTextureRect(sf::IntRect(1335, 0, 158, 237));
//		return m_mapSprite.find(Object)->second; break;
//	}
//	case 'B': {  m_mapSprite.find(BossType)->second.setTextureRect(sf::IntRect(0, 0, 160, 160));
//		return m_mapSprite.find(BossType)->second; break;
//	}
//	}
//}

	//m_mapSprite[Object].setTexture(m_mapTexture[Object]);
	//m_mapSprite[PlayerType].setTexture(m_mapTexture[PlayerType]);
	//m_mapSprite[EnemyType].setTexture(m_mapTexture[EnemyType]);
	//m_mapSprite[BossType].setTexture(m_mapTexture[BossType]);
	//m_mapSprite[Buttons].setTexture(m_mapTexture[Buttons]);


	//m_mapSprite[Background1].setTexture(m_mapTexture[Background1]);

	//m_mapSprite[Background2].setTexture(m_mapTexture[Background2]);

	//m_mapSprite[Background3].setTexture(m_mapTexture[Background3]);
	//m_mapSprite[BackOptions].setTexture(m_mapTexture[BackOptions]);
	//m_mapSprite[Welcome].setTexture(m_mapTexture[Welcome]);
	//m_mapSprite[Help].setTexture(m_mapTexture[Help]);
	//m_mapSprite[GameOverMsg].setTexture(m_mapTexture[GameOverMsg]);
	//m_mapSprite[YouWonMsg].setTexture(m_mapTexture[YouWonMsg]);
	//m_mapSprite[Pause].setTexture(m_mapTexture[Pause]);
	//m_mapSprite[Empty].setTexture(m_mapTexture[Empty]);