#ifndef __NL_QUEEN_H__
#define __NL_QUEEN_H__

//--------------------------------------------------------------------------------------

#include "../../Common.h"

#include "Figure.h"

//--------------------------------------------------------------------------------------

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{		

			class Queen : public Figure
			{
			public:

				Queen();
				~Queen();

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);

			};

		};

	};

};

#endif