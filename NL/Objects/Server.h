#ifndef __NL_SERVER_H__
#define __NL_SERVER_H__

//--------------------------------------------------------------------------------------

#include "../Common.h"

#include "../Object.h"

#include "Figure/Figure.h"

#include "../Utils/Net/Net.h"

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class Server : public Object
			{
			public:

				Server();
				~Server();

				bool Start();

				static void *ServerLoop(void *args);

			private:

				std::vector<Turn> turns;

				NLsocket sock;

				bool Shutdown;

			};

		};

	};


};

#endif