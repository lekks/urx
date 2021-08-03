#ifndef URX_OBSERVER_BASE_HPP
#define URX_OBSERVER_BASE_HPP


namespace urx {

    class ObserversList;

    class ObserverBase {
        friend class ObserversList;

        ObserverBase *next_listener = nullptr;
        ObserversList *observable = nullptr;
    public:
        ObserverBase &operator=(ObserverBase &) = delete;

        ObserverBase(ObserverBase &) = delete;

        ObserverBase(ObserverBase &&) = default;

        ObserverBase() = default;

        virtual ~ObserverBase() = default;

        bool is_connected() {
            return observable != nullptr;
        };
    };

    class ObserversList final {
        ObserverBase *first_listener;

        static void add_listener(ObserverBase *&dst, ObserverBase *listener) {
            if (dst && (dst != listener)) { // search duplicates
                add_listener(dst->next_listener, listener);
            } else {
                dst = listener;
            }
        };

        static void remove_listener(ObserverBase *&dst, ObserverBase *listener) {
            if (dst) {
                if (dst == listener) {
                    dst = listener->next_listener;
                    listener->next_listener = nullptr;
                    listener->observable = nullptr;
                } else {
                    remove_listener(dst->next_listener, listener);
                }
            }
        };
    public:
        ObserversList() : first_listener(nullptr) {};

        ~ObserversList() {
            remove_all_listeners();
        };

        inline ObserverBase *get_first_listener() const {
            return first_listener;
        }

        static inline ObserverBase *next_conn(ObserverBase *listener) {
            return listener->next_listener;
        }

        void add_listener(ObserverBase *listener) {
            if (listener->observable)
                listener->observable->remove_listener(listener);
            add_listener(first_listener, listener);
            listener->observable = this;
        };

        void remove_listener(ObserverBase *listener) {
            remove_listener(first_listener, listener);
        };

        void remove_all_listeners() {
            while (ObserverBase *listener = get_first_listener()) {
                remove_listener(first_listener, listener);
            }
        }
    };

}

#endif // URX_OBSERVER_BASE_HPP

