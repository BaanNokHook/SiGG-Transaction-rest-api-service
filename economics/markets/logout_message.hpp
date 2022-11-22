/**
 * @file logout_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_LOGOUT_MESSAGE_HPP
#define ME_LOGOUT_MESSAGE_HPP

#include <esl/interaction/message.hpp>

namespace esl::economics::markets {
    ///
    /// \brief  A message that is sent by the client to deregister from an exchange.
    ///         Triggers settlement of trades, and cancels any data subscriptions
    ///
    struct logout_message
    : public interaction::message<logout_message,
                                  interaction::library_message_code<0x00C01>()>
    {
        explicit logout_message(
            const identity<agent> &sender    = identity<agent>(),
            const identity<agent> &recipient = identity<agent>(),
            simulation::time_point sent      = simulation::time_point(),
            simulation::time_point received  = simulation::time_point())
        : interaction::message<
            logout_message,
            interaction::library_message_code<0x00C01>()>::message(sender,
                                                                   recipient,
                                                                   sent,
                                                                   received)
        { 
        
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
 
            archive &boost::serialization::make_nvp( "message⟨logout_message⟩"
                                                   , boost::serialization::base_object<
                                                            interaction::message<logout_message,interaction::library_message_code<0x00C01>()>
                                                                                      >(*this));
        }
    };

}//namespace esl::economics::markets


#endif//ME_LOGOUT_MESSAGE_HPP