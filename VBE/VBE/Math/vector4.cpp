#include "vector4.h"

namespace Engine {

	namespace Math {

		Vector4::Vector4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		Vector4::Vector4(const float& _x, const float& _y, const float& _z, const float& _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		Vector4::Vector4(const Vector3 & vec, const float& _w)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = _w;
		}

		Vector4& Vector4::add(const Vector4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vector4& Vector4::multiply(const Vector4& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Vector4& Vector4::substract(const Vector4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vector4& Vector4::divide(const Vector4& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}


		Vector4 operator+(Vector4 left, const Vector4& rigth)
		{
			return left.add(rigth);
		}

		Vector4 operator-(Vector4 left, const Vector4& rigth)
		{
			return left.substract(rigth);
		}

		Vector4 operator*(Vector4 left, const Vector4& rigth)
		{
			return left.multiply(rigth);
		}

		Vector4 operator/(Vector4 left, const Vector4& rigth)
		{
			return left.divide(rigth);
		}

		Vector4& Vector4::operator+=(const Vector4& rigth)
		{
			return add(rigth);
		}

		Vector4& Vector4::operator-=(const Vector4& rigth)
		{
			return substract(rigth);
		}

		Vector4& Vector4::operator/=(const Vector4& rigth)
		{
			return divide(rigth);
		}

		Vector4& Vector4::operator*=(const Vector4& rigth)
		{
			return multiply(rigth);
		}

		bool Vector4::operator==(const Vector4& other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool Vector4::operator!=(const Vector4& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
		{
			stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}

	}
}