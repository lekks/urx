//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_POC_HPP
#define URXLIB_URX_POC_HPP

#include "urx_observer.hpp"

namespace urx {



    template<int inputs_num, typename ...T>
    class Merge : public Observable<T...> {
        Observer<T...> inputs[inputs_num];

    public:

        void on_next(const T &...value) override {
            this->next(value...);
        };

        Observer<T...> &input(int i) {
            return &inputs[i];
        }

    };

}

#endif //URXLIB_URX_POC_HPP
