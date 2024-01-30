
#include <gtest/gtest.h>
#include <ros/ros.h>

TEST(SimpleTest,testFunction){

    int value = 5;
    ASSERT_EQ(value,5);
}

