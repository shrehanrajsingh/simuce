#if !defined(FILEIO_H)
#define FILEIO_H

#include "header.h"
#include "memory.h"

/**
 * _sce_file_s
 * @param name File name
 * @param perms File mode
 * @param f File stream
 * @param is_open Is the file open?
 */
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

  /**
   * Create a new sce_file_t with default parameters
   * @param fname Filename
   * @param params Mode
   */
  SCE_BASE_API sce_file_t *SCE_File_New (const char *, const char *);

  /**
   * Read a character from file
   * @param file
   */
  SCE_BASE_API char SCE_File_Readc (sce_file_t *);

  /**
   * Read n characters from file
   * @param file
   * @param n
   */
  SCE_BASE_API char *SCE_File_Readn (sce_file_t *, int);

  /**
   * Read all characters from file
   * @param file
   */
  SCE_BASE_API char *SCE_File_Readall (sce_file_t *);

  /**
   * Destroy allocated file instance
   * @param f
   */
  SCE_BASE_API void SCE_File_Destroy (sce_file_t *);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // FILEIO_H
