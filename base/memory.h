#if !defined(SCE_BASE_MEMORY_H)
#define SCE_BASE_MEMORY_H

#include "header.h"

struct _sce_memory_node_s
{
  size_t size;
  void *addr;

  struct _sce_memory_node_s *next;
  struct _sce_memory_node_s *prev;
};

typedef struct _sce_memory_node_s sce_memnode_t;

struct _sce_mem_ctx_s
{
  sce_memnode_t *head;
};

typedef struct _sce_mem_ctx_s sce_mem_ctx;

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus

  SCE_BASE_API void SCE_mem_init (sce_mem_ctx *);
  SCE_BASE_API void SCE_mem_destroy (void);

  SCE_BASE_API void *SCE_Malloc (sce_mem_ctx *, size_t);
  SCE_BASE_API void *SCE_Realloc (sce_mem_ctx *, void *, size_t);
  SCE_BASE_API void SCE_Free (sce_mem_ctx *, void *);

  SCE_BASE_API sce_mem_ctx *_SCE_get_context ();

#if !defined(SCE_MALLOC)
#define SCE_MALLOC(X) SCE_Malloc (NULL, (X))
#endif // SCE_MALLOC

#if !defined(SCE_REALLOC)
#define SCE_REALLOC(X, Y) SCE_Realloc (NULL, (X), (Y))
#endif // SCE_REALLOC

#if !defined(SCE_FREE)
#define SCE_FREE(X) SCE_Free (NULL, (X))
#endif // SCE_FREE

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // SCE_BASE_MEMORY_H
