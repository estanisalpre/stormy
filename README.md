# Stormy Engine

Motor de juego base 2D escrito en C++ con SDL2 para crear un MMORPG isométrico tipo Tibia/MU.

## Estructura

stormy-game/
├── src/ → Código fuente
│ ├── core/ → Motor principal
│ └── entities/ → Jugador, NPCs, etc.
├── include/ → Headers externos (SDL2)
├── lib/ → Librerías .lib/.a de SDL2
├── bin/ → Ejecutable final
│ └── SDL2.dll
├── build.bat → Script para compilar y ejecutar


## Requisitos

- g++ (MinGW-W64)
- SDL2 (copiar include/, lib/, y SDL2.dll)

## Cómo compilar

```bash
build.bat
