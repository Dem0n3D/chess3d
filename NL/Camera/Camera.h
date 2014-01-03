#ifndef __NL_CAMERA_H__
#define __NL_CAMERA_H__

#include "../Math/Math.h"

#include "../System.h"

#include <SDL.h>

namespace NL
{

	namespace Scene
	{

		class Camera
		{
		public:

			Camera();
			virtual ~Camera();

		public:

			void SetProjParams(float Aspect,float Fovy,float Zn,float Zf){Set_aspect(Aspect);Set_fovy(Fovy);Set_zn(Zn);Set_zf(Zf);};
			
			virtual void Rotate(float x,float y,float z);
			virtual void Rotate(const NL::Math::Vector3 &v);
			
			virtual void Move(float x,float y,float z);
			virtual void Move(const NL::Math::Vector3 &v);
			
			virtual void Slide(float x,float y,float z);
			virtual void Slide(const NL::Math::Vector3 &v);

			virtual Math::Matrix4x4 GetViewMatrix();
			virtual Math::Matrix4x4 GetProjMatrix();

			virtual void Callback(WORD mt,std::vector<DWORD> param);

			GET_SET_ACCESSOR(float,aspect);
			GET_SET_ACCESSOR(float,fovy);
			GET_SET_ACCESSOR(float,zn);
			GET_SET_ACCESSOR(float,zf);

		protected:

			void KeyDown(void *args);
			void MouseMove(void *args);

			float aspect,fovy;
			float zn,zf;

			Math::Vector3 u,r,d,p,rot;
			
		};

	};

};

#endif