#pragma once

#include <stdexcept>

namespace Math_ias
{
	template <class T>
	class Vector3
	{
		T _x;
		T _y;
		T _z;

	public:
		Vector3(T x, T y, T z) : _x(x), _y(y), _z(z)
		{
			
		}

		const T &operator[](int i)
		{
			if (i == 0) return _x;
			if (i == 1) return _y;
			if (i == 2) return _z;

			throw std::out_of_range("Index out of bounds!");
		}

		T dot(Vector3<T>& other)
		{
			return _x*other._x + _y*other._y + _z*other._z;
		}
	};
}