#pragma once

#include <functional>

namespace CppTest
{

template <size_t... S, typename Functor, typename... Args>
auto callMeUnpacked(std::index_sequence<S...>, Functor &&func, const std::tuple<Args...> &args)
{
    return std::invoke(std::forward<Functor>(func), std::get<S>(args)...);
}

template <typename Functor, typename... Args>
auto callMe(Functor &&func, Args &&... args)
{
    return callMeUnpacked(std::index_sequence_for<Args...>(), func, std::forward_as_tuple(std::forward<Args>(args)...));
}

}