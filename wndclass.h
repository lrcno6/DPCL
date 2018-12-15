#ifndef _WNDCLASS_H_
#define _WNDCLASS_H_
#include<string>
#include<windows.h>
#include"application.h"
namespace dpcl{
	class Wndclass{
		public:
			const WNDCLASSEXA m_wc;
			Wndclass(const WNDCLASSEXA &wc):m_registered(false),m_wc(wc){}
			Wndclass(const Wndclass&)=delete;
			Wndclass(Wndclass&&)=default;
			Wndclass& operator=(const Wndclass&)=delete;
			Wndclass& operator=(Wndclass&&)=delete;
			const char* name(){
				return m_wc.lpszClassName;
			}
			bool Register(HINSTANCE hinstance){
				using namespace std;
				if(m_registered)
					return false;
				auto wc=m_wc;
				wc.hInstance=hinstance;
				if(!RegisterClassExA(&wc))
					throw string("Wndclass::Register:register class failed");
				return true;
			}
			bool Register(Application &app){
				return Register(app.handle());
			}
			bool Register(Application *app){
				return Register(app?app->handle():nullptr);
			}
		private:
			bool m_registered;
	};
	extern Wndclass def_wndclass,main_window;
}
#endif