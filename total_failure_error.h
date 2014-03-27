/*
	This handles outputting error message and closing of process in case of a startup error.
	It uses GetLastError.
*/

#pragma once

extern
#ifdef __cplusplus
	"C"
#endif
void TotalFailureError();
