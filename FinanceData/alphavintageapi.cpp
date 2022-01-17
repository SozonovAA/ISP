#include "alphavintageapi.h"
#include "../Utils/JsonParser.h"

#include <iostream>

namespace financedata {

AlphaVintageAPIRequester::AlphaVintageAPIRequester
    ( std::function< std::string( std::string ) >  _req)
    : request( _req)
{

}

std::string AlphaVintageAPIRequester::send_request()
{
    return request( create_request() );
}

std::string AlphaVintageAPIRequester::create_request() {
    std::string return_string {"https://www.alphavantage.co/query?"};
    switch ( api_params.function ) {
        case AlphaVintageAPIParameters::Function::TIME_SERIES_DAILY:
            return_string += "function=TIME_SERIES_DAILY";
            break;

    }

    return_string += ( "&symbol=" + api_params.symbol );

    if ( api_params.oz ) {
        switch ( api_params.oz ) {
            case AlphaVintageAPIParameters::OutputSize::COMPACT:
                return_string += "&outputsize=compact";
                break;
            case AlphaVintageAPIParameters::OutputSize::FULL:
                return_string += "&outputsize=full";
                break;
        }
    }
    if ( api_params.datatype ) {
        switch ( api_params.datatype ) {
            case AlphaVintageAPIParameters::DataType::JSON:
                return_string += "&datatype=json";
                break;
        }
    }

    return_string += ( "&apikey=" + api_params.API_KEY );

    return return_string;
}


void AlphaVintageAPIReplyer::parce( std::string _reply)
{
    asc::JsonParser parser;
    auto query = parser.parse( _reply );
    for ( auto [ key, value] : query.dict()["Time Series (Daily)"].dict() )
    {
        daily_price[ std::make_tuple(
                     std::stoi( key.substr(0, 4) ),
                     std::stoi( key.substr(5, 2) ),
                     std::stoi( key.substr(8, 2) )
        )] = std::stod( value.dict()["4. close"].string() );
    }

    std::cout << daily_price.size() << std::endl;
}

const std::map< std::tuple< int, int, int >, double > &AlphaVintageAPIReplyer::get_daily_price()
{
    return daily_price;
}

} // namespace financedata
