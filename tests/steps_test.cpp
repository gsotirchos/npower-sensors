#include <steps_monior.hpp>
#include <iostream>

using namespace std;

class StepsTest: public ::testing::Test
  protected:
    //...

    void SetUp() {
        //...
    }

    void TearDown() { /*...*/ }
};

TEST_F(Steps, SomeTest) {
    EXPECT_TRUE( return True /*...*/);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
