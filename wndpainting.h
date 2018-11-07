#ifndef _WND_PAINTING_H_
#define _WND_PAINTING_H_
#include"painting_factory.h"
namespace dpcl{
	class WindowPainting:public Painting{
		friend Painting* PaintingFactory::create(Window&);
		public:
			virtual ~WindowPainting(){
				if(m_rt)
					EndPaint(get_hwnd(),&m_ps);
			}
			virtual void end(){
				if(m_rt){
					Painting::end();
					EndPaint(get_hwnd(),&m_ps);
				}
			}
		private:
			PAINTSTRUCT m_ps;
			static WindowPainting* create(ID2D1Factory *factory,Window &wnd){
				RECT rc;
				ID2D1RenderTarget *rt;
				GetClientRect(wnd.handle(),&rc);
				if(FAILED(factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),D2D1::HwndRenderTargetProperties(wnd.handle(),D2D1::SizeU(rc.right,rc.bottom)),(ID2D1HwndRenderTarget**)&rt)))
					throw std::string("WindowPainting::WindowPainting:create render target failed");
				return new WindowPainting(rt);
			}
			WindowPainting(ID2D1RenderTarget *rt):Painting(rt){
				BeginPaint(get_hwnd(),&m_ps);
			}
			HWND get_hwnd(){
				return ((ID2D1HwndRenderTarget*)m_rt)->GetHwnd();
			}
	};
}
#endif