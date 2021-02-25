//
// Created by ldir on 23.02.2021.
//


#include <catch2/catch.hpp>
#include <urx.hpp>
#include "utils.hpp"
#include <cstdlib>

using namespace urx;

TEST_CASE("LastBuffer buffer ", "[urx]") {
    Observable<int> src;
    LastBuffer<int> last_value(42);

    src >> last_value;

    REQUIRE(last_value.get_last() == 42);
    src.next(1);
    REQUIRE(last_value.get_last() == 1);
    src.next(2);
    REQUIRE(last_value.get_last() == 2);
}

TEST_CASE("Test fifo buffer", "[urx]") {
    Observable<int> src;
    FifoBuffer<3, int> fifo;
    src >> fifo;

    int val;
    for (int i = 0; i < 17; ++i) {
        REQUIRE(fifo.is_empty());
        src.next(i);
        REQUIRE_FALSE(fifo.is_empty());
        src.next(i+1);
        src.next(i+2);
        REQUIRE(*fifo.front() == i);
        REQUIRE((fifo.take(&val) && val == i));
        REQUIRE((fifo.take(&val) && val == i+1));
        REQUIRE((fifo.take(&val) && val == i+2));
        REQUIRE_FALSE(fifo.take(&val));
        REQUIRE(fifo.is_empty());
    }
}
