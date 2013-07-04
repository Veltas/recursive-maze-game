/* LOL predefs */

#ifndef _PREDEFS_HPP_INCLUDED_
#define _PREDEFS_HPP_INCLUDED_

#define UNICODE 1
//#define DEBUG

#define NTDDI_VERSION 0x5010000
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
// Go digging through Windows.h if you want more NO-XXXX defs.

#ifdef DEBUG
#define DEBUG_OUT(a) globalDebugger->PrintLine( a )
#endif

#ifndef DEBUG
#define DEBUG_OUT(a) a
#endif

#ifdef DEBUG
#define DEBUG_VAL(a, b) globalDebugger->PrintLine( a , b )
#endif

#ifndef DEBUG
#define DEBUG_VAL(a, b) a , b
#endif

#ifdef DEBUG
#define DEBUG_ONLY(a) a
#endif

#ifndef DEBUG
#define DEBUG_ONLY(a) 0
#endif

#endif
