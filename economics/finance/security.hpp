/**
 * @file security.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_SECURITY_HPP
#define ESL_SECURITY_HPP


#include <esl/economics/asset.hpp>
#include <esl/economics/finance/isin.hpp>
#include <esl/economics/fungibility.hpp>

#include <esl/geography/countries.hpp>

#include <esl/law/contract.hpp>


namespace esl::economics::finance {

    ///
    /// \brief
    ///
    /// \note   necessarily fungible
    ///
    struct security
    : public asset
    , public virtual fungible
    , public law::contract
    {
        explicit security( identity<property> i = identity<property>()
                         , std::vector<identity<agent>> parties = {})
        : asset(i)
        , contract(parties)
        {
            
        }

        virtual ~security() = default;

        std::string name() const override
        {
            std::stringstream stream_;
            stream_ << "security" << ' ' << this->identifier;
            return stream_.str();
        }

        ///
        /// \tparam archive_t
        /// \param archive
        /// \param version
        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(asset);
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(fungible);
            archive &BOOST_SERIALIZATION_NVP(code);
        }
    };
}  // namespace esl::economics::finance

#endif  // ESL_SECURITY_HPP
