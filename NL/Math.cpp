#include "Math.h"

// Vector3

NL::Math::Vector3::Vector3()
{
	x = y = z = 0;
};

NL::Math::Vector3::Vector3(float xyz)
{
	x = y = z = xyz;
};

NL::Math::Vector3::Vector3(const Vector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
};

NL::Math::Vector3::Vector3(float X,float Y,float Z)
{
	x = X;
	y = Y;
	z = Z;
};


NL::Math::Vector3::~Vector3()
{
	 
};

float NL::Math::Vector3::Length() const
{
	return sqrtf(x*x + y*y + z*z);
};

NL::Math::Vector3 NL::Math::Vector3::Normalize() const
{
	float len = Length();
	return Vector3(x/len,y/len,z/len);
};

float &NL::Math::Vector3::operator [] (size_t n)
{
	return *((float *)this+n);
};

NL::Math::Vector3 &NL::Math::Vector3::operator += (const Vector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
};

NL::Math::Vector3 &NL::Math::Vector3::operator -= (const Vector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
};

NL::Math::Vector3 &NL::Math::Vector3::operator /= (float f)
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
};

NL::Math::Vector3 &NL::Math::Vector3::operator *= (float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
};

NL::Math::Vector3 &NL::Math::Vector3::operator *= (const Matrix4x4 &M)
{
	Vector4 v(x,y,z,0);
	v *= M;
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
};

NL::Math::Vector3 &NL::Math::Vector3::operator *= (const Quaternion &Q)
{
	Vector4 v(x,y,z,0);
	v *= Q;
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
};

NL::Math::Vector3 NL::Math::Vector3::operator - () const
{
	return Vector3(-x,-y,-z);
};

NL::Math::Vector3 NL::Math::Vector3::operator + (const Vector3 &v) const
{
	return Vector3(x + v.x,y + v.y,z + v.z);
};

NL::Math::Vector3 NL::Math::Vector3::operator - (const Vector3 &v) const
{
	return Vector3(x - v.x,y - v.y,z - v.z);
};

NL::Math::Vector3 NL::Math::Vector3::operator / (float f) const
{
	return Vector3(x/f,y/f,z/f);
};

NL::Math::Vector3 NL::Math::Vector3::operator * (float f) const
{
	return Vector3(x*f,y*f,z*f);
};

float NL::Math::Vector3::operator ^ (const Vector3 &v) const
{
	return x*v.x + y*v.y + z*v.z;
};

NL::Math::Vector3 NL::Math::Vector3::operator % (const Vector3 &v) const
{
	return Vector3(y*v.z - z*v.y,z*v.x - x*v.z,x*v.y - y*v.x);
};

bool NL::Math::Vector3::operator == (const Vector3 &v) const
{
	return (fabs(x - v.x) < EPSILON ? true : false) && (fabs(y - v.y) < EPSILON ? true : false) && (fabs(z - v.z) < EPSILON ? true : false);
};

bool NL::Math::Vector3::operator != (const Vector3 &v) const
{
	return (fabs(x - v.x) > EPSILON ? true : false) || (fabs(y - v.y) > EPSILON ? true : false) || (fabs(z - v.z) > EPSILON ? true : false);
};

NL::Math::Vector3 NL::Math::Vector3::operator *	(const Matrix3x3 &M) const
{
	return Vector3(	*this ^ Vector3(M.m[0].x,M.m[1].x,M.m[2].x),
					*this ^ Vector3(M.m[0].y,M.m[1].y,M.m[2].y),
					*this ^ Vector3(M.m[0].z,M.m[1].z,M.m[2].z)	);
};

NL::Math::Vector3 NL::Math::Vector3::operator *	(const Matrix4x4 &M) const
{
	Vector4 v(x,y,z,1);
	v *= M;
	return Vector3(v.x,v.y,v.z);
};

NL::Math::Vector3 NL::Math::Vector3::operator *	(const Quaternion &Q) const
{
	Vector4 v(x,y,z,0);
	v *= Q;
	return Vector3(v.x,v.y,v.z);
};

//////////////////////////////////////////////////////////////////////////
// Vector4

NL::Math::Vector4::Vector4()
{
	x = y = z = w = 0;
};

NL::Math::Vector4::Vector4(float xyzw)
{
	x = y = z = w = xyzw;
};

NL::Math::Vector4::Vector4(const Vector4 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
};

NL::Math::Vector4::Vector4(const Vector3 &v,float W)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = W;
};

NL::Math::Vector4::Vector4(float X,float Y,float Z,float W)
{
	x=X;
	y=Y;
	z=Z;
	w=W;
};

NL::Math::Vector4::~Vector4()
{

};

float NL::Math::Vector4::Length() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
};

NL::Math::Vector4 NL::Math::Vector4::Normalize() const
{
	float len = Length();
	return Vector4(x/len,y/len,z/len,w/len);
};

float &NL::Math::Vector4::operator [] (size_t n)
{
	return *((float *)this+n);
};

NL::Math::Vector4 &NL::Math::Vector4::operator += (const Vector4 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
};

NL::Math::Vector4 &NL::Math::Vector4::operator -= (const Vector4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
};

NL::Math::Vector4 &NL::Math::Vector4::operator /= (float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
};

NL::Math::Vector4 &NL::Math::Vector4::operator *= (float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
};

NL::Math::Vector4 &NL::Math::Vector4::operator *= (const NL::Math::Matrix4x4 &M)
{
	*this = Vector4(*this ^ Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),
					*this ^ Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),
					*this ^ Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),
					*this ^ Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w) );

	return *this;
};

NL::Math::Vector4 &NL::Math::Vector4::operator *= (const NL::Math::Quaternion &Q)
{
	*this = Vector4((Q * Quaternion(x,y,z,0) * (~Q)).v,0);

	return *this;
};

NL::Math::Vector4 NL::Math::Vector4::operator - () const
{
	return Vector4(-x,-y,-z,-w);
};

NL::Math::Vector4 NL::Math::Vector4::operator + (const Vector4 &v) const
{
	return Vector4(x + v.x,y + v.y,z + v.z,w + v.w);
};

NL::Math::Vector4 NL::Math::Vector4::operator - (const Vector4 &v) const
{
	return Vector4(x - v.x,y - v.y,z - v.z,w - v.w);
};

NL::Math::Vector4 NL::Math::Vector4::operator / (float f) const
{
	return Vector4(x/f,y/f,z/f,w/f);
};

NL::Math::Vector4 NL::Math::Vector4::operator * (float f) const
{
	return Vector4(x*f,y*f,z*f,w*f);
};

float NL::Math::Vector4::operator ^ (const Vector4 &v) const
{
	return x*v.x + y*v.y + z*v.z + w*v.w;
};

bool NL::Math::Vector4::operator == (const Vector4 &v) const
{
	return (fabs(x - v.x) < EPSILON ? true : false) && (fabs(y - v.y) < EPSILON ? true : false) && (fabs(z - v.z) < EPSILON ? true : false) && (fabs(w - v.w) < EPSILON ? true : false);
};

bool NL::Math::Vector4::operator != (const Vector4 &v) const
{
	return (fabs(x - v.x) > EPSILON ? true : false) || (fabs(y - v.y) > EPSILON ? true : false) || (fabs(z - v.z) > EPSILON ? true : false) || (fabs(w - v.w) > EPSILON ? true : false);
};

NL::Math::Vector4 NL::Math::Vector4::operator * (const Matrix4x4 &M) const
{
	return Vector4(*this ^ Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),
				   *this ^ Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),
				   *this ^ Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),
				   *this ^ Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w) );
};

NL::Math::Vector4 NL::Math::Vector4::operator * (const Quaternion &Q) const
{
	return Vector4((Q * Quaternion(x,y,z,0) * (~Q)).v,0);
};

//////////////////////////////////////////////////////////////////////////
// Matrix3x3

NL::Math::Matrix3x3::Matrix3x3()
{
	m[0] = m[1] = m[2] = Vector3(0,0,0);
};

NL::Math::Matrix3x3::Matrix3x3(Vector3 row1,Vector3 row2,Vector3 row3)
{
	m[0] = row1;
	m[1] = row2;
	m[2] = row3;
};

NL::Math::Matrix3x3::Matrix3x3(float m11,float m12,float m13,
							   float m21,float m22,float m23,
							   float m31,float m32,float m33)
{
	m[0] = Vector3(m11,m12,m13);
	m[1] = Vector3(m21,m22,m23);
	m[2] = Vector3(m31,m32,m33);
};

NL::Math::Matrix3x3::~Matrix3x3()
{
	
};

NL::Math::Matrix3x3 &NL::Math::Matrix3x3::Nil()
{
	m[0] = Vector3(0,0,0);
	m[1] = Vector3(0,0,0);
	m[2] = Vector3(0,0,0);

	return *this;
};

NL::Math::Vector3 &NL::Math::Matrix3x3::operator [] (size_t row)
{
	return m[row];
};

NL::Math::Matrix3x3 &NL::Math::Matrix3x3::operator += (const Matrix3x3 &M)
{
	for(int i = 0; i < 3; i++)
	{
		m[i] += M.m[i];
	}

	return *this;
};

NL::Math::Matrix3x3 NL::Math::Matrix3x3::operator * (float f) const
{
	return Matrix3x3(m[0]*f,m[1]*f,m[2]*f);
};

NL::Math::Matrix3x3 NL::Math::Matrix3x3::operator * (const Matrix3x3 &M) const
{
	return Matrix3x3(m[0]^Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[0]^Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[0]^Vector3(M.m[0].z,M.m[1].z,M.m[2].z),
					 m[1]^Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[1]^Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[1]^Vector3(M.m[0].z,M.m[1].z,M.m[2].z),
					 m[2]^Vector3(M.m[0].x,M.m[1].x,M.m[2].x),m[2]^Vector3(M.m[0].y,M.m[1].y,M.m[2].y),m[2]^Vector3(M.m[0].z,M.m[1].z,M.m[2].z));
};

//////////////////////////////////////////////////////////////////////////
// Matrix4x4

NL::Math::Matrix4x4::Matrix4x4()
{
	m[0] = m[1] = m[2] = m[3] = Vector4(0,0,0,0);
};

NL::Math::Matrix4x4::Matrix4x4(const Matrix4x4 &M)
{
	m[0] = M.m[0];
	m[1] = M.m[1];
	m[2] = M.m[2];
	m[3] = M.m[3];
};

NL::Math::Matrix4x4::Matrix4x4(const Vector4 *rows)
{
	m[0] = rows[0];
	m[1] = rows[1];
	m[2] = rows[2];
	m[3] = rows[3];
};

NL::Math::Matrix4x4::Matrix4x4(Vector4 row1,Vector4 row2,Vector4 row3,Vector4 row4)
{
	m[0] = row1;
	m[1] = row2;
	m[2] = row3;
	m[3] = row4;
};

NL::Math::Matrix4x4::Matrix4x4(const float *m16)
{
	memcpy(m,m16,16*sizeof(float));
};

NL::Math::Matrix4x4::Matrix4x4(float m11,float m12,float m13,float m14,
							   float m21,float m22,float m23,float m24,
							   float m31,float m32,float m33,float m34,
							   float m41,float m42,float m43,float m44)
{
	m[0] = Vector4(m11,m12,m13,m14);
	m[1] = Vector4(m21,m22,m23,m24);
	m[2] = Vector4(m31,m32,m33,m34);
	m[3] = Vector4(m41,m42,m43,m44);
};

NL::Math::Matrix4x4::~Matrix4x4()
{

};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Identity()
{
	m[0] = Vector4(1,0,0,0);
	m[1] = Vector4(0,1,0,0);
	m[2] = Vector4(0,0,1,0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Nil()
{
	m[0] = Vector4(0,0,0,0);
	m[1] = Vector4(0,0,0,0);
	m[2] = Vector4(0,0,0,0);
	m[3] = Vector4(0,0,0,0);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Transpose()
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

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Inverse()
{
	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Translate(const Vector3 &t)
{
	m[0] = Vector4(1,0,0,0);
	m[1] = Vector4(0,1,0,0);
	m[2] = Vector4(0,0,1,0);
	m[3] = Vector4(t,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Translate(float x,float y,float z)
{
	m[0] = Vector4(1,0,0,0);
	m[1] = Vector4(0,1,0,0);
	m[2] = Vector4(0,0,1,0);
	m[3] = Vector4(x,y,z,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Scale(const Vector3 &s)
{
	m[0] = Vector4(s.x,0,0,0);
	m[1] = Vector4(0,s.y,0,0);
	m[2] = Vector4(0,0,s.z,0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Scale(float x,float y,float z)
{
	m[0] = Vector4(x,0,0,0);
	m[1] = Vector4(0,y,0,0);
	m[2] = Vector4(0,0,z,0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::RotateX(float x)
{
	m[0] = Vector4(1,0,0,0);
	m[1] = Vector4(0,cosf(x),sinf(x),0);
	m[2] = Vector4(0,-sinf(x),cosf(x),0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::RotateY(float y)
{
	m[0] = Vector4(cosf(y),0,-sinf(y),0);
	m[1] = Vector4(0,1,0,0);
	m[2] = Vector4(sinf(y),0,cosf(y),0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::RotateZ(float z)
{
	m[0] = Vector4(cosf(z),sinf(z),0,0);
	m[1] = Vector4(-sinf(z),cosf(z),0,0);
	m[2] = Vector4(0,0,1,0);
	m[3] = Vector4(0,0,0,1);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Rotate(const Vector3 &a)
{
	Matrix4x4 X,Y,Z;

	*this = Y.RotateY(a.y) * X.RotateX(a.x) * Z.RotateZ(a.z);

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::Rotate(float x,float y,float z)
{
	return *this;
};

float NL::Math::Matrix4x4::Determinant() const
{
	return 0.0f;
};

/*NL::Math::Matrix4x4::operator float * ()
{
	return (float *)this;
};

NL::Math::Matrix4x4::operator const float * () const
{
	return (const float *)this;
};*/

NL::Math::Vector4 &NL::Math::Matrix4x4::operator [] (size_t row)
{
	return m[row];
};

NL::Math::Vector4 &NL::Math::Matrix4x4::operator () (size_t row)
{
	return m[row];
};

float &NL::Math::Matrix4x4::operator () (size_t row,size_t col)
{
	return m[row][col];
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::operator += (const Matrix4x4 &M)
{
	for(int i = 0; i < 4; i++)
	{
		m[i] += M.m[i];
	}

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::operator -= (const Matrix4x4 &M)
{
	for(int i = 0; i < 4; i++)
	{
		m[i] -= M.m[i];
	}

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::operator /= (float f)
{
	for(int i = 0; i < 4; i++)
	{
		m[i] /= f;
	}

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::operator *= (float f)
{
	for(int i = 0; i < 4; i++)
	{
		m[i] *= f;
	}

	return *this;
};

NL::Math::Matrix4x4 &NL::Math::Matrix4x4::operator *= (const Matrix4x4 &M)
{
	*this = Matrix4x4(m[0]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[0]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[0]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[0]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					  m[1]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[1]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[1]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[1]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					  m[2]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[2]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[2]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[2]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					  m[3]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[3]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[3]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[3]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w));

	return *this;
};

NL::Math::Matrix4x4 NL::Math::Matrix4x4::operator + (const Matrix4x4 &M) const
{
	return Matrix4x4(m[0] + M.m[0],m[1] + M.m[1],m[2] + M.m[2],m[3] + M.m[3]);
};

NL::Math::Matrix4x4 NL::Math::Matrix4x4::operator - (const Matrix4x4 &M) const
{
	return Matrix4x4(m[0] - M.m[0],m[1] - M.m[1],m[2] - M.m[2],m[3] - M.m[3]);
};

NL::Math::Matrix4x4 NL::Math::Matrix4x4::operator / (float f) const
{
	return Matrix4x4(m[0]/f,m[1]/f,m[2]/f,m[3]/f);
};

NL::Math::Matrix4x4 NL::Math::Matrix4x4::operator * (float f) const
{
	return Matrix4x4(m[0]*f,m[1]*f,m[2]*f,m[3]*f);
};

NL::Math::Matrix4x4 NL::Math::Matrix4x4::operator * (const Matrix4x4 &M) const
{
	return Matrix4x4(m[0]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[0]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[0]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[0]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					 m[1]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[1]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[1]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[1]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					 m[2]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[2]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[2]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[2]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w),
					 m[3]^Vector4(M.m[0].x,M.m[1].x,M.m[2].x,M.m[3].x),m[3]^Vector4(M.m[0].y,M.m[1].y,M.m[2].y,M.m[3].y),m[3]^Vector4(M.m[0].z,M.m[1].z,M.m[2].z,M.m[3].z),m[3]^Vector4(M.m[0].w,M.m[1].w,M.m[2].w,M.m[3].w));
};

bool NL::Math::Matrix4x4::operator == (const Matrix4x4 &M) const
{
	return (m[0] == M.m[0] && m[1] == M.m[1] && m[2] == M.m[2] && m[3] == M.m[3]);
};

bool NL::Math::Matrix4x4::operator != (const Matrix4x4 &M) const
{
	return (m[0] != M.m[0] || m[1] != M.m[1] || m[2] != M.m[2] || m[3] != M.m[3]);
};

//////////////////////////////////////////////////////////////////////////

NL::Math::Quaternion::Quaternion()
{
	v = Vector3(0,0,0);
	w = 0;
};

NL::Math::Quaternion::Quaternion(const Quaternion &q)
{
	v = q.v;
	w = q.w;
};

NL::Math::Quaternion::Quaternion(const Vector3 &V,float W)
{
	v = V;
	w = W;
};

NL::Math::Quaternion::Quaternion(float X,float Y,float Z,float W)
{
	v = Vector3(X,Y,Z);
	w = W;
};

NL::Math::Quaternion::~Quaternion()
{

};

float NL::Math::Quaternion::Norm() const // Magnitude
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + w*w);
};

NL::Math::Quaternion &NL::Math::Quaternion::Normalize()
{
	operator /= (Norm());

	return *this;
};

NL::Math::Quaternion &NL::Math::Quaternion::RotateX(float x)
{
	v = Vector3(1.0f,0.0f,0.0f) * sinf(0.5f * x);
	w = cosf(0.5f * x);
	Normalize();

	return *this;
};

NL::Math::Quaternion &NL::Math::Quaternion::RotateY(float y)
{
	v = Vector3(0.0f,1.0f,0.0f) * sinf(0.5f * y);
	w = cosf(0.5f * y);
	Normalize();

	return *this;
};

NL::Math::Quaternion &NL::Math::Quaternion::RotateZ(float z)
{
	v = Vector3(0.0f,0.0f,1.0f) * sinf(0.5f * z);
	w = cosf(0.5f * z);
	Normalize();

	return *this;
};

NL::Math::Matrix3x3 NL::Math::Quaternion::ToMatrix3x3()	const
{
	NL::Math::Matrix3x3 m;
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = v.x + v.x;
	y2 = v.y + v.y;
	z2 = v.z + v.z;
	xx = v.x * x2;  xy = v.x * y2;  xz = v.x * z2;
	yy = v.y * y2;  yz = v.y * z2;  zz = v.z * z2;
	wx = w	* x2;	wy = w	* y2;	wz = w	* z2;

	m[0][0]=1.0f-(yy+zz); m[0][1]=xy-wz;        m[0][2]=xz+wy;
	m[1][0]=xy+wz;        m[1][1]=1.0f-(xx+zz); m[1][2]=yz-wx;
	m[2][0]=xz-wy;        m[2][1]=yz+wx;        m[2][2]=1.0f-(xx+yy);

	return m;
};

NL::Math::Matrix4x4 NL::Math::Quaternion::ToMatrix4x4()	const
{
	NL::Math::Matrix4x4 m;
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = v.x + v.x;
	y2 = v.y + v.y;
	z2 = v.z + v.z;
	xx = v.x * x2;  xy = v.x * y2;  xz = v.x * z2;
	yy = v.y * y2;  yz = v.y * z2;  zz = v.z * z2;
	wx = w	* x2;	wy = w	* y2;	wz = w	* z2;

	m[0][0]=1.0f-(yy+zz); m[0][1]=xy-wz;        m[0][2]=xz+wy;
	m[1][0]=xy+wz;        m[1][1]=1.0f-(xx+zz); m[1][2]=yz-wx;
	m[2][0]=xz-wy;        m[2][1]=yz+wx;        m[2][2]=1.0f-(xx+yy);

	m[0][3] = m[1][3] = m[2][3] = 0;
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;

	return m;
};

NL::Math::Quaternion &NL::Math::Quaternion::operator /= (float f)
{
	v /= f;
	w /= f;

	return *this;
};

NL::Math::Quaternion &NL::Math::Quaternion::operator *= (float f)
{
	v *= f;
	w *= f;

	return *this;
};

NL::Math::Quaternion &NL::Math::Quaternion::operator *= (const Quaternion &q)
{
	v = Vector3(v*q.w + q.v*w + v%q.v);
	w = w*q.w - (v^q.v);

	return *this;
};

NL::Math::Quaternion NL::Math::Quaternion::operator * (float f) const
{
	return Quaternion(v*f,w*f);
};

NL::Math::Quaternion NL::Math::Quaternion::operator / (float f) const
{
	return Quaternion(v/f,w/f);
};


NL::Math::Quaternion NL::Math::Quaternion::operator * (const Quaternion &q) const
{
	return Quaternion(Vector3(v*q.w + q.v*w + v%q.v),w*q.w - (v^q.v));
};

float NL::Math::Quaternion::operator ^ (const Quaternion &q) const
{
	return (v^q.v)+w*q.w;
};


NL::Math::Quaternion NL::Math::Quaternion::operator ~ () const
{
	return Quaternion(-v,w);
};

NL::Math::Quaternion NL::Math::Quaternion::operator ! () const
{
	return (operator ~ () / Norm());
};