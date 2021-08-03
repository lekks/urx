//
// Created by ldir on 22.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"

using namespace urx;

TEST_CASE("Test distinct", "[urx]") {
    Observable<int> src;
    Distinct<int> filter;
    CounterValue<int> dst1;
    LastValue<int> dst2;
    src >> filter >> dst1;
    filter >> dst2;

    src.next(1);
    REQUIRE(dst1.counter == 1);
    REQUIRE(dst2.last == 1);

    src.next(1);
    REQUIRE(dst1.counter == 1);
    REQUIRE(dst2.last == 1);

    src.next(2);
    REQUIRE(dst1.counter == 2);
    REQUIRE(dst2.last == 2);

    src.next(2);
    REQUIRE(dst1.counter == 2);
    REQUIRE(dst2.last == 2);

    src.next(3);
    REQUIRE(dst1.counter == 3);
    REQUIRE(dst2.last == 3);

}
