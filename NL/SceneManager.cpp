#include "SceneManager.h"

//--------------------------------------------------------------------------------------

#include "Utils/Net/Net.h"

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::SceneManager::SceneManager()
{

};

NL::Scene::SceneManager::~SceneManager()
{

};

void NL::Scene::SceneManager::Initialize()
{
	int width = *((int *)ResourceManager::getSingleton().GetResourcePtr("Window width"));
	int height = *((int *)ResourceManager::getSingleton().GetResourcePtr("Window height"));

	Cam	= new Scene::Camera();
	Cam->SetProjParams((float)width/(float)height,45,0.1f,1000);

	Main	= new Scene::Objects::Object();

	Log::getSingleton().AddLine("Initializing GUI...");

	//--------------------------------------------------------------------------------------

	using namespace CEGUI;

	Renderer *renderer = new CEGUI::OpenGLRenderer(0,width,height);
	new CEGUI::System(renderer);

	SchemeManager::getSingleton().loadScheme("Data/GUI/schemes/TaharezLook.scheme");
	SchemeManager::getSingleton().loadScheme("Data/GUI/schemes/WindowsLook.scheme");
	SchemeManager::getSingleton().loadScheme("Data/GUI/schemes/VanillaSkin.scheme");

	FontManager::getSingleton().createFont("Data/GUI/fonts/Arial.font");

	Window* myRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("Data/GUI/layouts/GUI.layout");
	CEGUI::System::getSingleton().setGUISheet(myRoot);

	WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);
	WindowManager::getSingleton().getWindow("LANMenu")->setVisible(false);
	WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(false);
	WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(false);
	WindowManager::getSingleton().getWindow("Console")->setVisible(false);
	WindowManager::getSingleton().getWindow("Change")->setVisible(false);
	WindowManager::getSingleton().getWindow("Message")->setVisible(false);
	WindowManager::getSingleton().getWindow("ProtocolWindow")->setVisible(false);

	//--------------------------------------------------------------------------------------

	MultiColumnList* mcl = (MultiColumnList *)WindowManager::getSingleton().getWindow("Protocol");
	
	mcl->addColumn((utf8 *)"№",1,cegui_reldim(0.14f));
	mcl->addColumn((utf8 *)"Белые",2,cegui_reldim(0.40f));
	mcl->addColumn((utf8 *)"Чёрные",3,cegui_reldim(0.40f));

	mcl->setUserSortControlEnabled(false);

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	WindowManager::getSingleton().getWindow("but1")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::NewGame,this));
	WindowManager::getSingleton().getWindow("but2")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::LoadGame,this));
	WindowManager::getSingleton().getWindow("but3")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::LANGameDialog,this));
	WindowManager::getSingleton().getWindow("but4")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Exit,this));
	WindowManager::getSingleton().getWindow("but5")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::NewGame,this));
	WindowManager::getSingleton().getWindow("but6")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::LoadGame,this));
	WindowManager::getSingleton().getWindow("but7")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::SaveGame,this));
	WindowManager::getSingleton().getWindow("but8")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::EndGame,this));
	WindowManager::getSingleton().getWindow("but9")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Save,this));
	WindowManager::getSingleton().getWindow("but10")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Back,this));
	WindowManager::getSingleton().getWindow("but11")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Load,this));
	WindowManager::getSingleton().getWindow("but12")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Back,this));
	WindowManager::getSingleton().getWindow("but13")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::NewGame,this));

	WindowManager::getSingleton().getWindow("but15")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::ClientConnect,this));
	WindowManager::getSingleton().getWindow("but16")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::SceneManager::Back,this));

	//======================================================================================

	Scene::Objects::Console *console = new Scene::Objects::Console();
	console->Initialize();
	console->Set_Name("Console");
	Main->AttachChild(console);

	Net::Initialize();

	gstate = GS_MAIN_MENU;
};

bool NL::Scene::SceneManager::Update(float fElapsedTime)
{
	Main->UpdateAll(fElapsedTime);

	CEGUI::System::getSingleton().injectTimePulse(fElapsedTime/1000.0f);

	return true;
};

bool NL::Scene::SceneManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//--------------------------------------------------------------------------------------

	OpenGL::getSingleton().LoadIdentityMatrix(M_WORLD);
	OpenGL::getSingleton().LoadMatrix(M_VIEW,Cam->GetViewMatrix());
	OpenGL::getSingleton().LoadMatrix(M_PROJECTION,Cam->GetProjMatrix());

	Main->RenderAll(RENDER_PASS_MAIN);

	CEGUI::System::getSingleton().renderGUI();

	//--------------------------------------------------------------------------------------

	glFlush();

	return true;
};

bool NL::Scene::SceneManager::Release()
{
	return true;
};

void NL::Scene::SceneManager::Callback(WORD mt,std::vector<DWORD> param)
{
	Cam->Callback(mt,param);
	Main->Callback(mt,param);

	//--------------------------------------------------------------------------------------

	switch(mt)
	{
	case EVENT_MOUSE_MOVE:		
		CEGUI::System::getSingleton().injectMousePosition(float(param[0]),float(param[1]));
		break;

	case EVENT_KEY_DOWN:
		// to tell CEGUI that a key was pressed, we inject the scancode.
		CEGUI::System::getSingleton().injectKeyDown(param[1]);
		CEGUI::System::getSingleton().injectChar(param[2]);
		break;

	case EVENT_KEY_UP:
		{
			CEGUI::System::getSingleton().injectKeyUp(param[1]);

			switch(char(param[0]))
			{
			case '`':
				{
					CEGUI::WindowManager::getSingleton().getWindow("Console")->setVisible(!CEGUI::WindowManager::getSingleton().getWindow("Console")->isVisible());

					break;
				}
			case 27:
				{
					if (gstate == GS_GAME)
					{
						CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(true/*!CEGUI::WindowManager::getSingleton().getWindow("Menu2")->isVisible()*/);
						gstate = GS_GAME_MENU;
					}
					else if (gstate == GS_GAME_MENU)
					{
						CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false/*!CEGUI::WindowManager::getSingleton().getWindow("Menu2")->isVisible()*/);
						gstate = GS_GAME;
					}

					break;
				}
			}

			break;
		}		

	case EVENT_MOUSEBUTTON_DOWN:
		switch(param[0])
		{
		case MOUSEBUTTON_LEFT:
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
			break;
		case MOUSEBUTTON_MIDDLE:
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
			break;
		case MOUSEBUTTON_RIGHT:
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
			break;
		case MOUSEBUTTON_WHEELUP:
			CEGUI::System::getSingleton().injectMouseWheelChange( +1 );
			break;
		case MOUSEBUTTON_WHEELDOWN:
			CEGUI::System::getSingleton().injectMouseWheelChange( -1 );
			break;
		}
		break;

	case EVENT_MOUSEBUTTON_UP:
		switch(param[0])
		{
		case MOUSEBUTTON_LEFT:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
			break;
		case MOUSEBUTTON_MIDDLE:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
			break;
		case MOUSEBUTTON_RIGHT:
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
			break;
		}
		break;

	}
};

bool NL::Scene::SceneManager::NewGame(const CEGUI::EventArgs &e)
{
	Main->RemoveChild("Board"); // Избавляемся от хлама
	Main->RemoveChild("Client");
	Main->RemoveChild("Server");

	CEGUI::MultiColumnList* mcl = (CEGUI::MultiColumnList *)CEGUI::WindowManager::getSingleton().getWindow("Protocol");
	mcl->resetList();

	Scene::Objects::Board *board = new Scene::Objects::Board();
	board->Initialize();
	board->Set_Name("Board");
	Main->AttachChild(board);

	switch(gstate)
	{
	case GS_LAN_MENU:
		{
			gstate = GS_LAN_GAME;

			Objects::Client *client1 = new Objects::Client();
			client1->Set_Name("Client_1");
			client1->adress = "127.0.0.1";
			client1->Set_color(WHITE);
			client1->Set_console((Objects::Console *)Main->GetChild("Console"));
			client1->Set_board((Objects::Board *)Main->GetChild("Board"));
			client1->Start();
			Main->AttachChild(client1);

			Objects::Server *server = new Objects::Server();
			client1->Set_Name("Server_1");
			client1->Start();
			Main->AttachChild(server);

			SLOT sl_turn;
			sl_turn.Connect(&NL::Scene::Objects::Client::OnTurn,client1);
			NL::System::getSingleton().ConnectSlot(EVENT_TURN,sl_turn);

			break;
		}
	default:
		{
			gstate = GS_GAME;

			break;
		}
	}

	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("ProtocolWindow")->setVisible(true);
	
	return true;
};

bool NL::Scene::SceneManager::LoadGame(const CEGUI::EventArgs &e)
{
	std::vector<NL::String> v;
	System::getSingleton().GetFileList("Data/Saves/",&v);

	CEGUI::Listbox *lst = (CEGUI::Listbox *)CEGUI::WindowManager::getSingleton().getWindow("LoadList");

 	for (int i = 0; i < (int)v.size(); i++)
 	{
		CEGUI::ListboxItem *item = new CEGUI::ListboxTextItem((CEGUI::utf8 *)copy(v[i],v[i].length()-4,0).c_str()); // Копируем без расширения
		item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
 		lst->addItem(item);
 	}

	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(true);

	return true;
};

bool NL::Scene::SceneManager::LANGameDialog(const CEGUI::EventArgs &e)
{
	gstate = GS_LAN_MENU;

	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(true);

	/*Scene::Objects::Board *board = new Scene::Objects::Board();
	board->Initialize();
	board->Set_Name("Board");
	Main->AttachChild(board);

	Objects::Client *client1 = new Objects::Client();
	client1->Set_Name("Client_1");
	client1->adress = "127.0.0.1";
	client1->Set_color(WHITE);
	client1->Set_console((Objects::Console *)Main->GetChild("Console"));
	client1->Set_board((Objects::Board *)Main->GetChild("Board"));
	client1->Start();
	Main->AttachChild(client1);

	SLOT sl_turn;
	sl_turn.Connect(&NL::Scene::Objects::Client::OnTurn,client1);
	NL::System::getSingleton().ConnectSlot(EVENT_TURN,sl_turn);

	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(false);*/

	return true;
};

bool NL::Scene::SceneManager::ClientConnect(const CEGUI::EventArgs &e)
{
	Scene::Objects::Board *board = new Scene::Objects::Board();
	board->Initialize();
	board->Set_Name("Board");
	Main->AttachChild(board);

	Objects::Client *client1 = new Objects::Client();
	client1->Set_Name("Client_1");
	client1->adress = CEGUI::WindowManager::getSingleton().getWindow("Edit2")->getText().c_str();
	client1->Set_color(WHITE);
	client1->Set_console((Objects::Console *)Main->GetChild("Console"));
	client1->Set_board((Objects::Board *)Main->GetChild("Board"));
	client1->Start();
	Main->AttachChild(client1);

	SLOT sl_turn;
	sl_turn.Connect(&NL::Scene::Objects::Client::OnTurn,client1);
	NL::System::getSingleton().ConnectSlot(EVENT_TURN,sl_turn);

	CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(false);

	return true;
};

bool NL::Scene::SceneManager::Exit(const CEGUI::EventArgs &e)
{
	System::getSingleton().GenerateEvent(EVENT_QUIT);

	return true;
};

bool NL::Scene::SceneManager::SaveGame(const CEGUI::EventArgs &e)
{
	CEGUI::WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(true);
	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);

	return true;
};

bool NL::Scene::SceneManager::EndGame(const CEGUI::EventArgs &e)
{
	gstate = GS_MAIN_MENU;

	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(true);
	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(true);

	Main->RemoveChild("Board"); // Избавляемся от хлама
	Main->RemoveChild("Client");
	Main->RemoveChild("Server");

	CEGUI::MultiColumnList* mcl = (CEGUI::MultiColumnList *)CEGUI::WindowManager::getSingleton().getWindow("Protocol");
	mcl->resetList();

	return true;
};

bool NL::Scene::SceneManager::Load(const CEGUI::EventArgs &e)
{
	Main->RemoveChild("Board"); // Избавляемся от хлама
	Main->RemoveChild("Client");
	Main->RemoveChild("Server");

	CEGUI::MultiColumnList* mcl = (CEGUI::MultiColumnList *)CEGUI::WindowManager::getSingleton().getWindow("Protocol");
	mcl->resetList();

	gstate = GS_GAME;

	Scene::Objects::Board *board = new Scene::Objects::Board();
	board->Initialize();
	board->Set_Name("Board");
	Main->AttachChild(board);

	CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("ProtocolWindow")->setVisible(true);

	//--------------------------------------------------------------------------------------

	CEGUI::Listbox *lst = (CEGUI::Listbox *)CEGUI::WindowManager::getSingleton().getWindow("LoadList");
	CEGUI::ListboxTextItem *item = (CEGUI::ListboxTextItem *)lst->getFirstSelectedItem();
	if (item)
	{
		String filename = "Data/Saves/" + String(item->getText().c_str()) + ".chs";

		std::ifstream f(filename.c_str());

		int size=0;
		f >> size;

		for (int i = 0; i < size; i++)
		{
			Scene::Objects::Turn t;
			f >> t.from.x >> t.from.y >> t.to.x >> t.to.y;
			((Scene::Objects::Board *)Main->GetChild("Board"))->MakeTurn(t.from,t.to);
		}

		f.close();
	}

	return true;
};

bool NL::Scene::SceneManager::Save(const CEGUI::EventArgs &e)
{
	std::vector<Scene::Objects::Turn> &v = ((Scene::Objects::Board *)Main->GetChild("Board"))->turns_list;

	String filename = "Data/Saves/" + String(CEGUI::WindowManager::getSingleton().getWindow("Edit1")->getText().c_str()) + ".chs";

	std::ofstream f(filename.c_str());

	f << v.size();

	for (int i = 0; i < (int)v.size(); i++)
	{
		f << v[i].from.x << v[i].from.y << v[i].to.x << v[i].to.y;
	}

	f.close();

	CEGUI::WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(false);
	CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(true);

	return true;
};

bool NL::Scene::SceneManager::Back(const CEGUI::EventArgs &e)
{
	switch(gstate)
	{
	case GS_MAIN_MENU:
		{
			CEGUI::WindowManager::getSingleton().getWindow("Menu1")->setVisible(true);
			CEGUI::WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(false);
			CEGUI::WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(false);

			break;
		}
	case GS_GAME_MENU:
		{
			CEGUI::WindowManager::getSingleton().getWindow("Menu2")->setVisible(true);
			CEGUI::WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(false);
			CEGUI::WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(false);

			break;
		}
	case GS_LAN_MENU:
		{
			CEGUI::WindowManager::getSingleton().getWindow("LANMenu")->setVisible(true);
			CEGUI::WindowManager::getSingleton().getWindow("LoadDialog")->setVisible(false);
			CEGUI::WindowManager::getSingleton().getWindow("SaveDialog")->setVisible(false);

			break;
		}
	}

	return true;
};