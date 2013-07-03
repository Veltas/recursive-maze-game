@SETLOCAL

@SET OUTPUTNAME=maze_game.exe
@SET LIBINPUT=user32.lib kernel32.lib Gdiplus.lib Gdi32.lib
@SET PRECOMPILED=
@SET INPUTFILES=main.cpp wtotal_failure_error.c defs_n_consts.cpp game.cpp draw_game.cpp debugger.cpp

@CL /EHsc /Fe%OUTPUTNAME% %LIBINPUT% %PRECOMPILED% %INPUTFILES%

@ENDLOCAL
