#ifndef __TextureManager__
#define __TextureManager__


#include <SDL2/SDL_render.h>
#include <map>
#include <string>

class TextureManager {

public:
    bool load(std::string filename, std::string id, SDL_Renderer* pRenderer);

    // draw
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // drawframe
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    std::map<std::string, SDL_Texture*> m_textureMap;
};

#endif // defined(__SDL_Game_Programming_Book__TextureManager__)