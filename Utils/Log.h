#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <vector>

namespace utils {
/**
     * @brief The LogStream class
     */
class LogStream {
public:

    LogStream( std::string _thr_name,
               std::size_t _thr_numb,
               std::string _module_name );

    template<class T>
    LogStream& operator<< ( T arg );

    ~LogStream();



private:
    /**
         * @brief thread_name
         */
    std::string thread_name;
    /**
         * @brief thread_numb
         */
    std::size_t thread_numb;

    /**
     * @brief module_name
     */
    std::string module_name;


    void write_to_log( std::string&& _message );

    std::size_t log_pos;
};

/**
 * @brief LogStream::operator <<
 * @param arg
 * @return
 */

template<class T>
LogStream &LogStream::operator<< ( T arg )
{
    if constexpr ( std::is_same_v<T, std::string> ){
        write_to_log( std::move( arg ) );
    }
    else {
        write_to_log( std::move( std::to_string( arg ) ) );
    }
    return *this;
}


} // namespace utils

#endif // LOG_H
