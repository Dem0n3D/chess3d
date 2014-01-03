#include "Mesh.h"

//--------------------------------------------------------------------------------------

#include "../../Utils/TinyXML/tinyxml.h"

#include "../../System.h"

//--------------------------------------------------------------------------------------

#include <zlib.h>

#ifdef _WIN32

	#ifdef _DEBUG
		#pragma comment(lib,"zlibd.lib")
	#else
		#pragma comment(lib,"zlib.lib")
	#endif

#endif

//--------------------------------------------------------------------------------------

// #define M3DT			0x0001
// #define M3DB			0x0002
// 
// #define TNAME			0x0003
// #define OBJECT			0x0004
// //#define NAME			0x0005
// #define VERTICES		0x0006
// #define INDEXES			0x0007
// #define TEXTURE			0x0008
// #define TCOORDS			0x0009
// #define END				0x1000

//--------------------------------------------------------------------------------------
// Флаги

#define TEXCOORDS0	0x0001
#define NORMALS		0x0010
#define VERTEXES	0x0100
#define INDEXES		0x1000

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Mesh::Mesh()
{
	FMname = "";

	bUseVBO = bVBOInitialized = false;
};

NL::Scene::Objects::Mesh::~Mesh()
{

};

void NL::Scene::Objects::Mesh::Load(const String &filename,const String &modelname)
{
	using namespace std;
	using namespace NL::Math;
	using namespace TinyXML;

	//--------------------------------------------------------------------------------------

	ResourceManager *rm = ResourceManager::getSingletonPtr();

	if (!rm)
		throw(ResourceManager::ResourceManagerNotInitialized()); // Не инициализирован менеджер ресурсов

	WORD flags = 0;

	FMname = filename+"|"+modelname;

	if (rm->GetResource(FMname+":"+"Flags",&flags))
	{
		rm->GetResource(FMname+":"+"Transformation",&M); // Попробуем достать матрицу транформации

		return;
	}

	//--------------------------------------------------------------------------------------

	// Не будем сдесь генерить ВБО, чтоб он не висел в видеопамяти без дела
	// Здесь только загрузим флаги|вершины|нормали|индексы в менеджер ресурсов

	//--------------------------------------------------------------------------------------

	// Считываем, декомпрессим

	ifstream fi(filename.c_str(),ios_base::binary); 

	size_t unc_size,comp_size; // размеры: несжатый и сжатый

	fi.read((char *)&unc_size,sizeof(unc_size));
	fi.read((char *)&comp_size,sizeof(comp_size));

	BYTE *unc_str = new BYTE[unc_size]; // несжатая строка
	BYTE *comp_str = new BYTE[comp_size]; // сжатая строка

	fi.read((char *)comp_str,(std::streamsize)comp_size);

	int n = uncompress((Bytef *)unc_str,(uLongf *)&unc_size,(const Bytef *)comp_str,(uLong)comp_size);

	fi.close();	

	//--------------------------------------------------------------------------------------

	TiXmlDocument scene(filename);
	scene.Parse((char *)unc_str);

	delete[] comp_str;
	delete[] unc_str;

	TiXmlNode *obj = scene.FirstChild("Scene");

	if (!obj)
		throw(CorruptedFile(FMname + " - Can't find section \"Scene\"!"));

	obj = obj->FirstChild("Objects");

	if (!obj)
		throw(CorruptedFile(FMname + " - Can't find section \"Objects\"!"));

	obj = obj->FirstChild("Object");

	String name;

	do
	{
		obj->ToElement()->QueryValueAttribute("name",&name);
	
	} while ((name != modelname) && (obj = obj->NextSibling())); // Ищем нужный объект

	if (!obj)
		throw(CorruptedFile(FMname + " - Can't find required object!"));

	Set_Name(name);

	//--------------------------------------------------------------------------------------

	TiXmlElement *mesh = obj->FirstChildElement("Mesh");

	if (!mesh)
		throw(CorruptedFile(FMname + " - Can't find section \"Mesh\"!"));

	//--------------------------------------------------------------------------------------

	TiXmlElement *elem = mesh->FirstChildElement("Vertexes"); // Достаём вершины

	if (elem)
	{
		flags |= VERTEXES;

		int vcount;
		elem->QueryValueAttribute("count",&vcount);

		istringstream istr(elem->GetText());

		vector<Vector3> Verts(vcount);

		for(int i = 0; i < vcount; i++)
		{
			istr >> Verts[i].x >> Verts[i].y >> Verts[i].z; 
		}

		rm->AddResource(FMname+":"+"Verts",&Verts[0],vcount*sizeof(Vector3));

		istr.clear();
	}

	//--------------------------------------------------------------------------------------

	elem = mesh->FirstChildElement("Faces"); // Достаём индексы треугольников

	if (elem)
	{
		flags |= INDEXES;

		int fcount;
		elem->QueryValueAttribute("count",&fcount);

		istringstream istr(elem->GetText());

		vector<WORD> Inds(fcount*3);

		for(int i = 0; i < fcount*3; i += 3)
		{
			istr >> Inds[i+0] >> Inds[i+1] >> Inds[i+2]; 
		}

		rm->AddResource(FMname+":"+"Inds",&Inds[0],fcount*3*sizeof(WORD));

		istr.clear();
	}

	//--------------------------------------------------------------------------------------

	elem = mesh->FirstChildElement("Normals"); // Достаём вершины

	if (elem)
	{
		flags |= NORMALS;

		int ncount;
		elem->QueryValueAttribute("count",&ncount);

		istringstream istr(elem->GetText());

		vector<Vector3> Norms(ncount);

		for(int i = 0; i < ncount; i++)
		{
			istr >> Norms[i].x >> Norms[i].y >> Norms[i].z; 
		}

		rm->AddResource(FMname+":"+"Norms",&Norms[0],ncount*sizeof(Vector3));

		istr.clear();
	}

	//--------------------------------------------------------------------------------------

	// Тута нужно добавить ещё обработку текстурных координат и ещё чё-нибудь :)

	rm->AddResource(FMname+":"+"Flags",&flags,sizeof(flags)); // Запишем флаги

	//--------------------------------------------------------------------------------------

	TiXmlElement *trans = obj->FirstChildElement("Transformation");

	if (!trans)
		throw(CorruptedFile(FMname + " - Can't find section \"Transformation\"!"));

	Vector3 pos,scale;
	Quaternion rot;

	trans->FirstChildElement("Position")->QueryValueAttribute("x",&pos.x);
	trans->FirstChildElement("Position")->QueryValueAttribute("y",&pos.y);
	trans->FirstChildElement("Position")->QueryValueAttribute("z",&pos.z);

	trans->FirstChildElement("Scale")->QueryValueAttribute("x",&scale.x);
	trans->FirstChildElement("Scale")->QueryValueAttribute("y",&scale.y);
	trans->FirstChildElement("Scale")->QueryValueAttribute("z",&scale.z);

	trans->FirstChildElement("Orientation")->QueryValueAttribute("x",&rot.v.x);
	trans->FirstChildElement("Orientation")->QueryValueAttribute("y",&rot.v.y);
	trans->FirstChildElement("Orientation")->QueryValueAttribute("z",&rot.v.z);
	trans->FirstChildElement("Orientation")->QueryValueAttribute("w",&rot.w);

	Matrix3x3 m = QuaternionToMatrix3x3(rot);

	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;

	M[0] = Vector4(m[0],0);
	M[1] = Vector4(m[1],0);
	M[2] = Vector4(m[2],0);
	M[3] = Vector4(pos,1);

	M.Identity(); // Не тру! :-(

	rm->AddResource(FMname+":"+"Transformation",&M,sizeof(Matrix4x4)); // Запишем матрицу трансформации

	//--------------------------------------------------------------------------------------

	scene.Clear();
};

void NL::Scene::Objects::Mesh::SetTexture(const String &filename)
{
	/*if(!rm->GetResource(filename.c_str(),&geom.textureID[0]))
	{
		geom.textureID[0] = OpenGL::getSingleton().LoadTexture(filename.c_str());
		rm->AddResource(filename.c_str(),&geom.textureID[0],sizeof(geom.textureID[0]));
		rm->DeleteResource(filename.c_str());
	}*/
};

bool NL::Scene::Objects::Mesh::Render(WORD pass)
{
	using namespace std;
	using namespace Math;

	//--------------------------------------------------------------------------------------

	ResourceManager *rm = ResourceManager::getSingletonPtr();

	WORD flags = 0;

	if (!rm->GetResource(FMname+":"+"Flags",&flags))
		throw(ModelDoesNotLoaded(FMname + " - Model does not loaded!"));

	////////////////////////////////////////////////////////////////////////////////////////

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	////////////////////////////////////////////////////////////////////////////////////////

	if (bUseVBO) // Выводим с бУферами
	{
		GLuint vbo[4];

		if (!bVBOInitialized)
		{
			glGenBuffersARB(4,vbo);

			//--------------------------------------------------------------------------------------

			if (flags & VERTEXES)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,vbo[0]);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB,rm->GetResourceSize(FMname+":"+"Verts"),rm->GetResourcePtr(FMname+":"+"Verts"),GL_STATIC_DRAW_ARB);
			}

			//--------------------------------------------------------------------------------------

			if (flags & NORMALS)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,vbo[1]);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB,rm->GetResourceSize(FMname+":"+"Norms"),rm->GetResourcePtr(FMname+":"+"Norms"),GL_STATIC_DRAW_ARB);
			}

			//--------------------------------------------------------------------------------------

			if (flags & INDEXES)
			{
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo[2]);
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,rm->GetResourceSize(FMname+":"+"Inds"),rm->GetResourcePtr(FMname+":"+"Inds"),GL_STATIC_DRAW_ARB);
			}

			//--------------------------------------------------------------------------------------

			rm->AddResource(FMname+":"+"VBO",vbo,4*sizeof(GLuint)); // Запишем индексы буферов

			bVBOInitialized = true;
		}

		//--------------------------------------------------------------------------------------

		rm->GetResource(FMname+":"+"VBO",vbo);

		//--------------------------------------------------------------------------------------

		if (flags & VERTEXES)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,vbo[0]);
			glVertexPointer(3,GL_FLOAT,0,NULL);
		}

		//--------------------------------------------------------------------------------------

		if (flags & NORMALS)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,vbo[1]);
			glNormalPointer(GL_FLOAT,0,NULL);
		}

		//--------------------------------------------------------------------------------------

		if (flags & INDEXES)
		{
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,vbo[2]);
			glDrawElements(GL_TRIANGLES,rm->GetResourceSize(FMname+":"+"Inds")/2,GL_UNSIGNED_SHORT,0);
		}

		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0); // Отключаем вывод из бУферов
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}
	else // Выводим буз бУферов
	{
		if (flags & VERTEXES)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,GL_FLOAT,0,rm->GetResourcePtr(FMname+":"+"Verts"));
		}

		//--------------------------------------------------------------------------------------

		if (flags & NORMALS)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT,0,rm->GetResourcePtr(FMname+":"+"Norms"));
		}

		//--------------------------------------------------------------------------------------

		if (flags & INDEXES)
		{
			glDrawElements(GL_TRIANGLES,rm->GetResourceSize(FMname+":"+"Inds")/2,GL_UNSIGNED_SHORT,rm->GetResourcePtr(FMname+":"+"Inds"));
		}
	}

	return true;
};

bool NL::Scene::Objects::Mesh::Update(float fElapsedTime)
{
	return true;
};

bool NL::Scene::Objects::Mesh::Release()
{
	if (bUseVBO) // Выводим с бУферами
	{
		GLuint vbo[4];
		ResourceManager::getSingletonPtr()->GetResource(FMname+":"+"VBO",vbo);

		glDeleteBuffersARB(1,vbo);
	}

	return true;
};