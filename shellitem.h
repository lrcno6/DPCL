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
			CComPtr<IShellItem> m_item;
	};
}
dpcl::ShellItem::ShellItem(IShellItem *inter):m_item(inter){}
IShellItem* dpcl::ShellItem::get_interface(){
	return m_item;
}
std::wstring dpcl::ShellItem::get_name(SIGDN sigdn){
	using namespace std;
	wchar_t *wstr;
	wstring rwstr;
	if(FAILED(m_item->GetDisplayName(sigdn,&wstr)))
		throw string("Get Display Name Failed");
	rwstr=wstr;
	CoTaskMemFree(wstr);
	return rwstr;
}
#endif