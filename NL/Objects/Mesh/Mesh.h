#ifndef __NL_MESH_H__
#define __NL_MESH_H__

//--------------------------------------------------------------------------------------

#include "../../Common.h"

#include "../../Object.h"

#include "../../ResourceManager.h"

////////////////////////////////////////////////////////////////////////////////////////

namespace NL
{

	namespace Scene
	{

		namespace Objects
		{

			class Mesh : public Object
			{
			public:

				Mesh();
				~Mesh();

				virtual void Load(const String &filename,const String &modelname);
			
				void SetTexture(const String &filename);

				GET_SET_ACCESSOR(bool,bUseVBO);

			public:

				// Связанные исключения

				class CorruptedFile : public Exception // Повреждённый или неподдерживаемый файл
				{
				public:

					CorruptedFile():Exception("File is corrupted!"){};
					explicit CorruptedFile(const String &message):Exception(message){};
				};

				class ModelDoesNotLoaded : public Exception // Модель не загружена
				{
				public:

					ModelDoesNotLoaded():Exception("Model does not loaded!"){};
					explicit ModelDoesNotLoaded(const String &message):Exception(message){};
				};

			protected:

				bool Render(WORD pass);
				bool Update(float fElapsedTime);
				bool Release();

			protected:

				bool bUseVBO,bVBOInitialized;

				String FMname;

			};

		};

	};


};

#endif