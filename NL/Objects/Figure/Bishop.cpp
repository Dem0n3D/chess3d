#include "Bishop.h"

NL::Scene::Objects::Bishop::Bishop()
{

};

NL::Scene::Objects::Bishop::~Bishop()
{

};

void NL::Scene::Objects::Bishop::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	int x1=pos.x+1,y1=pos.y+1;
	while (x1<8 && y1<8)
	{
		if (B[x1][y1]==0) T[x1][y1] = 1;
		else 
		{if (B[x1][y1]->Get_color() !=color) T[x1][y1] = 1; 
		break;}
		x1++; y1++;
	}
	if (pos.y-1>=0)
	{
		x1=pos.x+1,y1=pos.y-1;
		while (x1<8 && y1>=0)
		{
			if (B[x1][y1]==0) T[x1][y1] = 1;
			else 
			{if (B[x1][y1]->Get_color() !=color) T[x1][y1] = 1; 
			break;}
			x1++; y1--;
		}
	}
	if (pos.x-1>=0)
	{
		x1=pos.x-1,y1=pos.y+1;
		while (x1>=0 && y1<8)
		{
			if (B[x1][y1]==0) T[x1][y1] = 1;
			else 
			{if (B[x1][y1]->Get_color() !=color) T[x1][y1] = 1; 
			break;}
			x1--; y1++;
		}
	}
	if (pos.y-1>=0 && pos.x-1>=0)
	{
		x1=pos.x-1,y1=pos.y-1;
		while (x1>=0 && y1>=0)
		{
			if (B[x1][y1]==0) T[x1][y1] = 1;
			else 
			{if (B[x1][y1]->Get_color() !=color) T[x1][y1] = 1; 
			break;}
			x1--; y1--;
		}
	}

};