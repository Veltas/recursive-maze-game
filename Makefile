
CLARGS=/EHsc /Ox /DUNICODE=1
LIBINPUT=user32.lib kernel32.lib Gdiplus.lib Gdi32.lib

all: mkdirs bin\maze_game.exe

mkdirs:
	MKDIR bin obj

clean:
	DEL bin\*.exe obj\*.obj

bin\maze_game.exe: obj\main.obj obj\total_failure_error.obj obj\defs_n_consts.obj obj\game.obj obj\draw_game.obj
	CL $(CLARGS) /Fe$@ $** $(LIBINPUT)

obj\main.obj: src\main.cpp
	CL /c $(CLARGS) /Fo$@ $**

obj\total_failure_error.obj: src\total_failure_error.c
	CL /c $(CLARGS) /Fo$@ $**

obj\defs_n_consts.obj: src\defs_n_consts.cpp
	CL /c $(CLARGS) /Fo$@ $**

obj\game.obj: src\game.cpp
	CL /c $(CLARGS) /Fo$@ $**

obj\draw_game.obj: src\draw_game.cpp
	CL /c $(CLARGS) /Fo$@ $**
