//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_OBSERVER_HPP
#define URXLIB_URX_OBSERVER_HPP

#include "urx_observer_base.hpp"

namespace urx {
    template<typename ...T>
    class Observable;

    template<typename ...T>
    class Observer : public ObserverBase {
    public:
        Observer() = default;

        inline explicit Observer(Observable<T...> &observable) {
            observable.subscribe(*this);
        }

        virtual void on_next(const T &...value) {}; //TODO =0
    };


    template<typename ...T>
    class Observable {
        ObserversList observers;
    public:
        Observable &operator=(Observable &) = delete;

        void subscribe(Observer<T...> &observer) {
            observers.add(&observer);
        };

        void unsubscribe(Observer<T...> &observer) {
            observers.remove(&observer);
        };

        void next(const T &...value) {
            for (ObserverBase *conn = observers.first_conn(); conn; conn = observers.next_conn(conn)) {
                static_cast<Observer<T...> *>(conn)->on_next(value...);
            }
        };
    };

    template<typename ...S, typename Dst>
    Dst& operator>>(Observable<S...> &src, Dst &dst)
    {
        src.subscribe(dst);
        return dst;
    }

    template<typename ...S, typename Dst>
    Dst& operator | (Observable<S...> &src, Dst &dst)
    {
        src.subscribe(dst);
        return dst;
    }

}

#endif //URXLIB_URX_OBSERVER_HPP
