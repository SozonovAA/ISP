//
// Created by titov on 30.06.2021.
//

#ifndef UFC_ASYNCSERIALCONNECTOR_JSONPARSER_H
#define UFC_ASYNCSERIALCONNECTOR_JSONPARSER_H

#include <nlohmann/json.hpp>

#include "Parser.h"

#include <concepts>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <map>
#include <any>
#include <functional>

namespace asc {

    class JsonParser : public Parser {
    public:
        any_data parse( std::string_view raw ) const;
        std::string pack( any_data data ) const;

        using json = nlohmann::json;

        JsonParser();
    private:
        asc::any_data do_parse( json js ) const;

        json do_pack( asc::any_data data ) const;
        template<typename T>
        void register_typical_packer();

        std::map<std::type_index, std::function<json(asc::any_data)>> packers;
    };
}

//template<typename T, std::invocable F>
//void asc::JsonParser::register_any_parser( F parser ) {
//    parsers.insert( {typeid(T), [parser](json const & js) -> std::any {
//        return parser(js);
//    } } );
//}
//
template<typename T>
void asc::JsonParser::register_typical_packer() {
    packers.insert( std::pair{std::type_index(typeid(T)), [](asc::any_data data) {
        json answer;
        auto const & typed_data = std::any_cast<T const &>(data);
        answer = typed_data;
        return answer;
    } } );
}

#endif //UFC_ASYNCSERIALCONNECTOR_JSONPARSER_H
