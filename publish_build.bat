mkdir bin
g++ -shared ./src/Engine/*.cpp -o ./lib/Engine.dll -I ".\include" -L ".\lib" -lSDL3 -lSDL3_image -std=c++23 -DBUILD_DLL
g++ ./src/Game/*.cpp -o ./bin/main.exe -I ".\include" -I ".\src\Engine" -L ".\lib" -lSDL3 -lEngine -std=c++23  -mwindows
copy ".\lib\*.dll" ".\bin\"