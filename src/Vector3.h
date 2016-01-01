#pragma once

#include <stdexcept>

namespace Math_ias
{
	template<typename T>
	class Vector3
	{
		T _x;
		T _y;
		T _z;

	public:
		Vector3(T x, T y, T z) : _x(x), _y(y), _z(z)
		{
			
		}

		const T &operator[](size_t i) const
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

		Vector3<T> operator-(const Vector3<T> &other) const
		{
			Vector3<T> result = Vector3<T>(
				_x - other._x,
				_y - other._y,
				_z - other._z);

			return result;
		}

		Vector3<T> operator-() const
		{
			Vector3<T> result = Vector3<T>(-_x, -_y, -_z);

			return result;
		}

		Vector3<T> operator+(const Vector3<T> &other) const
		{
			return Vector3<T>(
				_x + other._x,
				_y + other._y,
				_z + other._z);
		}

		

		Vector3<T> operator*(T scalar) const
		{
			return Vector3<T>(
				_x * scalar,
				_y * scalar,
				_z * scalar);
		}

		static Vector3<T> right()
		{
			return Vector3<T>(1, 0, 0);
		}

		static Vector3<T> up()
		{
			return Vector3<T>(0, 1, 0);
		}

		static Vector3<T> forward()
		{
			return Vector3<T>(0, 0, 1);
		}
	};

	typedef Vector3<float> Vector3f;
}

