#pragma once
#include <iostream>

namespace Engine {
	namespace Math {

		struct Vector2 {
			float x, y;

			Vector2();
			Vector2(const float& x, const float& y);

			Vector2& add(const Vector2& other);
			Vector2& multiply(const Vector2& other);
			Vector2& substract(const Vector2& other);
			Vector2& divide(const Vector2& other);

			friend Vector2 operator-(Vector2 left, const Vector2& right);
			friend Vector2 operator*(Vector2 left, const Vector2& right);
			friend Vector2 operator/(Vector2 left, const Vector2& right);
			friend Vector2 operator+(Vector2 left, const Vector2& right);

			Vector2& operator+=(const Vector2& right);
			Vector2& operator-=(const Vector2& right);
			Vector2& operator*=(const Vector2& right);
			Vector2& operator/=(const Vector2& right);

			bool operator==(const Vector2& other);
			bool operator!=(const Vector2& other);
			bool operator<(const Vector2& other);
			bool operator>(const Vector2& other);

			float dist(const Vector2& other) const;

			friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		};


	}
}
