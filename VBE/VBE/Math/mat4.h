#pragma once
#include <iostream>
#include "vector3.h"
#include "vector4.h"
#include "funcs.h"

namespace Engine {

	namespace Math {

		struct mat4 {

			union
			{
				float elements[16];
				Vector4 columns[4];
			};

			mat4();
			mat4(float diagonal);

			static mat4 identity();

			static mat4 orthographic(float left, float rigth, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translation(const Vector3& translation);
			static mat4 rotation(const Vector3& axis, float angle);
			static mat4 scale(const Vector3& scale);


			mat4& multiply(const mat4& other);
			friend mat4 operator*(mat4 left, const mat4& rigth);
			mat4& operator*=(const mat4& other);

			Vector3 multiply(const Vector3& other) const;
			friend Vector3 operator*(const mat4& left, const Vector3& rigth);
			Vector4 multiply(const Vector4& other) const;
			friend Vector4 operator*(const mat4& left, const Vector4& rigth);

			friend std::ostream& operator<<(std::ostream& stream, const mat4& mat);

		};
	}
}
