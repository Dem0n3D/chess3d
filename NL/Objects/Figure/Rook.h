#ifndef __NL_ROOK_H__
#define __NL_ROOK_H__

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

			class Rook : public Figure
			{
			public:

				Rook();
				~Rook();

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);
	
			};

		};

	};

};

#endif