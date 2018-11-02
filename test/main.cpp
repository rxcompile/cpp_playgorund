#include <iostream>

#include "cpp_playground/function_traits.hpp"
#include "cpp_playground/delayed_call.hpp"
#include "cpp_playground/python_container.hpp"
#include "cpp_playground/unpacked_call.hpp"

class Foo
{
  public:
    double bar(int a, float b)
    {
        return a * b;
    }
};

int foo(int a, int b = 5)
{
    return a * b;
}

int main()
{
    using namespace CppTest;
    Foo a{};
    Container b{2, 2};
    std::cout << delayedCall(a, &Foo::bar, b) << std::endl;
    std::cout << callMe(std::function<int(int, int)>(foo), 1, 2) << std::endl;
    std::cout << foo(1, 2) << std::endl;
    std::cout << callMe(std::function<int(int, int)>(foo), 2, 5) << std::endl;
    std::cout << foo(2) << std::endl;
    //std::cout << callMe(std::function<int(int,int)>(foo), std::make_tuple(1,2)) << std::endl;
    auto lam = [](int a = 0) -> int { return a; };
    std::cout << typeid(lam).name() << std::endl;
}