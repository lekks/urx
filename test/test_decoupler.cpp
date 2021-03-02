//
// Created by ldir on 22.02.2021.
//

#include <catch2/catch.hpp>
#include "utils.hpp"

using namespace urx;

TEST_CASE("Test nonblocking decouple single", "[urx]") {
    Observable<int> src;
    NonBlockingDecoupler<40, int> decoupler;
    LastValue<int> dst;
    src >> decoupler >> dst;

    REQUIRE(decoupler.is_empty());
    REQUIRE_FALSE(decoupler.process_one());
    src.emit(1);
    src.emit(2);
    REQUIRE(dst.last == -1);
    REQUIRE(decoupler.process_one());
    REQUIRE(dst.last == 1);
    REQUIRE(decoupler.process_one());
    REQUIRE(dst.last == 2);
    REQUIRE_FALSE(decoupler.process_one());
    REQUIRE(decoupler.is_empty());
}

TEST_CASE("Test nonblocking decouple process all", "[urx]") {
    Observable<int> src;
    NonBlockingDecoupler<40, int> decoupler;
    LastValue<int> dst;
    CounterValue<int> cnt;
    src >> decoupler >> dst;
    decoupler >> cnt;

    REQUIRE(decoupler.is_empty());
    REQUIRE_FALSE(decoupler.process_all());
    src.emit(1);
    src.emit(2);
    REQUIRE(dst.last == -1);
    REQUIRE(decoupler.process_all());
    REQUIRE(dst.last == 2);
    REQUIRE(cnt.counter == 2);
    REQUIRE(decoupler.is_empty());
}

TEST_CASE("Test nonblocking decouple strategy ", "[urx]") {
    Observable<int> src;
    NonBlockingDecoupler<3, int> decoupler;
    LastValue<int> dst;
    src >> decoupler >> dst;

    SECTION("Drop oldest") {
        decoupler.set_strategy(DecouplerNoSpaceStrategy::DROP_OLDEST);
        REQUIRE(decoupler.is_empty());
        REQUIRE_FALSE(decoupler.process_one());
        src.emit(1);
        src.emit(2);
        src.emit(3);
        src.emit(4);
        REQUIRE(dst.last == -1);
        REQUIRE(decoupler.process_one());
        REQUIRE(dst.last == 2);
    }

    SECTION("Push oldest") {
        decoupler.set_strategy(DecouplerNoSpaceStrategy::PUSH_OLDEST);
        REQUIRE(decoupler.is_empty());
        REQUIRE_FALSE(decoupler.process_one());
        src.emit(1);
        src.emit(2);
        src.emit(3);
        REQUIRE(dst.last == -1);
        src.emit(4);
        REQUIRE(dst.last == 1);
    }
}
