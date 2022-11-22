/**
 * @file cancel_order_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_CANCEL_ORDER_MESSAGE_HPP
#define ESL_CANCEL_ORDER_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief
    ///
    struct cancel_order_message
    : public interaction::message< cancel_order_message
                                 , interaction::library_message_code<0x00C07>()
                                 >
    {
        ticker symbol;

        basic_book::order_identifier order;

        // TODO
        explicit cancel_order_message(
                                        const identity<agent> &sender    = identity<agent>(),
                                        const identity<agent> &recipient = identity<agent>(),
                                        simulation::time_point sent      = simulation::time_point(),
                                        simulation::time_point received  = simulation::time_point())
        : interaction::message<
            cancel_order_message,
            interaction::library_message_code<0x00C07>()>::message(sender,
                                                                   recipient,
                                                                   sent,
                                                                   received)
        {
        
        }

    };
}//namespace esl::economics::markets


#endif//ESL_CANCEL_ORDER_MESSAGE_HPP