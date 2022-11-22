/**
 * @file tangibility.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_TANGIBILITY_HPP
#define ESL_TANGIBILITY_HPP

#include <boost/serialization/serialization.hpp>

#include <esl/geography/location.hpp>

namespace esl::economics {
    ///
    /// \brief  A tangible is a physical object and its physical location and
    ///         state play an economic role e.g. transportation and
    ///         storage cost. It is not necessarily infungible; depending on the
    ///         buyers views, one lot can be as good as another.
    ///
    struct tangible
    {
        virtual ~tangible() = default;

        /// \brief
        geography::location place;
    };

    struct intangible
    {
        virtual ~intangible() = default;

    };
}  // namespace esl::economics

#endif  // ESL_TANGIBILITY_HPP
