#include "Console.h"

//--------------------------------------------------------------------------------------

#include <CEGUI.h>

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Console::Console()
{
	lines.clear();
};

NL::Scene::Objects::Console::~Console()
{

};

void NL::Scene::Objects::Console::Initialize()
{
	/*CEGUI::Window* Console = CEGUI::WindowManager::getSingleton().loadWindowLayout("Data/GUI/layouts/Console.layout");
	Console->setVisible(false);
	 
	CEGUI::WindowManager::getSingleton().getWindow("Root")->addChildWindow(Console);
	 
	CEGUI::WindowManager::getSingleton().getWindow("List")->setText((CEGUI::utf8 *)"");*/
};

/*NL::String &NL::Scene::Objects::Console::operator [] (size_t n)
{
	// Проверка на выход за границы!
	return lines[n];
};*/

bool NL::Scene::Objects::Console::Update(float fElapsedTime)
{
	String res = "";

	for (int i = (int)lines.size()-1; i >= 0; i--)
	{
		res += lines[i] + "\n";
	}

	CEGUI::WindowManager::getSingleton().getWindow("List")->setText((CEGUI::utf8 *)res.c_str());

	return true;
};