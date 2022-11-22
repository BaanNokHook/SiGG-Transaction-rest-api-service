/**
 * @file bondholder.hpp
 * 
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_BONDHOLDER_HPP
#define ESL_BONDHOLDER_HPP

#include <map>
#include <tuple>
#include <unordered_map>

//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/serialization.hpp>

#include <esl/economics/owner.hpp>
#include <esl/economics/cash.hpp>
#include <esl/economics/finance/bond.hpp>



namespace esl::economics {
    struct company;
}


namespace esl::economics::finance {
    ///
    /// \brief  An interface that adds bondholder functionality to agents.
    ///
    /// \note   A shareholder automatically filters transfers for cash and stock
    ///         and therefore inherits law::owner<cash> and law::owner<stock>
    ///
    struct bondholder
    : public virtual law::owner<cash>
    , public virtual law::owner<bond>
    , public identifiable_as<bondholder>
    {
    public:
        bondholder();

    public:



        ///
        /// \brief  The valuation of the stocks
        ///
        esl::law::property_map<price> bond_prices;

        esl::law::property_map<nominal_interest_rate> yields;


        explicit bondholder(const identity<bondholder> &i);

        virtual ~bondholder() = default;

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
        }
    };
}  // namespace esl::economics::finance

#endif  // ESL_BONDHOLDER_HPP
