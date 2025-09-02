#include <simuce-base.h>

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);

  sce_file_t *f = SCE_File_New ("../../CMakeLists.txt", "r");

  printf ("%s\n", SCE_File_Readall (f));

  SCE_File_Destroy (f);
  SCE_mem_destroy ();
  free (ctx);

  return 0;
}