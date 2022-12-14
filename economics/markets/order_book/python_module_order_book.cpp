/**
 * @file python_module_order_book.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifdef WITH_PYTHON

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/python.hpp>
using namespace boost::python;

#include <esl/economics/markets/order_book/basic_book.hpp>
#include <esl/economics/markets/order_book/binary_tree_order_book.hpp>
#include <esl/economics/markets/order_book/static_order_book.hpp>
#include <esl/economics/markets/order_book/matching_engine.hpp>
#include <esl/economics/markets/order_book/python_module_order_book.hpp>
using namespace esl::economics::markets::order_book;

BOOST_PYTHON_MODULE(_order_book)
{
   enum_<execution_report::state_t>("state_t")
       .value("invalid", execution_report::state_t::invalid)
       .value("cancel", execution_report::state_t::cancel)
       .value("match", execution_report::state_t::match)
       .value("placement", execution_report::state_t::placement)
       ;

   class_<execution_report>("execution_report")
       .def_readwrite("quantity", &execution_report::quantity)
       .def_readwrite("identifier", &execution_report::identifier)
       .def_readwrite("side", &execution_report::side)
       .def_readwrite("limit", &execution_report::limit)
       .def_readwrite("owner", &execution_report::owner)
       .def("__repr__", &execution_report::representation)
       .def("__str__", &execution_report::representation)
       ;


   ///
   /// \brief Export the abstract base class, so that python users too can
   ///        implement new order books.
   ///
   class_<basic_book, boost::noncopyable>("basic_book", no_init)
       .def_readwrite("reports", &basic_book::reports)
       .def("ask", &basic_book::ask)
       .def("bid", &basic_book::bid)
       .def("insert", &basic_book::insert)
       .def("cancel", &basic_book::cancel)
       .def("display", &basic_book::display)
       ;


   ///
   /// \brief Export the abstract base class, so that python users too can
   ///        implement new order books.
   ///
   class_<basic_book, boost::noncopyable>("basic_book", no_init)
       .def_readwrite("reports", &basic_book::reports)
       .def("ask", &basic_book::ask)
       .def("bid", &basic_book::bid)
       .def("insert", &basic_book::insert)
       .def("cancel", &basic_book::cancel)
       .def("display", &basic_book::display)
       ;

   class_<static_order_book, bases<basic_book>>("static_order_book", init<esl::economics::markets::quote, esl::economics::markets::quote, size_t>())
       .def_readwrite("reports", &basic_book::reports)
       .def("ask", &basic_book::ask)
       .def("bid", &basic_book::bid)
       .def("insert", &basic_book::insert)
       .def("cancel", &basic_book::cancel)
       .def("display", &basic_book::display)
       ;

   class_<binary_tree_order_book, bases<basic_book>>("binary_tree_order_book", init<>())
       .def_readwrite("reports", &basic_book::reports)
       .def("ask", &basic_book::ask)
       .def("bid", &basic_book::bid)
       .def("insert", &basic_book::insert)
       .def("cancel", &basic_book::cancel)
       .def("display", &basic_book::display)
       ;

   class_<matching_engine>("matching_engine", init<>())
       .def_readwrite("books", &matching_engine::books)
       .def("insert", &basic_book::insert)
       .def("cancel", &basic_book::cancel)
       ;
}

#endif