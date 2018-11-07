#ifndef _PAINTING_H_
#define _PAINTING_H_
#include<d2d1.h>
#include"subject.h"
//#include"brush.h"
#include"function.h"
namespace dpcl{
	class Brush;
	class Painting:public Subject{
		public:
			Painting(Painting &&other):m_rt(other.m_rt){
				other.m_rt=nullptr;
			}
			virtual ~Painting(){
				end();
			}
			ID2D1RenderTarget* operator->(){
				return m_rt;
			}
			Brush* create_brush(const D2D1_COLOR_F&);
			virtual void end(){
				if(m_rt){
					HRESULT hr=m_rt->EndDraw();
					if(FAILED(hr) || hr==D2DERR_RECREATE_TARGET)
						throw std::string("Painting:paint failed");
					SafeRelease(&m_rt);
				}
			}
			void clear(const D2D1_COLOR_F &color){
				m_rt->Clear(color);
			}
			D2D1_SIZE_F size(){
				return m_rt->GetSize();
			}
		protected:
			Painting(ID2D1RenderTarget *rt):m_rt(rt){
				m_rt->BeginDraw();
			}
			ID2D1RenderTarget *m_rt;
	};
	class Brush:public Subject{
		friend Brush* Painting::create_brush(const D2D1_COLOR_F&);
		public:
			ID2D1SolidColorBrush* get(){
				return m_brush;
			}
		private:
			ID2D1SolidColorBrush *m_brush;
			static Brush* create(Painting &p,const D2D1_COLOR_F &color){
				ID2D1SolidColorBrush *brush;
				if(FAILED(p->CreateSolidColorBrush(color,&brush)))
					throw std::string("Brush::Brush:failed");
				return new Brush(brush);
			}
			Brush(ID2D1SolidColorBrush *brush):m_brush(brush){}
	};
}
#endif