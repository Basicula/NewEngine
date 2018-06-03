#pragma once
#include <iostream>
#include "vector3.h"

namespace Engine {

	namespace Math {

		struct Vector4 {
			float x, y, z, w;

			Vector4();
			Vector4(const float& x, const float& y, const float& z, const float& w);
			Vector4(const Vector3 &vec, const float& _w);

			Vector4& add(const Vector4& other);
			Vector4& multiply(const Vector4& other);
			Vector4& substract(const Vector4& other);
			Vector4& divide(const Vector4& other);

			friend Vector4 operator-(Vector4 left, const Vector4& rigth);
			friend Vector4 operator*(Vector4 left, const Vector4& rigth);
			friend Vector4 operator/(Vector4 left, const Vector4& rigth);
			friend Vector4 operator+(Vector4 left, const Vector4& rigth);

			Vector4& operator+=(const Vector4& rigth);
			Vector4& operator-=(const Vector4& rigth);
			Vector4& operator*=(const Vector4& rigth);
			Vector4& operator/=(const Vector4& rigth);

			bool operator==(const Vector4& other);
			bool operator!=(const Vector4& other);

			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
		};


	}
}
