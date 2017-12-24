#ifndef COUNT_TRIANGLES_H
#define COUNT_TRIANGLES_H

struct Graph
{
  int num_pts;
  int* points;

  struct _iterator {
    /* always keep pt1_idx < pt2_idx < pt3_idx */
    int pt1_idx;
    int pt2_idx;
    int pt3_idx;
  } iter;
  
};


void iterator_begin(struct Graph* g);
int  iterator_end(struct Graph* g);
void iterator_next(struct Graph* g, int* p1, int* p2, int* p3);

#endif	/* COUNT_TRIANGLES_H */
