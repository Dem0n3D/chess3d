#ifndef __NL_CONSOLE_H__
#define __NL_CONSOLE_H__

//--------------------------------------------------------------------------------------

#include "../Common.h"

#include "../Object.h"

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class Console : public Object
			{
			public:

				Console();
				~Console();

				void Initialize();

				//String &operator [] (size_t n);

			protected:

				bool Update(float fElapsedTime);

			public:

				std::vector<String> lines;

			};

		};

	};


};

#endif