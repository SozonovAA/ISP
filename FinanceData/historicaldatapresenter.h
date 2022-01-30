#ifndef HISTORICALDATAPRESENTER_H
#define HISTORICALDATAPRESENTER_H

#include "ihistiricaldata.h"
#include "alphavintageapi.h"

namespace financedata {

class HistoricalDataPresenter :
        public IHistoricalData,
        private AlphaVintageAPIReplyer
{
public:
    HistoricalDataPresenter(
            std::function< std::string( std::string ) >  _req ) :
        AlphaVintageAPIReplyer( _req ) {

    }

    std::map< utils::Date, utils::Transaction_t::price_t >
        getDailyPrise ( std::string _company, OutSize _size = OutSize::COMPACT )
    override;
};

}

#endif // HISTORICALDATAPRESENTER_H
