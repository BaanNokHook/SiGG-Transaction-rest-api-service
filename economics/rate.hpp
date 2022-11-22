/**
 * @file rate.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_RATE_HPP
#define ESL_RATE_HPP

#include <esl/economics/price.hpp>
#include <esl/mathematics/rational.hpp>
#include <esl/simulation/time.hpp>

#include <type_traits>


namespace esl::economics {

    ///
    /// \brief  Abstract base class for rates, used to add extension functions
    template<typename integer_type_ = int64_t>
    struct rate
    : public boost::rational<integer_type_>
    {
        constexpr rate(boost::rational<integer_type_> r)
        : boost::rational<integer_type_>(r)
        {

        }

        constexpr rate(integer_type_ numerator, integer_type_ denominator)
        : boost::rational<integer_type_>(numerator, (assert(denominator > 0), denominator))
        {

        }

        constexpr rate(const rate<integer_type_> &r)
        : boost::rational<integer_type_>(r)
        {

        }

        ///
        /// \brief Rate from double, truncates to zero.
        /// 
        /// \param  value_untruncated   The rate as a floating point number.
        /// \param  precision   The number of sub-units of the rate, in essence the 
        ///                     denominator in the fractional number.
        ///
        constexpr rate( double value_untruncated
                      , typename std::make_unsigned<integer_type_>::type precision = 10'000)
        : rate( static_cast<integer_type_>(value_untruncated*precision)
              , static_cast<integer_type_>(precision))
        {

        }

        virtual ~rate() = default;

        //rate<integer_type_> &operator=(const rate<integer_type_> &o)
        //{
        //    boost::rational<integer_type_>::operator=(o);
        //    return *this;
        //}


        //bool operator==(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator==(o);
        //}

        //bool operator!=(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator!=(o);
        //}

        //bool operator<(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator<(o);
        //}

        //bool operator>(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator>(o);
        //}

        //bool operator<=(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator<=(o);
        //}

        //bool operator>=(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator>=(o);
        //}

        //rate<integer_type_> operator+(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator+(o);
        //}

        //rate<integer_type_> operator-(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator-(o);
        //}
        //
        //rate<integer_type_> operator*(const rate<integer_type_> &o) const
        //{
        //    return boost::rational<integer_type_>::operator*(o);
        //}

        //rate<integer_type_> operator / (const rate<integer_type_> &o) const
        //{
        //    return rate<integer_type_>
        //        (boost::rational<integer_type_>::operator/(
        //        (const boost::rational<integer_type_> &)o));
        //}

        template<typename floating_point_t_>
        [[nodiscard]] explicit operator floating_point_t_() const
        {
            return boost::rational_cast<floating_point_t_>(*this);
        }

        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &boost::serialization::make_nvp(
                "rational_integer_type__",
                boost::serialization::base_object<
                    boost::rational<integer_type_>>(*this));
        }
    };
}  // namespace esl::economics


#ifdef WITH_MPI
namespace boost::mpi {
    template<typename integer_type_>
    struct is_mpi_datatype<esl::economics::rate<integer_type_>>
    : public mpl::true_
    {

    };
}  // namespace boost::mpi
#endif  // WITH_MPI


#endif  // ESL_RATE_HPP
