//
// Created by ldir on 23.02.2021.
//

#ifndef URXLIB_URX_BUFFERS_HPP
#define URXLIB_URX_BUFFERS_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename T>
    class Last : public urx::Observer<T> {
        T last;

        void on_next(const T &val) override {
            last = val;
        }

    public:
        using urx::Observer<T>::Observer;

        Last() = default;

        Last(const T &initial) : last(initial) {};

        inline const T &get_last() const {
            return last;
        }
    };
};


#endif //URXLIB_URX_BUFFERS_HPP
