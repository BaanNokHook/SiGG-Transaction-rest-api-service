/**
 * @file market_data_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_MARKET_DATA_MESSAGE_HPP
#define ESL_MARKET_DATA_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/order_book/order.hpp>

namespace esl::economics::markets {
    ///
    /// \brief
    ///
    struct market_data_message
    : public interaction::message<market_data_message, interaction::library_message_code<0x00C0B>()>
    {
        /// 
        /// \brief  
        /// 
        time_interval period;

        ticker symbol;

        // TODO: decide to add timestamp or not 

        std::vector<std::pair<quote, size_t>> ask;

        std::vector<std::pair<quote, size_t>> bid;
        
        std::vector<std::pair<quote, size_t>> trades;

        explicit market_data_message( const identity<agent> &sender    = identity<agent>()
                                    , const identity<agent> &recipient = identity<agent>()
                                    , simulation::time_point sent      = simulation::time_point()
                                    , simulation::time_point received  = simulation::time_point()
                                    )
        : interaction::message< market_data_message
                              , interaction::library_message_code<0x00C0B>()
                              >::message( sender
                                        , recipient
                                        , sent
                                        , received
                                        )
        {

        }
    };
}//namespace esl::economics::markets


#endif//ESL_MARKET_DATA_MESSAGE_HPP