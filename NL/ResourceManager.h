#ifndef __NL_RESOURCE_MANAGER_H__
#define __NL_RESOURCE_MANAGER_H__

//--------------------------------------------------------------------------------------

#include "Common.h"

#include "Log.h"

#include "Singleton.h"

#include "Exception.h"

////////////////////////////////////////////////////////////////////////////////////////

//Мэнеджер ресурсов

namespace NL
{	

	enum RESOURCE_TYPE { RT_MODEL = 0x01, RT_TEXTURE = 0x10 };

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:

		ResourceManager();
		~ResourceManager();

	public:

		bool GetResource(const String &name,void *buffer);
		bool GetResourcePtr(const String &name,void **ptr);

		void *GetResourcePtr(const String &name);

		int GetResourceSize(const String &name);

		bool AddResource(const String &name,void *buffer,size_t size);

		bool DeleteResource(const String &name);

	// Связанные исключения

		class ResourceManagerNotInitialized : public Exception
		{
		public:

			ResourceManagerNotInitialized():Exception("Resource manager not initialized!"){};
		};

	private:

		struct Resource 
		{
			void *Data;
			size_t size;
		};

		std::map<String,Resource> resources;

	};

};

#endif