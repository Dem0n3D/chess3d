#include "QCamera.h"

using namespace NL::Math;

NL::Scene::QCamera::QCamera()
{
	r = Math::Vector3(1,0,0);
	u = Math::Vector3(0,1,0);
	d = Math::Vector3(0,0,1);	
	p = Math::Vector3(0,0,0);

	rot = Math::Vector3(0,0,0);
};

NL::Scene::QCamera::~QCamera()
{

};

void NL::Scene::QCamera::Rotate(float x,float y,float z)
{
	rot += Math::Vector3(x,y,z);

	rot.x = __min(rot.x,PI/2);
	rot.x = __max(rot.x,-PI/2);

	while(rot.y >= 2*PI)
		rot.y -= 2*PI; 

	while(rot.y <= -2*PI)
		rot.y += 2*PI; 
};

void NL::Scene::QCamera::Rotate(const NL::Math::Vector3 &v)
{
	Rotate(v.x,v.y,v.z);
};

void NL::Scene::QCamera::Move(float x,float y,float z)
{
	Move(Math::Vector3(x,y,z));
};

void NL::Scene::QCamera::Move(const NL::Math::Vector3 &v)
{
	p += v;
};

void NL::Scene::QCamera::Slide(float x,float y,float z)
{
	p += r*x + u*y + d*z;
};

void NL::Scene::QCamera::Slide(const NL::Math::Vector3 &v)
{
	Slide(v.x,v.y,v.z);
};

NL::Math::Matrix4x4 NL::Scene::QCamera::GetViewMatrix()
{
	Quaternion qx,qy;

	qx.RotateX(rot.x);
	qy.RotateY(rot.y);

	r = Math::Vector3(1,0,0)*qy;
	d = Math::Vector3(0,0,1)*(qx%qy);

	r.Normalize();
	d.Normalize();

	u = d%r;

	u.Normalize();

	return NL::Math::Matrix4x4(	r.x,	u.x,	-d.x,	0.0f,
								r.y,	u.y,	-d.y,	0.0f,
								r.z,	u.z,	-d.z,	0.0f,
								-(r*p), -(u*p), (d*p),	1.0f );
};

NL::Math::Matrix4x4 NL::Scene::QCamera::GetProjMatrix()
{
	Math::Matrix4x4 mProj;

	float sine, cotangent, deltaZ;
	float radians = fovy / 2.0f * PI / 180.0f;

	deltaZ = zf - zn;
	sine = sin(radians);
	/* Should be non-zero to avoid division by zero. */
	
	cotangent = cos(radians) / sine;

	mProj[0][0] = cotangent / aspect;
	mProj[1][0] = 0.0f;
	mProj[2][0] = 0.0f;
	mProj[3][0] = 0.0f;

	mProj[0][1] = 0.0f;
	mProj[1][1] = cotangent;
	mProj[2][1] = 0.0f;
	mProj[3][1] = 0.0f;

	mProj[0][2] = 0.0f;
	mProj[1][2] = 0.0f;
	mProj[2][2] = -(zf + zn) / deltaZ;
	mProj[3][2] = -2 * zn * zf / deltaZ;

	mProj[0][3] = 0.0f;
	mProj[1][3] = 0.0f;
	mProj[2][3] = -1.0f;
	mProj[3][3] = 0.0f;

	return mProj;
};

void NL::Scene::QCamera::Callback(WORD mt,std::vector<DWORD> param)
{
	switch(mt)
	{
	case EVENT_KEY_DOWN:
		{
			switch(param[0])
			{
			case BUTTON_DOWN:
				{
					Slide(Math::Vector3(0,0,-2));
					break;
				}
			case BUTTON_UP:
				{
					Slide(Math::Vector3(0,0,2));
					break;
				}
			case BUTTON_RIGHT:
				{
					Slide(Math::Vector3(2,0,0));
					break;
				}
			case BUTTON_LEFT:
				{
					Slide(Math::Vector3(-2,0,0));
					break;
				}
			case BUTTON_PAGE_UP:
				{
					Slide(Math::Vector3(0,2,0));
					break;
				}
			case BUTTON_PAGE_DOWN:
				{
					Slide(Math::Vector3(0,-2,0));
					break;
				}		
			}

			break;
		}
	case EVENT_MOUSE_MOVE:
		{
			static float ox = param[0];
			static float oy = param[1];

			float x = float(ox - param[0]);
			float y = float(oy - param[1]);

			ox = param[0];
			oy = param[1];

			if(param[2] & SDL_BUTTON(SDL_BUTTON_RIGHT))
				Rotate(Math::Vector3(-y*PI/180.0f,-x*PI/180.0f,0));

			break;
		}
	}
};