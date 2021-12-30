# extras-c
<img align="left" src="https://github.com/raysan5/raylib/raw/master/logo/raylib_logo_animation.gif" width="64">
Useful comonents for use the [Raylib](https://www.raylib.com/) library (C language version). 

Note that the C versions of any extra can be used in C++ without issue.

# Building
raylib-extras is setup to use premake to generate static libraries and examples for Visual Studio 2019. Premake can also be used to generate makefiles for linux. Each of the extras can be used as a static library, or by direclty including the files into your game project.

If you wish to use premake, you will need to download the Premake5 executable for your platform from. https://premake.github.io/download

# Components
raylib-extras is broken up into modular components. Most components are designed to be used standalone.

## path_utils
Utilities to help manage paths with raylib and other games.

### application_dir
A single function to locate the folder/directory that the running executable is in. Used to set your working directory for future raylib resource loads.

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

### rlFreeCamera
TODO

# Other langauges
raylib-extras is broken up into seperate repositories per language.

 * C and C++ https://github.com/raylib-extras/extras-c 
 * C++ https://github.com/raylib-extras/extras-cpp
 * C# https://github.com/raylib-extras/extras-cs

