#ifndef __NL_MATH_H__
#define __NL_MATH_H__

#include <math.h>

#include "Common.h"

//Математические расширения

namespace NL
{	

	namespace Math
	{

		//Математически константы

		#define PI		3.1415926535897932384626433832795f

		#ifdef EPSILON
		#undef EPSILON
		#endif
		#define EPSILON 0.001f

		class Matrix3x3;
		class Matrix4x4;
		class Quaternion;

		class Vector2
		{
		public:

			Vector2(){};
			Vector2(float X,float Y){};

			~Vector2(){};

			float x,y;
		};

		class Vector3
		{
		public:

			Vector3();
			Vector3(float xyz);
			Vector3(const Vector3 &v);
			Vector3(float X,float Y,float Z);

			~Vector3();

		public:

			float	 Length()		const;
			Vector3  Normalize()	const;

		public:

			float	 &operator []	(size_t n);

		public:

			Vector3   &operator +=	(const Vector3 &v);
			Vector3   &operator -=	(const Vector3 &v);
			Vector3   &operator /=	(float f);
			Vector3   &operator *=	(float f);

		public:

			Vector3   &operator *=	(const Matrix4x4 &M);
			Vector3   &operator *=	(const Quaternion &Q);

		public:

			Vector3	   operator -	()						const;

			Vector3    operator +	(const Vector3 &v)		const;
			Vector3    operator -	(const Vector3 &v)		const;
			Vector3    operator /	(float f)				const;
			Vector3	   operator *	(float f)				const;

			float	   operator ^	(const Vector3 &v)		const; // Скалярное произведение

			Vector3	   operator %	(const Vector3 &v)		const; // Векторное произведение

			bool	   operator ==	(const Vector3 &v)		const;
			bool	   operator !=	(const Vector3 &v)		const;

		public:

			Vector3    operator *	(const Matrix3x3 &M)	const;
			Vector3    operator *	(const Matrix4x4 &M)	const;
			Vector3    operator *	(const Quaternion &Q)	const;

		public:

			float x,y,z;

		};

		class Vector4
		{
		public:

			Vector4();
			Vector4(float xyzw);
			Vector4(const Vector4 &v);
			Vector4(const Vector3 &v,float W);
			Vector4(float X,float Y,float Z,float W);

			~Vector4();

		public:

			float	 Length()		const;
			Vector4  Normalize()	const;

		public:

			float	  &operator [] (size_t n);

		public:

			Vector4   &operator +=	(const Vector4 &v);
			Vector4   &operator -=	(const Vector4 &v);
			Vector4   &operator /=	(float f);
			Vector4   &operator *=	(float f);

		public:

			Vector4   &operator *=	(const Matrix4x4 &M);
			Vector4   &operator *=	(const Quaternion &Q);

		public:

			Vector4	   operator -	()						const;

			Vector4    operator +	(const Vector4 &v)		const;
			Vector4    operator -	(const Vector4 &v)		const;
			Vector4    operator /	(float f)				const;
			Vector4	   operator *	(float f)				const;

			float	   operator ^	(const Vector4 &v)		const; // Скалярное произведение

			bool	   operator ==	(const Vector4 &v)		const;
			bool	   operator !=	(const Vector4 &v)		const;

		public:

			Vector4    operator *	(const Matrix4x4 &M)	const;
			Vector4    operator *	(const Quaternion &Q)	const;

		public:

			float x,y,z,w;

		};

		class Matrix3x3
		{
		public:

			Matrix3x3();
			Matrix3x3(Vector3 row1,Vector3 row2,Vector3 row3);
			Matrix3x3(float m11,float m12,float m13,
					  float m21,float m22,float m23,
					  float m31,float m32,float m33);

			~Matrix3x3();

		public:

			Matrix3x3 &Nil();

		public:

			Vector3	  &operator []  (size_t row);

		public:

			friend class Vector3;

			Matrix3x3 &operator +=  (const Matrix3x3 &M);

			Matrix3x3  operator *	(float f)				const;

			Matrix3x3  operator *	(const Matrix3x3 &M)	const;

		private:

			Vector3 m[3];
		};

		class Matrix4x4
		{
		public:

			Matrix4x4();
			Matrix4x4(const Matrix4x4 &M);
			Matrix4x4(const Vector4 *rows);
			Matrix4x4(Vector4 row1,Vector4 row2,Vector4 row3,Vector4 row4);
			Matrix4x4(const float *m16);
			Matrix4x4(float m11,float m12,float m13,float m14,
					  float m21,float m22,float m23,float m24,
					  float m31,float m32,float m33,float m34,
					  float m41,float m42,float m43,float m44);

			~Matrix4x4();

		public:

			Matrix4x4 &Identity();
			Matrix4x4 &Nil();
			Matrix4x4 &Transpose();
			Matrix4x4 &Inverse();

			Matrix4x4 &Translate(const Vector3 &t);
			Matrix4x4 &Translate(float x,float y,float z);

			Matrix4x4 &Scale(const Vector3 &s);
			Matrix4x4 &Scale(float x,float y,float z);

			Matrix4x4 &RotateX(float x);
			Matrix4x4 &RotateY(float y);
			Matrix4x4 &RotateZ(float z);
	
			Matrix4x4 &Rotate(const Vector3 &a);
			Matrix4x4 &Rotate(float x,float y,float z);

			//Matrix4x4 &Mirror(float x,float y,float z);

			float Determinant()		const;

		public:

			Vector4	  &operator []  (size_t row);
	
			Vector4   &operator ()  (size_t row);
			float	  &operator ()  (size_t row,size_t col);

		public:

			friend class Vector3;
			friend class Vector4;

			Matrix4x4 &operator +=  (const Matrix4x4 &M);
			Matrix4x4 &operator -=	(const Matrix4x4 &M);
			Matrix4x4 &operator /=	(float f);
			Matrix4x4 &operator *=	(float f);

			Matrix4x4 &operator *=	(const Matrix4x4 &M);

			Matrix4x4  operator +	(const Matrix4x4 &M)	const;
			Matrix4x4  operator -	(const Matrix4x4 &M)	const;
			Matrix4x4  operator /	(float f)				const;
			Matrix4x4  operator *	(float f)				const;

			Matrix4x4  operator *	(const Matrix4x4 &M)	const;

			bool	   operator ==	(const Matrix4x4 &M)	const;
			bool	   operator !=	(const Matrix4x4 &M)	const;

		private:

			Vector4 m[4];

		};

		class Quaternion
		{
		public:

			Quaternion();
			Quaternion(const Quaternion &q);
			Quaternion(const Vector3 &V,float W);
			Quaternion(float X,float Y,float Z,float W);

			~Quaternion();

		public:

			float Norm()			const;
			
			Quaternion &Normalize();

			Quaternion &RotateX(float x);
			Quaternion &RotateY(float y);
			Quaternion &RotateZ(float z);

		public:

			Matrix3x3 ToMatrix3x3()	const;
			Matrix4x4 ToMatrix4x4()	const;

		public:

			friend class Vector3;
			friend class Vector4;

			Quaternion	&operator	/=	(float f);
			Quaternion	&operator	*=	(float f);

			Quaternion	&operator	*=	(const Quaternion &q);

			Quaternion	 operator	/	(float f)				const;
			Quaternion	 operator	*	(float f)				const;

			Quaternion	 operator	*	(const Quaternion &q)	const;

			float		 operator	^	(const Quaternion &q)	const; // Скалярное произведение

			Quaternion	 operator	~	()						const;
			Quaternion	 operator	!	()						const;

		public:

			GET_ACCESSOR(Vector3,v);
			GET_ACCESSOR(float,w);

		private:

			Vector3 v;
			float w;

		};

	}

};

#endif