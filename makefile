DPCL.lib:mainwnd.obj painting.obj painting_factory.obj rand.obj wnd.obj wndclass.obj
	lib mainwnd.obj painting.obj painting_factory.obj rand.obj wnd.obj wndclass.obj /out:DPCL.lib
mainwnd.obj:mainwnd.cpp
	cl /c mainwnd.cpp
painting.obj:painting.cpp
	cl /c painting.cpp
painting_factory.obj:painting_factory.cpp
	cl /c painting_factory.cpp
rand.obj:rand.cpp
	cl /c rand.cpp
wnd.obj:wnd.cpp
	cl /c wnd.cpp
wndclass.obj:wndclass.cpp
	cl /c wndclass.cpp
clean:
	del mainwnd.obj painting.obj painting_factory.obj rand.obj wnd.obj wndclass.obj DPCL.lib