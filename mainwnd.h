#ifndef _MAIN_WND_H_
#define _MAIN_WND_H_
#include"wnd.h"
#include"painting_factory.h"
namespace dpcl{
	class MainWindow:public Window{
		public:
			MainWindow(const char *name,Application &app,int x=CW_USEDEFAULT,int y=CW_USEDEFAULT,int w=CW_USEDEFAULT,int h=CW_USEDEFAULT,Window *parent=nullptr,DWORD style=0,DWORD styleex=0){
				static WNDCLASSEXA wc=[]{
					WNDCLASSEXA wc={};
					wc.cbSize=sizeof(WNDCLASSEXA);
					wc.lpszClassName="MainWindow";
					wc.lpfnWndProc=wndproc;
					return wc;
				}();
				if(!m_registered){
					wc.hInstance=app.handle();
					Register(wc);
				}
				create(styleex,"MainWindow",name,style|WS_OVERLAPPEDWINDOW,x,y,w,h,parent,&app);
				connect(WM_DESTROY,app,&Application::quit);
				connect(WM_PAINT,*this,&MainWindow::paint);
			}
			virtual void paint(WPARAM,LPARAM){
				/*PAINTSTRUCT ps;
				HDC hdc=BeginPaint(m_hwnd,&ps);
				FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
				EndPaint(m_hwnd,&ps);*/
				Painting *painting=m_factory.create(*this);
				painting->clear(D2D1::ColorF(D2D1::ColorF::White));
				delete painting;
			}
		protected:
			static bool m_registered;
			static PaintingFactory m_factory;
	};
}
#endif
