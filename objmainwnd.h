#ifndef _OBJMAINWND_H_
#define _OBJMAINWND_H_
#include"mainwnd.h"
namespace dpcl{
	class MainWndproc:public Window::Wndproc{
		public:
			inline MainWndproc(Window* =nullptr);
			inline virtual LRESULT message(unsigned,WPARAM,LPARAM);
	};
	class ObjMainwnd:public Window{
		public:
			inline static Wndclass& wndclass();
			inline ObjMainwnd(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Title",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);
	};
}
dpcl::MainWndproc::MainWndproc(Window *wnd):Wndproc(wnd){}
LRESULT dpcl::MainWndproc::message(unsigned msg,WPARAM wparam,LPARAM lparam){
	HWND hwnd=m_wnd->get_handle();
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc=BeginPaint(hwnd,&ps);
			FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd,&ps);
			return 0;
		}
	}
	return DefWindowProcA(hwnd,msg,wparam,lparam);
}
dpcl::Window::Wndclass& dpcl::ObjMainwnd::wndclass(){
	static Wndclass wc=[]{
		Wndclass::Struct strt=MainWindow::wndclass().m_struct;
		strt.m_wc.lpszClassName="ObjMainwnd";
		strt.m_wc.lpfnWndProc=Wndclass::tran2obj<MainWndproc>;
		strt.m_istran2obj=true;
		return Wndclass(strt);
	}();
	return wc;
}
dpcl::ObjMainwnd::ObjMainwnd(Window *parent,Wndclass &wc,const std::string &title,int x,int y,int w,int h,DWORD style,DWORD styleex,void *param,HMENU hmenu):Window(parent,wc,title,x,y,w,h,style,styleex,param,hmenu){}
#endif