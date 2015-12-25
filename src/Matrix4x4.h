#pragma once

namespace Math_ias
{
    template <class T>
    class Matrix4x4
    {
		T _values[16];

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

		Matrix4x4<T> transposed()
		{
			return Matrix4x4(
				_values[0], _values[4], _values[8], _values[12],
				_values[1], _values[5], _values[9], _values[13],
				_values[2], _values[6], _values[10], _values[14],
				_values[3], _values[7], _values[11], _values[15]
				);
		}
    };
}
