/**
 * @file dividend.cpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <esl/economics/finance/dividend.hpp>

namespace esl::economics::finance {

    dividend_policy::dividend_policy(
        simulation::time_point announcement_date,
        simulation::time_point ex_dividend_date,
        const simulation::time_interval &dividend_period,
        simulation::time_point payable_date,
        const iso_4217 &dividend_currency,
        const std::map<share_class, std::tuple<std::uint64_t, price>>
        &dividend_per_share)
        : announcement_date(announcement_date)
        , ex_dividend_date(ex_dividend_date)
        , dividend_period(dividend_period)
        , payable_date(payable_date)
        , dividend_currency(dividend_currency)
        , dividend_per_share(dividend_per_share)
    {

    }

    price dividend_policy::total_dividends() const
    {
        price total_ = price::approximate(0.00, dividend_currency);
        for(const auto &[s, dividend_distribution] : dividend_per_share) {
            (void)s;
            total_ += (std::get<0>(dividend_distribution)
                       * std::get<1>(dividend_distribution));
        }
        return total_;
    }
}  // namespace esl::economics::finance

