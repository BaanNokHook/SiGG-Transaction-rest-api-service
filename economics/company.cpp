/**
 * @file company.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/company.hpp>

#include <tuple>

namespace esl::economics {

    std::set<identity<finance::shareholder>>
    company::unique_shareholders() const
    {
        std::set<identity<shareholder>> result_;
        for(const auto &[holder_, ownership_] : shareholders) {
            (void)ownership_;
            result_.insert(holder_);
        }
        return result_;
    }


    std::uint64_t company::total_shares() const
    {
        std::uint64_t result_ = 0;
        for(const auto &[s, c] : shares_outstanding) {
            (void) s;
            result_ += c;
        }
        return result_;
    }


    ///
    /// \warning: TODO advanced share rules including preference, cumulative
    /// shares etc \warning: the rounding rule is in favor of the company,
    /// fractional currency dividends are not paid out! \param
    /// unappropriated_profit \return
    std::map<finance::share_class, std::tuple<std::uint64_t, price>>
    company::compute_dividend_per_share(const price &unappropriated_profit)
    {
        // in the default implementation, the company does not pay out of it
        // did not have any excess income in the previous period
        if(double(unappropriated_profit) <= 0) {
            return {};
        }

        std::map<finance::share_class, std::tuple<std::uint64_t, price>> result_;

        double fraction_ = double(unappropriated_profit) / total_shares();

        for(const auto &[s, q]: shares_outstanding) {
            if(s.dividend) {
                result_.insert(make_pair(
                    s, std::make_tuple(q,cash(primary_jurisdiction.tender).price(fraction_ * q))));
            }
        }

        return result_;
    }

    company::company()
    : company(
        identity<company>(),
        law::jurisdiction(geography::countries::US, economics::currencies::USD))
    {}


    company::company(const identity<company> &i, const law::jurisdiction &j)
    : agent(i)
    , owner<cash>(i)
    , owner<finance::stock>(i)
    , organization(i, j)
    , shareholder(i)
    , identifiable_as<company>()
    , balance_sheet(*this)
    , last_announced_(0)
    , last_payment_(0)
    {}


    std::optional<finance::dividend_policy>
    company::upcoming_dividend(simulation::time_interval interval, std::seed_seq &seed)
    {
        (void)interval;
        (void)seed;
        return {};
    }


    simulation::time_point company::act(simulation::time_interval interval,
                                        std::seed_seq &s)
    {
        (void)s;

        auto possible_policy_ = upcoming_dividend(interval, s);
        auto next_event_      = interval.upper;

        if(!possible_policy_.has_value()) {
            return next_event_;
        }

        auto policy_ = possible_policy_.value();

        if(interval.lower >= policy_.announcement_date) {
            if(last_announced_ < policy_.announcement_date) {
                last_announced_ = policy_.announcement_date;

                for(const auto &s : unique_shareholders()) {
                    this->template create_message<
                        finance::dividend_announcement_message>(
                        s, interval.lower, this->identifier, s, policy_);
                }
            }
        } else {
            next_event_ = std::min<simulation::time_point>(
                policy_.announcement_date, next_event_);
        }

        if(interval.lower >= policy_.payable_date) {
            if(last_payment_ < policy_.announcement_date) {
                last_payment_ = policy_.announcement_date;

                // TODO: make payment
                /*
                   double dps_ = 0.01;
                   double variance_ = 0.01;

                   auto precision_ = currencies::USD.denominator;

                   std::normal_distribution<double> distribution_( dps_ *
                   total_shares() * precision_ , variance_ * total_shares() *
                   precision_ );

                   auto unappropriated_profit_ =
                   cash(currencies::USD).value(distribution_(generator_));

                   auto dividends_ =
                   this->compute_dividend_per_share(unappropriated_profit_);
                   for(const auto &[holder_, ownership_] : shareholders){
                       identity<owner<cash>> ic =
                   dynamic_identity_cast<owner<cash>>(holder_);
                       //this->template create_message<transfer<cash>>(  ic,
                   unappropriated_profit_); // this fails, because the
                   constructor is called with identity<agent> auto result_ =
                   std::make_shared<transfer<cash>> ( *this , ic ,
                   inventory<cash>( cash(currencies::USD) ,
                   quantity(unappropriated_profit_.value,
                   cash(currencies::USD).denomination.denominator))
                                                );
                       result_->recipient  = ic;
                       result_->sender     = identifier;
                       result_->sent       = time.lower;
                       result_->received   = time.lower;
                       this->outbox().push_back(result_);
                   }*/
            }
        } else {
            next_event_ = std::min<simulation::time_point>(
                policy_.announcement_date, next_event_);
        }
        return next_event_;
    }

}