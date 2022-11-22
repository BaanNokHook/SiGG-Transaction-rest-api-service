/**
 * @file quote_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_WALRAS_QUOTE_MESSAGE_HPP
#define ESL_WALRAS_QUOTE_MESSAGE_HPP


#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>

#include <esl/economics/markets/quote_message.hpp>


namespace esl::economics::markets::walras {
    struct quote_message
    : public markets::quote_message<
          quote_message, interaction::library_message_code<0x00A0U>()>
    {
        explicit quote_message(
            identity<agent> sender            = identity<agent>(),
            identity<agent> recipient         = identity<agent>(),
            law::property_map<quote> proposed = {},
            simulation::time_point sent       = simulation::time_point(),
            simulation::time_point received   = simulation::time_point())
        : markets::quote_message<
            quote_message, interaction::library_message_code<0x00A0U>()>(
            std::move(sender), std::move(recipient), proposed,
            markets::indication::indicative, sent, received)
        {

        }

        virtual ~quote_message() = default;

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            typedef markets::quote_message<
                quote_message,
                esl::interaction::library_message_code<0x00A0U>()>
                quote_message_base_type;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(
                quote_message_base_type);
        }
    };
}  // namespace esl::economics::walras

#ifdef WITH_MPI
#include <boost/mpi.hpp>
namespace boost::mpi {

    template<>
    struct is_mpi_datatype<esl::economics::markets::walras::quote_message>
    : public mpl::false_
    {

    };

}  // namespace boost::mpi
#endif  // WITH_MPI

#endif  // ESL_WALRAS_QUOTE_MESSAGE_HPP
