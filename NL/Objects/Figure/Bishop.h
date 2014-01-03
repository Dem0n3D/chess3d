#ifndef __NL_BISHOP_H__
#define __NL_BISHOP_H__

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

			class Bishop : public Figure
			{
			public:

				Bishop();
				~Bishop();

				void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos);

			};

		};

	};

};

#endif