#ifndef _WND_H_
#define _WND_H_
#include"application.h"
namespace dpcl{
	class Window:public Subject{
		public:
			HWND handle(){
				return m_hwnd;
			}
			void show(int cmd_show){
				if(m_hwnd==nullptr)
					throw std::string("Window::show:invalid window object");
				ShowWindow(m_hwnd,cmd_show);
			}
		protected:
			HWND m_hwnd;
			static LRESULT CALLBACK wndproc(HWND,unsigned,WPARAM,LPARAM);
			static void Register(WNDCLASSEXA &wc){
				if(RegisterClassExA(&wc)==0)
					throw std::string("Window::Register:register window class failed");
			}
			Window(HWND hwnd=nullptr):m_hwnd(hwnd){}
			void create(DWORD styleex,const char *class_name,const char *window_name,DWORD style,int x,int y,int w,int h,HWND parent,HMENU menu,HINSTANCE hinstance){
				m_hwnd=CreateWindowExA(styleex,class_name,window_name,style,x,y,w,h,parent,menu,hinstance,this);
				if(m_hwnd==nullptr)
					throw std::string("Window::Window:create window failed");
			}
			void create(DWORD styleex,const char *class_name,const char *window_name,DWORD style,int x,int y,int w,int h,Window &parent,Application &app){
				create(styleex,class_name,window_name,style,x,y,w,h,parent.m_hwnd,nullptr,app.handle());
			}
			void create(DWORD styleex,const char *class_name,const char *window_name,DWORD style,int x,int y,int w,int h,Window *parent,Application *app){
				create(styleex,class_name,window_name,style,x,y,w,h,parent?parent->m_hwnd:nullptr,nullptr,app?app->handle():nullptr);
			}
	};
}
#endif