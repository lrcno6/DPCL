#ifndef _PAINTING_FACTORY_H_
#define _PAINTING_FACTORY_H_
#include"painting.h"
#include"wnd.h"
namespace dpcl{
	class PaintingFactory{
		public:
			PaintingFactory(bool multi_threaded=false){
				if(FAILED(D2D1CreateFactory(multi_threaded?D2D1_FACTORY_TYPE_MULTI_THREADED:D2D1_FACTORY_TYPE_SINGLE_THREADED,&m_factory)))
					throw std::string("PaintingFactory:create factory failed");
			}
			PaintingFactory(const PaintingFactory&)=delete;
			PaintingFactory(PaintingFactory &&other):m_factory(other.m_factory){
				other.m_factory=nullptr;
			}
			~PaintingFactory(){
				SafeRelease(&m_factory);
			}
			PaintingFactory& operator=(const PaintingFactory&)=delete;
			PaintingFactory& operator=(PaintingFactory&&)=delete;
			Painting* create(Window&);
		private:
			ID2D1Factory *m_factory;
	};
}
#endif
