/**
 * @file physical_money.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_PHYSICAL_MONEY_HPP
#define ESL_PHYSICAL_MONEY_HPP

#include <esl/economics/money.hpp>
#include <esl/economics/tangible.hpp>


namespace esl::economics {
    struct physical_money
    : public virtual money
    , public virtual tangible
    {
        physical_money(currency denomination, uint64_t quantity = 0)
        : money(denomination, quantity)
        {

        }

        virtual ~physical_money() = default;
    };

}

#endif//ESL_PHYSICAL_MONEY_HPP
