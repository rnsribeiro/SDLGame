#include "Game.h"

int main(int argc, char* argv[]){
    Game* g_game = new Game();

    g_game->init("Chapter 1", 100, 100, 155, 97, false);

    while (g_game->running()) {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }

    g_game->clean();
    delete g_game;

    return 0;
}
