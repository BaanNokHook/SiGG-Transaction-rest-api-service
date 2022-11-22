/**
 * @file commodity.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_COMMODITY_HPP
#define ESL_COMMODITY_HPP

#include <esl/economics/asset.hpp>
#include <esl/economics/fungibility.hpp>
#include <esl/economics/tangibility.hpp>


namespace esl::economics {

    struct commodity
    : public virtual asset
    , public virtual fungible
    , public virtual tangible
    {
        explicit commodity()
        : asset()
        , fungible()
        , tangible()
        {

        }

        virtual ~commodity() = default;
    };

}

#endif//ESL_COMMODITY_HPP
