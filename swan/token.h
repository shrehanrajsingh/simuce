#if !defined(TOKEN_H)
#define TOKEN_H

#include "globals.h"

#define TOKEN_LET "LET"
#define TOKEN_CALL "CALL"
#define TOKEN_ADD "ADD"
#define TOKEN_SUB "SUB"
#define TOKEN_MUL "MUL"
#define TOKEN_DIV "DIV"
#define TOKEN_BEGIN "BEGIN"
#define TOKEN_ROUTINE "ROUTINE"
#define TOKEN_END "END"
#define TOKEN_REPEAT "REPEAT"
#define TOKEN_RETURN "RETURN"

enum
{
  TOK_TOKEN = 1,
  TOK_IDENTIFIER = 2,
  TOK_NUMBER = 3,
  TOK_OPERATOR = 4,
  TOK_EOF
};

struct sce_token_s
{
  int type;

  union
  {
    char *tok_name;
    char *idt_name;
    char *number;
    char *operator;
  };
};

typedef struct sce_token_s sce_token_t;

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus

  SCE_SWAN_API sce_token_t sce_swan_tokenize ();
  SCE_SWAN_API int sce_swan_isvalidtoken (char *);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // TOKEN_H
