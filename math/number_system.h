#if !defined(SCE_NUMBER_SYSTEM)
#define SCE_NUMBER_SYSTEM

#include "math_header.h"

struct sce_int_s
{
  int is_neg;
  char *val;
  size_t prec;
};

typedef struct sce_int_s sce_int_t;

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus

  SCE_MATH_API sce_int_t _sce_math_int_new (const char *, size_t);
  SCE_MATH_API sce_int_t _sce_math_int_add (sce_int_t *, sce_int_t *);
  SCE_MATH_API sce_int_t _sce_math_int_sub (sce_int_t *, sce_int_t *);
  SCE_BASE_API sce_int_t _sce_math_int_mul (sce_int_t *, sce_int_t *);
  SCE_MATH_API int _sce_math_int_isgreater (sce_int_t *, sce_int_t *);
  SCE_MATH_API int _sce_math_int_isless (sce_int_t *, sce_int_t *);
  SCE_MATH_API int _sce_math_int_iseq (sce_int_t *, sce_int_t *);
  SCE_MATH_API void _sce_math_int_reset_prec (sce_int_t *, size_t);

#if !defined(SCE_MATH_INT_DEFAULT_PREC)
#define SCE_MATH_INT_DEFAULT_PREC 128
#endif // SCE_MATH_INT_DEFAULT_PREC

#if !defined(NUM_PRINT)
#define NUM_PRINT(X)                                                          \
  do                                                                          \
    {                                                                         \
      sce_int_t t = (X);                                                      \
      printf ("%c%s\n", t.is_neg ? '-' : '+', t.val);                         \
    }                                                                         \
  while (0)
#endif // NUM_PRINT

#if !defined(NUM)
#define NUM(X) _sce_math_int_new ((X), SCE_MATH_INT_DEFAULT_PREC)
#endif // NUM

#if !defined(NUM2)
#define NUM2(X, Y) _sce_math_int_new ((X), (Y))
#endif // NUM

#if !defined(ADD)
#define ADD(X, Y) _sce_math_int_add ((X), (Y))
#endif // ADD

#if !defined(SUB)
#define SUB(X, Y) _sce_math_int_sub ((X), (Y))
#endif // SUB

#if !defined(MUL)
#define MUL(X, Y) _sce_math_int_mul ((X), (Y))
#endif // MUL

#if !defined(ISGR)
#define ISGR(X, Y) _sce_math_int_isgreater ((X), (Y))
#endif // ISGR

#if !defined(ISLE)
#define ISLE(X, Y) _sce_math_int_isless ((X), (Y))
#endif // ISLE

#if !defined(ISEQ)
#define ISEQ(X, Y) _sce_math_int_iseq ((X), (Y))
#endif // ISEQ

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // SCE_NUMBER_SYSTEM
