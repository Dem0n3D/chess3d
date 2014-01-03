#include "NL/Root.h"

using namespace NL;

int main(int argc,NCHAR* argv[])
{
	Root root;

	try
	{				
		root.Initialize();
		root.Run();
		return root.Close(0);
	}
	// Нужно просмотреть исключения, связанные с логом и корнем!
	catch (...)
	{
		Log::getSingleton().AddLine("Аварийное завершение: не перехвачено сгенерированное исключение!","red");
		Log::getSingleton().Save("Log.htm");
		return root.Close(1);
	}	
}