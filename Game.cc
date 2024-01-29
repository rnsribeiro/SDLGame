#include "Game.h"
#include <iostream>

Game::Game() : m_pWindow(nullptr), m_pRenderer(nullptr), m_bRunning(false) {}

Game::~Game() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != nullptr) {
            std::cout << "Window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != nullptr) {
                std::cout << "Renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            } else {
                std::cout << "Renderer init fail\n";
                return false;
            }
        } else {
            std::cout << "Window init fail\n";
            return false;            
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }
    std::cout << "Init success\n";
    m_bRunning = true;
    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
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

