/**
 * @file inventory.cpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <boost/serialization/export.hpp>
#if BOOST_VERSION >= 106500
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>
#endif
#include <boost/serialization/shared_ptr.hpp>

#include <esl/economics/accounting/inventory.hpp>

//typedef esl::economics::accounting::inventory_by_fungibility<esl::law::property, true> inventory_by_fungibility_p;
//BOOST_CLASS_EXPORT(inventory_by_fungibility_p);

//BOOST_CLASS_EXPORT(esl::economics::accounting::inventory_filter<esl::law::property>)
