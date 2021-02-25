//
// Created by ldir on 21.02.2021.
//

#include <catch2/catch.hpp>
#include <urx.hpp>
#include "utils.hpp"
#include <cstdlib>

using namespace urx;

TEST_CASE("Merge ", "[urx]") {
    Observable<int> src1;
    Observable<int> src2;
    Merge<2, int> merge;
    LastValue<int> dst;

    src1 >> merge.input(0);
    src2 >> merge.input(1);
    merge >> dst;

    src1.emit(1);
    REQUIRE(dst.last == 1);
    src2.emit(2);
    REQUIRE(dst.last == 2);
}
