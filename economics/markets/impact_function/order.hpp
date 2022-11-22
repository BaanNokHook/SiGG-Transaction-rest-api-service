/**
 * @file order.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MARKET_ECOLOGY_IMPACT_FUNCTION_ORDER_HPP
#define MARKET_ECOLOGY_IMPACT_FUNCTION_ORDER_HPP


#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>

#include <esl/economics/markets/order_message.hpp>


namespace esl::economics::markets::impact_function {

    struct order_message
    : public esl::economics::markets::order_message<order_message, interaction::library_message_code<0x00B2U>()>
    {

        enum side_t
        { buy
        , sell
        } side;

        law::property_map<std::pair<std::uint64_t, side_t>> volumes;


        order_message( identity<agent> sender
                      , identity<agent> recipient
                      , simulation::time_point sent     = simulation::time_point()
                      , simulation::time_point received = simulation::time_point())
        : markets::order_message<order_message, interaction::library_message_code<0x00B2U>()>
            (sender, recipient, sent, received)
        {

        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            typedef markets::order_message<order_message, interaction::library_message_code<0x00B2U>()>
                order_message_type;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(order_message_type);
        }
    };
}

#endif  // MARKET_ECOLOGY_IMPACT_FUNCTION_ORDER_HPP
