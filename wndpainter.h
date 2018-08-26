#ifndef _WNDPAINTER_H_
#define _WNDPAINTER_H_
#include"wnd.h"
#include"basepainter.h"
class dpcl::Window::Painter:public Base_Painter{
	public:
		Window* const m_wnd;
		inline Painter(Window* =nullptr);
		inline Painter(Painter&&);
		inline virtual ~Painter();
		inline virtual void make_brush(const D2D1_COLOR_F&);
		inline virtual ID2D1HwndRenderTarget* get_rt();
		inline virtual void clear(const D2D1_COLOR_F&);
		inline void end();
		inline virtual D2D1_SIZE_F size();
	private:
		ID2D1HwndRenderTarget *m_rt;
		PAINTSTRUCT m_ps;
};
dpcl::Window::Painter::Painter(Window *wnd):m_wnd(wnd),m_ps({}){
	using namespace std;
	RECT rc;
    GetClientRect(wnd->m_hwnd,&rc);
	if(FAILED(m_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(wnd->m_hwnd,D2D1::SizeU(rc.right,rc.bottom)),&m_rt)))
		throw string("Create Render Target Failed");
	BeginPaint(wnd->m_hwnd,&m_ps);
	m_rt->BeginDraw();
}
dpcl::Window::Painter::Painter(Painter &&other):Base_Painter((Base_Painter&&)other),m_wnd(other.m_wnd),m_rt(other.m_rt),m_ps({}){
	other.m_rt=nullptr;
}
dpcl::Window::Painter::~Painter(){
	end();
	EndPaint(m_wnd->m_hwnd,&m_ps);
	SafeRelease(&m_rt);
}
void dpcl::Window::Painter::make_brush(const D2D1_COLOR_F &color){
	using namespace std;
	if(FAILED(m_rt->CreateSolidColorBrush(color,&m_brush)))
		throw string("Create Brush Failed");
}
ID2D1HwndRenderTarget* dpcl::Window::Painter::get_rt(){
	return m_rt;
}
void dpcl::Window::Painter::clear(const D2D1_COLOR_F &color){
	m_rt->Clear(color);
}
void dpcl::Window::Painter::end(){
	using namespace std;
	HRESULT hr=m_rt->EndDraw();
	if(FAILED(hr)||hr==D2DERR_RECREATE_TARGET)
		throw string("Paint Failed");
}
D2D1_SIZE_F dpcl::Window::Painter::size(){
	return m_rt->GetSize();
}
#endif