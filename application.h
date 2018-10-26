#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include"subject.h"
#define DPCL_main \
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){\
	Application app(hinstance,cmd_show);\
	int argc=0,value;\
	wchar_t **wargv=CommandLineToArgvW(GetCommandLineW(),&argc);\
	char **argv=wstring2string(wargv,argc);\
	try{\
		value=app.main(argc,argv);\
	}\
	catch(std::string str){\
		MessageBoxA(nullptr,str.c_str(),nullptr,MB_OK|MB_ICONERROR);\
	}\
	for(int i=0;i<argc;i++)\
		delete argv[i];\
	delete argv;\
	LocalFree(wargv);\
	return value;\
}
namespace dpcl{
	class Application:public Subject{
		public:
			Application(HINSTANCE hinstance,int cmd_show):m_hinstance(hinstance),m_cmd_show(cmd_show){}
			int main(int,char**);
			HINSTANCE handle()const{
				return m_hinstance;
			}
			int message_loop()const{
				MSG msg={};
				while(GetMessageA(&msg,nullptr,0,0)){
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
				}
				return msg.wParam;
			}
			void quit(WPARAM wparam,LPARAM){
				PostQuitMessage(wparam);
			}
		private:
			HINSTANCE m_hinstance;
			int m_cmd_show;
	};
	inline char** wstring2string(wchar_t **wargv,int argc){
		char **argv=new char*[argc];
		for(int i=0;i<argc;i++){
			int len=WideCharToMultiByte(CP_ACP,0,wargv[i],wcslen(wargv[i]),nullptr,0,nullptr,nullptr);
			argv[i]=new char[len+1];
			WideCharToMultiByte(CP_ACP,0,wargv[i],wcslen(wargv[i]),argv[i],len,nullptr,nullptr);
			argv[i][len]='\0';
		}
		return argv;
	}
}
#endif