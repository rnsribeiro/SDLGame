#ifndef __Game__
#define __Game__

#include "SDL2/SDL.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    //void update();
    void handleEvents();
    void clean();
    bool running();

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture; // the new SDL_Texture variable
    SDL_Rect m_sourceRectangle; // the first rectangle
    SDL_Rect m_destinationRectangle; // another rectangle
    bool m_bRunning;
};

#endif /* defined(__Game__) */
