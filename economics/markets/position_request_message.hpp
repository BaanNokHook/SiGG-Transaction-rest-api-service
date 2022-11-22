/**
 * @file position_request_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_POSITION_REQUEST_MESSAGE_HPP
#define ESL_POSITION_REQUEST_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief  The sender asks the exchange to update them of their trading
    ///         position.
    ///
    struct position_request_message
    : public interaction::message< position_request_message
                                 , interaction::library_message_code<0x00C0A>()
                                 >
    {
        // TODO
    };
}//namespace esl::economics::markets


#endif//ESL_POSITION_REQUEST_MESSAGE_HPP