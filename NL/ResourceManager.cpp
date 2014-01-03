#include "ResourceManager.h"

//--------------------------------------------------------------------------------------

NL::ResourceManager* NL::Singleton<NL::ResourceManager>::ms_Singleton = 0;

//--------------------------------------------------------------------------------------

NL::ResourceManager::ResourceManager()
{

};

NL::ResourceManager::~ResourceManager()
{

};

bool NL::ResourceManager::GetResource(const String &name,void *buffer)
{
	if(!resources[name].Data)
		return false;

	memcpy(buffer,resources[name].Data,resources[name].size);

	return true;
};

bool NL::ResourceManager::GetResourcePtr(const String &name,void **ptr)
{
	if(!resources[name].Data)
		return false;

	*ptr = resources[name].Data;

	return true;
};

void *NL::ResourceManager::GetResourcePtr(const String &name)
{
	return resources[name].Data;
};

int NL::ResourceManager::GetResourceSize(const String &name)
{
	if(!resources[name].Data)
		return -1;

	return (int)resources[name].size;
};

bool NL::ResourceManager::AddResource(const String &name,void *buffer,size_t size)
{
	if(resources[name].Data)
	{
		DeleteResource(name);
	}

	resources[name].Data = malloc(size);
	memcpy(resources[name].Data,buffer,size);
	resources[name].size = size;

	return true;
};

bool NL::ResourceManager::DeleteResource(const String &name)
{
	free(resources[name].Data);
	resources.erase(name);

	return true;
};