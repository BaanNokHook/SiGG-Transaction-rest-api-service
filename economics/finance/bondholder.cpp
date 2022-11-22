/**
 * @file bondholder.cpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/finance/bondholder.hpp>

#include <esl/economics/finance/bond.hpp>
#include <esl/simulation/identity.hpp>

#include <esl/economics/markets/walras/quote_message.hpp>

namespace esl::economics::finance {

    bondholder::bondholder()
        : bondholder(identity<bondholder>())
    {}

    bondholder::bondholder(const identity<bondholder> &i)
        : agent(i), owner<cash>(i), owner<bond>(i)
    {
         
        auto process_quotes_ =
            [this](std::shared_ptr<markets::walras::quote_message> m,
                   simulation::time_interval step, std::seed_seq &seed) {
                (void) seed;
                for(auto &[k, v] : m->proposed){
                    assert(std::holds_alternative<price>(v.type));
                    auto p = std::make_pair(k, std::get<price>(v.type));
                    this->bond_prices.insert(std::move(p));
                }
                return step.upper;
            };

        ESL_REGISTER_CALLBACK(markets::walras::quote_message, 0, process_quotes_, "extract bond prices from Walrasian market");
    } 


}