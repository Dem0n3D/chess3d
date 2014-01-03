#ifndef __NL_SYSTEM_H__
#define __NL_SYSTEM_H__

#include "Common.h"

#include "Log.h"
#include "Math/Math.h"

#include "Singleton.h"

//--------------------------------------------------------------------------------------

#include <SDL.h> 

#define SDL_main main 

#ifdef WIN32
	#pragma comment(lib,"SDL.lib")
#endif

////////////////////////////////////////////////////////////////////////////////////////

//Системная обертка

namespace NL
{	

	enum EVENTS			
	{	
		EVENT_NOEVENTS = 0,
		EVENT_KEY_DOWN,
		EVENT_KEY_UP,
		EVENT_MOUSE_MOVE,
		EVENT_MOUSEBUTTON_DOWN,
		EVENT_MOUSEBUTTON_UP,
		EVENT_BUTTON_CLICK,
		EVENT_QUIT		
	};

	enum MOUSEBUTTONS	
	{	
		MOUSEBUTTON_LEFT = SDL_BUTTON_LEFT,
		MOUSEBUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
		MOUSEBUTTON_RIGHT = SDL_BUTTON_RIGHT, 
		MOUSEBUTTON_WHEELUP = SDL_BUTTON_WHEELUP,
		MOUSEBUTTON_WHEELDOWN = SDL_BUTTON_WHEELDOWN 
	};

	enum BUTTONS
	{
		BUTTON_DOWN = SDLK_DOWN,
		BUTTON_UP = SDLK_UP,
		BUTTON_RIGHT = SDLK_RIGHT,
		BUTTON_LEFT = SDLK_LEFT,
		BUTTON_PAGE_UP = SDLK_PAGEUP, 
		BUTTON_PAGE_DOWN = SDLK_PAGEDOWN
	};

	class SLOT
	{
	public:

		SLOT(){};
		~SLOT(){};

		template<typename T>
		void Connect(void (T::*function)(void *args),T *obj){ slot = new __Slot<T>(function,obj); };

		void Call(void *args) { slot->Call(args); };

	private:		

		struct __SlotBase 
		{
			virtual void Call(void *args) = 0;
		} *slot;

		template<typename T>
		struct __Slot : public __SlotBase
		{
			typedef void (T::*Function)(void *args);

			__Slot(Function fn,T *Obj):function(fn),obj(Obj){};

			void Call(void *args) { (obj->*function)(args); };

		private:

			Function function;
			T *obj;
		};

	};

	class System : public Singleton<System>
	{		
	public:

		struct Event
		{
			Event();
			Event(WORD Message);
			Event(WORD Message,const std::vector<DWORD> &Param);

			WORD message;
			std::vector<DWORD> param;
		};

	public:

		System();

		~System();

		void Initialize();

		DWORD GetTicks();

		void ShowCursor(bool bShow);
		void EnableUNICODE(bool bEnable);
		void EnableKeyRepeat(int delay,int interval);

		void SwapBufffers();

		Event GetEvent();
		void GenerateEvent(const Event &event);

		void ConnectSlot(DWORD event,SLOT slot);

		void GetCurPos(int *x,int *y);

		void Quit();

		void GetFileList(const String &dirname,std::vector<NL::String> *v);

	private:

		std::queue<NL::System::Event> events;

		std::map<DWORD,std::list<SLOT> > slots;

	};

};

#endif