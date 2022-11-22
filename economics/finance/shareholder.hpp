/**
 * @file shareholder.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_SHAREHOLDER_HPP
#define ESL_SHAREHOLDER_HPP

#include <map>
#include <tuple>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>

#include <esl/economics/owner.hpp>
#include <esl/economics/cash.hpp>
#include <esl/economics/finance/stock.hpp>



namespace esl::economics {
    struct company;
}


namespace esl::economics::finance {

    ///
    /// \brief  An interface that adds shareholder functionality to agents.
    ///
    /// \note   A shareholder automatically filters transfers for cash and stock
    ///         and therefore inherits law::owner<cash> and law::owner<stock>
    ///
    struct shareholder
    : public virtual law::owner<cash>
    , public virtual law::owner<stock>
    , public identifiable_as<shareholder>
    {
    public:
        shareholder();

    public:
        ///
        /// A datastructure relating the shares of a company to stocks
        ///
        std::map<std::tuple<identity<company>, share_class>, identity<law::property>>
            stocks;

        ///
        /// \brief  The valuation of the stocks
        ///
        esl::law::property_map<price> prices;


        ///
        /// \brief Datastructure to map share holdings to the issuing company
        ///
        typedef std::map<identity<company>,
                                   std::map<share_class, std::uint64_t>>
            share_holdings;

        share_holdings shares;

        ///
        /// \return
        std::map<identity<law::property>, quantity> stock_holdings() const;

        ///
        /// TODO: other mapping, perhaps including identity<property>?
        ///
        std::set<std::tuple<simulation::time_point, identity<company>>>
            ex_dividend_dates;

        explicit shareholder(const identity<shareholder> &i);

        virtual ~shareholder() = default;

        simulation::time_point
        submit_dividend_record(simulation::time_interval interval);

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &BOOST_SERIALIZATION_NVP(shares);
            archive &BOOST_SERIALIZATION_NVP(ex_dividend_dates);
        }
    };
}  // namespace esl::economics::finance

#endif  // ESL_SHAREHOLDER_HPP
