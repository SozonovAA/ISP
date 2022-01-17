//
// Created by titov on 30.06.2021.
//

#include "JsonParser.h"
#include <list>
#include <ranges>

#include <iostream>

asc::any_data asc::JsonParser::parse( std::string_view raw ) const {
    
    return do_parse( json::parse(raw) );

}

std::string asc::JsonParser::pack(asc::any_data data) const {
    return do_pack(data).dump();
}

asc::any_data asc::JsonParser::do_parse(asc::JsonParser::json js) const {

    
    if( js.is_null() ) {

        return asc::any_data();

    } else if( js.is_object() ) {

        std::map<std::string, asc::any_data> answer;

        for( auto [key, item] : js.items() )
            answer[key] = do_parse(item);

        return answer;

    } else if( ( js.is_array() ) || ( js.is_structured() ) ) {

        std::list<asc::any_data> answer;

        for( auto item : js )
            answer.push_back( do_parse(item) );

        return std::vector<asc::any_data>(std::begin(answer), std::end(answer));

    } else if( js.is_string() ) {
        return js.get<std::string>();

    } else if( js.is_number_unsigned() ) {

        return js.get<std::uint64_t>();

    } else if( js.is_number_integer() ) {

        return js.get<std::int64_t>();

    } else if( js.is_number_float() ) {

        return js.get<std::double_t>();

    } else if( js.is_boolean() ) {

        return js.get<bool>();

    } else if( js.is_binary() ) {

        return js.get<std::vector<std::uint8_t>>();

    } else if( js.is_structured() ) {

//        return js.get<std::vector<std::uint8_t>>();

    } else
        throw std::domain_error("Unknown data type: parse json to std::any");

}

#include <iostream>

asc::JsonParser::json asc::JsonParser::do_pack(asc::any_data data) const {

    json answer;

    if( data.has_value() )
        answer = packers.at(std::type_index(data.type()))(std::move(data));

    return answer;

}

asc::JsonParser::JsonParser() {

    packers[std::type_index(typeid(std::map<std::string, asc::any_data>))] =
            [this](asc::any_data data) {
                json answer;

                auto const & typed_data = std::any_cast<std::map<std::string, asc::any_data> &>(data); //data.dict();//

                for( auto const & [key, value] : typed_data )
                    answer[key] = do_pack(value);

                return answer;
            };
    packers[std::type_index(typeid(std::vector<asc::any_data>))] =
            [this](asc::any_data data) {
                json answer;

                auto const & typed_data = std::any_cast<std::vector<asc::any_data> &>(data); //data.array();//

                for( auto index : std::views::iota(0ul, typed_data.size()) )
                    answer[index] = do_pack(typed_data[index]);

                return answer;
            };
    register_typical_packer<std::string>();
    //register_typical_packer<std::double_t>();
    //register_typical_packer<std::float_t>();
    register_typical_packer<std::int8_t>();
    register_typical_packer<std::uint8_t>();
    register_typical_packer<std::int16_t>();
    register_typical_packer<std::uint16_t>();
    register_typical_packer<std::int32_t>();
    register_typical_packer<std::uint32_t>();
    register_typical_packer<std::int64_t>();
    register_typical_packer<std::uint64_t>();
    register_typical_packer<std::vector<std::uint8_t>>();
    register_typical_packer<bool>();
    register_typical_packer<std::nullptr_t>();

    packers[std::type_index(typeid(std::float_t))] =
            [this](asc::any_data data) {
                json answer;

                auto const & typed_data = std::any_cast<std::float_t &>(data);

                if( std::isfinite(typed_data) )
                    answer = typed_data;
                else if( std::isnan(typed_data) )
                    answer = "nan";
                else if( typed_data < 0 )
                    answer = "-inf";
                else
                    answer = "inf";

                return answer;
            };
    packers[std::type_index(typeid(std::double_t))] =
            [this](asc::any_data data) {
                json answer;

                auto const & typed_data = std::any_cast<std::double_t &>(data);

                if( std::isfinite(typed_data) )
                    answer = typed_data;
                else if( std::isnan(typed_data) )
                    answer = "nan";
                else if( typed_data < 0 )
                    answer = "-inf";
                else
                    answer = "inf";

                return answer;
            };
}
