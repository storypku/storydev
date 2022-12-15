#include "fastrtps/utils/fixed_size_string.hpp"

#include "gtest/gtest.h"

namespace eprosima {
namespace fastrtps {

TEST(FixedSizeStringTest, TestFixedSizeString) {
    constexpr size_t kMaxLen = 127;
    fixed_string<kMaxLen> my_fixed_str;
    EXPECT_EQ(my_fixed_str.size(), 0);
    constexpr char msg[] = "Hello";

    my_fixed_str.assign(msg, strlen(msg));
    EXPECT_EQ(my_fixed_str.size(), 5);

    my_fixed_str = msg;
    EXPECT_EQ(my_fixed_str.size(), 5);
}

} // namespace fastrtps
} // namespace eprosima
