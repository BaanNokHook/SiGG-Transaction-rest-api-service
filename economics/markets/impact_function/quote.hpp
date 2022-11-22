/**
 * @file quote.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MARKET_ECOLOGY_IMPACT_FUNCTION_QUOTE_HPP
#define MARKET_ECOLOGY_IMPACT_FUNCTION_QUOTE_HPP

#include <esl/economics/markets/quote_message.hpp>



namespace esl::economics::markets::impact_function {
    class quote_message
    : public markets::quote_message<
            quote_message, interaction::library_message_code<0x00B0U>()>
    {
        using markets::quote_message<
            quote_message, interaction::library_message_code<0x00B0U>()>::quote_message;
    };
}

#endif  // MARKET_ECOLOGY_IMPACT_FUNCTION_QUOTE_HPP
