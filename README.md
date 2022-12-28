# extras-c
<img align="left" src="https://github.com/raysan5/raylib/raw/master/logo/raylib_logo_animation.gif" width="64">
Useful comonents for use the [Raylib](https://www.raylib.com/) library (C language version). 

Note that the C versions of any extra can be used in C++ without issue.

# Building
raylib-extras is setup to use premake to generate static libraries and examples for Visual Studio 2022 and makefiles for gcc on linux/mac OS and mingw on windows. 
The system is based on game-premake and will download raylib for you. Please see https://github.com/raylib-extras/game-premake for more info.

# Components
raylib-extras is broken up into modular components. Most components are designed to be used standalone.

## ray_collision_2d.h
A single file header with utillities to help detect collisions between 2d rays and various shapes.

## path_utils
Utilities to help manage paths with raylib and other games.

### application_dir
A single function to locate the folder/directory that the running executable is in. Used to set your working directory for future raylib resource loads.

### resource_dir
A single function to locate a named resource/assets folder relative to several common locations and set it as the working directory.
Checks the follopwing paths untill it finds the specificed folder name.
1) Working Dir
2) Applicaiton Dir
3) Up to 3 levels above the application dir

This can be very useful to ensure that the working dir is set correctly on whatever platform your game is running on, regardless of how it is started.

A simple way to call the funciton would be.
```
   if (!SearchAndSetResourceDir("resources"))
        TraceLog(LOG_ERROR, "Resources dir Not Found!");
    TraceLog(LOG_INFO, "Using working dir %s", GetWorkingDirectory());
```

## Cameras
There are 3 different camera controllers provided in raylib-extras. Each one is intended to show an example of a different way to move the camera around a scene.

### rlFPCamera
This is a first person camera. It uses the traditional mouse and WASD keys for movement. It provides position and view angle data back to the calling application.
See cameras/rlFPCamera/samples/example.c for a simple use case.

![fpCamera](https://user-images.githubusercontent.com/322174/136627569-64e0b660-d846-4b1c-9239-5e09b030b2aa.gif)

### rlTPCamera
This is a third person camera. It uses the traditional mouse and WASD keys for movement. It follows a target position and lets the user rotate around that as it moves.
See cameras/rlTPCamera/samples/example.c for a simple use case.
![tpCamera](https://user-images.githubusercontent.com/322174/136641801-3f7f0a05-e79a-4f67-b05a-217e183eedde.gif)


# Other langauges
raylib-extras is broken up into seperate repositories per language.

 * C and C++ https://github.com/raylib-extras/extras-c 
 * C++ https://github.com/raylib-extras/extras-cpp
 * C# https://github.com/raylib-extras/extras-cs

