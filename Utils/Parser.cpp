//
// Created by titov on 01.07.2021.
//

#include "Parser.h"
#include <iostream>

std::map<std::string, asc::any_data> & asc::any_data::dict() {

    if( not this->has_value() ){
        this->emplace<std::map<std::string, any_data>>();
    }


    return std::any_cast<std::map<std::string, any_data> &>(*this);

}

std::vector<asc::any_data> & asc::any_data::array() {

    if( not this->has_value() )
        this->emplace<std::vector<any_data>>();

    return std::any_cast<std::vector<any_data> &>(*this);

}

std::map<std::string, asc::any_data> & asc::any_data::structured() {

    if( not this->has_value() ){
        this->emplace<std::map<std::string, any_data>>();
    }

    return std::any_cast<std::map<std::string, any_data> &>(*this);
}

std::vector<std::uint8_t> & asc::any_data::binary() {

    if( not this->has_value() )
        this->emplace<std::vector<std::uint8_t>>();

    return std::any_cast<std::vector<std::uint8_t> &>(*this);

}

bool & asc::any_data::flag() {
    if( not this->has_value() )
        this->emplace<bool>();

    return std::any_cast<bool &>(*this);
}

std::string & asc::any_data::string() {

    if( not this->has_value() )
        this->emplace<std::string>();

    return std::any_cast<std::string &>(*this);

}


//const bool & asc::any_data::flag() const {
//    return std::any_cast<const bool &>(*this);
//}
//const std::vector<std::uint8_t> & asc::any_data::binary() const {
//    return std::any_cast<const std::vector<std::uint8_t> &>(*this);
//}
//const std::vector<asc::any_data> & asc::any_data::array() const {
//    return std::any_cast<const std::vector<any_data> &>(*this);
//}
//const std::map<std::string, asc::any_data> &asc::any_data::dict() const {
//    return std::any_cast<const std::map<std::string, any_data> &>(*this);
//}
//const std::string & asc::any_data::string() const {
//    return std::any_cast<const std::string &>(*this);
//}
