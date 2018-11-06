#ifndef _FUNCTION_H_
#define _FUNCTION_H_
namespace dpcl{
	template<typename type>
	void SafeRelease(type **p){
		if(*p){
			(*p)->Release();
			*p=nullptr;
		}
	}
}
#endif