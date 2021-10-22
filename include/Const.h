#pragma once

enum class TypeMusic {
	Music1, Music2, Music3, MainMenuMusic, HelpWindowMusic, GameOverWindowMusic, CreatorModeMusic
};
//----------------------
enum class TypeSound {
	EmeraldType, Bounce, EnemySlowType, EnemyFastType, SpikesType, PlayerHurt, BossHurt,
	LevelComplete, GameOverSound, ExtraLife, RingSound, BossDead, MouseWheel, Click, SmoothClick,
    BulletType, JumpSound
};
//-----------------------
enum class Bool {
	Running, Play, Pause, SoundOn, SoundOff, SoundLow, Help, GameOverBool, RestartGameBool,
	CreateWindowBool, Delete, Save, Clear,
	isPlayer, wasPlayer, isEmerald, wasEmerald, isBoss, wasBoss
};

enum class BoolPlayer {
	Jumping, JumpingSpringboard, OnCircle, FinishLoop, BallSpeed, Dead, KillBoss, TouchEmerald,
	Stay
};

namespace
{
	enum Level {
		MainMenu, First, Second, Third, Fourth,
		HelpWindow, WinLevel, LooseLevel, RestartGame, GameOver, CreatorMode
	};

	enum TypeImage {
		PlayerType, Object, EnemyType, BossType, Buttons,
		Background1, Background2, Background3,
		BackOptions, Welcome, Help, GameOverMsg, YouWonMsg, Pause, Empty
	};

	const int OBJECT_SIZE = 79;
	const int RADIUS = 240;
	const int RADIUS_JUMP = 200;
	const double PI = 2 * asin(1.0);
	const double TO_DEGREES = 57.2958;
	const int ROTATE = 90;
	const double START_CIRCLE = PI / 2;
	const double FULL_CIRCLE = -3 * PI / 2;
	const double START_JUMP = PI;
	const double HALF_JUMP = 3 * PI / 2;
	const double COMPLETE_JUMP = 2 * PI;

	const int DEF_SIZE_WINDOW_X = 1700;
	const int DEF_SIZE_WINDOW_Y = 800;
	const int DEF_SIZE_MAIN_MENU_X = 1430;
	const int DEF_SIZE_MAIN_MENU_Y = 800;
	const int DEF_SIZE_HELP_WINDOW_X = 1420;
	const int DEF_SIZE_HELP_WINDOW_Y = 800;
	const int DEF_SIZE_GM_X = 1900;
	const int DEF_SIZE_GM_Y = 1100;

	const int OUTLINE_THIKNESS = 4;
	const int CHARACTER_SIZE = 55;
	const int SIZE_TEXT = 40;
	const float MSG_X_POS = 100.f;
	const float MSG_Y_POS = 80.f;
	const int NUM_BUTTOMS = 10;
	const int BUTTON_HEIGHT = 100;

	const int FULL_LIFE = 100;
	const int START_HEART = 3;
	const int MAX_HEART = 6;
	const int RING_VALUE = 5;
	const int SLOW_ENEMY_DAMAGE = 22;
	const int FAST_ENEMY_DAMAGE = 37;
	const int SPIKES_DAMAGE = 64;
	const int BOSS_DAMAGE = 99;
	const int PLAYER_DAMAGE = 10;
	const int BULLET_DAMAGE = 9;

	const double FALL_ANGLE = 0.4;
	const double JUMP_ANGLE = 0.3;

	const float SPEED_PLAYER = 400.0f;
	const float SPEED_PLATFORM_HORIZONTAL = 200.0f;
	const float SPEED_PLATFORM_VERTIVAL = 150.0f;
	const float SPEED_ENEMY_SLOW = 100.0f;
	const float SPEED_ENEMY_FAST = 350.0f;
	const float SPEED_BOSS = 400.0f;
	const float SPEED_BULLET = 500.0f;

	const int PLAYER_INDEX = 0;
	const int FOUR_SEC = 4000;
	const int FIVE_SEC = 5000;
	const int SIX_SEC = 6000;
	const int SEVEN_SEC = 7000;

	const char PLAY_BUTTON = 'P';
	const char PAUSE_BUTTON = 'Q';
	const char STOP_BUTTON = 's';
	const char START_BUTTON = 'T';
	const char EXIT_BUTTON = 'e';
	const char CREATE_BUTTON = '9';
	const char SOUND_ON = '4';
	const char SOUND_OFF = '5';
	const char SOUND_LOW = '}';
	const char SETTINGS = '6';
	const char PAUSE = '7';
	const char HELP = '?';
	const char HELP_WINDOW = 'f';
	const char NEXT = 't';
	const char BACK = 'k';
	const char RESTART = 'z';
	const char BEGIN = '%';
	const char DELETE_BUTTON = 'Z';
	const char CLEAR = '{';
	const char SAVE = 'M';
	const char CLOSE = 'b';

	const char EMPTY = ' ';
	const char BACKGROUND1 = '$';
	const char BACKGROUND2 = '2';
	const char BACKGROUND3 = '3';
	const char BACKGROUND_OPTIONS = 'X';
	const char PLAYER = '@';
	const char PLAYER_LEFT_START = '<';
	const char PLAYER_STAY1 = 'j';
	const char PLAYER_STAY2 = '"';
	const char PLAYER_STAY3 = '+';
	const char PLAYER_STAY4 = '`';
	const char FLOOR = 'F';
	const char POLE = '-';
	const char WALL = '#';
	const char RUN1_RIGHT = 'R';
	const char RUN1_LEFT = 'L';
	const char RUN0_RIGHT = 'r';
	const char RUN0_LEFT = 'l';
	const char RUN2_RIGHT = '>';
	const char RUN2_LEFT = 'p';
	const char READY_RIGHT = '(';
	const char READY_LEFT = ')';
	const char WALK_RIGHT = 'c';
	const char WALK_LEFT = 'd';
	const char RUN_RIGHT = 'a';
	const char RUN_LEFT = 'b';
	const char JUMP_RIGHT = 'j';
	const char JUMP_LEFT = 'i';
	const char RING = 'o';
	const char SPRINGBOARD = 'u';
	const char SPRING_J_R = '|';
	const char BALL_SPEED = '0';
	const char SPIKES = '^';
	const char JUMP = 'J';
	const char HORIZONTAL_PLAT = '=';
	const char GET_DOWN = 'D';
	const char EMERALD = 'E';
	const char CIRCLE = 'O';
	const char VERTICAL_PLAT = 'V';
	const char ENEMY_SLOW = 'S';
	const char ENEMY_SLOW_RIGHT = '8';
	const char ENEMY_FAST = '&';
	const char ENEMY_FAST_RIGHT = 'K';
	const char ENEMY_FAST_RUN_LEFT = 'N';
	const char ENEMY_FAST_RUN_RIGHT = 'U';
	const char ENEMY_FAST_LEFT_HIT = 'A';
	const char ENEMY_FAST_RIGHT_HIT = ':';
	const char BOSS = 'B';
	const char BOSS_RIGHT = '_';
	const char BOSS_SHOOT1_LEFT = '1';
	const char BOSS_SHOOT1_RIGHT = '/';
	const char BOSS_SHOOT2_LEFT = ',';
	const char BOSS_SHOOT2_RIGHT = '~';
	const char BOSS_EGG_LEFT = ']';
	const char BOSS_EGG_RIGHT = '[';
	const char BOSS_HAMMER_LEFT = ';';
	const char BOSS_HAMMER_RIGHT = 'H';
	const char BULLET = '*';

	const char GAME_OVER = 'G';
	const char WIN = 'w';

	const char BOSS_DEAD = 'D';
	const char WELCOME = 'W';
	const char MAIN_MENU = 'm';
	const char TIME = 'y';
	const char HEART = 'h';
	const char LIFE_BAR = 'q';
}
//---------------------------------------

//const char* OUTPUT_PATH = "../../../resources/BoardLevels/output.txt";
//const char* DEFAULT_PATH = "Board.txt";










//
//enum Type
//{
//	PLAY_BUTTON, PAUSE_BUTTON, STOP_BUTTON, START_BUTTON, EXIT_BUTTON, CREATE_BUTTON,
//	SOUND_ON, SOUND_OFF, SOUND_LOW, SETTINGS, PAUSE, HELP, HELP_WINDOW,
//	NEXT, BACK, RESTART, BEGIN, DELETE_BUTTON, CLEAR, SAVE, CLOSE, EMPTY,
//	BACKGROUND1, BACKGROUND2, BACKGROUND3, BACKGROUND_OPTIONS, PLAYER, PLAYER_LEFT_START,
//	PLAYER_STAY1, PLAYER_STAY2, PLAYER_STAY3, PLAYER_STAY4, FLOOR, POLE, WALL,
//	RUN1_RIGHT, RUN1_LEFT, RUN0_RIGHT, RUN0_LEFT, RUN2_RIGHT, RUN2_LEFT, READY_RIGHT,
//	READY_LEFT, WALK_RIGHT, WALK_LEFT, RUN_RIGHT, RUN_LEFT, JUMP_RIGHT,
//	JUMP_LEFT, RING,
//	SPRINGBOARD,
//	SPRING_J_R,
//	BALL_SPEED, SPIKES, JUMP, HORIZONTAL_PLAT,
//	GET_DOWN, EMERALD, CIRCLE, VERTICAL_PLAT, ENEMY_SLOW, ENEMY_SLOW_RIGHT,
//	ENEMY_FAST, ENEMY_FAST_RIGHT,
//	ENEMY_FAST_RUN_LEFT,
//	ENEMY_FAST_RUN_RIGHT,
//	ENEMY_FAST_LEFT_HIT,
//	ENEMY_FAST_RIGHT_HIT,
//	BOSS,
//	BOSS_RIGHT,
//	BOSS_SHOOT1_LEFT,
//	BOSS_SHOOT1_RIGHT,
//	BOSS_SHOOT2_LEFT,
//	BOSS_SHOOT2_RIGHT,
//	BOSS_EGG_LEFT,
//	BOSS_EGG_RIGHT,
//	BOSS_HAMMER_LEFT,
//	BOSS_HAMMER_RIGHT, BULLET,
//
//	GAME_OVER,
//	WIN,
//
//	BOSS_DEAD,
//	WELCOME,
//	MAIN_MENU,
//	TIME,
//	HEART,
//	LIFE_BAR
//};