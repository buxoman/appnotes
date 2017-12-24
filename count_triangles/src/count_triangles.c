#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "count_triangles.h"

struct Graph graph;

int point[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11};

int line[7][12] = {
    /* line N     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} */
    /* line 1  */ {0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0},
    /* line 2  */ {0, 0, 0, 3, 4, 5, 6, 0, 0, 0,  0,  0},
    /* line 3  */ {0, 1, 0, 0, 0, 0, 6, 7, 0, 0,  0,  0},
    /* line 4  */ {0, 1, 0, 0, 4, 0, 0, 0, 0, 9, 10,  0},
    /* line 5  */ {0, 1, 0, 0, 0, 5, 0, 0, 8, 0,  0, 11},
    /* line 6  */ {0, 0, 2, 0, 0, 0, 0, 7, 8, 9,  0,  0},
    /* line 7  */ {0, 0, 0, 3, 0, 0, 0, 7, 0, 0, 10, 11}
};

void graph_construct(struct Graph* g,
		     int num_pts, int* pts,
		     int num_lns, int* lns)
{
  size_t sz;
  assert(g);
  
  g->num_pts = num_pts;
  g->points = NULL;
  sz = (size_t)num_pts *  sizeof(int);
  g->points = (int*)malloc(sz);
  if (g->points) {
    memcpy(g->points, pts, sz);
  }

  g->num_lns = num_lns;
  g->lines = NULL;
  sz = sizeof(int) * (size_t)g->num_lns * (size_t)(g->num_pts + 1);
  g->lines = (int*)malloc(sz);
  if (g->lines) {
    memcpy(g->lines, lns, sz);
  }

  g->iter.pt1_idx = -1;
  g->iter.pt2_idx = -1;
  g->iter.pt3_idx = -1;
}

void graph_destroy(struct Graph* g)
{
  assert(g);

  if (g->points)
    free (g->points);

  if (g->lines)
    free (g->lines);

  memset(g, 0, sizeof(*g));
}

void iterator_begin(struct Graph* g)
{
  assert(g);
  
  g->iter.pt1_idx = 0;
  g->iter.pt2_idx = 1;
  g->iter.pt3_idx = 2;
}

/* 遍历完成则返回1否则返回0. */
int iterator_end(struct Graph* g)
{
  assert(g);
  
  return (g->iter.pt1_idx >= (g->num_pts - 2))
    &&   (g->iter.pt2_idx >= (g->num_pts - 1))
    &&   (g->iter.pt3_idx >= g->num_pts);
}

/* 取得三点的一个组合 */
void iterator_next(struct Graph* g, int* p1, int* p2, int* p3)
{
  *p1 = g->points[g->iter.pt1_idx];
  *p2 = g->points[g->iter.pt2_idx];
  *p3 = g->points[g->iter.pt3_idx];

  g->iter.pt3_idx += 1;
  if (g->iter.pt3_idx < g->num_pts) {
    return;
  }

  g->iter.pt2_idx += 1;
  if (g->iter.pt2_idx < (g->num_pts - 1)) {
    g->iter.pt3_idx = g->iter.pt2_idx + 1;
    return;
  }

  g->iter.pt1_idx += 1;
  if (g->iter.pt1_idx < (g->num_pts - 2)) {
    g->iter.pt2_idx = g->iter.pt1_idx + 1;
    g->iter.pt3_idx = g->iter.pt2_idx + 1;
    return;
  }
}

int is_connected(struct Graph* g, int p1, int p2)
{
  assert(g);

  int row = 0;
  int* line_points = NULL;

  for(row = 0; row < g->num_lns; ++row) {
    line_points = g->lines + row * (g->num_pts + 1);
    if ( line_points[p1] && line_points[p2] ) {
      return 1;
    }
  }
  
  return 0;
}

int is_same_line(struct Graph* g, int p1, int p2, int p3)
{
  assert(g);

  int row = 0;
  int* line_points = NULL;

  for(row = 0; row < g->num_lns; ++row) {
    line_points = g->lines + row * (g->num_pts + 1);
    if ( line_points[p1] && line_points[p2] && line_points[p3]) {
      return 1;
    }
  }

  return 0;
}

int count_triangles(struct Graph* g)
{
  int p1 = 0, p2 = 0, p3 = 0;
  int cnt = 0;
  
  assert(g);

  iterator_begin(g);
  while ( ! iterator_end(g)) {
    iterator_next(g, &p1, &p2, &p3);
    if ( is_connected(g, p1, p2)
	 && is_connected(g, p1, p3)
	 && is_connected(g, p2, p3)
	 && ! is_same_line(g, p1, p2, p3)) {
      cnt += 1;
    }
  }

  return cnt;
}
