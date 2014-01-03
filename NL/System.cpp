#include "System.h"

#include "ResourceManager.h"

//--------------------------------------------------------------------------------------

#include <io.h>

//--------------------------------------------------------------------------------------

NL::System* NL::Singleton<NL::System>::ms_Singleton = 0;

////////////////////////////////////////////////////////////////////////////////////////

NL::System::Event::Event()
{

};

NL::System::Event::Event(WORD Message)
{
	message = Message;
};

NL::System::Event::Event(WORD Message,const std::vector<DWORD> &Param)
{
	message = Message;
	param = Param;
};

//--------------------------------------------------------------------------------------

NL::System::System()
{

};

NL::System::~System()
{

};

void NL::System::Initialize()
{
	int width,height,flags;
	DWORD whitecol,blackcol,bordercolor;

	bool fullscreen,mirror;

	std::ifstream f("Data/config.cfg");
	f >> width >> height >> fullscreen;
	f >> whitecol >> blackcol >> bordercolor >> mirror;
	f.close();

	flags = SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL;

	if (fullscreen)
	{
		flags |= SDL_FULLSCREEN;
	}

	ResourceManager::getSingleton().AddResource("Window width",&width,sizeof(width));
	ResourceManager::getSingleton().AddResource("Window height",&height,sizeof(height));
	ResourceManager::getSingleton().AddResource("Mirror",&mirror,sizeof(mirror));
	ResourceManager::getSingleton().AddResource("Border color",&bordercolor,sizeof(bordercolor));
	ResourceManager::getSingleton().AddResource("White color",&whitecol,sizeof(whitecol));
	ResourceManager::getSingleton().AddResource("Black color",&blackcol,sizeof(blackcol));

	ADD_LOG("Initializing SDL...",(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) >= 0));
	ADD_LOG("Initializing SDL_VideoMode...",SDL_SetVideoMode(width,height,24,flags));

	SDL_ShowCursor(SDL_DISABLE);
	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
};

NL::DWORD NL::System::GetTicks()
{
	return SDL_GetTicks();
};

void NL::System::ShowCursor(bool bShow)
{
	SDL_ShowCursor(bShow);
};

void NL::System::EnableUNICODE(bool bEnable)
{
	SDL_EnableUNICODE(bEnable);
};

void NL::System::EnableKeyRepeat(int delay,int interval)
{
	SDL_EnableKeyRepeat(delay,interval);
};

void NL::System::SwapBufffers()
{
	SDL_GL_SwapBuffers();
};

NL::System::Event NL::System::GetEvent()
{
	Event e(EVENT_NOEVENTS);

	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
			{
				e.message = EVENT_KEY_DOWN;
				e.param.resize(3);
				e.param[0] = event.key.keysym.sym;
				e.param[1] = event.key.keysym.scancode;
				e.param[2] = event.key.keysym.unicode;

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_KEY_DOWN];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		case SDL_KEYUP:
			{
				e.message = EVENT_KEY_UP;
				e.param.resize(3);
				e.param[0] = event.key.keysym.sym;
				e.param[1] = event.key.keysym.scancode;
				e.param[2] = event.key.keysym.unicode;

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_KEY_UP];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		case SDL_MOUSEMOTION:
			{
				e.message = EVENT_MOUSE_MOVE;
				e.param.resize(3);
				e.param[0] = event.motion.x;
				e.param[1] = event.motion.y;
				e.param[2] = event.motion.state/2+1; // Да, извращенцы :(

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_MOUSE_MOVE];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			{
				e.message = EVENT_MOUSEBUTTON_DOWN;
				e.param.resize(1);
				e.param[0] = event.button.button;

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_MOUSEBUTTON_DOWN];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		case SDL_MOUSEBUTTONUP:
			{
				e.message = EVENT_MOUSEBUTTON_UP;
				e.param.resize(1);
				e.param[0] = event.button.button;

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_MOUSEBUTTON_UP];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		case SDL_QUIT:
			{
				e.message = EVENT_QUIT;

				//--------------------------------------------------------------------------------------

				std::list<SLOT> ls = slots[EVENT_QUIT];

				for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
				{
					(*it).Call(&e.param);
				}

				//--------------------------------------------------------------------------------------

				break;
			}
		}
	}
	else if(events.size() > 0) // Да, я тоже извращенец :)
	{
		e = events.front();
		events.pop();

		std::list<SLOT> ls = slots[e.message];

		for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
		{
			(*it).Call(&e.param);
		}
	}
		
	return e;
};

void NL::System::GenerateEvent(const Event &event)
{
	events.push(event);

	//--------------------------------------------------------------------------------------

	/*std::list<SLOT> ls = slots[event.message];

	for (std::list<SLOT>::iterator it = ls.begin(); it != ls.end(); it++) // Вызываем приконнекченные слоты
	{
		(*it).Call((void *)&event.param[0]);
	}*/

	//--------------------------------------------------------------------------------------
};

void NL::System::ConnectSlot(DWORD event,SLOT slot)
{
	slots[event].push_back(slot);
};

void NL::System::GetCurPos(int *x,int *y)
{
	SDL_GetMouseState(x,y);
};

void NL::System::Quit()
{
	SDL_Quit();
};

void NL::System::GetFileList(const String &dirname,std::vector<NL::String> *v)
{
	_finddata_t fi;
	intptr_t h;

	if(h = _findfirst((dirname+"/*.chs").c_str(),&fi))
	{
		v->push_back(fi.name);

		while (_findnext(h,&fi) == 0)
		{
			v->push_back(fi.name);
		}

		_findclose(h);
	}

	/*void ListFiles(AnsiString path, TStrings* List)
	{
		TSearchRec sr;

		FILE *fp;
		char szBuffer[256];
		AnsiString SearchText;

		for (int ferr = FindFirst(path+"*.*", faAnyFile, sr); ferr == 0; ferr=FindNext(sr))
		{ if (sr.Attr & faDirectory)
		{ if (sr.Name == "." ) continue;
		else if (sr.Name == "..") continue;
		else ListFiles(path+sr.Name+"\\",List);
		continue;
		} // faDirectory

		// блок "один файл"
		List->Add(ExtractFileName(sr.Name));
		} // for i = 0

		FindClose(sr);
	}*/
};