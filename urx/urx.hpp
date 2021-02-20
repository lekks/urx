//
// Created by ldir on 14.02.2021.
//

#ifndef URX_URX_HPP
#define URX_URX_HPP

#include "urx_baseconnector.hpp"

namespace urx {
    template<typename ...T>
    class Observable;

    template<typename ...T>
    class Observer : public BaseConnector {
    public:
        Observer() = default;

        inline explicit Observer(Observable<T...> &observable) {
            observable.subscribe(*this);
        }

        virtual void on_next(const T &...value) {}; //TODO =0
    };


    template<typename ...T>
    class Observable {
        ConnectorList observers;
    public:
        Observable &operator=(Observable &) = delete;

        void subscribe(Observer<T...> &observer) {
            observers.add(&observer);
        };

        void unsubscribe(Observer<T...> &observer) {
            observers.remove(&observer);
        };

        void next(const T &...value) {
            for (BaseConnector *conn = observers.first_conn(); conn; conn = observers.next_conn(conn)) {
                static_cast<Observer<T...> *>(conn)->on_next(value...);
            }
        };
    };

    template<typename ...T>
    class Subject : public Observer<T...>, public Observable<T...> {
        virtual void on_next(const T &...value) override {
            this->next(value...); // https://stackoverflow.com/questions/10639053/name-lookups-in-c-templates
        };
    };

    template<typename S, typename D>
    class Convert : public Observable<D>, public Observer<S> {
    };

}
#endif //URX_URX_HPP
