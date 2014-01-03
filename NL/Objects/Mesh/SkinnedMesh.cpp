#include "SkinnedMesh.h"

//--------------------------------------------------------------------------------------

#include "../../Utils/TinyXML/tinyxml.h"

//--------------------------------------------------------------------------------------

#define SKLT			0x0065 // Скелет (текстовый)
#define WTBL			0x0066 // Таблица весов
#define ANIM			0x0067 // Таблица весов
#define END				0x1000

//--------------------------------------------------------------------------------------

NL::Scene::Objects::SkinnedMesh::SkinnedMesh()
{

};

NL::Scene::Objects::SkinnedMesh::~SkinnedMesh()
{

};

void NL::Scene::Objects::SkinnedMesh::Load(const String &filename,const String &skinname)
{
	/*using namespace std;
	using namespace NL::Math;
	using namespace TinyXML;

	Mesh::Load(filename);

	TiXmlDocument scene(filename);
	scene.LoadFile();

	TiXmlElement *obj = scene.FirstChild("Scene")->FirstChild("Objects")->FirstChild("Object")->FirstChild("Mesh")->FirstChildElement("Weights");

	int vcount;

	obj->QueryValueAttribute("count",&vcount);

	wtbl.Initialize(vcount);

	istringstream istr(obj->GetText());

	for (int i = 0; i < vcount; i++)
	{	
		int wcount;

		istr >> wcount;

		for (int j = 0; j < wcount; j++)
		{
			int bid;
			float weight;

			istr >> bid >> weight;

			wtbl.AddWeight(i,bid,weight);
		}
	}*/

	//--------------------------------------------------------------------------------------
/*TiXmlDocument dc(skinname);
	dc.LoadFile();
TiXmlNode *n = dc.FirstChild("Skeleton");

	n = n->LastChild();
	obj = n->FirstChildElement("Animation");

	obj->QueryValueAttribute("start",&start);
	obj->QueryValueAttribute("end",&end);

	obj = obj->FirstChildElement("Bone");

	while (obj)
	{
		Bone *bone = new Bone();

		obj->QueryValueAttribute("id",&bone->ID);

		TiXmlElement *kframe = obj->FirstChild("Keyframes")->FirstChildElement("Keyframe");

		while (kframe)
		{
			kframe = kframe->NextSiblingElement();
		}

		obj = obj->NextSiblingElement();
	}*/
};

bool NL::Scene::Objects::SkinnedMesh::Render(WORD pass)
{
//	OpenGL::getSingleton().SetColor(255,255,255);

	/*OpenGL::getSingleton().SetVertexStreamsCount(1);
	OpenGL::getSingleton().SetIndexStreamsCount(1);
	OpenGL::getSingleton().SetVertexArray(0,&tVerts);
	OpenGL::getSingleton().SetIndexArray(0,&geom.Inds);

	OpenGL::getSingleton().SetTexture(geom.textureID[0]);
	OpenGL::getSingleton().SetTexCoordArray(0,&geom.Tcs[0]);

	OpenGL::getSingleton().DrawIndexedPrimitive(0,0,geom.Inds.size());		*/

	return true;
};

bool NL::Scene::Objects::SkinnedMesh::Update(float fElapsedTime)
{
	/*static int frame = 0;

	std::vector<Bone> tBones = frames[frame];

	tVerts = geom.Verts;

	static float tm = 0;
	tm += fElapsedTime*1000.0f;

	float speed = 25.0f;

	int c = geom.Verts.size();
	for(int i = 0; i < c; i++)
	{
		int cn = wtbl[i].BWeights.size();

		Math::Matrix3x3 M;
		Math::Vector3 pos(0,0,0);
		M.Nil();

		for(int j = 0; j <cn ; j++)
		{	
			M += tBones[wtbl[i][j].ID].rot*wtbl[i][j].Weight;		
			pos += tBones[wtbl[i][j].ID].pos*wtbl[i][j].Weight;
			//tVerts[i] += (geom.Verts[i]*frames[frame][wtbl[i][j].ID].M+frames[frame][wtbl[i][j].ID].pos)*wtbl[i][j].Weight;
		}

		tVerts[i] = geom.Verts[i]*M+pos;
	}

	if(frame >= frames.size()-1)
		frame = 0;

	if(tm*speed >= 1)
	{
		frame++;
		tm = 0;
	}*/
	//frame = (frame < frames.size()-1) ? frame+1 : 0;

	return true;
};