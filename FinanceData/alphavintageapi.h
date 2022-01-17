#ifndef ALPHAVINTAGEAPI_H
#define ALPHAVINTAGEAPI_H
#include <functional>
#include <string>
#include <ctime>
#include <tuple>
#include <map>


namespace financedata {
//todo: подумать над шаблонным классом, для данных пацанов
/**
 * Класс отвечающий за создание запросов к AlphaVintage API.
 */
class AlphaVintageAPIRequester
{
public:
    AlphaVintageAPIRequester( std::function< std::string( std::string ) >  _req );

    struct AlphaVintageAPIParameters {

        /** Признак того, что данная опция не используется. */
        const std::uint16_t _NULL = 0;
        /**
         * Тип запрашиваемой функции.
         */
        enum Function : std::uint16_t {
            /** Cтоимость акции по дням.( исторические данные ) */
            TIME_SERIES_DAILY = 1,
        };
        Function function { TIME_SERIES_DAILY };

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
    };

    /**
     * @brief api_params Настраивыемые параметры для создания запроса.
     */
    AlphaVintageAPIParameters api_params;



    /**
     * @brief send_request отправка юрл запроса, по сформированым полям класса
     * @return ответ на запрос
     */
    std::string send_request();
private:

    /**
     * @brief create_request метод формирования URL зарпоса на основании полей класса
     * @return сформированый hhtps запрос
     */
    std::string create_request();

    /**
     * @brief request внешняя функция, реализующая URL запрос
     */
    std::function< std::string( std::string ) > request;



};

/**
 * Класс отвечающий за обработку ответов от AlphaVintage API.
 */
class AlphaVintageAPIReplyer
{
public:
    /**
     * @brief parce Метод разбора ответа на https запрос.
     */
    void parce( std::string );

    /**
     * @brief get_daily_price метод получения константной ссылки
     *       на получившиеся данные после разбора
     * @return Стоимость компании по дням.
     */
    const std::map< std::tuple< int, int, int >, double > & get_daily_price();

private:
    /**
     * @brief daily_price Стоимость компании по дням.
     */
    //todo: заменить std::tuple на структуру
    std::map< std::tuple< int, int, int >, double > daily_price;

};

} // namespace financedata

#endif // ALPHAVINTAGEAPI_H
