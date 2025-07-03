#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
public:
    Player(int x, int y, int size, int speed);
    void handleInput(const Uint8* keyboardState);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect rect;
    int speed;
};

#endif
