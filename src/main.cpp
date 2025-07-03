#include "utils/json.hpp"
#include <fstream>
#include <iostream>
#include "core/Game.h"
#include "map/TileMap.h"

void testJson() {
    std::ifstream file("assets/maps/mapa1.json");
    if (!file.is_open()) {
        std::cerr << "❌ No se pudo abrir el JSON\n";
        return;
    }

    nlohmann::json j;
    file >> j;

    std::cout << "✅ El mapa tiene: " << j["width"] << "x" << j["height"] << std::endl;
}

int main(int argc, char* argv[]) {
    testJson();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "❌ Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Stormy Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "❌ No se pudo crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "❌ No se pudo crear el renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 👉 Carga y prueba del mapa antes de Game.run()
    TileMap map;
    if (!map.loadMap("assets/maps/mapa1.json", renderer, "assets/tilesets/base_grass_detail_S.png")) {
        std::cerr << "❌ Falló la carga del mapa\n";
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.render(renderer); // 👈 Aquí dibujamos el mapa

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
