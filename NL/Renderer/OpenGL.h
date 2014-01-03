#pragma once

#include "../Common.h"
#include "../Log.h"
#include "../Math/Math.h"
#include "../Singleton.h"
//#include "FreeType.h"

//--------------------------------------------------------------------------------------

#ifdef WIN32
	#include <windows.h>
#endif

//--------------------------------------------------------------------------------------

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "libExt.h" // Расширения

//--------------------------------------------------------------------------------------

#ifdef WIN32
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
	#pragma comment(lib,"glaux.lib")
#endif

//--------------------------------------------------------------------------------------
// Текстурная библиотека

#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>

#ifdef WIN32
	#pragma comment(lib,"DevIL.lib")
	#pragma comment(lib,"ILU.lib")
	#pragma comment(lib,"ILUT.lib")
#endif

//--------------------------------------------------------------------------------------

namespace NL
{

	enum MATRIX_MODE	{ M_WORLD, M_VIEW, M_PROJECTION };

	class OpenGL : public Singleton<OpenGL>
	{
	public:

		OpenGL();
		~OpenGL();

	public:

		bool Initialize();

	public:

		//void DrawText(const String &family,unsigned int size,const String &text);

		//--------------------------------------------------------------------------------------
		// Операции над матрицами и стеком

		void LoadMatrix(unsigned int mode,const Math::Matrix4x4 &mat);
		void LoadIdentityMatrix(unsigned int mode);
		void MultMatrix(unsigned int mode,const Math::Matrix4x4 &mat);

		void PushMatrix();
		void PopMatrix();

		Math::Matrix4x4 GetMatrix(unsigned int mode);

		//--------------------------------------------------------------------------------------
		// Текстуры

		int  LoadTexture(const String &filename);
		void SetTexture(int index);

		//--------------------------------------------------------------------------------------
		// Расширения

		bool IsExtensionSupported(const String &extname); // Проверяет поодержку расширений

		//--------------------------------------------------------------------------------------
		// Шейдеры

		/*int CreateShader(const String &filename,const String &efuncname);

		bool BindShaderProgram(int index);
		bool EnableShaderProfile(int index);
		bool DisableShaderProfile(int index);

		void SetShaderMatrix(int index,const Math::Matrix4x4 &mat);*/

		//--------------------------------------------------------------------------------------

		void Release();

		void ApplyTransform();

	private:		

		Math::Matrix4x4 ViewMatrix,ProjectionMatrix;

		//--------------------------------------------------------------------------------------

		class MatrixStack // Усовершенствовать!
		{
		public:

			MatrixStack(){NL::Math::Matrix4x4 m; st.push(m.Identity());};
			~MatrixStack(){};

			void push(const NL::Math::Matrix4x4 &M)
			{
				st.push(st.top() * M);
			}

			void pop()
			{
				st.pop();
			}

			NL::Math::Matrix4x4 top()
			{
				return st.top();
			}

			void Mul(const NL::Math::Matrix4x4 &M)
			{
				NL::Math::Matrix4x4 m = st.top();
				st.pop();
				st.push(m * M);
			};

		private:

			std::stack<NL::Math::Matrix4x4> st;

		} mst;

	};
	
};