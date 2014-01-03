#ifndef __NL_PAWN_H__
#define __NL_PAWN_H__

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

			class Pawn : public Figure
			{
			public:

				Pawn();
				~Pawn();

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);
				void Turn(Cell npos);//, bool BP[8][8], bool TT[8][8]);
				void AllStrike(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);

			};

		};

	};

};

#endif