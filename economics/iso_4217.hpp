/**
 * @file iso_4217.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_ISO_4217_HPP
#define ESL_ISO_4217_HPP

#include <array>
#include <cassert>
#include <ostream>
#include <string>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>

#include <esl/exception.hpp>


namespace esl::economics {

    ///
    /// \brief ISO 4217 Currency Code
    ///
    struct iso_4217
    {
        ///
        /// The currency code as represented by 3 characters.
        ///
        std::array<char, 3> code;

        ///
        /// \brief  The number of subunits of the currency, e.g. when a currency
        ///         has cents as the smallest unit, denominator is set to 100.
        ///
        std::uint64_t denominator;

        ///
        ///
        ///
        /// \param operand
        constexpr iso_4217(const iso_4217 &operand)
        : iso_4217(operand.code, operand.denominator)
        {

        }

        ///
        /// \brief construct ISO 4217 code from code and denominator
        ///
        /// \param isocode
        /// \param denominator
        constexpr iso_4217(const std::array<char, 3> &isocode = {'X', 'X', 'X'},
                                    std::uint64_t denominator   = 100)
        : code(isocode), denominator(denominator)
        {
            for(auto c:isocode){
                if(!('A' <= c && 'Z' >= c)){
                    throw esl::exception(std::string("unexpected symbol ") + c + " in code");
                }
            }
            if(0 >= denominator){
                throw esl::exception("denominator must be strictly positive");
            }
        }

        ~iso_4217() = default;

        iso_4217 &operator = (const iso_4217 &operand)
        {
            for(size_t i = 0; i < code.size(); ++i) {
                code[i] = operand.code[i];
            }
            denominator = operand.denominator;
            return *this;
        }

        [[nodiscard]] constexpr bool operator == (const iso_4217 &operand) const
        {
            return code[0] == operand.code[0] && code[1] == operand.code[1]
                   && code[2] == operand.code[2]
                   && denominator == operand.denominator;
        }

        [[nodiscard]] constexpr bool operator != (const iso_4217 &operand) const
        {
            return code[0] != operand.code[0] || code[1] != operand.code[1]
                   || code[2] != operand.code[2]
                   || denominator != operand.denominator;
        }


        [[nodiscard]] constexpr bool operator < (const iso_4217 &operand) const
        {
            for(size_t i = 0; i < code.size(); ++i) {
                if(code[i] < operand.code[i]) {
                    return true;
                }
                if(code[i] > operand.code[i]) {
                    return false;
                }
            }

            return false;
        }

        [[nodiscard]] explicit operator std::string() const
        {
            return std::string(code.data(), code.size());
        }

        [[nodiscard]] std::string format(std::uint64_t quantity) const
        {
            return std::string(code.data(), code.size()) + ' '
                   + std::to_string(quantity) + '/'
                   + std::to_string(denominator);
        }

        template<typename archive_t>
        void save(archive_t &archive, const unsigned int version) const
        {
            (void) version;
            std::string code_;
            for(char c: code) {
                code_.push_back(c);
            }

            archive << boost::serialization::make_nvp("code", code_);
            archive << BOOST_SERIALIZATION_NVP(denominator);
        }

        template<typename archive_t>
        void load(archive_t &archive, const unsigned int version)
        {
            (void) version;
            std::string code_;

            archive >> boost::serialization::make_nvp("code", code_);
            assert(3 == code_.length());

            for(size_t i = 0; i < code.size(); ++i){
                code[i] = code_[i];
            }

            archive >> BOOST_SERIALIZATION_NVP(denominator);
        }

        template<class archive_t>
        void serialize(archive_t &archive,const unsigned int file_version){
            boost::serialization::split_member(archive, *this, file_version);
        }

        friend std::ostream &operator << (std::ostream &o, const iso_4217 &c)
        {
            o.write(c.code.data(), c.code.size());
            return o;
        }
    };

}  // namespace esl::economics

namespace std {
    template<>
    struct hash<esl::economics::iso_4217>
    {
        constexpr size_t operator()(const esl::economics::iso_4217 &c) const
        {
            return             size_t(c.code[0]) - size_t('A')
                        + 26 * size_t(c.code[1]) - size_t('A')
                   + 26 * 26 * size_t(c.code[2]) - size_t('A');
        }
    };
}  // namespace std

#ifdef WITH_MPI

#include <boost/mpi.hpp>
namespace boost ::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::iso_4217>
    : public mpl::false_
    {};
}  // namespace boost::mpi
#endif  // WITH_MPI

#endif  //ESL_ISO_4217_HPP
