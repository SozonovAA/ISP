//
// Created by sozonov on 16.11.2021.
//
#include <gmock/gmock.h>
#include "gtest/gtest.h"

#include "iostream"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
