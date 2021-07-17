#include "math/base.h"

#include "gtest/gtest.h"

TEST(BaseTest, TestAdd) {
  int c = add(3, 4);
  EXPECT_EQ(c, 7);
}

TEST(BaseTest, TestSub) {
  int c = sub(3, 4);
  EXPECT_EQ(c, -1);
  c = sub(4, 3);
  EXPECT_EQ(c, 1);
}
