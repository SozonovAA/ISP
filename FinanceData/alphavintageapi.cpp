#include "alphavintageapi.h"
#include <iostream>
namespace financedata {

AlphaVintageAPI::AlphaVintageAPI( std::function< std::string( std::string ) >  _req)
    : request( _req)
{

}

std::string AlphaVintageAPI::get_request()
{
    return request( create_request() );
}

std::string AlphaVintageAPI::create_request() {
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

    std::cout << return_string << std::endl;

    return return_string;
}

} // namespace financedata
