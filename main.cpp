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
	// ����� ����������� ����������, ��������� � ����� � ������!
	catch (...)
	{
		Log::getSingleton().AddLine("��������� ����������: �� ����������� ��������������� ����������!","red");
		Log::getSingleton().Save("Log.htm");
		return root.Close(1);
	}	
}