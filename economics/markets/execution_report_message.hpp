/**
 * @file execution_report_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_EXECUTION_REPORT_MESSAGE_HPP
#define ESL_EXECUTION_REPORT_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief
    ///
    struct execution_report_message
    : public interaction::message< execution_report_message
    , interaction::library_message_code<0x00C09>()
    >
    {
        /// 
        /// \brief  The order that generated this execution
        /// 
        limit_order order;

        ///
        /// \brief  Report data
        /// 
        execution_report report;

        explicit execution_report_message( const identity<agent> &sender     = identity<agent>()
                                         , const identity<agent> &recipient  = identity<agent>()
                                         , simulation::time_point sent       = simulation::time_point()
                                         , simulation::time_point received   = simulation::time_point()
                                         )
        : interaction::message< execution_report_message
                              , interaction::library_message_code<0x00C09>()
                              >::message(sender, recipient, sent, received)
        {

        }

    };
}//namespace esl::economics::markets


#endif//ESL_EXECUTION_REPORT_MESSAGE_HPP