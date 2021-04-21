#include <gtest/gtest.h>
#include <npower_monitor.hpp>
#include <iostream>

using namespace std;

class StepsTests: public ::testing::Test {
  protected:
    //...

    void SetUp() {
        //...
    }

    void TearDown() { /*...*/ }
};

TEST_F(StepsTests, SomeTest) {
    EXPECT_TRUE( /*...*/ true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
