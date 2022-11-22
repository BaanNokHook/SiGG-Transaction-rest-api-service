/**
 * @file asset.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <esl/economics/asset.hpp>
#include <esl/economics/accounting/standard.hpp>
#include <esl/simulation/identity.hpp>

namespace esl::economics {

    asset::asset(identity<property> i)
    : property(i)
    {

    }

    std::string asset::name() const
    {
        return "asset";
    }

    ///
    /// \param a    Valuation method and accounting rules
    /// \return
    //[[nodiscard]] price asset::value(const accounting::standard &a, const quantity &amount) const
    //{
    //    return price(0ll, a.reporting_currency);
    //}
}

/*
#ifdef WITH_PYTHON
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(asset)
{
    class_<esl::economics::asset, bases<esl::law::property>>(
        "asset", init<esl::identity<esl::economics::asset>>())
        .def("name", &esl::economics::asset::name)
        .def("value", &esl::economics::asset::value)
        ;

}

#endif  // WITH_PYTHON
*/