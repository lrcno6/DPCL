#include"wnd.h"
using namespace dpcl;
LRESULT CALLBACK Window::wndproc(HWND hwnd,unsigned msg,WPARAM wparam,LPARAM lparam){
	Window *p=nullptr;
	if(msg==WM_NCCREATE){
		p=(Window*)((CREATESTRUCT*)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd,GWLP_USERDATA,(LONG_PTR)p);
	}
	else
		p=(Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
	bool def=true;
	if(p)
		def=!p->call(msg,wparam,lparam);
	return def?DefWindowProc(hwnd,msg,wparam,lparam):0;
}