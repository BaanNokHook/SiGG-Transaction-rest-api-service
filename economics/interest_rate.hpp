/**
 * @file interest_rate.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_INTEREST_RATE_HPP
#define ESL_INTEREST_RATE_HPP

#include <esl/economics/rate.hpp>
#include <esl/mathematics/rational.hpp>

namespace esl::economics {
    ///
    ///
    ///
    struct interest_rate
    : public rate<>
    {
        esl::simulation::time_duration duration;

        ///
        /// \param rate_over_duration
        /// \param duration
#if BOOST_VERSION >= 106500
        //constexpr
#endif
            interest_rate(rational rate_over_duration = 0,
                                esl::simulation::time_duration duration = esl::simulation::time_duration(1))
        : rate<>(rate_over_duration), duration(duration)
        {

        }

#if BOOST_VERSION >= 106500
        //constexpr
#endif
            interest_rate(rate<> rate_over_duration,
                                esl::simulation::time_duration duration)
                : rate<>(rate_over_duration), duration(duration)
        {

        }

        virtual ~interest_rate() = default;

        ///
        /// \tparam archive_t
        /// \param archive
        /// \param version
        template<class archive_t>
        void serialize(archive_t &archive, const unsigned int version)
        {
            (void)version;

            archive &boost::serialization::make_nvp(
                "rate_uint64_t_",
                boost::serialization::base_object<rate<>>(*this));
            archive &BOOST_SERIALIZATION_NVP(duration);
        }
    };

    struct inflation_rate
    : public interest_rate
    {
        using interest_rate::interest_rate;

        virtual ~inflation_rate() = default;


        static inflation_rate from_consumer_prices(price begin, price end, esl::simulation::time_duration d)
        {
            return inflation_rate(rate<>((end - begin).value, begin.value), d );
        }
    };

    struct nominal_interest_rate
    : public interest_rate
    {
        using interest_rate::interest_rate;

        virtual ~nominal_interest_rate() = default;

    };

    struct real_interest_rate
    : public interest_rate
    {
        using interest_rate::interest_rate;

        virtual ~real_interest_rate() = default;

    };
}

#ifdef WITH_MPI
namespace boost::mpi {
    template<>
    struct is_mpi_datatype<esl::economics::interest_rate>
    : public mpl::true_
    {

    };
}
#endif

#endif  // ESL_INTEREST_RATE_HPP
