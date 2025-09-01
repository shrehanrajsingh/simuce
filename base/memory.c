#include "memory.h"

sce_mem_ctx *context = NULL;

#define ASSERT_CONTEXT_IS_SET(X)                                              \
  if ((X) == NULL && context == NULL)                                         \
    {                                                                         \
      perror ("Error: global sce_mem_ctx is not set. Did you call "           \
              "SCE_mem_init (...)?");                                         \
      exit (-1);                                                              \
    }

#define CONTEXT_SET(X)                                                        \
  if ((X) == NULL)                                                            \
    {                                                                         \
      (X) = context;                                                          \
    }

#define CONTEXT_INIT(ctx)                                                     \
  ASSERT_CONTEXT_IS_SET (ctx);                                                \
  CONTEXT_SET (ctx);

#define HEAD(ctx) (ctx->head)

SCE_BASE_API void
SCE_mem_init (sce_mem_ctx *ctx)
{
  if (context != NULL)
    SCE_mem_destroy ();
  context = ctx;
}

SCE_BASE_API void
SCE_mem_destroy (void)
{
  context = NULL;
}

SCE_BASE_API void *
SCE_Malloc (sce_mem_ctx *ctx, size_t s)
{
  CONTEXT_INIT (ctx);

  sce_memnode_t *nt = malloc (sizeof (*nt));
  nt->addr = malloc (s);
  nt->next = NULL;
  nt->prev = NULL;
  nt->size = s;

  if (HEAD (ctx) == NULL)
    HEAD (ctx) = nt;
  else if (HEAD (ctx)->next == NULL)
    {
      HEAD (ctx)->next = nt;
      nt->next = HEAD (ctx);
      nt->prev = HEAD (ctx);
      HEAD (ctx)->prev = nt;
    }
  else
    {
      nt->next = HEAD (ctx)->next;
      HEAD (ctx)->next->prev = nt;
      HEAD (ctx)->next = nt;
      nt->prev = HEAD (ctx);
    }
}

SCE_BASE_API void *
SCE_Realloc (sce_mem_ctx *ctx, void *old, size_t n)
{
  CONTEXT_INIT (ctx);
  sce_memnode_t *mt = NULL;
  sce_memnode_t *hd = HEAD (ctx);

  while (HEAD (ctx) != NULL && HEAD (ctx) != hd)
    {
      if (HEAD (ctx)->addr <= old && HEAD (ctx)->addr + HEAD (ctx)->size > old)
        {
          mt = HEAD (ctx);
          break;
        }

      HEAD (ctx) = HEAD (ctx)->next;
    }

  if (mt == NULL)
    {
      perror ("Error: pointer realloc'ed was not allocated. Did you call "
              "SCE_Malloc (...)?");
      exit (-1);
    }
  else
    {
      void *newptr = realloc (old, n);
      mt->size = n;

      if (newptr != mt->addr)
        mt->addr = newptr;
    }
}

SCE_BASE_API void
SCE_Free (sce_mem_ctx *ctx, void *ptr)
{
  CONTEXT_INIT (ctx);

  sce_memnode_t *mt = NULL;
  sce_memnode_t *hd = HEAD (ctx);

  while (HEAD (ctx) != NULL && HEAD (ctx) != hd)
    {
      if (HEAD (ctx)->addr <= ptr && HEAD (ctx)->addr + HEAD (ctx)->size > ptr)
        {
          mt = HEAD (ctx);
          break;
        }

      HEAD (ctx) = HEAD (ctx)->next;
    }

  if (mt == NULL)
    {
      perror ("Error: pointer to free was not allocated. Did you call "
              "SCE_Malloc (...)?");
      exit (-1);
    }
  else
    {
      free (mt->addr);

      if (mt->prev != NULL)
        mt->prev->next = mt->next;
      free (mt);
    }
}