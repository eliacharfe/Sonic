#include "GameManager.h"

int main() try
{
	srand((int)time(NULL));
	GameManager game;
	game.run();

	return EXIT_SUCCESS;
}
catch (std::exception& e) {
	cerr << "Catch in main: " << e.what();
}

