﻿#pragma once

#include <stdexcept>

namespace Math_ias
{
	template <typename T>
	class Vector4
	{
		T _x;
		T _y;
		T _z;
		T _w;

	public:
		Vector4(T x, T y, T z, T w) : _x(x), _y(y), _z(z), _w(w)
		{
			
		}

		const T &operator[](size_t i)
		{
			if (i == 0) return _x;
			if (i == 1) return _y;
			if (i == 2) return _z;
			if (i == 3) return _w;

			throw std::out_of_range("Index out of bounds!");
		}

		T dot(Vector4<T>& other)
		{
			return _x*other._x + _y*other._y + _z*other._z + _w*other._w;
		}
	};

	typedef Vector4<float> Vector4f;
}