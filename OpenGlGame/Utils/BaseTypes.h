#pragma once

#include <cmath>
#include "glm\vec2.hpp"
#include "glm\mat3x3.hpp"
#include "glm\trigonometric.hpp"
#include "glm\gtc\matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm\gtx\matrix_transform_2d.hpp"

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat2x2 Mat2f;
typedef glm::mat3x3 Mat3f;
typedef glm::mat4x4 Mat4f;


#define PI 3.1415927


struct Rectf
{

	Rectf(float left, float top, float right, float bottom) :
		Left(left), Top(top), Right(right), Bottom(bottom)
	{}

	Rectf() :
		Rectf(0.0f, 0.0f, 0.0f, 0.0f)
	{}

	Rectf(const Vec2& origin, float width, float height) :
		Rectf(origin.x, origin.y, origin.x + width, origin.y + height)
	{}

	Rectf(const Vec2& topLeft, const Vec2& bottomRight) :
		Rectf(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)
	{
	}

	float GetWidth()
	{
		return Left + Right;
	}

	float GetHeight()
	{
		return Top + Bottom;
	}

	Vec2 GetSize()
	{
		return Vec2(GetWidth(), GetHeight());
	}

	float Left, Right, Top, Bottom;



};