/**
 * @file securities_lending_contract.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef ME_SECURITIES_LENDING_CONTRACT_HPP
#define ME_SECURITIES_LENDING_CONTRACT_HPP

#include <esl/economics/finance/loan.hpp>
#include <esl/quantity.hpp>


namespace esl::economics::finance {

     inline identity<law::property> prepend(identity<law::property>::digit_t v, identity<law::property> p)
    {
        std::vector<identity<law::property>::digit_t> result_ = {v};
        for(auto d: p.digits){
            result_.emplace_back(d);
        }
        return identity<law::property>(result_);
    }


    class securities_lending_contract
    : public  esl::law::contract
    {
    public:
        //std::map<identity<property>, quantity> basket;

        identity<property> security;
        quantity size;

        securities_lending_contract( identity<agent> lender
                                   , identity<agent> borrower
                                   , identity<property> security
                                   , quantity size)
        : property(prepend(typeid(securities_lending_contract).hash_code(), security))
        //, loan(lender, borrower)
        , contract({lender, borrower})
        , security(security)
        , size(size)
        {

        }

        virtual ~securities_lending_contract() = default;


        [[nodiscard]] std::string name() const override
        {
            std::stringstream stream_;
            stream_ << "securities lending contract " << identifier;
            return stream_.str();
        }
    };

}//namespace esl::economics::finance

#endif  // ME_SECURITIES_LENDING_CONTRACT_HPP
