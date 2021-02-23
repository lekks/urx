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

    public:
        Filter(F func) : predicate(func) {};

        virtual void on_next(T &&...value) {
            if (predicate(value...)) {
                this->next(std::forward<T>(value)...);
            }
        }

    };

    template<typename ...T, typename F>
    Filter<F, T...> make_filter(F &&func) {
        return Filter<F, T...>(func);
    }

    template<typename F, typename S, typename D>
    class Map : public Observer<S>, public Observable<D> {
        const F function;

    public:
        Map(F func) : function(func) {};

        virtual void on_next(S &&value) {
            this->next(function(value));
        }

    };

    template<typename S, typename D, typename F>
    Map<F, S, D> make_map(F &&func) {
        return Map<F, S, D>(func);
    }

}

#endif //URXLIB_URX_FUNCTIONAL_HPP
