#include "Figure.h"

NL::Scene::Objects::Figure::Figure()
{
	
};

NL::Scene::Objects::Figure::~Figure()
{

};

void NL::Scene::Objects::Figure::Turn(Cell npos)
{
	pos = npos;
};

bool NL::Scene::Objects::Figure::Render(WORD pass)
{
	if(color == WHITE)
	{
		BYTE *whitecolor = ((BYTE *)ResourceManager::getSingleton().GetResourcePtr("White color"));
		glColor3ub(whitecolor[2],whitecolor[1],whitecolor[0]);

		//glColor3ub(200,200,200);
	}
	else
	{
		BYTE *blackcolor = ((BYTE *)ResourceManager::getSingleton().GetResourcePtr("Black color"));
		glColor3ub(blackcolor[2],blackcolor[1],blackcolor[0]);

		//glColor3ub(50,50,50);
	}

	Mesh::Render(pass);

	return true;
};

bool NL::Scene::Objects::Figure::Update(float fElapsedTime)
{
	M[3][0] = 2*pos.x-7.0f;
	M[3][2] = 2*pos.y-7.0f;

	Mesh::Update(fElapsedTime);

	return true;
};