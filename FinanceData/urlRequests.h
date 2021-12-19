//
// Created by andrey on 19.12.2021.
//


#ifndef ISP_URLREQUESTS_H
#define ISP_URLREQUESTS_H
#include <string>
namespace financedata {

    /**
     * Parameters to AlphaVintage API request
     */
    struct AlphaVintageAPIParametrs {

        /** Признак того, что данная опция не используется. */
        const std::uint16_t _NULL = 0;
        /**
         * Тип запрашиваемой функции.
         */
        enum Function : std::uint16_t {
            /** Cтоимость акции по дням.( исторические данные ) */
            TIME_SERIES_DAILY_ADJUSTED = 1,
        };
        Function function { TIME_SERIES_DAILY_ADJUSTED };

        /** Тикер акции */
        std::string symbol;

        /**
         * Опционально!
         * Размер получаемых данных.
         */
        enum OutputSize : std::uint16_t {
            /** Опция не оспользуется */
            COMPACT = 1,
            FULL,
        };
        OutputSize oz{ _NULL };

        /**
         * Опционально!
         * Тип передаваемого типа данных, по дефолту json
         * */
        enum DataType : std::uint16_t {
            JSON = 1,
        };
        DataType datatype{ _NULL };

        /**
         * API key
         */
        const std::string API_KEY = "6UQN44IKREM4QDY3";

        std::string request();

    };

    /**
     * Класс для реализации URL запросов к API.
     */
    class urlRequests {
    public:
        std::string request();


    private:

        std::string https_request = "http://example.com";


    };
}



#endif //ISP_URLREQUESTS_H
