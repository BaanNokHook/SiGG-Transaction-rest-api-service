/**
 * @file new_order_single_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_NEW_ORDER_SINGLE_MESSAGE_HPP
#define ESL_NEW_ORDER_SINGLE_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief
    ///
    struct new_order_single_message
    : public interaction::message<new_order_single_message
    , interaction::library_message_code<0x00C05>()
    >
    {
        limit_order order_details;

        explicit new_order_single_message( const identity<agent> &sender     = identity<agent>()
                                         , const identity<agent> &recipient  = identity<agent>()
                                         , simulation::time_point sent       = simulation::time_point()
                                         , simulation::time_point received   = simulation::time_point()
                                         )
        :interaction::message<  new_order_single_message
        , interaction::library_message_code<0x00C05>()>::message(sender,
                                                                   recipient,
                                                                   sent,
                                                                   received)
        {

        }

        new_order_single_message &operator=(const new_order_single_message &o) = default;
    };
}//namespace esl::economics::markets


#endif//ESL_NEW_ORDER_SINGLE_MESSAGE_HPP