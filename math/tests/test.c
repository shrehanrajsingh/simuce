#include <simuce-math.h>

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);
  sce_int_t n = _sce_math_int_new ("123456789", 64);

  printf ("%s\n", n.val);

  SCE_mem_destroy ();
  return 0;
}