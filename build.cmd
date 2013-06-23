@SETLOCAL





@SET COMPILE=main.cpp wtotal_failure_error.obj user32.lib kernel32.lib
@SET OUTPUT_NAME=maze_game.exe





@CL /EHsc %COMPILE% /Fe%OUTPUT_NAME%
@ENDLOCAL
