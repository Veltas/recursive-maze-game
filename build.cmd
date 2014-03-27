:: TODO - add checks for existing files for make-style building (or write for
:: an actual make utility, this is pretty ugly)

@SETLOCAL

@SET LIBINPUT=user32.lib kernel32.lib Gdiplus.lib Gdi32.lib

@SET CLARGS=/EHsc /Ox /DUNICODE=1

@MKDIR bin obj

@CL /c %CLARGS% /Foobj\total_failure_error.obj src\total_failure_error.c
@CL /c %CLARGS% /Foobj\defs_n_consts.obj src\defs_n_consts.cpp
@CL /c %CLARGS% /Foobj\game.obj src\game.cpp
@CL /c %CLARGS% /Foobj\draw_game.obj src\draw_game.cpp
@CL /c %CLARGS% /Foobj\main.obj src\main.cpp

@CL %CLARGS% /Febin\maze_game.exe obj\main.obj obj\total_failure_error.obj obj\defs_n_consts.obj obj\game.obj obj\draw_game.obj %LIBINPUT%

@ENDLOCAL
