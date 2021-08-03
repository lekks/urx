//
// Created by ldir on 24.02.2021.
//

#ifndef URXLIB_URX_DSP_HPP
#define URXLIB_URX_DSP_HPP

#include "urx_observer.hpp"

namespace urx {

    /* To Implement:
     * Resample with averaging
     * Transform (multiply on matrix or polynom)
     * Exponential filter
     * Window average
     * Swinging door filter
     * Filer small changes
     * Hysteresis
     * Integrator
     * Differentiator
     * Min
     * Max
     * Average
     * Count
     */

    template<typename T>
    class Distinct : public Observable<T>, public Observer<T> {
        bool is_set = false;
        T last;

        void on_next(const T &value) override {
            if (!is_set || last != value) {
                is_set = true;
                last = value;
                this->next(value);
            }
        }
    };


}
#endif //URXLIB_URX_DSP_HPP
