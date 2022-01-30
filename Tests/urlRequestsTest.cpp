//
// Created by andrey on 19.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../FinanceData/alphavintageapi.h"
#include "../FinanceData/urlRequests.h"
#include "../FinanceData/historicaldatapresenter.h"

namespace testing {

    TEST(urlRequestTests, SimpleRequestTest) {

        financedata::HistoricalDataPresenter hdp( financedata::request );
        EXPECT_EQ( hdp.getDailyPrise( "IBM" ).size(), 100);
        EXPECT_TRUE( hdp.getDailyPrise( "IBM", financedata::OutSize::FULL ).size() > 5000);


    }
} // namespace testing

