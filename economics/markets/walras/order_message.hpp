/**
 * @file order_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_WALRAS_ORDER_MESSAGE_HPP
#define ESL_WALRAS_ORDER_MESSAGE_HPP


#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>

#include <esl/economics/markets/order_message.hpp>


namespace esl::economics::markets::walras {
    ///
    /// \brief
    ///
    template<typename message_type_, std::uint64_t type_code_>
    struct walras_order_message
    : public esl::economics::markets::order_message<message_type_, type_code_>
    , public virtual demand_supply_function
    {
        walras_order_message(
            identity<agent> sender, identity<agent> recipient,
            simulation::time_point sent     = simulation::time_point(),
            simulation::time_point received = simulation::time_point())
        : markets::order_message<message_type_, type_code_>(sender, recipient,
                                                            sent, received)
        {}

        template<typename quote_type_, uint64_t any_>
        explicit walras_order_message(
            const markets::quote_message<quote_type_, any_> &q)
        : markets::order_message<message_type_, type_code_>(q)
        {}

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            typedef markets::order_message<message_type_, type_code_>
                order_message_type;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(order_message_type);
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(
                demand_supply_function);
        }
    };
}  // namespace esl::economics::markets::walras


#ifdef WITH_MPI
#include <boost/mpi.hpp>
namespace boost::mpi {

    template<typename message_type_, uint64_t type_code_>
    struct is_mpi_datatype<esl::economics::markets::walras::
                               walras_order_message<message_type_, type_code_>>
    : public mpl::false_
    {

    };
} // namespace boost::mpi
#endif  // WITH_MPI


#endif  // ESL_WALRAS_ORDER_MESSAGE_HPP
