/**
 * @file inventory.hpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_INVENTORY_HPP
#define ESL_INVENTORY_HPP

#include <initializer_list>

#include <boost/core/demangle.hpp>

#include <esl/exception.hpp>
#include <esl/economics/accounting/standard.hpp>
#include <esl/economics/cash.hpp>
#include <esl/economics/currencies.hpp>
#include <esl/law/property.hpp>
#include <esl/quantity.hpp>
#include <esl/law/property_collection.hpp>


namespace esl::economics::accounting {


    struct insufficent_inventory
    : public esl::exception
    {
    public:
        const quantity before;

        const quantity withdrawal;

        const identity<law::property> identifier;

        const std::string property_name;

        //std::string message;

        ///
        /// \brief                  used to
        /// \param before
        /// \param withdrawal
        /// \param property_name    textual description of the property that is
        ///                         missing, used for message only
        insufficent_inventory( quantity before
                             , quantity withdrawal
                             , identity<law::property> identifier
                             , const std::string &property_name = "property"
                             )
        : esl::exception()
        , before(before)
        , withdrawal(withdrawal)
        , identifier(identifier)
        , property_name(property_name)
        {
            std::stringstream stream_;
            stream_ << "insufficient inventory (" << before << ") for withdrawal (" << withdrawal << ") of " << property_name << std::endl;
            message_ = stream_.str();
        }

        ///
        /// \return a human-readable message that describes the missing item and
        /// quantity
        [[nodiscard]] const char *what() const noexcept override
        {

            return message_.c_str();
        }
    };


    struct fractional_infungible
    : public std::exception
    {
    public:
        const quantity invalid;

        explicit fractional_infungible(quantity q) : invalid(q)
        {

        }

        const char *what() const throw()
        {
            return "attempt to divide infungible property";
        }
    };


    struct duplicate_infungible
    : public std::exception
    {
    public:
        const quantity invalid;

        explicit duplicate_infungible(quantity q)
        : invalid(q)
        {

        }

        const char *what() const throw()
        {
            return "attempt to duplicate infungible property";
        }
    };


    ///
    /// \brief  This container is used to map specific property types to the
    /// approrpriate datastructures. The underlying
    ///         datastructures can be changed later behind this static
    ///         interface, for example for performance reasons (example:
    ///         vector<> may be faster than unordered_set, to be confirmed in
    ///         testing.
    ///
    /// \tparam property_t_
    /// \tparam fungible_   whether or not the property is a fungible property.
    template<typename property_t_, bool fungible_>
    struct inventory_by_fungibility;


    ///
    /// \tparam property_t_
    template<typename property_t_>
    struct inventory_by_fungibility<property_t_, true>
    {
        law::property_filter_map<property_t_, quantity> items;

        inventory_by_fungibility()
        : items()
        {

        }

        inventory_by_fungibility(std::initializer_list<std::pair<const std::shared_ptr<property_t_>, quantity>> l)
        : items(l)
        {

        }

        inventory_by_fungibility(property_t_ item, quantity q)
        : items()
        {
            items.insert(make_pair(item, q));
        }


        ///
        /// \brief
        ///
        /// \param a
        /// \return
        price value(const accounting::standard &a)
        {
            auto result_ = economics::cash(a.reporting_currency).price(0);
            for(auto [k, v]: items) {
                auto unit_     = k->value(a);
                auto multiple_ = static_cast<int64_t>((unit_.value * v.amount) / v.basis);
                // auto q  = quantity(multiple_, unit_.valuation.denominator);
                auto p = price(multiple_, unit_.valuation);
                result_ += p;
            }
            return result_;
        }

        void insert(std::shared_ptr<property_t_> item, quantity q)
        {
            auto iterator_ = items.find(item);
            if(items.end() == iterator_) {
                items.insert(std::make_pair(item, q));
            } else {
                iterator_->second += q;
            }
        }

        void insert(const inventory_by_fungibility<property_t_, true> &added)
        {
            for(const auto &[k, v]: added.items) {
                insert(k, v);
            }
        }

        void erase(std::shared_ptr<property_t_> item, const quantity &q)
        {
            auto iterator_ = items.find(item);

            if(items.end() == iterator_ && q.amount > 0) {
                throw insufficent_inventory(quantity(0), q, item->identifier, boost::core::demangle(typeid(property_t_).name()));
            }

            if(iterator_->second < q) {
                throw insufficent_inventory(iterator_->second, q, item->identifier, boost::core::demangle(typeid(property_t_).name()));
            }

            iterator_->second -= q;
        }

        void erase(const inventory_by_fungibility<property_t_, true> &removed)
        {
            for(const auto &[k, v]: removed.items) {
                erase(k, v);
            }
        }


        void insert_into(law::property_map<quantity> &m) const
        {
            for(auto [k, v] : items) {
                auto i = m.find(k);
                if(m.end() == i) {
                    m.insert(std::make_pair(k, v));
                }else{
                    i->second += v;
                }
            }
        }


        void erase_from(law::property_map<quantity> &m) const
        {
            for(auto [k, v] : items) {
                if(v == 0){
                    continue;
                }
                auto i = m.find(k);
                if(m.end() == i) {
                    //LOG(errorlog) << "when looking for property " << boost::core::demangle(typeid(property_t_).name()) << " id: "<< k->identifier << " no entry was found" << std::endl;
                    throw insufficent_inventory(quantity(0), quantity(1), k->identifier, boost::core::demangle(typeid(property_t_).name()));
                } else if(i->second < v) {
                    //LOG(errorlog) << "when looking for property " << boost::core::demangle(typeid(property_t_).name()) << " id: "<< k->identifier << " there were insufficient ("<<i->second<<") items to withdraw " << v << std::endl;
                    throw insufficent_inventory(i->second, v, k->identifier, k->name());
                } else if(i->second == v) {
                    m.erase(k);
                } else {
                    i->second -= v;
                }
            }
        }

        friend std::ostream &
        operator<<(std::ostream &o, inventory_by_fungibility<property_t_, true> &i)
        {
            o << i.items;
            return o;
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive & BOOST_SERIALIZATION_NVP(items);
        }
    };

    ///
    /// \brief  An inventory of infungible (unique) property.
    ///
    /// \tparam property_t_
    template<typename property_t_>
    struct inventory_by_fungibility<property_t_, false>
    {
        law::property_filter_set<property_t_> items;

        inventory_by_fungibility() = default;


        inventory_by_fungibility(std::initializer_list<std::shared_ptr<property_t_>> l)
        : items(l)
        {

        }

        void insert(std::shared_ptr<property_t_> value)
        {
            items.insert(value);
        }

        ///
        /// \brief  Adds an overload to insert to insertentire collections of
        /// property \param values
        void insert(const law::property_set &values)
        {
            items.insert(values.begin(), values.end());
        }

        void erase(std::shared_ptr<property_t_> value)
        {
            items.erase(value);
        }

        ///
        /// \brief  Adds an overload to erase to insert entire collections of
        /// property \param values
        void erase(const law::property_set &values)
        {
            items.erase(values.begin(), values.end());
        }

        void insert_into(law::property_map<quantity> &m) const
        {
            for(auto k : items) {
                auto i = m.find(k);
                if(m.end() == i) {
                    m.insert({k, quantity(1)});
                } else {
                    throw duplicate_infungible(i->second + 1);
                }
            }
        }

        /*
        void erase_from(law::property_map<quantity> &m) const
        {
            for(auto k : items) {
                auto i = m.find(k);
                if(m.end() == i || i->second.amount == 0) {
                    throw insufficent_inventory(quantity(0), quantity(1), i->first->identifier);
                } else {
                    // if(i->second.amount > 1){
                    //    throw duplicate_infungible();
                    //}
                    m.erase(k);
                }
            }
        }
         */

        ///
        /// \return
        std::enable_if<std::is_base_of<asset, property_t_>::value, price>
        value()
        {
            auto default_currency = currencies::USD;  // TODO
            auto result_          = price(0, default_currency);

            for(const auto &element : items) {
                result_ += element;
            }

            return result_;
        }

        friend std::ostream &
        operator<<(std::ostream &o, inventory_by_fungibility<property_t_, false> &i)
        {
            o << "{ ";
            for(auto p : i.items) {
                o << p->name() << ", ";
            }
            o << "}";
            return o;
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive & BOOST_SERIALIZATION_NVP(items);
        }
    };

    template<typename property_t_>
    using inventory_filter = inventory_by_fungibility<
        property_t_, std::is_same<esl::law::property, property_t_>::value
                         || std::is_base_of<esl::economics::fungible, property_t_>::value>;


}  // namespace esl::economics::accounting






#ifdef WITH_MPI
#include <boost/mpi.hpp>
namespace boost::mpi {
    template<typename property_t_>
    struct is_mpi_datatype<esl::economics::accounting::inventory_filter<property_t_>>
        : public mpl::false_
    {};
}  // namespace boost::mpi
#endif  // WITH_MPI



#endif  // PROJECT_INVENTORY_HPP
