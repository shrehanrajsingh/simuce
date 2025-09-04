#include "globals.h"

static char *code;

SCE_SWAN_API void
_sce_swan_setcode (char *c)
{
  code = c;
}

SCE_SWAN_API char
_sce_swan_fetch ()
{
  return *code++;
}

SCE_SWAN_API char
_sce_swan_peek ()
{
  return *code;
}

SCE_SWAN_API char
_sce_swan_peeknext ()
{
  return *(code + 1);
}

SCE_SWAN_API char *
_sce_swan_getcode ()
{
  return code;
}