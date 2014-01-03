#include "Queen.h"

NL::Scene::Objects::Queen::Queen()
{

};

NL::Scene::Objects::Queen::~Queen()
{

};

void NL::Scene::Objects::Queen::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
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