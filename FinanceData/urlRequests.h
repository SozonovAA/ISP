//
// Created by andrey on 19.12.2021.
//


#ifndef ISP_URLREQUESTS_H
#define ISP_URLREQUESTS_H
#include <string>
namespace financedata {

/**
 * @brief request функция реализует https запрос
 * @param _req https запрос
 * @return результат запроса
 */
std::string request( std::string _req );

}


#endif //ISP_URLREQUESTS_H
