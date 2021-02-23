//
// Created by ldir on 14.02.2021.
//

#include <catch2/catch.hpp>
#include <urx.hpp>
#include <cstdlib>
#include "utils.hpp"

using namespace urx;


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
    void on_next(T &&...value) override {
        this->next(std::forward<T>(value)...);
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

TEST_CASE("Double subscription", "[urx]") {
}


class StrToInt : public Observable<int>, public Observer<const char *> {
public:
    void on_next(const char * &&value) override {
        this->next(atoi(value));
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

