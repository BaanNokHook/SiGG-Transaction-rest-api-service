/**
 * @file standard.cpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/accounting/standard.hpp>


namespace esl::economics::accounting {

    standard::standard(iso_4217 reporting_currency)
    : reporting_currency(reporting_currency)
    {
        foreign_currencies.emplace( reporting_currency
                                  , exchange_rate(1,1));
    }

}