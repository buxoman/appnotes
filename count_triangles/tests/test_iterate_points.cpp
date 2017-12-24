#include "CppUTest/TestHarness.h"

extern "C" {
  extern int point[];
  extern int num_pts;
  
  void iterate_init(void);
  void iterate_points(int* p1, int* p2, int* p3);
}

// 计算较小的数n的阶乘
// unsigned int factorial(unsigned int n)
// {
//   int result = 1;
//   if (0 == n) return 0;
  
//   if (n == 1)
//     return result;
//   else
//     result = n * factorial(n-1);

//   return result;
// }


TEST_GROUP(Iterate3Points)
{
  int p1, p2, p3;

  void setup()
  {
    p1 = p2 = p3 = 0;
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

TEST(Iterate3Points, call_twice)
{
  iterate_points(&p1, &p2, &p3);
  iterate_points(&p1, &p2, &p3);

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

TEST(Iterate3Points, call_N_times_until_p2_reach_ending)
{
  int i;
  for (i = 0; i < num_pts - 1; ++i) {
    iterate_points(&p1, &p2, &p3);
  }

  CHECK_EQUAL(1, p1);
  CHECK_EQUAL(3, p2);
  CHECK_EQUAL(4, p3);
}


