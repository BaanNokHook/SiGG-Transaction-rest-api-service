/**
 * @file price.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/price.hpp>


/*
#ifdef WITH_PYTHON
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(price)
{
    class_<esl::economics::price>("price",
        init<std::int64_t, esl::economics::iso_4217>())
        .def_readwrite("value", &esl::economics::price::value)
        .def_readonly("valuation", &esl::economics::price::valuation)

        .def(self == self)
        .def(self != self)
        .def(self <  self)
        .def(self <= self)
        .def(self >  self)
        .def(self >= self)

        .def(self +  self)
        .def(self += self)
        .def(self -  self)
        .def(self -= self)
        ;
}

#endif  // WITH_PYTHON
*/

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(esl::economics::price);


