#ifndef DATETIME_H
#define DATETIME_H
#include <cstddef>
#include <utility>
#include <tuple>
#include <compare>
#include <stdexcept>



namespace utils {

typedef std::size_t year_t;
typedef std::size_t mounth_t;
typedef std::size_t day_t;

struct Date {

    bool operator==( const Date & _r ) const {
        return _r == *this;
    }

    std::strong_ordering operator<=>( const Date & _r ) const {
        if( this->year == _r.year ) {
            if( this->mounth == _r.mounth ) {
                if( this->day == _r.day ) {
                    return std::strong_ordering::equal ;
                } else
                    if ( this->day > _r.day ) {
                        return  std::strong_ordering::less;
                    } else {
                        return std::strong_ordering::greater;
                    }
            } else
                if ( this->mounth > _r.mounth ) {
                    return  std::strong_ordering::less;
                } else {
                    return std::strong_ordering::greater;
                }

        } else
            if ( this->year > _r.year ) {
                return  std::strong_ordering::less;
            } else {
                return std::strong_ordering::greater;
            }
    }

    Date ( year_t _y, mounth_t _m, day_t _d ) :
        year( _y ),
        mounth( _m ),
        day ( _d )
    {
        if( ( year > 3000 ) || ( year < 0 ) )
            throw std::range_error {"Seted uncorrect year!"};

        if( ( mounth > 12 ) || ( mounth < 0 ) )
            throw std::range_error {"Seted uncorrect mounth!"};

        if( ( day > 30 ) || ( day < 0 ) )
            throw std::range_error {"Seted uncorrect day!"};
    };

    std::tuple< year_t&, mounth_t&, day_t& > get_date() {
        return { year, mounth, day };
    };

    std::tuple< const year_t&, const mounth_t&, const day_t& > сget_date() {
        return { year, mounth, day };
    };

private:
    year_t year = 0;
    mounth_t mounth = 0;
    day_t day = 0;
};

struct Time {
    std::size_t hour = 0;
    std::size_t minutes = 0;
    std::size_t seconds = 0;

    Time ( std::size_t _h, std::size_t _m, std::size_t _s ) :
        hour( _h ),
        minutes( _m ),
        seconds ( _s )
    {};
};

class DateTime
{
public:
    DateTime();
    const Date & get_date() { return date; }
    const Time & get_time() { return time; }

    const std::pair< Date, Time > get_date_time() { return std::make_pair( date, time ); };

private:
    Date date;
    Time time;

};
} //namespace utils
#endif // DATETIME_H
