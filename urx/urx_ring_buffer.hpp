﻿/*
 * SafeRingBuffer.h
 *
 *  Created on: 06 ����� 2014 �.
 *      Author: Ldir
 */

#ifndef URXLIB_RINGBUFFER_HPP_
#define URXLIB_RINGBUFFER_HPP_

namespace urx {

    template<int SIZE, typename T, typename AtomicIndex>
    class SafeRingBuffer {
        T buffer[SIZE + 1];
        AtomicIndex write_index;
        AtomicIndex read_index;

        inline unsigned next(unsigned n) const {
            if (n == SIZE) return 0;
            else return n + 1;
        };
    public:
        int get_size() const { return SIZE; }

        bool is_empty() const {
            return (read_index == write_index);
        }

        bool is_full() const {
            return (next(write_index) == read_index);
        }

        bool put(const T &value) {
            if (is_full()) {
                return false;
            } else {
                buffer[write_index] = value;
                write_index = next(write_index);
                return true;
            }
        }

        bool get(T *value) {
            if (is_empty()) {
                return false;
            } else {
                *value = buffer[read_index];
                read_index = next(read_index);
                return true;
            }
        }

        T *front() {
            if (is_empty()) {
                return 0;
            } else {
                return &buffer[read_index];
            }
        }

        void pop() {
            if (!is_empty()) {
                read_index = next(read_index);
            }
        }

        void clear() { // Not thread safe
            read_index = write_index = 0;
        }

        SafeRingBuffer() : write_index(0), read_index(0) {};
    };

} /* namespace  */

#endif /* URXLIB_RINGBUFFER_HPP_ */
