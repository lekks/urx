//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_OBSERVER_HPP
#define URXLIB_URX_OBSERVER_HPP

#include "urx_observers_list.hpp"

namespace urx {
    template<typename ...T>
    class Observable;

    template<typename ...T>
    class Observer : public ObserverBase {
        virtual void on_next(const T &...value) = 0;

    public:
        Observer() = default;

        explicit Observer(Observable<T...> &observable) {
            observable.subscribe(*this);
        }

        inline void call_on_next(const T &...value) {
            on_next(value...);
        }

        inline Observer<T...> &get_observer() {
            return *this;
        }

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
            observers.remove_listener(&observer);
        };

        void unsubscribe_all() {
            observers.remove_all_listeners();
        }

        void next(const T &...value) const {
            for (ObserverBase *conn = observers.get_first_listener(); conn; conn = ObserversList::next_conn(conn)) {
                static_cast<Observer<T...> *>(conn)->call_on_next(value...);
            }
        };

        inline Observable<T...> &get_observable() {
            return *this;
        }

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
