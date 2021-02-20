//
// Created by ldir on 14.02.2021.
//

#include <catch2/catch.hpp>
#include <urx.hpp>

using namespace urx;

template<typename T>
class RegisterValue : public Observer<T> {
    void on_next(const T& val) override {
        last=val;
        ++counter;
    }

public:
    int last = -1;
    int counter = 0;
};

TEST_CASE("Pass value to subscribers", "[urx]") {
    Observable<int> out;
    RegisterValue<int> in1;
    RegisterValue<int> in2;
    out.subscribe(in1);
    out.subscribe(in2);
    out.next(5);
    REQUIRE(in1.counter == 1);
    REQUIRE(in1.last == 5);
    REQUIRE(in2.counter == 1);
    REQUIRE(in2.last == 5);
    out.next(6);
    REQUIRE(in1.counter == 2);
    REQUIRE(in1.last == 6);
    REQUIRE(in2.counter == 2);
    REQUIRE(in2.last == 6);
}

TEST_CASE("Multiple inheritance", "[urx]") {
    Observer<int> a;
    Observable<int> b;
    b.subscribe(a);
}



TEST_CASE("Convert", "[urx]") {
    Observable<const char *> src;
    Observer<int> dst;
    Convert<const char *, int> cnv;
    src.subscribe(cnv);
    cnv.subscribe(dst);
}




