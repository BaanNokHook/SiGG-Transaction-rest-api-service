/**
 * @file order_status_response_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_ORDER_STATUS_RESPONSE_MESSAGE_HPP
#define ME_ORDER_STATUS_RESPONSE_MESSAGE_HPP

#include <esl/interaction/message.hpp>

namespace esl::economics::markets {
    ///
    /// \brief  A structure with the status of one or more orders
    ///
    struct order_status_response_message
    : public markets::quote_message< order_status_response_message
                                   , interaction::library_message_code<0x00C04>()
                                   >
    {
        explicit order_status_response_message( const identity<agent> &sender       = identity<agent>()
                                                , const identity<agent> &recipient  = identity<agent>()
                                                , law::property_map<quote> proposed = {}
                                                , indication binding                = indication::firm
                                                , simulation::time_point sent       = simulation::time_point()
                                                , simulation::time_point received   = simulation::time_point()
                                                )
        : markets::quote_message< order_status_response_message
        , interaction::library_message_code<0x00C04>()
        >::quote_message(sender, recipient, proposed, binding, sent, received)
        {

        }
    };
}//namespace esl::economics::markets


#endif//ME_ORDER_STATUS_RESPONSE_MESSAGE_HPP