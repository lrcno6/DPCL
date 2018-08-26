#ifndef _WNDPROC_H_
#define _WNDPROC_H_
#include"wnd.h"
class dpcl::Window::Wndproc{
	public:
		Window *m_wnd;
		inline Wndproc(Window* =nullptr);
		Wndproc(const Wndproc&)=delete;
		Wndproc(Wndproc&&)=default;
		Wndproc& operator=(const Wndproc&)=delete;
		Wndproc& operator=(Wndproc&&)=delete;
		virtual ~Wndproc()=default;
		virtual LRESULT message(unsigned,WPARAM,LPARAM);
};
dpcl::Window::Wndproc::Wndproc(Window *wnd):m_wnd(wnd){}
LRESULT dpcl::Window::Wndproc::message(unsigned msg,WPARAM wparam,LPARAM lparam){
	return DefWindowProcA(m_wnd?m_wnd->get_handle():nullptr,msg,wparam,lparam);
}
#endif