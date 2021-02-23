//
// Created by ldir on 21.02.2021.
//

#ifndef URXLIB_UTILS_HPP
#define URXLIB_UTILS_HPP

#include <urx.hpp>

template<typename T>
class LastValue : public urx::Observer<T> {
    void on_next(const T &val) override {
        last = val;
    }

public:
    using urx::Observer<T>::Observer;
    T last = -1;
};

template<typename ...T>
class CounterValue : public urx::Observer<T...> {
    void on_next(const T &...) override {
        ++counter;
    }

public:
    using urx::Observer<T...>::Observer;
    int counter = 0;
};


#endif //URXLIB_UTILS_HPP
