#include "Player.h"

Player::Player(int x, int y, int size, int speed) {
    rect = { x, y, size, size };
    this->speed = speed;
}

void Player::handleInput(const Uint8* keyboardState) {
    if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W])
        rect.y -= speed;
    if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S])
        rect.y += speed;
    if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
        rect.x -= speed;
    if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
        rect.x += speed;

    // Límites de ventana
    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.x > 800 - rect.w) rect.x = 800 - rect.w;
    if (rect.y > 600 - rect.h) rect.y = 600 - rect.h;
}

void Player::update() {
    // Aquí podrías añadir física o animación
}

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanco
    SDL_RenderFillRect(renderer, &rect);
}
