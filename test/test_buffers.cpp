//
// Created by ldir on 23.02.2021.
//


#include <catch2/catch.hpp>
#include <urx.hpp>
#include "utils.hpp"
#include <cstdlib>

using namespace urx;

TEST_CASE("Last buffer ", "[urx]") {
    Observable<int> src;
    Last<int> last_value(42);

    src >> last_value;

    REQUIRE(last_value.get_last() == 42);
    src.next(1);
    REQUIRE(last_value.get_last() == 1);
    src.next(2);
    REQUIRE(last_value.get_last() == 2);
}
