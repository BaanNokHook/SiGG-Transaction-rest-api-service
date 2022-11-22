/**
 * @file binary_tree_order_book.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <esl/data/log.hpp>
#include <esl/economics/markets/order_book/binary_tree_order_book.hpp>


namespace esl::economics::markets::order_book {

    namespace dynamically_allocated {

/*
        bool book::insert(const limit_order &order)
        {
            if(order.side == limit_order::buy) {
                index assigned_ = next_++;
                orders_bid.insert(bid_t::value_type( order.limit
                                                      , std::make_pair(assigned_, order) ));
            } else if(order.side == limit_order::sell) {
                index assigned_ = next_++;
                orders_ask.insert(ask_t::value_type( order.limit
                                                      , std::make_pair(assigned_, order)));
            }

            return true;
        }

        void book::erase(index identifier)
        {
            for(auto i = orders_bid.begin_(); i != orders_bid.end(); ++i) {
                if(i->second.first == identifier) {
                    orders_bid.erase(i);
                    return;
                }
            }

            for(auto i = orders_ask.begin_(); i != orders_ask.end(); ++i) {
                if(i->second.first == identifier) {
                    orders_ask.erase(i);
                    return;
                }
            }
        }

        bool book::match(std::queue<limit_order> &orders)
        {
            while(true) {
                if(orders_bid.empty() || orders_ask.empty()) {
                    return !orders.empty();
                }

                auto i_bid_ = orders_bid.begin_();
                auto i_ask_ = orders_ask.begin_();

                if(i_bid_->second.second.limit >= i_ask_->second.second.limit) {
                    limit_order &bid = i_bid_->second.second;
                    limit_order &ask = i_ask_->second.second;

                    match(bid, ask);
                    orders.push(bid);
                    orders.push(ask);

                    if(bid.closed()) {
                        orders_bid.erase(i_bid_);
                    }

                    if(ask.closed()) {
                        orders_ask.erase(i_ask_);
                    }
                } else {
                    return !orders.empty();
                }
            }
        }

        limit_order &book::find(limit_order::side_t side,
                          //const esl::identity<esl::law::property> &
                              index identifier)
        {
            if(side == limit_order::buy) {
                for(auto &i : orders_bid) {
                    if(i.second.first == identifier) {
                        return i.second.second;
                    }
                }
            } else if(side == limit_order::sell) {
                for(auto &i : orders_ask) {
                    if(i.second.first == identifier) {
                        return i.second.second;
                    }
                }
            }

            throw std::exception();
        }

        void book::match(limit_order &bid, limit_order &ask)
        {
            auto price     = ask.limit;
            auto quantity_ = std::min(bid.quantity, ask.quantity);

            bid.quantity -= quantity_;
            ask.quantity -= quantity_;

            // TODO: 1 trade report to all participants
            //       2 executionreports to buyer/seller
        }*/
    }

}
