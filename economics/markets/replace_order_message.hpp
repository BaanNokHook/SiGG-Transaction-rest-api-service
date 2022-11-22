/**
 * @file replace_order_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_REPLACE_ORDER_MESSAGE_HPP
#define ESL_REPLACE_ORDER_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief
    ///
    struct replace_order_message
    : public markets::quote_message<
          replace_order_message, interaction::library_message_code<0x00C08>()>
    {
        // TODO
    };
}//namespace esl::economics::markets


#endif//ESL_REPLACE_ORDER_MESSAGE_HPP