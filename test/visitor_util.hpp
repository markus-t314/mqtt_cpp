// Copyright Takatoshi Kondo 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(MQTT_VISITOR_UTIL_HPP)
#define MQTT_VISITOR_UTIL_HPP

#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>

template <typename ReturnType, typename... Lambdas>
struct lambda_visitor;

template <typename ReturnType, typename Lambda1, typename... Lambdas>
struct lambda_visitor<ReturnType, Lambda1, Lambdas...>
    : lambda_visitor<ReturnType, Lambdas...>, Lambda1 {
    using Lambda1::operator();
    using lambda_visitor<ReturnType, Lambdas...>::operator();
    lambda_visitor(Lambda1 lambda1, Lambdas... lambdas)
        : Lambda1(lambda1), lambda_visitor<ReturnType, Lambdas...>(lambdas...) {}
};


template <typename ReturnType, typename Lambda1>
struct lambda_visitor<ReturnType, Lambda1>
    : boost::static_visitor<ReturnType>, Lambda1 {
    using Lambda1::operator();
    lambda_visitor(Lambda1 lambda1)
        : boost::static_visitor<ReturnType>(), Lambda1(lambda1) {}
};


template <typename ReturnType>
struct lambda_visitor<ReturnType>
    : public boost::static_visitor<ReturnType> {
    lambda_visitor() : boost::static_visitor<ReturnType>() {}
};

template <typename ReturnType, typename... Lambdas>
inline lambda_visitor<ReturnType, Lambdas...> make_lambda_visitor(Lambdas&&... lambdas) {
    return { std::forward<Lambdas>(lambdas)... };
}

#endif // MQTT_VISITOR_UTIL_HPP
