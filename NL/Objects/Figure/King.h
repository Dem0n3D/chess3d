#ifndef __NL_KING_H__
#define __NL_KING_H__

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

			class King : public Figure
			{
			public:

				King();
				~King();

				void Turn(Cell npos);

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);
				
			};

		};

	};

};

#endif