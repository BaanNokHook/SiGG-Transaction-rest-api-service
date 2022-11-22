/**
 * @file fungibility.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_FUNGIBILITY_HPP
#define ESL_FUNGIBILITY_HPP

#include <esl/law/property.hpp>


namespace esl::economics {

    ///
    /// \brief  An object that is fungible is interchangeable for objects of the
    /// same types.
    ///
    /// \example
    ///
    struct fungible
    {
        virtual ~fungible() = default;

        [[nodiscard]] constexpr bool is_fungible() const
        {
            return true;
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)archive;
            (void)version;
        }
    };


    struct infungible
    {
        virtual ~infungible() = default;

        [[nodiscard]] constexpr bool is_fungible() const
        {
            return false;
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)archive;
            (void)version;
        }
    };

}  // namespace esl::economics


#ifdef WITH_MPI
#include <boost/mpi.hpp>
namespace boost::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::fungible>
        : public mpl::true_
    {};

    template<>
    struct is_mpi_datatype<esl::economics::infungible>
        : public mpl::true_
    {};
}  // namespace boost::mpi
#endif  // WITH_MPI


#endif  // ESL_FUNGIBILITY_HPP
