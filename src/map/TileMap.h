#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class TileMap {
public:
    bool loadMap(const std::string& jsonPath, SDL_Renderer* renderer, const std::string& tilesetPath);
    void render(SDL_Renderer* renderer);

private:
    int mapWidth, mapHeight;
    int tileWidth, tileHeight;
    int tilesetColumns;
    int firstgid = 1;

    SDL_Texture* tilesetTexture = nullptr;
    std::vector<int> tileData;
};

#endif
