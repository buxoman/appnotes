#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>

/* 定义个 TEST_GROUP, 名称为 sample */
TEST_GROUP(funny_ranges)
{
  void setup(){}

  void teardown(){}
};

/* 定义一个属于 TEST_GROUP 的 TEST, 名称为 ret_int_success */
TEST(funny_ranges, test1)
{
    CHECK_EQUAL(0, 3);
}
