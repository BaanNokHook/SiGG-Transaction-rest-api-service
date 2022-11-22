/**
 * @file cash.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_CASH_HPP
#define ESL_CASH_HPP

#include <string>
#include <sstream>

#include <esl/economics/money.hpp>
#include <esl/economics/tangibility.hpp>


namespace esl::economics {
    ///
    /// \brief  (Financial) cash, that for example can be exchanged
    /// electronically. For tangible (physical) money, such as notes and coins,
    /// see physical_money
    ///
    struct cash
    : public money
    , public intangible
    {
    private:
        static identity<law::property>
        create_identifier(const iso_4217 &denomination)
        {
            return identity<law::property>(
                    {typeid(cash).hash_code(),
                     std::hash<iso_4217>()(denomination)});
        }

    public:
        explicit cash(iso_4217 denomination)
                : law::property( create_identifier(denomination))
                , money(denomination,  create_identifier(denomination))
        {

        }

        virtual ~cash() = default;

        virtual std::string name() const  // C++20 constexpr
        {
            std::stringstream stream_;
            stream_ << denomination << " cash";
            return stream_.str();
        }

        bool operator == (const cash &c) const
        {
            return this->denomination == c.denomination;
        }

    };
}  // namespace esl::economics


namespace std {
    template<>
    struct hash<esl::economics::cash>
    {
        std::size_t operator()(const esl::economics::cash &c) const
        {
            return std::hash<esl::economics::iso_4217>()(
                c.denomination);
        }
    };
}  // namespace std

#endif  // ESL_CASH_HPP
