﻿/// \file   order_status_request_message.hpp
///
/// \brief
///
/// \authors    Maarten
/// \date       2020-06-24
/// \copyright  Copyright 2017-2020 The Institute for New Economic Thinking,
///             Oxford Martin School, University of Oxford
///
///             Licensed under the Apache License, Version 2.0 (the "License");
///             you may not use this file except in compliance with the License.
///             You may obtain a copy of the License at
///
///                 http://www.apache.org/licenses/LICENSE-2.0
///
///             Unless required by applicable law or agreed to in writing,
///             software distributed under the License is distributed on an "AS
///             IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
///             express or implied. See the License for the specific language
///             governing permissions and limitations under the License.
///
///             You may obtain instructions to fulfill the attribution
///             requirements in CITATION.cff
///
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