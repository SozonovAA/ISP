#ifndef IHISTIRICALDATA_H
#define IHISTIRICALDATA_H
#include <map>
#include <string>
#include <ctime>
namespace financedata {
enum OutSize : std::uint16_t {
    DEFAULT = 0,
    COMPACT,
    FULL,
};

class IHistoricalData {
public:
    virtual map<std::tm, double>getDailyPrise (std::string _company, OutSize _size) = 0;


};
} // namespace financedata


#endif // IHISTIRICALDATA_H
