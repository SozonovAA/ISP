//
// Created by andrey on 19.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../FinanceData/urlRequests.h"

namespace testing {

    TEST(urlRequestTests, SimpleRequestTest) {
        financedata::urlRequests exampleUrl;

        std::cout << exampleUrl.request();
    }
} // namespace testing

