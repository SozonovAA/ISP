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

        test_log << std::string( "Hello Test" );
    }

} // namespace testing

