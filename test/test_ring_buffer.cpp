//
// Created by ldir on 25.02.2021.
//

#include <catch2/catch.hpp>
#include <urx_ring_buffer.hpp>
#include <cstdlib>
#include <thread>
#include <atomic>


using namespace urx;


TEST_CASE("Test ring buffer size 1", "[urx]") {
    RingBuffer<1, int, unsigned> buf;
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
    RingBuffer<2, int, unsigned> buf;
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
                   (RingBuffer<1, int, unsigned>), (RingBuffer<2, int, unsigned>), (RingBuffer<11, int, unsigned>),
                   (RingBuffer<111, int, unsigned>)) {

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


using TestingBuffer = RingBuffer<123, int, unsigned long long int>;

void producer_func(TestingBuffer &buf) {
    for (int i = 0; i < 1000000; ++i) {
        while (!buf.put(i));
    }
    buf.put(-1);
}

void consumer_func(TestingBuffer &buf, bool* result) {
    int val=0;
    int counter=0;
    for(;;) {
        while (!buf.get(&val));
        if(val == -1) {
            return;
        } else if (val != counter++) {
            *result = false;
            printf("%i ",val);
        }
    }
}

TEST_CASE("Test buffer thread safety", "[urx]") {
    TestingBuffer buf;

    bool result_correct = true;
    std::thread producer_thr(producer_func, std::ref(buf));
    std::thread consumer_thr(consumer_func, std::ref(buf), &result_correct);
    producer_thr.join();
    consumer_thr.join();
    REQUIRE(result_correct);
}
