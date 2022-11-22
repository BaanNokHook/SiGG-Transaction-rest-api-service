/**
 * @file new_order_list_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_NEW_ORDER_LIST_MESSAGE_HPP
#define ESL_NEW_ORDER_LIST_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief  Places multiple orders on the exchange, assuring that all orders are executed in sequence without
    ///         interleaving other market participants' orders as can happen with multiple single-order messages.
    ///
     
    struct new_order_list_message
    : public interaction::message< new_order_list_message
                                 , interaction::library_message_code<0x00C06>()
                                 >
    {
        std::vector<limit_order> order_details;

        explicit new_order_list_message( const identity<agent> &sender    = identity<agent>()
                                       , const identity<agent> &recipient = identity<agent>()
                                       , simulation::time_point sent      = simulation::time_point()
                                       , simulation::time_point received  = simulation::time_point()
                                       )
        :interaction::message< new_order_list_message
                             , interaction::library_message_code<0x00C06>()>::message( sender
                                                                                     , recipient
                                                                                     , sent
                                                                                     , received
                                                                                     )
        {

        }

    };
}//namespace esl::economics::markets


#endif//ESL_NEW_ORDER_LIST_MESSAGE_HPP