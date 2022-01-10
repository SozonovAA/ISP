//
// Created by andrey on 28.12.2021
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Utils/Log.h"
#include <string>

namespace testing {

    TEST(LogTest, SimpleLogTest) {
        utils::LogStream test_log( "TestThread", 0, "Test_Module" );

        utils::LogStream test_log1( "TestThread1", 1, "Test_Module1" );

        test_log << std::string( "Hello Test" ) << 5;
        test_log1 << std::string( "Hello Test" );
    }

} // namespace testing

