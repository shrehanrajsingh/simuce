#if !defined(GLOBALS_H)
#define GLOBALS_H

#include "swan_header.h"

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus

  SCE_SWAN_API void _sce_swan_setcode (char *);

  SCE_SWAN_API char _sce_swan_fetch (); /* return char and increment code */

  SCE_SWAN_API char
  _sce_swan_peek (); /* return char without incrementing code */

  SCE_SWAN_API char
  _sce_swan_peeknext (); /* return next char without incrementing code */

  SCE_SWAN_API char *_sce_swan_getcode ();

#if !defined(fetch)
#define fetch() _sce_swan_fetch ()
#endif // fetch

#if !defined(peek)
#define peek() _sce_swan_peek ()
#endif // fetch

#if !defined(next)
#define next() _sce_swan_peeknext ()
#endif // fetch

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // GLOBALS_H
