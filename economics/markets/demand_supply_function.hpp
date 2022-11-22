/**
 * @file demand_supply_function.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ESL_SUPPLY_DEMAND_FUNCTION_HPP
#define ESL_SUPPLY_DEMAND_FUNCTION_HPP

#include <array>
#include <vector>


#include <esl/economics/markets/quote.hpp>
// for fungible, agree on basis (fractions)
// for infungible, demand can logically be only 0 or 1...
// multiple dimensions, because we can have dependent demand (packages,
// constraints)

/*
namespace esl {

    template<typename identifiable_t_>
    struct identity;

    namespace law {
        struct property;
    }  // namespace law
}  // namespace esl
*/
#include <esl/simulation/identity.hpp>
#include <esl/law/property.hpp>


namespace esl::economics::markets {
    ///
    /// \brief                  excess demand (demand-supply) function dynamic in the number of properties.
    ///
    struct demand_supply_function
    {
        virtual ~demand_supply_function() = default;
        ///
        /// \param quotes
        /// \return
        virtual std::map<identity<law::property>, double>
        excess_demand(const std::map<identity<law::property>,
                                     std::tuple<quote, double>>
                          &quotes) const = 0;

        ///
        /// \tparam archive_t
        /// \param archive
        /// \param version
        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)archive;
            (void)version;
        }
    };

}//

#ifdef WITH_MPI
namespace boost::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::markets::demand_supply_function>
    : public mpl::true_
    {
        
    };
}      // namespace boost::mpi
#endif  // WITH_MPI

#endif  // ESL_SUPPLY_DEMAND_FUNCTION_HPP
