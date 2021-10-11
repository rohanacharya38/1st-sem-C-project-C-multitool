@echo off
if exist "SDL2MinGw/" goto DontDown
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
echo Downloading SDL2_image
curl "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz" --output SDL2MinGw_image.tar.gz
tar -xf SDL2MingW_image.tar.gz -C SDL2MinGw
del SDL2MingW_image.tar.gz
:DontDown

if  "%PROCESSOR_ARCHITECTURE%"=="x86" (
    echo set the include path 32 bit
set SDL2MinGw_Include="SDL2MinGw/SDL2-2.0.14/i686-w64-mingw32/include/"
set SDL2MinGw_Library="SDL2MinGw/SDL2-2.0.14/i686-w64-mingw32/lib/"
set SDL2MinGw_DLL="SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\bin\SDL2.dll"
set SDL2MinGw_ttf_Library="SDL2MinGw/SDL2_ttf-2.0.15/i686-w64-mingw32/lib/"
set SDL2MinGw_ttf_DLL="SDL2MinGw\SDL2_ttf-2.0.15\i686-w64-mingw32\bin\*.dll"
set SDL2MinGw_image_Library="SDL2MinGw/SDL2_image-2.0.5/i686-w64-mingw32/lib/"
set SDL2MinGw_image_DLL="SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\bin\*.dll"
)
if  "%PROCESSOR_ARCHITECTURE%"=="x86" (echo copying 32 bit dll
xcopy /Y SDL2MinGw\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2\SDL_ttf.h SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\include\SDL2
xcopy /Y SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2\SDL_image.h SDL2MinGw\SDL2-2.0.14\i686-w64-mingw32\include\SDL2
xcopy /Y %SDL2MinGw_DLL%
xcopy /Y %SDL2MinGw_ttf_DLL%
xcopy /Y "SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\bin\SDL2_image.dll"
xcopy /Y "SDL2MinGw\SDL2_image-2.0.5\i686-w64-mingw32\bin\libpng16-16.dll"
)
if  "%PROCESSOR_ARCHITECTURE%"=="AMD64" (echo copying 64 bit dlls
set SDL2MinGw_Include="SDL2MinGw/SDL2-2.0.14/x86_64-w64-mingw32/include/"
set SDL2MinGw_Library="SDL2MinGw/SDL2-2.0.14/x86_64-w64-mingw32/lib/"
set SDL2MinGw_DLL="SDL2MinGw\SDL2-2.0.14\x86_64-w64-mingw32\bin\SDL2.dll"

set SDL2MinGw_ttf_Library="SDL2MinGw/SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib/"
set SDL2MinGw_ttf_DLL="SDL2MinGw\SDL2_ttf-2.0.15\x86_64-w64-mingw32\bin\SDL2_ttf.dll"

set SDL2MinGw_image_Library="SDL2MinGw/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/"
set SDL2MinGw_image_DLL="SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\bin\*.dll"

xcopy /Y %SDL2MinGw_DLL%
xcopy /Y %SDL2MinGw_ttf_DLL%
xcopy /Y %SDL2MinGw_mixer_DLL%
xcopy /Y "SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\bin\SDL2_image.dll"
xcopy /Y "SDL2MinGw\SDL2_image-2.0.5\x86_64-w64-mingw32\bin\libpng16-16.dll"
xcopy /Y "SDL2MinGw\SDL2_ttf-2.0.15\x86_64-w64-mingw32\bin\libfreetype-6.dll"

)
set SourceFiles="source/mainmenu.c"
call    gcc     -mwindows   -I%SDL2MinGw_Include%   -L%SDL2MinGw_Library%       -L%SDL2MinGw_ttf_Library%   -L%SDL2MinGw_image_Library%     %SourceFiles%	-o	mainmenu 	-lmingw32	-lSDL2_ttf	-lSDL2_mixer -lSDL2main	-lSDL2 	-lSDL2_image	
echo ---------------------------------------	
echo Gcc Build Complete
echo ----------------------------------------
pause