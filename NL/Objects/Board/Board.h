#ifndef __NL_BOARD_H__
#define __NL_BOARD_H__

//--------------------------------------------------------------------------------------

#include "../../Common.h"

#include "../../Object.h"

#include "../Figure/Figure.h"

#include "../Figure/Pawn.h"
#include "../Figure/King.h"
#include "../Figure/Queen.h"
#include "../Figure/Horse.h"
#include "../Figure/Bishop.h"
#include "../Figure/Rook.h"

//--------------------------------------------------------------------------------------

#include <CEGUI.h>

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			#define RENDER_PASS_MAIN 0
			#define RENDER_PASS_SELECT 1
			
			#define EVENT_TURN 1000

			class Board : public Object
			{
			public:

				Board();
				~Board();

				void Initialize();

				void MakeTurn(Cell from,Cell to);

				bool UpdateAll(float fElapsedTime);

				//--------------------------------------------------------------------------------------

				void Click(void *args);

				Figure *at(Cell c) const;

			protected:

				bool Render(WORD pass);
				bool Update(float fElapsedTime);
				bool Release();

			private:

				bool player;

				Cell pick,selected;

				Figure *B[8][8];

				King *b_king, *w_king;
				
				bool strikewh[8][8];
				bool strikebl[8][8];

				int Fcnt[2][6];

				GLuint quads_vbo_id;

				Mesh *bound;

			public:

				std::vector<Turn> turns_list;

			private:

				void DrawQuad(int x,int y);

				bool ChangeToQueen(const CEGUI::EventArgs &e);
				bool ChangeToHorse(const CEGUI::EventArgs &e);
				bool ChangeToRook(const CEGUI::EventArgs &e);
				bool ChangeToBishop(const CEGUI::EventArgs &e);
				
				void MayTurn(Figure *B[8][8], bool T[8][8],Cell p);
				bool Shax(bool M[8][8],Cell p);
				void Strike(Figure *B[8][8], bool strikewh[8][8], bool strikebl[8][8], King *w_king, King *b_king);

			};

		};

	};

};

#endif