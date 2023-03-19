#include <iostream>
#include "Game.h"
#include "Player.h"

int main()
{
    //Init Game
    Game game;
    

    //Game loop
    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();
        
    }

    //End of APP
    return 0;
}