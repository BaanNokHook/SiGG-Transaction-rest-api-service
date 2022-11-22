﻿/// \file   new_order_single_message.hpp
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