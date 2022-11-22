/**
 * @file order.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ESL_ECONOMICS_MARKETS_ORDER_HPP
#define ESL_ECONOMICS_MARKETS_ORDER_HPP

#include <string>
#include <utility>
#include <iomanip>
#include <ostream>

#include <esl/agent.hpp>
#include <esl/simulation/identity.hpp>
#include <esl/economics/markets/ticker.hpp>
#include <esl/economics/markets/quote.hpp>


namespace esl::economics::markets::order_book {

    ///
    ///
    /// \details:   0 is a valid quantity, as it denotes an order that was recently closed
    ///
    class limit_order
    {
    private:
    public:

        enum class lifetime_t
        {   good_until_cancelled = 0 // GTC
        ,   fill_or_kill         = 1 // FOK
        ,   immediate_or_cancel  = 2 // IOC
        } lifetime;

        enum side_t
        { buy  = 0
        , sell = 1
        } side;

        ticker symbol;

        identity<agent> owner;

        quote limit;

        std::uint32_t quantity;

        explicit limit_order ( ticker symbol = ticker()
                             , const identity<agent> &owner = identity<agent>()
                             , side_t side = buy
                             , const quote& limit = quote(price::approximate(0.))
                             , std::uint32_t quantity = 0
                             , lifetime_t lifetime = lifetime_t::good_until_cancelled
                             )
        : lifetime(lifetime)
        , side(side)
        , symbol(std::move(symbol))
        , owner(owner)
        , limit(limit)
        , quantity(quantity)
        {

        }

        [[nodiscard]] constexpr bool operator == (const limit_order &o) const
        {
            return lifetime == o.lifetime
                && side == o.side
                && symbol == o.symbol
                && owner == o.owner
                && limit == o.limit
                && quantity == o.quantity;
        }

        ///
        /// \return
        [[nodiscard]] constexpr bool closed() const
        {
            return 0 == quantity;
        }

        ///
        /// \brief
        ///
        void cancel()
        {
            quantity = 0;
        }

    protected:
        friend std::ostream &operator << (std::ostream &, const limit_order &);
    };

    inline std::ostream &operator << (std::ostream &ostream, const limit_order &order)
    {
        (void)ostream;
        (void)order;
        return ostream;
    }

}  // namespace esl::economics::markets::order_book


#endif  // ESL_ECONOMICS_MARKETS_ORDER_HPP
