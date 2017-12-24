#include "CppUTest/TestHarness.h"

extern "C" {
#include "count_triangles.h"
  
  extern int point[];
  extern int num_pts;
  
  void iterate_init(void);
  void iterate_points(int* p1, int* p2, int* p3);
}


TEST_GROUP(Iterate3Points)
{
  int p1, p2, p3;

  struct Graph g;

  int test_points[5];

  void setup()
  {
    p1 = p2 = p3 = 0;

    // my points: [1, 2, 3, 4, 5]
    for(int i = 0; i < 5; ++i) {
      test_points[i] = i + 1;
    }

    g.num_pts = 5;
    g.points = test_points;
    
    iterate_init();
  }

  void teardown()
  {
  }
};

TEST(Iterate3Points, call_once)
{

  iterate_points(&p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(3, p3);
}

TEST(Iterate3Points, call_once_)
{

  iterator_begin(&g);
  iterator_next(&g, &p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(3, p3);
}


TEST(Iterate3Points, call_twice)
{
  iterate_points(&p1, &p2, &p3);
  iterate_points(&p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(4, p3);
}

TEST(Iterate3Points, call_twice_)
{
  iterator_begin(&g);
  iterator_next(&g, &p1, &p2, &p3);
  iterator_next(&g, &p1, &p2, &p3);

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(4, p3);
}

TEST(Iterate3Points, call_N_times_until_p3_reach_ending)
{
  int i;
  for (i = 0; i < num_pts - 2; ++i) {
    iterate_points(&p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(11, p3);
}

TEST(Iterate3Points, call_N_times_until_p3_reach_ending_)
{
  iterator_begin(&g);
  
  for (int i = 0; i < g.num_pts - 2; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(2, p2);
  CHECK_EQUAL(5, p3);
}

TEST(Iterate3Points, call_N_times_until_p3_walk_over_ending)
{
  int i;
  for (i = 0; i < num_pts - 1; ++i) {
    iterate_points(&p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}

TEST(Iterate3Points, call_N_times_until_p3_walk_over_ending_)
{
  iterator_begin(&g);
  
  for (int i = 0; i < g.num_pts - 1; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}

TEST(Iterate3Points, call_N_times_until_p2_reach_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 6; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(4, p2);
  CHECK_EQUAL(5, p3);
}

TEST(Iterate3Points, call_N_times_until_p2_walk_over_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 7; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(2, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}

TEST(Iterate3Points, call_N_times_until_p1_reach_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 10; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(3, p1);
  CHECK_EQUAL(4, p2);
  CHECK_EQUAL(5, p3);
}  

TEST(Iterate3Points, call_N_times_until_p1_wakl_over_ending_)
{
  iterator_begin(&g);

  for(int i = 0; i < 11; ++i) {
    iterator_next(&g, &p1, &p2, &p3);
  }

  CHECK_EQUAL(1, iterator_end(&g));
}  


