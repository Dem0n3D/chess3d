#ifndef __NL_SCENE_MANAGER_H__
#define __NL_SCENE_MANAGER_H__

#include "Common.h"

#include "Camera/Camera.h"
#include "Camera/QCamera.h"
#include "Object.h"
#include "Log.h"

#include "ResourceManager.h"
#include "Renderer/OpenGL.h"

#ifdef _WIN32
	#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef _WIN32
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
#endif

#include <SDL.h> 

//--------------------------------------------------------------------------------------

#include <CEGUI.h>
#include <../RendererModules/OpenGLGUIRenderer/openglrenderer.h>

#ifdef _WIN32
	#ifdef _DEBUG
		#pragma comment(lib,"CEGUIBase_d.lib")
		#pragma comment(lib,"OpenGLGUIRenderer_d.lib")
	#else
		#pragma comment(lib,"CEGUIBase.lib")
		#pragma comment(lib,"OpenGLGUIRenderer.lib")
	#endif
#endif

//--------------------------------------------------------------------------------------
//Подключаем объекты

#include "Objects/Console.h"

#include "Objects/Mesh/Mesh.h"
#include "Objects/Mesh/SkinnedMesh.h"

#include "Objects/Board/Board.h"
#include "Objects/Figure/Figure.h"

#include "Objects/Client.h"
#include "Objects/Server.h"

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------

//Мэнеджер сцены

namespace NL
{	

	namespace Scene
	{

		enum GAME_STATE { GS_MAIN_MENU, GS_GAME_MENU, GS_LAN_MENU, GS_GAME, GS_LAN_GAME };

		class SceneManager
		{
		public:

			SceneManager();
			~SceneManager();

			void Initialize();

			bool Update(float fElapsedTime);
			bool Render();
			bool Release();

			void Callback(WORD mt,std::vector<DWORD> param);

		public:

			bool NewGame(const CEGUI::EventArgs &e);
			bool LoadGame(const CEGUI::EventArgs &e);

			bool LANGameDialog(const CEGUI::EventArgs &e);

			bool ClientConnect(const CEGUI::EventArgs &e);

			bool Exit(const CEGUI::EventArgs &e);

			bool SaveGame(const CEGUI::EventArgs &e);
			bool EndGame(const CEGUI::EventArgs &e);

			bool Load(const CEGUI::EventArgs &e);
			bool Save(const CEGUI::EventArgs &e);
			bool Back(const CEGUI::EventArgs &e);

		private:

			Scene::Camera *Cam;
			Scene::Objects::Object *Main;

			GAME_STATE gstate;

		};

	};

};

#endif