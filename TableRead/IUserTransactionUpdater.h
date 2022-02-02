#ifndef IUSERTRANSACTIONUPDATER_H
#define IUSERTRANSACTIONUPDATER_H
#include <map>
#include <string>
#include <vector>


#include "../Utils/DataTypes.h"

namespace teble_read {
/**
 * @brief Брокер.
 */
enum Brokers : std::uint16_t {
    TINKOFF = 0,
    VTB,
    SBER
};
/**
 * @brief Интерфейсный класс для получения данных о сделках пользователя.
 */
class IUserTransactionUpdater {
public:
    /**
     * Тип данных описывающи историю сделок совершенных с ценными бумагами.
     */
    using transactions_map = std::map<
    utils::Transaction_t::ticker_t,
    std::vector< utils::Transaction >
    >;

    /**
     * Тип данных, описывающий одну сделку.
     */
    using single_transaction = std::pair<
    utils::Transaction_t::ticker_t,
    utils::Transaction
    >;

    /**
     * @brief get_transactions_map получение информации о сделках пользователя
     * @return сделки пользователя
     */
    virtual
    const transactions_map & get_transactions_map() = 0;

    /**
     * @brief set_transactions_map задать заранее сформированую мапу со
     * сделками пользователя
     */
    virtual
    void set_transactions_map( transactions_map & _usr_transactions ) = 0;

    /**
     * @brief add_transaction добавить транзакцию в мапу сделок
     */
    virtual void add_transaction( const single_transaction & _transaction );

    /**
     * @brief delete_transaction функция находит уже существующую сделку
     * и удаляет её из истории сделок
     */
    virtual void delete_transaction( const single_transaction & _transaction );

    /**
     * @brief read_table составление истории сделок после чтения файла
     * @return признак успешного чтения и составления истории сделок
     */
    virtual bool read_table( std::string _filepath, Brokers _broker ) = 0;
};

} // namespace teble_read


#endif // IUSERTRANSACTIONUPDATER_H
