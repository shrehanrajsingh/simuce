#include "number_system.h"

SCE_MATH_API sce_int_t
_sce_math_int_new (const char *n, size_t p)
{
  sce_int_t t;
  t.prec = p;
  t.val = SCE_MALLOC (t.prec + 1);

  memset (t.val, '0', t.prec);
  t.val[t.prec] = '\0';

  size_t nl = strlen (n);
  char *end = t.val + t.prec;
  char *nend = n + nl - 1;

  for (size_t i = 0; i < nl; i++)
    *end-- = *nend--;

  return t;
}