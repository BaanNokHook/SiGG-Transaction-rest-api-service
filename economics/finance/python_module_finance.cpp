/**
 * @file python_module_finance.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/finance/python_module_finance.hpp>
    #include <esl/economics/finance/isin.hpp>
    #include <esl/economics/finance/share_class.hpp>


#ifdef WITH_PYTHON

#include <utility>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using boost::python::init;
using boost::python::no_init;
using boost::python::object;
using boost::python::enum_;
using boost::python::class_;
using boost::python::dict;
using boost::python::list;
using boost::python::len;
using boost::python::self;
using boost::python::make_tuple;
using boost::python::extract;
using boost::python::wrapper;
using boost::python::vector_indexing_suite;

std::string get_isin_code(const esl::economics::finance::isin &i)
{
   return std::string(i.code.data(), i.code.data() + i.code.size());
}


void set_isin_code(esl::economics::finance::isin &i, const std::string &code)
{
   i.code = esl::to_array<0,9,char>(code);
}

BOOST_PYTHON_MODULE(_finance)
{
   class_<esl::economics::finance::isin>("isin", init<esl::geography::iso_3166_1_alpha_2, std::string>())
       .add_property("issuer", &esl::economics::finance::isin::issuer)
       .add_property("code", &get_isin_code, &set_isin_code)
       .def("__repr__", &esl::economics::finance::isin::representation)
       .def("__str__", &esl::economics::finance::isin::representation)
       ;



   class_<esl::economics::finance::share_class>("share_class", init<std::uint8_t, std::uint8_t, float, bool, bool, bool>())
       .add_property("rank", &esl::economics::finance::share_class::rank)
       .add_property("votes", &esl::economics::finance::share_class::votes)
       .add_property("preference", &esl::economics::finance::share_class::preference)
       .add_property("dividend", &esl::economics::finance::share_class::dividend)
       .add_property("cumulative", &esl::economics::finance::share_class::cumulative)
       .add_property("redeemable", &esl::economics::finance::share_class::redeemable)
       .def(self == self)
       .def(self < self)
       ;

}

#endif