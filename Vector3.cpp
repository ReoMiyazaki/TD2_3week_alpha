#include "Vector3.h"
#include <cmath>

// �R���X�g���N�^
// ��x�N�g���Ƃ��Đ���
Vector3::Vector3() : x(0), y(0), z(0) {}

// x, y, z�������w�肵�Ă̐���
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// �m����(����)�����߂�
float Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

// ���K��
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

// ���ς����߂�
float Vector3::dot(const Vector3& v)const
{
	return x * v.x + y * v.y + z * v.z;
}

// �O�ς����߂�
Vector3 Vector3::cross(const Vector3& v) const
{
	return  {
		{y * v.z - z * v.y},
		{z * v.x - x * v.z},
		{x * v.y - y * v.x}
	};
}

// �P�����Z�q�I�[�o�[���[�h
Vector3 Vector3::operator+() const
{
	return *this;
}
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

// ������Z�q�I�[�o�[���[�h
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

bool Vector3::operator==(const Vector3 v)
{
	

	return (x == v.x)&&(y == v.y)&&(z == v.z);
}

const Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const float Timer)
{
	return start * (1.0f - Timer) + end * Timer;
}

// 2�����Z�q�I�[�o�[���[�h
// �������Ȉ����̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}
const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}
const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}
const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}