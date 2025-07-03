@echo off
echo Compilando Stormy Engine...
g++ src/main.cpp src/core/*.cpp src/entities/*.cpp src/map/*.cpp -Iinclude -Isrc/utils -Llib -lmingw32 -lSDL2main -lSDL2 -o bin/stormy.exe
echo ---
echo Build completado. Ejecutando...
echo ---
bin\stormy.exe
pause
