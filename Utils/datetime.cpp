#include <boost/date_time/gregorian/gregorian.hpp>

#include "datetime.h"

typedef boost::gregorian::date b_date;
typedef boost::gregorian::day_iterator b_date_it;
namespace utils {

////префиксная версия возвращает значение после инкремента
const Date& operator++(Date& i) {
    b_date_it a( b_date( i.year, i.mounth, i.day) );
    ++a;
    i = std::move( std::tuple {a->year(), a->month(), a->day() } );
    return ( i );
}



////префиксная версия возвращает значение после декремента
const Date& operator--(Date& i) {
    b_date_it a( b_date( i.year, i.mounth, i.day) );
    --a;
    i = std::move( std::tuple {a->year(), a->month(), a->day() } );
    return i;
}


} // namespace utils
