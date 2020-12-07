
#include "Game.h"


int main() {

	// Init random seed
	srand(static_cast<unsigned>(time(0)));

	// Game loop
	Game game;
	
	while (game.running())
	{
		game.update();
		game.render();

	}

		return 0;
}