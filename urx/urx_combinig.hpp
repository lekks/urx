//
// Created by ldir on 23.02.2021.
//

#ifndef URXLIB_URX_COMBINIG_HPP
#define URXLIB_URX_COMBINIG_HPP

#include "urx_observer.hpp"

namespace urx {

    template<int inputs_num, typename ...T>
    class Merge : public Observable<T...> {

        class MergeInput : public urx::Observer<T...> {
            void on_next(const T &...val) override {
                output->emit(val...);
            }

        public:
            Observable<T...> *output;
        };


        Merge::MergeInput inputs[inputs_num];

    public:
        Merge() {
            for (int i = 0; i < inputs_num; ++i) {
                inputs[i].output = this;
            }
        }

        Observer<T...> &input(int i) {
            return inputs[i];
        }

    };

}

#endif //URXLIB_URX_COMBINIG_HPP
