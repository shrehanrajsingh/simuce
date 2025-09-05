#if !defined(DEBUG_H)
#define DEBUG_H

#include "header.h"

#if !defined(D)
#define D(X) X
#endif // D

#if !defined(dprintf)
#define dprintf(...) printf (__VA_ARGS__)
#endif // dprintf

#endif // DEBUG_H
