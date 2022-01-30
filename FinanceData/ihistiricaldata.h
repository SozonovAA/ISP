#ifndef IHISTIRICALDATA_H
#define IHISTIRICALDATA_H
#include <map>
#include <string>
#include <ctime>

#include "../Utils/DataTypes.h"
#include "../Utils/datetime.h"

namespace financedata {
enum OutSize : std::uint16_t {
    DEFAULT = 0,
    COMPACT,
    FULL,
};

class IHistoricalData {
public:
    virtual std::map< utils::Date, utils::Transaction_t::price_t >
    getDailyPrise (std::string _company, OutSize _size) = 0;


};
} // namespace financedata


#endif // IHISTIRICALDATA_H
