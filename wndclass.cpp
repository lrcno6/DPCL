#include"wndclass.h"
#include"wnd.h"
using namespace dpcl;
Wndclass dpcl::def_wndclass({
	sizeof(WNDCLASSEXA),	// cbSize
	0,						// style
	Window::wndproc,		// lpfnWndProc
	0,						// cbClsExtra
	0,						// cbWndExtra
	nullptr,				// hInstance
	nullptr,				// hIcon
	nullptr,				// hCursor
	nullptr,				// hbrBackground
	nullptr,				// lpszMenuName
	nullptr,				// lpszClassName
	nullptr					// hIconSm
}),
dpcl::main_window({
	sizeof(WNDCLASSEXA),				// cbSize
	0,									// style
	Window::wndproc,					// lpfnWndProc
	0,									// cbClsExtra
	0,									// cbWndExtra
	nullptr,							// hInstance
	LoadIcon(nullptr,IDI_APPLICATION),	// hIcon
	nullptr,							// hCursor
	nullptr,							// hbrBackground
	nullptr,							// lpszMenuName
	"MainWindow",						// lpszClassName
	nullptr								// hIconSm
});