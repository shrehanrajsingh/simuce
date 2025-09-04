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
  char *end = t.val + t.prec - 1;
  char *nend = (char *)n + nl - 1;

  for (size_t i = 0; i < nl; i++)
    *end-- = *nend--;

  return t;
}

SCE_MATH_API sce_int_t
_sce_math_int_add (sce_int_t *a, sce_int_t *b)
{
  sce_int_t r;

  /* fix precision */
  if (a->prec < b->prec)
    _sce_math_int_reset_prec (a, b->prec);
  else
    _sce_math_int_reset_prec (b, a->prec);

  int carry = 0;
  char *aa = a->val + a->prec - 1;
  char *bb = b->val + b->prec - 1;

  r = _sce_math_int_new ("0", a->prec);
  char *rr = r.val + r.prec - 1;

  while (aa != a->val)
    {
      int v = (*aa-- - '0') + (*bb-- - '0') + carry;
      carry = v / 10;
      *rr-- = (char)(v % 10) + '0';
    }

  /* last bit */
  int v = *aa + *bb - '0' - '0' + carry;
  carry = v / 10;
  *rr = (char)(v % 10) + '0';

  if (carry)
    {
      /* raise precision */
      _sce_math_int_reset_prec (&r, r.prec + 1);
      r.val[0] = carry + '0';
    }

  return r;
}

SCE_MATH_API void
_sce_math_int_reset_prec (sce_int_t *a, size_t n)
{
  if (n <= a->prec) /* don't reduce precision */
    return;

  size_t old = a->prec;
  a->prec = n;
  a->val = SCE_REALLOC (a->val, a->prec + 1);

  memmove (a->val + n - old, a->val, old);
  memset (a->val, '0', n - old);
  a->val[a->prec] = '\0';
}