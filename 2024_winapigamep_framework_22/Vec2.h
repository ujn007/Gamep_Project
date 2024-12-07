#pragma once
#include<assert.h>
struct Vec2
{
public:
	Vec2() = default;
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	//Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}
public:
	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}
	Vec2 operator + (const Vec2& _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (const Vec2& _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (const Vec2& _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator * (float _val)
	{
		return Vec2(x * _val, y * _val);
	}
	Vec2 operator / (const Vec2& _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	void operator+=(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
	}
	void operator-=(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
	}
	void operator*=(float _f)
	{
		x *= _f;
		y *= _f;
	}
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}
	float LengthSquared()
	{
		return x * x + y * y;
	}
	float Length()
	{
		return ::sqrt(LengthSquared());
	}
	Vec2& Normalize()
	{
		float len = Length();
		// 0�̸� �ȵ�.
		assert(len > FLT_EPSILON);

		x /= len;
		y /= len;
		return *this;
	}
	float Dot(Vec2 _other)
	{
		return x * _other.x + y * _other.y;
	}
	float Cross(Vec2 _other)
	{
		// z���� ���´ٰ� ����
		return x * _other.y - y * _other.x;
	}
public:
	float x = 0.f;
	float y = 0.f;
};