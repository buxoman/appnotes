#include "CppUTest/TestHarness.h"

extern "C" {
#include "count_triangles.h"
}
////////////////////////////////////////////////////////////
//测试图形:
//           /\        *
//          /  \       *
//         ------      *
//         /    \      *
//         ------      *
// 5个交点从顶部逆时针依次为1,2,3,4,5
// 不同的直线上共线的点集合:[1,2,3],[1,5,4],[2,5],[3,4]
////////////////////////////////////////////////////////////

int  test_points[5] = {1, 2, 3, 4, 5};

int test_line[4][6] = {{0, 1, 2, 3, 0, 0},
		  {0, 1, 0, 0, 4, 5},
		  {0, 2, 0, 0, 0, 5},
		  {0, 0, 0, 3, 4, 5}};

struct Graph g;

////////////////////////////////////////////////////////////

TEST_GROUP(CountTriangles)
{
  int p1, p2, p3;

  void setup()
  {
    p1 = p2 = p3 = 0;
    
    graph_construct(&g,
		    5, &test_points[0],
		    4, &test_line[0][0]);
		    
  }

  void teardown()
  {
    graph_destroy(&g);
  }
};

TEST(CountTriangles, call_once_)
{

  iterator_begin(&g);
  iterator_next(&g, &p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(3, p3);
}

TEST(CountTriangles, call_twice_)
{
  iterator_begin(&g);
  iterator_next(&g, &p1, &p2, &p3);
  iterator_next(&g, &p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(4, p3);
}

TEST(CountTriangles, call_N_times_until_p3_reach_ending_)
{
  iterator_begin(&g);
  
  for (int i = 0; i < g.num_pts - 2; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(5, p3);
}

TEST(CountTriangles, call_N_times_until_p3_walk_over_ending_)
{
  iterator_begin(&g);
  
  for (int i = 0; i < g.num_pts - 1; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}

TEST(CountTriangles, call_N_times_until_p2_reach_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 6; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(4, p2);
  CHECK_EQUAL(5, p3);
}

TEST(CountTriangles, call_N_times_until_p2_walk_over_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 7; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(2, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}

TEST(CountTriangles, call_N_times_until_p1_reach_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 10; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(3, p1);
  CHECK_EQUAL(4, p2);
  CHECK_EQUAL(5, p3);
}  

TEST(CountTriangles, call_N_times_until_p1_wakl_over_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 11; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, iterator_end(&g));
}

////////////////////////////////////////////////////////////


TEST(CountTriangles, connected_points_1_2_)
{
  CHECK_EQUAL(1, is_connected(&g, 1, 2));
}

TEST(CountTriangles, connected_points_4_5_)
{
  CHECK_EQUAL(1, is_connected(&g, 4, 5));
}

TEST(CountTriangles, connected_points_3_4_)
{
  CHECK_EQUAL(1, is_connected(&g, 3, 4));
}

TEST(CountTriangles, NOT_connected_points_2_4_)
{
  CHECK_EQUAL(0, is_connected(&g, 2, 4));
}

////////////////////////////////////////////////////////////

TEST(CountTriangles, points_on_same_line_1_2_3_)
{
  CHECK_EQUAL(1, is_same_line(&g, 1, 2, 3));
}

TEST(CountTriangles, points_NOT_on_same_line_1_2_4_)
{
  CHECK_EQUAL(0, is_same_line(&g, 1, 2, 4));
}

////////////////////////////////////////////////////////////

TEST(CountTriangles, count_triangles_2_)
{
  CHECK_EQUAL(2, count_triangles(&g));
}





