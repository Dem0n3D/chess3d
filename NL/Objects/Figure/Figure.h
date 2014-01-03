#ifndef __NL_FIGURE_H__
#define __NL_FIGURE_H__

//--------------------------------------------------------------------------------------

#include "../../Common.h"

#include "../../Object.h"

#include "../Mesh/Mesh.h"

//--------------------------------------------------------------------------------------

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{		

			#define WHITE 1
			#define BLACK 0

			struct Cell // Клетка
			{
				Cell(){};
				Cell(BYTE X,BYTE Y):x(X),y(Y){};

				bool operator == (Cell c)
				{
					return (x == c.x) && (y == c.y);
				};

				bool operator != (Cell c)
				{
					return (x != c.x) || (y != c.y);
				};

				BYTE x,y;
			};

			struct Turn // Ход
			{
				Turn(){};
				Turn(Cell From,Cell To):from(From),to(To){};

				bool operator == (Turn t)
				{
					return (from == t.from) && (to == t.to);
				};

				bool operator != (Turn t)
				{
					return (from != t.from) || (to != t.to);
				};

				Cell from,to;
			};			

			class Figure : public Mesh
			{
			public:

				Figure();
				~Figure();

				virtual void Turn(Cell npos);

				virtual void AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos) = 0;

			protected:

				bool Render(WORD pass);
				bool Update(float fElapsedTime);

			public:				

				GET_SET_ACCESSOR(Cell,pos);
				GET_SET_ACCESSOR(bool,color);

			protected:

				bool color;

				Cell pos;

			};

		};

	};

};

#endif