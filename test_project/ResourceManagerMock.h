#include <gmock\gmock.h>
#include <base_interfaces.h>

class CResourceManagerMock : public IResourceManager
{
public:
	MOCK_METHOD2(addResource, UINT(UINT type, const LPCTSTR path));
	virtual IResource_ptr operator[](UINT index) { return nullptr; };
	~CResourceManagerMock(){};
	virtual void CleanOld() {};
};
