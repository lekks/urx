#ifndef URX_OBSERVER_BASE_HPP
#define URX_OBSERVER_BASE_HPP


namespace urx {

    class ObserversList;

    class ObserverBase {
        friend class ObserversList;

        ObserverBase *next_listener = nullptr;
        ObserversList *listeners = nullptr;
    public:
        ObserverBase &operator=(ObserverBase &) = delete;

        ObserverBase(ObserverBase &) = delete;

        ObserverBase(ObserverBase &&) = default;

        ObserverBase() = default;

        bool is_connected() {
            return listeners != nullptr;
        };
    };

    class ObserversList {
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
                    listener->next_listener = 0;
                    listener->next_listener = 0;
                } else {
                    remove_listener(dst->next_listener, listener);
                }
            }
        };
    public:
        ObserversList() : first_listener(nullptr) {};

        ~ObserversList() {
            //TODO remove_all_listeners();
        };

        inline ObserverBase *get_first_listener() const {
            return first_listener;
        }

        static inline ObserverBase *next_conn(ObserverBase *listener) {
            return listener->next_listener;
        }

        void add_listener(ObserverBase *listener) {
            if (listener->next_listener)
                listener->listeners->remove_listeners(listener);
            add_listener(first_listener, listener);
            listener->listeners = this;
        };

        void remove_listeners(ObserverBase *plug) {
            remove_listener(first_listener, plug);
        };

        // TODO void remove_all_listeners() {}
    };

}

#endif // URX_OBSERVER_BASE_HPP

