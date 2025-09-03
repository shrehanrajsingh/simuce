#include "memory.h"

static sce_mem_ctx *context = NULL;

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
  if (context == NULL)
    return;

  sce_memnode_t *head = HEAD (context);
  if (head == NULL)
    {
      context = NULL;
      return;
    }

  do
    {
      free (head->addr);
      head = head->next;
    }
  while (head != NULL && head != HEAD (context));

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

  return nt->addr;
}

SCE_BASE_API void *
SCE_Realloc (sce_mem_ctx *ctx, void *old, size_t n)
{
  CONTEXT_INIT (ctx);
  sce_memnode_t *mt = NULL;
  sce_memnode_t *hd = HEAD (ctx);

  if (hd == NULL)
    {
      perror ("Error: pointer realloc'ed was not allocated. Did you call "
              "SCE_Malloc (...)?");
      exit (-1);
    }

  do
    {
      if ((char *)hd->addr <= (char *)old
          && (char *)hd->addr + hd->size > (char *)old)
        {
          mt = hd;
          break;
        }

      hd = hd->next;
    }
  while (hd != NULL && HEAD (ctx) != hd);

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

      return newptr;
    }

  return NULL;
}

SCE_BASE_API void
SCE_Free (sce_mem_ctx *ctx, void *ptr)
{
  CONTEXT_INIT (ctx);

  sce_memnode_t *mt = NULL;
  sce_memnode_t *hd = HEAD (ctx);

  if (hd == NULL)
    {
      perror ("Error: pointer to free was not allocated. Did you call "
              "SCE_Malloc (...)?");
      exit (-1);
    }

  // printf ("%p\n", ptr);
  do
    {
      // printf ("%p %p\n", ptr, HEAD (ctx)->addr);
      if (hd->addr <= ptr && (char *)hd->addr + hd->size > (char *)ptr)
        {
          mt = hd;
          break;
        }

      hd = hd->next;
    }
  while (HEAD (ctx) != NULL && HEAD (ctx) != hd);

  if (mt == NULL)
    {
      perror ("Error: pointer to free was not allocated. Did you call "
              "SCE_Malloc (...)?");
      exit (-1);
    }
  else
    {
      free (mt->addr);

      if (mt->next == mt && mt->prev == mt)
        {
          HEAD (ctx) = NULL;
        }
      else
        {
          mt->prev->next = mt->next;
          mt->next->prev = mt->prev;

          if (HEAD (ctx) == mt)
            HEAD (ctx) = mt->next;
        }

      free (mt);
    }
}

SCE_BASE_API sce_mem_ctx *
_SCE_get_context ()
{
  return context;
}