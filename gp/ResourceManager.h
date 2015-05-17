#pragma once
#include <vector>
#include "all_resources.h"
#include "base_interfaces.h"

class CResourceManager: public IResourceManager
{
public:
	CResourceManager();
	~CResourceManager();
	IResource_ptr operator[](UINT index);
	UINT addResource(UINT type, const LPCTSTR path);
	void CleanOld();
	
private:
	std::vector<std::pair<IResource_ptr,ULONG>> resources;

};

