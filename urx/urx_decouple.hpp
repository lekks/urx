//
// Created by ldir on 24.02.2021.
//

#ifndef URXLIB_URX_DECOUPLE_HPP
#define URXLIB_URX_DECOUPLE_HPP

namespace urx {

    template<int SIZE, typename T, class BufferType>
    class BasicNonBlockingDecoupler : public Observer<T>, public Observable<T> {
    public:
        enum class NoSpaceStrategy {
            DROP_OLDEST,
            DROP_NEWEST,
            PUSH_OLDEST,
        };

    private:
        BufferType ring;
        NoSpaceStrategy noSpaceStrategy = NoSpaceStrategy::DROP_NEWEST;

        void on_next(const T &val) override {
            if (!ring.put(val)) {
                switch (noSpaceStrategy) {
                    case NoSpaceStrategy::DROP_OLDEST:
                        ring.pop();
                        ring.put(val);
                        break;
                    case NoSpaceStrategy::PUSH_OLDEST:
                        process_one();
                        ring.put(val);
                        break;
                    case NoSpaceStrategy::DROP_NEWEST:
                        //No actions
                        break;
                }
            }
        }


    public:


        using Observer<T>::Observer;

        BasicNonBlockingDecoupler(NoSpaceStrategy noSpaceStrategy) : noSpaceStrategy(noSpaceStrategy) {};

        bool process_one() {
            T val;
            if (ring.get(val)) {
                this->emit(val);
            } else {
                return false;
            }
        }

        bool process_all() {
            T val;
            bool processed_something = false;
            while (ring.get(val)) {
                this->emit(val);
            }
            return processed_something;
        }

        inline bool is_empty() const { return ring.is_empty(); }

        inline bool is_full() const { return ring.is_full(); }
    };

    template<int SIZE, typename Data, typename AtomicIndex=unsigned int>

    using NonBlockingDecoupler = BasicNonBlockingDecoupler<SIZE, Data, RingBuffer < SIZE, Data, AtomicIndex >>;

}

#endif //URXLIB_URX_DECOUPLE_HPP
