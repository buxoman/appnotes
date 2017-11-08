#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


/* 判断是否回文数 */
int isPn(int n)
{
  char nstr[16];
  char reverse[16];
  int  sz = 0;
  int  i = 0;
  
  memset(nstr, 0, sizeof(nstr));
  memset(reverse, 0, sizeof(reverse));

  sprintf(nstr, "%d", n);
  sz = strlen(nstr);

  for (i = 0; i < sz; ++i) {
    reverse[sz - 1 -i] = nstr[i];
  }

  if (strncmp(nstr, reverse, sz) == 0) {
    return 1;
  }

  return 0;
}

int isNotPn(int n)
{
  return !isPn(n);
}
  
  
int range_end(int start, int ubound, int (*predicate)(int))
{
  int i = start;
  while ( i < ubound ) {
    if (predicate(i)) {
      ++i;
      continue;
    }
    else
      break;
  }
  return (i - 1);
}

typedef struct Set
{
  int start;
  int end;
  int isPn;
} Set;

Set* create(int start, int ubound)
{
  Set* s = (Set*)malloc(sizeof(Set));
  if (!s)
    return s;
  memset(s, 0, sizeof(s));
  
  s->start = start;
  s->isPn = isPn(start);
  s->end = range_end(start, ubound, s->isPn ? isPn : isNotPn);

  return s;
}

void destroy(Set* s)
{
  if (s)
    free(s);
}

int main(int artc, char* argv[])
{
  int i = 0;
  Set** sets = NULL;
  int ssz = 128;
  int newsz = ssz;
  int nsets = 0;
  int a = 10;
  int b = 20;
  int result = 0;
  int ubound = b + 1;

  int n = a;

  sets = (Set**)malloc(sizeof(Set*) * ssz);
  if (!sets) {
    printf("Memory error\n");
    return 1;
  }
  memset(sets, 0, sizeof(sets));

  while( n < ubound ) {
    sets[i] = create(n, ubound);
    if (sets[i]) {
      ++nsets;
    }
    n = sets[i]->end + 1;
    i++;
    if (i >= ssz) {
      newsz = newsz + ssz;
      sets = (Set**)realloc(sets, sizeof(Set*) * newsz);
      if (!sets) {
	printf("Memory panic\n");
	return 1;
      }
    }
  }

  /* debug */
  for (i = 0; i < nsets; ++i) {
    printf("[%03d] %08d  %08d  %s\n",
	   i,
	   sets[i]->start,
	   sets[i]->end,
	   sets[i]->isPn ? "P" : "Np");
  }
  

  /* TODO: Counts number of funny ranges */

  printf("Number of funny ranges: %d\n", result);
  
  for (i = 0; i < sizeof(sets) / sizeof(Set*); ++i) {
    destroy(sets[i]);
  }
  free(sets);
  
  return 0;
}
