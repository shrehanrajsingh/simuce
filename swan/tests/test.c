#include <swan.h>

int
main (int argc, char const *argv[])
{
  sce_mem_ctx *ctx = malloc (sizeof (sce_mem_ctx));
  ctx->head = NULL;

  SCE_mem_init (ctx);

  sce_file_t *f = SCE_File_New ("../../tests/test.swan", "r");

  char *fdata = SCE_File_Readall (f);

  _sce_swan_setcode (fdata);
  sce_swan_tokenize ();

  SCE_File_Destroy (f);
  SCE_mem_destroy ();

  return 0;
}