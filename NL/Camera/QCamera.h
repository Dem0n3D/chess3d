#ifndef __NL_CAMERA_QCAMERA_H__
#define __NL_CAMERA_QCAMERA_H__

#include "Camera.h"

namespace NL
{

	namespace Scene
	{

		class QCamera : public Camera
		{
		public:

			QCamera();
			~QCamera();

		public:

			void Rotate(float x,float y,float z);
			void Rotate(const NL::Math::Vector3 &v);

			void Move(float x,float y,float z);
			void Move(const NL::Math::Vector3 &v);

			void Slide(float x,float y,float z);
			void Slide(const NL::Math::Vector3 &v);

			Math::Matrix4x4 GetViewMatrix();
			Math::Matrix4x4 GetProjMatrix();

			void Callback(WORD mt,std::vector<DWORD> param);

		protected:

			Math::Vector3 u,r,d,p,rot;

		};

	};

};

#endif