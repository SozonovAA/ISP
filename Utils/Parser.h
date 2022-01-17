//
// Created by titov on 30.06.2021.
//

#ifndef UFC_ASYNCSERIALCONNECTOR_PARSER_H
#define UFC_ASYNCSERIALCONNECTOR_PARSER_H

#include <any>
#include <string_view>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>

namespace asc {

    struct any_data : public std::any {
        using any::any;
        any_data( const any & a ) : any( a ) {}
        any_data( any && a ) : any( a ) {}

        using std::any::operator=;

        template<std::regular regular_t>
        regular_t & regular();
        std::map<std::string, any_data> & dict();
        std::vector<any_data> & array();
        std::map<std::string, asc::any_data> & structured();
        std::vector<std::uint8_t> & binary();
        bool & flag();
        std::string & string();
    };

    struct Parser {
        virtual any_data parse( std::string_view raw ) const = 0;
        virtual std::string pack( any_data data ) const = 0;

        virtual ~Parser() = default;
    };

}

#include <exception>

namespace asc {

    class bad_ieee754_special_value_cast : public std::exception {
    public:
        bad_ieee754_special_value_cast( std::string_view value ) {
            using std::literals::string_literals::operator""s;
            message = "bad ieee754 value cast: "s + std::string(value);
        }
        const char * what() const noexcept {
            return message.c_str();
        }
    private:
        std::string message;
    };

}

template<std::regular regular_t>
regular_t & asc::any_data::regular() {

    if( not this->has_value() )
        this->emplace<regular_t>();

    if( this->type() != typeid(regular_t) ) {
        if (this->type() == typeid(std::uint64_t))
            this->emplace<regular_t>(std::any_cast<std::uint64_t>(*this));

        else if (this->type() == typeid(std::int64_t))
            this->emplace<regular_t>(std::any_cast<std::int64_t>(*this));

        else if (this->type() == typeid(std::double_t))
            this->emplace<regular_t>(std::any_cast<std::double_t>(*this));

        else if (this->type() == typeid(std::uint32_t))
            this->emplace<regular_t>(std::any_cast<std::uint32_t>(*this));

        else if (this->type() == typeid(std::int32_t))
            this->emplace<regular_t>(std::any_cast<std::int32_t>(*this));

        else if (this->type() == typeid(std::float_t))
            this->emplace<regular_t>(std::any_cast<std::float_t>(*this));

        else if (this->type() == typeid(std::uint16_t))
            this->emplace<regular_t>(std::any_cast<std::uint16_t>(*this));

        else if (this->type() == typeid(std::int16_t))
            this->emplace<regular_t>(std::any_cast<std::int16_t>(*this));

        else if (this->type() == typeid(std::uint8_t))
            this->emplace<regular_t>(std::any_cast<std::uint8_t>(*this));

        else if (this->type() == typeid(std::int8_t))
            this->emplace<regular_t>(std::any_cast<std::int8_t>(*this));

        else if (this->type() == typeid(std::string)) {

            const auto & string = std::any_cast<std::string &>(*this);

            if( not string.compare("nan"))
                this->emplace<regular_t>(NAN);
            else if( not string.compare("inf") )
                this->emplace<regular_t>(INFINITY);
            else if(not string.compare("-inf"))
                this->emplace<regular_t>(-INFINITY);
            else
                throw bad_ieee754_special_value_cast(string);

        }

    }

    return std::any_cast<regular_t &>(*this);

}

#endif //UFC_ASYNCSERIALCONNECTOR_PARSER_H
