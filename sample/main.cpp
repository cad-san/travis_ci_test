#include <future>
#include <iostream>

int add_async(int a, int b)
{
    return a + b;
}

int main(int argc, char const* argv[])
{
    auto result = std::async(std::launch::async, add_async, 1, 2);

    std::cout << result.get() << std::endl;
    return 0;
}
