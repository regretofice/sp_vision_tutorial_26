#include<fmt/format.h>
int main()
{
    fmt::print("fmt_test {}\n","passed");
    std::string message = fmt::format("The answer is {}.", 42);
    fmt::print(message);
    return 0;
}