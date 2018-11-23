## DPCL Alpha 4.3

Alpha 4.3:for *Observer*

I have a poor English,so some of the sentences are translated by *Google Translate*.So maybe some sentences have grammatical errors.

As the name implies,*DPCL*(*Desktop Programming Class Library*) is a class library for desktop programming.

-----

GitHub address: https://github.com/lrcno6/DPCL

-----

License:*LGPL v3.0*

-----

### About the Version

In this version,we rewrote the entire class library again,and make it more like *Qt* programming - to make the object subject(see [Observer](https://en.wikipedia.org/wiki/Observer_pattern)).However,the other core functionalities have not changed much.

### How to Use it

DPCL is a static library.If you are using Visual Studio,you can use nmake - there is a *makefile* for it.If not,please compile all the cpp source and make a static library.

You need not to add to link *d2d1.lib* please we add `#pragma comment(lib,"d2d1")` in *DPCL.h*.But you need to link *DPCL.lib* by yourself because we deleted the `#pragma comment(lib,"DPCL")` in *DPCL.h*

If you cannot find *D2D1CreateFactory* or others while you compile,maybe you also need to link d2d1.lib(I do not know why).

### Note

All classes and functions are in namespace *dpcl*

### Wiki

see file *wiki.md*

-----

I hope that more people can improve *DPCL*.

by *EnderPearl*