@echo off
md bin
pushd bin
copy  ..\SDL2\lib\*.dll
popd
setlocal
set source_name="source\mainmenu.c"
set executable_name=bin\main.exe
set lib_path=SDL2\lib\
set include_path=SDL2\include\
set compiler_flags=/nologo /EHsc /Zi /FC
@REM set libraries=SDL2.lib SDL2main.lib user32.lib shell32.lib gdi32.lib
set libraries=SDL2.lib SDL2main.lib user32.lib shell32.lib gdi32.lib SDL2_ttf.lib SDL2_image.lib SDL2test.lib
cl   %source_name% /Fe%executable_name% %compiler_flags% /I%include_path% /link /LIBPATH:%lib_path% %libraries% /SUBSYSTEM:windows