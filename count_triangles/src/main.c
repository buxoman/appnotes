#include <stdio.h>
#include "count_triangles.h"

int main(int argc, char* argv[])
{
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

  int cnt = 0;

  graph_construct(&graph,
		  11, &point[0],
		  7,  &line[0][0]);

    
  cnt = count_triangles(&graph);

  printf("Number of triangles: %d\n", cnt);

  graph_destroy(&graph);

  return 0;
}
