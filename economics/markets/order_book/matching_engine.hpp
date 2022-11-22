/**
 * @file matching_engine.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef ME_MATCHING_ENGINE_HPP
#define ME_MATCHING_ENGINE_HPP

#include <iostream>
#include <map>
#include <queue>

#include <boost/container/flat_map.hpp>

#include <esl/economics/markets/order_book/binary_tree_order_book.hpp>
#include <esl/economics/markets/order_book/order.hpp>
#include <esl/economics/markets/ticker.hpp>


namespace esl::economics::markets::order_book {
    class matching_engine
    {
    protected:
        std::function<std::shared_ptr<basic_book>(
            void)>
            order_book_factory_;
    public:
        boost::container::flat_map<ticker, std::shared_ptr<basic_book>> books;

        explicit matching_engine(
            std::function< std::shared_ptr<basic_book>(void) >
                order_book_factory = [](){
                        return std::make_shared<binary_tree_order_book>();
                                     })
        : order_book_factory_(order_book_factory)
        {

        }

        ///
        /// \brief
        ///
        /// \param order
        /// \return
        void insert(const limit_order &order)
        {
            auto i = books.find(order.symbol);

            if(i == books.end()) {
                i = books.emplace(order.symbol, order_book_factory_()).first;
            }
            return i->second->insert(order);
        }

        void cancel(const ticker &symbol,
                    const typename basic_book::order_identifier
                        identifier)
        {
            auto i = books.find(symbol);
            if(books.end() != i){
                i->second->cancel(identifier);
            }
        }

        /*
        ///
        /// \param symbol
        /// \param side
        /// \param id
        /// \return
        limit_order &find( const ticker& symbol
                   , limit_order::side_t side
                   , const esl::identity<esl::law::property>& identifier)
        {
            auto i = books.find(symbol);
            if(books.end() == i) {
                throw std::exception();
            }
            return i->second->find(side, identifier);
        }


        bool match(const ticker &symbol, std::queue<limit_order> &orders)
        {
            auto i = books.find(symbol);
            if(i == books.end()) {
                return false;
            }


            return i->second->insert(orders);
        }

        bool match(std::queue<limit_order> &orders)
        {
            for(auto & book : books) {
                book.second->insert(orders);
            }
            return !orders.empty();
        }
        */
    };

}  // namespace esl::economics::markets::order_book

#endif  // ME_MATCHING_ENGINE_HPP
