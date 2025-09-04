#include "token.h"

SCE_SWAN_API void
sce_swan_tokenize ()
{
  const size_t size_token = 256;
  size_t size_number = 1024;

  char token[size_token];
  char *number = SCE_MALLOC (size_number);

  char *ptr_tok = token;
  char *ptr_number = number;

  char c;
  int last = 0;

  while ((c = fetch ()))
    {
    _start:
      if (c >= '0' && c <= '9')
        *ptr_number++ = c;

      if (ptr_tok == token)
        {
          if (isalpha (c))
            *ptr_tok++ = c;
        }
      else
        {
          if (isalnum (c))
            *ptr_tok++ = c;
        }

      if (isspace (c) || c == ',')
        {
        _l_check:
          *ptr_number = '\0';
          *ptr_tok = '\0';

          if (ptr_tok != token)
            {
              if (sce_swan_isvalidtoken (token))
                printf ("found token '%s'\n", token);
              else
                printf ("found identifier '%s'\n", token);
            }
          else if (ptr_number != number)
            {
              printf ("found number '%s'\n", number);
            }

          ptr_tok = token;
          ptr_number = number;
        }
    }

  /* hack to scan last token */
  if (!last++)
    goto _l_check;

  SCE_FREE (number);
}

SCE_SWAN_API int
sce_swan_isvalidtoken (char *t)
{
  const char *toks[] = { TOKEN_ADD,    TOKEN_BEGIN,   TOKEN_CALL, TOKEN_DIV,
                         TOKEN_END,    TOKEN_LET,     TOKEN_MUL,  TOKEN_REPEAT,
                         TOKEN_RETURN, TOKEN_ROUTINE, TOKEN_SUB,  NULL };

  int i = 0;
  while (toks[i] != NULL && strcmp (toks[i], t))
    i++;

  return toks[i] != NULL;
}