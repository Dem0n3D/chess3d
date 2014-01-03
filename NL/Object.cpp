#include "Object.h"

NL::Scene::Objects::Object::Object()
{
	Parent = NULL;

	Visible = true;
	Active	= true;

	M.Identity();

	Name = NL_T("Object");
};

NL::Scene::Objects::Object::~Object()
{

};

bool NL::Scene::Objects::Object::AttachChild(Object *pChild)
{
	pChild->Set_Parent(this);
	if(GetChild(pChild->Name))
		return false;
	else
		Childrens.push_back(pChild);

	return true;
};

NL::Scene::Objects::Object *NL::Scene::Objects::Object::GetChild(const NL::String &Name)
{
	std::list<Object *>::iterator it;

	for(it = Childrens.begin(); it != Childrens.end(); it++)
	{
		if((*it)->Name == Name)break;
	}

	if(it==Childrens.end()) return NULL;
	else 
		return (*it);
};

bool NL::Scene::Objects::Object::RemoveChild(const NL::String &Name)
{
	for(std::list<Object *>::iterator it = Childrens.begin(); it != Childrens.end(); it++)
	{
		if((*it)->Name == Name)
		{
			(*it)->ReleaseAll();
			Childrens.erase(it);
			return true;
		}
	}

	return false;
};

bool NL::Scene::Objects::Object::Release()
{
	Name.clear();
	Parent = NULL;
	Childrens.clear();	

	return true;
};

bool NL::Scene::Objects::Object::UpdateAll(float fElapsedTime)
{
	if(!Active)
		return false;

	for(std::list<Object *>::iterator it = Childrens.begin(); it != Childrens.end(); it++)
	{
		if(!((Object *)(*it))->UpdateAll(fElapsedTime))
			return false;
	}

	return Update(fElapsedTime);
}

bool NL::Scene::Objects::Object::RenderAll(WORD pass)
{
	if(!Visible)
		return false;

	//--------------------------------------------------------------------------------------

	OpenGL *ogl = OpenGL::getSingletonPtr();

	ogl->PushMatrix();
	ogl->LoadMatrix(M_WORLD,M);
	ogl->ApplyTransform();

	//--------------------------------------------------------------------------------------

	bool b = Render(pass);

	for(std::list<Object *>::iterator it = Childrens.begin(); it != Childrens.end(); it++)
	{
		((Object *)(*it))->RenderAll(pass);
	}

	//--------------------------------------------------------------------------------------

	ogl->PopMatrix();

	return b;
}

bool NL::Scene::Objects::Object::ReleaseAll()
{
	for(std::list<Object *>::iterator it = Childrens.begin(); it != Childrens.end(); it++)
	{
		if(!(*it)->ReleaseAll())
			return false;
	}

	return Release();
};

void NL::Scene::Objects::Object::Callback(WORD mt,std::vector<DWORD> param)
{
	for(std::list<Object *>::iterator it = Childrens.begin(); it != Childrens.end(); it++)
	{
		(*it)->Callback(mt,param);
	}
};

void NL::Scene::Objects::Object::Rotate(const Math::Vector3 &Angle)
{
	NL::Math::Matrix4x4 rx,ry,rz;
	M *= rx.RotateX(Angle.x) * ry.RotateY(Angle.y) * rz.RotateZ(Angle.z);
};

void NL::Scene::Objects::Object::Rotate(float x,float y,float z)
{
	Rotate(Math::Vector3(x,y,z));
};

void NL::Scene::Objects::Object::Move(const Math::Vector3 &Move)
{
	M[3][0] += Move.x;
	M[3][1] += Move.y;
	M[3][2] += Move.z;
};

void NL::Scene::Objects::Object::Move(float x,float y,float z)
{
	Move(Math::Vector3(x,y,z));
};

void NL::Scene::Objects::Object::SetPos(const Math::Vector3 &Pos)
{
	M[3][0] = Pos.x;
	M[3][1] = Pos.y;
	M[3][2] = Pos.z;
};

void NL::Scene::Objects::Object::SetPos(float x,float y,float z)
{
	SetPos(Math::Vector3(x,y,z));
};

void NL::Scene::Objects::Object::Scale(const Math::Vector3 &Scale)
{
	NL::Math::Matrix4x4 s;
	M *= s.Scale(Scale);
};

void NL::Scene::Objects::Object::Scale(float x,float y,float z)
{
	Scale(Math::Vector3(x,y,z));
};

//--------------------------------------------------------------------------------------

NL::Math::Matrix4x4 NL::Scene::Objects::Object::GetWorldTransform()
{
	NL::Math::Matrix4x4 tmp;
	tmp.Identity();

	Object *obj = this;

	while (obj)
	{
		tmp *= obj->M;
		obj = obj->Parent;
	}

	return tmp;
};