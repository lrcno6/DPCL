#include"painting.h"
using namespace dpcl;
Brush* Painting::create_brush(const D2D1_COLOR_F &color){
	return Brush::create(*this,color);
}