#ifndef _WNDCLASS_H_
#define _WNDCLASS_H_
#include"wnd.h"
class dpcl::Window::Wndclass{
	public:
		struct Struct{
			bool m_istran2obj;
			DWORD m_style,m_styleex;
			WNDCLASSEXA m_wc;
		};
		const Struct m_struct;
		//type should be a child class of class Window::Wndproc
		template<typename type=Wndproc>
		inline static LRESULT CALLBACK tran2obj(HWND,unsigned,WPARAM,LPARAM);
		inline Wndclass(const Struct&);
		Wndclass(const Wndclass&)=delete;
		Wndclass(Wndclass&&)=default;
		Wndclass& operator=(const Wndclass&)=delete;
		Wndclass& operator=(Wndclass&&)=delete;
		inline std::string name();
		inline void Register();
	private:
		bool m_registered;
};
template<typename type>
LRESULT CALLBACK dpcl::Window::Wndclass::tran2obj(HWND hwnd,unsigned msg,WPARAM wparam,LPARAM lparam){
	Window *pthis=nullptr;
	if(msg==WM_NCCREATE){
		pthis=(Window*)((CREATESTRUCT*)lparam)->lpCreateParams;
		SetWindowLongPtrA(hwnd,GWLP_USERDATA,(LONG_PTR)pthis);
		pthis->m_hwnd=hwnd;
	}
	else
		pthis=(Window*)GetWindowLongPtrA(hwnd,GWLP_USERDATA);
	type wndproc(pthis);
	if(pthis)
		return wndproc.message(msg,wparam,lparam);
	else
		return DefWindowProcA(hwnd,msg,wparam,lparam);
}
dpcl::Window::Wndclass::Wndclass(const Struct &strt):m_registered(false),m_struct(strt){}
std::string dpcl::Window::Wndclass::name(){
	return m_struct.m_wc.lpszClassName;
}
void dpcl::Window::Wndclass::Register(){
	using namespace std;
	if(m_registered)
		throw string("Registered");
	if(!RegisterClassExA(&m_struct.m_wc))
		throw string("Register Class Failed");
}
#endif