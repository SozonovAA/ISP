//
// Created by andrey on 19.12.2021.
//
#include <iostream>
#include <iterator>
#include "urlRequests.h"
#include "curl/curl.h"


/**
 * Функция, которая используется, для возвращения URL запроса в строку.
 */
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

namespace financedata {

    std::string request(  std::string _req  ) {
        CURL *curl;
        CURLcode res;

        std::string response_string;
        std::string header_string;

        curl = curl_easy_init();
        if (curl) {
            res = curl_easy_setopt(curl, CURLOPT_URL,
                                   _req.c_str());

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));

            /* always cleanup */
            curl_easy_cleanup(curl);
        }

        return response_string;
    }


}
