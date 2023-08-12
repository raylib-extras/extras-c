
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

	bool CheckCollisionRay2dRay2d(Ray2d ray1, Ray2d ray2, float* length);
	bool CheckCollisionRay2dRect(Ray2d ray, Rectangle rect, Vector2* intersection);
	bool CheckCollisionRay2dCircle(Ray2d ray, Vector2 center, float radius, Vector2* intersection);
	bool CheckCollisionRay2dPoly(Ray2d ray, Vector2* points, int pointCount, Vector2* intersection);

#ifdef RAY2D_COLLISION_IMPLEMENTATION

	// https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/565282

	bool CheckCollisionRay2dRay2d(Ray2d ray1, Ray2d ray2, float* length) 
	{
		float rXs = (ray1.Direction.x * ray2.Direction.y) - (ray1.Direction.y * ray2.Direction.x); 

		Vector2 qp = Vector2Subtract(ray2.Origin, ray1.Origin);

		float qpXs = (qp.x * ray2.Direction.y) - (qp.y * ray2.Direction.x);
		float qpXr = (qp.x * ray1.Direction.y) - (qp.y * ray1.Direction.x);

		if (rXs != 0.0f) 
		{
			float inverseRxS = 1.0f / rXs;

			float t = qpXs * inverseRxS, u = qpXr * inverseRxS;

			if ((t >= 0.0f && t <= 1.0f) && (u >= 0.0f && u <= 1.0f)) 
			{
				if (length) 
				{
					*length = t;
				}

				return true;
			}
		} 
		else
		{
			if (qpXr != 0.0f) return false;

			float rDr = Vector2DotProduct(ray1.Direction, ray1.Direction);
			float sDr = Vector2DotProduct(ray2.Direction, ray1.Direction);

			float inverseRdR = 1.0f / rDr;

			float qpDr = Vector2DotProduct(qp, ray1.Direction);

			float t0 = qpDr * inverseRdR, t1 = t0 + sDr * inverseRdR;

			if (sDr < 0.0f)
			{
				float tmp = t0;
				
				t0 = t1, t1 = tmp;
			}

			if ((t0 < 0.0f && t1 == 0.0f) || (t0 == 1.0f && t1 > 1.0f)) 
			{
				if (length) 
				{
					*length = (t0 == 1.0f);
				}

				return true;
			}

			if (t1 >= 0.0f && t0 <= 1.0f) 
			{
				// the rays are collinear and overlapping
				return false;
			}

			return false;
		}
	}

	// intersection using the slab method
	// https://tavianator.com/2011/ray_box.html#:~:text=The%20fastest%20method%20for%20performing,remains%2C%20it%20intersected%20the%20box.

	bool CheckCollisionRay2dRect(Ray2d ray, Rectangle rect, Vector2* intersection)
	{
		float minParam = -INFINITY, maxParam = INFINITY;

		if (ray.Direction.x != 0.0)
		{
			float txMin = (rect.x - ray.Origin.x) / ray.Direction.x;
			float txMax = ((rect.x + rect.width) - ray.Origin.x) / ray.Direction.x;

			minParam = fmax(minParam, fmin(txMin, txMax));
			maxParam = fmin(maxParam, fmax(txMin, txMax));
		}

		if (ray.Direction.y != 0.0)
		{
			float tyMin = (rect.y - ray.Origin.y) / ray.Direction.y;
			float tyMax = ((rect.y + rect.height) - ray.Origin.y) / ray.Direction.y;

			minParam = fmax(minParam, fmin(tyMin, tyMax));
			maxParam = fmin(maxParam, fmax(tyMin, tyMax));
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
			*intersection = Vector2Add(ray.Origin, Vector2Scale(ray.Direction, minParam));
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

	bool CheckCollisionRay2dPoly(Ray2d ray, Vector2* points, int pointCount, Vector2* intersection) 
	{
		if (points == NULL || pointCount < 3) 
		{
			return false;
		}

		Vector2 result = { INFINITY, INFINITY };

		float distSq = INFINITY;

		for (int j = pointCount - 1, i = 0; i < pointCount; j = i, i++) 
		{
			Ray2d edgeRay = { 
				.Origin = points[i],
				.Direction = Vector2Subtract(points[j], points[i])
			};

			float length = -INFINITY;

			bool intersect = CheckCollisionRay2dRay2d(ray, edgeRay, &length);

			Vector2 nearest = Vector2Add(ray.Origin, Vector2Scale(ray.Direction, length));

			float nearestDistSq = Vector2DistanceSqr(ray.Origin, nearest);

			if (distSq > nearestDistSq) 
			{
				result = nearest, distSq = nearestDistSq;
			}
		}

		if (distSq == INFINITY) 
		{
			return false;
		}

		if (intersection) 
		{
			*intersection = result;
		}

		return true;
	}

#endif //RAY2D_COLLISION_IMPLEMENTATION

#if defined(__cplusplus)
}
#endif