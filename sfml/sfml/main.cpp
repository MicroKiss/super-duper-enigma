#include "Game.h"

int main ()
{
	Game game;
	while (game.IsAlive ()) {
		game.Update ();
		game.Draw ();
	}

	return 0;
}