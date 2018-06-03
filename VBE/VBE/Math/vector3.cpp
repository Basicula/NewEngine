#include "vector3.h"

namespace Engine {

	namespace Math {

		Vector3::Vector3()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector3::Vector3(const float& _x, const float& _y, const float& _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		Vector3& Vector3::add(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& Vector3::multiply(const Vector3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3& Vector3::substract(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& Vector3::divide(const Vector3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}


		Vector3 operator+(Vector3 left, const Vector3& rigth)
		{
			return left.add(rigth);
		}

		Vector3 operator-(Vector3 left, const Vector3& rigth)
		{
			return left.substract(rigth);
		}

		Vector3 operator*(Vector3 left, const Vector3& rigth)
		{
			return left.multiply(rigth);
		}

		Vector3 operator/(Vector3 left, const Vector3& rigth)
		{
			return left.divide(rigth);
		}

		Vector3& Vector3::operator+=(const Vector3& rigth)
		{
			return add(rigth);
		}

		Vector3& Vector3::operator-=(const Vector3& rigth)
		{
			return substract(rigth);
		}

		Vector3& Vector3::operator/=(const Vector3& rigth)
		{
			return divide(rigth);
		}

		Vector3& Vector3::operator*=(const Vector3& rigth)
		{
			return multiply(rigth);
		}

		bool Vector3::operator==(const Vector3& other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vector3::operator!=(const Vector3& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
		{
			stream <<"("<< vector.x << ", " << vector.y<<", "<<vector.z<<")";
			return stream;
		}

	}
}