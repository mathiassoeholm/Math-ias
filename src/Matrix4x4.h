#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include <string>
#include <sstream>

namespace Math_ias
{
    template <class T>
    class Matrix4x4
    {
		T _values[16];

		Matrix4x4() {}
    public:
		

		Matrix4x4(T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15, T n16)
		{
			_values[0] = n1; _values[1] = n2; _values[2] = n3;  _values[3] = n4;
			_values[4] = n5; _values[5] = n6; _values[6] = n7;  _values[7] = n8;
			_values[8] = n9; _values[9] = n10; _values[10] = n11;  _values[11] = n12;
			_values[12] = n13; _values[13] = n14; _values[14] = n15;  _values[15] = n16;
		}

		T get(int row, int column)
		{
			return _values[column + row * 4];
		}

		Vector4<T> getRow(int row)
		{
			return Vector4<T>(
				get(row, 0),
				get(row, 1),
				get(row, 2),
				get(row, 3));
		}

		Vector4<T> getColumn(int column)
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

		const std::string toString()
		{
			auto ss = std::stringstream();
			ss << _values[0] << ", " << _values[1] << ", " << _values[2] << ", " << _values[3] << endl;
			ss << _values[4] << ", " << _values[5] << ", " << _values[6] << ", " << _values[7] << endl;
			ss << _values[8] << ", " << _values[9] << ", " << _values[10] << ", " << _values[11] << endl;
			ss << _values[12] << ", " << _values[13] << ", " << _values[14] << ", " << _values[15] << endl;

			return ss.str();
		}

		static Matrix4x4<T> Matrix4x4::translation(const Vector3<T>& vector)
		{
			return Matrix4x4<T>(
				1, 0, 0, vector[0],
				0, 1, 0, vector[1],
				0, 0, 1, vector[2],
				0, 0, 0, 1
				);
		}

		Matrix4x4<T> Matrix4x4::operator*(Matrix4x4<T> &other)
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
    };
}
