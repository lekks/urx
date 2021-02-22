//
// Created by ldir on 21.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"

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

TEST_CASE("Test filter 2 arguments argument", "[urx]") {
    Observable<int, int> src;
    auto filter = make_filter<int, int>([](const int &a, const int &b) -> bool { return a % b == 0; });
    CounterValue<int, int> cnt;
    src >> filter >> cnt;

    src.next(1,2);
    REQUIRE(cnt.counter == 0);

    src.next(2,1);
    REQUIRE(cnt.counter == 1);

    src.next(3,2);
    REQUIRE(cnt.counter == 1);

    src.next(4,2);
    REQUIRE(cnt.counter == 2);
}
