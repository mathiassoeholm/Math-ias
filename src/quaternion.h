#pragma once

#include "Vector3.h"
#include <cmath>

namespace Math_ias
{
    template<class T>
    class Quaternion
    {
		T _q[4];
    public:
		Quaternion(T theta, const Vector3<T>& vec)
		{
			_q[0] = cos(theta/2);
			_q[1] = sin(theta/2)*vec[0];
			_q[2] = sin(theta/2)*vec[1];
			_q[3] = sin(theta/2)*vec[2];
		}
    };
}
