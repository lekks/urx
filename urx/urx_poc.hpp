//
// Created by ldir on 20.02.2021.
//

#ifndef URXLIB_URX_POC_HPP
#define URXLIB_URX_POC_HPP

#include "urx_observer.hpp"

namespace urx {

    template<typename ...T>
    class Topic {
    public:
        Observable<T...> get_observable() {};
    };

    template<typename S, typename D>
    class Convert : public Observable<D>, public Observer<S> {
    };

}

#endif //URXLIB_URX_POC_HPP
