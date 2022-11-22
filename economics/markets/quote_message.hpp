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
#ifndef ESL_QUOTE_MESSAGE_HPP
#define ESL_QUOTE_MESSAGE_HPP

#include <esl/interaction/message.hpp>
#include <esl/law/property_collection.hpp>
#include <esl/economics/markets/quote.hpp>
#include <esl/economics/markets/indication.hpp>


namespace esl::economics::markets {
    ///
    /// \brief
    /// \tparam message_type_
    /// \tparam type_code_
    template<typename message_type_, uint64_t type_code_>
    struct quote_message
    : public interaction::message<message_type_, type_code_>
    {
        ///
        /// \brief  Quotes for each property
        ///
        law::property_map<quote> proposed;

        ///
        /// \brief  Whether the sender is bound to deliver on the offered
        ///         quote (see @indication).
        ///
        indication binding;

        ///
        /// \brief
        ///
        explicit quote_message(
            identity<agent> sender            = identity<agent>(),
            identity<agent> recipient         = identity<agent>(),
            law::property_map<quote> proposed = {},
            indication binding                = indication::firm,
            simulation::time_point sent       = simulation::time_point(),
            simulation::time_point received   = simulation::time_point())
        : interaction::message<message_type_, type_code_>(sender, recipient,
                                                          sent, received)
        , proposed(move(proposed))
        , binding(binding)
        {

        }

        virtual ~quote_message() = default;

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &make_nvp(
                "interaction〈message_type_,type_code_〉",
                boost::serialization::base_object<
                    interaction::message<message_type_, type_code_>>(*this));
            archive &BOOST_SERIALIZATION_NVP(proposed);
            archive & BOOST_SERIALIZATION_NVP(binding);
        }
    };
}  // namespace esl::economics::markets


#ifdef WITH_MPI
#include <boost/mpi/datatype.hpp>

namespace boost::mpi {

    template<typename message_type_, uint64_t type_code_>
    struct is_mpi_datatype<
        esl::economics::markets::quote_message<message_type_, type_code_>>
        : public mpl::false_
    {

    };
}   // namespace boost::mpi
#endif  // WITH_MPI


#endif  // ESL_QUOTE_MESSAGE_HPP
