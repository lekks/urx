//
// Created by ldir on 21.02.2021.
//

#ifndef URXLIB_URX_FUNCTIONAL_HPP
#define URXLIB_URX_FUNCTIONAL_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename F, typename ...T>
    class Filter : public Observable<T...>, public Observer<T...> {
        const F predicate;

        virtual void on_next(const T &...value) {
            if (predicate(value...)) {
                this->next(value...);
            }
        }

    public:
        Filter(F func) : predicate(func) {};

    };

    template<typename ...T, typename F>
    Filter<F, T...> make_filter(F &&func) {
        return Filter<F, T...>(func);
    }

    template<typename F, typename S, typename D>
    class Map : public Observer<S>, public Observable<D> {
        const F function;

        virtual void on_next(const S &value) {
            this->next(function(value));
        }

    public:
        Map(F func) : function(func) {};

    };

    template<typename S, typename D, typename F>
    Map<F, S, D> make_map(F &&func) {
        return Map<F, S, D>(func);
    }


    template<typename F, typename S, typename D>
    class Scan : public Observer<S>, public Observable<D> {
        const F function;
        D accumulator;

        virtual void on_next(const S &value) {
            accumulator = function(accumulator, value);
            this->next(accumulator);
        }

    public:
        Scan(F func, const D &initial) : function(func), accumulator(initial) {};

    };

    template<typename S, typename D, typename F>
    Scan<F, S, D> make_scan(F &&func, const D &initial) {
        return Scan<F, S, D>(func, initial);
    }


}

#endif //URXLIB_URX_FUNCTIONAL_HPP
