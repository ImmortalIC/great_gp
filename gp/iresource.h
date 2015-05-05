#define RES_GDI_BITMAP 0

class IResource
{
public:
	IResource(){ };
	virtual ~IResource(){};

	virtual void* getResource()=0;
	
};


typedef  std::shared_ptr < IResource > IResource_ptr;