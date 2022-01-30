#include <boost/date_time/gregorian/gregorian.hpp>

#include "datetime.h"

typedef boost::gregorian::date b_date;
typedef boost::gregorian::day_iterator b_date_it;
typedef boost::gregorian::week_iterator b_week_it;
typedef boost::gregorian::month_iterator b_mon_it;
typedef boost::gregorian::year_iterator b_year_it;



namespace utils {

const Date& operator++( Date& i ) {
    b_date_it a( b_date( i.year, i.mounth, i.day) );
    ++a;
    i = ( Date{a->year(), a->month(), a->day() } );
    return ( i );
}

const Date& operator--( Date& i ) {
    b_date_it a( b_date( i.year, i.mounth, i.day) );
    --a;
    i = ( Date{a->year(), a->month(), a->day() } );
    return i;
}

const Date& Date::add_week()
{
    b_week_it a( b_date( this->year, this->mounth, this->day) );

    ++a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}

const Date& Date::add_month()
{
    b_mon_it a( b_date( this->year, this->mounth, this->day) );

    ++a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}

const Date& Date::add_year()
{
    b_year_it a( b_date( this->year, this->mounth, this->day) );

    ++a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}


const Date& Date::decrease_week()
{
    b_week_it a( b_date( this->year, this->mounth, this->day) );

    --a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}

const Date& Date::decrease_month()
{
    b_mon_it a( b_date( this->year, this->mounth, this->day) );

    --a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}

const Date& Date::decrease_year()
{
    b_year_it a( b_date( this->year, this->mounth, this->day) );

    --a;
    *this = ( Date{a->year(), a->month(), a->day() } );
    return *this;
}

void Date::date_check()
{
    b_date a( this->year, this->mounth, this->day );

}

} // namespace utils


