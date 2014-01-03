#include "Root.h"

NL::Root::Root()
{
	
};

NL::Root::~Root()
{
	
};

void NL::Root::Initialize()
{
	new Log();

	Log::getSingleton().AddLine("Initializing resource manager...");

	new ResourceManager();

//	try
//	{
		Log::getSingleton().AddLine("Initializing system...");

		new NL::System();
		System::getSingleton().Initialize();

		new OpenGL();
		ADD_LOG("Initializing render...",OpenGL::getSingleton().Initialize());

		Log::getSingleton().AddLine("Initializing scene manager...");

		Sm = new Scene::SceneManager();
		Sm->Initialize();

		System::getSingleton().ShowCursor(true);
		System::getSingleton().EnableKeyRepeat(500,30);
		System::getSingleton().EnableUNICODE(true);

		loop = true;
/*	}
	catch(...) // ���� ��������������� ���������� �� �����������, ����� ��������� ��� � ��������� �����
	{
		Log::getSingleton().AddLine("�� ����������� ��������������� ����������!","red");

		Log::getSingleton().Save("Log.htm");

		Close(1);
	}*/
};

void NL::Root::Run()
{
	//--------------------------------------------------------------------------------------
	static DWORD oldt = System::getSingleton().GetTicks();
	DWORD newt = System::getSingleton().GetTicks();
	DWORD dwElapsedTime = (newt > oldt) ? newt - oldt : 1;

	//--------------------------------------------------------------------------------------
	
	while(loop) // ���� �������� �� ������� � ������������
	{
		//System::getSingleton().CallSlots();
		System::Event event = System::getSingleton().GetEvent();
		while(event.message != EVENT_NOEVENTS)
		{
			event.param.push_back(dwElapsedTime);

			switch(event.message)
			{
			case EVENT_QUIT:
				{
					loop = false;

					return;
				}
			default:
				{
					Sm->Callback(event.message,event.param);
					break;
				}
			}

			event = System::getSingleton().GetEvent();
		}

		//--------------------------------------------------------------------------------------
		
		Sm->Update(dwElapsedTime/1000.0f);

		oldt = newt;

		Sm->Render();

		//--------------------------------------------------------------------------------------

		System::getSingleton().SwapBufffers();

		//--------------------------------------------------------------------------------------
	}
};

int NL::Root::Close(int code)
{
	Log::getSingleton().AddLine("Quiting with code " + IntToStr(code) + "...");

	System::getSingleton().Quit();

	delete Sm;
	Sm = NULL;

	Log::getSingleton().Save("Log.htm");

	loop = false;

	return code;
};