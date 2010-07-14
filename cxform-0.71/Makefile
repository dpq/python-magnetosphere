# CXFORM multi-purpose makefile
# See INSTALL.TXT for more information
#
# 2000/06/14: Ed Santiago - Original version
# 2003/09/12: Ryan Boller - Modified for multiple platforms/languages
# 2004/03/18: Ryan Boller - Modified for OS auto-detect, Mac compatibility
# 2009/11/25: Ryan Boller - Added compiler flags for 64-bit Mac platform

SRC = 	cxform.c
ASM = 	cxform.a
DEF = 	cxform.def


# NOTE: If using MS Windows, this Makefile is only useful for gcc/cygwin builds.
#    Also note that these builds will not be compatible with IDL 6.0+, as
#    they are based on Microsoft Visual C++ 7.0.  If you need to build for
#    IDL 6.0+, use the "make_CXFORM_MSVC.bat" file.  You will also need
#    to have either MSVC++ 7.0 (not free) or MSVC++ Toolkit 2003 (free)
#    installed.


# NOTE: User needs to modify appropriate directory for system-specific location of IDL
IDL_DIR_UNIX=/usr/local/rsi/idl
IDL_DIR_WIN=c:\dev\RSI\IDL63


IDL_EXT_UNIX=$(IDL_DIR_UNIX)/external
IDL_EXT_WIN=$(IDL_DIR_WIN)\external
IDL_LIB_WIN=$(IDL_DIR_WIN)\bin\bin.x86


# Detect which OS is running and select appropriate flags
all:		dll
so:
	@echo "OS type detected: "`uname`
	@case `uname` in \
		"SunOS")  make sun-cxform.so \
				"CFLAGS=-fPIC -shared -I$(IDL_EXT_UNIX)" ;;\
		"Darwin") make mac-cxform.so \
				"CFLAGS=-fPIC -arch x86_64 -arch i386 -arch ppc -arch ppc64 -I$(IDL_EXT_UNIX)" ;;\
		"Linux")  make linux-cxform.so \
				"CFLAGS=-fPIC -shared -I$(IDL_EXT_UNIX)" ;;\
		*) echo "This operating system is not supported -- use make dll if under MS Windows" ;;\
	esac

so-c:
	@echo "OS type detected: "`uname`
	@case `uname` in \
		"SunOS")  make sun-cxform-c.so \
				"CFLAGS=-fPIC -shared" ;;\
		"Darwin") make mac-cxform-c.so \
				"CFLAGS=-fPIC -arch x86_64 -arch i386 -arch ppc -arch ppc64" ;;\
		"Linux")  make linux-cxform-c.so \
				"CFLAGS=-fPIC -shared" ;;\
		*) echo "This operating system is not supported -- use make dll-c if under MS Windows" ;;\
	esac


dll:		
	make cxform.dll "CFLAGS=-Wall -shared -g -I$(IDL_EXT_WIN)"
dll-c:		
	make cxform-c.dll "CFLAGS=-Wall -shared -g"


# MAC-SPECIFIC
mac-cxform.so:	cxform-auto.o  cxform-manual.o  cxform-dlm.o 
	gcc -arch x86_64 -arch i386 -arch ppc -arch ppc64 -flat_namespace -undefined suppress -bundle -o cxform.so $^ 

mac-cxform-c.so: cxform-auto.o  cxform-manual.o
	gcc -arch x86_64 -arch i386 -arch ppc -arch ppc64 -flat_namespace -undefined suppress -bundle -o cxform-c.so $^


# LINUX-SPECIFIC
linux-cxform.so:  cxform-auto.o  cxform-manual.o  cxform-dlm.o 
	ld -G -lm -o cxform.so $^

linux-cxform-c.so: cxform-auto.o  cxform-manual.o
	ld -G -lm -o cxform-c.so $^


# SUN-SPECIFIC
sun-cxform.so:  cxform-auto.o  cxform-manual.o  cxform-dlm.o 
	ld -G -lm -o cxform.so $^

sun-cxform-c.so: cxform-auto.o  cxform-manual.o
	ld -G -lm -o cxform-c.so $^




# former UNIX build command
#cxform-c.so:	cxform-auto.o  cxform-manual.o
#	ld -G -lm -o $@ $^


# WINDOWS-SPECIFIC
cxform.dll:	cxform-auto.o  cxform-manual.o  cxform-dlm.o
	gcc -shared -W1,--enable-auto-image-base -o $@ -W1,--out-implib=$@.a $(DEF) $^ $(IDL_LIB_WIN)\idl.lib
	dlltool --def $(DEF) --dllname $@ --output-lib $(ASM)

cxform-c.dll: cxform-auto.o  cxform-manual.o
	gcc -shared $^ -o $@



#####################
# C testing routines
main.exe: cxform-c.dll main.o
	gcc $^ -o $@
	
tester.o:
	gcc -c -o tester.o tester.c

tester.exe: cxform-c.dll tester.o
	gcc $^ -o $@


main:
	@echo "OS type detected: "`uname`
	@case `uname` in \
		"SunOS")  make sun-main \
				"CFLAGS=-fPIC -shared" ;;\
		"Darwin") make mac-main \
				"CFLAGS=-fPIC" ;;\
		"Linux")  make linux-main \
				"CFLAGS=-fPIC -shared" ;;\
		*) echo "This operating system is not supported -- use make main.exe if under MS Windows" ;;\
	esac


sun-main: sun-cxform-c.so main.o
	gcc ./cxform-c.so main.o -lm -o main
#	gcc $^ -lm -o $@


mac-main:
	@echo "NOTE TO MAC USERS: There is currently a problem linking a C routine to the cxform-c.so shared library.  The alternative is to compile cxform directly with the routine, as done here"
	gcc main.c cxform-auto.c cxform-manual.c -o main

linux-main: linux-cxform-c.so main.o
	gcc ./cxform-c.so main.o -lm -o main



#######################
clean:
	rm -f *.so *.sl *.o *.obj *.a core a.out cxform.dll cxform-c.dll cxform.lib cxform.exp main main.exe tester.exe

