#ifndef __NL_NET_H__
#define __NL_NET_H__

#include "../../Exception.h"

//--------------------------------------------------------------------------------------

#include <nl.h>
#include <hawkthreads.h>

#ifdef _WIN32
	#pragma comment(lib,"HawkNL.lib")
#endif

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{
	
	namespace Net
	{
		
		void NetError();

		void Initialize();

		class SystemError : public Exception // Системная ошибка
		{
		public:

			SystemError():Exception("System error!"){ nlShutdown(); };
			explicit SystemError(const String &message):Exception(message){};
		};

		class HawkNL : public Exception // Ошибка HawkNL
		{
		public:

			HawkNL():Exception("HawkNL error!"){ nlShutdown(); };
			explicit HawkNL(const String &message):Exception(message){};
		};

	};

};

#endif