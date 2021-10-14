@echo off

setlocal

set SourceFiles="../../source/mainmenu.c"
set OutputName=mainmenu.exe

set CLFlags=-Od
set CLANGFlags=-g -gcodeview
set GCCFlags=-O -mwindows


where cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto CheckForClang
goto DownloadSDL
:CheckForClang
where clang >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto SkipDownloadSDL
:DownloadSDL
if exist "SDL2/" goto SkipDownloadSDL
mkdir SDL2
echo ----------------------------------------
echo Downloading SDL
echo ----------------------------------------
curl "https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip" --output SDL2.zip
tar -xf SDL2.zip -C SDL2
del SDL2.zip
echo ----------------------------------------
echo Downloading SDL_ttf
echo ----------------------------------------
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip" --output SDL2_ttf.zip
tar -xf  SDL2_ttf.zip -C SDL2
del SDL2_ttf.zip
xcopy /Y SDL2\SDL2_ttf-2.0.15\include\SDL_ttf.h SDL2\SDL2-2.0.14\include\
curl "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip" --output SDL2_image.zip
tar -xf SDL2_image.zip -C SDL2
del SDL2_image.zip
xcopy /Y SDL2\SDL2_ttf-2.0.15\include\SDL_ttf.h SDL2\SDL2-2.0.14\include\
xcopy /Y SDL2\SDL2_image-2.0.5\include\SDL_image.h SDL2\SDL2-2.0.14\include\
:SkipDownloadSDL

where gcc >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto SkipDownloadSDLMinGw

if exist "SDL2MinGw/" goto SkipDownloadSDLMinGw
mkdir SDL2MinGw
echo ----------------------------------------
echo Downloading SDLMinGw
echo ----------------------------------------
curl "https://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz" --output SDL2MinGw.tar.gz
tar -xf SDL2MinGw.tar.gz -C SDL2MinGw
del SDL2MinGw.tar.gz
echo ----------------------------------------
echo Downloading SDLMinGw_ttf
echo ----------------------------------------
curl "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-mingw.tar.gz" --output SDL2MinGw_ttf.tar.gz
tar -xf SDL2MinGw_ttf.tar.gz -C SDL2MinGw
del SDL2MinGw_ttf.tar.gz

echo --------------------------------------
echo Downloading SDL2_image
echo --------------------------------------
curl "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz" --output SDL2MinGw_image.tar.gz
tar -xf SDL2MinGw_image.tar.gz -C SDL2MinGw
del SDL2MingW_image.tar.gz


:SkipDownloadSDLMinGw
if  "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
     echo set the include path 64 bit
set SDL2_Include="../../SDL2/SDL2-2.0.14/include/"
set SDL2_Library="../../SDL2/SDL2-2.0.14/lib/x64"
set SDL2_DLL=..\..\SDL2\SDL2-2.0.14\lib\x64\SDL2.dll
set SDL2_ttf_Library="../../SDL2/SDL2_ttf-2.0.15/lib/x64"
set SDL2_ttf_DLL=..\..\SDL2\SDL2_ttf-2.0.15\lib\x64\*.dll
set SDL2_image_Library="../../SDL2/SDL2_image-2.0.5/lib/x64"
set SDL2_image_DLL="../../SDL2/SDL2_image-2.0.5/lib/x64/*.dll"
set SDL2_image_DLL=..\..\SDL2\SDL2_image-2.0.5\lib\x64\*.dll

@REM xcopy /Y SDL2MinGw\SDL2_ttf-2.0.15\x86_64-w64-mingw32\include\SDL2\SDL_ttf.h SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
@REM xcopy /Y SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2\SDL_image.h SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
set SDL2MinGw_Include="../../SDL2MinGw/SDL2-2.0.14/x86_64-w64-mingw32/include/"
set SDL2MinGw_Library="../../SDL2MinGw/SDL2-2.0.14/x86_64-w64-mingw32/lib/"
set SDL2MinGw_DLL="../../SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\bin\SDL2.dll"

set SDL2MinGw_ttf_Library="../../SDL2MinGw/SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib/"
set SDL2MinGw_image_Library="../../SDL2MinGw/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/"
set SDL2MinGw_ttf_DLL="../../SDL2MinGw\SDL2_ttf-2.0.15\x86_64-w64-mingw32\bin\*.dll"
set SDL2MinGw_image_DLL="../../SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\bin\*.dll"
)
if  "%PROCESSOR_ARCHITECTURE%"=="x86" (
    echo set the include path 32 bit

set SDL2_Include="../../SDL2/SDL2-2.0.14/include/"
set SDL2_Library="../../SDL2/SDL2-2.0.14/lib/x86"
set SDL2_DLL=..\..\SDL2\SDL2-2.0.14\lib\x86\SDL2.dll
set SDL2_ttf_Library="../../SDL2/SDL2_ttf-2.0.15/lib/x86"
set SDL2_ttf_DLL=..\..\SDL2\SDL2_ttf-2.0.15\lib\x86\*.dll
set SDL2_image_Library="../../SDL2/SDL2_image-2.0.5/lib/x86"
set SDL2_image_DLL=..\..\SDL2\SDL2_image-2.0.5\lib\x86\*.dll

set SDL2MinGw_Include="../../SDL2MinGw/SDL2-2.0.14/i686-w64-mingw32/include/"
set SDL2MinGw_Library="../../SDL2MinGw/SDL2-2.0.14/i686-w64-mingw32/lib/"
set SDL2MinGw_DLL="../../SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\bin\SDL2.dll"

set SDL2MinGw_ttf_Library="../../SDL2MinGw/SDL2_ttf-2.0.15/i686-w64-mingw32/lib/"
set SDL2MinGw_image_Library="../../SDL2MinGw/SDL2_image-2.0.5/i686-w64-mingw32/lib/"
set SDL2MinGw_ttf_DLL="../../SDL2MinGw\SDL2_ttf-2.0.15\i686-w64-mingw32\bin\*.dll"
set SDL2MinGw_image_DLL="../../SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\bin\*.dll"
)
if not exist "bin"  mkdir bin
:MSVC
where cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto SkipMSVC
echo Building with MSVC
if not exist "SDL2\SDL2-2.0.14\include\SDL2\" mkdir "SDL2\SDL2-2.0.14\include\SDL2\"
xcopy /Y "SDL2\SDL2-2.0.14\include\*.h"   "SDL2\SDL2-2.0.14\include\SDL2\" 
if not exist "bin\MsvcBuild" mkdir bin\MsvcBuild
pushd bin\MsvcBuild
xcopy /Y SDL2\SDL2_ttf-2.0.15\include\SDL2\SDL_ttf.h ..\..\SDL2\SDL2-2.0.14\include\SDL2
xcopy /Y SDL2\SDL2_image-2.0.5\include\SDL2\SDL_image.h ..\..\SDL2\SDL2-2.0.14\include\SDL2

xcopy %SDL2_DLL% ..\..\bin\MsvcBuild /Y
xcopy %SDL2_ttf_DLL% ..\..\bin\MsvcBuild /Y
xcopy %SDL2_image_DLL% ..\..\bin\MsvcBuild /Y
xcopy /Y "../../SDL2/SDL2-2.0.14/lib/x86/SDL2.dll" .\
call cl  -Zi -I%SDL2_Include% %CLFlags% -nologo -Zi -EHsc %SourceFiles% -Fe%OutputName% /link /LIBPATH:%SDL2_Library% SDL2.lib SDL2main.lib Shell32.lib Comdlg32.lib /LIBPATH:%SDL2_ttf_Library% SDL2_ttf.lib /LIBPATH:%SDL2_image_Library% SDL2_image.lib /subsystem:windows
popd
echo MSVC Build Complete
echo ----------------------------------------
goto CLANG

:SkipMSVC
echo MSVC not found. Skipping build with MSVC. 
echo ----------------------------------------

:CLANG
where clang >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto SkipCLANG
echo Building with CLANG
if not exist "bin\ClangBuild" mkdir bin\ClangBuild
pushd bin\ClangBuild
xcopy %SDL2_DLL% .\ /Y
xcopy %SDL2_ttf_DLL% .\ /Y
xcopy %SDL2_image_DLL% .\ /Y
xcopy 

call clang -I%SDL2_Include% -L%SDL2_Library% -L%SDL2_ttf_Library% -L%SDL2_image_Library% %CLANGFlags% %SourceFiles% -o %OutputName% -lSDL2main -lSDL2 -lSDL2_ttf -lShell32 -lComdlg32 -Xlinker -subsystem:windows
echo Clang Build Complete
echo ----------------------------------------
popd
goto GCC

:SkipCLANG
echo Clang not found. Skipping build with Clang. 
echo ----------------------------------------

:GCC
where gcc >nul 2>nul
IF %ERRORLEVEL% NEQ 0 goto SkipGCC
echo Building with GCC
if not exist "bin\GccBuild" mkdir bin\GccBuild
if  "%PROCESSOR_ARCHITECTURE%"=="AMD64" (
xcopy /Y SDL2MinGw\SDL2_ttf-2.0.15\x86_64-w64-mingw32\include\SDL2\SDL_ttf.h SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
xcopy /Y SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2\SDL_image.h SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
)
if  "%PROCESSOR_ARCHITECTURE%"=="x86" (
    xcopy /Y SDL2MinGw\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2\SDL_ttf.h SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\include\SDL2
xcopy /Y SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2\SDL_image.h SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\include\SDL2
)

pushd bin\GccBuild

xcopy %SDL2MinGw_DLL% .\ /Y
xcopy %SDL2MinGw_ttf_DLL% .\ /Y
xcopy %SDL2MinGw_image_DLL% .\ /Y


call gcc -mwindows -I%SDL2MinGw_Include% -L%SDL2MinGw_Library% -L%SDL2MinGw_ttf_Library% -L%SDL2MinGw_image_Library% %GCCFlags% %SourceFiles% -o %OutputName% -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf  -lSDL2_image -lComdlg32
popd
xcopy bin\GccBuild\*.dll .\ /Y
xcopy bin\GccBuild\*.exe .\ /Y
rmdir /Q  /S bin

echo Gcc Build Complete
echo ----------------------------------------
popd
goto Finished

:SkipGCC
echo Gcc not found. Skipping build with Gcc. 
echo ----------------------------------------

:Finished