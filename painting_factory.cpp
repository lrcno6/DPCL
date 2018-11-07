#include"painting_factory.h"
#include"wndpainting.h"
using namespace dpcl;
Painting* PaintingFactory::create(Window &wnd){
	return WindowPainting::create(m_factory,wnd);
}
