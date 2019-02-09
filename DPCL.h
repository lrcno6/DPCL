#ifndef _DPCL_H_
#define _DPCL_H_
/*
#include"application.h"
#include"function.h"
#include"mainwnd.h"
#include"painting.h"
#include"painting_factory.h"
#include"rand.h"
#include"subject.h"
#include"wnd.h"
#include"wndpainting.h"
*/
#include<cstdlib>
#include<ctime>
#ifdef WIN_OS
#pragma comment(lib,"d2d1")
#define DPCL_main \
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){ \
	srand(time(nullptr)); \
	Application app(hinstance,cmd_line); \
	return app.call_main(); \
}
#else
#define DPCL_main \
int main(int argc,char argv){ \
	srand(time(nullptr)); \
	Application app(argc,argv) \
	return app.call_main(); \
}
#endif
#endif