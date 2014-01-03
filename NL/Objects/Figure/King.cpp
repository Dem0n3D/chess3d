#include "King.h"

NL::Scene::Objects::King::King()
{

};

NL::Scene::Objects::King::~King()
{
	
};

void NL::Scene::Objects::King::Turn(Cell npos)
{
	pos=npos;
	if (color == WHITE)
	{
		bool *b_w=false;
		ResourceManager::getSingleton().AddResource("mayrok_w",&b_w,sizeof(b_w));
	}
	else
	{
		bool *b_b=false;
		ResourceManager::getSingleton().AddResource("mayrok_b",&b_b,sizeof(b_b));
	}
};


void NL::Scene::Objects::King::AllTurns(Figure *B[8][8],bool T[8][8],bool BP[8][8],Cell Kingpos)
{
	if (pos.x-1>=0)
	{
		if (B[pos.x-1][pos.y] == 0)
		{
			if (BP[pos.x-1][pos.y] == 0)
			{
				T[pos.x-1][pos.y] = 1;
			}
		}
		else 
			if  (B[pos.x-1][pos.y]->Get_color() != color)
			{
					if (BP[pos.x-1][pos.y] == 0)
					{
						T[pos.x-1][pos.y] = 1;
					}
			}
	
		if (pos.y-1>=0) 
		{
			if (B[pos.x-1][pos.y-1] == 0)
			{ 
				if (BP[pos.x-1][pos.y-1] == 0)
				{
					T[pos.x-1][pos.y-1] = 1;
				}
			}
			else
			if  (B[pos.x-1][pos.y-1]->Get_color() != color)
			{
				if (BP[pos.x-1][pos.y-1] == 0)
				{
					T[pos.x-1][pos.y-1] = 1;
				}
			}
		}
		if (pos.y+1<8) 
		{
			if (B[pos.x-1][pos.y+1] == 0)
			{ 
				if (BP[pos.x-1][pos.y+1] == 0)
				{
					T[pos.x-1][pos.y+1] = 1;
				}
			}
			else 
			if  (B[pos.x-1][pos.y+1]->Get_color() != color)
			{
				if (BP[pos.x-1][pos.y+1] == 0)
				{
					T[pos.x-1][pos.y+1] = 1;
				}
			}
		}
	}
	if (pos.x+1<8)
	{
		if (B[pos.x+1][pos.y] == 0)	
		{ 
			if (BP[pos.x+1][pos.y] == 0)
			{
				T[pos.x+1][pos.y] = 1;
			}
		}
		else
			if  (B[pos.x+1][pos.y]->Get_color() != color)
			{
				if (BP[pos.x+1][pos.y] == 0)
				{
					T[pos.x+1][pos.y] = 1;
				}
			}
		if (pos.y-1>=0)
		{
			if (B[pos.x+1][pos.y-1] == 0)
			{
				if (BP[pos.x+1][pos.y-1] == 0)
				{
					T[pos.x+1][pos.y-1] = 1;
				}
			}
			else
			if  (B[pos.x+1][pos.y-1]->Get_color() != color)
			{
				if (BP[pos.x+1][pos.y-1] == 0)
				{
					T[pos.x+1][pos.y-1] = 1;
				}
			}
		}
		if (pos.y+1<8) 
			if (B[pos.x+1][pos.y+1] == 0)
			{ 
				if (BP[pos.x+1][pos.y+1] == 0)
				{
					T[pos.x+1][pos.y+1] = 1;
				}
			}
			else
			if  (B[pos.x+1][pos.y+1]->Get_color() != color)
				if (BP[pos.x+1][pos.y+1] == 0)
				{
					T[pos.x+1][pos.y+1] = 1;
				}
				
	}
	if (pos.y-1>=0) 
	{
		if (B[pos.x][pos.y-1] == 0)
		{
			if (BP[pos.x][pos.y-1] == 0)
			{
				T[pos.x][pos.y-1] = 1;
			}
		}
		else
			if  (B[pos.x][pos.y-1]->Get_color() != color)
				if (BP[pos.x][pos.y-1] == 0)
				{
					T[pos.x][pos.y-1] = 1;
				}
	}
	if (pos.y+1<8) 
	{
		if (B[pos.x][pos.y+1] == 0)
		{ 
			if (BP[pos.x][pos.y+1] == 0)
			{
				T[pos.x][pos.y+1] = 1;
			}
		}
		else
			if  (B[pos.x][pos.y+1]->Get_color() != color)
					if (BP[pos.x][pos.y+1] == 0)
					{
						T[pos.x][pos.y+1] = 1;
					}
	}
	bool *b2=(bool *)true;
	if (color == WHITE) 
		b2=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_w");
	else
		b2=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_b");
	if (*b2)
	{
		if (color == WHITE)  
		{
			if (B[6][0]==0 && B[5][0]==0 && BP[6][0]==0 && BP[5][0]==0)
			{
				bool *bt=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_r_r_w");
				if (*bt) T[6][0] = 1;
			}
			if (B[3][0]==0 && B[2][0]==0 && B[1][0]==0 && BP[3][0]==0 && BP[2][0]==0)
			{
				bool *bt=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_r_l_w");
				if (*bt) T[2][0] = 1;
			}
		}
		else
		{
			if (B[6][7] == 0  && B[5][7]==0 && BP[6][7] == 0  && BP[5][7]==0) 
			{
				bool *bt=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_r_r_b");
				if (*bt) T[6][7] = 1;
			}
			if (B[3][7]==0 && B[2][7]==0 && B[1][7]==0 && BP[3][7]==0 && BP[2][7]==0)
			{
				bool *bt=(bool *)ResourceManager::getSingleton().GetResourcePtr("mayrok_r_l_b");
				if (*bt) T[2][7] = 1;
			}
		}
		
	}
		
};