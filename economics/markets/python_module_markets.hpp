/**
 * @file python_module_markets.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_PYTHON_MODULE_MARKETS_HPP
#define ESL_PYTHON_MODULE_MARKETS_HPP

#include <esl/economics/markets/quote_message.hpp>
#include <esl/interaction/header.hpp>

namespace esl::economics::markets {
#ifdef WITH_PYTHON
    struct python_quote_message
    : quote_message<python_quote_message, interaction::library_message_code<0x0100>()>
    {

    };

#endif

}//namespace esl::economics::markets

#endif  // ESL_PYTHON_MODULE_MARKETS_HPP
