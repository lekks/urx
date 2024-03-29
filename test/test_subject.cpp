//
// Created by ldir on 22.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"

using namespace urx;

TEST_CASE("Test subject", "[urx]") {
    Observable<int> src;
    Subject<int> subject;
    LastValue<int> dst1;
    LastValue<int> dst2;
    LastValue<int> dst3;
    src >> subject >> dst1;
    src >> dst3;
    subject >> dst2;

    src.next(1);
    REQUIRE(dst1.last == 1);
    REQUIRE(dst2.last == 1);
    REQUIRE(dst3.last == 1);

    src.next(2);
    REQUIRE(dst1.last == 2);
    REQUIRE(dst2.last == 2);
    REQUIRE(dst3.last == 2);

    src.next(3);
    REQUIRE(dst1.last == 3);
    REQUIRE(dst2.last == 3);
    REQUIRE(dst3.last == 3);

}

TEST_CASE("Subject getters", "[urx]") {
    Observable<int> src;
    Subject<int> subject;
    LastValue<int> dst;
    src >> subject.get_observer();
    subject.get_observable() >> dst;

    src.next(1);
    REQUIRE(dst.last == 1);
    src.next(2);
    REQUIRE(dst.last == 2);
    src.next(3);
    REQUIRE(dst.last == 3);
}

TEST_CASE("Subject next", "[urx]") {
    Observable<int> src;
    Subject<int> subject;
    LastValue<int> dst;
    src >> subject >> dst;

    src.next(1);
    REQUIRE(dst.last == 1);
    subject.next(2);
    REQUIRE(dst.last == 2);
    subject.call_on_next(3);
    REQUIRE(dst.last == 3);
}

TEST_CASE("Subscribe on ctor", "[urx]") {
    Observable<int> out;
    Subject<int> subject(out);
    LastValue<int> in(subject);
    out.next(5);
    REQUIRE(in.last == 5);
    REQUIRE(in.is_connected() == true);
}