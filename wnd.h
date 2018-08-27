#ifndef _WND_H_
#define _WND_H_
#include<string>
#include<windows.h>
namespace dpcl{
	class Window{
		public:
			class Wndclass;
			class Wndproc;
			class Painter;
			Window* const m_parent;
			Wndclass &m_wc;
			inline static Wndclass& wndclass();
			inline Window(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Name",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);
			Window(const Window&)=delete;
			Window(Window&&)=default;
			Window& operator=(const Window&)=delete;
			Window& operator=(Window&&)=delete;
			virtual ~Window()=default;
			inline HWND get_handle();
			inline void show(int);
		protected:
			HWND m_hwnd;
	};
}
#include"wndclass.h"
#include"wndpainter.h"
#include"wndproc.h"
dpcl::Window::Wndclass& dpcl::Window::wndclass(){
	using namespace std;
	static Wndclass wc=[]{
		Wndclass::Struct strt={};
		strt.m_wc.cbSize=sizeof(WNDCLASSEXA);
		strt.m_wc.lpszClassName="Window";
		strt.m_wc.lpfnWndProc=DefWindowProcA;
		strt.m_wc.hInstance=GetModuleHandleA(nullptr);
		return Wndclass(strt);
	}();
	return wc;
}
dpcl::Window::Window(Window *parent,Wndclass &wc,const std::string &name,int x,int y,int w,int h,DWORD style,DWORD styleex,void *param,HMENU hmenu):m_parent(parent),m_wc(wc){
	using namespace std;
	try{
		wc.Register();
	}
	catch(string str){
		if(str!="Registered")
			throw str;
	}
	const Wndclass::Struct &strt=wc.m_struct;
	if(strt.m_istran2obj){
		if(param)
			throw "param is not allowed";
		param=this;
	}
	m_hwnd=CreateWindowExA(styleex|strt.m_styleex,wc.name().c_str(),name.c_str(),style|strt.m_style,x,y,w,h,parent?parent->m_hwnd:nullptr,hmenu,GetModuleHandleA(nullptr),param);
	if(!m_hwnd)
		throw "Create Window Failed";
}
HWND dpcl::Window::get_handle(){
	return m_hwnd;
}
void dpcl::Window::show(int cmd_show){
	ShowWindow(m_hwnd,cmd_show);
}
#endif