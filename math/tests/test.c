#include <simuce-math.h>

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);
  sce_int_t a = NUM2 ("89", 2);
  sce_int_t b = NUM2 ("1", 2);
  sce_int_t c
      = NUM ("1028372910281922349198829294887162623490031882891984738");
  sce_int_t d = NUM ("10109293829438783439844578459485948694864098");

  NUM_PRINT (SUB (&a, &b));
  NUM_PRINT (SUB (&b, &a));
  NUM_PRINT (ADD (&c, &d));
  NUM_PRINT (SUB (&c, &d));

  SCE_mem_destroy ();
  return printf ("Program Ended\n");
}