#ifndef __NL_OBJECT_H__
#define __NL_OBJECT_H__

#include "Common.h"

#include "Math/Math.h"
#include "Log.h"

#include "ResourceManager.h"
#include "Renderer/OpenGL.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class Object
			{
			public:

				Object();
				virtual ~Object();

			//--------------------------------------------------------------------------------------

				virtual bool	AttachChild(Object *pChild);
				virtual Object *GetChild(const NL::String &Name);
				virtual bool	RemoveChild(const NL::String &Name);

			//--------------------------------------------------------------------------------------

				virtual bool RenderAll(WORD pass);
				virtual bool UpdateAll(float fElapsedTime);
				virtual bool ReleaseAll();

			//--------------------------------------------------------------------------------------

				virtual void Callback(WORD mt,std::vector<DWORD> param);

			//--------------------------------------------------------------------------------------

				virtual void Rotate(const Math::Vector3 &Angle);
				virtual void Rotate(float x,float y,float z);

				virtual void Move(const Math::Vector3 &Move);
				virtual void Move(float x,float y,float z);

				virtual void SetPos(const Math::Vector3 &Pos);
				virtual void SetPos(float x,float y,float z);

				virtual void Scale(const Math::Vector3 &Scale);
				virtual void Scale(float x,float y,float z);

			//--------------------------------------------------------------------------------------

				virtual NL::Math::Matrix4x4 GetWorldTransform();

			//--------------------------------------------------------------------------------------

				GET_SET_ACCESSOR(WORD,ObjectType);
				GET_SET_ACCESSOR(NL::String,Name);
				GET_SET_ACCESSOR(Object *,Parent);
				GET_SET_ACCESSOR(bool,Visible);
				GET_SET_ACCESSOR(bool,Active);
				GET_SET_ACCESSOR(NL::Math::Matrix4x4,M);

			protected:

				//////////////////////////////////////////////////////////////////////////
				////////////Обязательно исправить!!!
				virtual bool Render(WORD pass){return false;};// = 0;
				virtual bool Update(float fElapsedTime){return false;}; // = 0;
				virtual bool Release();

			//--------------------------------------------------------------------------------------

				WORD ObjectType;
				bool Visible,Active;
				NL::String Name;
				Object *Parent;
				std::list<Object *> Childrens;
				NL::Math::Matrix4x4 M;

				;

			};

		};

	};

};

#endif