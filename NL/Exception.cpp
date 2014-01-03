#include "Exception.h"

NL::Exception::Exception()
{
	Message = "";

	if (Log::getSingletonPtr())
	{
			Log::getSingleton().Add("Сгенерировано исключение! ","red");
			Log::getSingleton().AddLine("(нет описания)","brown");			 
	}
};

NL::Exception::Exception(const String &message)
{
	Message = message;

	if (Log::getSingletonPtr())
	{
		Log::getSingleton().Add("Сгенерировано исключение: ","red");
		Log::getSingleton().AddLine(Message,"brown");	
	}
};

NL::Exception::~Exception()
{

};

NL::String NL::Exception::GetMessage()
{
	return Message;
};