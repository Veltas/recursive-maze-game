/* LOL predefs */

#ifndef _PREDEFS_HPP_INCLUDED_
#define _PREDEFS_HPP_INCLUDED_

#define UNICODE 1
#define DEBUG



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
