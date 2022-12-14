/**
 * @file shareholder.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/finance/shareholder.hpp>

#include <esl/economics/company.hpp>
#include <esl/economics/finance/dividend.hpp>
#include <esl/economics/finance/share_class.hpp>
#include <esl/economics/markets/walras/quote_message.hpp>
#include <esl/simulation/identity.hpp>

#include <algorithm>
using std::min;

namespace esl::economics::finance {

    shareholder::shareholder()
        : shareholder(identity<shareholder>())
    {

    }

    shareholder::shareholder(const identity<shareholder> &i)
    : agent(i)
    , owner<cash>(i)
    , owner<stock>(i)
    , stocks()
    {
        //create_output<share_holdings>("holdings");

        auto handle_dividend_date_ =
            [this](std::shared_ptr<dividend_announcement_message> m,
                   simulation::time_interval step, std::seed_seq &seed) {
                (void) seed;
                ex_dividend_dates.insert(
                    {m->policy.ex_dividend_date,
                     dynamic_identity_cast<company>(m->sender)});

                return submit_dividend_record(step);
            };

        ESL_REGISTER_CALLBACK(dividend_announcement_message, 0, handle_dividend_date_, "submit investor record on dividend date");

        auto extract_prices_ =
            [this](std::shared_ptr<markets::walras::quote_message> m,
                   simulation::time_interval step, std::seed_seq &seed) {
                (void) seed;
                for(auto &[k, v] : m->proposed){
                    assert(std::holds_alternative<price>(v.type));

                    auto i = prices.find(k);
                    if(prices.end() == i){
                        prices.emplace(k, std::get<price>(v.type));
                    }else{
                        i->second.value = std::get<price>(v.type).value;
                    }
                }
                return step.upper;
            };

        ESL_REGISTER_CALLBACK(markets::walras::quote_message, 0, extract_prices_, "extract stock prices from Walrasian market");

    }

    simulation::time_point
    shareholder::submit_dividend_record(simulation::time_interval interval)
    {
        for(auto i = ex_dividend_dates.begin(); i != ex_dividend_dates.end();
            ++i) {
            const auto &[s, c] = *i;
            if(interval.lower <= s && interval.upper >= s) {  // reply ASAP
                if(shares.find(c) != shares.end()) {
                    auto record_ = this->create_message<dividend_record>(
                        c, 0, this->identifier, c, shares[c]);
                }
            }
        }
        return interval.upper;
    }

    std::map<identity<law::property>, esl::quantity>
    shareholder::stock_holdings() const
    {
        std::map<identity<law::property>, quantity> result_;

        for(const auto &[k, v] : shares) {
            for(const auto &[share_, amount_] : v) {
                auto key_         = std::make_tuple(k, share_);
                auto property_id_ = stocks.find(key_)->second;

                auto iterator_ = result_.find(property_id_);

                if(result_.end() == iterator_) {
                    result_.insert(
                        std::make_pair(property_id_, quantity(amount_)));
                } else {
                    iterator_->second += quantity(amount_);
                }
            }
        }

        return result_;
    }
}