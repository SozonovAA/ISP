//
// Created by andrey on 19.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../FinanceData/urlRequests.h"

namespace testing {

    TEST(urlRequestTests, SimpleRequestTest) {
        urlRequests exampleUrl;

        exampleUrl.request();
    }
} // namespace testing

