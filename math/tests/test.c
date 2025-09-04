#include <simuce-math.h>

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);
  sce_int_t n = NUM2 ("99", 2);
  sce_int_t m = NUM2 ("1", 2);

  printf ("%s\n", n.val);
  printf ("%s\n", m.val);
  printf ("%s\n", ADD (&n, &m).val);
  SCE_mem_destroy ();

  return printf ("Program Ended\n");
}