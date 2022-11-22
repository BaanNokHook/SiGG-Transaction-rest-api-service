/**
 * @file logon_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_LOGON_MESSAGE_HPP
#define ME_LOGON_MESSAGE_HPP

#include <esl/interaction/message.hpp>

#include <boost/container/flat_map.hpp>

namespace esl::economics::markets {

    ///
    /// \brief  A message sent by the client to register with exchange, and to
    /// register a supply.
    ///
    struct logon_message
    : public interaction::message<logon_message,interaction::library_message_code<0x00C00>()>
    {
        boost::container::flat_map<ticker, std::uint64_t> supply;

        explicit logon_message( const identity<agent> &sender    = identity<agent>()
                              , const identity<agent> &recipient = identity<agent>()
                              , simulation::time_point sent      = simulation::time_point()
                              , simulation::time_point received  = simulation::time_point()
                              )
        : interaction::message< logon_message
                              , interaction::library_message_code<0x00C00>()>::message( sender
                                                                                      , recipient
                                                                                      , sent
                                                                                      , received
                                                                                      )
        {

        }


        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
 
            archive &boost::serialization::make_nvp( "message⟨logon_message⟩"
                                                   , boost::serialization::base_object<
                                                            interaction::message<logon_message,interaction::library_message_code<0x00C00>()>
                                                                                      >(*this));

            archive &BOOST_SERIALIZATION_NVP(supply);
        }
    };
}//namespace esl::economics::markets


#endif//ME_LOGON_MESSAGE_HPP