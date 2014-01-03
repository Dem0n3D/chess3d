#ifndef __NL_MATH_QUATERNION_H__
#define __NL_MATH_QUATERNION_H__

#include "../Common.h"

#include "Def.h"

class Quaternion
{
public:

	Quaternion()
	{
		v = Vector3(0,0,0);
		w = 0;
	};

	Quaternion(const Quaternion &q)
	{
		v = q.v;
		w = q.w;
	};

	Quaternion(const Vector3 &V,float W)
	{
		v = V;
		w = W;
	};

	Quaternion(float X,float Y,float Z,float W)
	{
		v = Vector3(X,Y,Z);
		w = W;
	};

	//--------------------------------------------------------------------------------------

	~Quaternion(){};

public:

	//--------------------------------------------------------------------------------------

	inline float Norm()			const // Magnitude (длина)
	{
		return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + w*w);
	};

	inline Quaternion &Normalize()
	{
		operator /= (Norm());

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Quaternion &RotateX(float x)
	{
		v = Vector3(1.0f,0.0f,0.0f) * sinf(0.5f * x);
		w = cosf(0.5f * x);
		Normalize();

		return *this;
	};

	inline Quaternion &RotateY(float y)
	{
		v = Vector3(0.0f,1.0f,0.0f) * sinf(0.5f * y);
		w = cosf(0.5f * y);
		Normalize();

		return *this;
	};

	inline Quaternion &RotateZ(float z)
	{
		v = Vector3(0.0f,0.0f,1.0f) * sinf(0.5f * z);
		w = cosf(0.5f * z);
		Normalize();

		return *this;
	};

	//--------------------------------------------------------------------------------------

// public:
// 
// 	Matrix3x3 ToMatrix3x3()	const;
// 	Matrix4x4 ToMatrix4x4()	const;

public:

// 	friend class Vector3;
// 	friend class Vector4;

	//--------------------------------------------------------------------------------------

	inline Quaternion	&operator	/=	(float f)
	{
		v /= f;
		w /= f;

		return *this;
	};

	inline Quaternion	&operator	*=	(float f)
	{
		v *= f;
		w *= f;

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Quaternion	&operator	*=	(const Quaternion &q)
	{
		v = Vector3(v*q.w + q.v*w + v%q.v);
		w = w*q.w - (v*q.v);

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Quaternion	 operator	/	(float f)				const
	{
		return Quaternion(v*f,w*f);
	};

	inline Quaternion	 operator	*	(float f)				const
	{
		return Quaternion(v/f,w/f);
	};

	//--------------------------------------------------------------------------------------

	inline Quaternion	 operator	%	(const Quaternion &q)	const
	{
		return Quaternion(Vector3(v*q.w + q.v*w + v%q.v),w*q.w - (v*q.v));
	};

	inline float		 operator	*	(const Quaternion &q)	const // —кал€рное произведение
	{
		return (v*q.v)+w*q.w;
	};

	//--------------------------------------------------------------------------------------

	inline Quaternion	 operator	~	()						const // Conjugate (сопр€жение)
	{
		return Quaternion(-v,w);
	};

	inline Quaternion	 operator	!	()						const // Inverse (обращение)
	{
		return (operator ~ () / Norm());
	};

	//--------------------------------------------------------------------------------------

	friend Vector3 operator *	(const Vector3 &V,const Quaternion &Q);
	friend Vector4 operator *	(const Vector4 &V,const Quaternion &Q);

// public:
// 
// 	GET_ACCESSOR(Vector3,v);
// 	GET_ACCESSOR(float,w);

public:

	Vector3 v;
	float w;

};

#endif