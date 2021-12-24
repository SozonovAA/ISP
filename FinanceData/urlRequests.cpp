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

    std::string urlRequests::request() {
        CURL *curl;
        CURLcode res;

        std::string response_string;
        std::string header_string;

        //todo: подумать как это делать
        AlphaVintageAPIParametrs api {
            .function = AlphaVintageAPIParametrs::TIME_SERIES_DAILY_ADJUSTED,
            .symbol = "IBM"
        };

        curl = curl_easy_init();
        if (curl) {
            res = curl_easy_setopt(curl, CURLOPT_URL, api.request().c_str());
            /* example.com is redirected, so we tell libcurl to follow redirection */
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

    std::string AlphaVintageAPIParametrs::request() {
        std::string return_string {"https://www.alphavantage.co/query?"};
        switch ( function ) {
            case TIME_SERIES_DAILY_ADJUSTED:
                return_string += "function=TIME_SERIES_DAILY_ADJUSTED";
                break;

        }

        return_string += ( "&symbol=" + symbol );

        if ( oz ) {
            switch ( oz ) {
                case COMPACT:
                    return_string += "&outputsize=compact";
                    break;
                case FULL:
                    return_string += "&outputsize=full";
                    break;
            }
        }
        if ( datatype ) {
            switch ( datatype ) {
                case JSON:
                    return_string += "&datatype=json";
                    break;
            }
        }

        return_string += ( "&apikey=" + API_KEY );

        return return_string;
    }
}