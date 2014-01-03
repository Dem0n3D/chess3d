#ifndef __NL_MATH_VECTOR_H__
#define __NL_MATH_VECTOR_H__

#include "Def.h"

class Vector2
{
public:

	Vector2(){};
	Vector2(float X,float Y){};

	~Vector2(){};

public:

	float x,y;
};

class Vector3
{
public:

	Vector3(){ x = y = z = 0; };

	Vector3(float xyz){ x = y = z = xyz; };

	Vector3(const Vector3 &v)
	{	
		x = v.x;
		y = v.y;
		z = v.z;
	};

	Vector3(float X,float Y,float Z)
	{
		x = X;
		y = Y;
		z = Z;
	};

	//--------------------------------------------------------------------------------------

	~Vector3(){};

public:

	//--------------------------------------------------------------------------------------

	inline float	 Norm()	const // Длина (норма) вектора
	{
		return sqrtf(x*x + y*y + z*z);
	};

	inline Vector3  Normalize() const
	{
		float len = Norm();
		return Vector3(x/len,y/len,z/len);
	};

	//--------------------------------------------------------------------------------------

public:

	inline float	 &operator []	(size_t n){ return *((float *)this+n); };

	inline float	  operator []	(size_t n) const { return *((float *)this+n); };

public:

	//--------------------------------------------------------------------------------------

	inline Vector3   &operator +=	(const Vector3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	};

	inline Vector3   &operator -=	(const Vector3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	};

	inline Vector3   &operator /=	(float f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	};

	inline Vector3   &operator *=	(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Vector3   &operator *=	(const Matrix3x3 &M)
	{
		*this = *this * M;
		return *this;
	};

	inline Vector3   &operator *=	(const Quaternion &Q)
	{
		*this = *this * Q;
		return *this;
	};

	//--------------------------------------------------------------------------------------

public:

	//--------------------------------------------------------------------------------------

	inline Vector3	   operator -	()						const
	{
		return Vector3(-x,-y,-z);
	};

	//--------------------------------------------------------------------------------------

	inline Vector3    operator +	(const Vector3 &v)		const
	{
		return Vector3(x + v.x,y + v.y,z + v.z);
	};

	inline Vector3    operator -	(const Vector3 &v)		const
	{
		return Vector3(x - v.x,y - v.y,z - v.z);
	};

	inline Vector3    operator /	(float f)				const
	{
		return Vector3(x/f,y/f,z/f);
	};

	inline Vector3	  operator *	(float f)				const
	{
		return Vector3(x*f,y*f,z*f);
	};

	//--------------------------------------------------------------------------------------

	inline float	  operator *	(const Vector3 &v)		const // Скалярное произведение
	{
		return x*v.x + y*v.y + z*v.z;
	};

	inline Vector3	  operator %	(const Vector3 &v)		const // Векторное произведение
	{
		return Vector3(y*v.z - z*v.y,z*v.x - x*v.z,x*v.y - y*v.x);
	};

	//--------------------------------------------------------------------------------------

	friend Vector3	  operator *	(const Vector3 &V,const Matrix3x3  &M);
	friend Vector3    operator *	(const Vector3 &V,const Quaternion &Q);

	//--------------------------------------------------------------------------------------

	inline bool	   operator ==	(const Vector3 &v)		const
	{
		return (fabs(x - v.x) < EPSILON ? true : false) && (fabs(y - v.y) < EPSILON ? true : false) && (fabs(z - v.z) < EPSILON ? true : false);
	};

	inline bool	   operator !=	(const Vector3 &v)		const
	{
		return (fabs(x - v.x) > EPSILON ? true : false) || (fabs(y - v.y) > EPSILON ? true : false) || (fabs(z - v.z) > EPSILON ? true : false);
	};

	//--------------------------------------------------------------------------------------	

public:

	float x,y,z;

};

		
class Vector4
{
public:
	
	Vector4(){ x = y = z = w = 0; };

	Vector4(float xyzw){ x = y = z = w = xyzw; };

	Vector4(const Vector4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	};

	Vector4(const Vector3 &v,float W)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = W;
	};

	Vector4(float X,float Y,float Z,float W)
	{
		x=X;
		y=Y;
		z=Z;
		w=W;
	};

	//--------------------------------------------------------------------------------------

	~Vector4(){};
	
public:

	//--------------------------------------------------------------------------------------
	
	inline float	 Norm()	const
	{
		return sqrtf(x*x + y*y + z*z + w*w);
	};

	inline Vector4  Normalize() const
	{
		float len = Norm();
		return Vector4(x/len,y/len,z/len,w/len);
	};

	//--------------------------------------------------------------------------------------

public:
	
	inline float	  &operator [] (size_t n){ return *((float *)this+n); };

	inline float	   operator [] (size_t n) const { return *((float *)this+n); };

public:

	//--------------------------------------------------------------------------------------

	inline Vector4   &operator +=	(const Vector4 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	};

	inline Vector4   &operator -=	(const Vector4 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	};

	inline Vector4   &operator /=	(float f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;

		return *this;
	};

	inline Vector4   &operator *=	(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;

		return *this;
	};

	//--------------------------------------------------------------------------------------
	
	inline Vector4   &operator *=	(const Matrix4x4 &M)
	{
		*this = *this * M;

		return *this;
	};

	inline Vector4   &operator *=	(const Quaternion &Q)
	{
		*this = *this * Q;

		return *this;
	};

	//--------------------------------------------------------------------------------------

public:
	
	inline Vector4	  operator -	()						const
	{
		return Vector4(-x,-y,-z,-w);
	};

	inline Vector4    operator +	(const Vector4 &v)		const
	{
		return Vector4(x + v.x,y + v.y,z + v.z,w + v.w);
	};

	inline Vector4    operator -	(const Vector4 &v)		const
	{
		return Vector4(x - v.x,y - v.y,z - v.z,w - v.w);
	};

	inline Vector4    operator /	(float f)				const
	{
		return Vector4(x/f,y/f,z/f,w/f);
	};

	inline Vector4	  operator *	(float f)				const
	{
		return Vector4(x*f,y*f,z*f,w*f);
	};

	//--------------------------------------------------------------------------------------
	
	inline float	  operator *	(const Vector4 &v)		const // Скалярное произведение
	{
		return x*v.x + y*v.y + z*v.z + w*v.w;
	};	

	//--------------------------------------------------------------------------------------

	friend Vector4 operator * (const Vector4 &V,const Matrix4x4  &M);
	friend Vector4 operator * (const Vector4 &V,const Quaternion &Q);

	//--------------------------------------------------------------------------------------
	
	inline bool		  operator ==	(const Vector4 &v)		const
	{
		return (fabs(x - v.x) < EPSILON ? true : false) && (fabs(y - v.y) < EPSILON ? true : false) && (fabs(z - v.z) < EPSILON ? true : false) && (fabs(w - v.w) < EPSILON ? true : false);
	};

	inline bool		  operator !=	(const Vector4 &v)		const
	{
		return (fabs(x - v.x) > EPSILON ? true : false) || (fabs(y - v.y) > EPSILON ? true : false) || (fabs(z - v.z) > EPSILON ? true : false) || (fabs(w - v.w) > EPSILON ? true : false);
	};

	//--------------------------------------------------------------------------------------
	
public:

	float x,y,z,w;
	
};
	
#endif