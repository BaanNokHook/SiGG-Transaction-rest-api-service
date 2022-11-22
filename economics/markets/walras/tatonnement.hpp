/**
 * @file tatonnement.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PROJECT_TATONNEMENT_HPP
#define PROJECT_TATONNEMENT_HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <adept.h>

#include <esl/law/property_collection.hpp>
#include <esl/economics/markets/quote.hpp>
#include <esl/economics/markets/differentiable_demand_supply_function.hpp>
#include <esl/economics/markets/walras/differentiable_order_message.hpp>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

///
/// The following functions defined callbacks for various optimisers used to
/// solve the tatonnement problem. These functions reside in the
/// global namespace, because external "C" linkage doesn't deal with namespaces.
///

extern "C" double c_minimizer_function_value(const gsl_vector *variables, void *params);
extern "C" void c_minimizer_function_gradient(const gsl_vector *x, void *params, gsl_vector *gradJ);
extern "C" void c_minimizer_function_value_and_gradient(const gsl_vector *x, void *params, double *J, gsl_vector *gradJ);

extern "C" int multiroot_function_value_cb(const gsl_vector *x, void *params, gsl_vector *f);
extern "C" int multiroot_function_jacobian_cb(const gsl_vector * x, void * params, gsl_matrix * df);
extern "C" int multiroot_function_value_and_gradient_cb(const gsl_vector * x, void * params, gsl_vector * f, gsl_matrix *df);

extern "C" double uniroot_function_value (double x, void *params);
extern "C" double uniroot_function_value_and_gradient (double x, void *params);
extern "C" void   uniroot_function_jacobian_cb (double x, void *parameters, double *y, double *dy);


namespace esl::economics::markets::tatonnement {
    ///
    /// \brief
    ///
    class excess_demand_model
    {
    public:

        std::vector<std::shared_ptr<walras::differentiable_order_message>> excess_demand_functions_;

        ///
        /// \brief  Constructs the excess demand model given initial quotes.
        ///
        /// \param initial_quotes   Initial quote values that the solver
        ///                         uses to start the tatonnement process
        explicit excess_demand_model(law::property_map<quote> initial_quotes);

        virtual ~excess_demand_model();

        ///
        /// \brief  Types of solver that are offered
        ///
        enum solver
        { minimization  // minimize q: (demand(q) - supply(q))^2
        , root          // find a vector q: (demand(q) - supply(q))_i = 0 for all i
        , derivative_free_minimization
        , derivative_free_root
        };

        ///
        /// \brief  Limits maximum price decrease/increase
        ///
        std::pair<double, double> circuit_breaker = {1./11, 11.};

        ///
        /// \brief  The default approach is to try the root-finding approach
        ///         first, followed by the minimization approach if the
        ///         root finding solver does not make progress towards a
        ///         solution.
        ///
        std::vector<solver> methods =
            { root
            , minimization
            , derivative_free_root
            , derivative_free_minimization
            };

        ///
        /// \brief  The quotes to start the solving process from
        ///
        law::property_map<quote> quotes;

    protected:
        ///
        /// \brief  Adept data structure to track expressions
        ///
        adept::Stack stack_;

        ///
        /// \brief  Currently active differentiable variables. Stored in one place on the model, so that we can use
        ///         external solvers that operate on a pointer or reference to these variables
        ///
        std::vector<adept::adouble> active_;

        ///
        /// \brief
        ///
        /// \param multipliers
        /// \return
        adept::adouble demand_supply_mismatch(const adept::adouble *multipliers);

        ///
        /// \brief
        ///
        /// \param multipliers
        /// \return
        std::vector<adept::adouble> excess_demand(const adept::adouble *multipliers);

        double excess_demand_function_value(const double *multipliers);

        double minimizer_function_value_and_gradient(const double *multipliers, double *derivatives) ;

        friend void ::c_minimizer_function_gradient(const gsl_vector *multipliers, void *model, gsl_vector *derivatives);
        friend void ::c_minimizer_function_value_and_gradient(const gsl_vector *x, void *params, double *J, gsl_vector *gradJ);
        friend double ::c_minimizer_function_value(const gsl_vector *variables, void *params);

        friend int ::multiroot_function_value_cb(const gsl_vector *x, void *params, gsl_vector *f);
        friend int ::multiroot_function_value_and_gradient_cb(const gsl_vector *multipliers, void * params, gsl_vector * f, gsl_matrix *derivatives);
        friend int ::multiroot_function_jacobian_cb(const gsl_vector *multipliers, void * params, gsl_matrix *derivatives);
        std::vector<double> multiroot_function_value_and_gradient(const double *multipliers, double *derivatives) ;
        std::vector<double> multiroot_function_value(const double *multipliers);

        friend double ::uniroot_function_value(double x, void *params);
        friend double ::uniroot_function_value_and_gradient (double x, void *params);
        friend void   ::uniroot_function_jacobian_cb (double x, void *parameters, double *y, double *dy);

    public:
        ///
        /// \param max_iterations   The maximum number of iterations to perform
        ///                         while solving
        /// \return
        std::optional<std::map<identity<law::property>, double>>
        compute_clearing_quotes(size_t max_iterations = 16);

    };
} // namespace esl::economics::markets::tatonnement

#endif  // PROJECT_TATONNEMENT_HPP
