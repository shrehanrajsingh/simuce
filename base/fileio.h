#if !defined(FILEIO_H)
#define FILEIO_H

#include "header.h"
#include "memory.h"

struct _sce_file_s
{
  char name[64];
  char perms[16];

  FILE *f;
  int is_open;
};

typedef struct _sce_file_s sce_file_t;

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus

  SCE_BASE_API sce_file_t *SCE_File_New ();

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // FILEIO_H
