/**
 * @file exchange_rate.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_EXCHANGE_RATE_HPP
#define ESL_EXCHANGE_RATE_HPP

#include <cstdint>

#include <esl/economics/rate.hpp>

namespace esl::economics {
    ///
    /// \brief
    ///
    /// \note
    ///
    struct exchange_rate
    : public rate<std::uint64_t>
    {
        ///
        /// \param quote
        /// \param base
        constexpr exchange_rate( std::uint64_t quote = 1
                               , std::uint64_t base  = 1
                               )
        : rate<std::uint64_t>(quote, base)
        {
            assert(quote > 0);
            assert(base > 0);
        }

                /// \param base
        constexpr exchange_rate(const rate<std::uint64_t> &r)
        : rate<std::uint64_t>(r)
        {
            //assert(r.numerator   > 0);
           // assert(r.denominator > 0);
        }

        ///
        /// \param r
        constexpr exchange_rate(const exchange_rate &r)
        : exchange_rate(r.numerator(), r.denominator())
        {

        }


        ///
        /// \brief  Constructs an exchange rate similar to the provided exchange
        ///         rate, meaning with the same precision.
        ///
        /// \param r
        constexpr exchange_rate(double f, const exchange_rate &similar)
        : exchange_rate(std::uint64_t( f * similar.denominator()), similar.denominator())
        {

        }

        ///
        /// \param o
        /// \return
        //exchange_rate &operator = (const exchange_rate &o)
        //{
        //    rate<std::uint64_t>::operator=(o);
        //    return *this;
        //}
        
        //bool operator==(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator==(o);
        //}

        //bool operator!=(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator!=(o);
        //}
        //
        //bool operator<(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator<(o);
        //}

        //bool operator>(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator>(o);
        //}

        //bool operator<=(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator<=(o);
        //}

        //bool operator>=(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator>=(o);
        //}

        //exchange_rate operator+(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator+(o);
        //}

        //exchange_rate operator-(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator-(o);
        //}

        //exchange_rate operator*(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator*(o);
        //}

        //exchange_rate operator/(const exchange_rate &o) const
        //{
        //    return rate<std::uint64_t>::operator/(o);
        //}


        ///
        /// \param p
        /// \return
        constexpr price operator * (const price &p) const
        {
            return price(static_cast<int64_t>((p.value * numerator()) / denominator()), p.valuation);
        }



        ///
        /// \tparam archive_t
        /// \param archive
        /// \param version
        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;
            archive &boost::serialization::make_nvp(
                "rate_std::uint64_t_",
                boost::serialization::base_object<rate<>>(*this));
        }
    };
}


#ifdef WITH_MPI
namespace boost {
    namespace mpi {
        template<>
        struct is_mpi_datatype<esl::economics::exchange_rate>
        : public mpl::true_
        {};
    }
}
#endif//WITH_MPI





#endif//ESL_EXCHANGE_RATE_HPP