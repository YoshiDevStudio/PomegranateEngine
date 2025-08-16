mkdir bin
g++ -shared ./src/Engine/*.cpp -o ./lib/PomegranateEngine.dll -I ".\include" -L ".\lib" -lSDL3 -lSDL3_image -std=c++23 -DBUILD_DLL -D_DEBUG
g++ ./src/Game/*.cpp -o ./bin/main.exe -I ".\include" -I ".\src\Engine" -L ".\lib" -lSDL3 -lPomegranateEngine -std=c++23 -D_DEBUG
copy ".\lib\*.dll" ".\bin\"
cd .\bin
.\main.exe
cd ..\
