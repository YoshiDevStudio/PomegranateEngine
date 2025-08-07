mkdir bin
g++ -shared ./src/Engine/*.cpp -o ./lib/Engine.dll -I ".\include" -L ".\lib" -lSDL3 -std=c++23
g++ ./src/Game/*.cpp -o ./bin/main.exe -I ".\include" -I ".\src\Engine" -L ".\lib" -lSDL3 -lEngine -std=c++23
copy ".\lib\*.dll" ".\bin\"
.\bin\main.exe
