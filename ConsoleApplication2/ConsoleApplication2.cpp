#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Game.h"

int main()
{
    Game game;
    bool running = true;

    while (running)
    {
        if (_kbhit())
        {
            int key = _getch();

            if (key == 0 || key == 224)
            {
                key = _getch();
                if (key == 75)
                {
                    game.MoveLeft();
                }
                else if (key == 77)
                {
                    game.MoveRight();
                }
            }
            else if (key == ' ')
            {
                game.Jump();
            }
            else if (key == 'a' || key == 'A')
            {
                game.MoveLeft();
            }
            else if (key == 'd' || key == 'D')
            {
                game.MoveRight();
            }
            else if (key == 'q' || key == 'Q')
            {
                running = false;
            }
        }

        game.Update();
        game.Draw();
        Sleep(50);
    }

    std::cout << "Game Over!\n";
    return 0;
}
