/**
 * @file isin.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/finance/isin.hpp>


/*
#ifdef WITH_PYTHON
#include <boost/python.hpp>

using namespace boost::python;


BOOST_PYTHON_MODULE(isin)
{
    class_<esl::economics::finance::isin>(
        "isin",init<std::string>())
        .def_readonly("issuer", &esl::economics::finance::isin::issuer)
        .def_readonly("code", &esl::economics::finance::isin::code)
        .def("checksum", &esl::economics::finance::isin::checksum)
        ;
}

#endif  // WITH_PYTHON
*/