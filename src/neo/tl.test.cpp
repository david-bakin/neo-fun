#include <neo/tl.hpp>

#include <catch2/catch.hpp>

void not_noexcept() {}
void is_noexcept() noexcept {}

void foo(int, std::string = "eggs") {}

TEST_CASE("Create a simple lambda expression") {
    auto l     = NEO_TL(_1 + 2);
    auto three = l(1);
    CHECK(three == 3);
    static_assert(std::invocable<decltype(l), int>);
    static_assert(!std::invocable<decltype(l), std::string>);

    auto r = NEO_TL(55);
    CHECK(r() == 55);
    CHECK(r(1, 2, 3, 4) == 55);
    static_assert(noexcept(r()));

    auto maybe_throws = NEO_TL(not_noexcept());
    static_assert(!noexcept(maybe_throws()));

    auto no_throws = NEO_TL(is_noexcept());
    static_assert(noexcept(no_throws()));

    auto variadic = NEO_TL(foo(_args...));
    static_assert(std::invocable<decltype(variadic), int, std::string>);
    static_assert(std::invocable<decltype(variadic), int>);
    static_assert(!std::invocable<decltype(variadic), int, int>);
    static_assert(!std::invocable<decltype(variadic)>);
}
