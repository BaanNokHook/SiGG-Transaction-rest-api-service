/**
 * @file execution_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_EXECUTION_MESSAGE_HPP
#define ME_EXECUTION_MESSAGE_HPP


#include <esl/interaction/message.hpp>
#include <esl/law/property_collection.hpp>
#include <esl/economics/markets/quote.hpp>
#include <esl/economics/markets/indication.hpp>


namespace esl::economics::markets {

    template<typename message_type_, uint64_t type_code_>
    struct execution_message
    : public interaction::message<message_type_, type_code_>
    {
        typedef std::pair<price, quantity> execution_t;

        law::property_map<execution_t> executed;
    };

}

#endif //ME_EXECUTION_MESSAGE_HPP
