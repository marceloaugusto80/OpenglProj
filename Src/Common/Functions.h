#pragma once

#include "Types.h"


#define MIN(A,B) ((A < B) ? A : B)
#define MAX(A,B) ((A > B) ? A : B)



inline float Normalize(float value, float min, float max)
{
	return (value - min) / (max - min);
}

inline float Normalize(float value, float max)
{
	return value / max;
}



inline Mat4f Translate(const Vec3 & position)
{
	return glm::translate(Mat4f(1.0), position);
}

inline Mat4f Translate(const Mat4f & matrix, const Vec3 & position)
{
	return glm::translate(matrix, position);
}

inline Mat3f Translate(const Mat3f & matrix, const Vec2 & position)
{
	return glm::translate(matrix, position);
}

inline Mat3f Translate(const Vec2 & position)
{
	return Translate(Mat3f(1.0f), position);
}



inline Mat4f Rotate(float angle, const Vec3 & axis)
{
	return glm::rotate(Mat4f(1.0), angle, axis);
}

inline Mat4f Rotate(const Mat4f & matrix, float angle, const Vec3 & axis)
{
	return glm::rotate(matrix, angle, axis);
}



inline Mat4f Scale(const Vec3 & scale)
{
	return glm::scale(Mat4f(1.0), scale);
}

inline Mat4f Scale(const Mat4f & matrix, const Vec3 & scale)
{
	return glm::scale(matrix, scale);
}

inline Mat3f Scale(const Mat3f & matrix, const Vec2 & scale)
{
	return glm::translate(matrix, scale);
}

inline Mat3f Scale(const Vec2 & scale)
{
	return Scale(Mat3f(1.0f), scale);
}


