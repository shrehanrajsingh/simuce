#include "number_system.h"

SCE_MATH_API sce_int_t
_sce_math_int_new (const char *n, size_t p)
{
  sce_int_t t;
  t.is_neg = *n == '-';
  t.prec = p;
  t.val = SCE_MALLOC (t.prec + 1);

  memset (t.val, '0', t.prec);
  t.val[t.prec] = '\0';

  size_t nl = strlen (n);
  char *end = t.val + t.prec - 1;
  char *nend = (char *)n + nl - 1;

  for (size_t i = t.is_neg; i < nl; i++)
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

SCE_MATH_API int
_sce_math_int_isgreater (sce_int_t *a, sce_int_t *b)
{
  char *aa = a->val;
  char *bb = b->val;

  while (*aa != '\0' && *aa == '0')
    aa++;

  while (*bb != '\0' && *bb == '0')
    bb++;

  int a_size = a->prec - (aa - a->val);
  int b_size = b->prec - (bb - b->val);

  if (a_size != b_size)
    return a_size > b_size;

  return *aa > *bb;
}

SCE_MATH_API int
_sce_math_int_isless (sce_int_t *a, sce_int_t *b)
{
  char *aa = a->val;
  char *bb = b->val;

  while (*aa != '\0' && *aa == '0')
    aa++;

  while (*bb != '\0' && *bb == '0')
    bb++;

  int a_size = a->prec - (aa - a->val);
  int b_size = b->prec - (bb - b->val);

  if (a_size != b_size)
    return a_size < b_size;

  return *aa < *bb;
}

SCE_MATH_API int
_sce_math_int_iseq (sce_int_t *a, sce_int_t *b)
{
  char *aa = a->val;
  char *bb = b->val;

  while (*aa != '\0' && *bb != '\0' && *aa++ == *bb++)
    ;

  return *aa == '\0' && *bb == '\0';
}

SCE_MATH_API sce_int_t
_sce_math_int_sub (sce_int_t *a, sce_int_t *b)
{
  sce_int_t r;
  int is_neg = 0;

  if (ISGR (b, a))
    {
      is_neg = 1;
      sce_int_t *t = b;
      b = a;
      a = t;
    }

  if (a->prec < b->prec)
    _sce_math_int_reset_prec (a, b->prec);
  else
    _sce_math_int_reset_prec (b, a->prec);

  char *aa = a->val + a->prec - 1;
  char *bb = b->val + b->prec - 1;

  r = _sce_math_int_new ("0", a->prec);
  char *rr = r.val + r.prec - 1;
  int carry = 0;

  while (aa != a->val)
    {
      int va = *aa--;
      int vb = *bb--;

      if (va && carry)
        va--;

      if (va < vb)
        {
          va += 10;
          carry = 1;
        }
      else
        carry = 0;

      *rr-- = (char)(va - vb) + '0';
    }

  int va = *aa;
  int vb = *bb;

  *rr = (char)(va - vb) + '0';
  r.is_neg = is_neg;

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

/* SCE_BASE_API sce_int_t
_sce_math_int_mul (sce_int_t *a, sce_int_t *b)
{
  const size_t KARATSUBA_THRESHOLD = 40;

  int result_sign = (a->is_neg != b->is_neg) ? 1 : 0;

  size_t result_prec = a->prec + b->prec;
  sce_int_t result = _sce_math_int_new ("0", result_prec);
  result.is_neg = result_sign;

  if (a->prec < KARATSUBA_THRESHOLD || b->prec < KARATSUBA_THRESHOLD)
    {
      for (size_t i = 0; i < result_prec; i++)
        {
          result.val[i] = '0';
        }
      result.val[result_prec] = '\0';

      for (size_t i = 0; i < b->prec; i++)
        {
          int b_digit = b->val[b->prec - 1 - i] - '0';
          int carry = 0;

          for (size_t j = 0; j < a->prec; j++)
            {
              int a_digit = a->val[a->prec - 1 - j] - '0';
              int pos = result_prec - 1 - (i + j);

              int sum = (result.val[pos] - '0') + b_digit * a_digit + carry;
              result.val[pos] = (sum % 10) + '0';
              carry = sum / 10;
            }

          size_t pos = result_prec - 1 - (i + a->prec);
          while (carry > 0 && pos < result_prec)
            {
              int sum = (result.val[pos] - '0') + carry;
              result.val[pos] = (sum % 10) + '0';
              carry = sum / 10;
              pos--;
            }
        }
    }
  else
    {
      size_t max_prec = (a->prec > b->prec) ? a->prec : b->prec;
      if (max_prec % 2 != 0)
        max_prec++;

      sce_int_t a_copy = _sce_math_int_new ("0", max_prec);
      sce_int_t b_copy = _sce_math_int_new ("0", max_prec);

      memcpy (a_copy.val + max_prec - a->prec, a->val, a->prec);
      memcpy (b_copy.val + max_prec - b->prec, b->val, b->prec);

      size_t m = max_prec / 2;

      sce_int_t a_low = _sce_math_int_new ("0", m);
      sce_int_t a_high = _sce_math_int_new ("0", m);
      sce_int_t b_low = _sce_math_int_new ("0", m);
      sce_int_t b_high = _sce_math_int_new ("0", m);

      memcpy (a_low.val, a_copy.val + m, m);
      memcpy (a_high.val, a_copy.val, m);
      memcpy (b_low.val, b_copy.val + m, m);
      memcpy (b_high.val, b_copy.val, m);

      SCE_FREE (a_copy.val);
      SCE_FREE (b_copy.val);

      sce_int_t z0 = _sce_math_int_mul (&a_low, &b_low);

      sce_int_t z2 = _sce_math_int_mul (&a_high, &b_high);

      sce_int_t a_sum = _sce_math_int_add (&a_low, &a_high);
      sce_int_t b_sum = _sce_math_int_add (&b_low, &b_high);

      SCE_FREE (a_low.val);
      SCE_FREE (a_high.val);
      SCE_FREE (b_low.val);
      SCE_FREE (b_high.val);

      sce_int_t z1_full = _sce_math_int_mul (&a_sum, &b_sum);

      SCE_FREE (a_sum.val);
      SCE_FREE (b_sum.val);

      sce_int_t temp = _sce_math_int_sub (&z1_full, &z0);
      sce_int_t z1 = _sce_math_int_sub (&temp, &z2);

      SCE_FREE (z1_full.val);
      SCE_FREE (temp.val);

      for (size_t i = 0; i < z0.prec; i++)
        {
          result.val[result_prec - 1 - i] = z0.val[z0.prec - 1 - i];
        }

      for (size_t i = 0; i < z1.prec; i++)
        {
          int pos = result_prec - 1 - m - i;
          if (pos >= 0 && pos < result_prec)
            {
              int sum
                  = (result.val[pos] - '0') + (z1.val[z1.prec - 1 - i] - '0');
              int carry = sum / 10;
              result.val[pos] = (sum % 10) + '0';

              int carry_pos = pos - 1;
              while (carry > 0 && carry_pos >= 0)
                {
                  sum = (result.val[carry_pos] - '0') + carry;
                  result.val[carry_pos] = (sum % 10) + '0';
                  carry = sum / 10;
                  carry_pos--;
                }
            }
        }

      for (size_t i = 0; i < z2.prec; i++)
        {
          int pos = result_prec - 1 - 2 * m - i;
          if (pos >= 0 && pos < result_prec)
            {
              int sum
                  = (result.val[pos] - '0') + (z2.val[z2.prec - 1 - i] - '0');
              int carry = sum / 10;
              result.val[pos] = (sum % 10) + '0';

              int carry_pos = pos - 1;
              while (carry > 0 && carry_pos >= 0)
                {
                  sum = (result.val[carry_pos] - '0') + carry;
                  result.val[carry_pos] = (sum % 10) + '0';
                  carry = sum / 10;
                  carry_pos--;
                }
            }
        }

      SCE_FREE (z0.val);
      SCE_FREE (z1.val);
      SCE_FREE (z2.val);
    }

  size_t leading_zeros = 0;
  while (leading_zeros < result_prec - 1 && result.val[leading_zeros] == '0')
    {
      leading_zeros++;
    }

  if (leading_zeros > 0)
    {
      memmove (result.val, result.val + leading_zeros,
               result_prec - leading_zeros + 1);
      result.prec -= leading_zeros;
    }

  return result;
} */

SCE_BASE_API sce_int_t
_sce_math_int_mul (sce_int_t *a, sce_int_t *b)
{
  if (ISGR (b, a))
    {
      sce_int_t *t = b;
      b = a;
      a = t;
    }

  int is_neg = (a->is_neg || b->is_neg) ? 1 : 0;
  sce_int_t r = _sce_math_int_new ("0", a->prec + b->prec);

  char *aa = a->val + a->prec - 1;
  char *bb = b->val + b->prec - 1;
  char *rr = r.val + r.prec - 1;
  int shift = 0;

  while (bb + 1 != b->val)
    {
      int bv = *bb-- - '0';
      int carry = 0;

      while (aa + 1 != a->val)
        {
          int av = *aa-- - '0';

          int p = av * bv + carry;
          carry = p / 10;
          p %= 10;
          p += *rr - '0';

          carry += p / 10;
          p %= 10;

          *rr-- = p + '0';
        }

      shift++;
      aa = a->val + a->prec - 1;
      rr = r.val + r.prec - 1 - shift;
    }

  return r;
}