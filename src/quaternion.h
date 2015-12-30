#pragma once

#include "Vector3.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Matrix4x4.h"
#include <limits>

namespace Math_ias
{
    template<class T>
    class Quaternion
    {
		T _q[4];

		void renormalize()
		{
			T sqrLength = _q[0]*_q[0] + _q[1]*_q[1] + _q[2]*_q[2] + _q[3]*_q[3];

			if(abs(1 - sqrLength) < std::numeric_limits<T>().epsilon())
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

			renormalize();
		}

		Matrix4x4<T> getMatrix() const
		{
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
			
			result.renormalize();

			return result;
		}

		static Quaternion<T> slerp(const Quaternion<T>& start, const Quaternion<T>& end, T t)
		{
			T dot = start._q[0] * end._q[0] + start._q[1] * end._q[1] + start._q[2] * end._q[2] + start._q[3] * end._q[3];

			if(abs(dot) > 1.0 - std::numeric_limits<T>().epsilon())
			{
				return start;
			}

			T sinOmega = sqrt(1 - dot * dot);

			Quaternion<T> result;

			// If angle is 180, do linear interpolation
			if(abs(sinOmega) < std::numeric_limits<T>().epsilon())
			{
				for (auto i = 0; i < 4; i++)
				{
					result._q[i] = (1 - t) * start._q[i] + t * end._q[i];
				}

				return result;
			}

			T omega = acos(dot);
			T a = sin((1 - t) * omega) / sinOmega;
			T b = sin(t*omega) / sinOmega;

			for (auto i = 0; i < 4; i++)
			{
				result._q[i] = start._q[i] * a + end._q[i] * b;
			}

			return result;
		}
    };

	typedef Quaternion<float> Quaternionf;
}
