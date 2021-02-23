//
// Created by ldir on 21.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"
#include <cstdlib>

using namespace urx;

static bool is_even(const int &v) {
    return v % 2 == 0;
}

TEST_CASE("Test filter single argument", "[urx]") {
    Observable<int> src;
    int x = 3;
    auto filter1 = make_filter<int>(is_even);
    auto filter2 = make_filter<int>([&x](const int &v) -> bool { return v % x == 0; });
    LastValue<int> dst1;
    LastValue<int> dst2;
    src >> filter1 >> dst1;
    src >> filter2 >> dst2;

    src.next(1);
    REQUIRE(dst1.last == -1);
    REQUIRE(dst2.last == -1);

    src.next(2);
    REQUIRE(dst1.last == 2);
    REQUIRE(dst2.last == -1);

    src.next(3);
    REQUIRE(dst1.last == 2);
    REQUIRE(dst2.last == 3);

}

TEST_CASE("Test filter 2 arguments", "[urx]") {
    Observable<int, int> src;
    auto filter = make_filter<int, int>([](const int &a, const int &b) -> bool { return a % b == 0; });
    CounterValue<int, int> cnt;
    src >> filter >> cnt;

    src.next(1, 2);
    REQUIRE(cnt.counter == 0);

    src.next(2, 1);
    REQUIRE(cnt.counter == 1);

    src.next(3, 2);
    REQUIRE(cnt.counter == 1);

    src.next(4, 2);
    REQUIRE(cnt.counter == 2);
}

TEST_CASE("Test map", "[urx]") {
    Observable<const char *> src;
    LastValue<int> dst;
    auto map = make_map<const char *, int>([](const char *const &value) -> int { return atoi(value); });
    src >> map >> dst;

    src.next("54");
    REQUIRE(dst.last == 54);

}

TEST_CASE("Test reduce", "[urx]") {
    Observable<float> src;
    LastValue<int> dst;
    auto reduce = make_scan<float, int>(
            [](const int &accumulator, const float &value) -> int { return accumulator + value; }, 13);
    src >> reduce >> dst;

    src.next(0.5);
    REQUIRE(dst.last == 13);

    src.next(5.7);
    REQUIRE(dst.last == 18);

    REQUIRE(reduce.get() == 18);
}


TEST_CASE("Test function 2 arguments", "[urx]") {

    int accum = 0;
    Observable<int, int> src;
    auto func = make_function<int, int>([&accum](const int &a, const int &b) { accum += a + b; });
    src >> func;

    src.next(1, 2);
    REQUIRE(accum == 3);

    src.next(2, 3);
    REQUIRE(accum == 8);
}

TEST_CASE("Test function no arguments", "[urx]") {

    int counter = 0;
    Observable<> src;
    auto func = make_function<>([&counter]() { counter += 1; });
    src >> func;

    src.next();
    REQUIRE(counter == 1);

    src.next();
    REQUIRE(counter == 2);
}
