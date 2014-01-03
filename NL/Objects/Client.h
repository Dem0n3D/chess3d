#ifndef __NL_CLIENT_H__
#define __NL_CLIENT_H__

//--------------------------------------------------------------------------------------

#include "../Common.h"

#include "../Object.h"

#include "Board/Board.h"

#include "Console.h"

#include "../Utils/Net/Net.h"

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class Client : public Object
			{
			public:

				Client();
				~Client();

				bool Start();

				void OnTurn(void *args);

				GET_SET_ACCESSOR(bool,color);

				SET_ACCESSOR(Console *,console);
				SET_ACCESSOR(Board *,board);

				String adress;

			protected:

				bool Update(float fElapsedTime);

				static void *SendRequest(void *args);

			private:

				Console *console;

				Board *board;

				bool IsReqSended;

				bool color;				

				HTmutex mut;

			};

		};

	};


};

#endif