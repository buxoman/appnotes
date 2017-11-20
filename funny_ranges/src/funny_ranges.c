#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funny_ranges.h"


/* 回文数判断 */
int isPn(int n)
{
  char nstr[16];
  char reverse[16];
  size_t  sz = 0;
  size_t  i = 0;
  
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

/* 非回文数判断 */
int isNotPn(int n)
{
  return !isPn(n);
}
  
/* 从start开始，寻找满足条件predicate的连续N个数的范围的最后一个数。 */
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

/* 回文数或非回文数的集合 */
typedef struct Set
{
  int start;			/* start <= end */
  int end;
  int isPn;			/* 回文数标志 */
} Set;


Set* create(int start, int ubound)
{
  Set* s = (Set*)malloc(sizeof(Set));
  if (!s)
    return s;
  memset(s, 0, sizeof(*s));
  
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

int funny_ranges(const char* infile, const char* outfile)
{
  size_t i = 0;
  Set** sets = NULL;
  size_t ssz = 128;
  size_t newsz = ssz;
  size_t nsets = 0;
  int a = 10;
  int b = 20;
  int result = 0;
  int ubound = b + 1;

  int n = a;
  size_t size = sizeof(Set*) * ssz;

  infile = infile;
  outfile = outfile;
  
  sets = (Set**)malloc(size);
  if (!sets) {
    printf("Memory error\n");
    return 1;
  }
  memset(sets, 0, sizeof(size));

  while( n < ubound ) {
    sets[i] = create(n, ubound);
    if (sets[i]) {
      ++nsets;
    }
    n = sets[i]->end + 1;
    i++;
    if (i >= ssz) {
      newsz = size;
      sets = (Set**)realloc(sets, newsz + size);
      if (!sets) {
	printf("Memory panic\n");
	return 1;
      }
    }
  }

  /* debug */
  for (i = 0; i < nsets; ++i) {
    printf("%03lu %08d  %08d  %s\n",
	   i,
	   sets[i]->start,
	   sets[i]->end,
	   sets[i]->isPn ? "P" : "Np");
  }
  

  /* TODO: Counts number of funny ranges */

  printf("Number of funny ranges: %d\n", result);
  
  for (i = 0; i < nsets; ++i) {
    destroy(sets[i]);
  }
  free(sets);
  
  return 0;
}
