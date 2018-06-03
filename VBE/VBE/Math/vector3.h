#pragma once
#include <iostream>

namespace Engine {

	namespace Math {

		struct Vector3 {

			float x, y, z;

			Vector3();
			Vector3(const float& x, const float& y, const float& z);

			Vector3& add(const Vector3& other);
			Vector3& multiply(const Vector3& other);
			Vector3& substract(const Vector3& other);
			Vector3& divide(const Vector3& other);

			friend Vector3 operator-(Vector3 left, const Vector3& rigth);
			friend Vector3 operator*(Vector3 left, const Vector3& rigth);
			friend Vector3 operator/(Vector3 left, const Vector3& rigth);
			friend Vector3 operator+(Vector3 left, const Vector3& rigth);

			Vector3& operator+=(const Vector3& rigth);
			Vector3& operator-=(const Vector3& rigth);
			Vector3& operator*=(const Vector3& rigth);
			Vector3& operator/=(const Vector3& rigth);

			bool operator==(const Vector3& other);
			bool operator!=(const Vector3& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		};


	}
}
