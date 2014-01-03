#include "Net.h"

void NL::Net::NetError()
{
	NLenum err = nlGetError();

	if(err == NL_SYSTEM_ERROR)
	{
		NLint e = nlGetSystemError();

		throw(SystemError("System error: " + String(nlGetSystemErrorStr(e))));
	}
	else
	{
		throw(HawkNL("HawkNL error # " + String(nlGetErrorStr(err))));
	}
};

void NL::Net::Initialize()
{
	if(!nlInit())
		NetError();

	if(!nlSelectNetwork(NL_IP))
		NetError();
};