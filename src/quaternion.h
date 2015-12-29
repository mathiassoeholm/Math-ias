#pragma once

#include "Vector3.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix4x4.h"

namespace Math_ias
{
    template<class T>
    class Quaternion
    {
		T _q[4];

		void renormalize()
		{
			T sqrLength = _q[0]*_q[0] + _q[1]*_q[1] + _q[2]*_q[2] + _q[3]*_q[3];

			if(abs(1 - sqrLength) < 0.00001)
			{
				return;
			}

			T length = sqrt(sqrLength);

			_q[0] = _q[0] / length;
			_q[1] = _q[1] / length;
			_q[2] = _q[2] / length;
			_q[3] = _q[3] / length;
		}

		Quaternion(){}
    public:
		Quaternion(T angle, const Vector3<T>& vec) : Quaternion(angle, vec[0], vec[1], vec[2]){}

		Quaternion(T angle, const T& x, const T& y, const T& z)
		{
			T radians = angle * (static_cast<T>(M_PI) / 180);

			_q[0] = cos(radians / 2);
			_q[1] = sin(radians / 2)*x;
			_q[2] = sin(radians / 2)*y;
			_q[3] = sin(radians / 2)*z;
		}

		Matrix4x4<T> getMatrix()
		{
			renormalize();

			return Matrix4x4<T>(
				1 - 2*_q[2]*_q[2] - 2*_q[3]*_q[3], 2*_q[1]*_q[2] - 2*_q[0]*_q[3], 2*_q[1]*_q[3] + 2*_q[0]*_q[2], 0,
				2*_q[1]*_q[2] + 2*_q[0]*_q[3], 1 - 2*_q[1]*_q[1] - 2*_q[3]*_q[3], 2*_q[2]*_q[3] - 2*_q[0]*_q[1], 0,
				2*_q[1]*_q[3] - 2*_q[0]*_q[2], 2*_q[2]*_q[3] + 2*_q[0]*_q[1], 1 - 2*_q[1]*_q[1] - 2*_q[2]*_q[2], 0,
				0, 0, 0, 1
				);
		}

		std::string toString() const
		{
			auto ss = std::stringstream();
			ss << "(" << _q[0] << ", " << _q[1] << ", " << _q[2] << ", " << _q[3] << ")" << std::endl;

			return ss.str();
		}

		Quaternion<T> Quaternion::operator*(const Quaternion<T> &other) const
		{
			Quaternion<T> result = Quaternion<T>();

			result._q[0] = other._q[0] * _q[0] - other._q[1] * _q[1] - other._q[2] * _q[2] - other._q[3] * _q[3];
			result._q[1] = other._q[0] * _q[1] + other._q[1] * _q[0] - other._q[2] * _q[3] + other._q[3] * _q[2];
			result._q[2] = other._q[0] * _q[2] + other._q[1] * _q[3] + other._q[2] * _q[0] - other._q[3] * _q[1];
			result._q[3] = other._q[0] * _q[3] - other._q[1] * _q[2] + other._q[2] * _q[1] + other._q[3] * _q[0];
			
			return result;
		}
    };
}
