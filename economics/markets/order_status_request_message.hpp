/**
 * @file order_status_request_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_ORDER_STATUS_REQUEST_MESSAGE_HPP
#define ME_ORDER_STATUS_REQUEST_MESSAGE_HPP

#include <esl/interaction/message.hpp>


namespace esl::economics::markets {
    ///
    /// \brief  Requests the status of an order, or if no order is specified, all the participant's orders
    ///
    struct order_status_request_message
    : public interaction::message< order_status_request_message
                                 , interaction::library_message_code<0x00C03>()
                                 >
    {
        explicit order_status_request_message( const identity<agent> &sender     = identity<agent>()
                                             , const identity<agent> &recipient  = identity<agent>()
                                             , simulation::time_point sent       = simulation::time_point()
                                             , simulation::time_point received   = simulation::time_point()
                                             )
        :interaction::message<  order_status_request_message
        , interaction::library_message_code<0x00C03>()
        >::message(sender, recipient, sent, received)
        {

        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
 
            archive &boost::serialization::make_nvp( "message⟨order_status_request_message⟩"
                                                   , boost::serialization::base_object<
                                                            interaction::message<order_status_request_message,interaction::library_message_code<0x00C03>()>
                                                                                      >(*this));

        }
    };
}//namespace esl::economics::markets


#endif//ME_ORDER_STATUS_REQUEST_MESSAGE_HPP