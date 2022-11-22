/**
 * @file basic_book.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_BASIC_BOOK_HPP
#define ESL_BASIC_BOOK_HPP


#include <cstdint>
#include <optional>
#include <vector>

#include <esl/economics/markets/order_book/execution_report.hpp>
#include <esl/economics/markets/quote.hpp>


namespace esl::economics::markets::order_book {

    struct basic_book
    {
        ///
        /// \brief  Type used to keep track of placed orders
        ///         TODO: standardize by changing this to identity<order>
        ///
        typedef std::uint64_t order_identifier;

        ///
        /// \brief  This value is returned for orders that are directly executed
        ///         and did not receive an order ID
        ///
        constexpr static const order_identifier direct_order = (std::numeric_limits<order_identifier>::max)();

        ///
        /// \brief  Sequence of execution reports as they were
        ///
        std::vector<execution_report> reports;

        ///
        /// \brief  Constructs the base class for order books, which reserves
        ///         memory to store execution reports.
        ///
        /// \param report_reserved  number of spaces to reserve in the vector of
        ///                         reports, set so that memory allocations are
        ///                         minimized.
        explicit basic_book(size_t report_reserved = 16)
        : reports()
        {
            reports.reserve(report_reserved);
        }

        virtual ~basic_book() = default;

        ///
        /// \brief  Best bid quote for this order book
        ///
        /// \return quote if any bid orders are in the book, otherwise nullopt.
        [[nodiscard]] virtual std::optional<quote> bid() const = 0;

        ///
        /// \brief  Best ask quote for this order book
        ///
        /// \return quote if any ask orders are in the book, otherwise nullopt.
        [[nodiscard]] virtual std::optional<quote> ask() const = 0;

        ///
        /// \brief  Extracts the order and places it in the book.
        ///
        /// \param order    limit_order sent by the market participant
        virtual void insert(const limit_order &order) = 0;

        ///
        /// \brief  Cancels a placed order by its order_identifier
        ///
        /// \param order identifier the order book gave once the order was places
        virtual void cancel(order_identifier order) = 0;

        ///
        /// \brief  Obtains a vector of active orders.
        /// 
        [[nodiscard]] virtual std::vector<basic_book::order_identifier> orders() const = 0;


        ///
        /// \brief  Gets the n-th level in the order book and returns the associated quote and market depth
        ///
        /// \param level
        /// \param side
        /// \return
        //virtual std::optional<std::pair<quote, std::uint64_t>> level(std::uint64_t level, limit_order::side_t side) const = 0;


        ///
        /// \brief  Renders the order book to the console at 80 characters width
        ///         for debugging purposes. Prefer serialization for storage of
        ///         the order book to files.
        ///
        /// \param levels how many levels to display, must be at least 1
        virtual void display(std::uint64_t levels = 5) const = 0;
    };

} // namespace esl::economics::markets::order_book

#endif  // ESL_BASIC_BOOK_HPP