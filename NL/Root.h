#ifndef __NL_ROOT_H__
#define __NL_ROOT_H__

#include "Common.h"

#include "System.h"

#include "Log.h"
#include "SceneManager.h"

/*#include <SDL.h> 

#define SDL_main main 

#ifdef WIN32
	#pragma comment(lib,"SDL.lib")
#endif*/

////////////////////////////////////////////////////////////////////////////////////////

//Корень

namespace NL
{	

	class Root
	{
	public:

		Root();
		~Root();

	public:

		void Initialize();
		void Run();
		int Close(int code = 0);

	private:

		bool loop;

		Scene::SceneManager *Sm;
				
	};

};

#endif