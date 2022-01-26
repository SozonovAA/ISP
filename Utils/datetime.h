#ifndef DATETIME_H
#define DATETIME_H
#include <cstddef>
#include <utility>
#include <tuple>
#include <compare>
#include <stdexcept>
#include <shared_mutex>



namespace utils {

typedef std::size_t year_t;
typedef std::size_t mounth_t;
typedef std::size_t day_t;


struct Date {
    Date ( year_t _y, mounth_t _m, day_t _d ) :
        year( _y ),
        mounth( _m ),
        day ( _d )
    {
        date_check();
    };

    Date ( std::tuple< year_t, mounth_t, day_t >& _r) :
            year( std::get<0>(_r) ),
            mounth( std::get<1>(_r) ),
            day ( std::get<2>(_r) )
    {
        date_check();
    };

    Date( Date &_r ) :
        year( _r.year ),
        mounth( _r.mounth ),
        day ( _r.day ) {
        date_check();
    };

    Date( const Date &_r ) :
        year( _r.year ),
        mounth( _r.mounth ),
        day ( _r.day ) {
        date_check();
    };

    Date& operator=(const Date& _r) {
        // Проверка на самоприсваивание
        if ( &_r == this)
            return *this;

        date_check();
        year =  _r.year;
        mounth = _r.mounth;
        day = _r.day;
        return *this;

    };

    Date& operator=( Date&& _r) {
        // Проверка на самоприсваивание
        if ( &_r == this)
            return *this;

        date_check();
        _r.year = 0;
        _r.mounth = 0;
        _r.day = 0;
        return *this;
    };

    Date& operator=(const  std::tuple< year_t, mounth_t, day_t >& _r) {
        // Проверка на самоприсваивание
        if ( _r == *this)
            return *this;

        date_check();
        this->get_date() = _r;
        return *this;
    };

    Date( Date &&_r ) :
        year( _r.year ),
        mounth( _r.mounth ),
        day ( _r.day ) {

        date_check();
        _r = Date( 0, 0 , 0);
    };


    std::tuple< year_t&, mounth_t&, day_t& > get_date() {
        std::lock_guard sharedLock_date( date_lock );
        return { year, mounth, day };
    };

    const std::tuple< const year_t&, const mounth_t&, const day_t& > сget_date() {
        std::shared_lock sharedLock_date( sh_date_lock );
        return { year, mounth, day };
    }

private:
    year_t year = 0;
    mounth_t mounth = 0;
    day_t day = 0;

    //todo: плохая проверка, не учитываю месяц
    void date_check() {
        if( ( year > 5000 ) || ( year < 0 ) )
            throw std::range_error {"Seted uncorrect year!"};

        if( ( mounth > 12 ) || ( mounth < 0 ) )
            throw std::range_error {"Seted uncorrect mounth!"};

        if( ( day > 31 ) || ( day < 0 ) )
            throw std::range_error {"Seted uncorrect day!"};
    }

    std::shared_mutex sh_date_lock;
    std::mutex date_lock;

public:
    bool operator==( const Date & _r ) const {
        return ( std::make_tuple( (*this).year, (*this).mounth , (*this).day)
                 == std::make_tuple( _r.year, _r.mounth , _r.day) );    }

    bool operator==( const std::tuple<
                     const year_t&,
                     const mounth_t&,
                     const day_t& > _r ) const {
        return ( std::make_tuple( (*this).year, (*this).mounth , (*this).day)
                 == _r );    }


    std::strong_ordering operator<=>( const Date & _r ) const {

        return ( std::make_tuple( (*this).year, (*this).mounth , (*this).day)
                 <=> std::make_tuple( _r.year, _r.mounth , _r.day) );

    }

    std::strong_ordering operator<=>( const std::tuple<
                                      const year_t&,
                                      const mounth_t&,
                                      const day_t& > _r ) const {

        return ( std::make_tuple( (*this).year, (*this).mounth , (*this).day)
                 <=> _r );

    }

    //префиксный инкремент
    friend const Date& operator++(Date& i);

    //префиксный декремент
    friend const Date& operator--(Date& i);

    //todo: перегрузить бинарные операторы
    //https://habr.com/ru/post/132014/
    //https://habr.com/ru/post/66318/
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
