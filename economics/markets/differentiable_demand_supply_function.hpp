/**
 * @file differentiable_demand_supply_function.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_DIFFERENTIABLE_DEMAND_SUPPLY_FUNCTION_HPP
#define ESL_DIFFERENTIABLE_DEMAND_SUPPLY_FUNCTION_HPP

#include <map>

#include <esl/economics/markets/demand_supply_function.hpp>
#include <esl/mathematics/variable.hpp>


namespace esl::economics::markets {

    struct differentiable_demand_supply_function
    : public demand_supply_function
    {
        virtual ~differentiable_demand_supply_function() = default;


        virtual std::map<identity<law::property>, variable> excess_demand(
            const std::map<identity<law::property>,
                           std::tuple<quote, variable>> &quotes)
            const = 0;

#ifndef ADEPT_NO_AUTOMATIC_DIFFERENTIATION
        ///
        /// \brief  Shim to convert from auto-differentiated variables to double
        ///
        /// \param quotes
        /// \return
        virtual std::map<identity<law::property>, double> excess_demand(
            const std::map<identity<law::property>,
                           std::tuple<quote, double>> &quotes)
            const override
        {
            std::map<identity<law::property>,
                     std::tuple<quote, variable>>
                quotes_;
            for(auto [k, v] : quotes) {
                auto differential_ =
                    std::make_tuple(std::get<0>(v), variable(std::get<1>(v)));
                quotes_.emplace(k, differential_);
            }

            std::map<identity<law::property>, variable> intermediate_ =
                excess_demand(quotes_);

            std::map<identity<law::property>, double> result_;
            for(auto [k, v] : intermediate_) {
                result_.emplace(k, adept::value(v));
            }
            return result_;
        }
#endif

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)archive;
            (void)version;
        }
    };
}


#ifdef WITH_MPI
namespace boost { namespace mpi {

        template<>
        struct is_mpi_datatype<esl::economics::markets::differentiable_demand_supply_function>
            : public mpl::true_
        {};

    }}      // namespace boost::mpi
#endif  // WITH_MPI

#endif  // ESL_DIFFERENTIABLE_DEMAND_SUPPLY_FUNCTION_HPP
