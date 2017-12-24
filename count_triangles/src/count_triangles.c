#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "count_triangles.h"

struct Graph graph;

int point[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11};

int line[][12] = {
    /* line N     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} */
    /* line 1  */ {0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0},
    /* line 2  */ {0, 0, 0, 3, 4, 5, 6, 0, 0, 0,  0,  0},
    /* line 3  */ {0, 1, 0, 0, 0, 0, 6, 7, 0, 0,  0,  0},
    /* line 4  */ {0, 1, 0, 0, 4, 0, 0, 0, 0, 9, 10,  0},
    /* line 5  */ {0, 1, 0, 0, 0, 5, 0, 0, 8, 0,  0, 11},
    /* line 6  */ {0, 0, 2, 0, 0, 0, 0, 7, 8, 9,  0,  0},
    /* line 7  */ {0, 0, 0, 3, 0, 0, 0, 7, 0, 0, 10, 11}
};

int num_pts = sizeof(point) / sizeof(int);


/* keep pt1_idx < pt2_idx < pt3_idx */
static int pt1_idx = 0;
static int pt2_idx = 0;
static int pt3_idx = 0;


void graph_construct(struct Graph* g)
{
  assert(g);
  
  g->num_pts = num_pts;
  g->points  = point;

  g->iter.pt1_idx = -1;
  g->iter.pt2_idx = -1;
  g->iter.pt3_idx = -1;
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

void iterate_init(void)
{
  pt1_idx = 0;
  pt2_idx = 1;
  pt3_idx = 2;
}

void iterate_end(void)
{
  pt1_idx = -1;
  pt2_idx = -1;
  pt3_idx = -1;
}

void iterate_points(int* p1, int* p2, int* p3)
{
  *p1 = point[pt1_idx];
  *p2 = point[pt2_idx];
  *p3 = point[pt3_idx];

  pt3_idx += 1;
  if (pt3_idx < num_pts) {
    return;
  }

  pt2_idx += 1;
  if (pt2_idx < (num_pts - 1)) {
    pt3_idx = pt2_idx + 1;
    return;
  }

  pt1_idx += 1;
  if (pt1_idx < (num_pts - 2)) {
    pt2_idx = pt1_idx + 1;
    pt3_idx = pt2_idx + 1;
    return;
  }

  pt1_idx = -1;
  pt2_idx = -1;
  pt3_idx = -1;
}

/*
int main(int argc, char* argv[])
{
    argc = argc;
    argv = argv;
    return 0;
}
*/
