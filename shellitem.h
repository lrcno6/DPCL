#ifndef _SHELLITEM_H_
#define _SHELLITEM_H_
#include<atlbase.h>
#include<shobjidl.h>
#include"com.h"
namespace dpcl{
	class ShellItem:public COM{
		public:
			inline ShellItem(IShellItem*);
			inline virtual IShellItem* get_interface();
			inline std::wstring get_name(SIGDN);
		protected:
			CComPtr<IShellItem> m_p;
	};
}
dpcl::ShellItem::ShellItem(IShellItem *inter):m_p(inter){}
IShellItem* dpcl::ShellItem::get_interface(){
	return m_p;
}
std::wstring dpcl::ShellItem::get_name(SIGDN sigdn){
	using namespace std;
	wchar_t *wstr;
	wstring rwstr;
	if(FAILED(m_p->GetDisplayName(sigdn,&wstr)))
		throw string("Get Display Name Failed");
	rwstr=wstr;
	CoTaskMemFree(wstr);
	return rwstr;
}
#endif