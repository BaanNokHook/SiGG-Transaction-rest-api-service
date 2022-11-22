/**
 * @file stock.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_STOCK_HPP
#define ESL_STOCK_HPP


#include <memory>

#include <esl/economics/finance/security.hpp>
#include <esl/economics/finance/share_class.hpp>

namespace esl::economics {
    struct company;
}

namespace esl::economics::finance {
    struct stock
    : public virtual security
    {
        ///
        /// \brief  The company that issued the shares
        ///
        identity<company> company_identifier;

        ///
        /// \brief The description of the share
        ///
        share_class details;

        ///
        ///
        ///
        stock();

        ///
        /// \brief
        ///         This modifies the issuing company, as it needs to create a new
        ///         child property.
        ///
        stock(company &issuer, const share_class &details);

        ///
        /// \brief  Construct a stock from the issuer and share_class
        ///
        stock(const identity<property> &pi,
              const identity<company> &company_identifier,
              const share_class &details);

        //price value(const accounting::standard &a,
        //            const quantity &amount) const override;


        virtual ~stock() = default;

        /*C++20 constexpr*/ std::string name() const override
        {
            std::stringstream stream_;
            stream_ << "stock" << ' ' << this->identifier;
            return stream_.str();
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(security);
            archive &BOOST_SERIALIZATION_NVP(company_identifier);
            archive &BOOST_SERIALIZATION_NVP(details);
        }
    };

}

#endif//ESL_STOCK_HPP
