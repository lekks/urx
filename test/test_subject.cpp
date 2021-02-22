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

TEST_CASE("Test subject getters", "[urx]") {
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