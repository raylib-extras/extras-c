/*******************************************************************************************
*
*   raylib [core] example - 2D Transformations Example
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
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

#define TRANSFORM2D_IMPLEMENTATION
#include "../transform_2d.h"
#include <memory.h>

int main()
{
	InitWindow(1280, 800, "2D Transformations");

	const Vector2 polygon[] = {
		{ 1.0f, -1.0f },
		{ 2.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ -1.0f, 1.0f },
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f }
	};

	Transform2D transform;
	transform.translation.x = 1280 * 0.5f;
	transform.translation.y = 800 * 0.5f;
	transform.rotation = -90.0f * DEG2RAD;
	transform.scale = 100.0f;
	
    const float translationSpeed = 350.0f;
    const float rotationSpeed = 250.0f * DEG2RAD;
    const float scaleSpeed = 100.0f;
    while (!WindowShouldClose())
    {
        // Prefer time-based over frame-based movement
        const float deltaTime = GetFrameTime();
        const float translationDelta = translationSpeed * deltaTime;
        const float rotationDelta = rotationSpeed * deltaTime;
        const float scaleDelta = scaleSpeed * deltaTime;

        // Scale up/down
        if (IsKeyDown(KEY_SPACE))
            transform.scale += scaleDelta;
        if (IsKeyDown(KEY_LEFT_SHIFT))
            transform.scale -= scaleDelta;

        // Rotate clockwise/counter-clockwise
        if (IsKeyDown(KEY_E))
            transform.rotation += rotationDelta;
        if (IsKeyDown(KEY_Q))
            transform.rotation -= rotationDelta;

        // Translate forwards/backwards
        const Vector2 forward = { cosf(transform.rotation), sinf(transform.rotation) };
        if (IsKeyDown(KEY_W))
            transform.translation = Vector2Add(transform.translation,
                Vector2Scale(forward, translationDelta));
        if (IsKeyDown(KEY_S))
            transform.translation = Vector2Subtract(transform.translation,
                Vector2Scale(forward, translationDelta));

        // Translate left/right
        const Vector2 right = { -forward.y, forward.x };
        if (IsKeyDown(KEY_A))
            transform.translation = Vector2Subtract(transform.translation,
                Vector2Scale(right, translationDelta));
        if (IsKeyDown(KEY_D))
            transform.translation = Vector2Add(transform.translation,
                Vector2Scale(right, translationDelta));

        // Transform from model-space to world-space
        Vector2 points[sizeof polygon / sizeof polygon[0]];
        memcpy(points, polygon, (sizeof points / sizeof points[0]) * sizeof(Vector2));
        TransformPoints(&transform, points, sizeof points / sizeof points[0]);

        // Transform the origin for reference
        Vector2 origin = Vector2Zero();
        TransformPoint(&transform, &origin);

        // Point-in-polygon test with mouse position to validate transformed polygon points
        const Vector2 mouse = GetMousePosition();
        const Color color = CheckCollisionPointPoly(mouse, points, sizeof points / sizeof points[0])
            ? RED : GREEN;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(mouse, 5.0f, DARKGRAY);
        DrawCircleV(origin, 5.0f, DARKGRAY);
        DrawLineEx(origin, Vector2Add(origin, Vector2Scale(forward, transform.scale)), 5.0f, DARKGRAY);
        DrawLineStrip(points, sizeof points / sizeof points[0], color);
        DrawText("SPACE / LSHIFT to scale up/down", 10, 10, 20, RED);
        DrawText("W / S to move forwards/backwards", 10, 30, 20, ORANGE);
        DrawText("A / D to move left/right", 10, 50, 20, BLUE);
        DrawText("E / Q to rotate clockwise/counter-clockwise", 10, 70, 20, PURPLE);
        DrawText("Mouse-over the polygon to change its color", 10, 90, 20, GREEN);
        EndDrawing();
    }

	CloseWindow();
	return 0;
}
