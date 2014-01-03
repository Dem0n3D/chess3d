#ifndef __NL_HORSE_H__
#define __NL_HORSE_H__

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

			class Horse : public Figure
			{
			public:

				Horse();
				~Horse();

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);

			};

		};

	};

};

#endif