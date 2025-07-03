#include "Game.h"
#include <iostream>

Game::Game() {
    std::cout << "Inicializando juego..." << std::endl;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Stormy Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "❌ Error creando ventana: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << "Ventana creada correctamente" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "❌ Error creando renderer: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << "Renderer creado correctamente" << std::endl;

    // Cargar mapa
    std::cout << "Cargando mapa..." << std::endl;
    if (!tileMap.loadMap("assets/maps/mapa1.json", renderer, "assets/maps/tilesets/base_grass_detail_S.png")) {
        std::cerr << "❌ No se pudo cargar el mapa\n";
    }

    std::cout << "Mapa cargado correctamente" << std::endl;

    // Crear jugador
    player = new Player(400, 300, 32, 4);  // posición inicial centrada aprox.

    std::cout << "Jugador creado correctamente" << std::endl;
}

Game::~Game() {
    std::cout << "Liberando recursos..." << std::endl;
    delete player;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Recursos liberados correctamente" << std::endl;
}

void Game::update() {
    std::cout << "Actualizando juego..." << std::endl;
    // Lógica de juego
}

void Game::render() {
    std::cout << "Renderizando juego..." << std::endl;
    // Renderizar juego
}