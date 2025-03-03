#include <stdlib.h>
#include <string.h>

#undef exit
#undef abort
#undef calloc
#undef atoi
#undef atol
#undef getenv

typedef struct atexit_key
{
  void (*atexit_func)();
  struct atexit_key *next;
} __ESBMC_atexit_key;

static __ESBMC_atexit_key *__ESBMC_atexits = NULL;

void __atexit_handler()
{
__ESBMC_HIDE:;
  // This is here to prevent k-induction from unwind the next loop unnecessarily
  if(__ESBMC_atexits == NULL)
    return;

  while(__ESBMC_atexits)
  {
    __ESBMC_atexits->atexit_func();
    __ESBMC_atexit_key *__ESBMC_tmp = __ESBMC_atexits->next;
    free(__ESBMC_atexits);
    __ESBMC_atexits = __ESBMC_tmp;
  }
}

int atexit(void (*func)(void))
{
__ESBMC_HIDE:;
  __ESBMC_atexit_key *l =
    (__ESBMC_atexit_key *)malloc(sizeof(__ESBMC_atexit_key));
  if(l == NULL)
    return -1;
  l->atexit_func = func;
  l->next = __ESBMC_atexits;
  __ESBMC_atexits = l;
  return 0;
}

#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-noreturn"
void exit(int status)
{
__ESBMC_HIDE:;
  __atexit_handler();
  __ESBMC_memory_leak_checks();
  __ESBMC_assume(0);
}

void abort(void)
{
__ESBMC_HIDE:;
  __ESBMC_memory_leak_checks();
  __ESBMC_assume(0);
}

void _Exit(int status)
{
__ESBMC_HIDE:;
  __ESBMC_memory_leak_checks();
  __ESBMC_assume(0);
}
#pragma clang diagnostic pop

void *calloc(size_t nmemb, size_t size)
{
__ESBMC_HIDE:;
  if(!nmemb)
    return NULL;

  size_t total_size = nmemb * size;
  void *res = malloc(total_size);
  if(res)
    memset(res, 0, total_size);
  return res;
}

int atoi(const char *nptr)
{
__ESBMC_HIDE:;
  int res;
  /* XXX - does nothing without strabs */
  return res;
}

long atol(const char *nptr)
{
__ESBMC_HIDE:;
  long res;
  /* XXX - does nothing without strabs */
  return res;
}

char *getenv(const char *name)
{
__ESBMC_HIDE:;

  _Bool found;
  if(!found)
    return 0;

  char *buffer;
  size_t buf_size;

  __ESBMC_assume(buf_size >= 1);
  buffer = (char *)malloc(buf_size);
  buffer[buf_size - 1] = 0;
  return buffer;
}

typedef unsigned int gfp_t;

void *__kmalloc(size_t size, gfp_t flags)
{
  (void)flags;
  return malloc(size);
}

void *kmalloc(size_t size, gfp_t flags)
{
  (void)flags;
  return malloc(size);
}

void *kzalloc(size_t size, gfp_t flags)
{
  (void)flags;
  return malloc(size);
}

void *ldv_malloc(size_t size)
{
  return malloc(size);
}

void *ldv_zalloc(size_t size)
{
  return malloc(size);
}

void *kmalloc_array(size_t n, size_t size, gfp_t flags)
{
  return __kmalloc(n * size, flags);
}

void *kcalloc(size_t n, size_t size, gfp_t flags)
{
  (void)flags;
  return calloc(n, size);
}

void kfree(void *objp)
{
  free(objp);
}

size_t strlcat(char *dst, const char *src, size_t siz)
{
  char *d = dst;
  const char *s = src;
  size_t n = siz;
  size_t dlen;

  /* Find the end of dst and adjust bytes left but don't go past end */
  while(n-- != 0 && *d != '\0')
    d++;
  dlen = d - dst;
  n = siz - dlen;

  if(n == 0)
    return (dlen + strlen(s));
  while(*s != '\0')
  {
    if(n != 1)
    {
      *d++ = *s;
      n--;
    }
    s++;
  }
  *d = '\0';

  return (dlen + (s - src)); /* count does not include NUL */
}
