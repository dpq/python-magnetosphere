@ECHO OFF
REM  MS Windows batch file to build the CXFORM DLM/DLL.
REM
REM  You may pass the location of the IDL directory to this file on the
REM  command line: e.g., make_CXFORM_MSVC d:\myidl\idl
REM
REM  You may also edit the default location below.
REM
REM  2006/10/11 - Ryan Boller:  Initial version

SETLOCAL

IF "%1" == "" GOTO SET_IDLDIR
SET IDL_DIR=%1
GOTO CONTINUE

:SET_IDLDIR
SET IDL_DIR=c:\dev\RSI\idl63

:CONTINUE

SET IDL_LIBDIR=%IDL_DIR%\bin\bin.x86

IF NOT EXIST %IDL_LIBDIR%\idl.lib GOTO NO_IDL_LIB
IF NOT EXIST %IDL_DIR%\external\include/idl_export.h GOTO NO_EXPORT_H


:CompileAll
ECHO ON

cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c cxform-auto.c 
cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c cxform-manual.c 
cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c main.c 
cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /I%IDL_DIR%\external /c cxform-dlm.c 

link /out:cxform.dll /nodefaultlib /dll -nologo cxform-auto.obj cxform-manual.obj cxform-dlm.obj /def:cxform.def %IDL_LIBDIR%\idl.lib msvcrt.lib kernel32.lib

link /out:main.exe /nodefaultlib -nologo main.obj cxform-auto.obj cxform-manual.obj msvcrt.lib kernel32.lib

@ECHO OFF

GOTO END


:OnlyCompileForC
ECHO ON

cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c cxform-auto.c 
cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c cxform-manual.c 
cl -D_DLL -DMSWIN -DWIN32 -D_MT -nologo -DWIN32_LEAN_AND_MEAN /c main.c 

link /out:cxform-c.dll /nodefaultlib /dll -nologo cxform-auto.obj cxform-manual.obj msvcrt.lib kernel32.lib

link /out:main.exe /nodefaultlib -nologo main.obj cxform-auto.obj cxform-manual.obj msvcrt.lib kernel32.lib

@ECHO OFF

GOTO END


:NO_IDL_LIB
ECHO.
ECHO Unable to locate %IDL_LIBDIR%\idl.lib.
ECHO.
GOTO AskForCOnlyCompile


:NO_EXPORT_H
ECHO.
ECHO Unable to locate %IDL_DIR%\external\include\idl_export.h.
ECHO.
GOTO AskForCOnlyCompile


:AskForCOnlyCompile
ECHO If you want to use CXFORM as an IDL DLM, you will need to modify
ECHO this batch file, make_CXFORM_MSVC.bat, to include the correct path
ECHO to your IDL installation.
ECHO.
ECHO Do you still want to compile for C-only use (i.e., don't try to link with IDL)?
SET Choice=
SET /P Choice=Enter 'y' or 'n' and press Enter:
IF NOT '%Choice%'=='' SET Choice=%Choice:~0,1%
ECHO.
IF '%Choice%'=='y' GOTO OnlyCompileForC
IF '%Choice%'=='n' GOTO END
ECHO "%Choice%" is not valid. Exiting.
ECHO.
GOTO END



:END

ENDLOCAL


