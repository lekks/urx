//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_SUBJECT_HPP
#define URXLIB_URX_SUBJECT_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename ...T>
    class Subject : public Observer<T...>, public Observable<T...> {

        void on_next(const T &...value) override {
            this->next(value...);
        };

    public:
        using urx::Observer<T...>::Observer;

    };

}

#endif //URXLIB_URX_SUBJECT_HPP
