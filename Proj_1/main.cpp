//In order to run this whole program, we need to include all header files


#include "globals.h"
#include "Player.h"
#include "Vampire.h"
#include "Game.h"
#include "History.h"
#include "Arena.h"

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

      // Play the game
    g.play();
}

