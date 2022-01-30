#include "historicaldatapresenter.h"


namespace financedata {

std::map< utils::Date, utils::Transaction_t::price_t >
    HistoricalDataPresenter::getDailyPrise( std::string _company, OutSize _size )
{

    create_daily_prise_req( _company );

    create_daily_prise_req( _company,
    static_cast<
        AlphaVintageAPIRequester::AlphaVintageAPIParameters::OutputSize
                                                                    >( _size ));
             parce( send_request() );

    return get_daily_price();
}

}

