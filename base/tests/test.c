#include <simuce-base.h>

#define TEST(X) test##X ()

void
test1 ()
{
  sce_file_t *f = SCE_File_New ("../../CMakeLists.txt", "r");

  char *p;
  printf ("%s\n", p = SCE_File_Readall (f));
  SCE_FREE (p);

  SCE_File_Destroy (f);
}

void
test2 ()
{
  void *p1 = SCE_MALLOC (40);
  void *p2 = SCE_MALLOC (50);
  void *p3 = SCE_MALLOC (60);
  void *p4 = SCE_MALLOC (70);

  // sce_mem_ctx *ct = _SCE_get_context ();

  // while (ct->head)
  //   {
  //     printf ("%p\n", ct->head);
  //     ct->head = ct->head->next;
  //   }

  SCE_FREE (p1);
  SCE_FREE (p2);
  SCE_FREE (p3);
  SCE_FREE (p4);
  // SCE_FREE (p4);
}

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);

  TEST (1);
  TEST (2);

  SCE_mem_destroy ();
  free (ctx);
  return 0;
}