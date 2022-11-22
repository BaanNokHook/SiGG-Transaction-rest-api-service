/**
 * @file balance_sheet.hpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ME_BALANCE_SHEET_HPP
#define ME_BALANCE_SHEET_HPP

#include <esl/economics/accounting/standard.hpp>
#include <esl/economics/owner.hpp>


namespace esl::economics::accounting {
    class balance_sheet
    {
    public:

        explicit balance_sheet(const law::owner<law::property> &)
        {

        }



        price assets(const esl::economics::accounting::standard &s) const
        {
            price result_ = price(int64_t(0), s.reporting_currency);
            /*for(const auto &[property_, q]:  esl::law::owner<esl::law::property>::inventory){
                /// TODO: perhaps use compile time type information to filter assets
                (void) q;
                std::shared_ptr<asset> asset_ = std::dynamic_pointer_cast<asset>(property_);
                if(asset_){
                    result_ += asset_->value(s);
                }
            }*/
            return result_;
        }
    };

}


#endif //ME_BALANCE_SHEET_HPP
