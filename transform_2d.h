
/*******************************************************************************************
*
*   2d transformations
*
*   Copyright (c) 2022 Jeffery Myers
*
********************************************************************************************/


// define RAY2D_TRANSFORM_IMPLEMENTATION in one and only one c/cpp files

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"

#if defined(__cplusplus)
extern "C"
{
#endif

	typedef struct Transform2D
	{
		Vector2 translation;
		float rotation;
		float scale;
	} Transform2D;

	void TransformPoint(Transform2D* transform, Vector2* point);
	void TransformPoints(Transform2D* transform, Vector2* points, int pointCount);

#ifdef TRANSFORM2D_IMPLEMENTATION

	// Transform a single point by scaling, rotating, then transliting it directly
	void TransformPoint(Transform2D* transform, Vector2* point)
	{
		*point = Vector2Add(
			Vector2Rotate(
				Vector2Scale(*point, transform->scale),
				transform->rotation),
			transform->translation
		);
	}

	// Transform multiply points by building a transformation matrix, then applying it to each point
	void TransformPoints(Transform2D* transform, Vector2* points, int pointCount)
	{
		Matrix translation = MatrixTranslate(transform->translation.x, transform->translation.y, 0.0f);
		Matrix rotation = MatrixRotateZ(transform->rotation);
		Matrix scale = MatrixScale(transform->scale, transform->scale, transform->scale);
		Matrix transformation = MatrixMultiply(MatrixMultiply(scale, rotation), translation);
		for (int i = 0; i < pointCount; i++)
			points[i] = Vector2Transform(points[i], transformation);
	}

#endif //TRANSFORM2D_IMPLEMENTATION

#if defined(__cplusplus)
}
#endif