#ifndef _COM_H_
#define _COM_H_
#include<string>
#include<windows.h>
namespace dpcl{
	class COM{
		public:
			inline COM();
			COM(const COM&)=delete;
			inline COM(COM&&);
			inline virtual ~COM();
			COM& operator=(const COM&)=delete;
			COM& operator=(COM&&)=delete;
			virtual IUnknown* get_interface()=0;
		protected:
			static int m_count;
			static IUnknown* create(REFCLSID,REFIID);
	};
}
int dpcl::COM::m_count=0;
dpcl::COM::COM(){
	using namespace std;
	if(m_count++==0)
		if(FAILED(CoInitializeEx(nullptr,COINIT_APARTMENTTHREADED|COINIT_DISABLE_OLE1DDE)))
			throw string("Initialize COM Failed");
}
dpcl::COM::COM(COM&&){
	m_count++;
}
dpcl::COM::~COM(){
	if(!--m_count)
		CoUninitialize();
}
IUnknown* dpcl::COM::create(REFCLSID rclsid,REFIID riid){
	using namespace std;
	void *p;
	if(FAILED(CoCreateInstance(rclsid,nullptr,CLSCTX_ALL,riid,&p)))
		throw string("Create Instance Failed");
	return (IUnknown*)p;
}
#endif