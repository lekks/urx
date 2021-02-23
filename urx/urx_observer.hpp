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

        explicit Observer(Observable<T...> &observable) {
            observable.subscribe(*this);
        }

        virtual void on_next(T &&...value) = 0;
    };


    template<typename ...T>
    class Observable {
        ObserversList observers;
    public:
        Observable &operator=(Observable &) = delete;

        virtual ~Observable() = default;

        void subscribe(Observer<T...> &observer) {
            observers.add_listener(&observer);
        };

        void unsubscribe(Observer<T...> &observer) {
            observers.remove_listeners(&observer);
        };

        void next(T &&...value) {
            for (ObserverBase *conn = observers.get_first_listener(); conn; conn = ObserversList::next_conn(conn)) {
                static_cast<Observer<T...> *>(conn)->on_next(std::forward<T>(value)...);
            }
        };
    };

    template<typename ...S, typename Observer>
    Observer &operator>>(Observable<S...> &observable, Observer &observer) {
        observable.subscribe(observer);
        return observer;
    }

    template<typename ...S, typename Observer>
    Observer &operator|(Observable<S...> &observable, Observer &observer) {
        observable.subscribe(observer);
        return observer;
    }

}

#endif //URXLIB_URX_OBSERVER_HPP
