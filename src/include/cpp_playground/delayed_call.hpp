#pragma once

#include "cpp_playground/python_container.hpp"
#include "cpp_playground/function_traits.hpp"

#include <vector>
#include <functional>

namespace CppTest
{
template <typename TRet, typename... TArgs>
class DelayedCall
{
  public:
    DelayedCall(std::function<TRet(TArgs...)> fn, Container &data)
        : args(parseArgs(data, std::index_sequence_for<TArgs...>())), func(fn)
    {
    }

    auto call()
    {
        return callInternal(std::index_sequence_for<TArgs...>());
    }

  private:
    template <typename TArg, size_t idx>
    TArg parseArg(Container &data)
    {
        //TArg a = std::any_cast<TArg>(data[idx]);
        TArg a = data[idx];
        return a;
    }

    template <size_t... S>
    auto parseArgs(Container &data, std::index_sequence<S...>)
    {
        return std::make_tuple(parseArg<typename function_traits<decltype(func)>::template arg<S>::type, S>(data)...);
    }

    template <size_t... S>
    auto callInternal(std::index_sequence<S...>)
    {
        return func(std::get<S>(args)...);
    }

  private:
    std::tuple<TArgs...> args;
    std::function<TRet(TArgs...)> func;
};

template <typename TRet, typename... TArgs>
TRet delayedCall(std::function<TRet(TArgs...)> func, Container &data)
{
    return DelayedCall<TRet, TArgs...>(func, data).call();
}

template <typename M, typename TRet, typename... TArgs>
TRet delayedCall(M &ptr, TRet (M::*func)(TArgs...), Container &data)
{
    std::function<TRet(TArgs...)> f = [&ptr, func](TArgs... args) { return (ptr.*func)(args...); };
    return DelayedCall<TRet, TArgs...>(f, data).call();
}

}