
#include "Game.h"


int main()
{
    
    Game game;

    while (game.running())
    {
        game.Update();
        game.Render();
    }
    return 0;
}