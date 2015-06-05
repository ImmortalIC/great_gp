#include <gmock\gmock.h>
#include <base_interfaces.h>
class CRendererMock : public IRenderer
{
public:

	MOCK_METHOD0(Render, bool());
	MOCK_METHOD3(AddToQueue, void(UINT x, UINT y, ULONG resource));
	MOCK_METHOD3(InitRenderer, bool(HWND handle, UINT window_width, UINT window_height));

};