//
// Created by andrey on 19.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../FinanceData/alphavintageapi.h"
#include "../FinanceData/urlRequests.h"

namespace testing {

    TEST(urlRequestTests, SimpleRequestTest) {
        financedata::AlphaVintageAPI testReq( financedata::request );

        testReq.api_params.symbol = "IBM";
        testReq.api_params.function = financedata::AlphaVintageAPI::
                AlphaVintageAPIParameters::Function::TIME_SERIES_DAILY;

        std::cout << testReq.get_request();
    }
} // namespace testing

