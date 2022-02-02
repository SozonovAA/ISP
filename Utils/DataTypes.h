#ifndef DATATYPES_H
#define DATATYPES_H


#include <cstddef>
#include <string>

#include "datetime.h"

namespace utils {

/**
 * Пространство имен для описания сделок
 */
namespace Transaction_t{
    /**
     * @brief price_t тип данных для предоставления данных о стоимости
     */
    typedef double price_t;
    /**
     * @brief amount_of_deals_t тип данных для предоставление данных о количестве сделок
     */
    typedef std::uint16_t amount_of_deals_t;
    /**
     * @brief transaction_number_t тип данных для предоставление данныхо номере сделки
     */
    typedef std::uint32_t transaction_number_t ;

}

/**
 * @brief Валюта.
 */
enum class Currency : std::uint16_t {
    /** Рубль */
    RUB = 0,
    /** Доллар */
    USD,
    /** Евро */
    EUR
};

/**
 * @brief Тип совершаемой сделки
 */
enum class TransactionType : std::uint16_t {
    /** Покупка */
    BUY = 0,
    /** Продажа */
    SALE,
    /** Дивиденды */
    DIVIDENDS,
    /** купонная доходность */
    COUPON
};

/**
 * @brief Структура описывает сделки совершенные с ценными бумагами
 */
struct Transaction {
    /**
     * @brief company_ticker тикер компании (код актива)
     */
    std::string company_ticker;
    /**
     * @brief number номер сделки
     */
    Transaction_t::transaction_number_t number;
    /**
     * @brief type тип сделки
     */
    TransactionType type;
    /**
     * @brief date дата сделки
     */
    Date date;
    /**
     * @brief price стоимость покупки
     */
    Transaction_t::price_t price;
    /**
     * @brief currency валюта сделки
     */
    Currency currency;
    /**
     * @brief amount количество единиц актива в сделке
     */
    Transaction_t::amount_of_deals_t amount;
    /**
     * @brief summ_price суммарная стоимость
     */
    Transaction_t::price_t summ_price;
    /**
     * @brief summ_commission суммарные комиссии
     */
    Transaction_t::price_t summ_commission;

};




} //namespace utils
#endif // DATATYPES_H
