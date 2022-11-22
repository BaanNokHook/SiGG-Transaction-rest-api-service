/**
 * @file debtor.hpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef ME_DEBTOR_HPP
#define ME_DEBTOR_HPP

#include <esl/law/legal_person.hpp>


namespace esl::economics::finance {

    class debtor
    : virtual public law::legal_person
    {
    public:

        debtor(identity<law::legal_person> i, law::jurisdiction primary_jurisdiction)
        :   law::legal_person(i, primary_jurisdiction)
        {

        }

        virtual ~debtor() = default;

    };

}

#endif  // ME_DEBTOR_HPP
