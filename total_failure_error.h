/*
	This handles outputting error message and closing of process in case of a startup error.
	It uses GetLastError.
*/

extern
#ifdef __cplusplus
	"C"
#endif
void TotalFailureError();