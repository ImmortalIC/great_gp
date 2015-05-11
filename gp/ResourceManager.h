#pragma once
#include <vector>
#include "all_resources.h"


class CResourceManager
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

