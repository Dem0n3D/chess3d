#ifndef __NL_MATH_H__
#define __NL_MATH_H__

#include <math.h>

#include "../Common.h"

//Математические расширения

namespace NL
{	

	namespace Math
	{

		#include "Def.h"

		#include "Vector.h"
		#include "Matrix.h"
		#include "Quaternion.h"

		//--------------------------------------------------------------------------------------

		inline Vector3 operator *	(const Vector3 &V,const Matrix3x3 &M)
		{
			return Vector3(	V * Vector3(M.m[0].x,M.m[1].x,M.m[2].x),
							V * Vector3(M.m[0].y,M.m[1].y,M.m[2].y),
							V * Vector3(M.m[0].z,M.m[1].z,M.m[2].z) );
		};

		inline Vector4 operator *	(const Vector4 &V,const Matrix4x4 &M)
		{
			return Vector4(	V * Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),
							V * Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),
							V * Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),
							V * Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w) );
		};

		inline Vector3 operator *	(const Vector3 &V,const Quaternion &Q)
		{
			Vector4 v(V.x,V.y,V.z,0);
			v *= Q;
			return Vector3(v.x,v.y,v.z);
		};

		inline Vector4 operator *	(const Vector4 &V,const Quaternion &Q)
		{
			return Vector4((Q % Quaternion(V.x,V.y,V.z,0) % (~Q)).v,0);
		};

		//--------------------------------------------------------------------------------------

		inline Matrix3x3 QuaternionToMatrix3x3(const Quaternion &Q)
		{
			Matrix3x3 m;
			float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

			x2 = Q.v.x + Q.v.x;
			y2 = Q.v.y + Q.v.y;
			z2 = Q.v.z + Q.v.z;
			xx = Q.v.x * x2;  xy = Q.v.x * y2;  xz = Q.v.x * z2;
			yy = Q.v.y * y2;  yz = Q.v.y * z2;  zz = Q.v.z * z2;
			wx = Q.w	* x2;	wy = Q.w	* y2;	wz = Q.w	* z2;

			m[0][0]=1.0f-(yy+zz); m[0][1]=xy-wz;        m[0][2]=xz+wy;
			m[1][0]=xy+wz;        m[1][1]=1.0f-(xx+zz); m[1][2]=yz-wx;
			m[2][0]=xz-wy;        m[2][1]=yz+wx;        m[2][2]=1.0f-(xx+yy);

			return m;
		};

		//--------------------------------------------------------------------------------------

	}

};

#endif