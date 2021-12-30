/*******************************************************************************************
*
*   raylib extras samples * application path sample
*
*   Welcome to raylib!
*
*   Shows how to get the folder your game is running in
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "app_dir.h"
#include "raylib.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	// get the app path
	const char *appPath = rlGetApplicationBasePath();
	printf("application path = %s\n", appPath);

	// tell raylib to use this path as the new root
	ChangeDirectory(appPath);

	return 0;
}