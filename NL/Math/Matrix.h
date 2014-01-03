#ifndef __NL_MATH_MATRIX_H__
#define __NL_MATH_MATRIX_H__

#include "Def.h"

class Matrix3x3
{
public:

	Matrix3x3(){ m[0] = m[1] = m[2] = Vector3(0,0,0); };

	Matrix3x3(Vector3 row1,Vector3 row2,Vector3 row3)
	{
		m[0] = row1;
		m[1] = row2;
		m[2] = row3;
	};

	Matrix3x3(float m11,float m12,float m13,
			  float m21,float m22,float m23,
		      float m31,float m32,float m33)
	{
		m[0] = Vector3(m11,m12,m13);
		m[1] = Vector3(m21,m22,m23);
		m[2] = Vector3(m31,m32,m33);
	};

	//--------------------------------------------------------------------------------------

	~Matrix3x3(){};

public:

	inline Matrix3x3 &Nil()
	{
		m[0] = Vector3(0,0,0);
		m[1] = Vector3(0,0,0);
		m[2] = Vector3(0,0,0);

		return *this;
	};

	inline Matrix3x3 &Identity()
	{
		m[0] = Vector3(1,0,0);
		m[1] = Vector3(0,1,0);
		m[2] = Vector3(0,0,1);

		return *this;
	};

	inline Matrix3x3 &Transpose() // Транспозиция
	{
		Vector3 tm[3];

		tm[0] = Vector3(m[0][0],m[1][0],m[2][0]);
		tm[1] = Vector3(m[0][1],m[1][1],m[2][1]);
		tm[2] = Vector3(m[0][2],m[1][2],m[2][2]);

		m[0] = tm[0];
		m[1] = tm[1];
		m[2] = tm[2];

		return *this;
	};

	//inline Matrix3x3 &Inverse() // Обращение

	//--------------------------------------------------------------------------------------

	//inline float &Determinant() const // Определитель

	//--------------------------------------------------------------------------------------

	inline Matrix3x3 &Scale(const Vector3 &s)
	{
		m[0] = Vector3(s.x,0,0);
		m[1] = Vector3(0,s.y,0);
		m[2] = Vector3(0,0,s.z);

		return *this;
	};

	inline Matrix3x3 &Scale(float x,float y,float z)
	{
		m[0] = Vector3(x,0,0);
		m[1] = Vector3(0,y,0);
		m[2] = Vector3(0,0,z);

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Matrix3x3 &RotateX(float x)
	{
		m[0] = Vector3(1,0,0);
		m[1] = Vector3(0,cosf(x),sinf(x));
		m[2] = Vector3(0,-sinf(x),cosf(x));

		return *this;
	};

	inline Matrix3x3 &RotateY(float y)
	{
		m[0] = Vector3(cosf(y),0,-sinf(y));
		m[1] = Vector3(0,1,0);
		m[2] = Vector3(sinf(y),0,cosf(y));

		return *this;
	};

	inline Matrix3x3 &RotateZ(float z)
	{
		m[0] = Vector3(cosf(z),sinf(z),0);
		m[1] = Vector3(-sinf(z),cosf(z),0);
		m[2] = Vector3(0,0,1);

		return *this;
	};

	//--------------------------------------------------------------------------------------

public:

	inline Vector3	 &operator []  (size_t row){ return m[row];	};

	inline Vector3	  operator []  (size_t row) const { return m[row]; };

public:

	//--------------------------------------------------------------------------------------

	inline Matrix3x3 &operator +=  (const Matrix3x3 &M)
	{
		for(int i = 0; i < 3; i++)
		{
			m[i] += M.m[i];
		}

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Matrix3x3  operator *	(float f)				const
	{
		return Matrix3x3(m[0]*f,m[1]*f,m[2]*f);
	};

	//--------------------------------------------------------------------------------------

	inline Matrix3x3  operator *	(const Matrix3x3 &M)	const
	{
		return Matrix3x3(m[0]*Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[0]*Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[0]*Vector3(M.m[0].z,M.m[1].z,M.m[2].z),
						 m[1]*Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[1]*Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[1]*Vector3(M.m[0].z,M.m[1].z,M.m[2].z),
						 m[2]*Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[2]*Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[2]*Vector3(M.m[0].z,M.m[1].z,M.m[2].z));
	};

	//--------------------------------------------------------------------------------------

	friend Vector3	  operator *	(const Vector3 &V,const Matrix3x3 &M);

private:

	Vector3 m[3];
};

class Matrix4x4
{
public:

	Matrix4x4(){ m[0] = m[1] = m[2] = m[3] = Vector4(0,0,0,0); };

	Matrix4x4(const Matrix4x4 &M)
	{
		m[0] = M.m[0];
		m[1] = M.m[1];
		m[2] = M.m[2];
		m[3] = M.m[3];
	};

	Matrix4x4(const Vector4 *rows)
	{
		m[0] = rows[0];
		m[1] = rows[1];
		m[2] = rows[2];
		m[3] = rows[3];
	};

	Matrix4x4(Vector4 row1,Vector4 row2,Vector4 row3,Vector4 row4)
	{
		m[0] = row1;
		m[1] = row2;
		m[2] = row3;
		m[3] = row4;
	};

	Matrix4x4(const float *m16)
	{
		memcpy(m,m16,16*sizeof(float));
	};

	Matrix4x4(float m11,float m12,float m13,float m14,
			  float m21,float m22,float m23,float m24,
			  float m31,float m32,float m33,float m34,
			  float m41,float m42,float m43,float m44)
	{
		m[0] = Vector4(m11,m12,m13,m14);
		m[1] = Vector4(m21,m22,m23,m24);
		m[2] = Vector4(m31,m32,m33,m34);
		m[3] = Vector4(m41,m42,m43,m44);
	};

	//--------------------------------------------------------------------------------------

	~Matrix4x4(){};

public:

	inline Matrix4x4 &Nil()
	{
		m[0] = Vector4(0,0,0,0);
		m[1] = Vector4(0,0,0,0);
		m[2] = Vector4(0,0,0,0);
		m[3] = Vector4(0,0,0,0);

		return *this;
	};

	inline Matrix4x4 &Identity()
	{
		m[0] = Vector4(1,0,0,0);
		m[1] = Vector4(0,1,0,0);
		m[2] = Vector4(0,0,1,0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	inline Matrix4x4 &Transpose()
	{
		Vector4 tm[4];

		tm[0] = Vector4(m[0][0],m[1][0],m[2][0],m[3][0]);
		tm[1] = Vector4(m[0][1],m[1][1],m[2][1],m[3][1]);
		tm[2] = Vector4(m[0][2],m[1][2],m[2][2],m[3][2]);
		tm[3] = Vector4(m[0][3],m[1][3],m[2][3],m[3][3]);

		m[0] = tm[0];
		m[1] = tm[1];
		m[2] = tm[2];
		m[3] = tm[3];

		return *this;
	};

	//inline Matrix4x4 &Inverse()

	//--------------------------------------------------------------------------------------

	//inline float &Determinant() const // Определитель

	//--------------------------------------------------------------------------------------
	
	inline Matrix4x4 &Translate(const Vector3 &t)
	{
		m[0] = Vector4(1,0,0,0);
		m[1] = Vector4(0,1,0,0);
		m[2] = Vector4(0,0,1,0);
		m[3] = Vector4(t,1);

		return *this;
	};

	inline Matrix4x4 &Translate(float x,float y,float z)
	{
		m[0] = Vector4(1,0,0,0);
		m[1] = Vector4(0,1,0,0);
		m[2] = Vector4(0,0,1,0);
		m[3] = Vector4(x,y,z,1);

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Matrix4x4 &Scale(const Vector3 &s)
	{
		m[0] = Vector4(s.x,0,0,0);
		m[1] = Vector4(0,s.y,0,0);
		m[2] = Vector4(0,0,s.z,0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	inline Matrix4x4 &Scale(float x,float y,float z)
	{
		m[0] = Vector4(x,0,0,0);
		m[1] = Vector4(0,y,0,0);
		m[2] = Vector4(0,0,z,0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Matrix4x4 &RotateX(float x)
	{
		m[0] = Vector4(1,0,0,0);
		m[1] = Vector4(0,cosf(x),sinf(x),0);
		m[2] = Vector4(0,-sinf(x),cosf(x),0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	inline Matrix4x4 &RotateY(float y)
	{
		m[0] = Vector4(cosf(y),0,-sinf(y),0);
		m[1] = Vector4(0,1,0,0);
		m[2] = Vector4(sinf(y),0,cosf(y),0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	inline Matrix4x4 &RotateZ(float z)
	{
		m[0] = Vector4(cosf(z),sinf(z),0,0);
		m[1] = Vector4(-sinf(z),cosf(z),0,0);
		m[2] = Vector4(0,0,1,0);
		m[3] = Vector4(0,0,0,1);

		return *this;
	};

	//--------------------------------------------------------------------------------------


// 	Matrix4x4 &Rotate(const Vector3 &a);
// 	Matrix4x4 &Rotate(float x,float y,float z);

	//Matrix4x4 &Mirror(float x,float y,float z);

public:

	inline Vector4	  &operator []  (size_t row){ return m[row]; };

	inline Vector4	  operator []  (size_t row) const { return m[row]; };

public:

	//--------------------------------------------------------------------------------------

	inline Matrix4x4 &operator +=  (const Matrix4x4 &M)
	{
		for(int i = 0; i < 4; i++)
		{
			m[i] += M.m[i];
		}

		return *this;
	};

	inline Matrix4x4 &operator -=	(const Matrix4x4 &M)
	{
		for(int i = 0; i < 4; i++)
		{
			m[i] -= M.m[i];
		}

		return *this;
	};

	inline Matrix4x4 &operator /=	(float f)
	{
		for(int i = 0; i < 4; i++)
		{
			m[i] /= f;
		}

		return *this;
	};

	inline Matrix4x4 &operator *=	(float f)
	{
		for(int i = 0; i < 4; i++)
		{
			m[i] *= f;
		}

		return *this;
	};

	//--------------------------------------------------------------------------------------

	inline Matrix4x4 &operator *=	(const Matrix4x4 &M)
	{
		*this = Matrix4x4(m[0]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[0]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[0]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[0]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						  m[1]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[1]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[1]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[1]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						  m[2]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[2]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[2]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[2]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						  m[3]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[3]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[3]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[3]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w));

		return *this;
	};

	//--------------------------------------------------------------------------------------
	
	inline Matrix4x4  operator +	(const Matrix4x4 &M)	const
	{
		return Matrix4x4(m[0] + M.m[0],m[1] + M.m[1],m[2] + M.m[2],m[3] + M.m[3]);
	};

	inline Matrix4x4  operator -	(const Matrix4x4 &M)	const
	{
		return Matrix4x4(m[0] - M.m[0],m[1] - M.m[1],m[2] - M.m[2],m[3] - M.m[3]);
	};

	inline Matrix4x4  operator /	(float f)				const
	{
		return Matrix4x4(m[0]/f,m[1]/f,m[2]/f,m[3]/f);
	};

	inline Matrix4x4  operator *	(float f)				const
	{
		return Matrix4x4(m[0]*f,m[1]*f,m[2]*f,m[3]*f);
	};

	//--------------------------------------------------------------------------------------
	
	inline Matrix4x4  operator *	(const Matrix4x4 &M)	const
	{
		return Matrix4x4(m[0]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[0]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[0]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[0]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						 m[1]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[1]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[1]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[1]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						 m[2]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[2]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[2]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[2]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
						 m[3]*Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[3]*Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[3]*Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[3]*Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w));
	};

	//--------------------------------------------------------------------------------------
	
	inline bool	   operator ==	(const Matrix4x4 &M)	const
	{
		return (m[0] == M.m[0] && m[1] == M.m[1] && m[2] == M.m[2] && m[3] == M.m[3]);
	};

	inline bool	   operator !=	(const Matrix4x4 &M)	const
	{
		return (m[0] != M.m[0] || m[1] != M.m[1] || m[2] != M.m[2] || m[3] != M.m[3]);
	};

	//--------------------------------------------------------------------------------------

	friend Vector4 operator * (const Vector4 &V,const Matrix4x4 &M);

private:

	Vector4 m[4];

};

inline Matrix3x3 Transpose(const Matrix3x3 &M)
{
	return Matrix3x3( Vector3(M[0][0],M[1][0],M[2][0]),
					  Vector3(M[0][1],M[1][1],M[2][1]),
					  Vector3(M[0][2],M[1][2],M[2][2]) );
};

inline Matrix4x4 Transpose(const Matrix4x4 &M)
{
	return Matrix4x4( Vector4(M[0][0],M[1][0],M[2][0],M[3][0]),
					  Vector4(M[0][1],M[1][1],M[2][1],M[3][1]),
					  Vector4(M[0][2],M[1][2],M[2][2],M[3][2]),
					  Vector4(M[0][3],M[1][3],M[2][3],M[3][3]) );
};

#endif