/**
 * @file loan.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_LOAN_HPP
#define ESL_LOAN_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>

#include <esl/agent.hpp>
#include <esl/law/contract.hpp>


namespace esl::economics::finance {

    ///
    ///
    ///
    struct loan
    : esl::law::contract
    {
        [[nodiscard]] const esl::identity<esl::agent> &lender() const
        {
            return parties[0];
        }

        [[nodiscard]] const esl::identity<esl::agent> &borrower() const
        {
            return parties[1];
        }

        explicit loan( esl::identity<esl::agent> lender
                     , esl::identity<esl::agent> borrower
                     )

        : esl::law::contract({lender, borrower})
        {

        }

        virtual ~loan() = default;

        std::string name() const override
        {
            return "loan";
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &boost::serialization::make_nvp("contract"
                , boost::serialization::base_object<contract>(*this));

        }
    };

}  // namespace esl::economics::finance

///
/// \brief  Hash definition for loan
///
namespace std {
    template<>
    struct hash<esl::economics::finance::loan>
    {
        std::size_t operator()(const esl::economics::finance::loan &c) const
        {
            return std::hash<esl::entity<esl::law::property>>()(c);
        }
    };
}  // namespace std


#endif  // ESL_LOAN_HPP
