//
// Created by ldir on 24.02.2021.
//

#ifndef URXLIB_URX_DECOUPLE_HPP
#define URXLIB_URX_DECOUPLE_HPP

namespace urx {

    enum class DecouplerNoSpaceStrategy {
        DROP_OLDEST,
        DROP_NEWEST,
        PUSH_OLDEST,
    };

    template<int SIZE, typename T, class BufferType>
    class BasicNonBlockingDecoupler : public Observer<T>, public Observable<T> {
    private:
        BufferType ring;
        DecouplerNoSpaceStrategy noSpaceStrategy = DecouplerNoSpaceStrategy::DROP_NEWEST;

        void on_next(const T &val) override {
            if (!ring.put(val)) {
                switch (noSpaceStrategy) {
                    case DecouplerNoSpaceStrategy::DROP_OLDEST:
                        ring.pop();
                        ring.put(val);
                        break;
                    case DecouplerNoSpaceStrategy::PUSH_OLDEST:
                        process_one();
                        ring.put(val);
                        break;
                    case DecouplerNoSpaceStrategy::DROP_NEWEST:
                        //No actions
                        break;
                }
            }
        }

    public:
        using Observer<T>::Observer;

        BasicNonBlockingDecoupler(DecouplerNoSpaceStrategy noSpaceStrategy) : noSpaceStrategy(noSpaceStrategy) {};

        bool process_one() {
            T val;
            if (ring.get(&val)) {
                this->next(val);
                return true;
            } else {
                return false;
            }
        }

        bool process_all() {
            T val;
            bool processed_something = false;
            while (ring.get(&val)) {
                this->next(val);
                processed_something = true;
            }
            return processed_something;
        }

        void set_strategy(DecouplerNoSpaceStrategy strategy) { noSpaceStrategy = strategy; };

        inline bool is_empty() const { return ring.is_empty(); }

        inline bool is_full() const { return ring.is_full(); }
    };

    template<int SIZE, typename Data, typename AtomicIndex=unsigned int>
    using NonBlockingDecoupler = BasicNonBlockingDecoupler<SIZE, Data, SafeRingBuffer < SIZE, Data, AtomicIndex >>;

}

#endif //URXLIB_URX_DECOUPLE_HPP
