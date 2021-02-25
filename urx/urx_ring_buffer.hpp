/*
 * RingBuffer.h
 *
 *  Created on: 06 ����� 2014 �.
 *      Author: Ldir
 */

#ifndef URXLIB_RINGBUFFER_HPP_
#define URXLIB_RINGBUFFER_HPP_

namespace urx {

    template<int SIZE, typename T>
    class RingBuffer {
        T buffer[SIZE + 1];
        volatile unsigned write_index;
        volatile unsigned read_index;

        inline unsigned next(unsigned n) const {
            if (n == SIZE) return 0;
            else return n + 1;
        };
    public:
        int get_size() const { return SIZE; }

        bool have_data() const {
            return (read_index != write_index);
        }

        bool have_space() const {
            return (next(write_index) != read_index);
        }

        bool put(const T &value) {
            if (have_space()) {
                buffer[write_index] = value;
                write_index = next(write_index);
                return true;
            } else
                return false;
        }

        bool get(T *value) {
            if (have_data()) {
                *value = buffer[read_index];
                read_index = next(read_index);
                return true;
            } else
                return false;
        }

        T *front() {
            if (have_data()) {
                return &buffer[read_index];
            } else
                return 0;
        }

        void pop() {
            if (have_data()) {
                read_index = next(read_index);
            }
        }

        void clear() { // Not thread safe
            read_index = write_index = 0;
        }

        RingBuffer() : write_index(0), read_index(0) {};
    };

} /* namespace  */

#endif /* RINGBUFFER_H_ */
