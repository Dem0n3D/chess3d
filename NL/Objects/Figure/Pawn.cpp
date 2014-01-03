#include "Pawn.h"

//--------------------------------------------------------------------------------------

#include <CEGUI.h>

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Pawn::Pawn()
{

};

NL::Scene::Objects::Pawn::~Pawn()
{

};


void NL::Scene::Objects::Pawn::Turn(Cell npos)
{
	/*if (color == WHITE)
	{
		if (npos.y==7) //вот здесь должна быть вызвана менюшка
		{
			CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(true);

			bool waiting = true;
			ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));
		}		
	}
	else
	{
		if (npos.y==0) //аналогично, только цвет другой
		{
			CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(true);

			bool waiting = true;
			ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));
		}
	}*/

	pos = npos;	
};

void NL::Scene::Objects::Pawn::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	//взятие на проходе)
	Objects::Turn *lt=(Objects::Turn *)ResourceManager::getSingleton().GetResourcePtr("Last Turn");
	if (lt)
	{
		String s1;
		s1="class NL::Scene::Objects::Pawn";
		String s = typeid(*B[lt->to.x][lt->to.y]).name();
		if(color == WHITE)
		{
			if (s1==s)
			{
				if(pos.y==4)
					if ( lt->from.y==6 && lt->to.y==4)
					{
						if (pos.x-1>=0 && lt->from.x==pos.x-1)
							T[lt->from.x][pos.y+1]=1;
						if (pos.x+1<8 && lt->from.x==pos.x+1)
							T[lt->from.x][pos.y+1]=1;
					}
			}
		}
		else
		{
			if (s1==s)
			{
				if (pos.y==3)
					if ( lt->from.y==1 && lt->to.y==3)
					{
						if (pos.x-1>=0 && lt->from.x==pos.x-1)
							T[lt->from.x][pos.y-1]=1;
						if (pos.x+1<8 && lt->from.x==pos.x+1)
							T[lt->from.x][pos.y-1]=1;
					}
			}

		}
	}
	if(color == WHITE)
		{
			if (pos.y==1)
				if ( B[pos.x][pos.y+1]==0 && B[pos.x][pos.y+2]==0 )
					T[pos.x][pos.y+2] = 1;
			if (pos.y+1<8)
				if ( B[pos.x][pos.y+1]==0 )
					T[pos.x][pos.y+1] = 1;
			if (pos.y+1<8 && pos.x+1<8)
				if ( B[pos.x+1][pos.y+1] && B[pos.x+1][pos.y+1]->Get_color() == BLACK)
					T[pos.x+1][pos.y+1] = 1;
			if (pos.y+1<8 && pos.x-1>=0)
				if ( B[pos.x-1][pos.y+1] && B[pos.x-1][pos.y+1]->Get_color() == BLACK)
					T[pos.x-1][pos.y+1] = 1;		
		}
		else
		{
			if (pos.y==6)
				if ( B[pos.x][pos.y-1]==0 && B[pos.x][pos.y-2]==0 )
					T[pos.x][pos.y-2] = 1;
			if (pos.y-1>=0)
				if ( B[pos.x][pos.y-1]==0 )
					T[pos.x][pos.y-1] = 1;
			if (pos.y-1>=0 && pos.x+1<8)
				if ( B[pos.x+1][pos.y-1] && B[pos.x+1][pos.y-1]->Get_color() == WHITE)
					T[pos.x+1][pos.y-1] = 1;
			if (pos.y-1>=0 && pos.x-1>=0)
				if ( B[pos.x-1][pos.y-1] && B[pos.x-1][pos.y-1]->Get_color() == WHITE)
					T[pos.x-1][pos.y-1] = 1;	
		}
};
void NL::Scene::Objects::Pawn::AllStrike(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	if(color == WHITE)
	{
		if (pos.y+1<8 && pos.x+1<8)
			if ( B[pos.x+1][pos.y+1]==0 || B[pos.x+1][pos.y+1]->Get_color() == BLACK)
				T[pos.x+1][pos.y+1] = 1;
		if (pos.y+1<8 && pos.x-1>=0)
			if ( B[pos.x-1][pos.y+1]==0 || B[pos.x-1][pos.y+1]->Get_color() == BLACK)
				T[pos.x-1][pos.y+1] = 1;		
	}
	else
	{	if (pos.y-1>=0 && pos.x+1<8)
			if ( B[pos.x+1][pos.y-1]==0 || B[pos.x+1][pos.y-1]->Get_color() == WHITE)
				T[pos.x+1][pos.y-1] = 1;
		if (pos.y-1>=0 && pos.x-1>=0)
			if ( B[pos.x-1][pos.y-1]==0 || B[pos.x-1][pos.y-1]->Get_color() == WHITE)
				T[pos.x-1][pos.y-1] = 1;	
	}
};