#ifndef COUNT_TRIANGLES_H
#define COUNT_TRIANGLES_H

struct Graph
{
  int num_pts;
  int* points;

  struct _iterator {
    int pt1_idx;
    int pt2_idx;
    int pt3_idx;
  } iterator;
  
};

#endif	/* COUNT_TRIANGLES_H */
