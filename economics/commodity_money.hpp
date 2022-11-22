/**
 * @file commodity_money.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_COMMODITY_MONEY_HPP
#define ESL_COMMODITY_MONEY_HPP

#include <esl/economics/commodity.hpp>
#include <esl/economics/physical_money.hpp>


namespace esl::economics {

    struct commodity_money
    : virtual commodity
    , virtual physical_money
    {
        virtual ~commodity_money() = default;

    };

}

#endif//ESL_COMMODITY_MONEY_HPP
