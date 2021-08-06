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
        explicit Filter(F func) : predicate(func) {};

        Filter(F func, Observable<T...> &observable) : Observer<T...>(observable), predicate(func) {};

    };

    template<typename ...T, typename F>
    Filter<F, T...> make_filter(F &&func) {
        return Filter<F, T...>(func);
    }

    template<typename ...T, typename F>
    Filter<F, T...> make_filter(F &&func, Observable<T...> &observable) {
        return Filter<F, T...>(func, observable);
    }

    template<typename F, typename D, typename ...S>
    class Map : public Observable<D>, public Observer<S...> {
        const F function;

        virtual void on_next(const S &...value) {
            this->next(function(value...));
        }

    public:
        explicit Map(F func) : function(func) {};

        Map(F func, Observable<S...> &observable) : Observer<S...>(observable), function(func) {};

    };

    template<typename D, typename ...S, typename F>
    Map<F, D, S...> make_map(F &&func) {
        return Map<F, D, S...>(func);
    }

    template<typename D, typename ...S, typename F>
    Map<F, D, S...> make_map(F &&func, Observable<S...> &observable) {
        return Map<F, D, S...>(func, observable);
    }


    template<typename F, typename D, typename ...S>
    class Reduce : public Observable<D>, public Observer<S...> {
        const F function;
        D accumulator;

        virtual void on_next(const S &...value) {
            accumulator = function(accumulator, value...);
            this->next(accumulator);
        }

    public:
        Reduce(F func, const D &initial) : function(func), accumulator(initial) {};

        Reduce(F func, const D &initial, Observable<S...> &observable) : Observer<S...>(observable),
                                                                         function(func), accumulator(initial) {};

        const D &get() const {
            return accumulator;
        }
    };

    template<typename D, typename ...S, typename F>
    Reduce<F, D, S...> make_reduce(F &&func, const D &initial) {
        return Reduce<F, D, S...>(func, initial);
    }

    template<typename D, typename ...S, typename F>
    Reduce<F, D, S...> make_reduce(F &&func, const D &initial, Observable<S...> &observable) {
        return Reduce<F, D, S...>(func, initial, observable);
    }


    template<typename F, typename ...S>
    class Function : public Observer<S...> {
        const F function;

        virtual void on_next(const S &...value) {
            function(value...);
        }

    public:
        explicit Function(F func) : function(func) {};

        Function(F func, Observable<S...> &observable) : Observer<S...>(observable), function(func) {};

    };

    template<typename ...S, typename F>
    Function<F, S...> make_function(F &&func) {
        return Function<F, S...>(func);
    }

    template<typename ...S, typename F>
    Function<F, S...> make_function(F &&func, Observable<S...> &observable) {
        return Function<F, S...>(func, observable);
    }

}

#endif //URXLIB_URX_FUNCTIONAL_HPP
