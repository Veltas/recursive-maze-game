@SETLOCAL

@SET OUTPUTNAME=maze_game.exe
@SET LIBINPUT=user32.lib kernel32.lib Gdiplus.lib Gdi32.lib
@SET PRECOMPILED=wtotal_failure_error.obj defs_n_consts.obj game.obj draw_game.obj
@SET INPUTFILES=main.cpp

@CL /EHsc /Fe%OUTPUTNAME% %LIBINPUT% %PRECOMPILED% %INPUTFILES%

@ENDLOCAL
