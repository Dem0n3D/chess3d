#include "Rook.h"

NL::Scene::Objects::Rook::Rook()
{

};

NL::Scene::Objects::Rook::~Rook()
{

};

void NL::Scene::Objects::Rook::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	int i=pos.y+1;
	while (i<8)
	{
		if (B[pos.x][i]==0) T[pos.x][i] = 1;
		else 
		{if (B[pos.x][i]->Get_color() !=color) T[pos.x][i] = 1; 
		break;}
		i++;
	}
	if (pos.y-1>=0)
	{
		i=pos.y-1;
		while (i>=0)
		{
			if (B[pos.x][i]==0) T[pos.x][i] = 1;
			else 
			{if (B[pos.x][i]->Get_color() !=color) T[pos.x][i] = 1; 
			break;}
			i--;
		}
	}
	if (pos.x-1>=0)
	{
		i=pos.x-1;
		while (i>=0)
		{
			if (B[i][pos.y]==0) T[i][pos.y] = 1;
			else 
			{if (B[i][pos.y]->Get_color() !=color) T[i][pos.y] = 1;
			break;}
			i--;
		}
	}
	i=pos.x+1;
	while (i<8)
	{
		if (B[i][pos.y]==0) T[i][pos.y] = 1;
		else {if (B[i][pos.y]->Get_color() !=color) T[i][pos.y] = 1;
		break;}
		i++;
	}

};