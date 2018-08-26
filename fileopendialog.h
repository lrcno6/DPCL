#ifndef _FILEOPENDIALOG_H_
#define _FILEOPENDIALOG_H_
#include<atlbase.h>
#include<shobjidl.h>
#include"shellitem.h"
#include"wnd.h"
namespace dpcl{
	class FileOpenDialog:public COM{
		public:
			inline FileOpenDialog();
			inline virtual IFileOpenDialog* get_interface();
			inline ShellItem get_result();
			inline void show(Window* =nullptr);
		protected:
			CComPtr<IFileOpenDialog> m_dialog;
	};
}
dpcl::FileOpenDialog::FileOpenDialog(){
	m_dialog=(IFileOpenDialog*)create(CLSID_FileOpenDialog,IID_IFileOpenDialog);
}
IFileOpenDialog* dpcl::FileOpenDialog::get_interface(){
	return m_dialog;
}
dpcl::ShellItem dpcl::FileOpenDialog::get_result(){
	using namespace std;
	IShellItem *item;
	if(FAILED(m_dialog->GetResult(&item)))
		throw string("Get Result Failed");
	return item;
}
void dpcl::FileOpenDialog::show(Window *wnd){
	using namespace std;
	if(FAILED(m_dialog->Show(wnd?wnd->get_handle():nullptr)))
		throw string("Show Dialog Failed");
}
#endif