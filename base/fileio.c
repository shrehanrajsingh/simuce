#include "fileio.h"

#define ASSERT_FILE_IS_OPEN(X)                                                \
  if (!(X)->is_open)                                                          \
    {                                                                         \
      fprintf (stderr, "Error (%s: %d): reading from a closed file",          \
               __FILE__, __LINE__);                                           \
      exit (-1);                                                              \
    }

SCE_BASE_API sce_file_t *
SCE_File_New (const char *fname, const char *mode)
{
  sce_file_t *f = SCE_MALLOC (sizeof (sce_file_t));
  f->f = fopen (fname, mode);
  if (!!f->f)
    f->is_open = 1;

  strncpy (f->name, fname, 64);
  strncpy (f->perms, mode, 16);

  return f;
}

SCE_BASE_API char
SCE_File_Readc (sce_file_t *f)
{
  ASSERT_FILE_IS_OPEN (f);
  return fgetc (f->f);
}

SCE_BASE_API char *
SCE_File_Readn (sce_file_t *f, int n)
{
  ASSERT_FILE_IS_OPEN (f);

  char *r = SCE_MALLOC (n + 1);
  char *p = r;

  int c;
  int i = 0;
  while (i < n && (c = fgetc (f->f)) != EOF)
    {
      *p++ = (char)c;
      i++;
    }
  *p = '\0';

  return r;
}

SCE_BASE_API char *
SCE_File_Readall (sce_file_t *f)
{
  ASSERT_FILE_IS_OPEN (f);
  fseek (f->f, 0, SEEK_END);

  long fsize = ftell (f->f);

  if (fsize == -1)
    {
      perror ("Error: ftell returned -1");
      exit (-1);
    }

  fseek (f->f, 0, SEEK_SET);
  return SCE_File_Readn (f, (int)fsize);
}

SCE_BASE_API void
SCE_File_Destroy (sce_file_t *f)
{
  if (f->is_open)
    fclose (f->f);
  f->is_open = 0;

  SCE_FREE (f);
}