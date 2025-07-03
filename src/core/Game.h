#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../entities/Player.h"
#include "../map/TileMap.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player* player;
    TileMap tileMap;

    void handleEvents();
    void update();
    void render();
};

#endif
