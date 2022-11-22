/**
 * @file iso_4217.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/iso_4217.hpp>


/*
#ifdef WITH_PYTHON
#include <boost/python.hpp>

#include <string>

std::string python_currency_code(const esl::economics::iso_4217 &c)
{
    return ((std::string() + c.code[0]) + c.code[1]) + c.code[1];
}


using namespace boost::python;
BOOST_PYTHON_MODULE(currency)
{
    class_<esl::economics::iso_4217>("iso_4217")
        .add_property("code", python_currency_code)
        ;
}
#endif
 */
