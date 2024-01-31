#include "Game.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game() : m_pWindow(nullptr), m_pRenderer(nullptr), m_bRunning(false), m_pTexture(nullptr) {}

Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL init fail: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow == nullptr) {
        std::cout << "Window creation fail: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Create renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_pRenderer == nullptr) {
        std::cout << "Renderer creation fail: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return false;
    }

    // Load texture
    SDL_Surface* pTempSurface = IMG_Load("assets/animate-alpha.png");
    if (pTempSurface == nullptr) {
        std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return false;
    }

    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    if (m_pTexture == nullptr) {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(m_pRenderer);
        SDL_DestroyWindow(m_pWindow);
        SDL_Quit();
        return false;
    }

    // Set initial values for source rectangle
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;
    m_sourceRectangle.w = 155; // Width of the visible area of the tiger
    m_sourceRectangle.h = 97; // Height of the tiger image

    // Set initial values for destination rectangle
    m_destinationRectangle.x = 0; // X position in the window where the image will be rendered
    m_destinationRectangle.y = 0; // Y position in the window where the image will be rendered
    m_destinationRectangle.w = m_sourceRectangle.w; // Width of the destination rectangle
    m_destinationRectangle.h = m_sourceRectangle.h; // Height of the destination rectangle

    std::cout << "Init success\n";
    m_bRunning = true;
    return true;
}


void Game::update() {
    m_sourceRectangle.x = 156 * int(((SDL_GetTicks() / 100 ) % 6));
}


void Game::render() {
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 
        0, 0, SDL_FLIP_HORIZONTAL); // pass in the horizontal flip

    SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::clean() {
    std::cout << "Cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}

