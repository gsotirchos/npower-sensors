#include <gtest/gtest.h>
#include <npower_sensors.hpp>
#include <iostream>

using namespace std;

class HallSensorTests: public ::testing::Test {
  protected:
    //...

    void SetUp() {
        //...
    }

    void TearDown() { /*...*/ }
};

TEST_F(HallSensorTests, SomeTest) {
    EXPECT_TRUE( /*...*/ true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
