//
// Created by ldir on 21.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"

using namespace urx;

static bool is_even(const int &v) {
    return v % 2 == 0;
}

TEST_CASE("Test", "[urx]") {
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

