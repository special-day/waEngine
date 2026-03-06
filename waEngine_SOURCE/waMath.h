#pragma once
#include "cmath"

namespace wa::math
{
#define PI 3.141592f

	struct Vector2
	{
		static Vector2 Rotate(Vector2 v, float degree)
		{
			float radian = (degree / 180.0f) * PI;
			v.normalize();
			float x = cosf(radian) * v.x - sinf(radian) * v.y;
			float y = sinf(radian) * v.x + cosf(radian) * v.y;

			return Vector2(x, y);
		}

		static float Dot(Vector2& v1, Vector2& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		static Vector2 One;
		static Vector2 Zero;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

		float x;
		float y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{

		}

		Vector2(float _x, float _y)
			: x(_x)
			, y(_y)
		{
		}

		Vector2 operator -(const Vector2& other) 
		{
			return Vector2(x - other.x, y - other.y);
		}
		
		Vector2 operator +(const Vector2& other)
		{
			return Vector2(x + other.x, y + other.y); 
		}

		void operator +=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}
		
		Vector2 operator /(float value) 
		{
			return Vector2(x / value, y / value); 
		}

		Vector2 operator *(float value)
		{
			return Vector2(x * value, y * value);
		}

		Vector2 operator *(const Vector2& other)
		{
			return Vector2(x * other.x, y * other.y);
		}

		bool operator ==(const Vector2& other)
		{
			return (x == other.x) && (y == other.y);
		}

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}


		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2 normalize()
		{
			float len = length();
			x /= len;
			y /= len;

			return *this;
		}
	};
	
}

