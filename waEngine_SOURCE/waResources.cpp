#include "waResources.h"

namespace wa
{
	std::map<std::wstring, Resource*> Resources::mResources = {};

	void Resources::Release()
	{
		for (auto& pair : mResources)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

}