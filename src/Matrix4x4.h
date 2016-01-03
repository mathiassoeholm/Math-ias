#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include <sstream>
#include <cmath>

namespace Math_ias
{
    template <typename T>
    class Matrix4x4
    {
		T _values[16];
		
    public:
		Matrix4x4()
		{
			_values[0] = 1; _values[1] = 0; _values[2] = 0;  _values[3] = 0;
			_values[4] = 0; _values[5] = 1; _values[6] = 0;  _values[7] = 0;
			_values[8] = 0; _values[9] = 0; _values[10] = 1;  _values[11] = 0;
			_values[12] = 0; _values[13] = 0; _values[14] = 0;  _values[15] = 1;
		}

		Matrix4x4(T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15, T n16)
		{
			_values[0] = n1; _values[1] = n2; _values[2] = n3;  _values[3] = n4;
			_values[4] = n5; _values[5] = n6; _values[6] = n7;  _values[7] = n8;
			_values[8] = n9; _values[9] = n10; _values[10] = n11;  _values[11] = n12;
			_values[12] = n13; _values[13] = n14; _values[14] = n15;  _values[15] = n16;
		}

		T get(int row, int column) const
		{
			return _values[column + row * 4];
		}

		Vector4<T> getRow(int row) const
		{
			return Vector4<T>(
				get(row, 0),
				get(row, 1),
				get(row, 2),
				get(row, 3));
		}

		Vector4<T> getColumn(int column) const
		{
			return Vector4<T>(
				get(0, column),
				get(1, column),
				get(2, column),
				get(3, column));
		}

		Matrix4x4<T> transposed()
		{
			return Matrix4x4(
				_values[0], _values[4], _values[8], _values[12],
				_values[1], _values[5], _values[9], _values[13],
				_values[2], _values[6], _values[10], _values[14],
				_values[3], _values[7], _values[11], _values[15]
				);
		}

		T* valuePtr()
		{
			return _values;
		}

	    std::string toString() const
		{
			auto ss = std::stringstream();
			ss << _values[0] << ", " << _values[1] << ", " << _values[2] << ", " << _values[3] << std::endl;
			ss << _values[4] << ", " << _values[5] << ", " << _values[6] << ", " << _values[7] << std::endl;
			ss << _values[8] << ", " << _values[9] << ", " << _values[10] << ", " << _values[11] << std::endl;
			ss << _values[12] << ", " << _values[13] << ", " << _values[14] << ", " << _values[15] << std::endl;

			return ss.str();
		}

		static Matrix4x4<T> translation(const Vector3<T>& vector)
		{
			return Matrix4x4<T>(
				1, 0, 0, vector[0],
				0, 1, 0, vector[1],
				0, 0, 1, vector[2],
				0, 0, 0, 1
				);
		}

		static Matrix4x4<T> translation(const T& x, const T& y, const T& z)
		{
			return Matrix4x4<T>(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1
				);
		}

		static Matrix4x4<T> rotationX(const T& theta)
		{
			return Matrix4x4<T>(
				1, 0, 0, 0,
				0, cos(theta), -sin(theta), 0,
				0, sin(theta), cos(theta), 0,
				0, 0, 0, 1
				);
		}

		static Matrix4x4<T> rotationY(const T& theta)
		{
			return Matrix4x4<T>(
				cos(theta), 0, sin(theta), 0,
				0, 1, 0, 0,
				-sin(theta), 0, cos(theta), 0,
				0, 0, 0, 1
				);
		}

		static Matrix4x4<T> rotationZ(const T& theta)
		{
			return Matrix4x4<T>(
				cos(theta), -sin(theta), 0, 0,
				sin(theta), cos(theta), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		Matrix4x4<T> operator*(const Matrix4x4<T> &other) const
		{
			Matrix4x4<T> result = Matrix4x4<T>();

			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					auto row = getRow(r);
					auto column = other.getColumn(c);

					result._values[c + r * 4] = row.dot(column);
				}
			}

			return result;
		}

		Vector4<T> operator*(const Vector4<T> &vector) const
		{
			T values[4];

			for (int r = 0; r < 4; r++)
			{
				auto row = getRow(r);
				values[r] = row.dot(vector);
			}

			return Vector4<T>(values[0], values[1], values[2], values[3]);
		}
    };

	typedef Matrix4x4<float> Matrix4x4f;
}
