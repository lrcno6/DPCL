## DPCL Beta 3.1 Wiki

### About the classes and functions

-----

#### class Window

```cpp
class dpcl::Window{
	public:
		class Wndclass;
		class Wndproc;
		class Painter;

		//the parent window
		Window* const m_parent;

		//the wndclass
		Wndclass &m_wc;

		/*
			return the default wndclass for class Window
			you can override this function in the child classes
		*/
		inline static Wndclass& wndclass();

		/*
			if create the window failed,it will throw std::string("Create Window Failed")
			if wc.m_strt.m_istran2obj==true and param!=nullptr,it will throw std::string("param is not allowed")
		*/
		inline Window(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Name",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);

		//cannot copy
		Window(const Window&)=delete;

		//but you can move
		Window(Window&&)=default;

		Window& operator=(const Window&)=delete;
		Window& operator=(Window&&)=delete;

		virtual ~Window()=default;

		//return m_hwnd
		inline HWND get_handle();

		inline void show(int);
	protected:
		//the handle of the window
		HWND m_hwnd;
};
```

-----

#### class mainwnd

```cpp
class dpcl::MainWindow:public Window{
	public:
		//override
		inline static Wndclass& wndclass();

		//call the constructor Window()
		inline MainWindow(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Title",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);
	protected:
		//the wndproc
		inline static LRESULT CALLBACK wndproc(HWND,unsigned,WPARAM,LPARAM);
};
```

-----

#### class ObjMainwnd and MainWndproc

```cpp
//see dpcl::Window::Wndproc
class dpcl::MainWndproc:public Window::Wndproc{
	public:
		inline MainWndproc(Window* =nullptr);

		//override
		inline virtual LRESULT message(unsigned,WPARAM,LPARAM);
};
class dpcl::ObjMainwnd:public Window{
	public:
		//override
		inline static Wndclass& wndclass();

		//call the constructor Window()
		inline ObjMainwnd(Window* =nullptr,Wndclass& =wndclass(),const std::string& ="Title",int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,int=CW_USEDEFAULT,DWORD=0,DWORD=0,void* =nullptr,HMENU=nullptr);
};
```

-----

#### class Window::Wndclass

```cpp
class dpcl::Window::Wndclass{
	public:
		//extended wndclass struct
		struct Struct{
			bool m_istran2obj;
			DWORD m_style,m_styleex;
			WNDCLASSEXA m_wc;
		};

		//the struct
		const Struct m_struct;

		//if you need to let the window object process the message,make it the wndproc;
		//type should be a child class of class Window::Wndproc
		template<typename type=Wndproc>
		inline static LRESULT CALLBACK tran2obj(HWND,unsigned,WPARAM,LPARAM);

		inline Wndclass(const Struct&);

		//cannot copy
		Wndclass(const Wndclass&)=delete;

		//but you can move
		Wndclass(Wndclass&&)=default;

		Wndclass& operator=(const Wndclass&)=delete;
		Wndclass& operator=(Wndclass&&)=delete;

		//get the name of the wndclass
		inline std::string name();

		/*
			register the wndclass
			if it is registered,it will throw std::string("Registered")
			if register the wndclass failed,it will throw std::string("Register Class Failed")
		*/
		inline void Register();
};
```

-----

#### class Window::Painter

```cpp
//see class Base_Painter
class dpcl::Window::Painter:public Base_Painter{
	public:
		//the painted window
		Window* const m_wnd;

		//if create the render target failed,it will throw std::string("Create Render Target Failed")
		inline Painter(Window* =nullptr);

		inline Painter(Painter&&);

		/*
			call method end
			if you want to catch the exception thad method end throw,you need to call method end before calling the destructor
		*/
		inline virtual ~Painter();

		//if create brush failed,it will throw std::string("Create Brush Failed")
		inline virtual void make_brush(const D2D1_COLOR_F&);

		//get the render target
		inline virtual ID2D1HwndRenderTarget* get_rt();

		inline virtual void clear(const D2D1_COLOR_F&);

		/*
			if paint failed,it will throw std::string("Paint Failed")
			if you want to catch this exception,you need to call this method before calling the destructor
		*/
		inline void end();

		inline virtual D2D1_SIZE_F size();
};
```

-----

#### class Window::Wndproc

```cpp
//objective wndproc
class dpcl::Window::Wndproc{
	public:
		Window *m_wnd;
		inline Wndproc(Window* =nullptr);

		//cannot copy
		Wndproc(const Wndproc&)=delete;

		//but you can move
		Wndproc(Wndproc&&)=default;

		Wndproc& operator=(const Wndproc&)=delete;
		Wndproc& operator=(Wndproc&&)=delete;
		virtual ~Wndproc()=default;
		virtual LRESULT message(unsigned,WPARAM,LPARAM);
};
```

-----

#### class Base_Painter

```cpp
class dpcl::Base_Painter{
	public:
		//if create the factory failed,it will throw std::string("Create Factory Failed")
		inline Base_Painter();

		//cannot copy
		Base_Painter(const Base_Painter&)=delete;

		//but you can move
		inline Base_Painter(Base_Painter&&);

		Base_Painter& operator=(const Base_Painter&)=delete;
		Base_Painter& operator=(Base_Painter&&)=delete;
		inline virtual ~Base_Painter();
		virtual void make_brush(const D2D1_COLOR_F&)=0;

		//get the render target
		virtual ID2D1RenderTarget* get_rt()=0;

		//return m_brush
		inline ID2D1SolidColorBrush* get_brush();

		virtual D2D1_SIZE_F size()=0;
		virtual void clear(const D2D1_COLOR_F&)=0;
	protected:
		//the number of Base_Painter object
		static int m_count;

		static ID2D1Factory *m_factory;
		ID2D1SolidColorBrush *m_brush;
};
```

-----

#### class COM

```cpp
class dpcl::COM{
	public:
		//if initialize the COM library failed,it will throw std::string("Initialize COM Failed")
		inline COM();

		//cannot copy
		COM(const COM&)=delete;

		//but you can move
		inline COM(COM&&);

		inline virtual ~COM();
		COM& operator=(const COM&)=delete;
		COM& operator=(COM&&)=delete;
		virtual IUnknown* get_interface()=0;
	protected:
		//the number of Base_Painter object
		static int m_count;

		//if create failed,it will throw std::string("Create Instance Failed")
		inline static IUnknown* create(REFCLSID,REFIID);
};
```

-----

#### class FileOpenDialog

```cpp
class FileOpenDialog:public COM{
	public:
		//call the constructor COM() and method COM::create
		inline FileOpenDialog();

		//override
		inline virtual IFileOpenDialog* get_interface();

		//if failed,it will throw std::string("Get Result Failed")
		inline ShellItem get_result();

		//if failed,it will throw std::string("Show Dialog Failed")
		inline void show(Window* =nullptr);
	protected:
		CComPtr<IFileOpenDialog> m_p;
};
```

-----

#### class ShellItem

```cpp
class ShellItem:public COM{
	public:
		//call the constructor COM() and method COM::create
		inline ShellItem(IShellItem*);

		//override
		inline virtual IShellItem* get_interface();

		//if failed,it will throw std::string("Get Display Name Failed")
		inline std::wstring get_name(SIGDN);
	protected:
		CComPtr<IShellItem> m_p;
};
```

-----

#### some functions

```cpp
inline void message_loop();
template<typename type>
void SafeRelease(type**);
```

-----

### Demo

#### Show a Window

```cpp
#include"DPCL.h"
using namespace dpcl;
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){
	MainWindow wnd;
	wnd.show(cmd_show);
	message_loop();
	return 0;
}
```

-----

#### User Window Class

see *dpcl::MainWindow*

#### Using Objective Wndproc

```cpp
#include"DPCL.h"
using namespace dpcl;
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){
	ObjMainwnd wnd;
	wnd.show(cmd_show);
	message_loop();
	return 0;
}
```

-----

#### User Objective Wndproc

see *dpcl::MainWndproc* and *dpcl::ObjMainwnd*

#### Paint

```cpp
#include<algorithm>
#include"DPCL.h"
using namespace dpcl;
class MyWndproc:public MainWndproc{
	public:
		MyWndproc(Window *wnd=nullptr):MainWndproc(wnd){}
		virtual LRESULT message(unsigned msg,WPARAM wparam,LPARAM lparam){
			using namespace std;
			switch(msg){
				case WM_PAINT:{
					Window::Painter painter(m_wnd);
					auto size=painter.size();
					const float x=size.width/2,y=size.height/2;
					const float radius=min(x,y);
					D2D1_ELLIPSE ellipse=D2D1::Ellipse(D2D1::Point2F(x,y),radius,radius);
					painter.clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
					painter.make_brush(D2D1::ColorF(1,1,0));
        			painter.get_rt()->FillEllipse(ellipse,painter.get_brush());
					return 0;
				}					
				case WM_SIZE:
        			InvalidateRect(m_wnd->get_handle(),nullptr,false);
					return 0;
				default:
					return MainWndproc::message(msg,wparam,lparam);
			}
		}
};
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){
	Window::Wndclass wc=[]{
		Window::Wndclass::Struct strt=ObjMainwnd::wndclass().m_struct;
		strt.m_wc.lpszClassName="MyWindow";
		strt.m_wc.lpfnWndProc=Window::Wndclass::tran2obj<MyWndproc>;
		return Window::Wndclass(strt);
	}();
	ObjMainwnd wnd(nullptr,wc);
	wnd.show(cmd_show);
	message_loop();
	return 0;
}
```

-----

#### COM Demo:File Open Dialog

```cpp
#include"DPCL.h"
using namespace dpcl;
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE,char *cmd_line,int cmd_show){
	dpcl::FileOpenDialog dialog;
	dialog.show();
	dpcl::ShellItem item=dialog.get_result();
	MessageBoxW(nullptr,item.get_name(SIGDN_FILESYSPATH).c_str(),L"File Path",MB_OK);
	return 0;
}
```