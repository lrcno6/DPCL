#ifndef _MAINWND_H_
#define _MAINWND_H_
#include"wnd.h"
namespace dpcl{
	class MainWindow:public Window{
		public:
			inline static Wndclass& wndclass();
			inline MainWindow(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Title",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);
		protected:
			inline static LRESULT CALLBACK wndproc(HWND,unsigned,WPARAM,LPARAM);
	};
}
dpcl::Window::Wndclass& dpcl::MainWindow::wndclass(){
	static Wndclass wc=[]{
		Wndclass::Struct strt=Window::wndclass().m_struct;
		strt.m_wc.lpszClassName="MainWindow";
		strt.m_wc.lpfnWndProc=wndproc;
		strt.m_style=WS_OVERLAPPEDWINDOW;
		return Wndclass(strt);
	}();
	return wc;
}
dpcl::MainWindow::MainWindow(Window *parent,Wndclass &wc,const std::string &title,int x,int y,int w,int h,DWORD style,DWORD styleex,void *param,HMENU hmenu):Window(parent,wc,title,x,y,w,h,style,styleex,param,hmenu){}
LRESULT CALLBACK dpcl::MainWindow::wndproc(HWND hwnd,unsigned msg,WPARAM wparam,LPARAM lparam){
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc=BeginPaint(hwnd,&ps);
				FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
				EndPaint(hwnd,&ps);
			}
			return 0;
	}
	return DefWindowProcA(hwnd,msg,wparam,lparam);
}
#endif