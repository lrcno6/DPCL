#ifndef _BASEPAINTER_H_
#define _BASEPAINTER_H_
#include<string>
#include<d2d1.h>
#include"function.h"
#pragma comment(lib,"d2d1")
namespace dpcl{
	//only Single Threaded
	class Base_Painter{
		public:
			inline Base_Painter();
			Base_Painter(const Base_Painter&)=delete;
			inline Base_Painter(Base_Painter&&);
			Base_Painter& operator=(const Base_Painter&)=delete;
			Base_Painter& operator=(Base_Painter&&)=delete;
			inline virtual ~Base_Painter();
			virtual void make_brush(const D2D1_COLOR_F&)=0;
			virtual ID2D1RenderTarget* get_rt()=0;
			inline ID2D1SolidColorBrush* get_brush();
			virtual D2D1_SIZE_F size()=0;
			virtual void clear(const D2D1_COLOR_F&)=0;
		protected:
			static int m_count;
			static ID2D1Factory *m_factory;
			ID2D1SolidColorBrush *m_brush;
	};
}
int dpcl::Base_Painter::m_count=0;
ID2D1Factory *dpcl::Base_Painter::m_factory=nullptr;
dpcl::Base_Painter::Base_Painter():m_brush(nullptr){
	using namespace std;
	m_count++;
	if(!m_factory)
		if(FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_factory)))
			throw string("Create Factory Failed");
	
}
dpcl::Base_Painter::Base_Painter(Base_Painter &&other):m_brush(other.m_brush){
	m_count++;
	other.m_brush=nullptr;
}
dpcl::Base_Painter::~Base_Painter(){
	if(!--m_count)
		SafeRelease(&m_factory);
	SafeRelease(&m_brush);
}
ID2D1SolidColorBrush* dpcl::Base_Painter::get_brush(){
	return m_brush;
}
#endif