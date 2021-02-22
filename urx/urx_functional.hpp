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

        virtual void on_next(const T &...value) {
            if(predicate(value...)) {
                this->next(value...);
            }
        }

    };

    template<typename ...T, typename F>
    Filter<F, T...> make_filter(F&& func) {
        return Filter<F, T...>(func);
    }

    template<typename F, typename ...T>
    class Map : public Observable<T...>, public Observer<T...> {
        const F function;

    public:
        Map(F func) : function(func) {};

        virtual void on_next(const T &...value) {
            this->next(function(value...));
        }

    };

    template<typename ...T, typename F>
    Map<F, T...> make_map(F&& func) {
        return Map<F, T...>(func);
    }

}

#endif //URXLIB_URX_FUNCTIONAL_HPP
