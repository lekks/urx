//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_SUBJECT_HPP
#define URXLIB_URX_SUBJECT_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename ...T>
    class Subject : public Observer<T...>, public Observable<T...> {
        virtual void on_next(const T &...value) override {
            this->next(value...); // https://stackoverflow.com/questions/10639053/name-lookups-in-c-templates
        };
    };

}

#endif //URXLIB_URX_SUBJECT_HPP
