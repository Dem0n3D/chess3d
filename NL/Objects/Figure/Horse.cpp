#include "Horse.h"

NL::Scene::Objects::Horse::Horse()
{

};

NL::Scene::Objects::Horse::~Horse()
{

};

void NL::Scene::Objects::Horse::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	if (pos.x-1>=0 && pos.y+2<8) 
	{
		if (B[pos.x-1][pos.y+2]==0)
			T[pos.x-1][pos.y+2] = 1;
		else 
			if (B[pos.x-1][pos.y+2]->Get_color() != color)
				T[pos.x-1][pos.y+2] = 1; 
	}
	if (pos.x+1<8 && pos.y+2<8) 
	{
		if (B[pos.x+1][pos.y+2]==0)
			T[pos.x+1][pos.y+2] = 1;
		else
			if (B[pos.x+1][pos.y+2]->Get_color() != color)
				T[pos.x+1][pos.y+2] = 1;
	}
	if (pos.x+2<8 && pos.y+1<8) 
	{
		if (B[pos.x+2][pos.y+1]==0)
			T[pos.x+2][pos.y+1] = 1;
		else 
			if (B[pos.x+2][pos.y+1]->Get_color() != color)
				T[pos.x+2][pos.y+1] = 1;
	}
	if (pos.x+2<8 && pos.y-1>=0) 
	{
		if (B[pos.x+2][pos.y-1]==0)
			T[pos.x+2][pos.y-1] = 1;
		else
			if (B[pos.x+2][pos.y-1]->Get_color() != color)
				T[pos.x+2][pos.y-1] = 1;
	}
	if (pos.x+1<8 && pos.y-2>=0) 
	{
		if (B[pos.x+1][pos.y-2]==0)
			T[pos.x+1][pos.y-2] = 1;
		else 
			if (B[pos.x+1][pos.y-2]->Get_color() != color )
				T[pos.x+1][pos.y-2] = 1; 
	}
	if (pos.x-1>=0 && pos.y-2>=0) 
	{
		if (B[pos.x-1][pos.y-2]==0)
			T[pos.x-1][pos.y-2] = 1;
		else
			if (B[pos.x-1][pos.y-2]->Get_color() != color)
				T[pos.x-1][pos.y-2] = 1;
	}
	if (pos.x-2>=0 && pos.y-1>=0) 
	{
		if (B[pos.x-2][pos.y-1]==0)
			T[pos.x-2][pos.y-1] = 1;
		else 
			if (B[pos.x-2][pos.y-1]->Get_color() != color)
				T[pos.x-2][pos.y-1] = 1;
	}
	if (pos.x-2>=0 && pos.y+1<8) 
	{
		if (B[pos.x-2][pos.y+1]==0)
			T[pos.x-2][pos.y+1] = 1;
		else 
			if (B[pos.x-2][pos.y+1]->Get_color() !=color)
				T[pos.x-2][pos.y+1] = 1;
	}
};