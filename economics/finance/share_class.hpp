/**
 * @file share_class.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_SHARE_HPP
#define ESL_SHARE_HPP

#include <cstdint>

#include <boost/functional/hash.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>


namespace esl::economics::finance {

    ///
    /// \brief  The details of a certificate of (part-) ownership of a company
    ///
    struct share_class
    {
        friend class boost::serialization::access;

        ///
        /// \brief
        ///
        /*const */std::uint8_t rank;

        ///
        /// \brief  The number of votes per share, which can be zero.
        ///         Alternatively, some companies operate by assigning one vote
        ///         per individual shareholder that meets are certain threshold.
        ///
        /*const */uint8_t votes;

        ///
        /// \brief  If a share has non-zero dividend preference, the holder
        ///         receives a percentage before of dividends before other
        ///         shares are allocated a dividend payment
        ///
        /*const */ /*dividend*/ float preference;

        ///
        /// \brief  Whether the share is eligible for dividend
        ///
        /*const */ bool dividend;

        ///
        /// \brief
        ///
        /*const */bool cumulative;

        ///
        ///
        ///
        /*const */bool redeemable;


        //    bool wind_up;


        constexpr explicit share_class( std::uint8_t rank = 0
                                      , uint8_t votes     = 1
                                      , float preference  = 0.0
                                      , bool dividend     = true
                                      , bool cumulative   = false
                                      , bool redeemable   = false
                                      )
        : rank(rank)
        , votes(votes)
        , preference(preference)
        , dividend(dividend)
        , cumulative(cumulative)
        , redeemable(redeemable)
        {

        }

        share_class &operator = (const share_class &) = default;

        constexpr bool operator == (const share_class &s) const
        {
            return rank == s.rank
                && votes == s.votes
                && dividend == s.dividend
                && preference == s.preference
                && cumulative == s.cumulative
                && redeemable == s.redeemable;
        }

        constexpr bool operator < (const share_class &s) const
        {
            return rank < s.rank;
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {

            (void)version;
            archive & BOOST_SERIALIZATION_NVP(rank);
            archive & BOOST_SERIALIZATION_NVP(votes);
            archive &BOOST_SERIALIZATION_NVP(preference);

            archive &BOOST_SERIALIZATION_NVP(dividend);
            archive &BOOST_SERIALIZATION_NVP(cumulative);
            archive &BOOST_SERIALIZATION_NVP(redeemable);
        }
    };
}

namespace std {
    template <>
    struct hash<esl::economics::finance::share_class>
    {
        size_t operator()(const esl::economics::finance::share_class & s) const
        {
            size_t result_ = 0;
            boost::hash_combine(result_,s.rank);
            boost::hash_combine(result_,s.votes);
            boost::hash_combine(result_,s.dividend);
            boost::hash_combine(result_,s.preference);
            boost::hash_combine(result_,s.cumulative);
            boost::hash_combine(result_,s.redeemable);
            return result_;
        }
    };
}

#endif//ESL_SHARE_HPP
