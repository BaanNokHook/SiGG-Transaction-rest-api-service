/**
 * @file loan.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <esl/economics/finance/loan.hpp>
using namespace esl::economics::finance;

/*
#ifdef WITH_PYTHON
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(loan)
{
    class_<loan, bases<esl::law::contract>>
        ( "loan", init<esl::identity<esl::agent>, esl::identity<esl::agent>>())
        .add_property("lender"
            , make_function( &loan::lender
            , return_value_policy<copy_const_reference>())
            )
        .add_property("borrower"
            , make_function(&loan::borrower
            , return_value_policy<copy_const_reference>())
            )
        ;
}

#endif  // WITH_PYTHON
*/