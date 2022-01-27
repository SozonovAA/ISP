#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Utils/datetime.h"


namespace testing {

    TEST(DateTimeTest, InitialiseTest) {
        {
            EXPECT_ANY_THROW( utils::Date date( 2020, 2, 30) );
            EXPECT_ANY_THROW( utils::Date date( 2020, 13, 30) );
            EXPECT_ANY_THROW( utils::Date date( 2020, 12, 32) );
            EXPECT_ANY_THROW( utils::Date date( 2020, 0, 30) );
        }
        {
            utils::Date date1( 2020, 11, 12);
            utils::Date date2( 2021, 11, 12);

            EXPECT_FALSE( date1 > date2 );
            EXPECT_TRUE ( date1 < date2 );
        }
        {
            utils::Date date1( 2020, 11, 12);
            utils::Date date2( 2020, 12, 12);

            EXPECT_FALSE( date1 > date2 );
            EXPECT_TRUE ( date1 < date2 );
        }
        {
            utils::Date date1( 2020, 11, 12);
            utils::Date date2( 2020, 11, 13);

            EXPECT_FALSE( date1 > date2 );
            EXPECT_TRUE ( date1 < date2 );
        }
    }

    TEST(DateTimeTest, UnaryOperatorTest) {
        {
            utils::Date date1( 2020, 11, 12);
            utils::Date date2( 2021, 12, 31);

            ++date2;
            auto [ y, m, d] = date2.сget_date();
            EXPECT_EQ(y, 2022);
            EXPECT_EQ(m, 1);
            EXPECT_EQ(d, 1);
        }
        {
            utils::Date date2( 2021, 12, 31);
            --date2;
            auto [ y, m, d] = date2.сget_date();
            EXPECT_EQ(y, 2021);
            EXPECT_EQ(m, 12);
            EXPECT_EQ(d, 30);


        }


    }

    TEST(DateTimeTest, AddDecreaseFuncTest) {
        utils::Date date1( 2020, 12, 30);
        date1.add_month();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2021);
            EXPECT_EQ(m, 1);
            EXPECT_EQ(d, 30);

        }
        date1.add_week();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2021);
            EXPECT_EQ(m, 2);
            EXPECT_EQ(d, 6);

        }
        date1.add_year();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2022);
            EXPECT_EQ(m, 2);
            EXPECT_EQ(d, 6);

        }
        date1.decrease_year();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2021);
            EXPECT_EQ(m, 2);
            EXPECT_EQ(d, 6);

        }
        date1.decrease_week();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2021);
            EXPECT_EQ(m, 1);
            EXPECT_EQ(d, 30);

        }
        date1.decrease_month();
        {
            auto [ y, m, d] = (date1.get_date());
            EXPECT_EQ(y, 2020);
            EXPECT_EQ(m, 12);
            EXPECT_EQ(d, 30);

        }
    }


}
