/**
 * @file asset.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_ECONOMICS_ASSET_HPP
#define ESL_ECONOMICS_ASSET_HPP

//#include <boost/serialization/serialization.hpp>

#include <esl/quantity.hpp>
#include <esl/economics/price.hpp>
#include <esl/law/property.hpp>


namespace esl {
    template<typename entity_t_>
    struct identity;
}

namespace esl::economics {

    namespace accounting {
        struct standard;
    }

    ///
    /// \brief  A property that generates value for the holder.
    ///
    /// \detail An asset is a property that can generate value, and through
    ///         analysis of the value generating process it can be valued.
    ///         Because agents are able to value it, trading or lending against
    ///         money is possible. This class mixes in fungibility, since only
    ///         fungible assets can be valued together (sum)
    ///
    struct asset
    : virtual law::property
    {
        ///
        /// \brief
        ///
        explicit asset(esl::identity<law::property> i = esl::identity<law::property>());

        virtual ~asset() = default;

        ///
        /// \brief
        ///
        [[nodiscard]] std::string name() const override;


        ///
        /// \param a    Valuation method and accounting rules
        /// \return
        //[[nodiscard]] virtual price value(const accounting::standard &a, const quantity &amount) const;




        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &BOOST_SERIALIZATION_BASE_OBJECT_NVP(law::property);
        }
    };




}  // namespace esl::economics

#endif  // ESL_ECONOMICS_ASSET_HPP
