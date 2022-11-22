/**
 * @file money.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_MONEY_HPP
#define ESL_MONEY_HPP

#include <esl/economics/asset.hpp>
#include <esl/economics/fungibility.hpp>
#include <esl/algorithms.hpp>
#include <esl/quantity.hpp>
#include <esl/economics/price.hpp>


namespace esl::economics {
    ///
    /// \brief  Money is the idea that an amount of currency is a fungible asset
    ///         and it further specializes into intangible (cash) and tangible
    ///         (physical money < commodity money) forms of assets.
    ///
    struct money
    : public asset
    , public fungible
    {
        iso_4217 denomination;

        explicit money(iso_4217 denomination, identity<property> i = identity<property>())
        : law::property(i)
        , asset(i)
        , fungible()
        , denomination(denomination)
        {

        }

        virtual ~money() = default;

        virtual std::string name() const  // C++20 constexpr
        {
            std::stringstream stream_;
            stream_ << denomination << " money";
            return stream_.str();
        }

        inline bool operator == (const money &m) const
        {
            return this->denomination == m.denomination;
        }

        inline bool operator != (const money &m) const
        {
            return !(*this == m);
        }

        ///
        quantity amount(double real = 0.,
                        std::function<uint64_t(double)> rounding_rule =
                        rounding::integer_towards_zero<double, uint64_t>)
        {
            return quantity(rounding_rule(real * denomination.denominator));
        }

        esl::economics::price price(const quantity &q)
        {
            return esl::economics::price(int64_t(q.amount), denomination);
        }

        esl::economics::price price(double real = 0.,
                    std::function<int64_t(double)> rounding_rule =
                    rounding::integer_towards_zero<double, int64_t>)
        {
            return esl::economics::price(rounding_rule(real * denomination.denominator),
                                         denomination);
        }

    };

}  // namespace esl::economics

#endif  // ESL_MONEY_HPP
