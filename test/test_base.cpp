//
// Created by ldir on 14.02.2021.
//

#include <catch2/catch.hpp>
#include <urx.hpp>
#include <cstdlib>

using namespace urx;

template<typename T>
class RegisterValue : public Observer<T> {
    void on_next(const T &val) override {
        last = val;
    }

public:
    int last = -1;
};

template<typename ...T>
class CounterValue : public Observer<T...> {
    void on_next(const T& ...) override {
        ++counter;
    }

public:
    int counter = 0;
};



TEST_CASE("Pass value to subscribers", "[urx]") {
    Observable<int> out;
    RegisterValue<int> in1;
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

TEST_CASE("Void events", "[urx]") {
    Observable<> out;
    CounterValue<> in;
    out.subscribe(in);
    out.next();
    REQUIRE(in.counter == 1);
    out.next();
    REQUIRE(in.counter == 2);
}

TEST_CASE("Subject", "[urx]") {
    Observable<int> src;
    Subject<int> subj;
    RegisterValue<int> reg;
    CounterValue<int> cnt;
    src.subscribe(subj);
    subj.subscribe(reg);
    subj.subscribe(cnt);
    src.next(678);
    REQUIRE(cnt.counter == 1);
    REQUIRE(reg.last == 678);
}

class StrToInt : public Observable<int>, public Observer<const char *> {
public:
    void on_next(const char *const &value) override {
        next(atoi(value));
    }

public:
};

TEST_CASE("Convert sting to int", "[urx]") {
    Observable<const char *> src;
    RegisterValue<int> dst;
    StrToInt str2int;
    src.subscribe(str2int);
    str2int.subscribe(dst);

    src.next("54");
    REQUIRE(dst.last == 54);
}


TEST_CASE("Convert", "[urx]") {
    Observable<const char *> src;
    Observer<int> dst;
    Convert<const char *, int> cnv;
    src.subscribe(cnv);
    cnv.subscribe(dst);
}
