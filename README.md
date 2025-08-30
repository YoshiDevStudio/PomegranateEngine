# Pomegranate Engine

This is a 2D Game Engine built on top of SDL3 I built for learning purposes and for fun!
Pomegranate Engine's features so far are:

* Rendering Sprites
* Animations
* Tilemaps
* Cameras
* Logging
* Collisions
* Physics (Linear Motion Only)
* Gizmos

# Build Instructions

This engine is only built for **Windows**.
If you build on a different operating system there may be unexpected bugs and/or glitches

## Dependencies

To compile Pomegranate Engine, you will need to have access to the g++ terminal command.
You can get this by downloading [MinGW](https://sourceforge.net/projects/mingw-w64/)

Afterwards you can compile by running the included .bat files.
* build.bat will build the example application and move all necessary .dll files to the bin folder with the engines built in Debug functionalities such as Logging and Gizmos
* run.bat will do the same as build.bat but also run the application once everything is finished building
* publish_build.bat will build the example application and move all necessary .dll files to the bin folder without any of the Debug engine features, this is what you should use when shipping your game.
