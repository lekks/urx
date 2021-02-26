//
// Created by ldir on 23.02.2021.
//

#ifndef URXLIB_URX_BUFFERS_HPP
#define URXLIB_URX_BUFFERS_HPP

#include "urx_observer.hpp"
#include "urx_ring_buffer.hpp"

namespace urx {

    template<typename T>
    class LastBuffer : public Observer<T> {
        T last;

        void on_next(const T &val) override {
            last = val;
        }

    public:
        using Observer<T>::Observer;

        LastBuffer() = default;

        LastBuffer(const T &initial) : last(initial) {};

        inline const T &get_last() const {
            return last;
        }
    };

    template<int SIZE, typename T, class BufferType>
    class BasicFifoBuffer : public Observer<T> {
        BufferType ring;

        void on_next(const T &val) override {
            ring.put(val);
        }

    public:
        using Observer<T>::Observer;

        inline bool is_empty() const { return ring.is_empty(); }

        inline bool is_full() const { return ring.is_full(); }

        inline bool take(T *val) { return ring.get(val); }

        T *front() { return ring.front(); }

        void pop() { ring.pop(); }

        int get_size() const { return SIZE; }
    };

    template<int SIZE, typename T>
    using FifoBuffer = BasicFifoBuffer<SIZE, T, RingBuffer<SIZE, T, unsigned >>;
};


#endif //URXLIB_URX_BUFFERS_HPP
