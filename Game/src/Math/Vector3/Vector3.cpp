#include "stdafx.h"

#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

Vector3::Vector3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ), w(1.0f)
{
}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3 Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
    return Vector3(this->x / scalar, this->y / scalar, this->z / scalar);
}

Vector3 Vector3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector3::operator==(const Vector3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3 &other) const
{
    return x != other.x || y != other.y || z != other.z;
}

float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSquared() const
{
    return x * x + y * y + z * z;
}

Vector3 Vector3::Normalize() const
{
    assert(this->LengthSquared() > 0);
    return *this / this->Length();
}

float Vector3::Dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::Cross(const Vector3 &other) const
{
    return Vector3(y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - other.x * y);
}

std::string Vector3::ToString() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}