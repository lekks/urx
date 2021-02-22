//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_SUBJECT_HPP
#define URXLIB_URX_SUBJECT_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename ...T>
    class Subject : public Observer<T...>, public Observable<T...> {
    public:
        void on_next(const T &...value) override {
            this->next(value...);
        };

        Observable<T...>& get_observable() {
            return *this;
        }

        Observer<T...>& get_observer() {
            return *this;
        }

    };

}

#endif //URXLIB_URX_SUBJECT_HPP
