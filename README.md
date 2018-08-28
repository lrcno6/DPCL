## DPCL Beta 3.1

Beta 3.1:fix some bugs on beta 3.0

I realized that it is not easy to write a *README* file.

I have a poor English,so some of the sentences are translated by *Google Translate*.So maybe some sentences have grammatical errors.

As the name implies,DPCL(Desktop Programming Class Library) is a class library for desktop programming.

-----

GitHub address: https://github.com/lrcno6/DPCL

-----

### About the Version

In Beta 2.0,the desktop programming by DPCL is just like the Win32 programming.But in beta 3.0,we rewrite the entire class library,and make it more like *Qt* programming.However,the core functionality has not changed much.

### How to Use it

DPCL is a static library,although lots of functions are inlined.

To use DPCL,you need to compile the source *var.cpp* and create a static library named *DPCL.lib*(or *DPCL.a* or others).Because there are `#pragma comment(lib,"DPCL")` in header *DPCL.h*.

### Note

1. Use it by a single thread.If you need to use it with multiple threads,you should change something,or it will have lots of bugs.
2. All classes and functions are in namespace *dpcl*

### Wiki

see file *wiki.md*(no link)

-----

Finally,I hope that everyone can help me and improve *DPCL*.

We do,together!

by *EnderPearl*