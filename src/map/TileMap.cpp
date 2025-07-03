#include "TileMap.h"
#include <fstream>
#include <iostream>
#include "../utils/json.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

using json = nlohmann::json;

bool TileMap::loadMap(const std::string& jsonPath, SDL_Renderer* renderer, const std::string& tilesetPath) {
    std::cout << "📄 Cargando archivo JSON: " << jsonPath << std::endl;
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "❌ No se pudo abrir el mapa: " << jsonPath << std::endl;
        return false;
    }

    json j;
    file >> j;

    std::cout << "✅ Archivo JSON cargado correctamente" << std::endl;

    mapWidth = j["width"];
    mapHeight = j["height"];
    tileWidth = j["tilewidth"];
    tileHeight = j["tileheight"];
    tileData = j["layers"][0]["data"].get<std::vector<int>>();

    if (!j["tilesets"].empty()) {
        firstgid = j["tilesets"][0]["firstgid"];
        std::cout << "🔢 firstgid leído del JSON: " << firstgid << std::endl;
    }

    std::cout << "🖼️ Cargando tileset PNG: " << tilesetPath << std::endl;

    int imgW, imgH, imgC;
    unsigned char* pixels = stbi_load(tilesetPath.c_str(), &imgW, &imgH, &imgC, STBI_rgb_alpha);
    if (!pixels) {
        std::cerr << "❌ Error cargando PNG: " << stbi_failure_reason() << std::endl;
        return false;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels, imgW, imgH, 32, imgW * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        std::cerr << "❌ Error creando superficie desde pixels: " << SDL_GetError() << std::endl;
        stbi_image_free(pixels);
        return false;
    }

    tilesetTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(pixels);

    if (!tilesetTexture) {
        std::cerr << "❌ Error creando textura: " << SDL_GetError() << std::endl;
        return false;
    }

    int textureW;
    SDL_QueryTexture(tilesetTexture, NULL, NULL, &textureW, NULL);
    tilesetColumns = textureW / tileWidth;

    std::cout << "✅ Tileset cargado correctamente" << std::endl;
    return true;
}

void TileMap::render(SDL_Renderer* renderer) {
    if (!tilesetTexture) {
        std::cerr << "❌ No hay textura de tileset cargada." << std::endl;
        return;
    }

    int textureW, textureH;
    SDL_QueryTexture(tilesetTexture, NULL, NULL, &textureW, &textureH);
    int totalTiles = tilesetColumns * (textureH / tileHeight);

    // Cálculo del tamaño total del mapa en píxeles (isométrico)
    int mapPixelWidth  = (mapWidth + mapHeight) * (tileWidth / 2);
    int mapPixelHeight = (mapWidth + mapHeight) * (tileHeight / 2);

    // Offset para centrar el mapa en la pantalla
    int offsetX = (800 - mapPixelWidth) / 2;
    int offsetY = (600 - mapPixelHeight) / 2;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int rawIndex = tileData[y * mapWidth + x];
            if (rawIndex < firstgid) continue;

            int tileIndex = rawIndex - firstgid;
            if (tileIndex < 0 || tileIndex >= totalTiles) {
                std::cout << "⚠️ Tile fuera de rango: " << tileIndex << std::endl;
                continue;
            }

            SDL_Rect srcRect = {
                (tileIndex % tilesetColumns) * tileWidth,
                (tileIndex / tilesetColumns) * tileHeight,
                tileWidth, tileHeight
            };

            // 🧠 Proyección isométrica centrada
            int screenX = (x - y) * (tileWidth / 2) + offsetX;
            int screenY = (x + y) * (tileHeight / 2) + offsetY;

            SDL_Rect destRect = { screenX, screenY, tileWidth, tileHeight };
            SDL_RenderCopy(renderer, tilesetTexture, &srcRect, &destRect);
        }
    }

    std::cout << "🟩 TileMap renderizado correctamente.\n";
}