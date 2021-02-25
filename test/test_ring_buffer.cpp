//
// Created by ldir on 25.02.2021.
//

#include <catch2/catch.hpp>
#include <urx_ring_buffer.hpp>
#include <cstdlib>

using namespace urx;


TEST_CASE("Test ring buffer size 1", "[urx]") {
    RingBuffer<1, int> buf;
    int val;
    for (int i = 0; i < 7; i++) {
        REQUIRE(buf.is_empty());
        buf.put(i);
        REQUIRE_FALSE(buf.is_empty());
        buf.put(i + 1);
        REQUIRE(buf.get(&val));
        REQUIRE(val == i);
    }
}


TEST_CASE("Test ring buffer size 2", "[urx]") {
    RingBuffer<2, int> buf;
    int val;
    for (int j = 0; j < 7; ++j) {
        REQUIRE(buf.is_empty());
        REQUIRE_FALSE(buf.is_full());
        buf.put(j);
        buf.put(j + 1);
        buf.put(j + 2);
        REQUIRE(buf.is_full());
        REQUIRE_FALSE(buf.is_empty());
        REQUIRE(buf.get(&val));
        REQUIRE(val == j);
        buf.put(j + 3);
        buf.put(j + 4);
        REQUIRE(buf.is_full());
        REQUIRE(buf.get(&val));
        REQUIRE(val == j + 1);
        REQUIRE_FALSE(buf.is_empty());
        REQUIRE(buf.get(&val));
        REQUIRE(val == j + 3);
        REQUIRE(buf.is_empty());
    }
}


TEMPLATE_TEST_CASE("Test ring buffer different sizes", "[urx]",
                   (RingBuffer<1, int>), (RingBuffer<2, int>), (RingBuffer<11, int>), (RingBuffer<111, int>)) {

    int count = 101;
    TestType buf;

    int j;
    int t;
    int x = 0;
    int y = 0;
    while (buf.get(&t));

    while (x < count) {
        int iter = rand() % (buf.get_size()) + 1;

        REQUIRE(buf.is_empty());
        for (j = 0; j < iter; ++j) {
            buf.put(x++);
        }

        for (; j > 0; --j) {
            REQUIRE_FALSE(buf.is_empty());
            if (j % 2) {
                t = *buf.front();
                buf.pop();
            } else {
                REQUIRE(buf.get(&t));
            }
            REQUIRE(t == y++);
        }
        REQUIRE_FALSE(buf.get(&t));
        REQUIRE(buf.is_empty());
    }
}
