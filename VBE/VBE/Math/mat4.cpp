#include "mat4.h"

namespace Engine {

	namespace Math {

		mat4::mat4()
		{
			for (int i = 0; i < 16; i++)
				elements[i] = 0;
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 16; i++) {
				if (!(i % 5)) elements[i] = diagonal;
				else elements[i] = 0;
			}
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other)
		{
			float result[16];
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					float sum = 0.0f;
					for (int k = 0; k < 4; k++)
					{
						sum += elements[j + k * 4] * other.elements[k + i * 4];
					}
					result[j + i * 4] = sum;
				}
			}
			memcpy(elements, result, 16 * sizeof(float));
			return *this;
		}

		Vector3 mat4::multiply(const Vector3& other) const
		{
			return Vector3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
			);
		}

		Vector4 mat4::multiply(const Vector4& other) const
		{
			return Vector4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			);
		}

		Vector3 operator*(const mat4& left, const Vector3& right)
		{
			return left.multiply(right);
		}

		Vector4 operator*(const mat4& left, const Vector4& right)
		{
			return left.multiply(right);
		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}


		mat4 mat4::orthographic(float left, float rigth, float bottom, float top, float near, float far)
		{
			mat4 result(1);

			result.elements[0] = 2.0f / (rigth - left);
			result.elements[5] = 2.0f / (top - bottom);
			result.elements[10] = 2.0f / (near - far);

			result.elements[12] = (left + rigth) / (left - rigth);
			result.elements[13] = (bottom + top) / (bottom - top);
			result.elements[14] = (far + near) / (far - near);

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1);

			float q = 1.0f / tan(toRadians(0.5f*fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f*near*far) / (near - far);

			result.elements[0] = a;
			result.elements[5] = q;
			result.elements[10] = b;
			result.elements[14] = c;
			result.elements[11] = -1.0f;

			return result;
		}

		mat4 mat4::translation(const Vector3& translation)
		{
			mat4 result(1);

			result.elements[12] = translation.x;
			result.elements[13] = translation.y;
			result.elements[14] = translation.z;

			return result;
		}

		mat4 mat4::rotation(const Vector3& axis, float angle)
		{
			mat4 result(1);

			float rad = toRadians(angle);
			float c = cos(rad);
			float s = sin(rad);
			float cc = 1 - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0] = x * x * cc + c;
			result.elements[1] = x * y * cc + z * s;
			result.elements[2] = x * z * cc - y * s;

			result.elements[4] = x * y * cc - z * s;
			result.elements[5] = y * y * cc + c;
			result.elements[6] = y * z * cc + x * c;

			result.elements[8] = x * z * cc + y * s;
			result.elements[9] = y * z * cc - x * s;
			result.elements[10] = z * z * cc + c;

			return result;
		}

		mat4 mat4::scale(const Vector3& scale)
		{
			mat4 result(1);

			result.elements[0] = scale.x;
			result.elements[5] = scale.y;
			result.elements[10] = scale.z;

			return result;
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& mat)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					stream << mat.elements[i + j * 4] << " ";
				stream << std::endl;
			}

			return stream;
		}
	}
}