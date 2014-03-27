:: TODO - add checks for existing files for make-style building (or write for
:: an actual make utility, this is pretty ugly)

@SETLOCAL

@SET LIBINPUT=user32.lib kernel32.lib Gdiplus.lib Gdi32.lib

@SET CLARGS=/EHsc /Ox /DUNICODE=1

@CL /c %CLARGS% /Fototal_failure_error.obj total_failure_error.c
@CL /c %CLARGS% /Fodefs_n_consts.obj defs_n_consts.cpp
@CL /c %CLARGS% /Fogame.obj game.cpp
@CL /c %CLARGS% /Fodraw_game.obj draw_game.cpp

@CL %CLARGS% /Femaze_game.exe main.cpp total_failure_error.obj defs_n_consts.obj game.obj draw_game.obj %LIBINPUT%

@ENDLOCAL
