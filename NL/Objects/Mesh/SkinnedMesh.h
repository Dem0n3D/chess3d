#ifndef __NL_SKINNED_MESH_H__
#define __NL_SKINNED_MESH_H__

#include "Mesh.h"

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class SkinnedMesh : public Mesh
			{
			public:

				SkinnedMesh();
				~SkinnedMesh();

				void Load(const String &filename,const String &skinname);

			protected:

				bool Render(WORD pass);
				bool Update(float fElapsedTime);

			protected:

				/*struct WTable 
				{
					struct VWeights
					{
						struct IW 
						{
							DWORD ID;
							String Name;
							float Weight;
						};

						std::vector<IW> BWeights;

						IW &operator [] (size_t n)	{ return BWeights[n]; };
					};

					std::vector<VWeights> VBWeights;

					VWeights &operator [] (size_t n)	{ return VBWeights[n]; };
				} wtbl;	*/

				//--------------------------------------------------------------------------------------

				struct Bone
				{					
					String Name;
					DWORD ID;

					std::list<Bone *> childrens;

					struct Frame 
					{
						Math::Matrix3x3 rot;
						Math::Vector3 pos;

						int time;
					};

					std::vector<Frame> keyframes;
				};	

				std::vector<Bone *> bones;

				int start,end;

				/*struct Animation 
				{
					String Name;

					struct Frame 
					{
						int bone_id;

						Math::Matrix3x3 rot;
						Math::Vector3 pos;

						int time;
					};

					vector<Frame> frames;
				} anim1;*/

				/*struct Skeleton
				{
					Bone *Root;

					Bone *GetBoneByName();
					Bone *GetBoneByID();
				} skl;*/

				struct WTable // Таблица весов 
				{

					struct bone
					{
						bone(int ID,float W):id(ID),w(W){};

						int id;
						float w;
					};

					//--------------------------------------------------------------------------------------

					void Initialize(size_t vnum)
					{
						weights.resize(vnum);
					};

					void AddWeight(int v,int b_id,float w) // Добавляет новый вес к v'ой вершине
					{
						weights[v].push_back(bone(b_id,w));
					};

					std::vector<bone> &operator [] (size_t n)	{ /*Сделать проверку на выход за пределы!!!*/ return weights[n]; };

				private:					

					std::vector< std::vector<bone> > weights; // Для каждой вершины будет список идентификаторов костей с их весами

				} wtbl;

				//--------------------------------------------------------------------------------------

				std::vector<Math::Vector3> tVerts;

			};

		};

	};


};

#endif