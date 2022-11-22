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
#ifndef ESL_ORDER_MESSAGE_HPP
#define ESL_ORDER_MESSAGE_HPP

#include <cstdint>

#include <esl/interaction/message.hpp>
#include <esl/economics/markets/quote_message.hpp>

namespace esl::economics::markets {


///
/// \brief
/// \tparam message_type_
/// \tparam type_code_
template<typename message_type_, std::uint64_t type_code_>
struct order_message
    : public interaction::message<message_type_, type_code_>
{
    order_message(
        const identity<agent> &sender       = identity<agent>(),
        const identity<agent> recipient     = identity<agent>(),
        simulation::time_point sent         = simulation::time_point(),
        simulation::time_point received     = simulation::time_point())
        : interaction::message<message_type_, type_code_>(sender, recipient,
                                                          sent, received)
    {

    }

    ///
    /// Conventions: the order replies directly to the sender sending
    /// the quote, during the same timestep the quote is received \param
    /// q    The quote this order is a direct response to.
    ///
    template<typename quote_type_, std::uint64_t _>
    order_message(const markets::quote_message<quote_type_, _> &q)
        : interaction::message<message_type_, type_code_>(
        q.recipient, q.sender, q.received, q.received)
    {

    }

    template<class archive_t>
    void serialize(archive_t &archive, const unsigned int version)
    {
        (void)version;
        archive &make_nvp(
            "interaction〈message_type_,type_code_〉",
            boost::serialization::base_object<
            interaction::message<message_type_, type_code_>>(
                *this));
    }
};



}



#ifdef WITH_MPI
#include <boost/mpi/datatype.hpp>
namespace boost::mpi {

template<typename message_type_, uint64_t type_code_>
struct is_mpi_datatype<
    esl::economics::markets::order_message<message_type_, type_code_>>
: public mpl::false_
{

};
}  // namespace boost::mpi
#endif  // WITH_MPI


#endif  // ESL_ORDER_MESSAGE_HPP
