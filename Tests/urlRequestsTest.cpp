//
// Created by andrey on 19.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../FinanceData/alphavintageapi.h"
#include "../FinanceData/urlRequests.h"

namespace testing {

    TEST(urlRequestTests, SimpleRequestTest) {
        financedata::AlphaVintageAPIRequester testReq( financedata::request );

        testReq.api_params.symbol = "IBM";
        testReq.api_params.function = financedata::AlphaVintageAPIRequester::
                AlphaVintageAPIParameters::Function::TIME_SERIES_DAILY;

        std::cout << testReq.send_request();
    }
} // namespace testing

