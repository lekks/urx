//
// Created by ldir on 14.02.2021.
//

#include <catch2/catch.hpp>
#include <urx.hpp>
#include <cstdlib>
#include "utils.hpp"

using namespace urx;

TEST_CASE("No connection", "[urx]") {
    Observable<int> out;
    LastValue<int> in;
    out.next(5);
    REQUIRE(in.last == -1);
    REQUIRE(in.is_connected() == false);
}

TEST_CASE("Pass value to subscribers", "[urx]") {
    Observable<int> out;
    LastValue<int> in1;
    CounterValue<int> in2;
    out.subscribe(in1);
    out.subscribe(in2);
    out.next(5);
    REQUIRE(in1.last == 5);
    REQUIRE(in2.counter == 1);
    out.next(6);
    REQUIRE(in1.last == 6);
    REQUIRE(in2.counter == 2);
}


template<typename ...T>
class Link : public Observer<T...>, public Observable<T...> {
public:
    void on_next(const T &...value) override {
        this->next(value...);
    };
};

TEST_CASE("Chain operator values", "[urx]") {
    Observable<int> src;
    Link<int> subj;
    LastValue<int> reg;
    src | subj | reg;
    src.next(321);
    REQUIRE(reg.last == 321);
}

TEST_CASE("Chain operator events", "[urx]") {
    Observable<> out;
    Link<> subj;
    CounterValue<> in;
    out >> subj >> in;
    out.next();
    REQUIRE(in.counter == 1);
    out.next();
    REQUIRE(in.counter == 2);
}

TEST_CASE("Resubscribe subscription", "[urx]") {
    Observable<int> src1;
    Observable<int> src2;
    LastValue<int> dst;
    src1.subscribe(dst);
    src1.next(1);
    REQUIRE(dst.last == 1);
    src1.unsubscribe(dst);
    src1.next(2);
    REQUIRE(dst.last == 1);
    src1.subscribe(dst);
    src1.next(3);
    REQUIRE(dst.last == 3);
    src2.subscribe(dst);
    src1.next(5);
    REQUIRE(dst.last == 3);
    src2.next(6);
    REQUIRE(dst.last == 6);
}

TEST_CASE("Unsubscribe all subscription", "[urx]") {
    Observable<int> out;
    LastValue<int> in1;
    CounterValue<int> in2;
    out.subscribe(in1);
    out.subscribe(in2);
    REQUIRE(in1.is_connected());
    REQUIRE(in2.is_connected());
    out.next(5);
    REQUIRE(in1.last == 5);
    REQUIRE(in2.counter == 1);
    out.unsubscribe_all();
    REQUIRE_FALSE(in1.is_connected());
    REQUIRE_FALSE(in2.is_connected());
    out.next(6);
    REQUIRE(in1.last == 5);
    REQUIRE(in2.counter == 1);
}

TEST_CASE("Unsubscribe on destructor", "[urx]") {
    LastValue<int> in1;
    CounterValue<int> in2;
    {
        Observable<int> out;
        out.subscribe(in1);
        out.subscribe(in2);
        REQUIRE(in1.is_connected());
        REQUIRE(in2.is_connected());
    }
    REQUIRE_FALSE(in1.is_connected());
    REQUIRE_FALSE(in2.is_connected());
}



class StrToInt : public Observable<int>, public Observer<const char *> {
public:
    void on_next(const char *const &value) override {
        next(atoi(value));
    }

public:
};

TEST_CASE("Test type change", "[urx]") {
    Observable<const char *> src;
    LastValue<int> dst;
    StrToInt str2int;

    src >> str2int >> dst;

    src.next("54");
    REQUIRE(dst.last == 54);
}

