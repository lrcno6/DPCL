#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include<windows.h>
namespace dpcl{
	inline void message_loop();
	template<typename type>
	void SafeRelease(type**);
}
void dpcl::message_loop(){
	MSG msg={};
	while(GetMessage(&msg,nullptr,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
template<typename type>
void dpcl::SafeRelease(type **p){
	if(*p){
		(*p)->Release();
		*p=nullptr;
	}
}
#endif