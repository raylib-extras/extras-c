
/*******************************************************************************************
*
*   2d ray collisions
*
*   Copyright (c) 2022 Jeffery Myers
*
********************************************************************************************/


// define RAY2D_COLLISION_IMPLEMENTATION in one and only one c/cpp files

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"

#if defined(__cplusplus)
extern "C"
{
#endif

	typedef struct
	{
		Vector2 Origin;
		Vector2 Direction;
	}Ray2d;

	bool CheckCollisionRay2dRect(Ray2d ray, Rectangle rect, Vector2* intersection);
	bool CheckCollisionRay2dCircle(Ray2d ray, Vector2 center, float radius, Vector2* intersection);

#ifdef RAY2D_COLLISION_IMPLEMENTATION

	// intersection using the slab method
	// https://tavianator.com/2011/ray_box.html#:~:text=The%20fastest%20method%20for%20performing,remains%2C%20it%20intersected%20the%20box.

	bool CheckCollisionRay2dRect(Ray2d ray, Rectangle rect, Vector2* intersection)
	{
		float minParam = -INFINITY, maxParam = INFINITY;

		if (direction.x != 0.0)
		{
			float txMin = (rect.x - origin.x) / direction.x;
			float txMax = ((rect.x + rect.width) - origin.x) / direction.x;

			minParam = max(minParam, min(txMin, txMax));
			maxParam = min(maxParam, max(txMin, txMax));
		}

		if (direction.y != 0.0)
		{
			float tyMin = (rect.y - origin.y) / direction.y;
			float tyMax = ((rect.y + rect.height) - origin.y) / direction.y;

			minParam = max(minParam, min(tyMin, tyMax));
			maxParam = min(maxParam, max(tyMin, tyMax));
		}

		// if maxParam < 0, ray is intersecting AABB, but the whole AABB is behind us
		if (maxParam < 0)
		{
			return false;
		}

		// if minParam > maxParam, ray doesn't intersect AABB
		if (minParam > maxParam)
		{
			return false;
		}

		if (intersection != NULL)
		{
			*intersection = Vector2Add(origin, Vector2Scale(direction, minParam));
		}
		return true;
	}

	bool CheckCollisionRay2dCircle(Ray2d ray, Vector2 center, float radius, Vector2* intersection)
	{
		if (CheckCollisionPointCircle(ray.Origin, center, radius))
		{
			if (intersection)
				*intersection = ray.Origin;

			return true;
		}

		Vector2 vecToCenter = Vector2Subtract(center, ray.Origin);
		float dot = Vector2DotProduct(vecToCenter, ray.Direction);

		Vector2 nearest = Vector2Add(ray.Origin, Vector2Scale(ray.Direction, dot));

		float distSq = Vector2LengthSqr(Vector2Subtract(nearest, center));

		if (distSq <= radius * radius)
		{
			if (intersection)
			{
				float nearestDist = Vector2Length(Vector2Subtract(center, nearest));

				float b = sqrtf(radius * radius - nearestDist * nearestDist);

				*intersection = (Vector2){ ray.Origin.x + ray.Direction.x * (dot - b), ray.Origin.y + ray.Direction.y * (dot - b) };
			}
		}

		return false;
	}

#endif //RAY2D_COLLISION_IMPLEMENTATION

#if defined(__cplusplus)
}
#endif