/**
 * @file indication.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_INDICATION_HPP
#define ESL_INDICATION_HPP

#include <cstdint>


namespace esl::economics::markets {
    ///
    /// \brief  Denotes whether or not a quote that is sent is binding for
    ///         the sender, meaning that the sender must deliver at the quote
    ///         if the recipient accepts the offer.
    ///
    enum indication
    : std::uint8_t
    {
        firm,
        indicative
    };

}  // namespace esl::economics::markets

#ifdef WITH_MPI
#include <boost/mpi/datatype.hpp>
namespace boost::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::markets::indication>
    : public mpl::true_
    {

    };
}  // namespace boost::mpi
#endif  // WITH_MPI

#endif  // ESL_INDICATION_HPP
