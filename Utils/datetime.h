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
    };

    Date( const Date &_r ) :
        year( _r.year ),
        mounth( _r.mounth ),
        day ( _r.day ) {
    };

    Date& operator=(const Date& _r) {
        // Проверка на самоприсваивание
        if ( &_r == this)
            return *this;

        year =  _r.year;
        mounth = _r.mounth;
        day = _r.day;
        
        return *this;

    };

    Date& operator=( Date&& _r) {
        // Проверка на самоприсваивание
        if ( &_r == this)
            return *this;

        year =  _r.year;
        mounth = _r.mounth;
        day = _r.day;
        
        _r.year = 0;
        _r.mounth = 0;
        _r.day = 0;
        
        return *this;
    };

    Date& operator=(const  std::tuple< year_t, mounth_t, day_t >& _r) {
        // Проверка на самоприсваивание
        if ( _r == *this)
            return *this;

        this->get_date() = _r;
        
        return *this;
    };

    Date( Date &&_r ) :
        year( _r.year ),
        mounth( _r.mounth ),
        day ( _r.day ) {
        _r = Date( 0, 0 , 0);
    };


    std::tuple< year_t&, mounth_t&, day_t& > get_date() {
        return { year, mounth, day };
    };

    const std::tuple< const year_t&, const mounth_t&, const day_t& > сget_date() {
        return { year, mounth, day };
    }

private:
    year_t year = 0;
    mounth_t mounth = 0;
    day_t day = 0;

    void date_check();

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

    /**
     * @brief operator ++ префиксный декремент дня
     */
    friend const Date& operator++(Date& i);

    /**
     * @brief add_week функция увеличивает дату на неделю
     * @return ссылка на получившуюся дату
     */
    const Date& add_week();

    /**
     * @brief add_mounth функция увеличивает дату на месяц
     * @return ссылка на получившуюся дату
     */
    const Date& add_month();

    /**
     * @brief add_year функция увеличивает дату на год
     * @return ссылка на получившуюся дату
     */
    const Date& add_year();


    /**
     * @brief operator -- префиксный декремент дня
     */
    friend const Date& operator--(Date& i);

    /**
     * @brief add_week функция уменьшает дату на неделю
     * @return ссылка на получившуюся дату
     */
    const Date& decrease_week();

    /**
     * @brief add_mounth функция уменьшает дату на месяц
     * @return ссылка на получившуюся дату
     */
    const Date& decrease_month();

    /**
     * @brief add_year функция уменьшает дату на год
     * @return ссылка на получившуюся дату
     */
    const Date& decrease_year();
};


//todo: запилить классы
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
