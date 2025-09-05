#include "token.h"

SCE_SWAN_API sce_token_t
sce_swan_tokenize ()
{
  sce_token_t t;

  if (!peek ())
    {
      t.type = TOK_EOF;
      return t;
    }

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
                {
                  D (printf ("found token '%s'\n", token));

                  t.type = TOK_TOKEN;
                  t.idt_name = SCE_STRDUP ((const char *)token);
                }
              else
                {
                  D (printf ("found identifier '%s'\n", token));

                  t.type = TOK_IDENTIFIER;
                  t.idt_name = SCE_STRDUP ((const char *)token);
                }

              return t;
            }
          else if (ptr_number != number)
            {
              D (printf ("found number '%s'\n", number));

              t.type = TOK_NUMBER;
              t.number = SCE_STRDUP (number);
              return t;
            }

          ptr_tok = token;
          ptr_number = number;
        }
    }

  /* hack to scan last token */
  if (!last++)
    goto _l_check;

  SCE_FREE (number);
  return t;
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