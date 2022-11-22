/**
 * @file differentiable_order_message.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_DIFFERENTIABLE_ORDER_MESSAGE_HPP
#define ESL_DIFFERENTIABLE_ORDER_MESSAGE_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>

#include <esl/economics/markets/differentiable_demand_supply_function.hpp>
#include <esl/economics/markets/order_message.hpp>
#include <esl/quantity.hpp>


namespace esl::economics::markets::walras {
    ///
    /// \brief  An order presented as an (automatically) differentiable excess
    /// demand function.
    ///
    struct differentiable_order_message
    : differentiable_demand_supply_function
    , public order_message< differentiable_order_message
                          , interaction::library_message_code<0x00A2U>()
                          >
    {
        ///
        /// \brief  The amounts supplied: long positions and short positions
        ///
        std::map<identity<law::property>, std::tuple<quantity, quantity>> supply;

        ///
        ///
        ///
        using order_message< differentiable_order_message
                           , interaction::library_message_code<0x00A2U>()
                           >::order_message;

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &boost::serialization::make_nvp(
                "order_message_0x00A2U",
                boost::serialization::base_object<markets::order_message<
                    differentiable_order_message,
                    esl::interaction::library_message_code<0x00A2U>()>>(*this));
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(
                differentiable_demand_supply_function);
        }
    };
}  // namespace walras


#ifdef WITH_MPI
#include <boost/mpi.hpp>
namespace boost::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::markets::walras::differentiable_order_message>
    : mpl::false_
    {

    };
}      // namespace boost::mpi
#endif  // WITH_MPI

#endif  // ESL_DIFFERENTIABLE_ORDER_MESSAGE_HPP
